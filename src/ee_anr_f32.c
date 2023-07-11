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

#include "ee_audiomark.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "speex_preprocess.h"
#include "arch.h"


static const uint32_t param_anr_f32[1][2] = {
    {
        256,   // FRAME SIZE
        16000, // SAMPLE RATE
    },
};

void ee_anr_free_f32(SpeexPreprocessState *p)
{
  speex_preprocess_state_destroy(p);
}

SpeexPreprocessState *ee_anr_init_f32()
{
            uint32_t              frame_size  = 0;
            uint32_t              sample_rate = 0;
            SpeexPreprocessState *p_state     = NULL;


            frame_size  = param_anr_f32[0][0];
            sample_rate = param_anr_f32[0][1];

            p_state = speex_preprocess_state_init(frame_size, sample_rate);
            speex_preprocess_ctl(p_state, SPEEX_PREPROCESS_SET_ECHO_STATE, 0);
            return(p_state);
}

