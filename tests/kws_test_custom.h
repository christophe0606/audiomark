#ifndef _CUSTOM_H_

extern "C" {
extern int inferences ;
extern int testError;
}

#define CG_BEFORE_SCHEDULE \
debugCounter = iterations;

#endif 