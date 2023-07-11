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

#ifndef __EE_KWS_H
#define __EE_KWS_H

#include "ee_audiomark.h"
#include "ee_mfcc_f32.h"


/* TODO: Coalesce the massive amount of #defines! */

#define OUT_DIM            12
#define NUM_MFCC_FRAMES    49 /* 49 * 320 = 15.680e3 samples */
#define FEATURES_PER_FRAME NUM_MFCC_FEATURES

#define BYTES_PER_SAMPLE         2
#define BYTES_PER_FEATURE        1
#define SAMPLES_PER_CHUNK        64 /* 4ms is 64 samples @ 16 kHz */
#define CHUNKS_PER_INPUT_BUFFER  4  /* Incoming frame is 4 chunks (16ms) */
#define SAMPLES_PER_INPUT_BUFFER (CHUNKS_PER_INPUT_BUFFER * SAMPLES_PER_CHUNK)
#define CHUNKS_PER_MFCC_SLIDE    5 /* Outgoing is 5 chunks (20ms) */
#define SAMPLES_PER_OUTPUT_MFCC  (CHUNKS_PER_MFCC_SLIDE * SAMPLES_PER_CHUNK)
#define CHUNK_WATERMARK          10 /* Enough data in FIFO for an MFCC */
#define TOTAL_CHUNKS             13 /* Will never be more than this. */
/* CHUNK_WATERMARK = (CHUNKS_PER_MFCC_SLIDE * 2) */
/* TOTAL_CHUNKS = (CHUNK_WATERMARK + CHUNKS_PER_INPUT_BUFFER - 1) */
#define AUDIO_FIFO_SAMPLES (TOTAL_CHUNKS * SAMPLES_PER_CHUNK)


#endif // __EE_KWS_H
