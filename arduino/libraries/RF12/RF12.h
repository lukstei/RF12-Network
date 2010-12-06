// RFM12B driver definitions
// 2009-02-09 <jcw@equi4.com> http://opensource.org/licenses/mit-license.php
// $Id: RF12.h 6019 2010-09-13 19:37:32Z jcw $

#ifndef RF12_h
#define RF12_h

#include <stdint.h>

// version 1 did not include the group code in the crc
// version 2 does include the group code in the crc
#define RF12_VERSION    1

#define rf12_data       (rf12_buf)
#define rf12_len        rf12_data[0]

#define RF12_MAXDATA    66

#define RF12_433MHZ     1
#define RF12_868MHZ     2
#define RF12_915MHZ     3

extern volatile uint16_t rf12_crc;  // running crc value, should be zero at end
extern volatile uint8_t rf12_buf[]; // recv/xmit buf including hdr & crc bytes

// call this once with the node ID, frequency band, and optional group
void rf12_initialize(uint8_t id, uint8_t band);

// call this frequently, returns true if a packet has been received
uint8_t rf12_recvDone(void);

// call this to check whether a new transmission can be started
// returns true when a new transmission may be started with rf12_sendStart()
uint8_t rf12_canSend(void);

// call this only when rf12_recvDone() or rf12_canSend() return true
void rf12_sendStart(void* ptr, uint8_t len);

// wait for send to finish, sleep mode: 0=none, 1=idle, 2=standby, 3=powerdown
void rf12_sendWait (uint8_t mode);

// this simulates OOK by turning the transmitter on and off via SPI commands
// use this only when the radio was initialized with a fake zero node ID
void rf12_onOff(uint8_t value);

// power off the RF12, ms > 0 sets watchdog to wake up again after N * 32 ms
// note: once off, calling this with -1 can be used to bring the RF12 back up
void rf12_sleep(char n);

// returns true of the supply voltage is below 3.1V
char rf12_lowbat(void);

// low-level control of the RFM12B via direct register access
uint16_t rf12_control(uint16_t cmd);

#endif
