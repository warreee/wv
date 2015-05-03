#include "dev/sht11-sensor.h"

#include "contiki.h"
#include <avr/io.h>

/*---------------------------------------------------------------------------*/
PROCESS(antenna_on_idle_process, "antenna on, idle");
AUTOSTART_PROCESSES(&antenna_on_idle_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(antenna_on_idle_process, ev, data)
{
  PROCESS_BEGIN();
  static uint16_t avg;
  static uint16_t n;
  // initialise pin
  DDRE |= _BV(PE6);

  // flip pin
  /* PORTE ^= _BV(PE6); */

  //Pin hoog
  PORTE |= _BV(PE6);

  // pin low
  PORTE &= ~(_BV(PE6));

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
