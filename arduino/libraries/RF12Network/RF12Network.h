#ifndef _RF12_NETWORK_H_
#define _RF12_NETWORK_H_

#ifndef RF12_NETWORK_AVR // included in arduino env
# define RF12_NETWORK_AVR 1
#endif

#ifndef IS_MASTER
# define IS_MASTER          1
#endif

#include "Debug.h"

#include "Network.h"
#include "State.h"

#include "Layer/PhysicalLayer.h"
#include "Layer/DataLinkLayer.h"
#include "Layer/SynchronizationLayer.h"
#include "Layer/RoutingLayer.h"

#include "Layer/RoutingLayer.h"
#include "Manager/Manager.h"

class RF12Network
{
protected:
  PhysicalLayer l1;
  DataLinkLayer l2;
  SynchronizationLayer l3;
  RoutingLayer l4;
  ApplicationLayer l5;

  DidManager m1;

  Manager* manager[1];
  Packet packet;

public:
  RF12Network() :
    l1(), l2(l1), l3(l2), l4(l3), l5(l4),
      m1(l5) 
    {
      manager[0] = &m1;
    }

    void Tick()
    {
      l5.Tick();
      m1.Tick();

      if(l5.ReceivePacket(&packet)) // call app-layer
      {
        m1.Received(&packet);
      }
    }
};


#endif