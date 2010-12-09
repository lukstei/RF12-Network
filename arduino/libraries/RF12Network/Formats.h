#ifndef __FORMATS_H__
#define __FORMATS_H__

#ifdef WIN32
const int RF12_MAXDATA = 66;
typedef unsigned char uint8_t;
#endif

typedef uint8_t node_id;

typedef struct
{
  struct Head
  {
    uint8_t messageLength; // important: must be the first item!
    
    node_id receiver;
    node_id sender;
    
    uint8_t flags;
    
    uint8_t messageType;
  } head;

  union Formats
  {
    uint8_t raw[RF12_MAXDATA - sizeof(Head)/sizeof(uint8_t)];  // Todo: richtige size?

    struct MessageNodeFound
    {
      node_id nodeId;
      uint8_t hierachyDepth;
    } MessageNodeFound;

    struct MessagePotiValues
    {
      int data[10];
    } MessagePotiValues;
  } data;
  
} RF12Message;

#endif