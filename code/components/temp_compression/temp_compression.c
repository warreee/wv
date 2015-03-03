#include "contiki.h"
#include "looci.h"
#include "temp_compression.h"
#include <stdint.h>
#include <avr/pgmspace.h>

#ifdef LOOCI_COMPONENT_DEBUG
#include "debug.h"
#else
#include "nodebug.h"
#endif

#define APPLICATION_EVENT_TYPE 282

struct state{
};

#define LOOCI_COMPONENT_NAME temp_compression

COMPONENT_NO_INTERFACES();
//COMPONENT_INTERFACES(APPLICATION_EVENT_TYPE);
COMPONENT_NO_RECEPTACLES();
//COMPONENT_RECEPTACLES(APPLICATION_EVENT_TYPE);
#define LOOCI_NR_PROPERTIES 0
//format = {propertyId, datatype,offset,size,name}
LOOCI_PROPERTIES();
LOOCI_COMPONENT("temp_compression",struct state);

static uint8_t init(struct state* compState, void* data){
  return 1;
}

/*
 * Function called when etimer expires
 * Data contains the timer that expired
 */
static uint8_t time(struct state* compState, struct etimer* data){
  return 1;

}

static uint8_t event(struct state* compState, core_looci_event_t* event){
  //uint8_t test = 1;
  //PUBLISH_EVENT(APPLICATION_EVENT_TYPE,&test,sizeof(test));
  return 1;
}

COMP_FUNCS_INIT
COMP_FUNC_INIT(init)
     COMP_FUNC_TIMER(time)
     COMP_FUNC_EVENT(event)
     COMP_FUNCS_END(NULL)
