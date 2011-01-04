#ifndef _DID_MANAGER_H_
#define _DID_MANAGER_H_

#include "../Network.h"
#include "../Packet.h"
#include "Manager.h"

#include <Ports.h>

class DidManager : public Manager
{
  MilliTimer timer;

public:
  DidManager(ProtocolLayer &network) :
      Manager(network)
  {
  };

  virtual void Received(Packet *packet) 
  {
    switch(packet->Type) {
    case DID_DISCOVER:
      {
        if(GetState()->InitializationDone()) {
          LOG(5, "Someone searches for friends");

          Packet p(ID_BC);
          p.Flags |= FLAG_MAC_MSG;

          DynamicIdReply rep = p.OfType<DynamicIdReply>(DID_REPLY);
          memcpy(rep.Address, packet->RawData, MAC_ADDRESS_LEN);
          rep.HierachyDepth = GetState()->HierachyDepth;

          _net.Transmit(&p);
        }
      }

    case DID_REPLY:
      {
        DynamicIdReply rep = packet->GetData<DynamicIdReply>();
        if(rep.HierachyDepth + 1 < GetState()->HierachyDepth ) {
          LOGN(5, "Found new parent: ", packet->PacketSender);

          GetState()->Parent = packet->PacketSender;
          GetState()->HierachyDepth = rep.HierachyDepth + 1;
        }
      }
    }
  }
  
  virtual void Tick() 
  {
    if(GetState()->Parent = 0xFF && timer.poll(5000))
    {
      LOG(5, "searching for parents");

      Packet p(ID_BC);

      MacAddress mac = p.OfType<MacAddress>(DID_DISCOVER);
      GetState()->MacAddressc.GetAddress(&mac);

      _net.Transmit(&p);
    }
    else if(GetState()->Parent != 0xFF && GetState()->Id == 0xFF) {

    }
  }
};


#endif