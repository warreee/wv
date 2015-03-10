#include "contiki.h"
#include "string.h"

#include "cfs.h"
#include "cfs-coffee.h"

/* #include <stdio.h> /\* For printf() *\/ */
#include <stdlib.h> /* For malloc */
/*---------------------------------------------------------------------------*/
PROCESS(flash_power_usage_process, "Flash memory power usage meter");
AUTOSTART_PROCESSES(&flash_power_usage_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(flash_power_usage_process, ev, data)
{
  PROCESS_BEGIN();

#define MAX_WRITTEN_BYTES 65536
#define AMOUNT_OF_SAMPLES 20
#define BUFFER_SIZE 1024
  
  // a buffer full of NULL bytes
  uint8_t *buffer = malloc(BUFFER_SIZE);
  
  memset( (void *) buffer, '\0', BUFFER_SIZE);

  // initialise pin
  DDRE |= _BV(PE6);

  // loop variables
  uint8_t i, n;
  uint32_t bytes_to_write;
  uint32_t written_bytes;
  uint32_t sampling_round;

  int fd_write = cfs_open("/null_file", CFS_WRITE);
      
  for (sampling_round = 0; sampling_round < AMOUNT_OF_SAMPLES; sampling_round++) {
    bytes_to_write = 1;
    written_bytes = 0;
    
    while (bytes_to_write < MAX_WRITTEN_BYTES) {
      // opening a file

      if (fd_write = -1) {
	/* printf("ERROR: could not write to memory.\n"); */
	return 0;
      }
	
      // compute the amount of iterations
      n = bytes_to_write / BUFFER_SIZE;
	
      // flip pin
      PORTE ^= _BV(PE6);
	
      cfs_seek(fd_write, 0,CFS_SEEK_SET);
      
      // write the necessary bytes
      for (i = 0; i <= n; i++) {
	cfs_write(fd_write, &buffer, BUFFER_SIZE);
      }
	
      // flip pin once more
      PORTE ^= _BV(PE6);
	
      // double counter
      bytes_to_write = bytes_to_write * 2;

    }
  }
  
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
