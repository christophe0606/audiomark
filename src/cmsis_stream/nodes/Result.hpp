#pragma once

template<typename IN, int inputSize>
class Result;

template<>
class Result<int8_t,OUT_DIM>: 
public GenericSink<int8_t,OUT_DIM>, public AudioMarkNode
{
public:
    Result(FIFOBase<int8_t> &src):
    GenericSink<int8_t,OUT_DIM>(src),AudioMarkNode(){
    
     
    };

   
    int getMemoryUsage() final 
    {
        return(0);
    }

    int prepareForRunning() final
    {
        if (this->willUnderflow())
        {
           return(CG_SKIP_EXECUTION_ID_CODE); // Skip execution
        }

        return(0);
    };
    
    int run() final{
        
        int8_t *p_prediction=this->getReadBuffer();

#ifdef DEBUG_PRINTF_CLASSES
        printf("OUTPUT: ");
        char output_class[OUT_DIM][8]
            = { "Silence", "Unknown", "yes", "no",  "up",   "down",
                "left",    "right",   "on",  "off", "stop", "go" };
        for (int i = 0; i < OUT_DIM; ++i)
        {
            printf("% 4d ", p_prediction[i]);
        }
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
        printf(" --> %8s (%3d%%)",
               output_class[max_ind],
               ((int)(p_prediction[max_ind] + 128) * 100 / 256));
        printf("\n");
#endif

        return(0);
    };


};
