/*
 * QBtServiceDiscoverer_symbian.h
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

#ifndef QBTSERVICEDISCOVERER_SYMBIAN_H_
#define QBTSERVICEDISCOVERER_SYMBIAN_H_

#include <e32base.h>

#include <coecntrl.h>
#include <es_sock.h>
#include <btdevice.h>
#include <bt_sock.h>
#include <btsdp.h>

#include <QMap>
#include <QSet>
#include <QBtDevice.h>
#include <QBtServiceDiscoverer.h>


//____________________________________________________________________________
//
// Auxiliary classes for getting attribute values

class AttrVisitor : public MSdpAttributeValueVisitor
{
   public:

      AttrVisitor()
      { reset(); }

      virtual ~AttrVisitor()
      {}

      virtual void clear()
      {}

      void reset ()
      { clear(); }


   public:

      void VisitAttributeValueL(CSdpAttrValue& aValue, TSdpElementType aType)
      {}

      void StartListL(CSdpAttrValueList &aList)
      {}

      void EndListL()
      {}

};


//____________________________________________________________________________
//
//

class ProtocolListVisitor : public AttrVisitor
{
   public:


      void VisitAttributeValueL(CSdpAttrValue& aValue, TSdpElementType aType);

      void clear()
      { _protocols.clear(); _port = 0; }


      uint getPort () const
      { return _port; }


      QList<QBtUuid> getProtocols() const
      { return _protocols; }

      void print();

   private:

      QList<QBtUuid> _protocols;
      uint _port;


};


//____________________________________________________________________________
//
//

class StringVisitor : public AttrVisitor
{
   public:

      void VisitAttributeValueL(CSdpAttrValue& aValue, TSdpElementType aType);

      void clear()
      { _str.clear(); }

      QString get () const
       { return _str; }

      void print();

   private:
      QString _str;
};


//____________________________________________________________________________
//
// TODO: Some services return more than one UUID, how to handle these in QBtService?
//

class ServiceUuidVisitor : public AttrVisitor
{
   public:


      void VisitAttributeValueL(CSdpAttrValue& aValue, TSdpElementType aType);

      void clear()
      { _uuid.clear(); }


      // TODO
      QBtUuid get() const
      {
         if (_uuid.empty())
            return QBtUuid();
         else
            return _uuid [0];
      }

    void print();


   private:
      QList<QBtUuid> _uuid;

};


//____________________________________________________________________________
//
// Simple class to keep service record data we are interested in requesting.

class ServiceRecord
{
   public:
      ServiceRecord()
      {
         attributesToProcess.append (KSdpAttrIdBasePrimaryLanguage + KSdpAttrIdOffsetServiceName);
         attributesToProcess.append (KSdpAttrIdServiceClassIDList);
         attributesToProcess.append (KSdpAttrIdProtocolDescriptorList);
      }


   public:

      QString getName() const
      { return name.get(); }

      QBtUuid getUuid() const
      { return uuid.get(); }

      QList<QBtUuid> getProtocols() const
      { return protocols.getProtocols(); }

      uint getPort() const
      { return protocols.getPort(); }


      void print()
      {
         name.print();
         uuid.print();
         protocols.print();
      }


   public:

      QList <TSdpAttributeID> attributesToProcess;
      StringVisitor           name;
      ServiceUuidVisitor      uuid;
      ProtocolListVisitor     protocols;
};



//____________________________________________________________________________
//
//

class QBtServiceDiscovererPrivate : public CBase, public MSdpAgentNotifier
{
   public:


       //
       static QBtServiceDiscovererPrivate* NewL(QBtServiceDiscoverer* publicClass);

       //
       static QBtServiceDiscovererPrivate* NewLC(QBtServiceDiscoverer* publicClass);

       //
       ~QBtServiceDiscovererPrivate();


   public:

      // discover obex and rfcomm services
      void DiscoverServices (QBtDevice* targetDevice);

      // as is
      void DiscoverObexServices (QBtDevice* targetDevice);


      // as is
      void DiscoverRfcommServices (QBtDevice* targetDevice);

      //  discover a service belongin to the uuid, can be a service or protocol
      void DiscoverSpecificClass (QBtDevice* targetDevice, const QBtUuid & uuid);

      // discover services based on uuid list
      void DiscoverSpecificClasses (QBtDevice* targetDevice, const QList<QBtUuid> & uuids);



      // stops everything
      void StopDiscovery();

    
      // true if in discovery
      bool IsBusy() const;

   private:

      //
      QBtServiceDiscovererPrivate(QBtServiceDiscoverer* publicClass);

      //
      void ConstructL();


      // perfoms discovery for a particular uuid
      void _DiscoverSpecificClass (const QBtUuid & uuid);



      // inherited
      // called when an service record (CSdpAgent::NextRecordRequestL()) operation completes.
      void NextRecordRequestComplete (TInt aError, TSdpServRecordHandle aHandle, TInt aTotalRecordsCount);


      // inherited
      // Called by the attribute request (CSdpAgent::AttributeRequestL()) to pass the results of successful attribute request.
      //
      void AttributeRequestResult (TSdpServRecordHandle aHandle, TSdpAttributeID aAttrID, CSdpAttrValue* aAttrValue);


      // inhrited
      // Called when the attribute request (CSdpAgent::AttributeRequestL()) completes.
      void AttributeRequestComplete (TSdpServRecordHandle aHandle, TInt aError);


      // declare discovery as finished
      void FinishDiscovery();

      // misc preparation to start discovery
      void PrepareSearch (QBtDevice* targetDevice);

      // process next uuid in the list
      void ProcessNextService();


   private:

      // service discovery agent
      CSdpAgent* _agent;

      // service discovery search pattern
      CSdpSearchPattern* _searchPattern;


      // list of uuids to search
      QList <QBtUuid> _uuidList;

      // list of found services
      QBtService::List _serviceList;

      // set of found uuids, used to avoid duplicates in the results
      QSet<QString> _serviceUuidsFound;

      // device to query
      QBtDevice* _targetDevice;

      // pointer to parent object (from constructor). Not owned by this class
      QBtServiceDiscoverer *_parent_ptr;


      // service record data
      QMap <TSdpServRecordHandle, ServiceRecord> _serviceRecords;



      // if the process has been started
      bool _discoveryInProgress;

};

#endif /* QBTSERVICEDISCOVERER_SYMBIAN_H_ */
