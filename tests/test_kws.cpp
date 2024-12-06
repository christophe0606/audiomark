/**
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
#include "ee_types.h"
extern "C" {
#include "ee_audiomark.h"
}

#include "kws_test_custom.h"
#include "GenericNodes.h"
#include "cg_status.h"
#include "test_app_nodes.h"
#include "test_scheduler.h"


#define NBUFFERS 93
// Number of possible inference
// It must be a full number of iterations of
// the schedule and not reading more data than available
#define NINFERS  71
#define NSAMPLES 256
#define NCLASSES 12

extern "C" {
extern const int16_t p_input[NBUFFERS][NSAMPLES];
extern const int8_t  p_expected[NINFERS][NCLASSES];

int testError=0;

}


static int16_t        aec_output[256];     // 5
static int16_t        audio_fifo[13 * 64]; // 6
static int8_t         mfcc_fifo[490];      // 7
static int8_t         classes[12];         // 8

int
main(int argc, char *argv[])
{
    int           err           = 0;

    /* An iteration of the schedule loop is reading 5 buffers */
    err = init_test_scheduler(NBUFFERS/5,1,
                         (const int16_t*)p_input,
                         (const int8_t*)p_expected);

    if (err!=0)
    {
        printf("Init failed\n");
        exit(-1);
    }

    DSNN<int8_t,490,int8_t,12> *dsnn=dynamic_cast<DSNN<int8_t,490,int8_t,12>*>((NodeBase*)get_test_scheduler_node(DSNN_ID));

    
    if (dsnn==NULL)
    {
        printf("Can't access dsnn node\n");
        exit(-1);
    }

    uint32_t nbSched=test_scheduler(&err,
                              NBUFFERS/5,
                              1,
                              (const int16_t*)p_input,
                              (const int8_t*)p_expected);

   
    if (dsnn->getNbInferences() == 0)
    {
        err = 1;
        printf("KWS did not perform any inferences\n");
    }

    if (dsnn->getNbInferences() != NINFERS)
    {
        err = 1;
        printf("KWS expected %d inferences but got %d\n", NINFERS,dsnn->getNbInferences());
    }

    free_test_scheduler(NBUFFERS/5,1,
                   (const int16_t*)p_input,
                   (const int8_t*)p_expected);
    th_nn_free();

    if (err)
    {
        printf("KWS test failed\n");
        return -1;
    }

    printf("KWS test passed\n");
    return 0;
}