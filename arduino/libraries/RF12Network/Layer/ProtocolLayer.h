#ifndef _PROTOCOL_LAYER_H_
#define _PROTOCOL_LAYER_H_

#include "../Network.h"
#include "../Packet.h"

// Layers:
//
// Base class: ProtocolLayer
// 1: PhysicalLayer (RF12)
// 2: MacLayer
// 3: SynchronizationLayer
// 4: RoutingLayer
// 5: ApplicationLayer

class ProtocolLayer
{
protected:
  inline Packet *GetSendBuffer() { static Packet sendBuf; return &sendBuf; };

public:
  ProtocolLayer *upperLayer;
  ProtocolLayer *lowerLayer;

  ProtocolLayer() {
    lowerLayer = upperLayer = NULL;
  };

  ProtocolLayer(ProtocolLayer &layer) {
    ProtocolLayer();

    lowerLayer = &layer;
    layer.upperLayer = this;
  };

  virtual void ReceiveCallback(Packet *packet)  {
    if(upperLayer !=  NULL)
      upperLayer->ReceiveCallback(packet);
  };

  virtual uint8_t Transmit(Packet *packet) {
    if(lowerLayer !=  NULL)
      return lowerLayer->Transmit(packet);

    return true;
  };

  virtual void Tick() {
    if(lowerLayer !=  NULL)
      lowerLayer->Tick();
  };
};

#include "PhysicalLayer.h"
#include "DataLinkLayer.h"
#include "SynchronizationLayer.h"
#include "RoutingLayer.h"
#include "ApplicationLayer.h"

#endif