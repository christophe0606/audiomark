/*

Generated with CMSIS-DSP Compute Graph Scripts.
The generated code is not covered by CMSIS-DSP license.

The support classes and code is covered by CMSIS-DSP license.

*/

#ifndef _SCHEDULER_H_ 
#define _SCHEDULER_H_

#ifdef   __cplusplus
extern "C"
{
#endif


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

