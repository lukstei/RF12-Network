#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <stdlib.h>
#include <RF12.h> // for RF12_MAXDATA

typedef uint8_t node_id;

#define MAX_DATA RF12_MAXDATA

// cmsa/ca: wait for (1 up to PACKET_MAX_DICE) * PACKET_LEN_MS
#define PACKET_MAX_DICE       7

#define PACKET_LEN_MS         30
#define PACKET_WAIT_FOR_ACK   28

#define MAX_RETRIES           4
#define MAX_NODES             255

#ifndef IS_MASTER
# define IS_MASTER          1
#endif

#ifndef DEBUG
# define DEBUG                 1
# define LOG_LEVEL             0
#endif

#define ID_BC                 0
#define ID_MASTER             1

#if DEBUG
# define PRELOG()                   Serial.print("> "); 
# define LOG(n, str)                if(n >= LOG_LEVEL) {PRELOG(); Serial.println(str);}
# define LOG2(n, str1, str2)        if(n >= LOG_LEVEL) {PRELOG(); Serial.print(str1); Serial.print(" "); Serial.println(str2);}
# define LOG3(n, str1, str2, str3)  if(n >= LOG_LEVEL) {PRELOG(); Serial.print(str1); Serial.print(" "); Serial.print(str2); Serial.print(" "); Serial.println(str3);}
# define LOGN(n, str, num)          if(n >= LOG_LEVEL) {PRELOG(); Serial.print(str); Serial.print(" "); Serial.println(num, DEC);}
# define LOGN2(n, str, num1, num2)  if(n >= LOG_LEVEL) {PRELOG(); Serial.print(str); Serial.print(" "); Serial.print(num1, DEC); Serial.print(", "); Serial.println(num2, DEC);}
# define LOGC(n, ch)                if(n >= LOG_LEVEL) {Serial.print(ch);}
#else
# define LOG(n, str) 
# define LOG2(n, str1, str2) 
# define LOG3(n, str1, str2, str3) 
# define LOGN(n, str, num)
# define LOGN2(n, str, num1, num2)
# define LOGC(n, ch) 
# define LOGM(n, str, enu)
#endif

#include "Layer/RoutingLayer.h"
#include "Manager/Manager.h"

class Network
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
  Network() :
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


#include "Layer/PhysicalLayer.h"
#include "Layer/DataLinkLayer.h"
#include "Layer/SynchronizationLayer.h"
#include "Layer/RoutingLayer.h"

#endif