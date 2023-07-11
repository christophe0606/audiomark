/**
 * Copyright (C) 2022 EEMBC
 * Copyright (C) 2022 Arm Limited
 *
 * All EEMBC Benchmark Software are products of EEMBC and are provided under the
 * terms of the EEMBC Benchmark License Agreements. The EEMBC Benchmark Software
 * are proprietary intellectual properties of EEMBC and its Members and is
 * protected under all applicable laws, including all applicable copyright laws.
 *
 * If you received this EEMBC Benchmark Software without having a currently
 * effective EEMBC Benchmark License Agreement, you must discontinue use.
 */

#ifndef __EE_AUDIOMARK_H
#define __EE_AUDIOMARK_H

#include <stdint.h>
#include <stdlib.h>
#include "ee_kws.h"
#include "ee_mfcc_f32.h"
#include "ee_data/ee_data.h"

enum _component_req
{
    COMPONENT_BMF = 1,
    COMPONENT_AEC = 2,
    COMPONENT_ANR = 3,
    COMPONENT_KWS = 4,
};

#define SAMPLING_FREQ_HZ 16000
#define FRAME_LEN_SEC    0.016
#define MONO             1
#define BYTES_PER_SAMPLE 2 // int16
/* #define SAMPLES_PER_AUDIO_FRAME \
    (const int)(SAMPLING_FREQ_HZ * FRAME_LEN_SEC) */
#define SAMPLES_PER_AUDIO_FRAME 256
#define BYTES_PER_AUDIO_FRAME   (SAMPLES_PER_AUDIO_FRAME * BYTES_PER_SAMPLE)

int  ee_audiomark_initialize(bool);
int  ee_audiomark_run(int);
void ee_audiomark_release(void);

#endif
