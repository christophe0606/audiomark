#pragma once

template<typename IN, int inputSize,
         typename OUT,int outputSize>
class GstResult;

template<int inputSize>
class GstResult<int8_t,inputSize, 
                uint8_t,1>: 
public GenericNode<int8_t,inputSize,
                 uint8_t,1>, public AudioMarkNode
{
public:
    GstResult(FIFOBase<int8_t> &src,
           FIFOBase<uint8_t> &dst):
    GenericNode<int8_t,inputSize,
                uint8_t,1>(src,dst),AudioMarkNode(){
    
     
    };

   
    int getMemoryUsage() final 
    {
        return(0);
    }

    int prepareForRunning() final
    {
        if (this->willUnderflow() ||
            this->willOverflow())
        {
           return(CG_SKIP_EXECUTION_ID_CODE); // Skip execution
        }

        return(0);
    };
    
    int run() final{
        
        int8_t *p_prediction=this->getReadBuffer();
        uint8_t *o=this->getWriteBuffer();
      

        int max_ind = 0;
        int max_val = -128000;
        for (int i = 0; i < OUT_DIM; i++)
        {
            if (max_val < p_prediction[i])
            {
                max_val = p_prediction[i];
                max_ind = i;
            }
        }
        o[0] = (uint8_t)max_ind;
        

        return(0);
    };


};
