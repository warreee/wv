
#include "contiki.h"
#include "net/netstack.h"

/*---------------------------------------------------------------------------*/
PROCESS(antenna_on_idle_process, "antenna on, idle");
AUTOSTART_PROCESSES(&antenna_on_idle_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(antenna_on_idle_process, ev, data)
{
  static struct etimer et;
  
  PROCESS_BEGIN();

  // initialise pin
  DDRE |= _BV(PE6);
  
  uint32_t sampling_round;
  for (sampling_round = 0; sampling_round < AMOUNT_OF_SAMPLES; sampling_round++) {
    // flip pin
    PORTE ^= _BV(PE6);
  
    etimer_set(&et, (CLOCK_SECOND * 10));

    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
  
    // flip pin back
    PORTE ^= _BV(PE6);
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
