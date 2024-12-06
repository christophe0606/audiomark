#ifndef _CUSTOM_H_

extern "C" {
extern int testError;
}

#define CG_BEFORE_SCHEDULE \
debugCounter = iterations;

#define CG_BEFORE_FIFO_INIT \
dsnn_input=th_nn_init();

#endif 