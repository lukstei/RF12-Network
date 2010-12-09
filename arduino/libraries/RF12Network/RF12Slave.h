#ifndef __RF12SLAVE_H__
#define __RF12SLAVE_H__

#include <RF12Network.h>
#include "ParentManager.h"

class RF12Slave : public RF12Base {
protected:
  ParentManager _parent;

public:
  RF12Slave();
  
  void doWork();
  void handleMessage();
};

RF12Slave::RF12Slave() :
  RF12Base(),
  _parent(this)
{
}

void RF12Slave::doWork()
{
  RF12Base::doWork();
  _parent.doWork();
}

void RF12Slave::handleMessage() 
{
  uint8_t msgType = receivedMessage->head.messageType;
  _parent.messageReceived(msgType);
}

#endif