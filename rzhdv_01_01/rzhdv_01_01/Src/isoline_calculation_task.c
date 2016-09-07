/*
 * isoline_calculation_task.c
 *
 *  Created on: Sep 5, 2016
 *      Author: root
 */

#include <isoline.h>
#include "isoline_calculation_task.h"

//debug
#include "usart.h"
extern UART_HandleTypeDef huart1;


void isoline_calculation_task()
{
	//debug
	char message[64];  // remove when not debugging

	if(get_new_sample_flag())  // new sample added, and isoline is not recalculated yet
	{
		calculate_isoline_value();
		set_new_sample_flag(0); // drop flag

		// debug
		sprintf(message, "%dI%d\r\n", get_last_sample(), get_isoline_value());
		//sprintf(message, "%dI%d\r\n", get_isoline_value(), get_isoline_value());
		HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen(message), 500);  // for production board
		//debug
		//*
		if((GPIOB->IDR & GPIO_PIN_0) == GPIO_PIN_RESET)
			GPIOB->BSRR = (uint32_t)GPIO_PIN_0;
		else
			GPIOB->BRR = (uint32_t)GPIO_PIN_0;
		//*/
	}
}










