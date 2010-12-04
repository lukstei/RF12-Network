// Test encrypted communication, sender side
// 2010-02-21 <jcw@equi4.com> http://opensource.org/licenses/mit-license.php
// $Id: crypSend.pde 4833 2010-02-21 21:44:24Z jcw $

#include <RF12.h>
#include <Ports.h>

MilliTimer sendTimer;
byte sendSize;
char payload[] = "ABC 0123456789";

void setup () {
    rf12_initialize(0, RF12_868MHZ, 33);
}

void loop () {
    rf12_recvDone();
    if (rf12_canSend() && sendTimer.poll(1000)) {
        // send as broadcast, payload will be encrypted
        rf12_sendStart(0, payload, sendSize + 4);
        sendSize = (sendSize + 1) % 11;
    }
}
