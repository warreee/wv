#include "dev/sht11-sensor.h"

#include "contiki.h"
#include <avr/io.h>

/*---------------------------------------------------------------------------*/
PROCESS(temp_naive_aggregator_process, "antenna on, idle");
AUTOSTART_PROCESSES(&temp_naive_aggregator_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(temp_naive_aggregator_process, ev, data)
{
  PROCESS_BEGIN();

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
