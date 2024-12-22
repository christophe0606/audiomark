/*

Generated with CMSIS-Stream python scripts.
The generated code is not covered by CMSIS-Stream license.

The support classes and code are covered by CMSIS-Stream license.

*/


#include <cstdint>
#include "custom.h"
#include "cg_status.h"
#include "GenericNodes.h"
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
#define CG_BEFORE_NODE_EXECUTION(ID)
#endif

#if !defined(CG_AFTER_NODE_EXECUTION)
#define CG_AFTER_NODE_EXECUTION(ID)
#endif



#if !defined(CG_RESTORE_STATE_MACHINE_STATE)
#define CG_RESTORE_STATE_MACHINE_STATE
#endif

#if !defined(CG_SAVE_STATE_MACHINE_STATE)
#define CG_SAVE_STATE_MACHINE_STATE
#endif


CG_AFTER_INCLUDES


using namespace arm_cmsis_stream;

/*

Description of the scheduling. 

*/
static uint8_t schedule[69]=
{ 
6,10,12,5,13,14,0,1,2,6,10,12,5,13,14,0,1,2,3,7,8,4,9,11,6,10,12,5,13,14,0,1,2,3,7,8,4,9,11,6,
10,12,5,13,14,0,1,2,3,7,8,4,9,11,6,10,12,5,13,14,0,1,2,3,7,8,4,9,11,
};

/*

Internal ID identification for the nodes

*/
#define ABF_INTERNAL_ID 0
#define AEC_INTERNAL_ID 1
#define ANR_INTERNAL_ID 2
#define AUDIOWIN_INTERNAL_ID 3
#define DSNN_INTERNAL_ID 4
#define DUP0_INTERNAL_ID 5
#define LEFT_INTERNAL_ID 6
#define MFCC_INTERNAL_ID 7
#define MFCCWIN_INTERNAL_ID 8
#define RESULT_INTERNAL_ID 9
#define RIGHT_INTERNAL_ID 10
#define SINK_INTERNAL_ID 11
#define SPEAKER_INTERNAL_ID 12

/* For callback management */

#define CG_PAUSED_SCHEDULER_ID 1
#define CG_SCHEDULER_NOT_STARTED_ID 2
#define CG_SCHEDULER_RUNNING_ID 3

struct cb_state_t
{
    unsigned long scheduleStateID;
    unsigned long nbSched;
    int status;
    kCBStatus running;
};

static cb_state_t cb_state;


static void init_cb_state()
{
    cb_state.status = CG_SCHEDULER_NOT_STARTED_ID;
    cb_state.nbSched = 0;
    cb_state.scheduleStateID = 0;
    cb_state.running = kNewExecution;
}


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
#define FIFOSIZE8 10
#define FIFOSIZE9 490
#define FIFOSIZE10 12
#define FIFOSIZE11 8
#define FIFOSIZE12 2
#define FIFOSIZE13 256
#define FIFOSIZE14 256
#define FIFOSIZE15 256
#define FIFOSIZE16 256

#define BUFFERSIZE0 256
CG_BEFORE_BUFFER
int16_t buf0[BUFFERSIZE0]={0};

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

#define BUFFERSIZE6 512
CG_BEFORE_BUFFER
int16_t buf6[BUFFERSIZE6]={0};

#define BUFFERSIZE7 640
CG_BEFORE_BUFFER
int16_t buf7[BUFFERSIZE7]={0};

#define BUFFERSIZE8 10
CG_BEFORE_BUFFER
int8_t buf8[BUFFERSIZE8]={0};

#define BUFFERSIZE9 490
CG_BEFORE_BUFFER
int8_t buf9[BUFFERSIZE9]={0};

#define BUFFERSIZE10 12
CG_BEFORE_BUFFER
int8_t buf10[BUFFERSIZE10]={0};

#define BUFFERSIZE11 8
CG_BEFORE_BUFFER
uint8_t buf11[BUFFERSIZE11]={0};

#define BUFFERSIZE12 2
CG_BEFORE_BUFFER
float buf12[BUFFERSIZE12]={0};

#define BUFFERSIZE13 256
CG_BEFORE_BUFFER
int16_t buf13[BUFFERSIZE13]={0};

#define BUFFERSIZE14 256
CG_BEFORE_BUFFER
int16_t buf14[BUFFERSIZE14]={0};

#define BUFFERSIZE15 256
CG_BEFORE_BUFFER
int16_t buf15[BUFFERSIZE15]={0};

#define BUFFERSIZE16 256
CG_BEFORE_BUFFER
int16_t buf16[BUFFERSIZE16]={0};


typedef struct {
FIFO<int16_t,FIFOSIZE0,1,0> *fifo0;
FIFO<int16_t,FIFOSIZE1,1,0> *fifo1;
FIFO<int16_t,FIFOSIZE2,1,0> *fifo2;
FIFO<int16_t,FIFOSIZE3,1,0> *fifo3;
FIFO<int16_t,FIFOSIZE4,1,0> *fifo4;
FIFO<int16_t,FIFOSIZE5,1,0> *fifo5;
FIFO<int16_t,FIFOSIZE6,0,0> *fifo6;
FIFO<int16_t,FIFOSIZE7,1,0> *fifo7;
FIFO<int8_t,FIFOSIZE8,1,0> *fifo8;
FIFO<int8_t,FIFOSIZE9,1,0> *fifo9;
FIFO<int8_t,FIFOSIZE10,1,0> *fifo10;
FIFO<uint8_t,FIFOSIZE11,1,0> *fifo11;
FIFO<float,FIFOSIZE12,1,0> *fifo12;
FIFO<int16_t,FIFOSIZE13,1,0> *fifo13;
FIFO<int16_t,FIFOSIZE14,1,0> *fifo14;
FIFO<int16_t,FIFOSIZE15,1,0> *fifo15;
FIFO<int16_t,FIFOSIZE16,1,0> *fifo16;
} fifos_t;

typedef struct {
    ABF<int16_t,256,int16_t,256,int16_t,256> *abf;
    AEC<int16_t,256,int16_t,256,int16_t,256> *aec;
    ANR<int16_t,256,int16_t,256> *anr;
    SlidingBuffer<int16_t,640,320> *audioWin;
    DSNN<int8_t,490,int8_t,12> *dsnn;
    Duplicate<int16_t,256,int16_t,256> *dup0;
    GstSource<int16_t,256> *left;
    MFCC<int16_t,640,int8_t,10> *mfcc;
    SlidingBuffer<int8_t,490,480> *mfccWin;
    GstResult<int8_t,12,float,2,uint8_t,8> *result;
    GstSource<int16_t,256> *right;
    GstDurationSink<float,2,uint8_t,8> *sink;
    GstSource<int16_t,256> *speaker;
} nodes_t;

CG_BEFORE_BUFFER
static fifos_t fifos={0};

CG_BEFORE_BUFFER
static nodes_t nodes={0};


int init_scheduler(void *node,gst_api *gst)
{
init_cb_state();

    CG_BEFORE_FIFO_INIT;
    fifos.fifo0 = new FIFO<int16_t,FIFOSIZE0,1,0>(buf0);
    if (fifos.fifo0==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo1 = new FIFO<int16_t,FIFOSIZE1,1,0>(buf1);
    if (fifos.fifo1==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo2 = new FIFO<int16_t,FIFOSIZE2,1,0>(buf2);
    if (fifos.fifo2==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo3 = new FIFO<int16_t,FIFOSIZE3,1,0>(buf3);
    if (fifos.fifo3==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo4 = new FIFO<int16_t,FIFOSIZE4,1,0>(buf4);
    if (fifos.fifo4==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo5 = new FIFO<int16_t,FIFOSIZE5,1,0>(buf5);
    if (fifos.fifo5==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo6 = new FIFO<int16_t,FIFOSIZE6,0,0>(buf6);
    if (fifos.fifo6==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo7 = new FIFO<int16_t,FIFOSIZE7,1,0>(buf7);
    if (fifos.fifo7==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo8 = new FIFO<int8_t,FIFOSIZE8,1,0>(buf8);
    if (fifos.fifo8==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo9 = new FIFO<int8_t,FIFOSIZE9,1,0>(buf9);
    if (fifos.fifo9==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo10 = new FIFO<int8_t,FIFOSIZE10,1,0>(buf10);
    if (fifos.fifo10==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo11 = new FIFO<uint8_t,FIFOSIZE11,1,0>(buf11);
    if (fifos.fifo11==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo12 = new FIFO<float,FIFOSIZE12,1,0>(buf12);
    if (fifos.fifo12==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo13 = new FIFO<int16_t,FIFOSIZE13,1,0>(buf13);
    if (fifos.fifo13==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo14 = new FIFO<int16_t,FIFOSIZE14,1,0>(buf14);
    if (fifos.fifo14==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo15 = new FIFO<int16_t,FIFOSIZE15,1,0>(buf15);
    if (fifos.fifo15==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo16 = new FIFO<int16_t,FIFOSIZE16,1,0>(buf16);
    if (fifos.fifo16==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }

    CG_BEFORE_NODE_INIT;
    nodes.abf = new ABF<int16_t,256,int16_t,256,int16_t,256>(*(fifos.fifo2),*(fifos.fifo3),*(fifos.fifo4));
    if (nodes.abf==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.aec = new AEC<int16_t,256,int16_t,256,int16_t,256>(*(fifos.fifo4),*(fifos.fifo16),*(fifos.fifo5));
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
    nodes.dsnn = new DSNN<int8_t,490,int8_t,12>(*(fifos.fifo9),*(fifos.fifo10));
    if (nodes.dsnn==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.dup0 = new Duplicate<int16_t,256,int16_t,256>(*(fifos.fifo13),{fifos.fifo14,fifos.fifo15,fifos.fifo16});
    if (nodes.dup0==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.left = new GstSource<int16_t,256>(*(fifos.fifo0),node,gst,"left","audio/x-raw, layout=interleaved, channels=1, format=S16LE, rate=16000");
    if (nodes.left==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.mfcc = new MFCC<int16_t,640,int8_t,10>(*(fifos.fifo7),*(fifos.fifo8));
    if (nodes.mfcc==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.mfccWin = new SlidingBuffer<int8_t,490,480>(*(fifos.fifo8),*(fifos.fifo9));
    if (nodes.mfccWin==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.result = new GstResult<int8_t,12,float,2,uint8_t,8>(*(fifos.fifo10),*(fifos.fifo12),*(fifos.fifo11));
    if (nodes.result==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.right = new GstSource<int16_t,256>(*(fifos.fifo1),node,gst,"right","audio/x-raw, layout=interleaved, channels=1, format=S16LE, rate=16000");
    if (nodes.right==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.sink = new GstDurationSink<float,2,uint8_t,8>(*(fifos.fifo12),*(fifos.fifo11),node,gst,"sink","text/x-raw, format=utf8");
    if (nodes.sink==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.speaker = new GstSource<int16_t,256>(*(fifos.fifo13),node,gst,"speaker","audio/x-raw, layout=interleaved, channels=1, format=S16LE, rate=16000");
    if (nodes.speaker==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }

    return(CG_SUCCESS);

}

void free_scheduler(void *node,gst_api *gst)
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
    if (fifos.fifo13!=NULL)
    {
       delete fifos.fifo13;
    }
    if (fifos.fifo14!=NULL)
    {
       delete fifos.fifo14;
    }
    if (fifos.fifo15!=NULL)
    {
       delete fifos.fifo15;
    }
    if (fifos.fifo16!=NULL)
    {
       delete fifos.fifo16;
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
    if (nodes.mfccWin!=NULL)
    {
        delete nodes.mfccWin;
    }
    if (nodes.result!=NULL)
    {
        delete nodes.result;
    }
    if (nodes.right!=NULL)
    {
        delete nodes.right;
    }
    if (nodes.sink!=NULL)
    {
        delete nodes.sink;
    }
    if (nodes.speaker!=NULL)
    {
        delete nodes.speaker;
    }
}


CG_BEFORE_SCHEDULER_FUNCTION
uint32_t scheduler(int *error,void *node,gst_api *gst)
{
    int cgStaticError=0;
    uint32_t nbSchedule=0;

if (cb_state.status==CG_PAUSED_SCHEDULER_ID)
   {
      nbSchedule = cb_state.nbSched;

   }


    /* Run several schedule iterations */
    CG_BEFORE_SCHEDULE;
CG_RESTORE_STATE_MACHINE_STATE;
    while(cgStaticError==0)
    {
        /* Run a schedule iteration */
        CG_BEFORE_ITERATION;
        unsigned long id=0;
        if (cb_state.status==CG_PAUSED_SCHEDULER_ID)
        {
            id = cb_state.scheduleStateID;
            cb_state.status = CG_SCHEDULER_RUNNING_ID;
        }
        for(; id < 69; id++)
        {
            CG_BEFORE_NODE_EXECUTION(schedule[id]);
            switch(schedule[id])
            {
                case 0:
                {
                    nodes.abf->setExecutionStatus(cb_state.running);
                   cgStaticError = nodes.abf->run();
                }
                break;

                case 1:
                {
                    nodes.aec->setExecutionStatus(cb_state.running);
                   cgStaticError = nodes.aec->run();
                }
                break;

                case 2:
                {
                    nodes.anr->setExecutionStatus(cb_state.running);
                   cgStaticError = nodes.anr->run();
                }
                break;

                case 3:
                {
                    nodes.audioWin->setExecutionStatus(cb_state.running);
                   cgStaticError = nodes.audioWin->run();
                }
                break;

                case 4:
                {
                    nodes.dsnn->setExecutionStatus(cb_state.running);
                   cgStaticError = nodes.dsnn->run();
                }
                break;

                case 5:
                {
                    nodes.dup0->setExecutionStatus(cb_state.running);
                   cgStaticError = nodes.dup0->run();
                }
                break;

                case 6:
                {
                    nodes.left->setExecutionStatus(cb_state.running);
                   cgStaticError = nodes.left->run();
                }
                break;

                case 7:
                {
                    nodes.mfcc->setExecutionStatus(cb_state.running);
                   cgStaticError = nodes.mfcc->run();
                }
                break;

                case 8:
                {
                    nodes.mfccWin->setExecutionStatus(cb_state.running);
                   cgStaticError = nodes.mfccWin->run();
                }
                break;

                case 9:
                {
                    nodes.result->setExecutionStatus(cb_state.running);
                   cgStaticError = nodes.result->run();
                }
                break;

                case 10:
                {
                    nodes.right->setExecutionStatus(cb_state.running);
                   cgStaticError = nodes.right->run();
                }
                break;

                case 11:
                {
                    nodes.sink->setExecutionStatus(cb_state.running);
                   cgStaticError = nodes.sink->run();
                }
                break;

                case 12:
                {
                    nodes.speaker->setExecutionStatus(cb_state.running);
                   cgStaticError = nodes.speaker->run();
                }
                break;

                case 13:
                {
                    
                   
                  {

                   int16_t* i0;
                   int16_t* i1;
                   int16_t* o2;
                   i0=fifos.fifo0->getReadBuffer(256);
                   i1=fifos.fifo14->getReadBuffer(256);
                   o2=fifos.fifo2->getWriteBuffer(256);
                   th_add_q15(i0,i1,o2,256);
                   cgStaticError = 0;
                  }
                }
                break;

                case 14:
                {
                    
                   
                  {

                   int16_t* i0;
                   int16_t* i1;
                   int16_t* o2;
                   i0=fifos.fifo1->getReadBuffer(256);
                   i1=fifos.fifo15->getReadBuffer(256);
                   o2=fifos.fifo3->getWriteBuffer(256);
                   th_add_q15(i0,i1,o2,256);
                   cgStaticError = 0;
                  }
                }
                break;

                default:
                break;
            }
            CG_AFTER_NODE_EXECUTION(schedule[id]);
            cb_state.running = kNewExecution;
            if (cgStaticError == CG_PAUSED_SCHEDULER)
            {
                CG_SAVE_STATE_MACHINE_STATE;
                cb_state.status = CG_PAUSED_SCHEDULER_ID;
                cb_state.nbSched = nbSchedule;
                cb_state.scheduleStateID = id;
                cb_state.running = kResumedExecution;
            }
            CHECKERROR;
        }
       CG_AFTER_ITERATION;
       nbSchedule++;
    }

errorHandling:
    CG_AFTER_SCHEDULE;
    *error=cgStaticError;
    return(nbSchedule);
}
