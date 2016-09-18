/*
 * diagnosics_task.c
 *
 *  Created on: Sep 18, 2016
 *      Author: root
 */

#include "diagnostics_task.h"
#include "timer_1hz_obj.h"
#include "heart_rate_obj.h"


// This task performs diagnostics
void diagnosticsTask(void *parameters)
{

	char statusString[STATUSSTRINGLENGTH];

	// debug ***
	char timestamp[32];
	// debug ***

	static int local_call_stack_pointer;

	if(frozen_seconds_counter < timer1hz_get_tick())
	{
		frozen_seconds_counter = timer1hz_get_tick();

		int current_heartrate = get_current_heartrate();

		if(current_heartrate != 444)
		{
			makeDiagnosis(current_heartrate,
			getWalkingStatus(), getRunningStatus(),
			getPosition());

		 if(current_heartrate <= 85)
			common.heartRateWeight = 1;
		 else
			common.heartRateWeight = (int)( 1.0 + 0.044*((double)(current_heartrate) - 85.0));

		 // подсчитываем интегральную чсс
		 long dI = (long)((double)current_heartrate * common.heartRateWeight);
		 common.heartRateIntegral += dI;
		}

		int motion = getPosition();

		// send status string via uart

		if(adcFault)
		{
		 // no correct data from ADC
		 sprintf(statusString, "c%dp%03dm%dv%03dG\r\n", 0,
				 777, motion, battery);
		}
		else if(adcAbnormal)
		{
		 adcAbnormal = 0;
		 // no correct data from ADC
		 sprintf(statusString, "c%dp%03dm%dv%03dG\r\n", 0,
				 555, motion, battery);
		}
		else if(diagnost.badAdcRange)
		{

		 //*
		 if(diagnost.getBadAdcRangeFlag() == 0) // 444 appear right now
		 {
			diagnost.setBadAdcRangeFlag();
			diagnost.setBadAdcRangeMarker(timer1hz_get_tick());

			sprintf(statusString, "c%dp%03dm%dv%03dG\r\n", diagnost.getStatus(),
			diagnost.getLastDisplayedPulse(), movementDetector.getPosition(),
			common.batteryCharge);
		 }
		 else // 444 appear in some moment in the past
		 {
			if((timer1hz_get_tick() - getBadAdcRangeMarker()) > 10 ) // 444 more then 10 seconds
			{
			   // adc input is out of range
			   sprintf(statusString, "c%dp%03dm%dv%03dG\r\n", 0,
					   444, motion, battery);
			   common.heartRate = 444;

			   //sprintf(debugstatus1, "Iso = %d\r\n", diagnost.badIsoline);
			   //xSemaphoreTake(uartMutex, portMAX_DELAY);
			   //uart.sendMessage(debugstatus1);
			   //xSemaphoreGive(uartMutex);
			   //vTaskDelay(delay10);
			}
			else // 444 less then 10 seconds
			{
			   sprintf(statusString, "c%dp%03dm%dv%03dG\r\n", getStatus(),
			   getLastDisplayedPulse(), getPosition(),
			   common.batteryCharge);
			}
		 }
		 //*/


		}
		else if(current_heartrate > 205)
		{
		 // high noice in data
		 if(getLastDisplayedPulse() == 444) // no normal pulse yet
		 {
			sprintf(statusString, "c%dp%03dm%dv%03dG\r\n", 0,
					444, motion, battery);
		 }
		 else
		 {
			sprintf(statusString, "c%dp%03dm%dv%03dG\r\n", 0,
					333, motion, battery);
		 }
		}
		else if(isolineController.currentIsoline == 32768)    // no patient
		{
		  sprintf(statusString, "c%dp%03dm%dv%03dG\r\n", 0,
					444, motion, battery);
		}
		else
		{
		 // everything ok
		 resetBadAdcRangeFlag();

		 if(current_heartrate != 444)
		 {

			//////////////////////////////////////////////////////////////////////////
			// DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG
			//make_hard_fault();
			// DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG



			setLastDisplayedPulse(current_heartrate);
		#ifndef WIDEDIAGNOSIS
			// print classic form of status string
			sprintf(statusString, "c%dp%03dm%dv%03dG\r\n", getStatus(),
					current_heartrate, getPosition(),
			   common.batteryCharge);
		#else
			// print form of status string with Bayevsky tension index and hr integral
			common.movement = movementDetector.getPosition();
			sprintf(statusString, "c%dp%03dm%dv%03db%03di%08ldG\r\n", diagnost.getStatus(),
			   common.heartRate, movementDetector.getPosition(),
			   common.batteryCharge, (int)(rrHistogramm.getTensionIndex()), common.heartRateIntegral);


		#endif
		 }
		 else
		 {
			sprintf(statusString, "c%dp%03dm%dv%03dG\r\n", 0,
			   444, getPosition(),
			   common.batteryCharge);
		 }
		 //sprintf(statusString, "c%dp%03dm%dv%03db%dG\r\n", diagnost.getStatus(),
			//common.heartRate, movementDetector.getPosition(),
			//common.batteryCharge, (int)(rrHistogramm.getTensionIndex()));

		 // debug recreation curve
		 //sprintf(statusString, "c%dp%03dm%dv%03dG\r\n", diagnost.getStatus(),
			//ecgAnalizer.getHeartRate(), movementDetector.getPosition(),
			//diagnost.getTachiThreshold());
		}

		//output diagnosys
		long interval = getInterval();
		if((timer1hz_get_tick()%interval) == 0)
		{
		  // clip timestamp to status
		  //strncpy(timestamp, rtc.getTimeStamp(), 32);
		  //int statusLen = strlen(statusString);
		  //strncpy(statusString + statusLen - 2, "   ", 3);
		  //strncpy(statusString + statusLen + 1, timestamp, 32);


		 xSemaphoreTake(sdioMutex, portMAX_DELAY);
		 if(!common.commandMode) sdio.writeStringToBuffer(statusString);
		 xSemaphoreGive(sdioMutex);

		 if(common.sendStatus)
		 {

			 //strcat(statusString, timestamp);
			 // debug RTC
			 /*
			 if(common.lse_start_ok)  // lse startoval ok
				strcat(statusString, "LSE OK\r\n");
			 else
				strcat(statusString, "LSE BAD\r\n");

			 if(RCC_GetFlagStatus(RCC_FLAG_LSERDY) != RESET)  // current lse ok
				strcat(statusString, "Current LSE OK\r\n");
			 else
				strcat(statusString, "Current LSE BAD\r\n");

			 if(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) != RESET)  // current lsi ok
				strcat(statusString, "Current LSI OK\r\n");
			 else
				strcat(statusString, "Current LSI BAD\r\n");
			 //*/

			xSemaphoreTake(uartMutex, portMAX_DELAY);
			uart.sendMessage(statusString);
			//debug ***
			//sprintf(debugstatus1, "^^^^^^^^^%ld^^^^%ld\r\n", timer1hz_get_tick(), interval);
			//uart.sendMessage(debugstatus1);
			//debug ***
			//debug ***
			/*
			rrvectorString[0] = 0;
			for(int i=128; i >= 1; i--)
			{
			   sprintf(rrString, "%d ", bayevsky.getRRbyIndex(600 - i));
			   strcat(rrvectorString, rrString);
			}
			sprintf(rrString, "\r\n");
			strcat(rrvectorString, rrString);

			uart.sendMessage(rrvectorString);
			//*/
			//debug ***
			xSemaphoreGive(uartMutex);
			//printf("%s", statusString);
		 }
		}
		//debug************
		/*
		else
		{
		 sprintf(debugstatus2, "**********%ld****%ld\r\n", timer1hz_get_tick(), interval);
		 xSemaphoreTake(uartMutex, portMAX_DELAY);
		 uart.sendMessage(debugstatus2);
		 xSemaphoreGive(uartMutex);
		}
		//*/
	}// end if(frozen_seconds_counter < acc_buffer_get_received_samples_counter())

}










