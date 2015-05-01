
#include "contiki.h"
#include <stdio.h>
#include <avr/io.h>
#include "contiki-conf.h"
#include "dev/leds.h"
#include "sys/etimer.h"
#include "sys/process.h"




/*---------------------------------------------------------------------------*/
PROCESS(blink_process, "antenna on, idle");
AUTOSTART_PROCESSES(&blink_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(blink_process, ev, data)
{

  static struct etimer et;
  PROCESS_BEGIN();


  void leds_arch_init(void)
  {
    LED_PORT0 |= (1 << LED_PIN_0);
    LED_PORT_DIR0 |= (1 << LED_PIN_0);
    LED_PORT |= (1 << LED_PIN_1);
    LED_PORT_DIR |= (1 << LED_PIN_1);
    LED_PORT |= (1 << LED_PIN_2);
    LED_PORT_DIR |= (1 << LED_PIN_2);
  }
  void leds_arch_off(void)
  {
    LED_PORT0 &= ~(1 << LED_PIN_0);
    LED_PORT_DIR0 |= (1 << LED_PIN_0);
    LED_PORT &= ~(1 << LED_PIN_1);
    LED_PORT_DIR |= (1 << LED_PIN_1);
    LED_PORT &= ~(1 << LED_PIN_2);
    LED_PORT_DIR |= (1 << LED_PIN_2);
  }

  // initialise pin
  DDRE |= _BV(PE6);

  while(1)
  {
    // Pin Flip
    PORTE ^= _BV(PE6);  
    etimer_set(&et, (CLOCK_SECOND * 2));

    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/

