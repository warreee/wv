
#include "contiki.h"
#include "net/netstack.h"

/*---------------------------------------------------------------------------*/
PROCESS(antenna_on_idle_process, "antenna on, idle");
AUTOSTART_PROCESSES(&antenna_on_idle_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(antenna_on_idle_process, ev, data)
{
  PROCESS_BEGIN();

  /* NETSTACK_RADIO.on(); //radios on */

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
