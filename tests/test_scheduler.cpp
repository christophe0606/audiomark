/*

Generated with CMSIS-DSP Compute Graph Scripts.
The generated code is not covered by CMSIS-DSP license.

The support classes and code is covered by CMSIS-DSP license.

*/


#include <cstdint>
#include "kws_test_custom.h"
#include "GenericNodes.h"
#include "cg_status.h"
#include "test_app_nodes.h"
#include "test_scheduler.h"

#if !defined(CHECKERROR)
#define CHECKERROR       if (cgStaticError < 0) \
       {\
         goto errorHandling;\
       }

#endif

#if !defined(CG_BEFORE_ITERATION)
#define CG_BEFORE_ITERATION
#endif 

#if !defined(CG_AFTER_ITERATION)
#define CG_AFTER_ITERATION
#endif 

#if !defined(CG_BEFORE_SCHEDULE)
#define CG_BEFORE_SCHEDULE
#endif

#if !defined(CG_AFTER_SCHEDULE)
#define CG_AFTER_SCHEDULE
#endif

#if !defined(CG_BEFORE_BUFFER)
#define CG_BEFORE_BUFFER
#endif

#if !defined(CG_BEFORE_FIFO_BUFFERS)
#define CG_BEFORE_FIFO_BUFFERS
#endif

#if !defined(CG_BEFORE_FIFO_INIT)
#define CG_BEFORE_FIFO_INIT
#endif

#if !defined(CG_BEFORE_NODE_INIT)
#define CG_BEFORE_NODE_INIT
#endif

#if !defined(CG_AFTER_INCLUDES)
#define CG_AFTER_INCLUDES
#endif

#if !defined(CG_BEFORE_SCHEDULER_FUNCTION)
#define CG_BEFORE_SCHEDULER_FUNCTION
#endif

#if !defined(CG_BEFORE_NODE_EXECUTION)
#define CG_BEFORE_NODE_EXECUTION
#endif

#if !defined(CG_AFTER_NODE_EXECUTION)
#define CG_AFTER_NODE_EXECUTION
#endif



CG_AFTER_INCLUDES


/*

Description of the scheduling. 

*/
static unsigned int schedule[25]=
{ 
4,4,0,2,3,1,5,4,0,2,3,1,5,4,0,2,3,1,5,4,0,2,3,1,5,
};

CG_BEFORE_FIFO_BUFFERS
/***********

FIFO buffers

************/
#define FIFOSIZE0 512
#define FIFOSIZE1 640
#define FIFOSIZE2 10
#define FIFOSIZE3 490
#define FIFOSIZE4 12

#define BUFFERSIZE1 512
CG_BEFORE_BUFFER
int16_t buf1[BUFFERSIZE1]={0};

#define BUFFERSIZE2 640
CG_BEFORE_BUFFER
int16_t buf2[BUFFERSIZE2]={0};

#define BUFFERSIZE3 10
CG_BEFORE_BUFFER
int8_t buf3[BUFFERSIZE3]={0};

#define BUFFERSIZE4 490
CG_BEFORE_BUFFER
int8_t buf4[BUFFERSIZE4]={0};

#define BUFFERSIZE5 12
CG_BEFORE_BUFFER
int8_t buf5[BUFFERSIZE5]={0};


typedef struct {
FIFO<int16_t,FIFOSIZE0,0,0> *fifo0;
FIFO<int16_t,FIFOSIZE1,1,0> *fifo1;
FIFO<int8_t,FIFOSIZE2,1,0> *fifo2;
FIFO<int8_t,FIFOSIZE3,1,0> *fifo3;
FIFO<int8_t,FIFOSIZE4,1,0> *fifo4;
} fifos_t;

typedef struct {
    SlidingBuffer<int16_t,640,320> *audioWin;
    DSNN<int8_t,490,int8_t,12> *dsnn;
    MFCC<int16_t,640,int8_t,10> *mfcc;
    SlidingBuffer<int8_t,490,480> *mfccWin;
    Source<int16_t,256> *src;
    TestResult<int8_t,12> *test;
} nodes_t;

CG_BEFORE_BUFFER
static fifos_t fifos={0};

CG_BEFORE_BUFFER
static nodes_t nodes={0};

int init_test_scheduler(int iterations,
                              int testMode,
                              const int16_t *p_input,
                              const int8_t *p_expected)
{
    CG_BEFORE_FIFO_INIT;
    fifos.fifo0 = new FIFO<int16_t,FIFOSIZE0,0,0>(buf1);
    if (fifos.fifo0==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo1 = new FIFO<int16_t,FIFOSIZE1,1,0>(buf2);
    if (fifos.fifo1==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo2 = new FIFO<int8_t,FIFOSIZE2,1,0>(buf3);
    if (fifos.fifo2==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo3 = new FIFO<int8_t,FIFOSIZE3,1,0>(buf4);
    if (fifos.fifo3==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo4 = new FIFO<int8_t,FIFOSIZE4,1,0>(buf5);
    if (fifos.fifo4==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }

    CG_BEFORE_NODE_INIT;
    nodes.audioWin = new SlidingBuffer<int16_t,640,320>(*(fifos.fifo0),*(fifos.fifo1));
    if (nodes.audioWin==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.dsnn = new DSNN<int8_t,490,int8_t,12>(*(fifos.fifo3),*(fifos.fifo4),1);
    if (nodes.dsnn==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.mfcc = new MFCC<int16_t,640,int8_t,10>(*(fifos.fifo1),*(fifos.fifo2),1);
    if (nodes.mfcc==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.mfccWin = new SlidingBuffer<int8_t,490,480>(*(fifos.fifo2),*(fifos.fifo3));
    if (nodes.mfccWin==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.src = new Source<int16_t,256>(*(fifos.fifo0),p_input);
    if (nodes.src==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.test = new TestResult<int8_t,12>(*(fifos.fifo4),p_expected);
    if (nodes.test==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }

    return(CG_SUCCESS);

}

void free_test_scheduler(int iterations,
                              int testMode,
                              const int16_t *p_input,
                              const int8_t *p_expected)
{
    if (fifos.fifo0!=NULL)
    {
       delete fifos.fifo0;
    }
    if (fifos.fifo1!=NULL)
    {
       delete fifos.fifo1;
    }
    if (fifos.fifo2!=NULL)
    {
       delete fifos.fifo2;
    }
    if (fifos.fifo3!=NULL)
    {
       delete fifos.fifo3;
    }
    if (fifos.fifo4!=NULL)
    {
       delete fifos.fifo4;
    }

    if (nodes.audioWin!=NULL)
    {
        delete nodes.audioWin;
    }
    if (nodes.dsnn!=NULL)
    {
        delete nodes.dsnn;
    }
    if (nodes.mfcc!=NULL)
    {
        delete nodes.mfcc;
    }
    if (nodes.mfccWin!=NULL)
    {
        delete nodes.mfccWin;
    }
    if (nodes.src!=NULL)
    {
        delete nodes.src;
    }
    if (nodes.test!=NULL)
    {
        delete nodes.test;
    }
}


CG_BEFORE_SCHEDULER_FUNCTION
uint32_t test_scheduler(int *error,int iterations,
                              int testMode,
                              const int16_t *p_input,
                              const int8_t *p_expected)
{
    int cgStaticError=0;
    uint32_t nbSchedule=0;
    int32_t debugCounter=1;


    /* Run several schedule iterations */
    CG_BEFORE_SCHEDULE;
    while((cgStaticError==0) && (debugCounter > 0))
    {
        /* Run a schedule iteration */
        CG_BEFORE_ITERATION;
        for(unsigned long id=0 ; id < 25; id++)
        {
            CG_BEFORE_NODE_EXECUTION;

            switch(schedule[id])
            {
                case 0:
                {
                   cgStaticError = nodes.audioWin->run();
                }
                break;

                case 1:
                {
                   cgStaticError = nodes.dsnn->run();
                }
                break;

                case 2:
                {
                   cgStaticError = nodes.mfcc->run();
                }
                break;

                case 3:
                {
                   cgStaticError = nodes.mfccWin->run();
                }
                break;

                case 4:
                {
                   cgStaticError = nodes.src->run();
                }
                break;

                case 5:
                {
                   cgStaticError = nodes.test->run();
                }
                break;

                default:
                break;
            }
            CG_AFTER_NODE_EXECUTION;
            CHECKERROR;
        }
       debugCounter--;
       CG_AFTER_ITERATION;
       nbSchedule++;
    }

errorHandling:
    CG_AFTER_SCHEDULE;
    *error=cgStaticError;
    return(nbSchedule);
}