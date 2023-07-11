from cmsis_stream.cg.scheduler import *


class MFCC(GenericNode):
    def __init__(self,name,inLength,outLength,testMode):
        GenericNode.__init__(self,name)
        self.addInput("i",CType(SINT16),inLength)
        self.addOutput("o",CType(SINT8),outLength)
        self.addLiteralArg(testMode)

    @property
    def typeName(self):
        return "MFCC"

class DSNN(GenericNode):
    def __init__(self,name,inLength,testMode):
        GenericNode.__init__(self,name)
        self.addInput("i",CType(SINT8),inLength)
        self.addOutput("o",CType(SINT8),12)
        self.addLiteralArg(testMode)

        
    @property
    def typeName(self):
        return "DSNN"

class TestResult(GenericSink):
    def __init__(self,name,expected):
        GenericSink.__init__(self,name)
        self.addInput("i",CType(SINT8),12)
        self.addVariableArg(expected)
        
    @property
    def typeName(self):
        return "TestResult"

class Source(GenericSource):
    def __init__(self,name,inLength,buf):
        GenericSource.__init__(self,name)
        self.addOutput("o",CType(SINT16),inLength)
        self.addVariableArg(buf)

    @property
    def typeName(self):
        return "Source"


### Define nodes
SAMPLING_FREQ_HZ = 16000
AUDIO_PACKET_DURATION = 16 # ms 
OVERLAP_DURATION = 20 
WINDOWS_DURATION = 40 

NB_AUDIO_SAMPLES = int(1e-3 * AUDIO_PACKET_DURATION * SAMPLING_FREQ_HZ)
NB_OVERLAP_SAMPLES = int(1e-3 * OVERLAP_DURATION * SAMPLING_FREQ_HZ)
NB_WINDOW_SAMPLES = int(1e-3 * WINDOWS_DURATION * SAMPLING_FREQ_HZ)


NB = NB_AUDIO_SAMPLES
MFCC_FEATURES = 10
NN_FEATURES = 49

src=Source("src",NB,"p_input")


mfcc=MFCC("mfcc",NB_WINDOW_SAMPLES,MFCC_FEATURES,1)

audioWin=SlidingBuffer("audioWin",CType(SINT16),NB_WINDOW_SAMPLES,NB_OVERLAP_SAMPLES)
mfccWin=SlidingBuffer("mfccWin",CType(SINT8),MFCC_FEATURES*NN_FEATURES,MFCC_FEATURES*(NN_FEATURES-1))

dsnn=DSNN("dsnn",MFCC_FEATURES*NN_FEATURES,1)
test=TestResult("test","p_expected")


g = Graph()


g.connect(src.o,audioWin.i)
g.connect(audioWin.o,mfcc.i)
g.connect(mfcc.o,mfccWin.i)
g.connect(mfccWin.o,dsnn.i)
g.connect(dsnn.o,test.i)



print("Generate graphviz and code")

conf=Configuration()
conf.debugLimit=1
conf.cOptionalArgs=["int iterations",
                    "int testMode",
                    "const int16_t *p_input",
                    "const int8_t *p_expected"]
#conf.memoryOptimization=True
conf.heapAllocation = True

conf.customCName = "kws_test_custom.h"
conf.appNodesCName = "test_app_nodes.h"
conf.schedulerCFileName = "test_scheduler"
conf.schedName = "test_scheduler"
conf.nodeIdentification = True

generateGenericNodes(".")
generateCGStatus(".")

with open("pre_schedule_test_kws.dot","w") as f:
    g.graphviz(f)

sched = g.computeSchedule(config=conf)

print("Schedule length = %d" % sched.scheduleLength)
print("Memory usage %d bytes" % sched.memory)

sched.ccode(".",conf)

with open("test_kws.dot","w") as f:
    sched.graphviz(f)

