#ifndef __RF12BASE_H__
#define __RF12BASE_H__

#include <RF12Network.h>

class RF12Base
{
protected:
  node_id myId;
  
  virtual void handleMessage() {}; // klammern um compiler error zu vermeiden
  
  void handleReceivedData();
  void sendAck();
  void _send();
  
public:
  ReceiveBuffer<3> receiveBuffer;
  SendBuffer<3> sendBuffer;

  RF12Base();

  void initialize() {
    rf12_initialize();
  };

  const RF12Message *getReceivedMessage();
  
  void send();
  void send(node_id receiver, const String& str);
  void send(node_id receiver, uint8_t msg_type, int len = 0);

  virtual void doWork();
};

RF12Base::RF12Base() :
  myId(0xFF)
{
    randomSeed(analogRead(0)); // seed really random
    initialize(myId);
};

void RF12Base::_send(RF12Message *sendMessage)  {
  do {
      delay(50 * random(1, 20));
  } while(!rf12_canSend());

  LOGN("Sending to nodeid =", sendMessage->head.receiver);
  LOGM("Sending message", sendMessage->head.messageType);

  rf12_sendStart(sendMessage, sendMessage->head.messageLength);
};

void RF12Base::sendAck(node_id recv)  {
  LOGN("Sending ack back to node id =", recv);

  RF12Message *sendMessage = (RF12Message *) rf12_data;

  // send an ack back
  sendMessage->head.sender = myId;
  sendMessage->head.receiver = recv;

  sendMessage.head.flags = FLAG_ACK;
  sendMessage.head.messageLength = sizeof(sendMessage->head);

  rf12_sendStart();
};

void RF12Base::send(node_id receiver, const String& str) {
  str.toCharArray((char*)(&sendMessage.data.raw), sizeof(sendMessage.data.raw));
  send(receiver, MSG_DATA_LOG, str.length());
}

void RF12Base::send(node_id receiver, uint8_t msg_type, int len) {
  sendMessage.head.receiver = receiver;
  sendMessage.head.messageType = msg_type;
  sendMessage.head.messageLength = sizeof(sendMessage.head) + len;

  send();
};

void RF12Base::doWork() {
  if (rf12_recvDone()) {
    if (rf12_crc == 0 && 
      (receivedMessage.head.receiver == myId ||
       receivedMessage.head.receiver == ID_BC ))
    { // nachricht an mich
        LOG("Received");
        receiveBuffer.enqueueMessage();

        handleReceivedData();

      } else if(rf12_crc != 0) {
        LOG("Received something with bad crc");
      }
  }

  if (needToSend)
  {
    
    
    _send();
  }
}

void RF12Base::handleReceivedData() {
  // sende ack zurueck
  if (receivedMessage.head.flags & FLAG_NEED_ACK) {
    sendAck();
  }

  // acknowledge empfangen
  if(receivedMessage.head.flags & FLAG_ACK) {
    LOGN("Received ack from", receivedMessage->head.sender);
    // TODO: handle ack
  }
  else if(receivedMessage.head.flags & FLAG_NAK) {
    LOGN("Received nak from", receivedMessage->head.sender);
    // TODO: handle nak
  }
  // ganz normale nachricht empfangen
  else
  {
    LOGM("Received message", receivedMessage->head.messageType);
    
    switch(receivedMessage->head.messageType) {
        
      default:
        handleMessage();
          
        LOGN("Received data, length =", rf12_len);
        break;
    }
  }
};

#endif
