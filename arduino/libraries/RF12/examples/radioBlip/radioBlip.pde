// Send out a radio packet every minute, cusuming as little power as possible
// 2010-08-29 <jcw@equi4.com> http://opensource.org/licenses/mit-license.php
// $Id: radioBlip.pde 5994 2010-09-03 22:19:03Z jcw $

// all the low-power functions have been moved into the Ports library

#include <Ports.h>
#include <RF12.h>

static word payload;

EMPTY_INTERRUPT(WDT_vect); // just wakes us up to resume

void setup() {
    rf12_initialize(4, RF12_868MHZ, 5);
    rf12_sleep(0);
    
    // stay off approx 5 minutes after reset, to make sure that power is stable
    for (byte i = 0; i < 5; ++i)
        Sleepy::loseSomeTime(60000);
}

void loop() {
    ++payload;

    rf12_sleep(-1);
    
    while (!rf12_canSend())
        rf12_recvDone();
    
    // set the sync mode to 2 if the fuses are still the Arduino default
    // mode 3 (full powerdown) can only be used with 258 CK startup fuses
    rf12_sendStart(0, &payload, sizeof payload, 2); // low-power sync mode
    
    rf12_sleep(0);
    Sleepy::loseSomeTime(60000);
}
