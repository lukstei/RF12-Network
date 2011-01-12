/*
 * QBtServiceDiscoverer.h
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

#ifndef QBTSERVICEPROBER_H_
#define QBTSERVICEPROBER_H_

#include <QBtGlobal.h>
#include <QObject>
#include <QBtTypes.h>
#include <QBtDeviceDiscoverer.h>
#include <QBtServiceDiscoverer.h>


/**
 * This class provides the mechanism to inquire services available on all devices
 * in the vicinity.
 *
 * when startDiscovery() is called (or its variations), it searches for all devices
 * according to the query criteria (the service uuids).
 *
 * When the discovery starts, the discoveryStarted() signal is emitted. Likewise,
 * the signal discoveryEnded() is emitted when the discovery ends. This happens when
 * the inquiry ends normally or through interruption (by calling stopDiscovery() ).
 *
 * After each device is filled with all services, the signal newDeviceFound (const QBtDevice &)
 * is emitted.
 *
 * After the discovery ends, the found device list is accessible through getDeviceList(). If no
 * devices were found, this list is empty.
 */
class DLL_EXPORT QBtServiceDiscovererForAll : public QObject
{
    Q_OBJECT

public:
    QBtServiceDiscovererForAll(QObject* parent = 0);
    virtual ~QBtServiceDiscovererForAll();

    /**
     * Returns the list of found devices. The list is empty if no
     * devices were found.
     */
    const QBtDevice::List & getDeviceList() const;

    /**
     * Returns true if a discovery operation is in progress.
     */
    bool isBusy () const;


    /**
     * Returns the number of total devices found.
     */
    int getNumberOfFoundDevices () const;


   /**
    * Returns true if any device was found.
    */
    bool foundDevices() const;


public slots:


   /**
    * Starts service discovery for OBEX and RFCOMM services.
    * New devices with their services are reported through signal "newDeviceFound".
    */
   void startDiscovery ();


   /**
    * Starts service discovery for OBEX services only.
    * New devices with their services are reported through signal "newDeviceFound".
    *
    */
   void startObexDiscovery ();

   /**
    * Starts service discovery for RFCOMM services only.
    * New devices with their services are reported through signal "newDeviceFound".
    */
   void startRfcommDiscovery ();



   /**
    * Starts service discovery for the service (or protocol) identified by
    * the uuid parameter.
    * New devices with their services are reported through signal "newDeviceFound".
    */
   void startDiscovery (const QBtUuid & uuid);


   /**
    *
    * Starts service discovery for UUIDs provided in the list.
    * New devices with their services are reported through signal "newDeviceFound".
    */
   void startDiscovery (const QList <QBtUuid> & uuids);


   /**
    * Stops service discovery.
    * Services found so far can be acquired using "getInquiredServices" function.
    */
   void stopDiscovery();


signals:

   /**
    * Signal to report that discovery has started.
    */
   void discoveryStarted();

   /**
    * Signal to report that discovery has ended (either cancelled or no new devices to detect)
    */
   void discoveryEnded ();


   /**
   * Signal to report that the class finished searching for services
   * in the specified device.
   */
   void newDeviceFound (const QBtDevice & device);


   /**
    * Signal emitted when service discovery error occurs when searching for services in the
    * specified device.
    */
   void serviceDiscoveyError (const QBtDevice & device, QBtServiceDiscoverer::ServiceDiscoveryError error);

   /**
    * Signal emitted when device discovery error occurs.
    */
   void deviceDiscoveryError (QBtDeviceDiscoverer::DeviceDiscoveryErrors error);

private slots:

   void sd_newServiceFound (const QBtDevice &targetDevice, const QBtService & service);
   void sd_serviceDiscoveryStarted ();
   void sd_serviceDiscoveryEnded ();
   void sd_error (QBtServiceDiscoverer::ServiceDiscoveryError error);


   //
   void dd_discoveryEnded ();
   void dd_discoveryStarted ();
   void dd_newDeviceFound (const QBtDevice & remoteDevice);
   void dd_error (QBtDeviceDiscoverer::DeviceDiscoveryErrors error );

private:

   void _startDiscovery ();

private:

    QBtDeviceDiscoverer    _deviceDiscoverer;
    QBtServiceDiscoverer   _serviceDiscoverer;
    QList<QBtUuid>         _targetServices;

    QList <QBtDevice>      _deviceList;

    int                    _deviceIndex;
    bool                   _aborted;
    

};

#endif /* QBTSERVICEDISCOVERER_H_ */
