CONTIKI_PROJECT = idle_receiver
APPS=servreg-hack
# APPS+=powertrace
all: $(CONTIKI_PROJECT)

upload: 
	make all
	make $(CONTIKI_PROJECT).avr-zigduino.u

WITH_UIP6=1
UIP_CONF_IPV6=1
CFLAGS+= -DUIP_CONF_IPV6_RPL
CONTIKI = $(LOOCI)/looci2-contiki-os/contiki-2.7
include $(CONTIKI)/Makefile.include
