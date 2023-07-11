#pragma once

template<typename OUT,int outputSize>
class Source: public GenericSource<OUT,outputSize>, public AudioMarkNode
{
public:
    Source(FIFOBase<OUT> &dst,const OUT *source):
    GenericSource<OUT,outputSize>(dst),AudioMarkNode(),mSource(source){
        mIndex=0;
    };

    int getMemoryUsage() final 
    {
        return(0);
    }

    int prepareForRunning() final
    {
        if (this->willOverflow()
           )
        {
           return(CG_SKIP_EXECUTION_ID_CODE); // Skip execution
        }

        return(0);
    };

    int run() final{
        OUT *b=this->getWriteBuffer();

        
        memcpy(b,mSource+mIndex,sizeof(OUT)*outputSize);
        mIndex += outputSize;
        if (mIndex >= NINPUT_SAMPLES)
        {
            mIndex = 0;
        }

        
        return(CG_SUCCESS);
    };

protected:
    const OUT *mSource;
    int mIndex;
};