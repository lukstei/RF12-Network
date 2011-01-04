#ifndef _ROUTING_LAYER_H_
#define _ROUTING_LAYER_H_

#include "../Network.h"
#include "../Packet.h"
#include "ProtocolLayer.h"
#include "../RoutingTable.h"

class RoutingLayer : public ProtocolLayer {
protected:
  RoutingTable<MAX_NODES> _table;

public:
  RoutingLayer() :
    ProtocolLayer()
  {

  };

  RoutingLayer(ProtocolLayer &layer) :
    ProtocolLayer(layer)
  {
    RoutingLayer();

#if IS_MASTER
    GetState()->Id = ID_MASTER;
    GetState()->Parent = ID_MASTER;
    GetState()->HierachyDepth = 0;
#endif
  };

  node_id GetNextStation(Packet *packet) 
  {
    //if(packet & )
    //{
    //  DynamicId *data = message_type_read<DynamicId>(packet);
    //  if(data->Parent == GetState()->Id)
    //    return ID_BC;
    //  else if(low_address_my_id(&data->Address))
    //    return data->Parent;
    //}

    node_id child = _table.FindNextHop(packet->PacketReceiver);
    return child != 0 ? child : GetState()->Parent; // either the receiver is lower in the hierachy otherwise send packaet to parent
  };

  virtual void ReceiveCallback(Packet *packet)  
  {
    /*if(packet->Flags & FLAG_FAIL) {
      LOG(4, "received message with fail flag");

      if(_table.Find(packet->HopSender)) 
        _table.RemoveNode(packet->HopSender);
      else
        GetState()->Parent = 0xFF;

      return NULL;
    }*/
    
    if(packet->PacketReceiver != GetState()->Id) 
    {
      if(GetState()->InitializationDone()) 
      {
        LOGN(4, "Routing: forwarding message to node", packet->HopReceiver);
        Transmit(packet);
      }
      else 
      {
        LOGN(4, "Received package from but i have no id! from: ", packet->PacketSender);
       /*  packet->PacketReceiver = packet->PacketSender;
        packet->OfType<EmptyMessage>(MSG_CANNOT_ROUTE); // TODO: gscheit no überlegen
        Transmit(packet);*/
        // TODO: implement error handling
      }
    }
    else return ProtocolLayer::ReceiveCallback(packet);
  };

  virtual uint8_t Transmit(Packet *packet) {
    LOG(4, "Routing: transmit");

    if(!(packet->Flags & FLAG_MAC_MSG))
    {
      if(!GetState()->InitializationDone()) return false;

      packet->HopReceiver = GetNextStation(packet);
      if(IS_MASTER && packet->HopReceiver == ID_MASTER) {
        LOGN(4, "Cannot route package with type: ", packet->Type);
        return false;
      }

      packet->HopSender = GetState()->Id;
    }

    if(!ProtocolLayer::Transmit(packet)) {
      HopNotAvailable(packet->HopReceiver);
      return false;
    }
  };

  void HopNotAvailable(node_id node)
  {
    LOGN(4, "Hop no available: ", node);
    if(node == GetState()->Parent) 
      GetState()->Parent = 0xFF;
    else
    {
      _table.RemoveNode(node);
      // TODO: inform parents
    }
  }

  virtual void Tick() {
    ProtocolLayer::Tick();
  };
};

#endif