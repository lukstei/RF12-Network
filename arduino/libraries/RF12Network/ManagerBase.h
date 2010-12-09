#ifndef __MANAGERBASE_H__
#define __MANAGERBASE_H__

#include <RF12Network.h>

class ManagerBase {
protected:
  RF12Base *_rf12;

public:
  ManagerBase(RF12Base *rf12) :
      _rf12(rf12) 
  {
  };

  virtual bool messageReceived(uint8_t msgType) {};
};

#endif