/*
 * qrs_detection_task.c
 *
 *  Created on: Sep 8, 2016
 *      Author: root
 */

#include "qrs_obj.h"
#include "qrs_detection_task.h"
#include "gpio.h"


void qrs_detection_task()
{
	if(qrs_get_new_sample_flag())
	{
		qrs_set_new_sample_flag(0);   // drop flag

		//debug
		//*
		if((GPIOB->IDR & GPIO_PIN_0) == GPIO_PIN_RESET)
			GPIOB->BSRR = (uint32_t)GPIO_PIN_0;
		else
			GPIOB->BRR = (uint32_t)GPIO_PIN_0;
		//*/

	}
}
