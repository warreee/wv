
#include "contiki.h"
#include "net/netstack.h"

/* #include <stdio.h> /\* For print
/*---------------------------------------------------------------------------*/
PROCESS(antenna_off_idle_process, "antenna off, idle");
AUTOSTART_PROCESSES(&antenna_off_idle_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(antenna_off_idle_process, ev, data)
{
  PROCESS_BEGIN();

  NETSTACK_RADIO.off(); //radios off

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
