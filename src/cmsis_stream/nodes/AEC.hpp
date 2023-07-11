#pragma once

extern "C" {

    extern SpeexEchoState *ee_aec_init_f32();
    extern void ee_aec_free_f32(SpeexEchoState *);

}



template<typename IN1, int inputSize1,
         typename IN2, int inputSize2,
         typename OUT, int outputSize>
class AEC;

template<int nbSamples>
class AEC<int16_t,nbSamples,
          int16_t,nbSamples,
          int16_t,nbSamples>: public GenericNode21<int16_t,nbSamples,
                                                   int16_t,nbSamples,
                                                   int16_t,nbSamples>, public AudioMarkNode
{
public:
    AEC(FIFOBase<int16_t> &src1,
        FIFOBase<int16_t> &src2,
        FIFOBase<int16_t> &dst):
    GenericNode21<int16_t,nbSamples,
                int16_t,nbSamples,
                int16_t,nbSamples>(src1,src2,dst),AudioMarkNode(){
    
     
      reset_speex_memory_stats();
      p_state = ee_aec_init_f32();
      mSize = get_speex_allocated_memory();

    };

    ~AEC()
    {
        ee_aec_free_f32(p_state);
    }

    int getMemoryUsage() final 
    {
        return(sizeof(*this)+mSize);
    }

    int prepareForRunning() final
    {
        if (this->willOverflow() ||
            this->willUnderflow1() ||
            this->willUnderflow2() 
           )
        {
           return(CG_SKIP_EXECUTION_ID_CODE); // Skip execution
        }

        return(0);
    };
    
    int run() final{
        int32_t ret = 0;

        int16_t *reference=this->getReadBuffer1();
        int16_t *echo=this->getReadBuffer2();
        int16_t *outBufs=this->getWriteBuffer();

        speex_echo_cancellation(p_state, reference, echo, outBufs);

        return(ret);
    };

protected:
    SpeexEchoState *p_state;
    int mSize;
};