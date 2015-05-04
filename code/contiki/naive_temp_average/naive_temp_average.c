#include "dev/sht11-sensor.h"

#include "contiki.h"
#include <avr/io.h>
#include <stdio.h>
/*---------------------------------------------------------------------------*/
PROCESS(antenna_on_idle_process, "antenna on, idle");
AUTOSTART_PROCESSES(&antenna_on_idle_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(antenna_on_idle_process, ev, data)
{
#define AMOUNT_OF_SAMPLES 20

#define AMOUNT_TO_AVERAGE 5000
  static struct etimer et;
  static int avg;
  static uint8_t temps[AMOUNT_TO_AVERAGE];
  PROCESS_BEGIN();

  // initialise pin
  DDRE |= _BV(PE6);
    int i = 0;
    for (i = 0; i < AMOUNT_TO_AVERAGE; i++) {
      temps[i] = 16;
    }

  while (1) {
    // flip pin
    PORTE ^= _BV(PE6);
    int i = 0;
    for (i = 0; i < AMOUNT_TO_AVERAGE; i++) {
      avg = avg + temps[i];
    }

    avg = avg / AMOUNT_TO_AVERAGE;
    //printf("average: %d",avg);
    // pin low
    PORTE &= ~(_BV(PE6));
    etimer_set(&et, (CLOCK_SECOND * 0.01));

    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
  }
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
