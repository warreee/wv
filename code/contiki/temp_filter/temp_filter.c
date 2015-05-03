#include "dev/sht11-sensor.h"

#include "contiki.h"
#include <avr/io.h>

/*---------------------------------------------------------------------------*/
PROCESS(temp_filter_process, "antenna on, idle");
AUTOSTART_PROCESSES(&temp_filter_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(temp_filter_process, ev, data)
{
#define AMOUNT_OF_SAMPLES 20
#define AMOUNT_TO_AVERAGE 
  static struct etimer et;
  uint8_t *buffer = malloc(sizeof(uint8_t) * AMOUNT_TO_AVERAGE);
  
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
