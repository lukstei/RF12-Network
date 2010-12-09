#ifndef __RF12NETWORK_H__
#define __RF12NETWORK_H__

#include <Ports.h>
#include <RF12.h>
#include "Formats.h"

#define DEBUG 1

#define ID_BC     0 //broadcast
#define ID_MASTER 1

#define FLAG_NEED_ACK 1
#define FLAG_ACK      2
#define FLAG_NAK      4


#define RF12_MAX_DATA_LENGTH (RF12_MAXDATA - sizeof(RF12Message::Head)/sizeof(byte))

/*
#if RF12_MAXDATA < sizeof(RF12Message)
# error "RF12Message is bigger than RF12_MAXDATA"
#endif
*/

enum MessageTypes
{
  MSG_NO_DATA,

  NODE_DISCOVER, // Slave auf suche, bitte melden
  NODE_FOUND, // Freund gefunden

  MSG_FWD,

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
# define LOGM(str, enu)    PRELOG(); Serial.print(str); Serial.print(" "); Serial.println(MessageTypesNames[enu])

const char* MessageTypesNames[] =
{
  ENUM_AS_STRING(MSG_NO_DATA),

  ENUM_AS_STRING(NODE_DISCOVER), // Slave auf suche, bitte melden
  ENUM_AS_STRING(NODE_FOUND), // Freund gefunden

  ENUM_AS_STRING(MSG_FWD),

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