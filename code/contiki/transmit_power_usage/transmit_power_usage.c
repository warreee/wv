#include "contiki.h"
#include "string.h"
#include "net/rime.h"
#include <avr/io.h>

#include <stdio.h> /* For printf() */
#include <stdlib.h> /* For malloc */
/*---------------------------------------------------------------------------*/
PROCESS(transmit_power_usage_process, "TRANSMIT power usage meter");
AUTOSTART_PROCESSES(&transmit_power_usage_process);
/*---------------------------------------------------------------------------*/
static void
broadcast_recv(struct broadcast_conn *c, const rimeaddr_t *from)
{
  printf("broadcast message received from %d.%d: '%s'\n",
         from->u8[0], from->u8[1], (char *)packetbuf_dataptr());
}
static const struct broadcast_callbacks broadcast_call = {broadcast_recv};
static struct broadcast_conn broadcast;
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(transmit_power_usage_process, ev, data)
{
  static struct etimer et;

  // watch out with packet size, this component does NOT allocate the
  // bytes to be sent on the heap, so watch out for overflow
#define PACKET_SIZE 2 
  
  PROCESS_EXITHANDLER(broadcast_close(&broadcast);)
    
  PROCESS_BEGIN();

  broadcast_open(&broadcast, 129, &broadcast_call);
  
  // initialise pin
  DDRE |= _BV(PE6);

  etimer_set(&et, (CLOCK_SECOND * 1));

  PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
    
  uint8_t buffer[PACKET_SIZE];

  memset( (void *)buffer, '\0', PACKET_SIZE);
      
  while (1) {
    // wait
    etimer_set(&et, (CLOCK_SECOND * 0.1));
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
    
    packetbuf_copyfrom((void *) buffer, PACKET_SIZE);
      
    //Pin hoog
    PORTE |= _BV(PE6);

    broadcast_send(&broadcast);
    
    //Pin laag
    PORTE &= ~(_BV(PE6));

  }

  
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
