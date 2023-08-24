/*

Generated with CMSIS-Stream python scripts.
The generated code is not covered by CMSIS-Stream license.

The support classes and code are covered by CMSIS-Stream license.

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
#define CG_BEFORE_NODE_EXECUTION(ID)
#endif

#if !defined(CG_AFTER_NODE_EXECUTION)
#define CG_AFTER_NODE_EXECUTION(ID)
#endif



CG_AFTER_INCLUDES


using namespace arm_cmsis_stream;

/*

Description of the scheduling. 

*/
static uint8_t schedule[65]=
{ 
6,10,11,5,12,13,0,1,2,6,10,11,5,12,13,0,1,2,3,7,8,4,9,6,10,11,5,12,13,0,1,2,3,7,8,4,9,6,10,11,
5,12,13,0,1,2,3,7,8,4,9,6,10,11,5,12,13,0,1,2,3,7,8,4,9,
};

/***********

Node identification

************/
static void * identifiedNodes[AUDIOMARK_NB_IDENTIFIED_NODES]={0};

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
#define FIFOSIZE11 256
#define FIFOSIZE12 256
#define FIFOSIZE13 256
#define FIFOSIZE14 256

#define BUFFERSIZE1 256
CG_BEFORE_BUFFER
int16_t audiomark_buf1[BUFFERSIZE1]={0};

#define BUFFERSIZE2 256
CG_BEFORE_BUFFER
int16_t audiomark_buf2[BUFFERSIZE2]={0};

#define BUFFERSIZE3 256
CG_BEFORE_BUFFER
int16_t audiomark_buf3[BUFFERSIZE3]={0};

#define BUFFERSIZE4 256
CG_BEFORE_BUFFER
int16_t audiomark_buf4[BUFFERSIZE4]={0};

#define BUFFERSIZE5 256
CG_BEFORE_BUFFER
int16_t audiomark_buf5[BUFFERSIZE5]={0};

#define BUFFERSIZE6 256
CG_BEFORE_BUFFER
int16_t audiomark_buf6[BUFFERSIZE6]={0};

#define BUFFERSIZE7 512
CG_BEFORE_BUFFER
int16_t audiomark_buf7[BUFFERSIZE7]={0};

#define BUFFERSIZE8 640
CG_BEFORE_BUFFER
int16_t audiomark_buf8[BUFFERSIZE8]={0};

#define BUFFERSIZE9 10
CG_BEFORE_BUFFER
int8_t audiomark_buf9[BUFFERSIZE9]={0};

#define BUFFERSIZE10 490
CG_BEFORE_BUFFER
int8_t audiomark_buf10[BUFFERSIZE10]={0};

#define BUFFERSIZE11 12
CG_BEFORE_BUFFER
int8_t audiomark_buf11[BUFFERSIZE11]={0};

#define BUFFERSIZE12 256
CG_BEFORE_BUFFER
int16_t audiomark_buf12[BUFFERSIZE12]={0};

#define BUFFERSIZE13 256
CG_BEFORE_BUFFER
int16_t audiomark_buf13[BUFFERSIZE13]={0};

#define BUFFERSIZE14 256
CG_BEFORE_BUFFER
int16_t audiomark_buf14[BUFFERSIZE14]={0};

#define BUFFERSIZE15 256
CG_BEFORE_BUFFER
int16_t audiomark_buf15[BUFFERSIZE15]={0};


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
FIFO<int16_t,FIFOSIZE11,1,0> *fifo11;
FIFO<int16_t,FIFOSIZE12,1,0> *fifo12;
FIFO<int16_t,FIFOSIZE13,1,0> *fifo13;
FIFO<int16_t,FIFOSIZE14,1,0> *fifo14;
} fifos_t;

typedef struct {
    ABF<int16_t,256,int16_t,256,int16_t,256> *abf;
    AEC<int16_t,256,int16_t,256,int16_t,256> *aec;
    ANR<int16_t,256,int16_t,256> *anr;
    SlidingBuffer<int16_t,640,320> *audioWin;
    DSNN<int8_t,490,int8_t,12> *dsnn;
    Duplicate<int16_t,256,int16_t,256> *dup0;
    Source<int16_t,256> *left;
    MFCC<int16_t,640,int8_t,10> *mfcc;
    SlidingBuffer<int8_t,490,480> *mfccWin;
    Result<int8_t,12> *result;
    Source<int16_t,256> *right;
    Source<int16_t,256> *speaker;
} nodes_t;

CG_BEFORE_BUFFER
static fifos_t fifos={0};

CG_BEFORE_BUFFER
static nodes_t nodes={0};

void *get_scheduler_node(int32_t nodeID)
{
    if (nodeID >= AUDIOMARK_NB_IDENTIFIED_NODES)
    {
        return(NULL);
    }
    if (nodeID < 0)
    {
        return(NULL);
    }
    return(identifiedNodes[nodeID]);
}

int init_scheduler(int iterations,
                              const int16_t *left_microphone_capture,
                              const int16_t *right_microphone_capture,
                              const int16_t *downlink_audio)
{
    CG_BEFORE_FIFO_INIT;
    fifos.fifo0 = new FIFO<int16_t,FIFOSIZE0,1,0>(audiomark_buf1);
    if (fifos.fifo0==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo1 = new FIFO<int16_t,FIFOSIZE1,1,0>(audiomark_buf2);
    if (fifos.fifo1==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo2 = new FIFO<int16_t,FIFOSIZE2,1,0>(audiomark_buf3);
    if (fifos.fifo2==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo3 = new FIFO<int16_t,FIFOSIZE3,1,0>(audiomark_buf4);
    if (fifos.fifo3==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo4 = new FIFO<int16_t,FIFOSIZE4,1,0>(audiomark_buf5);
    if (fifos.fifo4==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo5 = new FIFO<int16_t,FIFOSIZE5,1,0>(audiomark_buf6);
    if (fifos.fifo5==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo6 = new FIFO<int16_t,FIFOSIZE6,0,0>(audiomark_buf7);
    if (fifos.fifo6==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo7 = new FIFO<int16_t,FIFOSIZE7,1,0>(audiomark_buf8);
    if (fifos.fifo7==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo8 = new FIFO<int8_t,FIFOSIZE8,1,0>(audiomark_buf9);
    if (fifos.fifo8==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo9 = new FIFO<int8_t,FIFOSIZE9,1,0>(audiomark_buf10);
    if (fifos.fifo9==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo10 = new FIFO<int8_t,FIFOSIZE10,1,0>(audiomark_buf11);
    if (fifos.fifo10==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo11 = new FIFO<int16_t,FIFOSIZE11,1,0>(audiomark_buf12);
    if (fifos.fifo11==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo12 = new FIFO<int16_t,FIFOSIZE12,1,0>(audiomark_buf13);
    if (fifos.fifo12==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo13 = new FIFO<int16_t,FIFOSIZE13,1,0>(audiomark_buf14);
    if (fifos.fifo13==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo14 = new FIFO<int16_t,FIFOSIZE14,1,0>(audiomark_buf15);
    if (fifos.fifo14==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }

    CG_BEFORE_NODE_INIT;
    nodes.abf = new ABF<int16_t,256,int16_t,256,int16_t,256>(*(fifos.fifo2),*(fifos.fifo3),*(fifos.fifo4));
    if (nodes.abf==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    identifiedNodes[AUDIOMARK_ABF_ID]=(void*)nodes.abf;
    nodes.abf->setID(AUDIOMARK_ABF_ID);
    nodes.aec = new AEC<int16_t,256,int16_t,256,int16_t,256>(*(fifos.fifo4),*(fifos.fifo14),*(fifos.fifo5));
    if (nodes.aec==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    identifiedNodes[AUDIOMARK_AEC_ID]=(void*)nodes.aec;
    nodes.aec->setID(AUDIOMARK_AEC_ID);
    nodes.anr = new ANR<int16_t,256,int16_t,256>(*(fifos.fifo5),*(fifos.fifo6));
    if (nodes.anr==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    identifiedNodes[AUDIOMARK_ANR_ID]=(void*)nodes.anr;
    nodes.anr->setID(AUDIOMARK_ANR_ID);
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
    identifiedNodes[AUDIOMARK_DSNN_ID]=(void*)nodes.dsnn;
    nodes.dsnn->setID(AUDIOMARK_DSNN_ID);
    nodes.dup0 = new Duplicate<int16_t,256,int16_t,256>(*(fifos.fifo11),{fifos.fifo12,fifos.fifo13,fifos.fifo14});
    if (nodes.dup0==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.left = new Source<int16_t,256>(*(fifos.fifo0),left_microphone_capture);
    if (nodes.left==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    identifiedNodes[AUDIOMARK_LEFT_ID]=(void*)nodes.left;
    nodes.left->setID(AUDIOMARK_LEFT_ID);
    nodes.mfcc = new MFCC<int16_t,640,int8_t,10>(*(fifos.fifo7),*(fifos.fifo8));
    if (nodes.mfcc==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    identifiedNodes[AUDIOMARK_MFCC_ID]=(void*)nodes.mfcc;
    nodes.mfcc->setID(AUDIOMARK_MFCC_ID);
    nodes.mfccWin = new SlidingBuffer<int8_t,490,480>(*(fifos.fifo8),*(fifos.fifo9));
    if (nodes.mfccWin==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.result = new Result<int8_t,12>(*(fifos.fifo10));
    if (nodes.result==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    identifiedNodes[AUDIOMARK_RESULT_ID]=(void*)nodes.result;
    nodes.result->setID(AUDIOMARK_RESULT_ID);
    nodes.right = new Source<int16_t,256>(*(fifos.fifo1),right_microphone_capture);
    if (nodes.right==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    identifiedNodes[AUDIOMARK_RIGHT_ID]=(void*)nodes.right;
    nodes.right->setID(AUDIOMARK_RIGHT_ID);
    nodes.speaker = new Source<int16_t,256>(*(fifos.fifo11),downlink_audio);
    if (nodes.speaker==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    identifiedNodes[AUDIOMARK_SPEAKER_ID]=(void*)nodes.speaker;
    nodes.speaker->setID(AUDIOMARK_SPEAKER_ID);

    return(CG_SUCCESS);

}

void free_scheduler(int iterations,
                              const int16_t *left_microphone_capture,
                              const int16_t *right_microphone_capture,
                              const int16_t *downlink_audio)
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
    if (nodes.speaker!=NULL)
    {
        delete nodes.speaker;
    }
}


CG_BEFORE_SCHEDULER_FUNCTION
uint32_t scheduler(int *error,int iterations,
                              const int16_t *left_microphone_capture,
                              const int16_t *right_microphone_capture,
                              const int16_t *downlink_audio)
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
        for(unsigned long id=0 ; id < 65; id++)
        {
            CG_BEFORE_NODE_EXECUTION(schedule[id]);

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
                   cgStaticError = nodes.audioWin->run();
                }
                break;

                case 4:
                {
                   cgStaticError = nodes.dsnn->run();
                }
                break;

                case 5:
                {
                   cgStaticError = nodes.dup0->run();
                }
                break;

                case 6:
                {
                   cgStaticError = nodes.left->run();
                }
                break;

                case 7:
                {
                   cgStaticError = nodes.mfcc->run();
                }
                break;

                case 8:
                {
                   cgStaticError = nodes.mfccWin->run();
                }
                break;

                case 9:
                {
                   cgStaticError = nodes.result->run();
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

                case 12:
                {
                   
                  {

                   int16_t* i0;
                   int16_t* i1;
                   int16_t* o2;
                   i0=fifos.fifo0->getReadBuffer(256);
                   i1=fifos.fifo12->getReadBuffer(256);
                   o2=fifos.fifo2->getWriteBuffer(256);
                   th_add_q15(i0,i1,o2,256);
                   cgStaticError = 0;
                  }
                }
                break;

                case 13:
                {
                   
                  {

                   int16_t* i0;
                   int16_t* i1;
                   int16_t* o2;
                   i0=fifos.fifo1->getReadBuffer(256);
                   i1=fifos.fifo13->getReadBuffer(256);
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
