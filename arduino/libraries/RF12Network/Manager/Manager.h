#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "../Network.h"
#include "../Packet.h"

class Manager
{
protected:
  ProtocolLayer _net;

public:
  Manager(ProtocolLayer &network) :
    _net(network)
  {
  };

  virtual void Received(Packet *packet) = 0;
  virtual void Tick() = 0;
};


#endif