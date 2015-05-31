#include "contiki.h"
#include "string.h"
#include <avr/io.h>

#include <stdio.h> /* For printf() */
#include <stdlib.h> /* For malloc */
#include "net/netstack.h"
/*---------------------------------------------------------------------------*/
PROCESS(ram_power_usage_process, "RAM power usage meter");
AUTOSTART_PROCESSES(&ram_power_usage_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(ram_power_usage_process, ev, data)
{
  static struct etimer et;
  
  PROCESS_BEGIN();

#define MAX_BYTES_TO_WRITE 8192
  

  // initialise pin
  DDRE |= _BV(PE6);

  NETSTACK_MAC.off(0); //mac off
  NETSTACK_RADIO.off(); //radios off


  while (1) {
    /* Delay 2 seconds */
    etimer_set(&et, (CLOCK_SECOND * 2));

    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));

    while (1) {
      // a buffer ready to be written to
      uint8_t *buffer = (uint8_t * ) malloc(MAX_BYTES_TO_WRITE * sizeof(uint8_t));

      //Pin hoog
      PORTE |= _BV(PE6);

        memset( (void *)buffer, '\0', MAX_BYTES_TO_WRITE);

      //Pin laag
      PORTE &= ~(_BV(PE6));

      free(buffer);      

      etimer_set(&et, (CLOCK_SECOND * 0.01));

      PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));

    }
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
