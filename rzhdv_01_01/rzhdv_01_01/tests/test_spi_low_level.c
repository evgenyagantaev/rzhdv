// here is a unit's under test interface
#include "spi_low_level.h"
#include "gpio.h"

#include "unity.h"

void setUp(void)
{
	// This is run before EACH TEST
	int i;
	i = 0;
}

void tearDown(void)
{
	// This is run after EACH TEST
	int i;
	i = 0;
}


void test_chipsel_high(void)
{
	/* All of these should pass */
	TEST_ASSERT_EQUAL_HEX32(spi1_chipsel_Pin, spi1_chipsel_Pin & chipsel_high());
}

void test_chipsel_low(void)
{
	/* All of these should pass */
	TEST_ASSERT_EQUAL_HEX32(spi1_chipsel_Pin, spi1_chipsel_Pin & (~chipsel_low()));
}

void test_write_2byte_word(void)
{
	/* All of these should pass */
	TEST_ASSERT_EQUAL_HEX32(0x5555, write_2byte_word(0x5555));
	TEST_ASSERT_EQUAL_HEX32(0x0000, write_2byte_word(0x0000));
	TEST_ASSERT_EQUAL_HEX32(0xffff, write_2byte_word(0xffff));
}


void test_write_4byte_word(void)
{
	/* All of these should pass */
	TEST_ASSERT_EQUAL_HEX32(0x55555555, write_4byte_word(0x55555555));
	TEST_ASSERT_EQUAL_HEX32(0x00000000, write_4byte_word(0x00000000));
	TEST_ASSERT_EQUAL_HEX32(0xffffffff, write_4byte_word(0xffffffff));
}






