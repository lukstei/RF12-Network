#ifndef __LOW_ADDRESS_H_
#define __LOW_ADDRESS_H_

#include <EEPROM.h>
#include <Ports.h>

#define LOW_ADRESS_LEN 4

typedef uint8_t low_address_t[LOW_ADRESS_LEN];

void low_address_read(uint8_t addr_offset);

void low_address_generate(uint8_t addr_offset);

void low_address_get(low_address_t *buf, uint8_t addr_offset = 0);

bool low_address_my_id(low_address_t *buf);

#endif