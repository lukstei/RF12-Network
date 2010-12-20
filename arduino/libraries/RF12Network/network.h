#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <stdlib.h>
#include <RF12.h> // for RF12_MAXDATA

#define MAX_DATA RF12_MAXDATA

// cmsa/ca: wait for (1 up to PACKET_MAX_DICE) * PACKET_LEN_MS
#define PACKET_MAX_DICE 7

#define PACKET_LEN_MS 50
#define PACKET_WAIT_FOR_ACK 49

#define MAX_RETRIES 4

#define MAX_NODES 255

#define DEBUG
#define LOG_LEVEL 0

#define ID_BC     0
#define ID_MASTER 1

#include "message_types.h"

typedef struct state_t
{
  state_t() : my_id(0xFF), hierachy_depth(0xFF), parent(0xFF) {};

  node_id my_id;
  node_id parent;
  node_id hierachy_depth;
  
  enum {
    idle,
    waiting,
    acking,
    retrying,
    failure
  } send_state;

} state_t;

inline volatile state_t *get_state();
bool message_is_for_me(net_packet_t *pkg);
inline bool low_level_message(net_packet_t *pkg);

class ProtocolLayer;

typedef struct 
{
  ProtocolLayer *lower_layer;
  ProtocolLayer *upper_layer;
} protocol_layer_t;

class ProtocolLayer
{
protected:
  protocol_layer_t protocol_layer;
  //static net_packet_t send_buf;
  
  inline net_packet_t *get_send_buffer() { static net_packet_t send_buf; return &send_buf; };

public:
  ProtocolLayer() {
    protocol_layer.lower_layer = protocol_layer.upper_layer = NULL;
  };
  
  ProtocolLayer(ProtocolLayer &layer) {
    ProtocolLayer();
    
    protocol_layer.lower_layer = &layer;
    layer.get_layer()->upper_layer = this;
  };
  
  protocol_layer_t *get_layer() {
    return &protocol_layer;
  };
  
  virtual net_packet_t *receive_callback(net_packet_t *packet)  {
    if(protocol_layer.upper_layer !=  NULL)
      return protocol_layer.upper_layer->receive_callback(packet);
    return NULL;
  };
  
  virtual uint8_t transmit(net_packet_t *packet) {
    if(protocol_layer.lower_layer !=  NULL)
      return protocol_layer.lower_layer->transmit(packet);
      
    return true;
  };
  
  uint8_t send(node_id receiver, net_packet_t *packet) {
    packet->sender = get_state()->my_id;
    packet->receiver = receiver;
    
    return transmit(packet);
  };
  
  virtual void tick() {
    if(protocol_layer.lower_layer !=  NULL)
      protocol_layer.lower_layer->tick();
  };
};


#ifdef DEBUG
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

#include "phy_layer.h"


#endif