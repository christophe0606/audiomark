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
#include "speex_echo.h"

#ifdef OS_SUPPORT_CUSTOM
#ifdef FIXED_POINT
#define XPH_AEC_INSTANCE_SIZE 45000
#else
#define XPH_AEC_INSTANCE_SIZE 68100
#endif
// We manipulate these for each speex alloc based off our memory heaps
extern char *spxGlobalHeapPtr;
extern char *spxGlobalHeapEnd;
extern long  cumulatedMalloc;
#endif

static const uint32_t param_aec_f32[1][3] = {
    {
        256,   // FRAME SIZE
        1024,  // FILTER LENGTH
        16000, // SAMPLE RATE
    },
};

SpeexEchoState *ee_aec_init_f32(uint32_t *size)
{
        uint32_t        frame_size    = 0;
        uint32_t        filter_length = 0;
        uint32_t        sample_rate   = 0;
        SpeexEchoState *p_state       = NULL;

        p_state = (SpeexEchoState*)th_malloc(XPH_AEC_INSTANCE_SIZE, COMPONENT_AEC);

#ifdef OS_SUPPORT_CUSTOM
        // speex aligns memory during speex_alloc
        spxGlobalHeapPtr = (char *)(p_state);
        spxGlobalHeapEnd = spxGlobalHeapPtr + XPH_AEC_INSTANCE_SIZE;
#endif
        *size = XPH_AEC_INSTANCE_SIZE;
        
        frame_size    = param_aec_f32[0][0];
        filter_length = param_aec_f32[0][1];
        sample_rate   = param_aec_f32[0][2];

        p_state = speex_echo_state_init(frame_size, filter_length);
        speex_echo_ctl(p_state, SPEEX_ECHO_SET_SAMPLING_RATE, &sample_rate);
            
        return(p_state);
}

