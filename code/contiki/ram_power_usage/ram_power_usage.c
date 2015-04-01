#include "contiki.h"
#define DEBUG 0

#include "string.h"
#include <avr/io.h>

#ifdef DEBUG
#include <stdio.h> /* For printf() */
#endif

#include <stdlib.h> /* For malloc */
/*---------------------------------------------------------------------------*/
PROCESS(ram_power_usage_process, "RAM power usage meter");
AUTOSTART_PROCESSES(&ram_power_usage_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(ram_power_usage_process, ev, data)
{
  static struct etimer et;
  
  PROCESS_BEGIN();

#define MAX_BYTES_TO_WRITE 12240
#define AMOUNT_OF_SAMPLES 20

  // initialise pin
  DDRE |= _BV(PE6);

  // loop variables


  while (1) {
    /* Delay 2 seconds */
    //etimer_set(&et, (CLOCK_SECOND * 2));

    //PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
    
    /* uint32_t sampling_round; */
    /* for (sampling_round = 0; sampling_round < AMOUNT_OF_SAMPLES; sampling_round++) { */
    while (1) {
      // a buffer ready to be written to
      uint8_t *buffer = (uint8_t * ) malloc(MAX_BYTES_TO_WRITE * sizeof(uint8_t));
      
#ifdef DEBUG
      if (buffer == 0) {
	printf("ERROR: Out of memory\n");
	return 1;
      } else {
	printf("Success \n");
      }
#endif
      
      //Pin hoog
      PORTE |= _BV(PE6);

      //int i;
      //for (i = 0; i < 100; i++) {
        memset( (void *)buffer, '\0', MAX_BYTES_TO_WRITE);
      //}

      //Pin laag
      PORTE &= ~(_BV(PE6));

      free(buffer);      

      etimer_set(&et, (CLOCK_SECOND * 3));

      PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));

    }
  }
  
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
