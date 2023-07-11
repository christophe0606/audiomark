#pragma once

extern "C" {
    extern void beamformer_f32_reset(abf_f32_instance_t *p_inst);
    extern void beamformer_f32_run(abf_f32_instance_t *p_inst,
                            int16_t            *input_buffer_left,
                            int16_t            *input_buffer_right,
                            int32_t             input_buffer_size,
                            int16_t            *output_buffer,
                            int32_t            *input_samples_consumed,
                            int32_t            *output_samples_produced,
                            int32_t            *returned_state);
    extern int ee_abf_f32_memory_usage();
}

template<typename IN1, int inputSize1,
         typename IN2, int inputSize2,
         typename OUT,int outputSize>
class ABF;

template<int nbSamples>
class ABF<int16_t,nbSamples,
          int16_t,nbSamples,
          int16_t,nbSamples>: public GenericNode21<int16_t,nbSamples,
                                                   int16_t,nbSamples,
                                                   int16_t,nbSamples>, public AudioMarkNode
{
public:
    ABF(FIFOBase<int16_t> &src1,
        FIFOBase<int16_t> &src2,
        FIFOBase<int16_t> &dst):
    GenericNode21<int16_t,nbSamples,
                int16_t,nbSamples,
                int16_t,nbSamples>(src1,src2,dst),AudioMarkNode(){
    

       p_abf_f32_instance = ee_abf_f32_init();

       //printf(" bmf = %d\n", size);

       beamformer_f32_reset(p_abf_f32_instance);
    };

    ~ABF()
    {
        ee_abf_f32_free(p_abf_f32_instance);
    }

    int getMemoryUsage() final 
    {
        return(sizeof(*this)+ee_abf_f32_memory_usage());
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

        int16_t *inBufs1stChannel=this->getReadBuffer1();
        int16_t *inBufs2ndChannel=this->getReadBuffer2();
        int16_t *outBufs=this->getWriteBuffer();

        int32_t  input_samples_consumed;
        int32_t  output_samples_produced;

        beamformer_f32_run(p_abf_f32_instance,
                           inBufs1stChannel,
                           inBufs2ndChannel,
                           nbSamples,
                           outBufs,
                           &input_samples_consumed,
                           &output_samples_produced,
                           &ret);
        return(ret);
    };

protected:
    abf_f32_instance_t *p_abf_f32_instance;

};