#ifndef _DID_MANAGER_H_
#define _DID_MANAGER_H_

#include "../Network.h"
#include "../Packet.h"
#include "Manager.h"

#include <Ports.h>

class DidManager : public Manager
{
  MilliTimer timer;

  node_id bestParent;
  uint8_t bestHierachy;

  MilliTimer parentTimer;

public:
  DidManager(ProtocolLayer &network) :
      Manager(network)
  {
    timer.set(1000);
  };

  virtual void Received(Packet *packet) 
  {
    switch(packet->Type) {
    case DID_DISCOVER:
      {
        if(GetState()->InitializationDone()) {
          LOG(5, "Someone searches for friends addr");
          
          Packet p(ID_BC);
          p.Flags |= FLAG_MAC_MSG;

          DynamicIdReply *rep = p.OfType<DynamicIdReply>(DID_REPLY);

          MacAddressManager::Copy(&rep->Address, packet->GetData<MacAddress>());

          rep->HierachyDepth = GetState()->HierachyDepth;
          rep->Id = GetState()->Id;

          _net.Transmit(&p);
        }
      }
      break;

    case DID_REPLY:
      {
        DynamicIdReply *rep = packet->GetData<DynamicIdReply>();
        if(rep->HierachyDepth + 1 < bestHierachy ) {
          bestHierachy = rep->HierachyDepth + 1;
          bestParent = rep->Id;
        }
      }
      break;

    case DID_REQ_ID:
      {
        MacAddress *rep = packet->GetData<MacAddress>();

#if IS_MASTER
        static uint8_t ids = 2;
        LOGN(5, "new member with node id = ", ids+1);
        
        Packet p(packet->PacketSender);

        LOGN(5, "paclage sender = ", packet->PacketSender);
        DynamicIdAccept *n = p.OfType<DynamicIdAccept>(DID_ACCEPT);
        n->id = ids++;
        n->parent = packet->PacketSender;
        MacAddressManager::Copy(&n->address, rep);

        _net.Transmit(&p);
#endif
      }
      break;

    case DID_ACCEPT:
      {
        if(GetState()->InitializationDone() && packet->HopSender != GetState()->Id) 
        {
          LOG(5, "got DID_ACCEPT forwarding to station");
          packet->HopSender = GetState()->Id;
          packet->Flags |= FLAG_MAC_MSG;

          packet->PacketReceiver = ID_BC;
          _net.Transmit(packet);
        }
        else
        {
          DynamicIdAccept *acc = packet->GetData<DynamicIdAccept>();
          
          LOGN(5, "got an id! :", acc->id);
          GetState()->Id = acc->id;
        }
      }
      break;
    }
  }
  
  virtual void Tick() 
  {
    if(parentTimer.poll()) {
      if(bestParent != 0) {
        LOGN(5, "Found new parent: ", bestParent);

        GetState()->Parent = bestParent;
        GetState()->HierachyDepth = bestHierachy;

        timer.set(1);
      }
      else {
        timer.set(10000);
      }
    }

    if(GetState()->Parent == 0xFF && timer.poll())
    {
      LOG(5, "searching for parents");

      Packet p(ID_BC);

      MacAddress *mac = p.OfType<MacAddress>(DID_DISCOVER);
      GetState()->MacAddressc.GetAddress(mac);

      _net.Transmit(&p);

      bestParent = 0;
      bestHierachy = GetState()->HierachyDepth;

      parentTimer.set(7000);
      timer.set(10000);
    }
    else if(GetState()->Parent != 0xFF && GetState()->Id == 0xFF && timer.poll()) 
    {
      LOG(5, "requesting id");

      Packet p(ID_MASTER);
      p.HopReceiver = GetState()->Parent;
      p.Flags |= FLAG_MAC_MSG;
      p.Flags &= ~FLAG_NEED_ACK;
      p.PacketSender = GetState()->Parent;

      MacAddress *mac = p.OfType<MacAddress>(DID_REQ_ID);
      GetState()->MacAddressc.GetAddress(mac);

      _net.Transmit(&p);

      timer.set(10000);
    }
  }
};


#endif