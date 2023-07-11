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
#include "ee_abf_f32.h"
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
extern const int16_t p_channel1[TEST_NBUFFERS][NSAMPLES];
extern const int16_t p_channel2[TEST_NBUFFERS][NSAMPLES];
extern const int16_t p_expected[TEST_NBUFFERS][NSAMPLES];
}

static int16_t p_left[NSAMPLES];
static int16_t p_right[NSAMPLES];
static int16_t p_output[NSAMPLES];



int
main(int argc, char *argv[])
{
    bool      err           = false;
    uint32_t  A             = 0;
    uint32_t  B             = 0;
    float     ratio         = 0.0f;

    FIFO<int16_t,NSAMPLES,1,0> fifo2(p_left);
    FIFO<int16_t,NSAMPLES,1,0> fifo3(p_right);
    FIFO<int16_t,NSAMPLES,1,0> fifo4(p_output);
    ABF<int16_t,NSAMPLES,
        int16_t,NSAMPLES,
        int16_t,NSAMPLES> abf(fifo2,fifo3,fifo4);

    for (unsigned i = 0; i < TEST_NBUFFERS; ++i)
    {
        memcpy(p_left, &p_channel1[i], NFRAMEBYTES);
        memcpy(p_right, &p_channel2[i], NFRAMEBYTES);

        int errID = abf.run();

        if (errID!=0)
        {
            err = true;
            printf("ABF NODE_RUN failed\n");
            break;
        }

        A = 0;
        B = 0;

        for (unsigned j = 0; j < NSAMPLES; ++j)
        {
            A += abs(p_output[j]);
            B += abs(p_output[j] - p_expected[i][j]);

#ifdef DEBUG_EXACT_BITS
            if (p_output[j] == p_expected[i][j])
            {
                err = true;
                printf("S[%03d]B[%03d]L[%-5d]R[%-5d]O[%-5d]E[%-5d] ... FAIL\n",
                       i,
                       j,
                       p_left[j],
                       p_right[j],
                       p_output[j],
                       p_expected[i][j]);
            }
#endif
        }

        ratio = (float)B / (float)A;
        if (ratio > NSRM50DB)
        {
            err = true;
            printf("ABF FAIL: Frame #%d exceeded -50 dB Noise-to-Signal ratio\n", i);
        }
    }

    if (err)
    {
        printf("ABF test failed\n");
        return -1;
    }
    printf("ABF test passed\n");
    return 0;
}
