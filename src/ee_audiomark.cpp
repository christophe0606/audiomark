#include <stdio.h>
extern "C" {
#include "ee_audiomark.h"
}

#include "custom.h"


#include "GenericNodes.h"
#include "cg_status.h"
#include "AppNodes.h"
#include "scheduler.h"

extern "C" {
extern const int16_t downlink_audio[NINPUT_SAMPLES];
extern const int16_t left_microphone_capture[NINPUT_SAMPLES];
extern const int16_t right_microphone_capture[NINPUT_SAMPLES];
}

int
ee_audiomark_initialize(bool printMem)
{
    int err = init_scheduler(1,left_microphone_capture,
                             right_microphone_capture,
                             downlink_audio);

    if (printMem)
    {
        printf("Memory alloc summary:\n");
        AudioMarkNode *abf=dynamic_cast<AudioMarkNode*>((NodeBase*)get_scheduler_node(AUDIOMARK_ABF_ID));
        AudioMarkNode *aec=dynamic_cast<AudioMarkNode*>((NodeBase*)get_scheduler_node(AUDIOMARK_AEC_ID));
        AudioMarkNode *anr=dynamic_cast<AudioMarkNode*>((NodeBase*)get_scheduler_node(AUDIOMARK_ANR_ID));
        AudioMarkNode *mfcc=dynamic_cast<AudioMarkNode*>((NodeBase*)get_scheduler_node(AUDIOMARK_MFCC_ID));
        AudioMarkNode *dsnn=dynamic_cast<AudioMarkNode*>((NodeBase*)get_scheduler_node(AUDIOMARK_DSNN_ID));
    
        // dynamic_cast needs RTTI.
        // If you don't want to use RTTI, you can use reinterpret_cast
        // but it is more risky since no check will be done at runtime
        /*
        ABF<int16_t,256,int16_t,256,int16_t,256> *abf =reinterpret_cast<ABF<int16_t,256,int16_t,256,int16_t,256>*>((NodeBase*)get_scheduler_node(AUDIOMARK_ABF_ID));
        AEC<int16_t,256,int16_t,256,int16_t,256> *aec =reinterpret_cast<AEC<int16_t,256,int16_t,256,int16_t,256>*>((NodeBase*)get_scheduler_node(AUDIOMARK_AEC_ID));
        ANR<int16_t,256,int16_t,256> *anr =reinterpret_cast<ANR<int16_t,256,int16_t,256>*>((NodeBase*)get_scheduler_node(AUDIOMARK_ANR_ID));
        MFCC<int16_t,640,int8_t,10> *mfcc=reinterpret_cast<MFCC<int16_t,640,int8_t,10>*>((NodeBase*)get_scheduler_node(AUDIOMARK_MFCC_ID));
        DSNN<int8_t,490,int8_t,12> *dsnn=reinterpret_cast<DSNN<int8_t,490,int8_t,12>*>((NodeBase*)get_scheduler_node(AUDIOMARK_DSNN_ID));
        */

        printf(" bmf = %d\n", abf->getMemoryUsage());
        printf(" aec = %d\n", aec->getMemoryUsage());
        printf(" anr = %d\n", anr->getMemoryUsage());
        printf(" mfcc = %d\n", mfcc->getMemoryUsage());
        printf(" dsnn = %d\n", dsnn->getMemoryUsage());
    }

    return(err);
}

void
ee_audiomark_release(void)
{
    free_scheduler(1,left_microphone_capture,
                             right_microphone_capture,
                             downlink_audio);
}


int
ee_audiomark_run(int iterations)
{
    int error;
    uint32_t nbSched=scheduler(&error,iterations,left_microphone_capture,
                             right_microphone_capture,
                             downlink_audio);

    if (error == CG_SUCCESS)
    {
        return(CG_SUCCESS);
    }
    
    if (error != CG_STOP_SCHEDULER)
    {
      return(error);
    }
    else
    {
        return CG_SUCCESS;
    }
}

