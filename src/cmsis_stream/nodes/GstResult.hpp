#pragma once

template<typename IN, int inputSize,
         typename OUT1,int outputSize1,
         typename OUT2,int outputSize2>
class GstResult;

template<int outputSize>
class GstResult<int8_t,OUT_DIM,
                float,2,
                uint8_t,outputSize>: 
public NodeBase, public AudioMarkNode
{
public:
    GstResult(FIFOBase<int8_t> &src,
              FIFOBase<float> &dst1,
              FIFOBase<uint8_t> &dst2):
    mSrc(src),mDst1(dst1),mDst2(dst2),AudioMarkNode(){
     nb = 0;
     clock = 0;
     last = 0;
    };

   
    int getMemoryUsage() final 
    {
        return(0);
    }

    int prepareForRunning() final
    {
        if (this->willUnderflow() || 
            this->willOverflowText() ||
            this->willOverflowDuration()
            )
        {
           return(CG_SKIP_EXECUTION_ID_CODE); // Skip execution
        }

        return(0);
    };
    
    int run() final{
        
        int8_t *p_prediction=this->getReadBuffer();
        uint8_t *dst=this->getWriteBufferText();
        float *d=this->getWriteBufferDuration();

        const char output_class[OUT_DIM][9]
            = { "Silence ", "Unknown ", "yes     ", "no      ",  "up      ", "down    ",
                "left    ", "right   ", "on      ", "off     ",  "stop    ", "go      " };
        
        d[0] = 0.0;

        memset(dst,' ',outputSize);

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

        if ((max_ind!=last) && (max_ind!=0) && (max_ind!=1))
        {
          strcpy((char*)dst,output_class[max_ind]);
          d[0]=300;
          d[1] = (unsigned long)(320.0*1000/16000*clock);
        }

        last=max_ind;
        

        clock++;


        return(0);
    };

protected:
    int last;
    int nb;
    unsigned long clock;

     uint8_t * getWriteBufferText(int nb=outputSize) {return mDst2.getWriteBuffer(nb);};
     float * getWriteBufferDuration(int nb=2) {return mDst1.getWriteBuffer(nb);};

     int8_t * getReadBuffer(int nb=OUT_DIM) {return mSrc.getReadBuffer(nb);};

     bool willOverflowText(int nb = outputSize) const {return mDst2.willOverflowWith(nb);};
     bool willOverflowDuration(int nb = 2) const {return mDst1.willOverflowWith(nb);};

     bool willUnderflow(int nb = OUT_DIM) const {return mSrc.willUnderflowWith(nb);};


private:
    FIFOBase<int8_t> &mSrc;
    FIFOBase<float> &mDst1;
    FIFOBase<uint8_t> &mDst2;

};
