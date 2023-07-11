#ifndef _TEST_APPNODES_H_
#define _TEST_APPNODES_H_

#include "AppNodes.h"

template<typename IN, int inputSize>
class TestResult;

template<>
class TestResult<int8_t,OUT_DIM>: 
public GenericSink<int8_t,OUT_DIM>
{
public:
    TestResult(FIFOBase<int8_t> &src,const int8_t* expected):
    GenericSink<int8_t,OUT_DIM>(src),p_expected(expected){
    
     idx_check = 0;
     nbTestRun = 0;
     inferences = 1;
    };

   
   
    int prepareForRunning() final
    {
        if (this->willUnderflow())
        {
           return(CG_SKIP_EXECUTION_ID_CODE); // Skip execution
        }

        return(0);
    };
    
    int run() final{
        

        int8_t *classes=this->getReadBuffer();

        const int8_t *p_check       = NULL;
        if (nbTestRun>0)
        {
            p_check = &p_expected[idx_check*OUT_DIM];
    
            for (int j = 0; j < OUT_DIM; ++j)
            {
                if (classes[j] != p_check[j])
                {
                    testError = 1;
                    printf("buffer[%d]class[%d]: Got %d, expected %d - FAIL\n",
                           inferences-1,
                           j,
                           classes[j],
                           p_check[j]);
                }
            }
    
            inferences++;
            ++idx_check;
        }
        nbTestRun ++;

        return(0);
    };

protected:
  int           idx_check;
  const int8_t* p_expected;
  int nbTestRun;
  int inferences;
};


#endif