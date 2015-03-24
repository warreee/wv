
#include "contiki.h"
#include "net/netstack.h"
#include <avr/io.h>

/*---------------------------------------------------------------------------*/
PROCESS(antenna_off_idle_process, "antenna off, idle");
AUTOSTART_PROCESSES(&antenna_off_idle_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(antenna_off_idle_process, ev, data)
{
#define AMOUNT_OF_SAMPLES 20
  
  static struct etimer et;
  PROCESS_BEGIN();

  // initialise pin
  DDRE |= _BV(PE6);
  
  NETSTACK_MAC.off(0); //mac off
  NETSTACK_RADIO.off(); //radios off
    
  uint32_t sampling_round;
  for (sampling_round = 0; sampling_round < AMOUNT_OF_SAMPLES; sampling_round++) {
    // flip pin
    PORTE ^= _BV(PE6);
  
    etimer_set(&et, (CLOCK_SECOND * 0.5));

    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
  }

  // pin low
  PORTE &= ~(_BV(PE6));

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
