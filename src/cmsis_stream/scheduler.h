/*

Generated with CMSIS-Stream python scripts.
The generated code is not covered by CMSIS-Stream license.

The support classes and code are covered by CMSIS-Stream license.

*/

#ifndef _SCHEDULER_H_ 
#define _SCHEDULER_H_

#ifdef   __cplusplus
extern "C"
{
#endif


#define AUDIOMARK_NB_IDENTIFIED_NODES 9
#define AUDIOMARK_ABF_ID 0
#define AUDIOMARK_AEC_ID 1
#define AUDIOMARK_ANR_ID 2
#define AUDIOMARK_DSNN_ID 3
#define AUDIOMARK_LEFT_ID 4
#define AUDIOMARK_MFCC_ID 5
#define AUDIOMARK_RESULT_ID 6
#define AUDIOMARK_RIGHT_ID 7
#define AUDIOMARK_SPEAKER_ID 8

extern void *get_scheduler_node(int32_t nodeID);

extern int init_scheduler(int iterations,
                              const int16_t *left_microphone_capture,
                              const int16_t *right_microphone_capture,
                              const int16_t *downlink_audio);
extern void free_scheduler(int iterations,
                              const int16_t *left_microphone_capture,
                              const int16_t *right_microphone_capture,
                              const int16_t *downlink_audio);
extern uint32_t scheduler(int *error,int iterations,
                              const int16_t *left_microphone_capture,
                              const int16_t *right_microphone_capture,
                              const int16_t *downlink_audio);

#ifdef   __cplusplus
}
#endif

#endif

