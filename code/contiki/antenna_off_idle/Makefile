CONTIKI_PROJECT = antenna_off_idle
# APPS+=powertrace

all: $(CONTIKI_PROJECT)

upload: 
	make all
	make $(CONTIKI_PROJECT).avr-zigduino.u

CONTIKI = $(LOOCI)/looci2-contiki-os/contiki-2.7/
include $(CONTIKI)/Makefile.include
