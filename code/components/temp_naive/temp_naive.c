/**
LooCI Copyright (C) 2013 KU Leuven.
All rights reserved.

LooCI is an open-source software development kit for developing and maintaining networked embedded applications;
it is distributed under a dual-use software license model:

1. Non-commercial use:
Non-Profits, Academic Institutions, and Private Individuals can redistribute and/or modify LooCI code under the terms of the GNU General Public License version 3, as published by the Free Software Foundation
(http://www.gnu.org/licenses/gpl.html).

2. Commercial use:
In order to apply LooCI in commercial code, a dedicated software license must be negotiated with KU Leuven Research & Development.

Contact information:
  Administrative Contact: Sam Michiels, sam.michiels@cs.kuleuven.be
  Technical Contact:           Danny Hughes, danny.hughes@cs.kuleuven.be
Address:
  iMinds-DistriNet, KU Leuven
  Celestijnenlaan 200A - PB 2402,
  B-3001 Leuven,
  BELGIUM. 
 */
/*
 * Copyright (c) 2010, Katholieke Universiteit Leuven
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 *     * Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright notice,
 *       this list of conditions and the following disclaimer in the documentation
 *       and/or other materials provided with the distribution.
 *     * Neither the name of the Katholieke Universiteit Leuven nor the names of
 *       its contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "contiki.h"
#include "looci.h"
#include "temp_naive.h"
#include <stdint.h>
#include <avr/pgmspace.h>
#include "event-types.h"

#ifdef LOOCI_COMPONENT_DEBUG
#include "debug.h"
#else
#include "nodebug.h"
#endif

#define APPLICATION_EVENT_TYPE 282

struct state{
};

#define LOOCI_COMPONENT_NAME temp_naive

COMPONENT_INTERFACES( TEMP_READING);
COMPONENT_RECEPTACLES( TEMP_READING);
#define LOOCI_NR_PROPERTIES 0
//format = {propertyId, datatype,offset,size,name}
LOOCI_PROPERTIES();
LOOCI_COMPONENT("temp_naive",struct state);

static uint8_t event(struct state* compState, core_looci_event_t* event){
  uint8_t temp = event->payload[0];
  if(event->type == TEMP_READING) {
    // forward the event
    PUBLISH_EVENT(TEMP_READING, event->payload,event->len);
  }
  return 1;
}

//FUNCTION DECLARATION
// You can comment out unused functions
COMP_FUNCS_INIT //THIS LINE MUST BE PRESENT
/* COMP_FUNC_INIT(init) */
/* COMP_FUNC_DESTROY(destroy) */
/* COMP_FUNC_ACTIVATE(activate) */
/* COMP_FUNC_DEACTIVATE(deactivate) */
/* COMP_FUNC_TIMER(time) */
COMP_FUNC_EVENT(event)
/* COMP_FUNC_PROPERTY_IS_SET(propertySet) */
COMP_FUNCS_END(NULL)//THIS LINE MUST BE PRESENT
