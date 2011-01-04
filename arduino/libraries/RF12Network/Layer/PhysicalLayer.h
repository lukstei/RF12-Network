#ifndef _PHYSICAL_LAYER_H_
#define _PHYSICAL_LAYER_H_

#include "../Network.h"
#include "ProtocolLayer.h"

class PhysicalLayer;
static PhysicalLayer *instance;
void isr_receive_callback();

class PhysicalLayer : public ProtocolLayer {
protected: 
  Packet _buf;
  
public:
  PhysicalLayer() :
    ProtocolLayer()
  {
    instance = this;
    rf12_set_receive_callback(&isr_receive_callback);
    
    rf12_initialize();
  };
  
  PhysicalLayer(ProtocolLayer &layer) :
    ProtocolLayer(layer)
  {
    PhysicalLayer();
  };
  
  void ReceiveCallback()
  {
    LOG(1, "Physical: ISR called");
    memcpy(&_buf, (const void *)rf12_data, rf12_len_safe);
    ReceiveCallback(&_buf);
  };

  virtual void ReceiveCallback(Packet *packet)  {
    LOG(1, "Physical: receive");

    return ProtocolLayer::ReceiveCallback(packet);
  };
  
  virtual uint8_t Transmit(Packet *packet) {
    LOG(1, "Physical: transmit");
    
    rf12_sendStart(packet, packet->Length);
    return ProtocolLayer::Transmit(packet);
  };
  
  virtual void Tick() {
    rf12_recvDone();
    ProtocolLayer::Tick();
  };
};

inline void isr_receive_callback()
{
  instance->ReceiveCallback();
}

#endif