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
//! \file   \libraries\dacs\dacOut\source\dacOut.c
//! \brief  Contains the various functions related to the dacOut object
//!
//------------------------------------------------------------------------------

#if defined(DAC_OUT_EN)

// the includes
#include "dacOut.h"

#if defined(SYSCONFIG_EN)
#include "board.h"
#endif  // SYSCONFIG_EN

dacOut_Handle DAC_OUT_init(void *pMemory)
{
    dacOut_Handle handle;
    dacOut_Obj *obj;

    // assign the handle
    handle = (dacOut_Handle)pMemory;
    obj = (dacOut_Obj *)handle;

#if defined(SYSCONFIG_EN)
    // assign the DAC handles
    obj->dacHandle[0] = MTR1_DAC_SITE1_BASE;
    obj->dacHandle[1] = MTR1_DAC_SITE2_BASE;
#else
#error Need to define dacHandles in dacOut.c function DAC_OUT_init().
#endif

    return(handle);
} // end of DAC128S_init() function

void DAC_OUT_writeData(dacOut_Handle handle)
{
    dacOut_Obj *obj = (dacOut_Obj *)handle;

    // dacVal = ((data * gain) + offset) & (uint16_t)0xFFF;
    obj->dacData[0] = ((int16_t)(*obj->dacOutPtrData[0] *
            obj->dacGain[0]) + obj->dacOffset[0]) & (uint16_t)0xFFF;
    obj->dacData[1] = ((int16_t)(*obj->dacOutPtrData[1] *
            obj->dacGain[1]) + obj->dacOffset[1]) & (uint16_t)0xFFF;


    DAC_setShadowValue(obj->dacHandle[0], obj->dacData[0]);
    DAC_setShadowValue(obj->dacHandle[1], obj->dacData[1]);
}


#endif // DAC128S_ENABLE

// end of file
