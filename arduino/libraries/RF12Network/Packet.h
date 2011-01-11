#ifndef _PACKET_H_
#define _PACKET_H_

#include "Network.h"

#if RF12_NETWORK_AVR
# include "State.h"
#endif

#define SIZE_HEADER   8
#define SIZE_DATA     MAX_DATA - SIZE_HEADER

#define FLAG_ACK      1
#define FLAG_NEED_ACK 2
#define FLAG_FAIL     4
#define FLAG_MAC_MSG  8

enum MessageType
{
  MSG_EMPTY,
  
  DID_DISCOVER,
  DID_REPLY,
  DID_REQ_ID,
  DID_ACCEPT,

  NODE_DOWN,
  NODE_CHANGE_PARENT
};

typedef struct Packet
{
  uint8_t Length;
  uint8_t Flags;
  
  node_id HopReceiver;
  node_id HopSender;
  
  MessageType Type;

  node_id PacketReceiver;
  node_id PacketSender;
  
  uint8_t RawData[SIZE_DATA];
  
  Packet() :
    Length(0),
    Flags(FLAG_NEED_ACK),
    PacketReceiver(0xFF), PacketSender(0xFF),
    Type(MSG_EMPTY)  {
    }
  
  Packet(node_id recv) :
      Length(0),
      Flags(FLAG_NEED_ACK),
      Type(MSG_EMPTY), 
      PacketReceiver(recv), PacketSender(0xFF) 
    {
    }
  
#if RF12_NETWORK_AVR
  template <class T>
  inline T* OfType(MessageType type)
  {
    Type = type;
    Length = sizeof(T) + SIZE_HEADER;
    return (T *)&RawData;
  }

  template <class T>
  inline T* GetData()
  {
    return (T *)&RawData;
  }
  
  inline bool IsForMe()
  {
    return ((PacketReceiver == ID_BC && !(Flags & FLAG_MAC_MSG))  // either a broadcast
      || HopReceiver == GetState()->Id // or a message addressed to me 
      || ((Flags & FLAG_MAC_MSG) && GetState()->MacAddressc.GetAddress() == *GetData<MacAddress>())) // or a message addressed to my mac address
      || (Type == DID_DISCOVER && !(GetState()->MacAddressc.GetAddress() == *GetData<MacAddress>())); // or a discover message
  }
#endif
} Packet;

typedef struct
{
} DataEmpty;

typedef struct
{
  MacAddress Address;
  node_id Id;
  uint8_t HierachyDepth;
} DynamicIdReply;

typedef struct 
{
  MacAddress address;
  node_id id;
  node_id parent;
} DynamicIdAccept;

typedef struct
{
  node_id id;
  node_id newParent;
} NodeNewParent;

typedef struct
{
  uint8_t command;
} NodeCommand;

#endif
