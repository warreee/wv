#include "contiki.h"
#include "string.h"
#include "dev/radio.h"
#include <avr/io.h>

#include <stdio.h> /* For printf() */
#include <stdlib.h> /* For malloc */
/*---------------------------------------------------------------------------*/
PROCESS(transmit_power_usage_process, "TRANSMIT power usage meter");
AUTOSTART_PROCESSES(&transmit_power_usage_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(transmit_power_usage_process, ev, data)
{
  static struct etimer et;
  
  PROCESS_BEGIN();

  /* #define MAX_BYTES_TO_WRITE 2048 */
#define PACKET_SIZE 2
  
  // initialise pin
  DDRE |= _BV(PE6);

  etimer_set(&et, (CLOCK_SECOND * 1));

  PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
    
  uint8_t *buffer = (uint8_t * ) malloc(PACKET_SIZE * sizeof(uint8_t));

  memset( (void *)buffer, '\0', PACKET_SIZE);
      
  while (1) {
    prepare((void *) buffer, PACKET_SIZE);
      
    //Pin hoog
    PORTE |= _BV(PE6);

    transmit(PACKET_SIZE);

    //Pin laag
    PORTE &= ~(_BV(PE6));

    // wait
    etimer_set(&et, (CLOCK_SECOND * 0.1));
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
  }

  
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
