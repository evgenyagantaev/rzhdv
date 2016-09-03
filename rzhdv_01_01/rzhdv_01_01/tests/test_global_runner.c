
/*=======Test Runner Used To Run Each Test Below=====*/
#define RUN_TEST(TestFunc, TestLineNum) \
{ \
  Unity.CurrentTestName = #TestFunc; \
  Unity.CurrentTestLineNumber = TestLineNum; \
  Unity.NumberOfTests++; \
  if (TEST_PROTECT()) \
  { \
      setUp(); \
      TestFunc(); \
  } \
  if (TEST_PROTECT() && !TEST_IS_IGNORED) \
  { \
    tearDown(); \
  } \
  UnityConcludeTest(); \
}


/* Includes ------------------------------------------------------------------*/
#include "main.h"

//#include "stm32l4xx.h"
#include "globals.h"
#include "stm32l4xx_hal.h"
#include "cmsis_os.h"
#include "adc.h"
#include "crc.h"
#include "iwdg.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"

#include "unity.h"
#include <setjmp.h>
#include <stdio.h>

#include "spi_low_level.h"
#include "configure_adas1000.h"
#include "adas1000_get_save_frame.h"
#include "timer250hz.h"
#include "frame_ring_buffer.h"
#include "ecg_ring_buffer.h"
#include "frame_ring_buffer_task.h"
#include "acc_data_read_task.h"
// here code to test
//#include "ProductionCode.h"

/* Private variables ---------------------------------------------------------*/

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi2;
USBD_HandleTypeDef USBD_Device;
extern PCD_HandleTypeDef hpcd;
extern USBD_DescriptorsTypeDef HID_Desc;

uint8_t InBuf[64];  // Память для буфера копии сообщений pCData->Report_buf ...

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
extern void MX_FREERTOS_Init(void);
/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
// here are test functions
extern void test_reset_adas1000(void);
extern void test_configure_register_reset(void);
extern void test_configure_register_write(void);
extern void test_configure_register_configured(void);
extern void test_configure_adas1000(void);

extern void test_chipsel_high(void);
extern void test_chipsel_low(void);
extern void test_write_2byte_word(void);
extern void test_write_4byte_word(void);

extern void test_crc_calculation(void);
extern void test_read_frame(void);

/*=======Test Reset Option=====*/
void resetTest(void);
void resetTest(void)
{
  tearDown();
  setUp();
}


/* Private function prototypes -----------------------------------------------*/


int main(void)
{

    /* MCU Configuration----------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* Configure the system clock */
    SystemClock_Config();

    /* Enable Power Clock*/
  __HAL_RCC_PWR_CLK_ENABLE();

    /* Enable USB power on Pwrctrl CR2 register */
    HAL_PWREx_EnableVddUSB();

    /* Initialize all configured peripherals */
    MX_GPIO_Init();

    /* Init Device Library */
    USBD_Init(&USBD_Device, &HID_Desc, 0);

    /* Add Supported Class */
    USBD_RegisterClass(&USBD_Device, USBD_HID_CLASS);

    /* Start Device Process */
    USBD_Start(&USBD_Device);

    // off both of leds
    HAL_GPIO_WritePin(GPIOA, red_led_odrain_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, green_led_odrain_Pin, GPIO_PIN_SET);

    MX_CRC_Init();
    MX_IWDG_Init();
    MX_SPI1_Init();
    MX_SPI2_Init();
    MX_TIM1_Init();
    MX_TIM2_Init();
    MX_TIM3_Init();
    MX_ADC1_Init();
    MX_USART1_UART_Init();
    MX_USART2_UART_Init();


    /* Call init function for freertos objects (in freertos.c) */
    //MX_FREERTOS_Init();

    // on green led
    HAL_GPIO_WritePin(GPIOA, green_led_odrain_Pin, GPIO_PIN_RESET);

    // adas reset high
    HAL_GPIO_WritePin(GPIOA, reset_adas_Pin, GPIO_PIN_SET);
    HAL_Delay(10);
    // adas reset low
	HAL_GPIO_WritePin(GPIOA, reset_adas_Pin, GPIO_PIN_RESET);
	HAL_Delay(10);
	// adas reset high
	HAL_GPIO_WritePin(GPIOA, reset_adas_Pin, GPIO_PIN_SET);
	HAL_Delay(10);
    // enable spi1
    SPI1->CR1 |= SPI_CR1_SPE;
    // enable spi1
    SPI2->CR1 |= SPI_CR1_SPE;
    /*
    configure_adas1000();
    HAL_Delay(3000);
    uint32_t data;
    while(1)
	{
		// read register 0x40 (frame header), initiate frame reading
		//synchronize();
        //write_4byte_word(((uint32_t)0x40) << 24);
        //data = read_4byte_word();
        data = read_control_register(0x40);
	}
	//*/

    // here are tests
    /*
    UnityBegin("test_spi_low_level.c");
    RUN_TEST(test_chipsel_high, 18);
    RUN_TEST(test_chipsel_low, 24);
    RUN_TEST(test_write_2byte_word, 30);
    RUN_TEST(test_write_4byte_word, 39);
    UnityEnd();
    //*/
    
    /*
    UnityBegin("test_configure_adas1000.c");
    RUN_TEST(test_reset_adas1000, 16);
    RUN_TEST(test_configure_register_reset, 21);
    RUN_TEST(test_configure_register_write, 30);
    RUN_TEST(test_configure_register_configured, 39);
    RUN_TEST(test_configure_adas1000, 48);
    UnityEnd();
    //*/
    
    /*
	UnityBegin("test_adas1000_get_save_frame.c");
	RUN_TEST(test_crc_calculation, 16);
	RUN_TEST(test_read_frame, 57);
	UnityEnd();
	//*/

	//*
    UnityBegin("test_frame_ring_buffer.c");
    RUN_TEST(test_frame_ring_buffer_initialization, 8);
    RUN_TEST(test_frame_ring_buffer_push, 13);
    RUN_TEST(test_frame_ring_buffer_pop, 36);
    UnityEnd();
    //*/

    //*
    UnityBegin("test_ecg_ring_buffer.c");
    RUN_TEST(test_ecg_ring_buffer_initialization, 9);
    RUN_TEST(test_ecg_ring_buffer_push, 14);
    RUN_TEST(test_ecg_ring_buffer_pop, 46);
    UnityEnd();
    //*/

	/* Run Application (Interrupt mode) */
    char message[64];
    int counter = 0;

    /*
    while (1)
    {
        sprintf(message, "c%dp%03dm%dv%03dG\r\n", counter%4, 75-3+(counter%7), counter%10, 80+(counter%6));
        USBD_HID_SendReport(&USBD_Device, message, strlen(message));
        HAL_GPIO_WritePin(GPIOA, green_led_odrain_Pin, GPIO_PIN_SET);
        HAL_Delay(1000);
        counter++;
        sprintf(message, "c%dp%03dm%dv%03dG\r\n", counter%4, 75-3+(counter%7), counter%10, 80+(counter%6));
        USBD_HID_SendReport(&USBD_Device, message, strlen(message));
        HAL_GPIO_WritePin(GPIOA, green_led_odrain_Pin, GPIO_PIN_RESET);
        HAL_Delay(1000);
        counter++;
    }
    //*/

	timer250hz_start();

	configure_adas1000();
    while(1)
    {
        //frame_ring_buffer_task();
		acc_data_read_task();
    }
    //return (UnityEnd());
}

//*
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;


  // Enable the LSE Oscilator
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  //* Enable the CSS interrupt in case LSE signal is corrupted or not present
  HAL_RCCEx_DisableLSECSS();

  //* Enable MSI Oscillator and activate PLL with MSI as source
  RCC_OscInitStruct.OscillatorType      = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState            = RCC_MSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIClockRange       = RCC_MSIRANGE_11;
  RCC_OscInitStruct.PLL.PLLState        = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource       = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM            = 6;
  RCC_OscInitStruct.PLL.PLLN            = 40;
  RCC_OscInitStruct.PLL.PLLP            = 7;
  RCC_OscInitStruct.PLL.PLLQ            = 4;
  RCC_OscInitStruct.PLL.PLLR            = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    //Error_Handler();
  }

  //* Enable MSI Auto-calibration through LSE
  HAL_RCCEx_EnableMSIPLLMode();

  // Select MSI output as USB clock source
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_MSI;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);

  // Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
  //clocks dividers
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    //Error_Handler();
  }
}
//*/

