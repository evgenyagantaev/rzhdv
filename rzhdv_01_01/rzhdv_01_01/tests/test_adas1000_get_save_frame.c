// here is a unit's under test interface
#include "adas1000_get_save_frame.h"
#include "gpio.h"

#include "unity.h"

extern void setUp(void);
extern void tearDown(void);


void test_crc_calculation(void)
{
	uint32_t crc;

	const int preset_all_zeros = (uint32_t)0x00000000;
	const int preset_all_ones =  (uint32_t)0xffffffff;
	const int preset_all_zeroone = (uint32_t)0x55555555;

	uint32_t message00[16] = {0xff000000, 0xff000000};
	uint32_t message01[16] = {0xff111111, 0xff000000};
	uint32_t message02[16] = {0xff555555, 0xff000000};
	uint32_t message10[16] = {0xff000000, 0xff000000, 0xff000000};
	uint32_t message11[16] = {0xff111111, 0xff111111, 0xff000000};
	uint32_t message12[16] = {0xff555555, 0xff555555, 0xff000000};
	uint32_t message20[16] = {0xff000000, 0xff000000, 0xff000000, 0xff000000};
	uint32_t message21[16] = {0xff111111, 0xff111111, 0xff111111, 0xff000000};
	uint32_t message22[16] = {0xff555555, 0xff555555, 0xff555555, 0xff000000};

	crc = crc_calculation(message22, 12, CRC_POLYNOM, preset_all_zeros, preset_all_zeros);
	TEST_ASSERT_EQUAL_HEX32(preset_all_zeros, crc_calculation(message22, 12, CRC_POLYNOM, preset_all_zeros, crc));
	//*
	crc = crc_calculation(message22, 12, CRC_POLYNOM, preset_all_ones, preset_all_zeros);
	crc ^= 0xffffffff;
	crc &= 0x00ffffff;
	message22[3] = crc<<8;
	TEST_ASSERT_EQUAL_HEX32(CHECK_CONSTANT, crc_calculation(message22, 15, CRC_POLYNOM, preset_all_ones, preset_all_zeros));
    //*/

	crc = crc_calculation(message20, 12, CRC_POLYNOM, preset_all_zeros, preset_all_zeros);
	TEST_ASSERT_EQUAL_HEX32(preset_all_zeros, crc_calculation(message20, 12, CRC_POLYNOM, preset_all_zeros, crc));
	//*
    crc = crc_calculation((uint8_t *)message20, 12, CRC_POLYNOM, preset_all_ones, preset_all_zeros);
	crc ^= 0xffffffff;
	crc &= 0x00ffffff;
	message20[3] = crc<<8;
	TEST_ASSERT_EQUAL_HEX32(CHECK_CONSTANT, crc_calculation(message20, 15, CRC_POLYNOM, preset_all_ones, preset_all_zeros));
	//*/

	crc = crc_calculation(message21, 12, CRC_POLYNOM, preset_all_zeros, preset_all_zeros);
	TEST_ASSERT_EQUAL_HEX32(preset_all_zeros, crc_calculation(message21, 12, CRC_POLYNOM, preset_all_zeros, crc));
	//*
	crc = crc_calculation((uint8_t *)message21, 12, CRC_POLYNOM, preset_all_ones, preset_all_zeros);
	crc ^= 0xffffffff;
	crc &= 0x00ffffff;
	message21[3] = crc<<8;
	TEST_ASSERT_EQUAL_HEX32(CHECK_CONSTANT, crc_calculation(message21, 15, CRC_POLYNOM, preset_all_ones, preset_all_zeros));
    //*/
}



void test_read_frame(void)
{
	uint32_t frame_buffer[17];

	configure_adas1000();

    TEST_ASSERT_EQUAL(11, read_frame(frame_buffer));
    TEST_ASSERT_EQUAL(11, read_frame(frame_buffer));
    TEST_ASSERT_EQUAL(11, read_frame(frame_buffer));
    TEST_ASSERT_EQUAL_HEX32(ADDRESS1, frame_buffer[1]&((uint32_t)0xff000000));
    TEST_ASSERT_EQUAL_HEX32(ADDRESS2, frame_buffer[2]&((uint32_t)0xff000000));
    TEST_ASSERT_EQUAL_HEX32(ADDRESS3, frame_buffer[3]&((uint32_t)0xff000000));
    TEST_ASSERT_EQUAL_HEX32(ADDRESS4, frame_buffer[4]&((uint32_t)0xff000000));
    TEST_ASSERT_EQUAL_HEX32(ADDRESS5, frame_buffer[5]&((uint32_t)0xff000000));
    TEST_ASSERT_EQUAL_HEX32(ADDRESS6, frame_buffer[6]&((uint32_t)0xff000000));
    TEST_ASSERT_EQUAL_HEX32(ADDRESS7, frame_buffer[7]&((uint32_t)0xff000000));
    TEST_ASSERT_EQUAL_HEX32(ADDRESS8, frame_buffer[8]&((uint32_t)0xff000000));
    TEST_ASSERT_EQUAL_HEX32(ADDRESS9, frame_buffer[9]&((uint32_t)0xff000000));
    TEST_ASSERT_EQUAL_HEX32(ADDRESS10, frame_buffer[10]&((uint32_t)0xff000000));
    TEST_ASSERT_EQUAL_HEX32(ADDRESS11, frame_buffer[11]&((uint32_t)0xff000000));

}










