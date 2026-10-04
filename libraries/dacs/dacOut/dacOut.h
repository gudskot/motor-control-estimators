//##############################################################################
// $Copyright:
// Copyright (C) 2017-2026 Texas Instruments Incorporated - http://www.ti.com/
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//   Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
//
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the
//   distribution.
//
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//##############################################################################

//------------------------------------------------------------------------------
//!
//! MotorControl SDK
//!
//! \file   \libraries\dacs\dacOut\include\dacOut.h
//! \brief  Contains public interface to various functions related
//!         to the dacOut object
//!
//------------------------------------------------------------------------------


#ifndef DACOUT_H_
#define DACOUT_H_

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

// the includes
#include <math.h>

// drivers
#include "device.h"

//
// the defines
//

//! \brief Defines the maximum DAC OUT channels
//!
#define DACOUT_NUM_MAXIMUM              (4U)

//! \brief Defines the enabled DAC OUT channels
//!
#define DACOUT_NUM_ENABLE               (2U)

#if DACOUT_NUM_ENABLE > DACOUT_NUM_MAXIMUM
#error The enabled channels must be less than or equal to the maximum channel
#endif

// **************************************************************************
// the typedefs

//! \brief Object for DAC OUT
//!
typedef struct _dacOut_Obj_
{
    volatile float32_t *dacOutPtrData[DACOUT_NUM_ENABLE];    //!< Input: First input pointer

    uint32_t   dacHandle[DACOUT_NUM_ENABLE];   //!< handle for the DAC peripheral interfaces

    float32_t   dacGain[DACOUT_NUM_ENABLE];
    uint16_t    dacOffset[DACOUT_NUM_ENABLE];

    uint16_t    dacData[DACOUT_NUM_ENABLE];
}dacOut_Obj;


//! \brief Defines the DAC OUT handle
//!
typedef struct dacOut_Obj *dacOut_Handle;

// **************************************************************************
// Prototypes:
extern dacOut_Handle DAC_OUT_init(void *pMemory);
void DAC_OUT_writeData(dacOut_Handle handle);


//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif // extern "C"

#endif // end of DACOUT_H_ definition
