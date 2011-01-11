#include "NetworkManager.h"

NetworkManager::NetworkManager(QObject *parent) :
    QObject(parent)
{
  QObject::connect(this, SIGNAL(deviceAdded(node_id,MacAddress)), this, SLOT(onDeviceAdded(node_id,MacAddress)));
  QObject::connect(this, SIGNAL(deviceRemoved(node_id)), this, SLOT(onDeviceRemoved(node_id)));
}

void NetworkManager::connect() {
  // ...
  
  emit connected(true);
}

void NetworkManager::disconnect() {
  // ...
  
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
