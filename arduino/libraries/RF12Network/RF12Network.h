#ifndef __RF12NETWORK_H__
#define __RF12NETWORK_H__

//#define DEBUG 1

#define ID_BC 0 //broadcast
#define ID_MASTER 1

#define FLAG_NEED_ACK 1
#define FLAG_ACK      2
#define FLAG_NAK      4

typedef uint8_t node_id;

typedef struct
{
  struct Head
  {
    uint8_t messageLength; // important: must be the first item!

    uint8_t flags;

    node_id messageReceiver;
    node_id messageSender;
    node_id sender;
    
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


#define RF12_MAX_DATA_LENGTH (RF12_MAXDATA - sizeof(RF12Message::Head)/sizeof(byte))

/*
#if RF12_MAXDATA < sizeof(RF12Message)
# error "RF12Message is bigger than RF12_MAXDATA"
#endif
*/

enum MessageTypes
{
  MSG_FWD = 22, // Forward
  MSG_NODE_DISCOVER, // Slave auf suche, bitte melden
  MSG_NODE_FOUND, // Freund gefunden
  MSG_POTI_VALUES,
  
  MSG_DATA_LOG // irgendwelche daten
};


#ifdef DEBUG
# define PRELOG()                Serial.print("log> "); 
# define LOG(str)                PRELOG(); Serial.println(str)
# define LOG2(str1, str2)        PRELOG(); Serial.print(str1); Serial.print(" "); Serial.println(str2)
# define LOG3(str1, str2, str3)  PRELOG(); Serial.print(str1); Serial.print(" "); Serial.print(str2); Serial.print(" "); Serial.println(str3)
# define LOGN(str, num)          PRELOG(); Serial.print(str); Serial.print(" "); Serial.println(num, DEC)
# define LOGN2(str, num1, num2)  PRELOG(); Serial.print(str); Serial.print(" "); Serial.print(num1, DEC); Serial.print(", "); Serial.println(num2, DEC)
# define LOGC(ch)                Serial.print(ch)

# define ENUM_AS_STRING(name) #name
# define LOGM(str, enu)    PRELOG(); Serial.print(str); Serial.print(" "); Serial.println(MessageTypesNames[enu - 22])

const char* MessageTypesNames[] =
{
  ENUM_AS_STRING(MSG_FWD), // Forward
  ENUM_AS_STRING(MSG_NODE_DISCOVER), // Slave auf suche, bitte melden
  ENUM_AS_STRING(MSG_NODE_FOUND), // Freund gefunden
  ENUM_AS_STRING(MSG_POTI_VALUES),
  ENUM_AS_STRING(MSG_DATA_LOG), // irgendwelche daten
  
  ENUM_AS_STRING(FILL MessageTypeNames in!),
  ENUM_AS_STRING(FILL MessageTypeNames in!),
};

#else
# define LOG(str) 
# define LOG2(str1, str2) 
# define LOG3(str1, str2, str3) 
# define LOGN(str, num)
# define LOGN2(str, num1, num2)
# define LOGC(ch) 
# define LOGM(str, enu)
#endif

#include "RF12Base.h"
#include "RF12Slave.h"
#include "RF12Master.h"

#endif