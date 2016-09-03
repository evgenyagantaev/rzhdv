/*
 * acc_data_read_task.c
 *
 *  Created on: Sep 2, 2016
 *      Author: root
 */

#include "acc_data_read_task.h"
#include "smb380.h"
#include "stdint.h"

//debug
#include "acc_spi_low_level.h"

void acc_data_read_task()
{
	//debug
	uint8_t accelerometer_data[16];

	smb380_read_xyz_rawdata(accelerometer_data);

	//debug
	//acc_spi_write_2byte_word(0x55);
}





