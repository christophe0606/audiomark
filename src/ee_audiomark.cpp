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

