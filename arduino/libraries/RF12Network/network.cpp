#include "network.h"

unsigned short volatile rf12_crc;
volatile state_t state;

inline volatile state_t *get_state() {
  return &state;
}

bool message_is_for_me(net_packet_t *pkg) {
  //return true; // DEBUG

  if(get_state()->my_id == 0xFF)
    low_level_message(pkg);
  else 
    return pkg->receiver == ID_BC || pkg->receiver == get_state()->my_id;
}

inline bool low_level_message(net_packet_t *pkg) {
  return pkg->type == DID_REPLY && low_address_my_id((low_address_t*)&pkg->data);
}