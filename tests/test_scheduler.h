/*

Generated with CMSIS-Stream python scripts.
The generated code is not covered by CMSIS-Stream license.

The support classes and code are covered by CMSIS-Stream license.

*/

#ifndef _TEST_SCHEDULER_H_ 
#define _TEST_SCHEDULER_H_

#ifdef   __cplusplus
extern "C"
{
#endif


#define NB_IDENTIFIED_NODES 6
#define AUDIOWIN_ID 0
#define DSNN_ID 1
#define MFCC_ID 2
#define MFCCWIN_ID 3
#define SRC_ID 4
#define TEST_ID 5

extern void *get_test_scheduler_node(int32_t nodeID);

extern int init_test_scheduler(int iterations,
                              int testMode,
                              const int16_t *p_input,
                              const int8_t *p_expected);
extern void free_test_scheduler(int iterations,
                              int testMode,
                              const int16_t *p_input,
                              const int8_t *p_expected);
extern uint32_t test_scheduler(int *error,int iterations,
                              int testMode,
                              const int16_t *p_input,
                              const int8_t *p_expected);

#ifdef   __cplusplus
}
#endif

#endif

