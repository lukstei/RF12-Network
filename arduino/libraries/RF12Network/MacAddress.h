#ifndef _MAC_ADDRESS_H_
#define _MAC_ADDRESS_H_

#include <avr/eeprom.h>
#include <WProgram.h>

#define MAC_EEPROM_OFFSET 0

class MacAddressManager
{
private:
  MacAddress _address;
  bool _haveRead;
  
  void Read()
  {
    for(uint8_t i = 0; i < MAC_ADDRESS_LEN; ++i)
      _address.Address[i] = eeprom_read_byte((unsigned char *) i + MAC_EEPROM_OFFSET);
  }

  void Generate()
  {
    uint8_t caddr = MAC_EEPROM_OFFSET;
    eeprom_write_byte((unsigned char *)caddr++, 0x1E);

    for(uint8_t i = 0; i < MAC_ADDRESS_LEN; ++i) {
      uint8_t ran = random(0, 0xFF);

      _address.Address[i] = ran;
      eeprom_write_byte((unsigned char *)i + caddr, ran);
    }
  }

public:
  const MacAddress &GetAddress()
  {
    if(!_haveRead)
    {
      if(eeprom_read_byte((unsigned char *)MAC_EEPROM_OFFSET) != 0x1E) // MAGIC VALUE
        Generate();
      else
        Read();

      _haveRead = true;
    }

    return _address;
  }
};

#endif