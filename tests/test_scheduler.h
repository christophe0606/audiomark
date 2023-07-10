/*

Generated with CMSIS-DSP Compute Graph Scripts.
The generated code is not covered by CMSIS-DSP license.

The support classes and code is covered by CMSIS-DSP license.

*/

#ifndef _TEST_SCHEDULER_H_ 
#define _TEST_SCHEDULER_H_

#ifdef   __cplusplus
extern "C"
{
#endif


extern int init_test_scheduler(int iterations,
                              const int16_t *p_input,
                              const int8_t *p_expected);
extern void free_test_scheduler(int iterations,
                              const int16_t *p_input,
                              const int8_t *p_expected);
extern uint32_t test_scheduler(int *error,int iterations,
                              const int16_t *p_input,
                              const int8_t *p_expected);

#ifdef   __cplusplus
}
#endif

#endif

