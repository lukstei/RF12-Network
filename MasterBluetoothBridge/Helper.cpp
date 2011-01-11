#include "Helper.h"

Helper::Helper(QObject *parent) :
    QObject(parent)
{
}

QString Helper::getMacAddressString(const MacAddress &address)
{
  QString str;
  
  for(int i = 0; i < MAC_ADDRESS_LEN; ++i) {
    str += QString("%1").sprintf("%02X", address.Address[i] & 0xFF);
    if(i != MAC_ADDRESS_LEN-1)
      str += ":";
  }
  
  return str;
}
