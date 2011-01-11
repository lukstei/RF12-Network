#include "NetworkManager.h"

NetworkManager::NetworkManager(QIODevice *serial, QObject *parent) :
    QObject(parent),
    serial(serial)
{
  QObject::connect(this, SIGNAL(deviceAdded(node_id,MacAddress)), this, SLOT(onDeviceAdded(node_id,MacAddress)));
  QObject::connect(this, SIGNAL(deviceRemoved(node_id)), this, SLOT(onDeviceRemoved(node_id)));
}

void NetworkManager::connect() {
  serial->write("HELO\n");
  QString resp = serial->readLine();
  if(resp == "EHLO") {
    emit connected(true);  
  }
}

void NetworkManager::disconnect() {
  serial->write("BYE\N");
  
  emit connected(false);
}

void NetworkManager::onDeviceAdded(node_id node, MacAddress address)
{
  table[node] = address;
}

void NetworkManager::onDeviceRemoved(node_id node)
{
  table.remove(node);
}
