while (1) {
      uint8_t *buffer = (uint8_t * ) malloc(MAX_BYTES_TO_WRITE * sizeof(uint8_t));
      //Pin hoog
      PORTE |= _BV(PE6);
        memset( (void *)buffer, '\0', MAX_BYTES_TO_WRITE);
      //Pin laag
      PORTE &= ~(_BV(PE6));
      
      free(buffer);      
      etimer_set(&et, (CLOCK_SECOND * 0.01));
      PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
    }
