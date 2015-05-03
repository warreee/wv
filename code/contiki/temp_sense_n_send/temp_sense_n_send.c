#include "contiki.h"
#include <avr/io.h>
#include "sensors.h"
#include "temperature-sensor.h"

/*---------------------------------------------------------------------------*/
PROCESS(temp_sense_n_send, "antenna on, idle");
AUTOSTART_PROCESSES(&temp_sense_n_send_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(temp_sense_n_send_process, ev, data)
{
  PROCESS_BEGIN();

  // Activate the sensor
  SENSORS_ACTIVATE(temp_sensor);
  // and wait until the value is available
  while(!temp_sensor.status(SENSORS_READY)) {
    PROCESS_WAIT_EVENT_UNTIL(ev == sensors_event && data == &temp_sensor);
  }
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
