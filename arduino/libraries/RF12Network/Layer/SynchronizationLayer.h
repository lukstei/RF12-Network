#ifndef _SYNCHRONIZATION_LAYER_H_
#define _SYNCHRONIZATION_LAYER_H_

#include "../Network.h"
#include "ProtocolLayer.h"
#include <Ports.h>

class SynchronizationLayer : public ProtocolLayer 
{
  volatile uint8_t _sync;
  
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
    ProtocolLayer::ReceiveCallback(packet);
  };
  
  virtual uint8_t Transmit(Packet *packet) {
    LOG(4, "send called");

    while(!ProtocolLayer::Transmit(packet))
      Tick();
    
    while(GetState()->SendState != State::Idle && GetState()->SendState != State::Failure) 
      Tick();
    
    LOGN(4, "success =", GetState()->SendState == State::Idle);
    
    return GetState()->SendState == State::Idle;
  };
  
  virtual void Tick() {
    ProtocolLayer::Tick();
  };
};

#endif