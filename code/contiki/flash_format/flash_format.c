
#include "contiki.h"
#include "string.h"

#include "cfs.h"
#include "cfs-coffee.h"

/* #include <stdio.h> /\* For printf() *\/ */
#include <stdlib.h> /* For malloc */
/*---------------------------------------------------------------------------*/
PROCESS(flash_format_process, "CFS formatter");
AUTOSTART_PROCESSES(&flash_format_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(flash_format_process, ev, data)
{
  PROCESS_BEGIN();

  cfs_coffee_format();

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
