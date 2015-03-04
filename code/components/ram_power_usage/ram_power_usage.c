#include "contiki.h"
#include "looci.h"
#include "ram_power_usage.h"
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

#define LOOCI_COMPONENT_NAME ram_power_usage

COMPONENT_NO_INTERFACES();
//COMPONENT_INTERFACES(APPLICATION_EVENT_TYPE);
COMPONENT_NO_RECEPTACLES();
//COMPONENT_RECEPTACLES(APPLICATION_EVENT_TYPE);
#define LOOCI_NR_PROPERTIES 0
//format = {propertyId, datatype,offset,size,name}
LOOCI_PROPERTIES();
LOOCI_COMPONENT("ram_power_usage",struct state);

#define MAX_BYTES_TO_WRITE 8192
#define AMOUNT_OF_SAMPLES 20

static uint8_t activate(struct state* compState, void* data){
  
  // a buffer full of NULL bytes
  uint8_t buffer[MAX_BYTES_TO_WRITE]; 

  // initialise pin
  DDRE |= _BV(PE6);

  // loop variables
  uint32_t bytes_to_write;
  uint32_t sampling_round;
  for (sampling_round = 0; sampling_round < AMOUNT_OF_SAMPLES; sampling_round++) {
    bytes_to_write = 1;
    
    while (bytes_to_write <= MAX_BYTES_TO_WRITE) {
      // flip pin
      PORTE ^= _BV(PE6);
	
      memset( (void *)&buffer, '\0', bytes_to_write);
	
      // flip pin back
      PORTE ^= _BV(PE6);
	
      // double counter
      bytes_to_write = bytes_to_write * 2;
    }
  }
  
  return 1;
}

COMP_FUNCS_INIT
COMP_FUNC_ACTIVATE(activate)
COMP_FUNCS_END(NULL)
