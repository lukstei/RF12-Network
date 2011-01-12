/*
 * QBtServiceDiscoverer.cpp
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

#include "../QBtServiceDiscoverer.h"
#include <QBtAuxFunctions.h>

#if defined(Q_OS_SYMBIAN)
#include "../QBtServiceDiscoverer_symbian.h"
#elif defined(Q_OS_WIN32)
#include "../QBtServiceDiscoverer_win32.h"
#elif !defined(Q_OS_WIN32) && !defined(Q_OS_SYMBIAN)
#include "../QBtServiceDiscoverer_stub.h"
#endif


//____________________________________________________________________________

QBtServiceDiscoverer::QBtServiceDiscoverer(QObject *parent) :
    QObject(parent)
{
#ifdef Q_OS_SYMBIAN
    QT_TRAP_THROWING(_implPtr = QBtServiceDiscovererPrivate::NewL(this));
#else
    _implPtr = new QBtServiceDiscovererPrivate(this);
#endif
}


//____________________________________________________________________________

QBtServiceDiscoverer::~QBtServiceDiscoverer()
{
    SafeDelete(_implPtr);
}

//____________________________________________________________________________

void QBtServiceDiscoverer::startDiscovery (const QBtDevice& targetDevice)
{
    _remoteDevice = targetDevice;
    _implPtr->DiscoverServices (& _remoteDevice);
}


//____________________________________________________________________________

void QBtServiceDiscoverer::startObexDiscovery (const QBtDevice& targetDevice)
{
    _remoteDevice = targetDevice;
    _implPtr->DiscoverObexServices (& _remoteDevice);
}

//____________________________________________________________________________

void QBtServiceDiscoverer::startRfcommDiscovery (const QBtDevice& targetDevice)
{
    _remoteDevice = targetDevice;
    _implPtr->DiscoverRfcommServices (& _remoteDevice);
}


//____________________________________________________________________________

void QBtServiceDiscoverer::startDiscovery (const QBtDevice& targetDevice, const QBtUuid & uuid)
{
    _remoteDevice = targetDevice;
    _implPtr->DiscoverSpecificClass (& _remoteDevice, uuid);
}


//____________________________________________________________________________

void QBtServiceDiscoverer::startDiscovery (const QBtDevice& targetDevice, const QList<QBtUuid> & uuids)
{
    _remoteDevice = targetDevice;
    _implPtr->DiscoverSpecificClasses (& _remoteDevice, uuids);
}



//____________________________________________________________________________

void QBtServiceDiscoverer::stopDiscovery()
{
    _implPtr->StopDiscovery();
}


//____________________________________________________________________________

const QBtDevice & QBtServiceDiscoverer::getTargetDevice() const
{
    return _remoteDevice;
}

//____________________________________________________________________________


QBtService::List QBtServiceDiscoverer::getInquiredServices()
{
    return _remoteDevice.getSupportedServices();
}


//____________________________________________________________________________

bool QBtServiceDiscoverer::isBusy () const
{
	return _implPtr->IsBusy();
}


