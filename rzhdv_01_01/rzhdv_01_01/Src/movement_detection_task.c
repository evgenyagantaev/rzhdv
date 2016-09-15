/*
 * movement_detection_task.c
 *
 *  Created on: Sep 14, 2016
 *      Author: root
 */
#include "movement_detection_task.h"
#include "movement_detector_obj.h"
#include "acc_data_buffer_obj.h"


void movement_detection_task()
{
	if(frozen_received_acc_samples_counter < acc_buffer_get_received_samples_counter())
	{
		movementDetection();
	}
}
