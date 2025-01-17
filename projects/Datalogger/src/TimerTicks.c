/* Copyright 2017, Juan Esteban Alarcon, Juan Manuel Cruz
 * All rights reserved.
 *
 * This file is part of Workspace.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/** @brief These are the Timer Ticks functions for simple statechart example
 *  using Yakindu Statechart Tool Plug-in
 *  (update site: http://updates.yakindu.org/sct/mars/releases/).
 */

/** \addtogroup statechart Simple UML Statechart example.
 ** @{ */

//a TimerTicks.c le tengo que agregar el .h de mi maquina de estado en este caso Datalogger_SA.h
// y el propio "TimerTicks.h"

#include "..\gen\DataloggerSA5.h"
#include "TimerTicks.h"

void InitTimerTicks(TimerTicks *list, uint32_t len)
{
	uint32_t i;

	for(i = 0; i < len; i++) {
		list[i].evid = (sc_eventid)0;
		list[i].time_ms = 0;
		list[i].count = 0;
		list[i].periodic = false;
		list[i].active = false;
		list[i].evPending = false;
	}
}


sc_eventid SetNewTimerTick(TimerTicks *list, uint32_t len, sc_eventid evid, sc_uinteger time_ms, sc_boolean periodic)
{
	uint32_t i;

	sc_eventid ret = (sc_eventid)0;
	for(i = 0; i < len; i++) {
		if(!list[i].evid) {
			list[i].time_ms = time_ms;
			list[i].count = time_ms;
			list[i].evid = evid;
			list[i].periodic = periodic;
			list[i].active = true;
			list[i].evPending = false;
			ret = evid;
			break;
		}
	}
	return ret;
}


void* UnsetTimerTick(TimerTicks *list, uint32_t len, sc_eventid id)
{
	uint32_t i;
	sc_eventid ret = (sc_eventid)0;

	for(i = 0; i < len; i++) {
		if(list[i].evid == id) {
			list[i].evid = (sc_eventid)0;
			list[i].time_ms = 0;
			list[i].count = 0;
			list[i].periodic = false;
			list[i].active = false;
			list[i].evPending = false;
			ret = id;
			break;
		}
	}
	return ret;
}


sc_boolean IsPendEvent(TimerTicks *list, uint32_t len, sc_eventid id)
{
	int i;
	sc_boolean ret = false;
	for(i=0; i < len; i++) {
		if((list[i].evid == id) && (list[i].evPending == true)) {
			ret = true;
			break;
		}
	}
	return ret;
}


void MarkAsAttEvent(TimerTicks *list, uint32_t len, sc_eventid id)
{
	uint32_t i;

	for(i = 0; i < len; i++) {
		if(list[i].evid == id) {
			list[i].evPending = false;
			break;
		}
	}
}


void UpdateTimers(TimerTicks *list, uint32_t len)
{
	uint32_t i;

	for(i = 0; i < len; i++) {
		if(list[i].active == true) {
			if(list[i].count)
				list[i].count--;
			if(!list[i].count) {
				if(list[i].periodic)
					list[i].count = list[i].time_ms;
				else
					list[i].active = false;
				list[i].evPending = true;
			}
		}
	}
}
