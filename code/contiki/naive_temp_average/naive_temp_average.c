#include "dev/sht11-sensor.h"

#include "contiki.h"
#include <avr/io.h>

/*---------------------------------------------------------------------------*/
PROCESS(antenna_on_idle_process, "antenna on, idle");
AUTOSTART_PROCESSES(&antenna_on_idle_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(antenna_on_idle_process, ev, data)
{
#define AMOUNT_OF_SAMPLES 20
#define AMOUNT_TO_AVERAGE 
  static struct etimer et;
  static uint8_t avg = 0;
  static uint8_t temps[20] = {16,15,16,16,15,16,17,18,18,18,18,17,16,16,17,17,17,17,17,17};

  PROCESS_BEGIN();

  // initialise pin
  DDRE |= _BV(PE6);

  while (1) {
    // flip pin
    PORTE ^= _BV(PE6);
    int i = 0;
    for (i = 0; i < 20; i++) {
      avg += temps[i];
    }

    avg = avg / 20;
    // pin low
    PORTE &= ~(_BV(PE6));
    etimer_set(&et, (CLOCK_SECOND * 0.5));

    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
  }
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
