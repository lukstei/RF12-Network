#ifndef _MAC_ADDRESS_H_
#define _MAC_ADDRESS_H_

#include <avr/eeprom.h>
#include <WProgram.h>

#define MAC_ADDRESS_LEN 4
#define MAC_EEPROM_OFFSET 0

typedef uint8_t MacAddress[MAC_ADDRESS_LEN];

class MacAddressManager
{
private:
  MacAddress _address;
  bool _haveRead;
  
  void Read()
  {
    for(uint8_t i = 0; i < MAC_ADDRESS_LEN; ++i)
      _address[i] = eeprom_read_byte((unsigned char *) i + MAC_EEPROM_OFFSET);
  }

  void Generate()
  {
    uint8_t caddr = MAC_EEPROM_OFFSET;
    eeprom_write_byte((unsigned char *)caddr++, 0x1E);

    for(uint8_t i = 0; i < MAC_ADDRESS_LEN; ++i) {
      uint8_t ran = random(0, 0xFF);

      _address[i] = ran;
      eeprom_write_byte((unsigned char *)i + caddr, ran);
    }
  }

public:
  static void Copy(MacAddress *dest, const MacAddress *src) {
    memcpy(dest, src, MAC_ADDRESS_LEN);
  }

  void GetAddress(MacAddress *buf)
  {
    if(!_haveRead)
    {
      if(eeprom_read_byte((unsigned char *)MAC_EEPROM_OFFSET) != 0x1E) // MAGIC VALUE
        Generate();
      else
        Read();

      _haveRead = true;
    }

    memcpy(buf, &_address, sizeof(MacAddress));
  }

  bool Equals(MacAddress *other) const
  {
    if(!_haveRead) return false;

    for(uint8_t i = 0; i < MAC_ADDRESS_LEN; ++i) {
      if((*other)[i] != _address[i]) return false;
    }
    return true;
  }
};

#endif