#ifndef __PARENTMANAGER_H__
#define __PARENTMANAGER_H__

#include <RF12Network.h>
#include "ManagerBase.h"

class ParentManager : public ManagerBase {
public:
  MilliTimer timer;

  uint8_t parentId;
  uint8_t hierachyDepth;

  ParentManager(RF12Base *rf12) :
    parentId(0),
    hierachyDepth(0xFF),
    ManagerBase(rf12)
  {
  };

  virtual bool messageReceived(uint8_t msgType);
  virtual void doWork();
};

void ParentManager::doWork() 
{
  if(parentId == 0 && timer.poll(5000)) {
    _rf12->send(ID_BC, NODE_DISCOVER);
  }
}

bool ParentManager::messageReceived(uint8_t msgType)
{
  switch(msgType) {
    case NODE_DISCOVER: {
      if(hierachyDepth < 0xFF) {
        const RF12Message *msg = _rf12->getReceivedMessage();

        _rf12->sendMessage.data.MessageNodeFound.hierachyDepth = hierachyDepth;
          
        LOGN2("Someone searches friends. [nodeid, my hierachy depth]", msg->head.sender, hierachyDepth);
            
        _rf12->send(msg->head.sender, NODE_FOUND, sizeof(_rf12->sendMessage.data.MessageNodeFound));
      }
    }
    break;

    case NODE_FOUND: {
      
      const RF12Message *msg = _rf12->getReceivedMessage();

      if(hierachyDepth > msg->data.MessageNodeFound.hierachyDepth + 1) 
      // wenn ich mit einem node verbunden bin, der hoeher in der hierachie sitzt
      {
        LOGN2("Found new parent. [parent id, his hierachy depth]", msg->head.sender, msg->data.MessageNodeFound.hierachyDepth);
        parentId = msg->head.sender;
        hierachyDepth = msg->data.MessageNodeFound.hierachyDepth + 1;
      }
    }
    break;
    
    default:
      return false;
  }

  return true;
}

#endif