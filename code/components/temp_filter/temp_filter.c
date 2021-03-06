#include "contiki.h"
#include "looci.h"
#include "event-types.h"

#define PREVIOUS_READING_PROP 40
#define THRESHOLD_PROP 41

struct state{
	uint8_t previous_reading;
	uint8_t threshold;
};

#define LOOCI_COMPONENT_NAME temp_filter
#define LOOCI_NR_PROPERTIES 2

LOOCI_PROPERTIES(
		{PREVIOUS_READING_PROP,DATATYPE_BYTE,offsetof(struct state, previous_reading),1,NULL},
		{THRESHOLD_PROP,DATATYPE_BYTE,offsetof(struct state, threshold),1,NULL}
	);
COMPONENT_INTERFACES( TEMP_READING);
COMPONENT_RECEPTACLES( TEMP_READING);
LOOCI_COMPONENT( "temp_filter",struct state);

static uint8_t init(struct state* compState, void* data){
  NETSTACK_MAC.off(0); //radios off
  compState->previous_reading = 0;
  compState->threshold = 0;
  return 1;
}

static uint8_t event(struct state* compState, core_looci_event_t* event){
  uint8_t temp = event->payload[0];
  if(event->type == TEMP_READING) {
    if(abs(temp - compState->previous_reading) >= compState->threshold) {
      // forward the event if it differs from the previous reading by more than the value of compState->threshold
      compState->previous_reading = *(event->payload);
      NETSTACK_MAC.on(); //radios on
      PUBLISH_EVENT(TEMP_READING, event->payload,event->len);
      NETSTACK_MAC.off(0); //radios off
    }
  }
  return 1;
}

COMP_FUNCS_INIT
COMP_FUNC_INIT(init)
COMP_FUNC_EVENT(event)
COMP_FUNCS_END(NULL)
