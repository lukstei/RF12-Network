/*
 * QBtSerialPortClient_symbian.cpp
 *
 *
 *      Author: Ftylitakis Nikolaos, Luis Valente
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

#include "../QBtSerialPortClient_symbian.h"
#include <QBtAuxFunctions.h>
#include "utf.h"


// protocol constants
_LIT(KStrRFCOMM, "RFCOMM");



//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------

QBtSerialPortClientPrivate* QBtSerialPortClientPrivate::NewL(QBtSerialPortClient* publicClass)
{
    QBtSerialPortClientPrivate* self = QBtSerialPortClientPrivate::NewLC(publicClass);
    CleanupStack::Pop(self);
    return self;
}


QBtSerialPortClientPrivate* QBtSerialPortClientPrivate::NewLC(QBtSerialPortClient* publicClass)
{
    QBtSerialPortClientPrivate* self = new (ELeave) QBtSerialPortClientPrivate(publicClass);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
}


void QBtSerialPortClientPrivate::ConstructL()
{
    if (iSocketServ.Connect() != KErrNone)
       QT_TRYCATCH_LEAVING (emit p_ptr->error(QBtSerialPortClient::ErrorUnavailable) );
    
    
    // timer
    iTimer = CPeriodic::NewL (CIdle::EPriorityIdle);
    
}


QBtSerialPortClientPrivate::QBtSerialPortClientPrivate(QBtSerialPortClient* publicClass)
 : CActive(CActive::EPriorityStandard),
   iState(ENone),
   p_ptr(publicClass),
   iMessage (0)
{
    CActiveScheduler::Add(this);    
}


QBtSerialPortClientPrivate::~QBtSerialPortClientPrivate()
{
    Disconnect();
    
    // delete connect timer
    CancelConnectionTimer();
    delete iTimer;
    
    // disconnect and kill socket
    if(IsActive())
       Cancel();
    
    
    if (iMessage)
     delete iMessage;
}


void QBtSerialPortClientPrivate::DoCancel()
{

}



// ----------------------------------------------------------------------------
// QBtSerialPortClientPrivate::ConnectL(THostName aName, TBTDevAddr aAddr, TInt aPort)
//
// create a connection to given address on given port.
// ----------------------------------------------------------------------------
TBool QBtSerialPortClientPrivate::ConnectL (const QBtDevice& remoteDevice, const QBtService& remoteService)
{		
    if (iState != ENone)        
    { BT_DEBUG_MSG("warning: trying to connect and state != ENone"); return false; }

    device =  remoteDevice;
    service = remoteService;

    // load protocol, RFCOMM
    //TProtocolDesc pdesc;
    //User::LeaveIfError(iSocketServ.FindProtocol(_L("RFCOMM"), pdesc));

    
    // see doc: NOTE: Deprecated default connection scenario
    
    // open socket
    User::LeaveIfError(iSock.Open(iSocketServ, KStrRFCOMM));
    
    // set address and port
    TBTSockAddr addr;
    addr.SetBTAddr(device.getAddress().convertToSymbianBtDevAddr());
    addr.SetPort(service.getPort());
    
    
    // what about these fields?
    //TBTServiceSecurity sec;
    //sec.SetAuthentication(ETrue);
    //sec.SetEncryption(ETrue);
    //addr.SetSecurity(sec);   
    
    
    _addr = addr;

    // connect socket
    TRequestStatus status;
    iSock.Connect(addr, status);  
    
    
    iState = EConnecting;
    
    // start connection timer    
    StartConnectionTimer();
    
            
    // wait (should we wait here? or use the ActiveObject RunL ?)
    User::WaitForRequest(status);
    
    
    // cancel timers    
    CancelConnectionTimer();
    
    
    if (status != KErrNone)
    {
        BT_DEBUG_MSG (QString ("[connect] error detected: %1").arg (status.Int()) );
    	
    	iState = ENone;
    	
    	switch (status.Int())
    	{
    		case KErrTimedOut:
    		case KErrCancel:
    			QT_TRYCATCH_LEAVING (emit p_ptr->error(QBtSerialPortClient::ErrorConnectionTimeout) );
    			break;
    			
    		case KErrAlreadyExists:
				QT_TRYCATCH_LEAVING (emit p_ptr->error(QBtSerialPortClient::ErrorAlreadyConnected) );
				break;
    			
    		case KErrCouldNotConnect:
    		default:
    			QT_TRYCATCH_LEAVING (emit p_ptr->error(QBtSerialPortClient::ErrorOpeningConnection) );
    	
    	}
    	
        return false;
    }

       
    // prepare for receive
    ReceiveData();
   
    // notify
    QT_TRYCATCH_LEAVING (emit p_ptr->connectedToServer() );
    
        
    //SetActive();   
    return true;    
}


// ----------------------------------------------------------------------------
// callback for notifying connection timeout 
//
// ----------------------------------------------------------------------------

TInt QBtSerialPortClientPrivate::ConnectTimerCallBack (TAny* aPtr)
{
    BT_DEBUG_MSG ("[timer] entering");
	
	QBtSerialPortClientPrivate* p = (QBtSerialPortClientPrivate*) aPtr;
		
	// ignore if connection was successful
	if (p->iState != EConnecting)
	{
        BT_DEBUG_MSG ("[timer] got connection, ignoring timeout event");
		return EFalse;
	}	
	
    BT_DEBUG_MSG ("[timer] canceling ActiveObject");
	
	
	if (p->IsActive())
		p->Cancel();
	
	// change state
	p->iState = ENone;
	
    BT_DEBUG_MSG ("[timer] emit error signal");
	
	// emit error
	QT_TRYCATCH_LEAVING (emit p->p_ptr->error (QBtSerialPortClient::ErrorConnectionTimeout));
	
    BT_DEBUG_MSG ("[timer] end");
	
	return EFalse;	
}


void QBtSerialPortClientPrivate::StartConnectionTimer()
{	
	// 30s interval (this should be a parameter)
	TTimeIntervalMicroSeconds32 interval (30 * 1000*1000);	
	
	if (iTimer)
		iTimer->Start (interval, interval, TCallBack (ConnectTimerCallBack, this) );	
}

void QBtSerialPortClientPrivate::CancelConnectionTimer()
{
	if (iTimer)
		iTimer->Cancel();
}

// ----------------------------------------------------------------------------
// QBtSerialPortClientPrivate::Disconnect()
//
// disconnect from remote device, shutdown connected socket
// ----------------------------------------------------------------------------
void QBtSerialPortClientPrivate::Disconnect()
{   	
	if (iState == ENone || iState == EDisconnecting)
    	return;
    
    // 
    iState = EDisconnecting;
    
    
    // cancel timers
    CancelConnectionTimer();
    
    
    // shutdown socket
    TRequestStatus status;
    
    
    // cancel all
    iSock.CancelAll();
    iSock.Shutdown(RSocket::ENormal, status);
    User::WaitForRequest(status);
    iSock.Close();

    iState = ENone;
    
    // check 
    if (status == KErrNone)
    {    	
    	QT_TRYCATCH_LEAVING (emit p_ptr->disconnectedFromServer() );	
    }
    else
    {
    	QT_TRYCATCH_LEAVING (emit p_ptr->error(QBtSerialPortClient::ErrorOnDisconnecting) );
    }        
    
        
    //iState = EDisconnecting;    
    // SetActive();
    // notification will be in RunL with KErrCancel (in case of using SetActive)
    
}

TBool QBtSerialPortClientPrivate::IsConnected()
{
    return (iState == ESending || iState == EWaiting);
}

// ----------------------------------------------------------------------------
// QBtSerialPortClientPrivate::ReceiveDataL()
//
// wait for and receive data from remote device, read connected socket
// ----------------------------------------------------------------------------
void QBtSerialPortClientPrivate::ReceiveData()
{
    // cancel pending operations
    iSock.CancelRead();
    if(IsActive())
        Cancel();
    
    // receive data from socket
    iState=EWaiting;
    iSock.RecvOneOrMore(iBuffer, 0, iStatus, iLen);
    SetActive();
}


// ----------------------------------------------------------------------------
// QBtSerialPortClientPrivate::SendData(const QString& data)
//
// send given data to remote device, write to connected socket
// ----------------------------------------------------------------------------

void QBtSerialPortClientPrivate::SendData (const QString& data)
{
	QByteArray array = data.toUtf8();	
	SendData (array);
}

// ----------------------------------------------------------------------------
// QBtSerialPortClientPrivate::SendData(const QByteArray& data)
//
// send given data to remote device, write to connected socket
// ----------------------------------------------------------------------------
void QBtSerialPortClientPrivate:: SendData (const QByteArray& data)
{
	TPtrC8 desc8 (reinterpret_cast<const TText8*> (data.constData()), data.size());
	 
	// delete previous data
	if (iMessage)
		delete iMessage;
	
	iMessage = HBufC8::NewL(desc8.Length());
	iMessage->Des().Copy(desc8);	
	
    
	// cancel any read requests on socket
    iSock.CancelRead();
    
    if (IsActive())
    	Cancel();
    
    // send message
    iState = ESending;    
 
    iSock.Write (*iMessage, iStatus);    
    SetActive();  
}

// ----------------------------------------------------------------------------
// 
// ----------------------------------------------------------------------------
void QBtSerialPortClientPrivate::RunL()
{
    //BT_DEBUG_MSG (QString ("[RunL status: %1 state: %2]").arg (iStatus.Int()).arg (iState) );
	
	// cancel possible timers
	CancelConnectionTimer();
	
	
	// see what's happened
    if (iStatus != KErrNone)
    {
    	switch (iStatus.Int() )
    	{    		    		
    		// we were disconnected (by us)    		
    		case KErrCancel:
    		{    			
    			iState = ENone;    			
    			// ignore this signal for now as Disconnect() is using WaitForRequest
    			// QT_TRYCATCH_LEAVING (emit p_ptr->disconnectedFromServer() );
    			
    			return;
    		}
    		
    			
    		// we were disconnected by peer	
    		case KErrDisconnected:
    		{
    			iState = ENone;
    			QT_TRYCATCH_LEAVING (emit p_ptr->connectionResetByPeer() );
    			return;
    		}
    			
    			
    		// not ready to initiate new operation (something is still underway)
    		case KErrNotReady:
    		{	
    			// no change in current state (?)    			
    			QT_TRYCATCH_LEAVING (emit p_ptr->error (QBtSerialPortClient::ErrorAlreadyInUse) );
    			return;
    		}
    		
    	}
    	
    	
    	
        BT_DEBUG_MSG (QString ("[RunL error: %1]").arg (iStatus.Int()));
    	    	
    	// get the error
    	switch (iState)
    	{
    		case EConnecting:
    		{
    			QT_TRYCATCH_LEAVING (emit p_ptr->error (QBtSerialPortClient::ErrorOpeningConnection) );
    			break;
    		}	
    		
    		case EWaiting:
    		case ESending:
    		{
    			QT_TRYCATCH_LEAVING (emit p_ptr->error (QBtSerialPortClient::ErrorConnectionError));
    			break;
    		}
    		
    		default:
    			QT_TRYCATCH_LEAVING (emit p_ptr->error (QBtSerialPortClient::ErrorUndefinedError));
    			break;
    			
    			
    	}   	
    	
    	iState = ENone; 
        return;
    }

    
    
    // no error
    switch (iState)
    {
    	// notification should be the last thing because the user might change the state of the
    	// object, for example, by calling SendData() in a slot for the 'connectedToServer' signal
    	
        case EConnecting:
        {	
        	// this one would run only if SetActive() is called in connect()        	
        	iState = EIdle;
        	
        	// wait incoming data on socket
            ReceiveData();
        	
        	// notify
        	QT_TRYCATCH_LEAVING (emit p_ptr->connectedToServer() );     	
            break;
        }
        
        case EWaiting:
        {                	
        	// we got incoming data!            
            QString receivedString = QString::fromUtf8((char*)iBuffer.Ptr(), iBuffer.Size());
            
            // start expecting new incoming data
            ReceiveData();
            
            // notify
            QT_TRYCATCH_LEAVING (emit p_ptr->dataReceived (receivedString) );            
            break;
        }
        case ESending:
        {                	
            // start expecting new incoming data
            ReceiveData();
            
            // notify
            QT_TRYCATCH_LEAVING  (emit p_ptr->dataSent() );
            break;
        }        
                
        default:         
        	break;
    }
}
