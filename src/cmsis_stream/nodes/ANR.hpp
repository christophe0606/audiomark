#pragma once

extern "C" {
    extern SpeexPreprocessState *ee_anr_init_f32();
    extern void ee_anr_free_f32(SpeexPreprocessState *p);

}

template<typename IN, int inputSize,
         typename OUT,int outputSize>
class ANR;

template<int nbSamples>
class ANR<int16_t,nbSamples,
          int16_t,nbSamples>: public GenericNode<int16_t,nbSamples,
                                                 int16_t,nbSamples>, public AudioMarkNode
{
public:
    ANR(FIFOBase<int16_t> &src,
        FIFOBase<int16_t> &dst):
    GenericNode<int16_t,nbSamples,
                int16_t,nbSamples>(src,dst),AudioMarkNode(){
    
      reset_speex_memory_stats();
      p_state = ee_anr_init_f32();
      mSize = get_speex_allocated_memory();

    };

    ~ANR()
    {
        ee_anr_free_f32(p_state);
    }

    int getMemoryUsage() final 
    {
        return(sizeof(*this)+mSize);
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
        int32_t ret = 0;

        int16_t *in=this->getReadBuffer();
        int16_t *p_in_place_buffer=this->getWriteBuffer();

        memcpy(p_in_place_buffer,in,sizeof(int16_t)*nbSamples);

        speex_preprocess_run(p_state, p_in_place_buffer);

        return(ret);
    };

protected:
    SpeexPreprocessState *p_state;
    int mSize;
};