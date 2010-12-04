#ifndef __RF12BASE_H__
#define __RF12BASE_H__

#include <RF12Network.h>

class RF12Base
{
protected:

  uint8_t hierachyDepth; // host = 0, dann jedeinstanz +1
  node_id myId;
  
  RF12Message *receivedMessage;
  
  bool needToSend;
  bool isMessageReceived;
  
  virtual void handleMessage() {};
  
  void handleReceivedData() {
    // sende ack zurueck
    if (receivedMessage->head.flags & FLAG_NEED_ACK) {
      sendAck();
    } 


    // acknowledge empfangen
    if(receivedMessage->head.flags & FLAG_ACK) {
      LOGN("Received ack from", receivedMessage->head.sender);
      // TODO: handle ack
    }
    else if(receivedMessage->head.flags & FLAG_NAK) {
      LOGN("Received nak from", receivedMessage->head.sender);
      // TODO: handle nak
    }
    // ganz normale nachricht empfangen
    else
    {      
      LOGM("Received message", receivedMessage->head.messageType);
      
      isMessageReceived = true;

      switch(receivedMessage->head.messageType) {
        case MSG_NODE_DISCOVER: { // Klammern werden gebraucht um compiler fehler zu vermeiden
            sendMessage.data.MessageNodeFound.nodeId = myId;
            sendMessage.data.MessageNodeFound.hierachyDepth = hierachyDepth;
          
            LOGN2("Someone searches friends. [nodeid, my hierachy depth]", receivedMessage->head.sender, hierachyDepth);
            
            send(receivedMessage->head.sender, MSG_NODE_FOUND, sizeof(sendMessage.data.MessageNodeFound));
          }
          break;
        
        default:
          handleMessage();
          
#if DEBUG
          LOGN("Received data, length =", rf12_len);
#endif
          break;
      }
    }
  };
  
  void sendAck()
  {      
    LOGN("Sending ack back to node id =", receivedMessage->head.sender);

    // send an ack back    
    sendMessage.head.sender = myId;
    sendMessage.head.messageReceiver = receivedMessage->head.sender;
    sendMessage.head.flags = FLAG_ACK;
    sendMessage.head.messageLength = sizeof(sendMessage.head);

    rf12_sendStart(&sendMessage, sendMessage.head.messageLength);
    memset(&sendMessage, 0, sizeof(sendMessage.head));
  };
  
  void _send()
  {
    needToSend = false;

    LOGN("Sending to nodeid =", sendMessage.head.messageReceiver);
    LOGM("Sending message", sendMessage.head.messageType);

    rf12_sendStart(&sendMessage, sendMessage.head.messageLength);
  }
  
public:
  RF12Base() :
    hierachyDepth(0xFF),
    myId(0xFF),
    needToSend(false),
    isMessageReceived(false) {
      
      receivedMessage = (RF12Message *) rf12_data;

      initialize(myId);
  };
    
  RF12Message sendMessage;

  void initialize(node_id id) {
    myId = id;
    rf12_initialize(myId, RF12_433MHZ);
  };

  bool messageReceived() {
    return isMessageReceived;
  };

  const RF12Message *getReceivedMessage()
  {
    isMessageReceived = false;
    return receivedMessage;
  };
  
  void send(node_id receiver, const String& str) {
    str.toCharArray((char*)(&sendMessage.data.raw), sizeof(sendMessage.data.raw));
    send(receiver, MSG_DATA_LOG, str.length());
  };
  
  void send(node_id receiver, uint8_t msg_type, int len = 0) {
    needToSend = true;
    
    sendMessage.head.messageReceiver = receiver;
    sendMessage.head.messageSender = myId;
    sendMessage.head.sender = myId;
    
    sendMessage.head.messageType = msg_type;
    
    sendMessage.head.messageLength = sizeof(sendMessage.head) +len;
  };

  virtual void doWork() {
    if (rf12_recvDone()) {
      if (rf12_crc == 0 && 
          (receivedMessage->head.messageReceiver == myId || 
          receivedMessage->head.messageReceiver == ID_BC ))
      {

          LOG("Received");

          memset(&sendMessage, 0, sizeof(sendMessage)); // sendData leeren um senden falscher Daten zu vermeiden

          handleReceivedData();

          if(needToSend) {
            _send();
          }
        } else if(rf12_crc != 0) {
          LOG("Received something with bad crc");
        }
    }

    if (needToSend && rf12_canSend()) {
        _send();
    }
  };
};

#endif
