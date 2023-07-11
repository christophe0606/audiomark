#include <stdio.h>
#include "ee_audiomark.h"

#include "scheduler.h"
#include "cg_status.h"


extern const int16_t downlink_audio[NINPUT_SAMPLES];
extern const int16_t left_microphone_capture[NINPUT_SAMPLES];
extern const int16_t right_microphone_capture[NINPUT_SAMPLES];

int
ee_audiomark_initialize(void)
{
    //printf("Memory alloc summary:\n");
    int err = init_scheduler(1,left_microphone_capture,
                             right_microphone_capture,
                             downlink_audio);
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

    //printf("nb=%d error=%d\n",nbSched,error);

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
        return 0;
    }
}

