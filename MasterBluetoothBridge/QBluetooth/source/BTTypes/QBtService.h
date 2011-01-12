/*
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

#ifndef QBTSERVICE_H
#define QBTSERVICE_H

#include <QString>
#include <QList>
#include <QBtGlobal.h>
#include <QBtConstants.h>
#include <QBtUuid.h>

/**
 * Class containing all the necessary information about a bluetooth service
 * of a remote device.
 */
class DLL_EXPORT QBtService
{
   public:
      typedef QList<QBtService> List;

      /**
       * This list will be populates either by the Service Discovery or
       * by the user.
       *
       * The index of every protocol contained corresponds to the level of
       * hierarchy that it belongs.
       *
       * example: to create a service using RFCOMM then the list will be:
       * [0]: L2CAP
       * [1]: RFCOMM
       *
       * So ProtocolList::last() returns the highest protocol.
       */
      typedef QList<QBtUuid> ProtocolList;


      /**
       * Constructs an empty instance.
       */
      QBtService();
    


      /**
       * Gets the protocol list used by this service.
       */
      ProtocolList getProtocols() const;


      /**
       * Gets the service id of this service.
       */
      QBtUuid getClass () const;


      /**
       * Gets the service name.
       */
      QString getName() const;


      /**
       * Gets the service description.
       */
      QString getDescription() const;

      /**
       * Gets the service port.
       */
      uint getPort() const;

      /**
       * Gets the native (?) service handle.
       */
      uint getHandle() const;

      /**
       * Adds a protocol to the service protocol list.
       */

      void addProtocol(const QBtUuid & uuid);

      bool removeProtocol (const QBtUuid & uuid);

      void setProtocols(const ProtocolList & newUUIDs);

      void setClass(const QBtUuid & newClass);

      void setName(const QString& newName);

      void setDescription(const QString& newDescription);

      void setPort(uint newPort);

      void setHandle (uint newHandle);



   private:

      // protocol list is mainly used on symbian
      // on windows tha connections are done using classUUID
      QBtUuid       _serviceUuid;
      ProtocolList  _protocolList;
      QString       _name;
      QString       _description;
      uint          _handle;

      // used on RFCOMM service as channel number to be used for connection
      // to remote device
      uint          _port;

};

#endif // QBTSERVICE_H
