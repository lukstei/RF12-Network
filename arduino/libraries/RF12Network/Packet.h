#ifndef _MESSAGE_TYPES_H__
#define _MESSAGE_TYPES_H__

#include <WProgram.h>
#include "State.h"

#define SIZE_HEADER   7
#define SIZE_DATA     MAX_DATA - SIZE_HEADER

#define FLAG_ACK      1
#define FLAG_FAIL     2
#define FLAG_MAC_MSG  4

enum MessageType
{
  MSG_EMPTY,
  
  DID_DISCOVER,
  DID_REPLY,
  DID_REQ_ID
};

typedef struct Packet
{
  Packet() :
    Length(0),
    Flags(0) {}
  
  Packet(node_id recv) :
    PacketReceiver(recv)
    {
      Packet();
    }

  uint8_t Length;
  uint8_t Flags;
  
  node_id HopReceiver;
  node_id HopSender;

  node_id PacketReceiver;
  node_id PacketSender;
  
  MessageType Type;
  
  uint8_t RawData[SIZE_DATA];

  template <class T>
  inline T& OfType(MessageType type)
  {
    Type = type;
    Length = sizeof(T) + SIZE_HEADER;
    return (T &)RawData;
  }

  template <class T>
  inline T& GetData()
  {
    return (T &)RawData;
  }

  inline bool IsForMe()
  {
    return (PacketReceiver == ID_BC && !(Flags & FLAG_MAC_MSG))  // either a broadcaste
      || HopReceiver == GetState()->Id // or a message addressed to me 
      || ((Flags & FLAG_MAC_MSG) && GetState()->MacAddressc.Equals((MacAddress*)&RawData)); // or a message addressed to my mac address
  }
} Packet;

typedef struct
{
} DataEmpty;

typedef struct
{
  MacAddress Address;
  uint8_t HierachyDepth;
} DynamicIdReply;

#endif