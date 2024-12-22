#ifndef _CUSTOM_H_

#define CG_BEFORE_BUFFER \
__attribute__((aligned(16)))

#define CG_BEFORE_SCHEDULE \
debugCounter = iterations;

#define CG_BEFORE_FIFO_INIT \
th_nn_init();

#endif 