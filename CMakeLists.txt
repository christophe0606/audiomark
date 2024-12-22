cmake_minimum_required(VERSION 3.14)
project(audiomark
	DESCRIPTION "Firmware for the AudioMark Self-Hosted Benchmark"
	VERSION 1.0.0)

set(CMAKE_C_FLAGS "-O2")
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_C_STANDARD 11)

include_directories(lib/speexdsp)
include_directories(lib/speexdsp/include)
include_directories(lib/speexdsp/include/speex)
include_directories(lib/speexdsp/libspeexdsp)
include_directories(src)
include_directories(src/cmsis_stream)
include_directories(../CMSIS-Stream/Include/cg/nodes/cpp/)

if(DEFINED PORT_DIR)
	include(${PORT_DIR}/port.cmake)
else()
	message(FATAL_ERROR "Please define PORT_DIR, e.g. -DPORT_DIR=<path>")
endif()

if(DEFINED CMSIS_STREAM_DIR)
	include_directories(${CMSIS_STREAM_DIR}/Include/cg/nodes/cpp/)
else()
	message(FATAL_ERROR "Please define CMSIS_STREAM_DIR, e.g. -DCMSIS_STREAM_DIR=<path>")
endif()

# For Xiph we are using Float, never Fixed
add_definitions(-DFLOATING_POINT)
# This macro is used extensively in LibSpeeX for function visibility.
add_definitions(-DEXPORT=)
# Benchmark system integrator provides heap
add_definitions(-DOS_SUPPORT_CUSTOM)
add_definitions(-D__RESTRICT=)
add_definitions(-DOVERRIDE_SPEEX_ALLOC)

#add_definitions(-DDEBUG_PRINTF_CLASSES)

set(EE_SOURCE
	# Note: main.c is just for self-hosted testing
	src/cmsis_stream/scheduler.cpp

	src/ee_aec_f32.c
	src/ee_anr_f32.c
	src/ee_abf_f32.c
	src/ee_abf_f32_tables.c
	src/ee_mfcc_f32.c
	src/ee_mfcc_f32_tables.c

	lib/speexdsp/libspeexdsp/speex_memory_stats.c

	lib/speexdsp/libspeexdsp/buffer.c
	lib/speexdsp/libspeexdsp/fftwrap.c
	lib/speexdsp/libspeexdsp/filterbank.c
	lib/speexdsp/libspeexdsp/jitter.c
	lib/speexdsp/libspeexdsp/kiss_fft.c
	lib/speexdsp/libspeexdsp/kiss_fftr.c
	lib/speexdsp/libspeexdsp/mdf.c
	lib/speexdsp/libspeexdsp/preprocess.c
	lib/speexdsp/libspeexdsp/resample.c
	lib/speexdsp/libspeexdsp/scal.c
	lib/speexdsp/libspeexdsp/smallft.c
)

set(TH_SOURCE
	# This is essentially an include needed in th_api.c
	src/ee_nn_tables.c
	src/ee_abf_f32_tables.c

	${PORT_SOURCE}
)

set(TEST_AEC_F32_SOURCE
	src/ee_aec_f32.c
	lib/speexdsp/libspeexdsp/speex_memory_stats.c
	lib/speexdsp/libspeexdsp/buffer.c
	lib/speexdsp/libspeexdsp/fftwrap.c
	lib/speexdsp/libspeexdsp/filterbank.c
	lib/speexdsp/libspeexdsp/jitter.c
	lib/speexdsp/libspeexdsp/kiss_fft.c
	lib/speexdsp/libspeexdsp/kiss_fftr.c
	lib/speexdsp/libspeexdsp/mdf.c
	lib/speexdsp/libspeexdsp/preprocess.c
	lib/speexdsp/libspeexdsp/resample.c
	lib/speexdsp/libspeexdsp/scal.c
	lib/speexdsp/libspeexdsp/smallft.c
	${TH_SOURCE}
	tests/data/aec_f32_input_source.c
	tests/data/aec_f32_input_echo.c
	tests/data/aec_f32_expected.c
	tests/test_aec_f32.cpp
)
#add_executable(test_aec_f32 ${TEST_AEC_F32_SOURCE})

set(TEST_ANR_F32_SOURCE
	src/ee_anr_f32.c
	lib/speexdsp/libspeexdsp/speex_memory_stats.c
	lib/speexdsp/libspeexdsp/buffer.c
	lib/speexdsp/libspeexdsp/fftwrap.c
	lib/speexdsp/libspeexdsp/filterbank.c
	lib/speexdsp/libspeexdsp/jitter.c
	lib/speexdsp/libspeexdsp/kiss_fft.c
	lib/speexdsp/libspeexdsp/kiss_fftr.c
	lib/speexdsp/libspeexdsp/mdf.c
	lib/speexdsp/libspeexdsp/preprocess.c
	lib/speexdsp/libspeexdsp/resample.c
	lib/speexdsp/libspeexdsp/scal.c
	lib/speexdsp/libspeexdsp/smallft.c
	${TH_SOURCE}
	tests/data/anr_f32_input.c
	tests/data/anr_f32_expected.c
	tests/test_anr_f32.cpp
)
#add_executable(test_anr_f32 ${TEST_ANR_F32_SOURCE})


set(TEST_ABF_F32_SOURCE
	src/ee_abf_f32.c
	${TH_SOURCE}
	tests/data/abf_f32_input_ch1.c
	tests/data/abf_f32_input_ch2.c
	tests/data/abf_f32_expected.c
	tests/test_abf_f32.cpp
)
#add_executable(test_abf_f32 ${TEST_ABF_F32_SOURCE})

set(TEST_MFCC_F32_SOURCE
	src/ee_mfcc_f32.c
	src/ee_mfcc_f32_tables.c
	${TH_SOURCE}
	tests/data/mfcc_f32_all.c
	tests/test_mfcc_f32.cpp
)
#add_executable(test_mfcc_f32 ${TEST_MFCC_F32_SOURCE})

set(TEST_KWS_SOURCE
	src/ee_mfcc_f32.c
	src/ee_mfcc_f32_tables.c
	${TH_SOURCE}
	tests/test_kws.cpp
	tests/test_scheduler.cpp
	tests/data/kws_input.c
	tests/data/kws_expected.c
)
#add_executable(test_kws ${TEST_KWS_SOURCE})
#target_include_directories(test_kws PUBLIC tests)

#add_executable(audiomark ${EE_SOURCE} ${TH_SOURCE})
add_library(network SHARED ${EE_SOURCE} ${TH_SOURCE})
target_include_directories(network PUBLIC ${GST}/cpp_nodes)
target_include_directories(network PUBLIC ${GST}/include)
target_compile_definitions(network PUBLIC GST)

if(CMAKE_C_COMPILER_ID MATCHES "MSVC")
else()
	target_link_libraries(network m)
endif()

