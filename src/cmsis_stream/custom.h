#ifndef _CUSTOM_H_

#if defined(GST)
#include "gst_intf.h"
#else

#define CG_BEFORE_SCHEDULE \
debugCounter = iterations;
#endif

#define CG_BEFORE_BUFFER \
__attribute__((aligned(16)))


#define CG_BEFORE_FIFO_INIT \
th_nn_init();

#endif 