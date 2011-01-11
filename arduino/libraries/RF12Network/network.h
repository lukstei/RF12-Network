#ifndef _NETWORK_H__
#define _NETWORK_H__

#include <stdlib.h>

typedef uint8_t node_id;

#define MAC_ADDRESS_LEN 4
#define MAC_EEPROM_OFFSET 0

typedef struct MacAddress
{
  uint8_t Address[MAC_ADDRESS_LEN];

  bool operator==(const MacAddress &other) const {
    for(uint8_t i = 0; i < MAC_ADDRESS_LEN; ++i) {
      if(Address[i] != other.Address[i]) return false;
    }
    return true;
  }

  MacAddress(const MacAddress& other) {
    for(uint8_t i = 0; i < MAC_ADDRESS_LEN; ++i) {
      Address[i] = other.Address[i];
    }
  }

  MacAddress() {
    for(uint8_t i = 0; i < MAC_ADDRESS_LEN; ++i) {
      Address[i] = 0;
    }
  }
} MacAddress;
//typedef uint8_t MacAddress[MAC_ADDRESS_LEN];

#define MAX_DATA 66 // RF12_MAXDATA

// cmsa/ca: wait for (1 up to PACKET_MAX_DICE) * PACKET_LEN_MS
#define PACKET_MAX_DICE       7

#define PACKET_LEN_MS         30
#define PACKET_WAIT_FOR_ACK   28

#define MAX_RETRIES           4
#define MAX_NODES             255

#define ID_BC                 0
#define ID_MASTER             1

#if !RF12_NETWORK_AVR
typedef unsigned char uint8_t;
#endif

#endif