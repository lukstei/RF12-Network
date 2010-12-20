#ifndef __PHY_LAYER_H_
#define __PHY_LAYER_H_

#include "network.h"
#include <WProgram.h>
#include <Ports.h>
#include <RF12.h>
#include "routing_table.h"

class PhysicalLayer;
static PhysicalLayer *instance;

void isr_receive_callback();

// Layers:
//
// 1: PhysicalLayer (RF12)
// 2: MacLayer
// 3: SynchronizationLayer
// 4: RoutingLayer

class PhysicalLayer : public ProtocolLayer {
protected: 
  net_packet_t buf;
  
public:
  PhysicalLayer() :
    ProtocolLayer()
  {
    instance = this;
    rf12_set_receive_callback(&isr_receive_callback);
    
    rf12_initialize();
  };
  
  PhysicalLayer(ProtocolLayer &layer) :
    ProtocolLayer(layer)
  {
    PhysicalLayer();
  };
  
  void receive_callback()
  {
    LOG(1, "Physical: ISR called");
    memcpy(&buf, (const void *)rf12_data, rf12_len_safe);
    receive_callback(&buf);
  };

  virtual net_packet_t *receive_callback(net_packet_t *packet)  {
    LOG(1, "Physical: receive");

    return ProtocolLayer::receive_callback(packet);
  };
  
  virtual uint8_t transmit(net_packet_t *packet) {
    LOG(1, "Physical: transmit");
    
    rf12_sendStart(packet, packet->length);
    return ProtocolLayer::transmit(packet);
  };
  
  virtual void tick() {
    rf12_recvDone();
    ProtocolLayer::tick();
  };
};

inline void isr_receive_callback()
{
  instance->receive_callback();
}

class DataLinkLayer : public ProtocolLayer {
protected:
  net_packet_t buf;
  MilliTimer timer;
  uint8_t retries;
 
public:
  DataLinkLayer() :
    ProtocolLayer()
  {
    get_state()->send_state = state_t::idle;
  };
  
  DataLinkLayer(ProtocolLayer &layer) :
    ProtocolLayer(layer)
  {
    DataLinkLayer();
  };

  virtual net_packet_t *receive_callback(net_packet_t *packet)  
  {
    if(rf12_crc == 0 && message_is_for_me(packet)) {
      LOGN(3, "MAC: Received msg with len = ", packet->length);
      net_packet_t *reply = NULL;

      if(packet->type != MSG_EMPTY && !(packet->flags & FLAG_FAIL))
        reply = ProtocolLayer::receive_callback(packet);

      // send ack
      if(!(packet->flags) & FLAG_ACK && packet->receiver != ID_BC) {
        if(reply == NULL) {
          reply = packet;
          reply->length = HEADER_SIZE;
          reply->type = MSG_EMPTY;
        }

        LOG(2, reply->type == MSG_EMPTY ? "MAC: sending ack" : "MAC: sending ack with reply");
        reply->flags |= FLAG_ACK;
        
        ProtocolLayer::transmit(packet);
      }
      else if(packet->flags & FLAG_ACK) {
        LOG(2, "MAC: got ack");
        get_state()->send_state = state_t::idle;  

        if(reply != NULL) {
          reply->flags |= FLAG_ACK;
          transmit(reply);
        }
      }
      else if(packet->flags & FLAG_FAIL) {
        LOG(2, "MAC: transmit: fail");
        get_state()->send_state = state_t::failure;
      }
    }

    return NULL;
  };
  
  virtual uint8_t transmit(net_packet_t *packet) 
  {
    LOGN(2, "MAC: transmit packet with length = ", packet->length);
    
    if( get_state()->send_state == state_t::idle || 
        get_state()->send_state == state_t::retrying || 
        get_state()->send_state == state_t::failure) 
    {
      if(get_state()->send_state != state_t::retrying) {
        memcpy(&buf, packet, packet->length);
        retries = MAX_RETRIES;
      }
      
      get_state()->send_state = state_t::waiting;
      timer.set(PACKET_LEN_MS * random(1, PACKET_MAX_DICE));
      
      return true;
    }
    else return false;
  };
  
  virtual void tick() {
    if(get_state()->send_state == state_t::acking && timer.poll()) { // ack timeout
      if(--retries == 0) {
        LOG(2, "MAC: max retries!!");
        get_state()->send_state = state_t::failure;
        // packet cannot be sent
      }
      else {
        LOGN(2, "MAC: retries left: ", retries);
        get_state()->send_state = state_t::retrying;
        transmit(&buf);
      }
    }
    else if(get_state()->send_state == state_t::waiting && timer.poll()) 
    {
      if(!ProtocolLayer::transmit(&buf))  // medium busy
      {
        LOG(2, "MAC: medium busy");
        timer.set(PACKET_LEN_MS * random(1, PACKET_MAX_DICE)); // rearm timer and wait again
      }
      else { // packet sent
        if(buf.receiver != ID_BC) {
          LOG(2, "MAC: packet sent, waiting for ack");

          get_state()->send_state = state_t::acking;
          timer.set(PACKET_WAIT_FOR_ACK);
        }
        else {
          LOG(2, "Broadcast sent");
          get_state()->send_state = state_t::idle;
        }
      }
    }
    
    ProtocolLayer::tick();
  };
};


class SynchronizationLayer : public ProtocolLayer 
{
  volatile uint8_t sync;
  MilliTimer timer;
  net_packet_t *last_packet;
  
public:
  SynchronizationLayer() :
    ProtocolLayer()
  {
  };
  
  SynchronizationLayer(ProtocolLayer &layer) :
    ProtocolLayer(layer)
  {
    SynchronizationLayer();
  };
  
  virtual net_packet_t *receive_callback(net_packet_t *packet)  {
    sync = true;
    last_packet = packet;
    
    return ProtocolLayer::receive_callback(packet);
  };
  
  virtual uint8_t transmit(net_packet_t *packet) {
    LOG(5, "send called");
    
    while(!ProtocolLayer::transmit(packet))
      tick();
    
    while(get_state()->send_state != state_t::idle && get_state()->send_state != state_t::failure) 
      tick();
    
    LOGN(5, "success =", get_state()->send_state == state_t::idle);
    
    return get_state()->send_state == state_t::idle;
  };
  
  net_packet_t *receive(int timeout = 10000) {
    LOG(5, "receiveing pckt");
    
    sync = false;
    timer.set(timeout); // timeout
    
    while(!sync && !timer.poll()) 
      tick();
      
    LOGN(5, "receive =", sync);
    return sync ? last_packet : NULL;
  };
  
  virtual void tick() {
    ProtocolLayer::tick();
  };
};

class RoutingLayer : public ProtocolLayer {
protected:
  RoutingTable<MAX_NODES> table;

public:
  RoutingLayer() :
    ProtocolLayer()
  {

  };

  RoutingLayer(ProtocolLayer &layer) :
    ProtocolLayer(layer)
  {
    RoutingLayer();
  };

  node_id get_next_station(node_id receiver) {
    node_id child = table.find_next_child(receiver);
    return child != 0 ? child : get_state()->parent;
  };

  bool ready_to_send()
  {
    return get_state()->parent != 0xFF && get_state()->my_id != 0xFF;
  };

  virtual net_packet_t *receive_callback(net_packet_t *packet)  
  {
    if(packet->flags & FLAG_FAIL) {
      table.remove(packet->sender); // was machen??
      get_state()->parent = 0xFF;

      return NULL;
    }
    else if(packet->real_receiver != get_state()->my_id) 
    {
      if(ready_to_send()) {
        packet->sender = get_state()->my_id;// here work
        packet->receiver = get_next_station(packet->real_receiver);
        LOGN(4, "Routing: forwarding message to node", packet->receiver);
      }
      else 
      {
        message_type_write<MSG_EMPTY, EmptyMessage>(packet);
        packet->flags = FLAG_FAIL;
      }
      return packet;
    }
    else return ProtocolLayer::receive_callback(packet);
  };

  virtual uint8_t transmit(net_packet_t *packet) {
    LOG(4, "Routing: transmit");

    if(!ready_to_send()) return false;

    packet->receiver = get_next_station(packet->real_receiver);
    packet->sender = get_state()->my_id;

    return ProtocolLayer::transmit(packet);
  };

  virtual void tick() {
    ProtocolLayer::tick();
  };
};

class DynamicIdLayer : public ProtocolLayer {
protected:
  MilliTimer timer;

public:
  DynamicIdLayer() :
      ProtocolLayer()
      {

      };

      DynamicIdLayer(ProtocolLayer &layer) :
      ProtocolLayer(layer)
      {
        DynamicIdLayer();
      };

      virtual net_packet_t *receive_callback(net_packet_t *packet)  {
        LOG(3, "DID: receive");

        if(packet->type == DID_DISCOVER) {
          if(get_state()->my_id != 0xFF) {
            DynamicIdReply *data = message_type_write<DID_REPLY, DynamicIdReply>(packet);
            data->node = get_state()->my_id;
            data->hierachy_depth = get_state()->hierachy_depth;
            packet->receiver = ID_BC;

            return packet;
          }
        }
        if(packet->type == DID_REPLY) {
          DynamicIdReply *data = message_type_read<DynamicIdReply>(packet);

          if(data->hierachy_depth <= get_state()->hierachy_depth) {
            // found a new parent
            LOGN(3, "Found a new parent with id =", data->node);
            get_state()->parent = data->node;
            get_state()->hierachy_depth = data->hierachy_depth + 1;
          }

          return NULL;
        }
        else return ProtocolLayer::receive_callback(packet);
      };

      virtual uint8_t transmit(net_packet_t *packet) {
        LOG(3, "DID: transmit");

        return ProtocolLayer::transmit(packet);
      };

      virtual void tick() {
        if(get_state()->parent == 0xFF && timer.poll(2000)) {
          LOG(3, "Searching for nodes...");
          net_packet_t *sbuf = get_send_buffer();

          DynamicIdDiscover *data = message_type_write<DID_DISCOVER, DynamicIdDiscover>(sbuf);
          low_address_get(&data->address);

          send(ID_BC, sbuf);
        }

        ProtocolLayer::tick();
      };
};

#endif