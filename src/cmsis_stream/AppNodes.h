/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        AppNodes.h
 * Description:  Application nodes for Example 1
 *
 * Target Processor: Cortex-M and Cortex-A cores
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2021-2023 ARM Limited or its affiliates. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef _APPNODES_H_
#define _APPNODES_H_

extern "C" {
#include "ee_audiomark.h"
#include "ee_abf_f32.h"
#include "ee_kws.h"
#include "ee_mfcc_f32.h"
}

#include "SlidingBuffer.h"

/* Used in tests */
int inferences = 0;


template<typename OUT,int outputSize>
class Source: GenericSource<OUT,outputSize>
{
public:
    Source(FIFOBase<OUT> &dst,const OUT *source):
    GenericSource<OUT,outputSize>(dst),mSource(source){
        mIndex=0;
    };

    int prepareForRunning() final
    {
        if (this->willOverflow()
           )
        {
           return(CG_SKIP_EXECUTION_ID_CODE); // Skip execution
        }

        return(0);
    };

    int run() final{
        OUT *b=this->getWriteBuffer();

        
        memcpy(b,mSource+mIndex,sizeof(OUT)*outputSize);
        mIndex += outputSize;
        if (mIndex >= NINPUT_SAMPLES)
        {
            mIndex = 0;
        }

        
        return(CG_SUCCESS);
    };

protected:
    const OUT *mSource;
    int mIndex;
};

extern "C" {
    extern void beamformer_f32_reset(abf_f32_instance_t *p_inst);
    extern void beamformer_f32_run(abf_f32_instance_t *p_inst,
                            int16_t            *input_buffer_left,
                            int16_t            *input_buffer_right,
                            int32_t             input_buffer_size,
                            int16_t            *output_buffer,
                            int32_t            *input_samples_consumed,
                            int32_t            *output_samples_produced,
                            int32_t            *returned_state);
}

template<typename IN1, int inputSize1,
         typename IN2, int inputSize2,
         typename OUT,int outputSize>
class ABF;

template<int nbSamples>
class ABF<int16_t,nbSamples,
          int16_t,nbSamples,
          int16_t,nbSamples>: public GenericNode21<int16_t,nbSamples,
                                                   int16_t,nbSamples,
                                                   int16_t,nbSamples>
{
public:
    ABF(FIFOBase<int16_t> &src1,
        FIFOBase<int16_t> &src2,
        FIFOBase<int16_t> &dst):
    GenericNode21<int16_t,nbSamples,
                int16_t,nbSamples,
                int16_t,nbSamples>(src1,src2,dst){
    

       p_abf_f32_instance = ee_abf_f32_init();

       //printf(" bmf = %d\n", size);

       beamformer_f32_reset(p_abf_f32_instance);
    };

    ~ABF()
    {
        ee_abf_f32_free(p_abf_f32_instance);
    }

   
    int prepareForRunning() final
    {
        if (this->willOverflow() ||
            this->willUnderflow1() ||
            this->willUnderflow2() 
           )
        {
           return(CG_SKIP_EXECUTION_ID_CODE); // Skip execution
        }

        return(0);
    };
    
    int run() final{
        int32_t ret = 0;

        int16_t *inBufs1stChannel=this->getReadBuffer1();
        int16_t *inBufs2ndChannel=this->getReadBuffer2();
        int16_t *outBufs=this->getWriteBuffer();

        int32_t  input_samples_consumed;
        int32_t  output_samples_produced;

        beamformer_f32_run(p_abf_f32_instance,
                           inBufs1stChannel,
                           inBufs2ndChannel,
                           nbSamples,
                           outBufs,
                           &input_samples_consumed,
                           &output_samples_produced,
                           &ret);
        return(ret);
    };

protected:
    abf_f32_instance_t *p_abf_f32_instance;

};

extern "C" {
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "speex_preprocess.h"
#include "arch.h"
#include "speex_echo.h"

    extern SpeexEchoState *ee_aec_init_f32();
    extern void ee_aec_free_f32(SpeexEchoState *);
}



template<typename IN1, int inputSize1,
         typename IN2, int inputSize2,
         typename OUT, int outputSize>
class AEC;

template<int nbSamples>
class AEC<int16_t,nbSamples,
          int16_t,nbSamples,
          int16_t,nbSamples>: public GenericNode21<int16_t,nbSamples,
                                                   int16_t,nbSamples,
                                                   int16_t,nbSamples>
{
public:
    AEC(FIFOBase<int16_t> &src1,
        FIFOBase<int16_t> &src2,
        FIFOBase<int16_t> &dst):
    GenericNode21<int16_t,nbSamples,
                int16_t,nbSamples,
                int16_t,nbSamples>(src1,src2,dst){
    
     
      p_state = ee_aec_init_f32();

      //printf(" aec = %d\n", size);
    };

    ~AEC()
    {
        ee_aec_free_f32(p_state);
    }

   
    int prepareForRunning() final
    {
        if (this->willOverflow() ||
            this->willUnderflow1() ||
            this->willUnderflow2() 
           )
        {
           return(CG_SKIP_EXECUTION_ID_CODE); // Skip execution
        }

        return(0);
    };
    
    int run() final{
        int32_t ret = 0;

        int16_t *reference=this->getReadBuffer1();
        int16_t *echo=this->getReadBuffer2();
        int16_t *outBufs=this->getWriteBuffer();

        speex_echo_cancellation(p_state, reference, echo, outBufs);

        return(ret);
    };

protected:
    SpeexEchoState *p_state;

};

extern "C" {
    extern SpeexPreprocessState *ee_anr_init_f32();
    extern void ee_anr_free_f32(SpeexPreprocessState *p);


}

template<typename IN, int inputSize,
         typename OUT,int outputSize>
class ANR;

template<int nbSamples>
class ANR<int16_t,nbSamples,
          int16_t,nbSamples>: public GenericNode<int16_t,nbSamples,
                                                 int16_t,nbSamples>
{
public:
    ANR(FIFOBase<int16_t> &src,
        FIFOBase<int16_t> &dst):
    GenericNode<int16_t,nbSamples,
                int16_t,nbSamples>(src,dst){
    
     
      p_state = ee_anr_init_f32();

      //printf(" anr = %d\n", size);
    };

    ~ANR()
    {
        ee_anr_free_f32(p_state);
    }

   
    int prepareForRunning() final
    {
        if (this->willOverflow() ||
            this->willUnderflow()
           )
        {
           return(CG_SKIP_EXECUTION_ID_CODE); // Skip execution
        }

        return(0);
    };
    
    int run() final{
        int32_t ret = 0;

        int16_t *in=this->getReadBuffer();
        int16_t *p_in_place_buffer=this->getWriteBuffer();

        memcpy(p_in_place_buffer,in,sizeof(int16_t)*nbSamples);

        speex_preprocess_run(p_state, p_in_place_buffer);

        return(ret);
    };

protected:
    SpeexPreprocessState *p_state;

};

template<typename IN, int inputSize,
         typename OUT,int outputSize>
class MFCC;

template<int inputSize, int outputSize>
class MFCC<int16_t,inputSize,
          int8_t,outputSize>: public GenericNode<int16_t,inputSize,
                                                 int8_t,outputSize>
{
public:
    MFCC(FIFOBase<int16_t> &src,
        FIFOBase<int8_t> &dst,int testMode=0):
    GenericNode<int16_t,inputSize,
                int8_t,outputSize>(src,dst),mTestMode(testMode){
    
     
    ee_status_t status = ee_mfcc_f32_init(&p_mfcc);
    nbMfccRun=0;
    };

   
   
    int prepareForRunning() final
    {
        if (this->willOverflow() ||
            this->willUnderflow()
           )
        {
           return(CG_SKIP_EXECUTION_ID_CODE); // Skip execution
        }

        return(0);
    };
    
    int run() final{
        
        int16_t *in=this->getReadBuffer();
        int8_t *out=this->getWriteBuffer();

        // In test mode, first iteration is doing nothing.
        // We are just filling the sliding audio buffer
        if ((!mTestMode) || (nbMfccRun>=1))
        {
           ee_mfcc_f32_compute(&p_mfcc,in,out);
        }

        
        nbMfccRun++;

        return(0);
    };

protected:
mfcc_instance_t p_mfcc;
int mTestMode;
int nbMfccRun;
};

template<typename IN, int inputSize,
         typename OUT, int outputSize>
class DSNN;

template<int inputSize>
class DSNN<int8_t,inputSize,
           int8_t,OUT_DIM>: 
public GenericNode<int8_t, inputSize,
                   int8_t,OUT_DIM>
{
public:
    DSNN(FIFOBase<int8_t> &src,FIFOBase<int8_t> &dst,int testMode=0):
    GenericNode<int8_t,inputSize,
                int8_t,OUT_DIM>(src,dst),mTestMode(testMode){
        th_nn_init();
        //printf(" kws = %d\n", 0);
        nbNNRun = 0;

    };

    int prepareForRunning() final
    {
        if (this->willUnderflow() || 
            this->willOverflow()
           )
        {
           return(CG_SKIP_EXECUTION_ID_CODE); // Skip execution
        }

        return(0);
    };

    int run () final
    {
        int8_t *p_mfcc_fifo=this->getReadBuffer();
        int8_t *prediction=this->getWriteBuffer();

        if ((!mTestMode) || (nbNNRun>=1))
        {
          ee_status_t status = th_nn_classify(p_mfcc_fifo, prediction);
          inferences ++;

        }

    
        nbNNRun++;

        return(0);
    };
protected:
    int mTestMode;
    int nbNNRun;
};


template<typename IN, int inputSize>
class Result;

template<>
class Result<int8_t,OUT_DIM>: 
public GenericSink<int8_t,OUT_DIM>
{
public:
    Result(FIFOBase<int8_t> &src):
    GenericSink<int8_t,OUT_DIM>(src){
    
     
    };

   
   
    int prepareForRunning() final
    {
        if (this->willUnderflow())
        {
           return(CG_SKIP_EXECUTION_ID_CODE); // Skip execution
        }

        return(0);
    };
    
    int run() final{
        
        int8_t *p_prediction=this->getReadBuffer();

#ifdef DEBUG_PRINTF_CLASSES
        printf("OUTPUT: ");
        char output_class[OUT_DIM][8]
            = { "Silence", "Unknown", "yes", "no",  "up",   "down",
                "left",    "right",   "on",  "off", "stop", "go" };
        for (int i = 0; i < OUT_DIM; ++i)
        {
            printf("% 4d ", p_prediction[i]);
        }
        int max_ind = 0;
        int max_val = -128000;
        for (int i = 0; i < OUT_DIM; i++)
        {
            if (max_val < p_prediction[i])
            {
                max_val = p_prediction[i];
                max_ind = i;
            }
        }
        printf(" --> %8s (%3d%%)",
               output_class[max_ind],
               ((int)(p_prediction[max_ind] + 128) * 100 / 256));
        printf("\n");
#endif

        return(0);
    };


};


#endif