
#include "contiki.h"
#include "net/netstack.h"
#include <avr/io.h>

/*---------------------------------------------------------------------------*/
PROCESS(idle_receiver_process, "antenna off, idle");
AUTOSTART_PROCESSES(&idle_receiver_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(idle_receiver_process, ev, data)
{

  PROCESS_BEGIN();

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
