#include "contiki.h"
#include "string.h"
#include "net/rime.h"
#include <avr/io.h>

#include <stdio.h> /* For printf() */
#include <stdlib.h> /* For malloc */
#include "net/netstack.h"
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

  // watch out with buffer size, the buffer has to be copied to the
  // packet buffer which by default has max size 128 bytes

#define BROADCAST_BUFFER_SIZE 64
#define NBPACKETS 64

  PROCESS_EXITHANDLER(broadcast_close(&broadcast);)

  PROCESS_BEGIN();
  NETSTACK_MAC.off(1); //mac off
  broadcast_open(&broadcast, 129, &broadcast_call);

  // initialise pin
  DDRE |= _BV(PE6);

  etimer_set(&et, (CLOCK_SECOND * 1));

  PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));

  uint8_t buffer[BROADCAST_BUFFER_SIZE];

  memset( (void *)buffer, '\0', BROADCAST_BUFFER_SIZE);

  while (1) {

    packetbuf_copyfrom((void *) buffer, BROADCAST_BUFFER_SIZE);
    int i = 0;
    //Pin hoog
    PORTE |= _BV(PE6);

    
    for (i = 0; i < NBPACKETS; i++) {
        if (broadcast_send(&broadcast) == 0) {
            printf("Whoopsie daisy");            
        }
    }    
    

    //Pin laag
    PORTE &= ~(_BV(PE6));

    // wait
    etimer_set(&et, (CLOCK_SECOND * 0.05));
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
  }


  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
