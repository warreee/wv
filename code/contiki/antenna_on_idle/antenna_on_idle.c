
#include "contiki.h"
#include "net/netstack.h"
#include <avr/io.h>

/*---------------------------------------------------------------------------*/
PROCESS(antenna_on_idle_process, "antenna on, idle");
AUTOSTART_PROCESSES(&antenna_on_idle_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(antenna_on_idle_process, ev, data)
{
#define AMOUNT_OF_SAMPLES 20
  static struct etimer et;
  
  PROCESS_BEGIN();

  // initialise pin
  DDRE |= _BV(PE6);
  
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

