/*
 * ecg_ring_buffer_task.c
 *
 *  Created on: Sep 5, 2016
 *      Author: root
 */

#include "ecg_ring_buffer_task.h"
#include "ecg_ring_buffer.h"
#include "frame_ring_buffer.h"
#include "isoline.h"

void ecg_ring_buffer_task()
{
	char message[64];

	if(get_received_ecg_samples_counter() < get_received_frames_counter())
	{
		frame_ring_buffer_pop(local_frame_copy, ADAS_FRAME_LENGTH);
		uint32_t sample = local_frame_copy[1]&((uint32_t)0x00ffffff);
		ecg_ring_buffer_push(sample);
		isoline_add_new_sample(sample);

	}
}
