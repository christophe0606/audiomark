from cmsis_stream.cg.scheduler import *

MFCC_OUTSIDE= True
### Define new types of Nodes 

class ABF(GenericNode):
    def __init__(self,name,ioLength):
        GenericNode.__init__(self,name)
        self.addInput("l",CType(SINT16),ioLength)
        self.addInput("r",CType(SINT16),ioLength)
        self.addOutput("o",CType(SINT16),ioLength)

    @property
    def typeName(self):
        return "ABF"

class AEC(GenericNode):
    def __init__(self,name,ioLength):
        GenericNode.__init__(self,name)
        self.addInput("s",CType(SINT16),ioLength)
        self.addInput("i",CType(SINT16),ioLength)
        self.addOutput("o",CType(SINT16),ioLength)

    @property
    def typeName(self):
        return "AEC"

class ANR(GenericNode):
    def __init__(self,name,ioLength):
        GenericNode.__init__(self,name)
        self.addInput("i",CType(SINT16),ioLength)
        self.addOutput("o",CType(SINT16),ioLength)

    @property
    def typeName(self):
        return "ANR"

class MFCC(GenericNode):
    def __init__(self,name,inLength,outLength):
        GenericNode.__init__(self,name)
        self.addInput("i",CType(SINT16),inLength)
        self.addOutput("o",CType(SINT8),outLength)

    @property
    def typeName(self):
        return "MFCC"

class DSNN(GenericSink):
    def __init__(self,name,inLength):
        GenericSink.__init__(self,name)
        if MFCC_OUTSIDE:
           self.addInput("i",CType(SINT8),inLength)
        else:
           self.addInput("i",CType(SINT16),inLength)

    @property
    def typeName(self):
        return "DSNN"

class Source(GenericSource):
    def __init__(self,name,inLength):
        GenericSource.__init__(self,name)
        self.addOutput("o",CType(SINT16),inLength)

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

left=Source("left",NB)
right=Source("right",NB)
speaker=Source("speaker",NB)


addl = Binary("arm_add_q15",CType(SINT16),NB,input_names=["l","s"])
addr = Binary("arm_add_q15",CType(SINT16),NB,input_names=["r","s"])

abf=ABF("abf",NB)
aec=AEC("aec",NB)
anr=ANR("anr",NB)

mfcc=MFCC("mfcc",NB_WINDOW_SAMPLES,MFCC_FEATURES)

sliding=SlidingBuffer("audioWin",CType(SINT16),NB_WINDOW_SAMPLES,NB_OVERLAP_SAMPLES)

if MFCC_OUTSIDE:
    dsnn=DSNN("dsnn",MFCC_FEATURES*NN_FEATURES)
else:
   dsnn=DSNN("dsnn",NB_OVERLAP_SAMPLES*NN_FEATURES)


g = Graph()

g.connect(left.o,addl.l)
g.connect(speaker.o,addl.s)

g.connect(right.o,addr.r)
g.connect(speaker.o,addr.s)

g.connect(addl.o,abf.l)
g.connect(addr.o,abf.r)

g.connect(speaker.o,aec.s)
g.connect(abf.o,aec.i)

g.connect(aec.o,anr.i)

if MFCC_OUTSIDE:
   g.connect(anr.o,sliding.i)
   g.connect(sliding.o,mfcc.i)
   g.connect(mfcc.o,dsnn.i)
else:
   g.connect(anr.o,dsnn.i)



print("Generate graphviz and code")

conf=Configuration()
conf.debugLimit=1
conf.cOptionalArgs=[]
#conf.memoryOptimization=True
conf.heapAllocation = True

generateGenericNodes(".")
generateCGStatus(".")

with open("pre_schedule_audiomark.dot","w") as f:
    g.graphviz(f)

sched = g.computeSchedule(config=conf)

print("Schedule length = %d" % sched.scheduleLength)
print("Memory usage %d bytes" % sched.memory)

sched.ccode(".",conf)

with open("audiomark.dot","w") as f:
    sched.graphviz(f)

