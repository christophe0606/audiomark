#pragma once

extern "C" {
    extern int ee_mfcc_f32_memory_usage();
}

template<typename IN, int inputSize,
         typename OUT,int outputSize>
class MFCC;

template<int inputSize, int outputSize>
class MFCC<int16_t,inputSize,
          int8_t,outputSize>: public GenericNode<int16_t,inputSize,
                                                 int8_t,outputSize>, public AudioMarkNode
{
public:
    MFCC(FIFOBase<int16_t> &src,
        FIFOBase<int8_t> &dst,int testMode=0):
    GenericNode<int16_t,inputSize,
                int8_t,outputSize>(src,dst),AudioMarkNode(),mTestMode(testMode){
    
     
    ee_status_t status = ee_mfcc_f32_init(&p_mfcc);
    nbMfccRun=0;
    };

   
    int getMemoryUsage() final 
    {
        return(sizeof(*this));
    }

    int prepareForRunning() final
    {
        if (this->willOverflow() ||
            this->willUnderflow()
           )
        {
           return(CG_SKIP_EXECUTION_ID_CODE); // Skip execution
        }

        return(0);
    };
    
    int run() final{
        
        int16_t *in=this->getReadBuffer();
        int8_t *out=this->getWriteBuffer();

        // In test mode, first iteration is doing nothing.
        // We are just filling the sliding audio buffer
        if ((!mTestMode) || (nbMfccRun>=1))
        {
           ee_mfcc_f32_compute(&p_mfcc,in,out);
        }

        
        nbMfccRun++;

        return(0);
    };

protected:
mfcc_instance_t p_mfcc;
int mTestMode;
int nbMfccRun;
};