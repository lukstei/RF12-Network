/*
 * QBtServiceDiscovererForAll.cpp
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

#include "../QBtServiceDiscovererForAll.h"
#include <QBtAuxFunctions.h>



//____________________________________________________________________________

QBtServiceDiscovererForAll::QBtServiceDiscovererForAll (QObject *parent) :
    QObject(parent)
{
    // service discovery
    connect (&_serviceDiscoverer, SIGNAL (newServiceFound (const QBtDevice &, const QBtService&)), SLOT (sd_newServiceFound (const QBtDevice &, const QBtService&)));
    connect (&_serviceDiscoverer, SIGNAL (discoveryStopped()), SLOT (sd_serviceDiscoveryEnded()) );
    connect (&_serviceDiscoverer, SIGNAL (discoveryStarted()), SLOT (sd_serviceDiscoveryStarted()) );
    connect (&_serviceDiscoverer, SIGNAL (error (QBtServiceDiscoverer::ServiceDiscoveryError)), SLOT(sd_error (QBtServiceDiscoverer::ServiceDiscoveryError)) );


    // device discovery
    connect (&_deviceDiscoverer, SIGNAL(discoveryStopped ()), SLOT (dd_discoveryEnded ()) );
    connect (&_deviceDiscoverer, SIGNAL(discoveryStarted ()), SLOT (dd_discoveryStarted ()) );
    connect (&_deviceDiscoverer, SIGNAL(newDeviceFound (const QBtDevice &)), SLOT (dd_newDeviceFound (const QBtDevice &)) );
    connect (&_deviceDiscoverer, SIGNAL(error(QBtDeviceDiscoverer::DeviceDiscoveryErrors)), SLOT (dd_error(QBtDeviceDiscoverer::DeviceDiscoveryErrors)) );
}


//____________________________________________________________________________

QBtServiceDiscovererForAll::~QBtServiceDiscovererForAll()
{ 
}




//____________________________________________________________________________

void QBtServiceDiscovererForAll::startDiscovery ()
{
   _targetServices.clear();
   _targetServices.append(QBtUuid (QBtConstants::RFCOMM));
   _targetServices.append(QBtUuid (QBtConstants::OBEX));


   _startDiscovery ();

}


//____________________________________________________________________________

void QBtServiceDiscovererForAll::startObexDiscovery ()
{
   _targetServices.clear();
   _targetServices.append(QBtUuid (QBtConstants::OBEX));

   _startDiscovery();
}

//____________________________________________________________________________

void QBtServiceDiscovererForAll::startRfcommDiscovery ()
{
   _targetServices.clear();
   _targetServices.append(QBtUuid (QBtConstants::RFCOMM));

   _startDiscovery();
}


//____________________________________________________________________________

void QBtServiceDiscovererForAll::startDiscovery (const QBtUuid & uuid)
{
   _targetServices.clear();
   _targetServices.append (uuid);

   _startDiscovery();
}


//____________________________________________________________________________

void QBtServiceDiscovererForAll::startDiscovery (const QList<QBtUuid> & uuids)
{
   _targetServices = uuids;
   _startDiscovery();
}


//____________________________________________________________________________

void QBtServiceDiscovererForAll::_startDiscovery ()
{
   if (isBusy() )
      return;

   //
   _aborted = false;

   //
   _deviceList.clear();

   // start first by discovering devices
   _deviceDiscoverer.startDiscovery();
}


//____________________________________________________________________________

void QBtServiceDiscovererForAll::stopDiscovery()
{
   if (_serviceDiscoverer.isBusy())
    { _serviceDiscoverer.stopDiscovery(); _aborted = true; }

   if (_deviceDiscoverer.isBusy())
    { _deviceDiscoverer.stopDiscovery(); _aborted = true; }

}


//____________________________________________________________________________

void QBtServiceDiscovererForAll::dd_discoveryEnded()
{
   // aborted ?
   if (_aborted)
   {
      emit discoveryEnded();
      return;
   }


   // starting fetching services
   const QBtDevice::List& list = _deviceDiscoverer.getInquiredDevices();
   _deviceIndex = 0;


    if (list.length() > 0)
    {
    BT_DEBUG_MSG("starting service search");

        _serviceDiscoverer.startDiscovery (list [0], _targetServices);
    }
    else
    {
      // no devices found
      emit discoveryEnded();
    }

}


//____________________________________________________________________________

void QBtServiceDiscovererForAll::dd_discoveryStarted()
{
    emit discoveryStarted();
}


//____________________________________________________________________________

void QBtServiceDiscovererForAll::sd_newServiceFound (const QBtDevice &targetDevice, const QBtService & newService)
{
}

//____________________________________________________________________________

void QBtServiceDiscovererForAll::sd_serviceDiscoveryStarted ()
{
}


//____________________________________________________________________________

void QBtServiceDiscovererForAll::sd_serviceDiscoveryEnded ()
{
   // was it aborted?
   if (_aborted)
   {
      emit discoveryEnded();
      return;
   }



   // get processed device
   const QBtDevice & device = _serviceDiscoverer.getTargetDevice();


   // let's see what happened, if there are no services, some error might have ocurred
   const QBtService::List & serviceList = device.getSupportedServices();


   // notify and keep if the device has services. If it doesn't have services, it
   // might have turned off bluetooth (or walked away) after it had been discovered
   if (serviceList.isEmpty() == false)
   {
      // notify about this device
      emit newDeviceFound (device);

      // keep this device
      _deviceList.append (device);
   }



   // fetch services for next device
   const QBtDevice::List& list = _deviceDiscoverer.getInquiredDevices();
   _deviceIndex++;

    if (_deviceIndex < list.length() )
    {
        _serviceDiscoverer.startDiscovery (list [_deviceIndex], _targetServices);
    }
    else
    {
        // service discovery ended
        emit discoveryEnded();
    }


}


//____________________________________________________________________________

void QBtServiceDiscovererForAll::sd_error (QBtServiceDiscoverer::ServiceDiscoveryError error)
{
    BT_DEBUG_MSG (QString("<service discovery error: %1>").arg(error) );
    emit serviceDiscoveyError (_serviceDiscoverer.getTargetDevice(), error);



}

//____________________________________________________________________________

void QBtServiceDiscovererForAll::dd_error(QBtDeviceDiscoverer::DeviceDiscoveryErrors error)
{
   BT_DEBUG_MSG (QString("<device discovery error: %1>").arg(error) );
   emit deviceDiscoveryError (error);
}



//____________________________________________________________________________

void QBtServiceDiscovererForAll::dd_newDeviceFound (const QBtDevice & remoteDevice)
{}




//____________________________________________________________________________

int QBtServiceDiscovererForAll::getNumberOfFoundDevices() const
{
    return _deviceList.length();
}


//____________________________________________________________________________

bool QBtServiceDiscovererForAll::foundDevices () const
{
   return _deviceList.length() != 0;
}

//____________________________________________________________________________


const QBtDevice::List & QBtServiceDiscovererForAll::getDeviceList() const
{
    return _deviceList;
}


//____________________________________________________________________________

bool QBtServiceDiscovererForAll::isBusy () const
{
    return (_deviceDiscoverer.isBusy() || _serviceDiscoverer.isBusy() );
}


