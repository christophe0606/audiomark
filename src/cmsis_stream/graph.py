from cmsis_stream.cg.scheduler import *

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

class DSNN(GenericNode):
    def __init__(self,name,inLength):
        GenericNode.__init__(self,name)
        self.addInput("i",CType(SINT8),inLength)
        self.addOutput("o",CType(SINT8),12)
        
    @property
    def typeName(self):
        return "DSNN"

class Result(GenericSink):
    def __init__(self,name):
        GenericSink.__init__(self,name)
        self.addInput("i",CType(SINT8),12)
        
    @property
    def typeName(self):
        return "Result"

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

left=Source("left",NB,"left_microphone_capture")
right=Source("right",NB,"right_microphone_capture")
speaker=Source("speaker",NB,"downlink_audio")


addl = Binary("th_add_q15",CType(SINT16),NB,input_names=["l","s"])
addr = Binary("th_add_q15",CType(SINT16),NB,input_names=["r","s"])

abf=ABF("abf",NB)
aec=AEC("aec",NB)
anr=ANR("anr",NB)

mfcc=MFCC("mfcc",NB_WINDOW_SAMPLES,MFCC_FEATURES)

audioWin=SlidingBuffer("audioWin",CType(SINT16),NB_WINDOW_SAMPLES,NB_OVERLAP_SAMPLES)
mfccWin=SlidingBuffer("mfccWin",CType(SINT8),MFCC_FEATURES*NN_FEATURES,MFCC_FEATURES*(NN_FEATURES-1))

audioWin.identified=False 
mfccWin.identified=False 

dsnn=DSNN("dsnn",MFCC_FEATURES*NN_FEATURES)
result=Result("result")


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

g.connect(anr.o,audioWin.i)
g.connect(audioWin.o,mfcc.i)
g.connect(mfcc.o,mfccWin.i)
g.connect(mfccWin.o,dsnn.i)
g.connect(dsnn.o,result.i)



print("Generate graphviz and code")

conf=Configuration()
conf.debugLimit=1
conf.cOptionalArgs=["int iterations",
                    "const int16_t *left_microphone_capture",
                    "const int16_t *right_microphone_capture",
                    "const int16_t *downlink_audio"]
#conf.memoryOptimization=True
conf.heapAllocation = True
conf.nodeIdentification = True
conf.prefix="audiomark_"

generateGenericNodes(".")
generateCGStatus(".")

with open("pre_schedule_audiomark.dot","w") as f:
    g.graphviz(f)

sched = g.computeSchedule(config=conf)

print("Schedule length = %d" % sched.scheduleLength)
print("Memory usage %d bytes" % sched.memory)

sched.ccode(".",conf)


# Style for KWS nodes in original demo
class MyStyle(Style):
    ############################
    #
    # NORMAL NODE CUSTOMIZATION
    #

    def node_color(self,node):
       
        kwsColor = "aquamarine"
        missingColor = "gray83"
        normal = "lightskyblue"

        if node.nodeName=="audioWin":
           return(kwsColor)
        if node.nodeName=="mfccWin":
           return(kwsColor)
        if node.nodeName=="mfcc":
           return(kwsColor)
        if node.nodeName=="dsnn":
           return(kwsColor)
        if node.nodeName=="result":
           return(kwsColor)

        if node.nodeName=="left":
           return(missingColor)
        if node.nodeName=="right":
           return(missingColor)
        if node.nodeName=="speaker":
           return(missingColor)

        if node.nodeName=="th_add_q15":
           return(missingColor)
        
        return(normal)

myStyle = MyStyle()

with open("audiomark.dot","w") as f:
    sched.graphviz(f,style=myStyle)

