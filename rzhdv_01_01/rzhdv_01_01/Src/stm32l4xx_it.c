/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"
#include "stm32l4xx.h"
#include "stm32l4xx_it.h"
#include "cmsis_os.h"
#include "usart.h"

/* variables --------------------------------------------------------*/
extern PCD_HandleTypeDef hpcd;
extern TIM_HandleTypeDef htim4;

/******************************************************************************/
/*            Cortex-M4 Processor Interruption and Exception Handlers         */ 
/******************************************************************************/

/**
* @brief This function handles System tick timer.
*/
void SysTick_Handler(void)
{
  osSystickHandler();
}

/******************************************************************************/
/* STM32L4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32l4xx.s).                    */
/******************************************************************************/

/**
* @brief This function handles TIM4 global interrupt.
*/
void TIM4_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim4);
  //debug
  /*
  if((GPIOB->IDR & GPIO_PIN_0) == GPIO_PIN_RESET)
	GPIOB->BSRR = (uint32_t)GPIO_PIN_0;
  else
	GPIOB->BRR = (uint32_t)GPIO_PIN_0;
  //*/
}

/**
* @brief This function handles USB OTG FS global interrupt.
*/
void OTG_FS_IRQHandler(void)
{
  /* USER CODE BEGIN OTG_FS_IRQn 0 */

  /* USER CODE END OTG_FS_IRQn 0 */
  HAL_PCD_IRQHandler(&hpcd);
  /* USER CODE BEGIN OTG_FS_IRQn 1 */

  /* USER CODE END OTG_FS_IRQn 1 */
}

/* USER CODE BEGIN 1 */

void EXTI9_5_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(drdy_adas_exti9_Pin);
}

void my_default_handler(void)
{
	HAL_UART_Transmit(&huart1, "default irq handler\r\n", strlen("default irq handler\r\n"), 500);
}

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
