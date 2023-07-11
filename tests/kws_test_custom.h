#ifndef _CUSTOM_H_

extern "C" {
extern int testError;
}

#define CG_BEFORE_SCHEDULE \
debugCounter = iterations;

#endif 