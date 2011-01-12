/*
 * QBtServiceDiscoverer_symbian.cpp
 *
 *  
 *      Author: Ftylitakis Nikolaos
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "../QBtServiceDiscoverer_symbian.h"
#include "../../QBtAuxFunctions.h"
#include <btsdp.h>
#include <e32des8.h>

#include <QMessageBox>


// debug aid
inline void MSG(const QString & m)
{ qDebug() << m; }


//____________________________________________________________________________

QBtServiceDiscovererPrivate* QBtServiceDiscovererPrivate::NewL(QBtServiceDiscoverer* publicClass)
{
	QBtServiceDiscovererPrivate* self = QBtServiceDiscovererPrivate::NewLC(publicClass);
	CleanupStack::Pop(self);
	return self;
}


//____________________________________________________________________________

QBtServiceDiscovererPrivate* QBtServiceDiscovererPrivate::NewLC(QBtServiceDiscoverer* publicClass)
{
	QBtServiceDiscovererPrivate* self = new (ELeave) QBtServiceDiscovererPrivate(publicClass);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
}


//____________________________________________________________________________

void QBtServiceDiscovererPrivate::ConstructL()
{}


//____________________________________________________________________________

QBtServiceDiscovererPrivate::QBtServiceDiscovererPrivate (QBtServiceDiscoverer* publicClass)
    : _agent(0),
      _searchPattern(0),
      _parent_ptr(publicClass),
      _discoveryInProgress (false)
{}


//____________________________________________________________________________

QBtServiceDiscovererPrivate::~QBtServiceDiscovererPrivate()
{
	// must not throw/leave
    //TRAPD (error, StopDiscovery() );
    TRAPD (error, FinishDiscovery() );
}


//____________________________________________________________________________

void QBtServiceDiscovererPrivate::FinishDiscovery()
{
   if (_discoveryInProgress == false)
      return;

   _discoveryInProgress = false;

   if (_agent)
   {
      _agent->Cancel();
      delete _agent;
      _agent = 0;
   }

   if (_searchPattern)
   {
      _searchPattern->Reset();
      delete _searchPattern;
      _searchPattern= 0;
   }


}

//____________________________________________________________________________

void QBtServiceDiscovererPrivate::PrepareSearch (QBtDevice* targetDevice)
{
   _targetDevice = targetDevice;

   _uuidList.clear();
   _serviceList.clear();
   _serviceUuidsFound.clear();
}

//____________________________________________________________________________

void QBtServiceDiscovererPrivate::DiscoverObexServices (QBtDevice* _targetDevice)
{
   PrepareSearch (_targetDevice);

   _uuidList.append(QBtUuid (QBtConstants::OBEX));
   _DiscoverSpecificClass (_uuidList [0]);
}


//____________________________________________________________________________

void QBtServiceDiscovererPrivate::DiscoverRfcommServices (QBtDevice* _targetDevice)
{
   PrepareSearch (_targetDevice);

   _uuidList.append(QBtUuid (QBtConstants::RFCOMM));
   _DiscoverSpecificClass (_uuidList [0]);
}


//____________________________________________________________________________

void QBtServiceDiscovererPrivate::DiscoverServices (QBtDevice* _targetDevice)
{
   PrepareSearch (_targetDevice);

   _uuidList.append(QBtUuid (QBtConstants::RFCOMM));
   _uuidList.append(QBtUuid (QBtConstants::OBEX));

   _DiscoverSpecificClass (_uuidList [0]);
}


//____________________________________________________________________________

void QBtServiceDiscovererPrivate::DiscoverSpecificClasses (QBtDevice* _targetDevice, const QList<QBtUuid> & uuids)
{
   BT_ASSERT_MSG (uuids.length() > 0, "empty uuid list");

   PrepareSearch (_targetDevice);

   _uuidList = uuids;
   _DiscoverSpecificClass (_uuidList [0]);
}

//____________________________________________________________________________

void QBtServiceDiscovererPrivate::DiscoverSpecificClass (QBtDevice* _targetDevice, const QBtUuid & uuid)
{
   BT_ASSERT_MSG (uuid.isNull() == false, "empty uuid");

   PrepareSearch (_targetDevice);

   _uuidList.append(uuid);
   _DiscoverSpecificClass (_uuidList [0]);
}

//____________________________________________________________________________
//
// discover a given services on given device.  a service discovery agent will be
// started to do the discovery of services on given remote device which 
// match to the given uuid

void QBtServiceDiscovererPrivate::_DiscoverSpecificClass (const QBtUuid & uuid)
{
   // end current discovery of any
   FinishDiscovery();

   // toggle guard, setup
   _discoveryInProgress = true;


   // get symbian addr
   const TBTDevAddr devAddress = _targetDevice->getAddress().convertToSymbianBtDevAddr();

   // init new service discovery agent
   _agent = CSdpAgent::NewL( *this, devAddress);

   // set search properties for agent
   _searchPattern = CSdpSearchPattern::NewL();


   // use our service id to filter the services discovered
   // -> will return only the services with matching service id(s)
   TUUID u = QBtUuidToSymbianUuid (uuid);
   _searchPattern->AddL (u);


   // add filter
   _agent->SetRecordFilterL (*_searchPattern);


   // initiate search
   // this will result in call to NextRecordRequestComplete()
   _agent->NextRecordRequestL();

}



//____________________________________________________________________________
//
// called when the service discovery agent has completed discovering services
// on device.  now the attributes of the found service records (if any) must
// be evaluated.  if no service records were discovered, proceed doing
// service discovery on next device.

void QBtServiceDiscovererPrivate::NextRecordRequestComplete (TInt aError,  TSdpServRecordHandle aHandle, TInt aTotalRecordsCount)
{	

   // is this query over?
   if (aError == KErrEof || aTotalRecordsCount == 0)
   {      
      ProcessNextService();
      return;
   }


   // an error ocurred?
   if (aError != KErrNone)
   {
      BT_DEBUG_MSG(QString("[ERROR: %1").arg(aError));

      //discovering new service on target device
      QT_TRYCATCH_LEAVING (emit _parent_ptr->error(QBtServiceDiscoverer::ServiceDiscoveryNotAbleToComplete) );

      //emit _parent_ptr->discoveryStopped("Error-ServiceDiscoveryNotAbleToComplete");
      QT_TRYCATCH_LEAVING(emit _parent_ptr->discoveryStopped() );

      _discoveryInProgress = false;
      return;
   }


   // new entry for service record
   _serviceRecords [aHandle] = ServiceRecord();


   // go for first attribute
   ServiceRecord & record = _serviceRecords [aHandle];
   TRAPD (err, _agent->AttributeRequestL(aHandle, record.attributesToProcess.first() ) );

}



//____________________________________________________________________________
//
// called when the service attributes for the service record have been
// retrieved.

void QBtServiceDiscovererPrivate::AttributeRequestResult (TSdpServRecordHandle aHandle,
                                                          TSdpAttributeID id,
                                                          CSdpAttrValue* aAttrValue)
{
   BT_ASSERT_MSG (_serviceRecords.contains(aHandle), "service not in the map");
   ServiceRecord & record = _serviceRecords [aHandle];

   switch (id)
   {
      case KSdpAttrIdProtocolDescriptorList:
      {
         record.protocols.reset();
         aAttrValue->AcceptVisitorL (record.protocols);

      } break;

      case KSdpAttrIdBasePrimaryLanguage + KSdpAttrIdOffsetServiceName:
      {
         record.name.reset();
         aAttrValue->AcceptVisitorL (record.name);

      } break;


      /*
      case KSdpAttrIdBasePrimaryLanguage + KSdpAttrIdOffsetServiceDescription:
      {
         serviceDescriptionVisitor.prepareToRun();
            aAttrValue->AcceptVisitorL (serviceDescriptionVisitor);
         serviceDescriptionVisitor.setFinished();

         serviceDescriptionVisitor.print();

         delete aAttrValue;

      } break;
      */


      case KSdpAttrIdServiceClassIDList:
      {
         record.uuid.reset();
         aAttrValue->AcceptVisitorL (record.uuid);


      } break;


      default:
      {
         BT_ASSERT_MSG2(false, "unexpected attribute", QString::number(id, 16));
      }


   }

   delete aAttrValue;
}



//____________________________________________________________________________
//
// called when the request to resolve the service attributes for the service
// record completes.  if there are more service records, proceed resolving
// the next service record.

void QBtServiceDiscovererPrivate::AttributeRequestComplete (TSdpServRecordHandle aHandle, TInt aError)
{
   if (aError != KErrNone)
   {
      //QT_TRYCATCH_LEAVING (emit _parent_ptr->error(QBtServiceDiscoverer::ProblemAcquiringNextServiceAttributes) );
      MSG (QString ("<Error> %1").arg(aError) );
      return;
   }

   // get current record
   BT_ASSERT_MSG (_serviceRecords.contains(aHandle), "record not in the map");
   ServiceRecord & record = _serviceRecords [aHandle];


   // discard processed attribute (even if it's empty, as in the case of jumping from AttributeRequestL to AttributeRequestComplete
   record.attributesToProcess.pop_front();


   // if complete, fill, notify and go to the next one
   if (record.attributesToProcess.isEmpty() )
   {
      // check if the service was already found
      QString uuid = record.getUuid().toString();

      if (_serviceUuidsFound.contains (uuid) == false)
      {
         // keep it for the record
         _serviceUuidsFound.insert (uuid);

         // save service
         QBtService service;
         service.setHandle    (aHandle);
         service.setClass     (record.getUuid() );
         service.setName      (record.getName() );
         service.setProtocols (record.getProtocols() );
         service.setPort      (record.getPort());

         _serviceList.append (service);

         QT_TRYCATCH_LEAVING (emit _parent_ptr->newServiceFound (*_targetDevice, service) );

      }
      else
      {
         // duplicate service
      }


      // done with attributes for this record, request next
      TRAPD (err, _agent->NextRecordRequestL());


  }
  else
  {
      // process remaining attributes
      TSdpAttributeID id = record.attributesToProcess.first();

      TRAPD (err,_agent->AttributeRequestL (aHandle, id) );

      if (err != KErrNone)
         { MSG (QString ("<Error-AttributeRequestL> %1").arg(err) ); }


  }



}



//____________________________________________________________________________

void QBtServiceDiscovererPrivate::ProcessNextService()
{
   // discard processed uid
   _uuidList.pop_front();


   if (_uuidList.isEmpty() == false)
   {
      _DiscoverSpecificClass (_uuidList [0]);
   }   
   else
   {
      // save service list
      _targetDevice->setSupportedServices (_serviceList);

      // no more uuids to process, finish discovery
      FinishDiscovery();

      // notify
      QT_TRYCATCH_LEAVING (emit _parent_ptr->discoveryStopped() );
   }


}


//____________________________________________________________________________

bool QBtServiceDiscovererPrivate::IsBusy() const
{
    return _discoveryInProgress;
}



//____________________________________________________________________________
//
// stop discovering services, stop service discovery agent.

void QBtServiceDiscovererPrivate::StopDiscovery()
{
    if (!_discoveryInProgress)
        return;

   FinishDiscovery();


   // notify
   QT_TRYCATCH_LEAVING (emit _parent_ptr->discoveryStopped() );
}


//____________________________________________________________________________

void ProtocolListVisitor::print()
{
   QString p = "{ProtocolListVisitor} ";
   for (int i = 0; i < _protocols.length(); ++i)
   {
      p += _protocols[i].toString();
      p += " ";
   }

   MSG (QString ("%1 (%2) port: %3").arg (p).arg(_protocols.length() ).arg(_port) );
}


//____________________________________________________________________________

void ProtocolListVisitor::VisitAttributeValueL (CSdpAttrValue &aValue, TSdpElementType aType)
{
   switch (aType)
   {
      case ETypeUUID:
      {         
         TPtrC8 uuid(aValue.UUID().ShortestForm());


         // build string
         QString u;
         for (int i = 0; i < uuid.Length(); ++i)
         {
            u += QString ("%1").arg (uuid[i], 2, 16, QLatin1Char('0') );
         }

         // keep
         _protocols.append(QBtUuid (u) );

      break;
      }

      case ETypeUint:
      {
         _port = aValue.Uint();         

      break;
      }


      default:
       // rest don't really matter..
      break;


   }


}


//____________________________________________________________________________

void StringVisitor::print()
{
   MSG (QString ("{StringVisitor} %1").arg (_str) );   
}


//____________________________________________________________________________

void StringVisitor::VisitAttributeValueL (CSdpAttrValue &aValue, TSdpElementType aType)
{
    switch (aType)
    {
        case ETypeString:
        {
            QString s = QString::fromUtf8( (const char*)aValue.Des().Ptr(), aValue.Des().Length() );            
            _str = s;

        } break;

        default:
          break;
    }

}


//____________________________________________________________________________

void ServiceUuidVisitor::print()
{   

   QString p = "{ServiceUuidVisitor} ";
   for (int i = 0; i < _uuid.length(); ++i)
   {
      p += _uuid[i].toString();
      p += " ";
   }

   MSG (p);
}

//____________________________________________________________________________

void ServiceUuidVisitor::VisitAttributeValueL (CSdpAttrValue &aValue, TSdpElementType aType)
{
    switch (aType)
    {
      case ETypeUUID:
      {
         TPtrC8 uuid(aValue.UUID().Des());

         QString u;
         for (int i = 0; i < uuid.Length(); ++i)
         {
            u += QString ("%1").arg (uuid[i], 2, 16, QLatin1Char('0') );
         }

         _uuid.append(QBtUuid (u) );


        } break;

        default:
        {
            // rest don't really matter..            
            break;

        }
    }

}

