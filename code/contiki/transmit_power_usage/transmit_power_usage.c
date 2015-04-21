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

  // watch out with buffer size, the buffer has to be copied to the
  // packet buffer which by default has max size 128 bytes

  
  NETSTACK_MAC.off(0); //mac off
  NETSTACK_RADIO.off(); //radios off
#define BROADCAST_BUFFER_SIZE 2

  PROCESS_EXITHANDLER(broadcast_close(&broadcast);)

  PROCESS_BEGIN();

  broadcast_open(&broadcast, 129, &broadcast_call);

  // initialise pin
  DDRE |= _BV(PE6);

  etimer_set(&et, (CLOCK_SECOND * 1));

  PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));

  uint8_t buffer[BROADCAST_BUFFER_SIZE];

  memset( (void *)buffer, '\0', BROADCAST_BUFFER_SIZE);

  while (1) {

    packetbuf_copyfrom((void *) buffer, BROADCAST_BUFFER_SIZE);

    //Pin hoog
    PORTE |= _BV(PE6);

    NETSTACK_RADIO.on(); //radios off
    broadcast_send(&broadcast);
    NETSTACK_RADIO.off(); //radios off

    //Pin laag
    PORTE &= ~(_BV(PE6));

    // wait
    etimer_set(&et, (CLOCK_SECOND * 0.1));
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
  }


  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
