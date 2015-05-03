
#include "contiki.h"
#include "net/netstack.h"
#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/power.h>
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
  

  /* while(1) */
  /* { */
    // Pin Flip
  PORTE ^= _BV(PE6);  
  
  etimer_set(&et, (CLOCK_SECOND * 2));

  PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
  PORTE ^= _BV(PE6);  
  /* } */

  set_sleep_mode(SLEEP_MODE_PWR_SAVE);
  sleep_enable();  
  sleep_mode();

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/

