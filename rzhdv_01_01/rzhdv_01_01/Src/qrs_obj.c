/*
 * qrs_obj.c
 *
 *  Created on: Sep 8, 2016
 *      Author: root
 */

#include "qrs_obj.h"

void qrs_add_new_sample(int32_t new_sample)
{
	qrs_shift_array(qrs_window, WINDOW_LENGTH);
	qrs_window[WINDOW_LENGTH-1] = new_sample;
	qrs_shift_array(markers, WINDOW_LENGTH);
	markers[WINDOW_LENGTH-1] = 0;

	qrs_new_sample_added_flag = 1;  // drop new sample flag


}



int qrs_get_new_sample_flag()
{
	return qrs_new_sample_added_flag;
}
void qrs_set_new_sample_flag(int flag)
{
	qrs_new_sample_added_flag = flag;
}

void qrs_shift_array(int32_t *array, int LENGTH)
{
	int i;
	for(i=0; i<(LENGTH-1); i++)
		array[i] = array[i+1];
}
