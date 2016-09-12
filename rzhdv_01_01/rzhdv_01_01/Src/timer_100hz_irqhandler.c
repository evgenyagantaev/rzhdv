/*
 * timer_100hz_irqhandler.c
 *
 *  Created on: Sep 12, 2016
 *      Author: root
 */

#include "timer_100hz_irqhandler.h"
#include "timer_100hz_obj.h"



void TIM2_IRQHandler(void)
{
    if((TIM2->SR & TIM_SR_UIF) != 0) // update interrupt pending flag
    {
        // clear flag
        TIM2->SR &= ~TIM_SR_UIF;

        timer100hz_increment_tick();
        //debug
		//*
		if((GPIOB->IDR & GPIO_PIN_0) == GPIO_PIN_RESET)
			GPIOB->BSRR = (uint32_t)GPIO_PIN_0;
		else
			GPIOB->BRR = (uint32_t)GPIO_PIN_0;
		//*/

		//*/
    }
}
