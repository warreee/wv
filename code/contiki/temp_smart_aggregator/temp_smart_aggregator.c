#include "dev/sht11-sensor.h"

#include "contiki.h"
#include <avr/io.h>
#include <stdlib.h>

/*---------------------------------------------------------------------------*/
PROCESS(temp_smart_aggregator_process, "antenna on, idle");
AUTOSTART_PROCESSES(&temp_smart_aggregator_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(temp_smart_aggregator_process, ev, data)
{

  static struct etimer et;
  static uint8_t temps[20] = {16,15,16,16,15,16,17,18,18,18,18,17,16,16,17,17,17,17,17,17};

  PROCESS_BEGIN();

  // initialise pin
  DDRE |= _BV(PE6);
  
  while (1) {
    //Pin hoog
    PORTE |= _BV(PE6);
    uint8_t *buffer = (uint8_t * ) malloc(10);
    int i; int j = 0;
    for (i = 0; i < 20; i++) {
      if (i == 0) {
        buffer[j++] = temps[i];
      } else {
        if (buffer[j] != temps[i]) {
          buffer[++j] = temps[i];
          if (j >= 10) {
            realloc((void *) buffer, j + 1);
          }
        }
      }
    }

    if (j < 10) {
      realloc((void *) buffer, j + 1);
    }
    //Pin laag
    PORTE &= ~(_BV(PE6));
    
    etimer_set(&et, (CLOCK_SECOND * 0.5));

    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
  }
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
