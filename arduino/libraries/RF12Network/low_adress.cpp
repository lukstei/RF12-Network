#include <EEPROM.h>
#include <Ports.h>
#include "low_address.h"

bool have_read = false;
low_address_t low_address_buf;

void low_address_read(uint8_t addr_offset)
{
  for(uint8_t i = 0; i < LOW_ADRESS_LEN; ++i)
    low_address_buf[i] = EEPROM.read(i + addr_offset);

  have_read = true;
}

void low_address_generate(uint8_t addr_offset)
{
  EEPROM.write(addr_offset++, 0x1E);

  for(uint8_t i = 0; i < LOW_ADRESS_LEN; ++i) {
    uint8_t ran = random(0, 0xFF);

    low_address_buf[i] = ran;
    EEPROM.write(i + addr_offset, ran);
  }

  have_read = true;
}

void low_address_get(low_address_t *buf, uint8_t addr_offset)
{
  if(!have_read)
  {
    if(EEPROM.read(addr_offset) != 0x1E) // MAGIC VALUE
      low_address_generate(addr_offset);
    else
      low_address_read(addr_offset);
  }

  memcpy(buf, &low_address_buf, LOW_ADRESS_LEN);
}


bool low_address_my_id(low_address_t *buf) {
  if(!have_read) return false;
  for(uint8_t i = 0; i < LOW_ADRESS_LEN; ++i) {
    if((*buf)[i] != low_address_buf[i]) return false;
  }
  return true;
}