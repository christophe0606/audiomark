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

#ifdef OS_SUPPORT_CUSTOM
#ifdef FIXED_POINT
#define XPH_ANR_INSTANCE_SIZE 29000
#else
#define XPH_ANR_INSTANCE_SIZE 45250
#endif
// We manipulate these for each speex alloc based off our memory heaps
extern char *spxGlobalHeapPtr;
extern char *spxGlobalHeapEnd;
extern long  cumulatedMalloc;
#endif

static const uint32_t param_anr_f32[1][2] = {
    {
        256,   // FRAME SIZE
        16000, // SAMPLE RATE
    },
};

SpeexPreprocessState *ee_anr_init_f32(uint32_t *size)
{
            uint32_t              frame_size  = 0;
            uint32_t              sample_rate = 0;
            SpeexPreprocessState *p_state     = NULL;

            *size = XPH_ANR_INSTANCE_SIZE;

            p_state = (SpeexPreprocessState*)th_malloc(XPH_ANR_INSTANCE_SIZE, COMPONENT_AEC);

       
#ifdef OS_SUPPORT_CUSTOM
            // speex aligns memory during speex_alloc
            spxGlobalHeapPtr = (char *)(p_state);
            spxGlobalHeapEnd = spxGlobalHeapPtr + XPH_ANR_INSTANCE_SIZE;
#endif
            frame_size  = param_anr_f32[0][0];
            sample_rate = param_anr_f32[0][1];

            p_state = speex_preprocess_state_init(frame_size, sample_rate);
            speex_preprocess_ctl(p_state, SPEEX_PREPROCESS_SET_ECHO_STATE, 0);
            return(p_state);
}

