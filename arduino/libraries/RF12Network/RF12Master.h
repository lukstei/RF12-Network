#ifndef __RF12MASTER_H__
#define __RF12MASTER_H__

#include <RF12Network.h>

class RF12Master : public RF12Base {

public: 
  
  RF12Master() :
    RF12Base() // verbent kontruktor aufrufen
  {
    myId = 1;
    hierachyDepth = 0;
  };
  
  node_id getNextReceiver()
  {
  }
 
  
  void handleMessage() 
  {
    // nicht an uns, weiterschicken zum parent
    if(receivedMessage->head.messageReceiver != myId && receivedMessage->head.messageReceiver != ID_BC) {
      LOGN("Nachricht zum weiterleiten erhalten, empfaenger =", receivedMessage->head.messageReceiver);
    }
    else {
      
    }
  };
};

#endif