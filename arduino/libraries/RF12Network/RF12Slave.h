#ifndef __RF12SLAVE_H__
#define __RF12SLAVE_H__

#include <RF12Network.h>

class RF12Slave : public RF12Base {
protected:
  node_id parentId;
  
  //node_id nextReceiver; // wenn der Host was an den Client schicken will, muss er in der Nachricht die Receiver alle eintragen,
                        // denn die Slaves sind dumm und kennen ihre Umgebung nicht

  void repeat(node_id id) {
    LOGN("Repeating to parent id:", id);
  };
  
  void discover() {
    LOG("Discover: Find friends...");
    send(ID_BC, MSG_NODE_DISCOVER); // broadcast mit discover
  };
  
  MilliTimer timer;

public:
  RF12Slave() :
    RF12Base(),
    parentId(0)
  {
    //discover();
  };
  
  void doWork()
  {
    RF12Base::doWork();
    
    //if(myId = 0xFF && timer.poll(5000))
    //  discover();
  }
  
  void handleMessage() {
    // nicht an uns, weiterschicken zum parent
    if(receivedMessage->head.messageReceiver != myId && receivedMessage->head.messageReceiver) {
      repeat(getNextReceiver());
    }
    else {    
    
      switch(receivedMessage->head.messageType) 
      {
        case MSG_NODE_FOUND:
          if(hierachyDepth > receivedMessage->data.MessageNodeFound.hierachyDepth + 1) 
          // wenn ich mit einem node verbunden bin, der tiefer in der hierachie sitzt
          {
            LOGN2("Found new parent. [parent id, his hierachy depth]", receivedMessage->data.MessageNodeFound.nodeId, receivedMessage->data.MessageNodeFound.hierachyDepth);
            parentId = receivedMessage->data.MessageNodeFound.nodeId;
            hierachyDepth = receivedMessage->data.MessageNodeFound.hierachyDepth + 1;
          }
          
        break;
      }
    }
  };
  
  node_id getNextReceiver()
  {
    if(receivedMessage->head.messageType == MSG_FWD) {
     // erstes uint8 auslesen aus nachricht
    }
    
    return parentId; // im standardfall immer an den Parent schicken
  };

};

#endif