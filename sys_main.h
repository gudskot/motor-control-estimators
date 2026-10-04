//##############################################################################
// $Copyright:
// Copyright (C) 2017-2025 Texas Instruments Incorporated - http://www.ti.com/
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
 
#ifndef SYS_MAIN_H
#define SYS_MAIN_H

//**************************************************************************
//! \file  solutions/universal_motorcontrol_lab/common/include/sys_main.h
//! \brief  header file to be included in all labs
//!
//**************************************************************************

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

//*****************************************************************************
//
//! \defgroup SYS MAIN
//! @{
//
//*****************************************************************************
// modules
#ifdef __TMS320C28XX_CLA__
#include "libraries/math/include/CLAmath.h"
#else
#include <math.h>
#include "libraries/math/include/math.h"
#endif

#include "user.h"
#include "src_board/hal.h"


#include "motor_common.h"
#include "motor1_drive.h"

#include "cpu_time.h"

// #include "controlparameters.h"
// #include "systemcontrol.h"

#define LED_BLINK_FREQ_Hz           (0.5f)       // 1Hz
#define POWER_RELAY_WAIT_TIME_ms    (1000)       // 1s
#define OFFSET_CHECK_WAIT_TIME_ms   (1000)          // 1s
#define POWER_RELAY_ON_VOLTAGE_V    (0.20f * USER_M1_ADC_FULL_SCALE_VOLTAGE_V)        // 100V

//
//! \brief typedefs for the fault
//
typedef struct _FAULT_SYS_BITS_
{             // bits  description
    uint16_t hardware:1;            // 0  Hardware failed
    uint16_t communication:1;       // 1  communication
    uint16_t temperature:1;         // 2  temperature
    uint16_t voltage:1;             // 3  voltage

    uint16_t motorStartFailed:1;    // 4  Motor startup failed
    uint16_t motorRunFailed:1;      // 5  Motor run failed
    uint16_t motorOverCurrent:1;    // 6  Motor over current
    uint16_t reserve7:1;            // 7  Reserve

    uint16_t reserve8:1;            // 8  Reserve
    uint16_t reserve9:1;            // 9  Reserve
    uint16_t reserve10:1;           // 10  Reserve
    uint16_t reserve11:1;           // 11 Reserve

    uint16_t reserve12:1;           // 12 Reserve
    uint16_t reserve13:1;           // 13 Reserve
    uint16_t reserve14:1;           // 14 Reserve
    uint16_t reserve15:1;           // 15 Reserve
} FAULT_SYS_BITS;

typedef union _FAULT_SYS_t
{
    uint16_t        all;
    FAULT_SYS_BITS  bit;
}FAULT_SYS_t;

//------------------------------------------------------------------------
typedef struct _SYSTEM_Vars_t_
{
    float32_t speedRef_Hz;
    uint32_t mainLoopCnt;
    uint32_t timerCnt_1min;

    uint16_t timerBase_1ms;
    uint16_t timerCnt_5ms;
    uint16_t timerCnt_1s;

    uint16_t powerRelayWaitTime_ms;

    uint16_t counterLEDC;       //!< Counter used to divide down a timer base for
                                //!< visually blinking an LED

    uint16_t counterLEDB;       //!< Counter used to divide down a timer base for
                                //!< visually blinking an LED

    uint16_t timeWaitLEDB;      //

    uint16_t            estLibVersion;
    EST_Type_e          estType;
    FASTLIB_Type_e      fastType;
    CURRENTSEN_Type_e   currentSenseType;

    uint16_t waitTimeCntLEDS;       //!< LEDS blink time counter
    uint16_t waitTimeSetLEDS;       //!< LEDS blink wait time settings
    uint16_t delayTimeSetLEDS;      //!< LEDS blink cycle delay time settings
    uint16_t blinkStatusLEDS;       //!< LEDs blink status
    uint16_t blinkTimesSetLEDS;     //!< LEDS blinking times settings
    uint16_t blinkTimesCntLEDS;     //!< LEDS blinking times counter
    uint16_t faultViewDelayTimeCnt;
    uint16_t faultComDelayTimeCnt;

    FAULT_SYS_t faultSysUse;
    FAULT_SYS_t faultSysView;
    FAULT_SYS_t faultSysCom;

    bool flagEnableSystem;
}SYSTEM_Vars_t;

extern volatile SYSTEM_Vars_t systemVars;




extern CPU_TIME_Obj     cpuTime;
extern CPU_TIME_Handle  cpuTimeHandle;

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif // extern "C"

#endif // end of SYS_MAIN_H definition
