// here is a unit's under test interface
#include "configure_adas1000.h"
#include "gpio.h"

#include "unity.h"

extern void setUp(void);
extern void tearDown(void);

void test_reset_adas1000(void)
{
	TEST_ASSERT_EQUAL_HEX32(reset_adas_Pin, reset_adas1000() & reset_adas_Pin);
}

void test_configure_register_reset(void)
{
    // check reset value
	TEST_ASSERT_EQUAL_HEX32((((uint32_t)FRMCTL_ADDRESS)<<24) | FRMCTL_RESET, read_control_register(FRMCTL_ADDRESS));
	TEST_ASSERT_EQUAL_HEX32((((uint32_t)ECGCTL_ADDRESS)<<24) | ECGCTL_RESET, read_control_register(ECGCTL_ADDRESS));
	TEST_ASSERT_EQUAL_HEX32((((uint32_t)LOFFCTL_ADDRESS)<<24) | LOFFCTL_RESET, read_control_register(LOFFCTL_ADDRESS));
	TEST_ASSERT_EQUAL_HEX32((((uint32_t)RESPCTL_ADDRESS)<<24) | RESPCTL_RESET, read_control_register(RESPCTL_ADDRESS));
}

void test_configure_register_write(void)
{
    // configure
	TEST_ASSERT_EQUAL_HEX32((((uint32_t)FRMCTL_ADDRESS)<<24) | FRMCTL_CONFIG, configure_register(FRMCTL_ADDRESS, FRMCTL_CONFIG));
	TEST_ASSERT_EQUAL_HEX32((((uint32_t)ECGCTL_ADDRESS)<<24) | ECGCTL_CONFIG, configure_register(ECGCTL_ADDRESS, ECGCTL_CONFIG));
	TEST_ASSERT_EQUAL_HEX32((((uint32_t)LOFFCTL_ADDRESS)<<24) | LOFFCTL_CONFIG, configure_register(LOFFCTL_ADDRESS, LOFFCTL_CONFIG));
	TEST_ASSERT_EQUAL_HEX32((((uint32_t)RESPCTL_ADDRESS)<<24) | RESPCTL_CONFIG, configure_register(RESPCTL_ADDRESS, RESPCTL_CONFIG));
}

void test_configure_register_configured(void)
{
    // check configured value
	TEST_ASSERT_EQUAL_HEX32((((uint32_t)FRMCTL_ADDRESS)<<24) | FRMCTL_CONFIG, read_control_register(FRMCTL_ADDRESS));
	TEST_ASSERT_EQUAL_HEX32((((uint32_t)ECGCTL_ADDRESS)<<24) | ECGCTL_CONFIG, read_control_register(ECGCTL_ADDRESS));
	TEST_ASSERT_EQUAL_HEX32((((uint32_t)LOFFCTL_ADDRESS)<<24) | LOFFCTL_CONFIG, read_control_register(LOFFCTL_ADDRESS));
	TEST_ASSERT_EQUAL_HEX32((((uint32_t)RESPCTL_ADDRESS)<<24) | RESPCTL_CONFIG, read_control_register(RESPCTL_ADDRESS));
}

void test_configure_adas1000(void)
{
	TEST_ASSERT_EQUAL_INT(4, configure_adas1000());
}





