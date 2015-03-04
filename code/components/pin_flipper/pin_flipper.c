#include "component.h"
#include <stdlib.h>
#include <stddef.h>
#include "contiki.h"
#include "looci.h"
#include "utils.h"
#include <avr/pgmspace.h>
#include "pin_flipper.h"
#include "clock.h"

#ifdef CONTIKI_TARGET_AVR_RAVEN
#include "raven-msg.h"
#endif


#ifdef LOOCI_COMPONENT_DEBUG
#include "debug.h"
#else
#include "nodebug.h"
#endif

struct state{
  struct etimer et;
  uint8_t counter;
  uint8_t interval;
};

#define PROPERTY_ID_INTERVAL 101
#define LOOCI_COMPONENT_NAME pin_flipper

COMPONENT_NO_INTERFACES();
COMPONENT_NO_RECEPTACLES();


#define LOOCI_NR_PROPERTIES 1
LOOCI_PROPERTIES({PROPERTY_ID_INTERVAL,DATATYPE_BYTE,offsetof(struct state,interval),1,NULL});
static const struct state initVar PROGMEM = {.counter=1,.interval=1};
LOOCI_COMPONENT_INIT("pin_flipper",struct state,&initVar);

static uint8_t activate(struct state* compState, void* data){
  // initialise pin
  DDRE |= _BV(PE6);
  ETIMER_SET(&compState->et, CLOCK_SECOND * compState->interval);
  PRINT_LN("Pin ready");
  return 1;
}

static uint8_t time(struct state* compState, void* data){
  compState->counter += 1;
  
  if (compState->counter % 2 == 0) {
    PORTE |= _BV(PE6);
    PRINT_LN("Pin high");
  } else {
    PORTE &= ~(_BV(PE6));
    PRINT_LN("Pin low");
  }
	  
  ETIMER_RESET(&compState->et);
  return 1;
}

COMP_FUNCS_INIT
COMP_FUNC_ACTIVATE(activate)
COMP_FUNC_TIMER(time)
COMP_FUNCS_END(NULL)
