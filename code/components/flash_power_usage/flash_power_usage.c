/*  
    Component to measure the power usage of writing null bytes to flash memory.
*/

#include "contiki.h"
#include "looci.h"
#include "flash_power_usage.h"
#include "cfs/cfs.h"
#include <stdint.h>
#include <avr/pgmspace.h>
/* #include <avr/cpu/dev/flash.h> */
#include <avr/io.h>

#ifdef LOOCI_COMPONENT_DEBUG
#include "debug.h"
#else
#include "nodebug.h"
#endif

#define LOOCI_COMPONENT_NAME flash_power_usage

struct state {
};

COMPONENT_NO_INTERFACES();
COMPONENT_NO_RECEPTACLES();
#define LOOCI_NR_PROPERTIES 0
LOOCI_PROPERTIES();


LOOCI_COMPONENT("flash_power_usage",struct state);

#define MAX_WRITTEN_BYTES 65536
#define AMOUNT_OF_SAMPLES 20

static uint8_t activate(struct state* compState, void* data){

  
  // a buffer full of NULL bytes
  uint8_t buffer[1024]; 
  memset( (void *)&buffer, '\0', 1024);

  // file to be written
  char filename[] = "/null_file";
  

  // initialise pin
  DDRE |= _BV(PE6);

  // loop variables
  uint8_t i, n;
  uint32_t bytes_to_write;
  uint32_t written_bytes;
  uint32_t sampling_round;
  for (sampling_round = 0; sampling_round < AMOUNT_OF_SAMPLES; sampling_round++) {
    bytes_to_write = 1;
    written_bytes = 0;
    
    while (written_bytes < MAX_WRITTEN_BYTES) {
      if (written_bytes + bytes_to_write <= MAX_WRITTEN_BYTES) {
	// opening a file
	int fd_write = cfs_open(filename, CFS_WRITE);

	if (fd_write = -1) {
	  /* printf("ERROR: could not write to memory.\n"); */
	  return 0;
	}
	
	// compute the amount of iterations
	n = bytes_to_write / 1024;
	
	// flip pin
	PORTE ^= _BV(PE6);
	
	// write the necessary bytes
	for (i = 0; i <= n; i++) {
	  cfs_write(fd_write, &buffer, 1024);
	}
	
	// flip pin once more
	PORTE ^= _BV(PE6);
	
	// double counter
	bytes_to_write = bytes_to_write * 2;

	cfs_close(fd_write);
	cfs_remove(filename);
      } else {
	break;
      }
    }
  }
  
  return 1;
}

COMP_FUNCS_INIT
COMP_FUNC_ACTIVATE(activate)
COMP_FUNCS_END(NULL)
