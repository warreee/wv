#include "contiki.h"
#define DEBUG 0

#include "string.h"
#include <avr/io.h>

#ifdef DEBUG
#include <stdio.h> /* For printf() */
#endif
#include <stdlib.h> /* For malloc */
/*---------------------------------------------------------------------------*/
PROCESS(timed_ram_power_usage_process, "RAM power usage meter");
AUTOSTART_PROCESSES(&timed_ram_power_usage_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(timed_ram_power_usage_process, ev, data)
{
  static struct etimer et;
  
  PROCESS_BEGIN();

#define MIN_BYTES_TO_WRITE 512
#define MAX_BYTES_TO_WRITE 8192
#define AMOUNT_OF_SAMPLES 20

  // initialise pin
  DDRE |= _BV(PE6);

  // loop variables


  while (1) {
    /* Delay 2 seconds */
    etimer_set(&et, (CLOCK_SECOND * 5));

    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
    
    /* uint32_t sampling_round; */
    /* for (sampling_round = 0; sampling_round < AMOUNT_OF_SAMPLES; sampling_round++) { */
    while (1) {

      static int size;
      for (size = MIN_BYTES_TO_WRITE; size <= MAX_BYTES_TO_WRITE; size = size * 2) {

	
	static int i;
	for (i = 0; i < 10; i++) {
	  
	  // a buffer ready to be written to
	  uint8_t *buffer = (uint8_t * ) malloc(size * sizeof(uint8_t));

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
	  memset( (void *)buffer, '\0', size);
	  //Pin laag
	  PORTE &= ~(_BV(PE6));

	  
#ifdef DEBUG
	  printf("%d bytes written to RAM.", size);
#endif

	  free(buffer);
	
	  // wait between samples
	  etimer_set(&et, (CLOCK_SECOND * 1));

	  PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
	}

	// wait between experiments for different size
	etimer_set(&et, (CLOCK_SECOND * 20));

	PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
	
      }



    }
  }
  
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
