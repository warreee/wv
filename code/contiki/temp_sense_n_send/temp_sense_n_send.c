#include "contiki.h"
#include "dev/sht11.h"
#include <stdio.h>
#include "sensors.h"
#include "temperature-sensor.h"
/*---------------------------------------------------------------------------*/
PROCESS(temp_sense_n_send_process, "antenna on, idle");
AUTOSTART_PROCESSES(&temp_sense_n_send_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(temp_sense_n_send_process, ev, data)
{
  static struct etimer et;

  static uint8_t temps[100] = { 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17 };

  PROCESS_BEGIN();

  while (1) {

  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
