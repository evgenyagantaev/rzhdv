#include "timer250hz.h"


static inline void timer250hz_increment_tick()
{
    timer250hz_tick++;
}


void TIM3_IRQHandler(void)
{
    if((TIM3->SR & TIM_SR_UIF) != 0) // update interrupt pending flag
    {
        // clear flag
        TIM3->SR &= ~TIM_SR_UIF;

        timer250hz_increment_tick();
        //debug
        //HAL_GPIO_TogglePin(GPIOA, spi1_chipsel_Pin);
    }
}
