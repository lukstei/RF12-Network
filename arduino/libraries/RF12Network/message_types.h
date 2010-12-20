#ifndef _MESSAGE_TYPES_H__
#define _MESSAGE_TYPES_H__

#define HEADER_SIZE 5

#include <stdint.h>

typedef uint8_t node_id;

#include "low_address.h"

enum message_type
{
  MSG_EMPTY,
  
  DID_DISCOVER,
  DID_REPLY
};

#define FLAG_ACK 1
#define FLAG_FAIL 2

typedef struct net_packet_t
{
  net_packet_t() :
    length(0),
    flags(0) {}

  uint8_t length;
  uint8_t flags;
  
  node_id receiver;
  node_id sender;

  node_id real_receiver;
  node_id real_sender;
  
  uint8_t type;
  
  uint8_t data[MAX_DATA - 3];
} net_packet_t;

typedef struct
{
} EmptyMessage;

typedef struct
{
  low_address_t address;
} DynamicIdDiscover;

typedef struct
{
  low_address_t address;
  
  node_id node;
  uint8_t hierachy_depth;
} DynamicIdReply;

template <uint8_t MessageType, class MessageStruct>
MessageStruct *message_type_write(net_packet_t *packet)
{
  packet->type = MessageType;
  packet->length = sizeof(MessageStruct) + HEADER_SIZE;
  return (MessageStruct *)packet->data;
}

template <class MessageStruct>
inline MessageStruct *message_type_read(net_packet_t *packet)
{
  return (MessageStruct *)packet->data;
}

#endif