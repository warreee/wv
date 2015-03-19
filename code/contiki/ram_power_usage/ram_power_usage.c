#include "contiki.h"
#include "string.h"
#include <avr/io.h>

#include <stdio.h> /* For printf() */
#include <stdlib.h> /* For malloc */
/*---------------------------------------------------------------------------*/
PROCESS(ram_power_usage_process, "RAM power usage meter");
AUTOSTART_PROCESSES(&ram_power_usage_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(ram_power_usage_process, ev, data)
{
  static struct etimer et;
  
  PROCESS_BEGIN();

#define MAX_BYTES_TO_WRITE 8192
#define AMOUNT_OF_SAMPLES 20
  

  // initialise pin
  DDRE |= _BV(PE6);

  // loop variables


  while (1) {
    /* Delay 2 seconds */
    etimer_set(&et, (CLOCK_SECOND * 2));

    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
    
    /* uint32_t sampling_round; */
    /* for (sampling_round = 0; sampling_round < AMOUNT_OF_SAMPLES; sampling_round++) { */
    while (1) {
      // a buffer ready to be written to
      uint8_t *buffer = malloc(MAX_BYTES_TO_WRITE);

      //Pin hoog
      PORTE |= _BV(PE6);

      int i;
      for (i = 0; i < 100; i++) {
        memset( (void *)buffer, '\0', MAX_BYTES_TO_WRITE);
      }

      //Pin laag
      PORTE &= ~(_BV(PE6));

      free(buffer);      

      etimer_set(&et, (CLOCK_SECOND * 1));

      PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));

    }
  }
  
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
