/**
 * Copyright (C) 2024 SPEC Embedded Group
 * Copyright (C) 2022 EEMBC
 *
 * All EEMBC Benchmark Software are products of EEMBC and are provided under the
 * terms of the EEMBC Benchmark License Agreements. The EEMBC Benchmark Software
 * are proprietary intellectual properties of EEMBC and its Members and is
 * protected under all applicable laws, including all applicable copyright laws.
 *
 * If you received this EEMBC Benchmark Software without having a currently
 * effective EEMBC Benchmark License Agreement, you must discontinue use.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
extern "C" {
  #include "ee_audiomark.h"
}

#include "custom.h"
#include "GenericNodes.h"
#include "cg_status.h"
#include "AppNodes.h"

#define TEST_NBUFFERS 104U
#define NSAMPLES      256U
#define NFRAMEBYTES   512U

/* Noise to signal ratio */
#define NSRM50DB 0.003162f

extern "C" {
extern const int16_t p_input[TEST_NBUFFERS][NSAMPLES];
extern const int16_t p_expected[TEST_NBUFFERS][NSAMPLES];
}

static int16_t p_input_sub[NSAMPLES];
static int16_t p_output_sub[NSAMPLES];

static xdais_buffer_t xdais[1];

extern "C" {
// Used deep inside speex_alloc; assigned by component NODE_RESET
char *spxGlobalHeapPtr;
char *spxGlobalHeapEnd;
long  cumulatedMalloc;
}

int
main(int argc, char *argv[])
{
    bool      err           = false;
   
    uint32_t  A             = 0;
    uint32_t  B             = 0;
    float     ratio         = 0.0f;

  
    FIFO<int16_t,NSAMPLES,1,0> fifo5(p_input_sub);
    FIFO<int16_t,NSAMPLES,1,0> fifo6(p_output_sub);
    ANR<int16_t,NSAMPLES,
        int16_t,NSAMPLES> anr(fifo5,fifo6);

    for (int i = 0; i < TEST_NBUFFERS; ++i)
    {
        memcpy(p_input_sub, &p_input[i], NFRAMEBYTES);

        anr.run();

        A = 0;
        B = 0;

        for (unsigned j = 0; j < NSAMPLES; ++j)
        {
            A += abs(p_output_sub[j]);
            B += abs(p_output_sub[j] - p_expected[i][j]);

#ifdef DEBUG_EXACT_BITS
            if (p_output_sub[j] != p_expected[i][j])
            {
                err = true;
                printf("S[%03d]B[%03d]O[%-5d]E[%-5d] ... FAIL\n",
                       i,
                       j,
                       p_output_sub[j],
                       p_expected[i][j]);
            }
#endif
        }

        ratio = (float)B / (float)A;
        if (ratio > NSRM50DB)
        {
            err = true;
            printf("ANR FAIL: Frame #%d exceeded -50 dB Noise-to-Signal ratio\n", i);
        }
    }

    if (err)
    {
        printf("ANR test failed\n");
        return -1;
    }
    printf("ANR test passed\n");
    return 0;
}
