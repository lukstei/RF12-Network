#ifndef _STATE_H_
#define _STATE_H_

#include "Network.h"
#include "MacAddress.h"

typedef struct State
{
  State() : Id(0xFF), HierachyDepth(0xFF), Parent(0xFF) {};

  MacAddressManager MacAddressc;
  node_id Id;
  node_id Parent;
  node_id HierachyDepth;

  enum {
    Idle,
    Waiting,
    Acking,
    Retrying,
    Failure
  } volatile SendState;

  inline bool InitializationDone()
  {
    return Parent != 0xFF && Id != 0xFF;
  }
} State;

State _state;
inline State* GetState() {
  return &_state;
}

#endif