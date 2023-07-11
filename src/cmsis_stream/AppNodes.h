/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        AppNodes.h
 * Description:  Application nodes for Example 1
 *
 * Target Processor: Cortex-M and Cortex-A cores
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2021-2023 ARM Limited or its affiliates. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef _APPNODES_H_
#define _APPNODES_H_

extern "C" {
#include "ee_audiomark.h"
#include "ee_abf_f32.h"
#include "ee_kws.h"
#include "ee_mfcc_f32.h"
}

#include "SlidingBuffer.h"



class AudioMarkNode
{
public:
    virtual int getMemoryUsage()=0;    
};


extern "C" {
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "speex_preprocess.h"
#include "arch.h"
#include "speex_echo.h"

#include "os_support_custom.h"
}

#include "Source.hpp"
#include "ABF.hpp"
#include "AEC.hpp"
#include "ANR.hpp"
#include "MFCC.hpp"
#include "DSNN.hpp"
#include "Result.hpp"


#endif