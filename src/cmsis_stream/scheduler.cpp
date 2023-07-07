/*

Generated with CMSIS-DSP Compute Graph Scripts.
The generated code is not covered by CMSIS-DSP license.

The support classes and code is covered by CMSIS-DSP license.

*/


#include <cstdint>
#include "custom.h"
#include "GenericNodes.h"
#include "cg_status.h"
#include "AppNodes.h"
#include "scheduler.h"

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
static unsigned int schedule[2601]=
{ 
8,10,11,7,3,4,0,1,2,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,
5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,
1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,8,10,11,7,3,
4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,
10,11,7,3,4,0,1,2,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,
9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,
2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,8,10,11,7,3,4,
0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,
11,7,3,4,0,1,2,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,
8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,
5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,8,10,11,7,3,4,0,
1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,
7,3,4,0,1,2,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,
10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,
9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,8,10,11,7,3,4,0,1,
2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,
3,4,0,1,2,8,10,11,7,3,4,0,1,2,5,9,6,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,
10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,
9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,8,10,11,7,3,4,0,1,
2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,
3,4,0,1,2,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,
11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,
8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,8,10,11,7,3,4,0,1,2,
5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,
4,0,1,2,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,
7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,
10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,8,10,11,7,3,4,0,1,2,5,
9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,
0,1,2,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,
3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,
11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,8,10,11,7,3,4,0,1,2,5,9,
8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,
1,2,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,6,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,
3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,
11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,8,10,11,7,3,4,0,1,2,5,9,
8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,
1,2,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,
4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,
7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,8,10,11,7,3,4,0,1,2,5,9,8,
10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,
2,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,
0,1,2,5,9,8,10,11,7,3,4,0,1,2,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,
3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,8,10,11,7,3,4,0,1,2,5,9,8,10,
11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,
8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,
1,2,5,9,8,10,11,7,3,4,0,1,2,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,
4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,8,10,11,7,3,4,0,1,2,5,9,8,10,11,
7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,8,
10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,6,8,10,11,7,3,4,0,
1,2,5,9,8,10,11,7,3,4,0,1,2,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,
4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,8,10,11,7,3,4,0,1,2,5,9,8,10,11,
7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,8,
10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,
2,5,9,8,10,11,7,3,4,0,1,2,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,
0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,
3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,8,10,
11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,
5,9,8,10,11,7,3,4,0,1,2,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,
1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,
4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,8,10,11,
7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,
9,8,10,11,7,3,4,0,1,2,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,
2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,
0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,8,10,11,7,
3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,8,10,11,7,3,4,0,1,2,5,9,
6,
};

CG_BEFORE_FIFO_BUFFERS
/***********

FIFO buffers

************/
#define FIFOSIZE0 256
#define FIFOSIZE1 256
#define FIFOSIZE2 256
#define FIFOSIZE3 256
#define FIFOSIZE4 256
#define FIFOSIZE5 256
#define FIFOSIZE6 512
#define FIFOSIZE7 640
#define FIFOSIZE8 490
#define FIFOSIZE9 256
#define FIFOSIZE10 256
#define FIFOSIZE11 256
#define FIFOSIZE12 256

#define BUFFERSIZE1 256
CG_BEFORE_BUFFER
int16_t buf1[BUFFERSIZE1]={0};

#define BUFFERSIZE2 256
CG_BEFORE_BUFFER
int16_t buf2[BUFFERSIZE2]={0};

#define BUFFERSIZE3 256
CG_BEFORE_BUFFER
int16_t buf3[BUFFERSIZE3]={0};

#define BUFFERSIZE4 256
CG_BEFORE_BUFFER
int16_t buf4[BUFFERSIZE4]={0};

#define BUFFERSIZE5 256
CG_BEFORE_BUFFER
int16_t buf5[BUFFERSIZE5]={0};

#define BUFFERSIZE6 256
CG_BEFORE_BUFFER
int16_t buf6[BUFFERSIZE6]={0};

#define BUFFERSIZE7 512
CG_BEFORE_BUFFER
int16_t buf7[BUFFERSIZE7]={0};

#define BUFFERSIZE8 640
CG_BEFORE_BUFFER
int16_t buf8[BUFFERSIZE8]={0};

#define BUFFERSIZE9 490
CG_BEFORE_BUFFER
int8_t buf9[BUFFERSIZE9]={0};

#define BUFFERSIZE10 256
CG_BEFORE_BUFFER
int16_t buf10[BUFFERSIZE10]={0};

#define BUFFERSIZE11 256
CG_BEFORE_BUFFER
int16_t buf11[BUFFERSIZE11]={0};

#define BUFFERSIZE12 256
CG_BEFORE_BUFFER
int16_t buf12[BUFFERSIZE12]={0};

#define BUFFERSIZE13 256
CG_BEFORE_BUFFER
int16_t buf13[BUFFERSIZE13]={0};


typedef struct {
FIFO<int16_t,FIFOSIZE0,1,0> *fifo0;
FIFO<int16_t,FIFOSIZE1,1,0> *fifo1;
FIFO<int16_t,FIFOSIZE2,1,0> *fifo2;
FIFO<int16_t,FIFOSIZE3,1,0> *fifo3;
FIFO<int16_t,FIFOSIZE4,1,0> *fifo4;
FIFO<int16_t,FIFOSIZE5,1,0> *fifo5;
FIFO<int16_t,FIFOSIZE6,0,0> *fifo6;
FIFO<int16_t,FIFOSIZE7,1,0> *fifo7;
FIFO<int8_t,FIFOSIZE8,0,0> *fifo8;
FIFO<int16_t,FIFOSIZE9,1,0> *fifo9;
FIFO<int16_t,FIFOSIZE10,1,0> *fifo10;
FIFO<int16_t,FIFOSIZE11,1,0> *fifo11;
FIFO<int16_t,FIFOSIZE12,1,0> *fifo12;
} fifos_t;

typedef struct {
    ABF<int16_t,256,int16_t,256,int16_t,256> *abf;
    AEC<int16_t,256,int16_t,256,int16_t,256> *aec;
    ANR<int16_t,256,int16_t,256> *anr;
    SlidingBuffer<int16_t,640,320> *audioWin;
    DSNN<int8_t,490> *dsnn;
    Duplicate<int16_t,256,int16_t,256> *dup0;
    Source<int16_t,256> *left;
    MFCC<int16_t,640,int8_t,10> *mfcc;
    Source<int16_t,256> *right;
    Source<int16_t,256> *speaker;
} nodes_t;

CG_BEFORE_BUFFER
static fifos_t fifos={0};

CG_BEFORE_BUFFER
static nodes_t nodes={0};

int init_scheduler()
{
    CG_BEFORE_FIFO_INIT;
    fifos.fifo0 = new FIFO<int16_t,FIFOSIZE0,1,0>(buf1);
    if (fifos.fifo0==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo1 = new FIFO<int16_t,FIFOSIZE1,1,0>(buf2);
    if (fifos.fifo1==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo2 = new FIFO<int16_t,FIFOSIZE2,1,0>(buf3);
    if (fifos.fifo2==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo3 = new FIFO<int16_t,FIFOSIZE3,1,0>(buf4);
    if (fifos.fifo3==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo4 = new FIFO<int16_t,FIFOSIZE4,1,0>(buf5);
    if (fifos.fifo4==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo5 = new FIFO<int16_t,FIFOSIZE5,1,0>(buf6);
    if (fifos.fifo5==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo6 = new FIFO<int16_t,FIFOSIZE6,0,0>(buf7);
    if (fifos.fifo6==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo7 = new FIFO<int16_t,FIFOSIZE7,1,0>(buf8);
    if (fifos.fifo7==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo8 = new FIFO<int8_t,FIFOSIZE8,0,0>(buf9);
    if (fifos.fifo8==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo9 = new FIFO<int16_t,FIFOSIZE9,1,0>(buf10);
    if (fifos.fifo9==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo10 = new FIFO<int16_t,FIFOSIZE10,1,0>(buf11);
    if (fifos.fifo10==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo11 = new FIFO<int16_t,FIFOSIZE11,1,0>(buf12);
    if (fifos.fifo11==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo12 = new FIFO<int16_t,FIFOSIZE12,1,0>(buf13);
    if (fifos.fifo12==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }

    CG_BEFORE_NODE_INIT;
    nodes.abf = new ABF<int16_t,256,int16_t,256,int16_t,256>(*(fifos.fifo2),*(fifos.fifo3),*(fifos.fifo4));
    if (nodes.abf==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.aec = new AEC<int16_t,256,int16_t,256,int16_t,256>(*(fifos.fifo4),*(fifos.fifo12),*(fifos.fifo5));
    if (nodes.aec==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.anr = new ANR<int16_t,256,int16_t,256>(*(fifos.fifo5),*(fifos.fifo6));
    if (nodes.anr==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.audioWin = new SlidingBuffer<int16_t,640,320>(*(fifos.fifo6),*(fifos.fifo7));
    if (nodes.audioWin==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.dsnn = new DSNN<int8_t,490>(*(fifos.fifo8));
    if (nodes.dsnn==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.dup0 = new Duplicate<int16_t,256,int16_t,256>(*(fifos.fifo9),{fifos.fifo10,fifos.fifo11,fifos.fifo12});
    if (nodes.dup0==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.left = new Source<int16_t,256>(*(fifos.fifo0));
    if (nodes.left==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.mfcc = new MFCC<int16_t,640,int8_t,10>(*(fifos.fifo7),*(fifos.fifo8));
    if (nodes.mfcc==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.right = new Source<int16_t,256>(*(fifos.fifo1));
    if (nodes.right==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.speaker = new Source<int16_t,256>(*(fifos.fifo9));
    if (nodes.speaker==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }

    return(CG_SUCCESS);

}

void free_scheduler()
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
    if (fifos.fifo5!=NULL)
    {
       delete fifos.fifo5;
    }
    if (fifos.fifo6!=NULL)
    {
       delete fifos.fifo6;
    }
    if (fifos.fifo7!=NULL)
    {
       delete fifos.fifo7;
    }
    if (fifos.fifo8!=NULL)
    {
       delete fifos.fifo8;
    }
    if (fifos.fifo9!=NULL)
    {
       delete fifos.fifo9;
    }
    if (fifos.fifo10!=NULL)
    {
       delete fifos.fifo10;
    }
    if (fifos.fifo11!=NULL)
    {
       delete fifos.fifo11;
    }
    if (fifos.fifo12!=NULL)
    {
       delete fifos.fifo12;
    }

    if (nodes.abf!=NULL)
    {
        delete nodes.abf;
    }
    if (nodes.aec!=NULL)
    {
        delete nodes.aec;
    }
    if (nodes.anr!=NULL)
    {
        delete nodes.anr;
    }
    if (nodes.audioWin!=NULL)
    {
        delete nodes.audioWin;
    }
    if (nodes.dsnn!=NULL)
    {
        delete nodes.dsnn;
    }
    if (nodes.dup0!=NULL)
    {
        delete nodes.dup0;
    }
    if (nodes.left!=NULL)
    {
        delete nodes.left;
    }
    if (nodes.mfcc!=NULL)
    {
        delete nodes.mfcc;
    }
    if (nodes.right!=NULL)
    {
        delete nodes.right;
    }
    if (nodes.speaker!=NULL)
    {
        delete nodes.speaker;
    }
}


CG_BEFORE_SCHEDULER_FUNCTION
uint32_t scheduler(int *error)
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
        for(unsigned long id=0 ; id < 2601; id++)
        {
            CG_BEFORE_NODE_EXECUTION;

            switch(schedule[id])
            {
                case 0:
                {
                   cgStaticError = nodes.abf->run();
                }
                break;

                case 1:
                {
                   cgStaticError = nodes.aec->run();
                }
                break;

                case 2:
                {
                   cgStaticError = nodes.anr->run();
                }
                break;

                case 3:
                {
                   
                  {

                   int16_t* i0;
                   int16_t* i1;
                   int16_t* o2;
                   i0=fifos.fifo0->getReadBuffer(256);
                   i1=fifos.fifo10->getReadBuffer(256);
                   o2=fifos.fifo2->getWriteBuffer(256);
                   arm_add_q15(i0,i1,o2,256);
                   cgStaticError = 0;
                  }
                }
                break;

                case 4:
                {
                   
                  {

                   int16_t* i0;
                   int16_t* i1;
                   int16_t* o2;
                   i0=fifos.fifo1->getReadBuffer(256);
                   i1=fifos.fifo11->getReadBuffer(256);
                   o2=fifos.fifo3->getWriteBuffer(256);
                   arm_add_q15(i0,i1,o2,256);
                   cgStaticError = 0;
                  }
                }
                break;

                case 5:
                {
                   cgStaticError = nodes.audioWin->run();
                }
                break;

                case 6:
                {
                   cgStaticError = nodes.dsnn->run();
                }
                break;

                case 7:
                {
                   cgStaticError = nodes.dup0->run();
                }
                break;

                case 8:
                {
                   cgStaticError = nodes.left->run();
                }
                break;

                case 9:
                {
                   cgStaticError = nodes.mfcc->run();
                }
                break;

                case 10:
                {
                   cgStaticError = nodes.right->run();
                }
                break;

                case 11:
                {
                   cgStaticError = nodes.speaker->run();
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
