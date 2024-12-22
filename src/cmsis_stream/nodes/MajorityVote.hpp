#pragma once

template<typename IN, int inputSize,
         typename OUT1,int outputSize1,
         typename OUT2,int outputSize2>
class MajorityVote;

template<int inputSize,int outputSize>
class MajorityVote<uint8_t,inputSize,
                   float,2,
                   uint8_t,outputSize>: 
public NodeBase, public AudioMarkNode
{
public:
    MajorityVote(FIFOBase<uint8_t> &src,
              FIFOBase<float> &dst1,
              FIFOBase<uint8_t> &dst2):
    mSrc(src),mDst1(dst1),mDst2(dst2),AudioMarkNode(){
     nb = 0;
     clock = 0;
     last = 0;
     hist.reserve(OUT_DIM);
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
        
        uint8_t *pred=this->getReadBuffer();
        uint8_t *dst=this->getWriteBufferText();
        float *d=this->getWriteBufferDuration();

        const char output_class[OUT_DIM][outputSize+1]
            = { "Silence ", "Unknown ", "yes     ", "no      ",  "up      ", "down    ",
                "left    ", "right   ", "on      ", "off     ",  "stop    ", "go      " };
        
        d[0] = 0.0;

        memset(dst,' ',outputSize);

        hist.clear();
        for(int i=0;i<OUT_DIM;i++)
        {
            hist[i]=0;
        }

        for(int i=0;i<inputSize;i++)
        {
            hist[pred[i]]++;
        }

        int m,idx;
        m=0;
        idx=0;
        for(int i=0;i<OUT_DIM;i++)
        {
            if (hist[i]>m)
            {
                idx=i;
                m = hist[i];
            }
        }

        

        if ((idx!=last) && (idx!=0) && (idx!=1))
        {
          strcpy((char*)dst,output_class[idx]);
          d[0]=300;
          d[1] = (unsigned long)(330.0*1000/16000*clock);
        }

        last=idx;
        

        clock++;


        return(0);
    };

protected:
    std::vector<uint8_t> hist;
    int last;
    int nb;
    unsigned long clock;

     uint8_t * getWriteBufferText(int nb=outputSize) {return mDst2.getWriteBuffer(nb);};
     float * getWriteBufferDuration(int nb=2) {return mDst1.getWriteBuffer(nb);};

     uint8_t * getReadBuffer(int nb=inputSize) {return mSrc.getReadBuffer(nb);};

     bool willOverflowText(int nb = outputSize) const {return mDst2.willOverflowWith(nb);};
     bool willOverflowDuration(int nb = 2) const {return mDst1.willOverflowWith(nb);};

     bool willUnderflow(int nb = inputSize) const {return mSrc.willUnderflowWith(nb);};


private:
    FIFOBase<uint8_t> &mSrc;
    FIFOBase<float> &mDst1;
    FIFOBase<uint8_t> &mDst2;

};
