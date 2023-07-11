#pragma once 
extern "C" {
    extern int ds_cnn_s_s8_get_buffer_size(void);
}

template<typename IN, int inputSize,
         typename OUT, int outputSize>
class DSNN;

template<int inputSize>
class DSNN<int8_t,inputSize,
           int8_t,OUT_DIM>: 
public GenericNode<int8_t, inputSize,
                   int8_t,OUT_DIM>, public AudioMarkNode
{
public:
    DSNN(FIFOBase<int8_t> &src,FIFOBase<int8_t> &dst,int testMode=0):
    GenericNode<int8_t,inputSize,
                int8_t,OUT_DIM>(src,dst),AudioMarkNode(),mTestMode(testMode){
        th_nn_init();
        //printf(" kws = %d\n", 0);
        nbNNRun = 0;
        inferences = 0;
    };

    ~DSNN()
    {
        th_nn_free();
    }

    int getNbInferences() const
    {
       return(inferences);
    }

    int getMemoryUsage() final 
    {
        return(sizeof(*this)+ds_cnn_s_s8_get_buffer_size());
    }

    int prepareForRunning() final
    {
        if (this->willUnderflow() || 
            this->willOverflow()
           )
        {
           return(CG_SKIP_EXECUTION_ID_CODE); // Skip execution
        }

        return(0);
    };

    int run () final
    {
        int8_t *p_mfcc_fifo=this->getReadBuffer();
        int8_t *prediction=this->getWriteBuffer();

        if ((!mTestMode) || (nbNNRun>=1))
        {
          ee_status_t status = th_nn_classify(p_mfcc_fifo, prediction);
          inferences ++;

        }

    
        nbNNRun++;

        return(0);
    };
protected:
    int mTestMode;
    int nbNNRun;
    int inferences;
};
