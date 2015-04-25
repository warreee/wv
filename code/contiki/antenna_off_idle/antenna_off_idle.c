
#include "contiki.h"
#include "net/netstack.h"
#include <avr/io.h>

/*---------------------------------------------------------------------------*/
PROCESS(antenna_off_idle_process, "antenna off, idle");
AUTOSTART_PROCESSES(&antenna_off_idle_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(antenna_off_idle_process, ev, data)
{

  static struct etimer et;

  PROCESS_BEGIN();

  // initialise pin
  DDRE |= _BV(PE6);
  
  NETSTACK_MAC.off(0); //mac off
  NETSTACK_RADIO.off(); //radios off
    
  while(1)
  {
    // Pin Flip
    PORTE ^= _BV(PE6);  
  
    etimer_set(&et, (CLOCK_SECOND * 2));

    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
  }



  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
