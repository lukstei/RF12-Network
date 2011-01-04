#ifndef _SYNCHRONIZATION_LAYER_H_
#define _SYNCHRONIZATION_LAYER_H_

#include "../Network.h"
#include "ProtocolLayer.h"
#include <Ports.h>

class SynchronizationLayer : public ProtocolLayer 
{
  volatile uint8_t _sync;
  MilliTimer _timer;
  Packet *_lastPacket;
  
public:
  SynchronizationLayer() :
    ProtocolLayer()
  {
    _sync = false;
  };
  
  SynchronizationLayer(ProtocolLayer &layer) :
    ProtocolLayer(layer)
  {
    SynchronizationLayer();
  };
  
  virtual void ReceiveCallback(Packet *packet)  
  {
    _sync = true;
    _lastPacket = packet;
    
    ProtocolLayer::ReceiveCallback(packet);
  };
  
  virtual uint8_t Transmit(Packet *packet) {
    LOG(5, "send called");
    
    while(!ProtocolLayer::Transmit(packet))
      Tick();
    
    while(GetState()->SendState != State::Idle && GetState()->SendState != State::Failure) 
      Tick();
    
    LOGN(5, "success =", GetState()->SendState == State::Idle);
    
    return GetState()->SendState == State::Idle;
  };
  
//   Packet *receive(int timeout = 10000) {
//     LOG(5, "receiveing pckt");
//     
//     _sync = false;
//     _timer.set(timeout); // timeout
//     
//     while(!_sync && !_timer.poll()) 
//       Tick();
//       
//     LOGN(5, "receive =", _sync);
//     return _sync ? _lastPacket : NULL;
//   };

  bool ReceivePacket(Packet *pck) {
    if(_sync) {
      memcpy(pck, _lastPacket, sizeof(*pck));
      return true;
    }
    return false;
  };
  
  virtual void Tick() {
    ProtocolLayer::Tick();
  };
};

#endif