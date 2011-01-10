#ifndef _APPLICATION_LAYER_H_
#define _APPLICATION_LAYER_H_

#include "../Network.h"
#include "ProtocolLayer.h"

class ApplicationLayer : public ProtocolLayer 
{  // TODO: noch einen Synclayer drüberlegen der solange blockt bis die nachricht wirklich angekommen ist!
  bool _received;
  Packet *_lastPacket;

public:
  ApplicationLayer() :
      ProtocolLayer()
      {
        _received = false;
      };

   ApplicationLayer(ProtocolLayer &layer) :
      ProtocolLayer(layer)
      {
        ApplicationLayer();
      };

      virtual void ReceiveCallback(Packet *packet)  
      {
        _received = true;
        _lastPacket = packet;

        ProtocolLayer::ReceiveCallback(packet);
      };

      virtual uint8_t Transmit(Packet *packet) {
        ProtocolLayer::Transmit(packet);
      };

      bool ReceivePacket(Packet *pck) {
        if(_received) {
          memcpy(pck, _lastPacket, _lastPacket->Length);
          _received = false;
          return true;
        }
        return false;
      };

      virtual void Tick() {
        ProtocolLayer::Tick();
      };
};

#endif