#include "NetworkManager.h"

NetworkManager::NetworkManager(QObject *parent) :
    QObject(parent)
{
}

void NetworkManager::connect() {
  // ...
  
  _connected = true;
  emit connected(true);
}

void NetworkManager::disconnect() {
  // ...
  
  _connected = false;
  emit connected(false);
}
