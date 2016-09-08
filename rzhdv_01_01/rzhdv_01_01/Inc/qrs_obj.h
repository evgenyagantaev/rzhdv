/*
 * qrs_obj.h
 *
 *  Created on: Sep 8, 2016
 *      Author: root
 */

#ifndef INC_QRS_OBJ_H_
#define INC_QRS_OBJ_H_

#define WINDOW_LENGTH 33

#include "isoline.h"

// threshold values for r-pick detection
static const uint16_t AMPLITUDELEASTTHRESHOLD = 5000;
static const uint16_t AMPLITUDEMOSTTHRESHOLD = 15000;
static const uint16_t RLEASTLENGTH = 2;
static const uint16_t RMOSTLENGTH = 7;
// length of local window (piece of ecg sample buffer)
static const uint16_t QRSWINDOWLENGTH = 15;
// constants definitions for array of markers
static const uint16_t EMPTYMARKER = 0;
static const uint16_t WHITEMARKER = 1;
static const uint16_t REDMARKER = 2;
static const uint16_t BLUEMARKER = 3;
// heart rate buffers length
static const uint16_t REGULARANDQUARANTINEBUFFERLENGTH = 5;
// maximum appropriate deviation of heart rate from mean value of buffer
// (percents)
static const uint16_t MAXHEARTRATEDEVIATION = 10;
static const uint16_t QRSSUSPENDPERIOD = 60;



int32_t qrs_window[WINDOW_LENGTH];
int32_t markers[WINDOW_LENGTH];
static int qrs_new_sample_added_flag;

void qrs_add_new_sample(int32_t new_sample);
int qrs_get_new_sample_flag();
void qrs_set_new_sample_flag(int flag);

void qrs_shift_array(int32_t *array, int LENGTH);

#endif /* INC_QRS_OBJ_H_ */
