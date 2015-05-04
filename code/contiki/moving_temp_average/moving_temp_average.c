#include "dev/sht11-sensor.h"

#include "contiki.h"
#include <avr/io.h>

/*---------------------------------------------------------------------------*/
PROCESS(antenna_on_idle_process, "antenna on, idle");
AUTOSTART_PROCESSES(&antenna_on_idle_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(antenna_on_idle_process, ev, data)
{
  static struct etimer et;

#define NUMBER_TO_AVERAGE 20
  
  static uint8_t avg = 0;
  static uint8_t n = 0; 
  static uint8_t fake_temp = 17;

  PROCESS_BEGIN();
  // initialise pin
  DDRE |= _BV(PE6);

  while (1) {

    //Pin hoog
    PORTE |= _BV(PE6);
    //pretend measurement
    if (n == 0) {
      avg = fake_temp;
    } else {
      avg = (avg * n + fake_temp) / (n + 1);
    }

    n++;

    if (n == NUMBER_TO_AVERAGE) {
      // send here, then reset this crap
      avg = 0;
      n = 0;
    }

    //Pin laag
    PORTE &= ~(_BV(PE6));
    etimer_set(&et, (CLOCK_SECOND * 0.5));

    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
