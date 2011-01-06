#ifndef _DATA_LINK_LAYER_H_
#define _DATA_LINK_LAYER_H_

#include <Ports.h>
#include "../Network.h"
#include "ProtocolLayer.h"

class DataLinkLayer : public ProtocolLayer {
protected:
  Packet *_buf;
  MilliTimer _timer;
  uint8_t _retries;

private:
  inline void SendAck(Packet *packet)
  {
    uint8_t origHeadLength = packet->Length;
    uint8_t origFlags = packet->Flags;
    
    packet->Length = SIZE_HEADER;

    LOG(2, "MAC: sending ack");
    packet->Flags = FLAG_ACK;

    ProtocolLayer::Transmit(packet);

    packet->Length = origHeadLength;
    packet->Flags = origFlags;
  }
 
public:
  DataLinkLayer() :
    ProtocolLayer()
  {
    GetState()->SendState = State::Idle;
  };
  
  DataLinkLayer(ProtocolLayer &layer) :
    ProtocolLayer(layer)
  {
    DataLinkLayer();
  };

  virtual void ReceiveCallback(Packet *packet)  
  {
    if(rf12_crc == 0 && packet->IsForMe()) {
      LOGN(3, "MAC: Received msg with len = ", packet->Length);

      if(packet->Flags & FLAG_FAIL) {
        LOGN(2, "MAC: transmit: fail, flags:", packet->Flags);
        GetState()->SendState = State::Failure;
        return;
      }

      // send ack
      if(!(packet->Flags & FLAG_ACK)) {
        if(packet->Flags & FLAG_NEED_ACK)
          SendAck(packet);

        ProtocolLayer::ReceiveCallback(packet); // weiter nach oben
      }
      else if(packet->Flags & FLAG_ACK) {
        LOG(2, "MAC: got ack");
        GetState()->SendState = State::Idle;
      }
    }
  };

  virtual uint8_t Transmit(Packet *packet) 
  {
    LOGN(2, "MAC: transmit packet with flags = ", packet->Flags);
    
    if( GetState()->SendState == State::Idle || 
        GetState()->SendState == State::Retrying || 
        GetState()->SendState == State::Failure) 
    {
      if(GetState()->SendState != State::Retrying) {
        //memcpy(&_buf, packet, packet->Length); // TODO: memcpy unnoetig?
        _buf = packet;
        _retries = MAX_RETRIES;
      }
      
      GetState()->SendState = State::Waiting;
      _timer.set(PACKET_LEN_MS * random(1, PACKET_MAX_DICE));
      return true;
    }
    else return false;
  };

  virtual void Tick() {
    if(GetState()->SendState == State::Acking && _timer.poll()) { // ack timeout
      if(--_retries == 0) {
        LOG(2, "MAC: max retries!!");
        GetState()->SendState = State::Failure;
        // packet cannot be sent
      }
      else {
        LOGN(2, "MAC: retries left: ", _retries);
        GetState()->SendState = State::Retrying;
        Transmit(_buf);
      }
    }
    else if(GetState()->SendState == State::Waiting && _timer.poll()) 
    {
      if(!ProtocolLayer::Transmit(_buf))  // medium busy
      {
        LOG(2, "MAC: medium busy");
        _timer.set(PACKET_LEN_MS * random(1, PACKET_MAX_DICE)); // rearm timer and wait again
      }
      else { // packet sent
        if(_buf->Flags & FLAG_NEED_ACK) {
          LOG(2, "MAC: packet sent, waiting for ack");

          GetState()->SendState = State::Acking;
          _timer.set(PACKET_WAIT_FOR_ACK);
        }
        else {
          LOG(2, "Message sent");
          GetState()->SendState = State::Idle;
        }
      }
    }
    
    ProtocolLayer::Tick();
  };
};
//
//
//class SynchronizationLayer : public ProtocolLayer 
//{
//  volatile uint8_t _sync;
//  MilliTimer _timer;
//  Packet *_lastPacket;
//  
//public:
//  SynchronizationLayer() :
//    ProtocolLayer()
//  {
//  };
//  
//  SynchronizationLayer(ProtocolLayer &layer) :
//    ProtocolLayer(layer)
//  {
//    SynchronizationLayer();
//  };
//  
//  virtual Packet *ReceiveCallback(Packet *packet)  {
//    _sync = true;
//    _lastPacket = packet;
//    
//    return ProtocolLayer::ReceiveCallback(packet);
//  };
//  
//  virtual uint8_t Transmit(Packet *packet) {
//    LOG(5, "send called");
//    
//    while(!ProtocolLayer::Transmit(packet))
//      Tick();
//    
//    while(GetState()->SendState != State::Idle && GetState()->SendState != State::Failure) 
//      Tick();
//    
//    LOGN(5, "success =", GetState()->SendState == State::Idle);
//    
//    return GetState()->SendState == State::Idle;
//  };
//  
//  Packet *receive(int timeout = 10000) {
//    LOG(5, "receiveing pckt");
//    
//    _sync = false;
//    _timer.set(timeout); // timeout
//    
//    while(!_sync && !_timer.poll()) 
//      Tick();
//      
//    LOGN(5, "receive =", _sync);
//    return _sync ? _lastPacket : NULL;
//  };
//  
//  virtual void Tick() {
//    ProtocolLayer::Tick();
//  };
//};
//
//class RoutingLayer : public ProtocolLayer {
//protected:
//  RoutingTable<MAX_NODES> _table;
//
//public:
//  RoutingLayer() :
//    ProtocolLayer()
//  {
//
//  };
//
//  RoutingLayer(ProtocolLayer &layer) :
//    ProtocolLayer(layer)
//  {
//    RoutingLayer();
//  };
//
//  node_id get_next_station(Packet *packet) 
//  {
//    if(low_level_message(packet))
//    {
//      DynamicId *data = message_type_read<DynamicId>(packet);
//      if(data->Parent == GetState()->Id)
//        return ID_BC;
//      else if(low_address_my_id(&data->Address))
//        return data->Parent;
//    }
//
//    node_id child = _table.FindNextHop(packet->PacketReceiver);
//    return child != 0 ? child : GetState()->Parent;
//  };
//
//  bool InitializationDone()
//  {
//    return GetState()->Parent != 0xFF && GetState()->Id != 0xFF;
//  };
//
//  virtual Packet *ReceiveCallback(Packet *packet)  
//  {
//    if(packet->Flags & FLAG_FAIL) {
//      LOG(4, "received message with fail flag");
//
//      if(_table.Find(packet->HopSender)) 
//        _table.RemoveNode(packet->HopSender);
//      else
//        GetState()->Parent = 0xFF;
//
//      return NULL;
//    }
//    
//    if(packet->PacketReceiver != GetState()->Id) 
//    {
//      if(InitializationDone()) {
//        packet->HopSender = GetState()->Id;
//        packet->HopReceiver = get_next_station(packet);
//        LOGN(4, "Routing: forwarding message to node", packet->HopReceiver);
//      }
//      else {
//        message_type_write<MSG_EMPTY, DataEmpty>(packet);
//        packet->Flags = FLAG_FAIL;
//      }
//      return packet;
//    }
//    else return ProtocolLayer::ReceiveCallback(packet);
//  };
//
//  virtual uint8_t Transmit(Packet *packet) {
//    LOG(4, "Routing: transmit");
//
//    if(!InitializationDone(packet)) return false;
//
//    packet->HopReceiver = get_next_station(packet);
//    packet->HopSender = GetState()->Id;
//
//    return ProtocolLayer::Transmit(packet);
//  };
//
//  virtual void Tick() {
//    ProtocolLayer::Tick();
//  };
//};
//
//class DynamicIdManager : public Manager {
//protected:
//  MilliTimer timer;
//
//public:
//  DynamicIdLayer() :
//      ProtocolLayer()
//      {
//
//      };
//
//      DynamicIdLayer(ProtocolLayer &layer) :
//      ProtocolLayer(layer)
//      {
//        DynamicIdLayer();
//      };
//
//      virtual Packet *receive_callback(Packet *packet)  {
//        LOG(3, "DID: receive");
//
//        if(packet->Type == DID_DISCOVER) {
//          if(GetState()->Id != 0xFF) {
//            DynamicIdReply *data = message_type_write<DID_REPLY, DynamicIdReply>(packet);
//            data->Node = GetState()->Id;
//            data->HierachyDepth = GetState()->HierachyDepth;
//            packet->HopReceiver = ID_BC;
//
//            return packet;
//          }
//        }
//        if(packet->Type == DID_REPLY) {
//          DynamicIdReply *data = message_type_read<DynamicIdReply>(packet);
//
//          if(data->HierachyDepth <= GetState()->HierachyDepth) {
//            // found a new parent
//            LOGN(3, "Found a new parent with id =", data->Node);
//            GetState()->Parent = data->Node;
//            GetState()->HierachyDepth = data->HierachyDepth + 1;
//          }
//
//          DynamicId *data = message_type_write<DID_REQ_ID, DynamicId>(packet);
//          data->Parent = GetState()->Parent;
//          packet->PacketReceiver = ID_MASTER;
//
//          return packet;
//        }
//        else return ProtocolLayer::ReceiveCallback(packet);
//      };
//
//      virtual void tick() {
//        if(GetState()->Parent == 0xFF && timer.poll(2000)) {
//          LOG(3, "Searching for nodes...");
//          Packet *sbuf = get_send_buffer();
//
//          DynamicId *data = message_type_write<DID_DISCOVER, DynamicId>(sbuf);
//          low_address_get(&data->Address);
//
//          send(ID_BC, sbuf);
//        }
//
//        ProtocolLayer::Tick();
//      };
//};

#endif