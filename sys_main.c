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
 
//
//! \file   /solutions/universal_motorcontrol_lab/common/source/sys_main.c.c
//!
//! \brief  This project is used to implement motor control with FAST, eSMO
//!         Encoder, and Hall sensors based sensored/sensorless-FOC.
//!         Supports multiple TI EVM boards
//!
//
//
// include the related header files
//
#include "user.h"
#include "sys_settings.h"
#include "sys_main.h"
// #include "mcsdk_libraries.h"
// #include "signalsight/signalsight.h"

volatile SYSTEM_Vars_t systemVars;
#pragma DATA_SECTION(systemVars,"sys_data");

// define CPU time for performance test
CPU_TIME_Obj     cpuTime;
CPU_TIME_Handle  cpuTimeHandle;
#pragma DATA_SECTION(cpuTime,"sys_data");
#pragma DATA_SECTION(cpuTimeHandle,"sys_data");





// **************************************************************************
// the functions
// !!! Please make sure that you had gone through the user guide, and follow the
// !!! guide to set up the kit and load the right code
void main(void)
{
    
    // Clear memory for system and controller
    // The variables must be assigned to these sector if need to be cleared to zero
    HAL_clearDataRAM((void *)loadStart_est_data, (uint16_t)loadSize_est_data);
    HAL_clearDataRAM((void *)loadStart_user_data, (uint16_t)loadSize_user_data);
    HAL_clearDataRAM((void *)loadStart_hal_data, (uint16_t)loadSize_hal_data);
    HAL_clearDataRAM((void *)loadStart_foc_data, (uint16_t)loadSize_foc_data);
    HAL_clearDataRAM((void *)loadStart_sys_data, (uint16_t)loadSize_sys_data);

    HAL_clearDataRAM((void *)loadStart_ctrl_data, (uint16_t)loadSize_ctrl_data);
    HAL_clearDataRAM((void *)loadStart_datalog_data, (uint16_t)loadSize_datalog_data);
    HAL_clearDataRAM((void *)loadStart_SFRA_F32_Data, (uint16_t)loadSize_SFRA_F32_Data);


    systemVars.estType = EST_TYPE_FAST;         // the estimator is only FAST
    motorVars_M1.estimatorType = SLEST_TYPE_FAST_ONLY;
    motorVars_M1.estimatorMode = ESTIMATOR_MODE_FAST;

    systemVars.estLibVersion = EST_getFASTVersion();   // gets FAST version 

    systemVars.currentSenseType = CURSEN_TYPE_THREE_SHUNT;
    motorVars_M1.currentSenType = LSC_TYPE_THREE_SHUNT;
// ** above codes are only for checking the settings, not occupy the memory

    // Initialize device clock and peripherals
    Device_init();                  // call the function in device.c

    // Disable pin locks and enable internal pullups.
    Device_initGPIO();              // call the function in device.c

    // Initializes PIE and clears PIE registers. Disables CPU interrupts.
    Interrupt_initModule();         // call the function in driverlib.lib

    // Initializes the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    Interrupt_initVectorTable();    // call the function in driverlib.lib

    // Call SysConfig
    Board_init();

    // Initialize Signal Sight tool state
    // SIGNALSIGHT_init();

    // initialize the driver
    halHandle = HAL_init(&hal, sizeof(hal));   

    // initialize the interrupt vector table
    HAL_initIntVectorTable(halHandle);

    // enable the ADC/PWM interrupts for control
    // enable interrupts to trig DMA
    HAL_enableADCInts(halHandle);
    HAL_enableCtrlInts(halHandle);

    // set the control parameters for motor 1
    motorHandle_M1 = (MOTOR_Handle)(&motorVars_M1);

    // set the reference speed, this can be replaced or removed
    motorVars_M1.flagEnableRunAndIdentify = false;

    motorVars_M1.speedRef_Hz  = USER_MOTOR1_SPEED_SET_Hz;       // Hz
    motorVars_M1.speedSet_Hz  = USER_MOTOR1_SPEED_SET_Hz;       // Hz

    // false - enables identification, true - disables identification
    userParams_M1.flag_bypassMotorId = true;

    initMotor1Handles(motorHandle_M1);
    initMotor1CtrlParameters(motorHandle_M1);
    resetMotor1CtrlParameters(motorHandle_M1);

    // set the driver parameters
    HAL_setParams(halHandle);

    // set up gate driver after completed GPIO configuration
    motorVars_M1.faultMtrNow.bit.gateDriver =
            HAL_MTR_setGateDriver(motorHandle_M1->halMtrHandle);

    // enable the ePWM module time base clock sync signal
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);



    // initialize the CPU usage module
    cpuTimeHandle = CPU_TIME_init(&cpuTime, sizeof(cpuTime));
    CPU_TIME_reset(cpuTimeHandle);
    CPU_TIME_setCtrlPeriod(cpuTimeHandle,
                    HAL_getTimeBasePeriod(motorHandle_M1->halMtrHandle) *
                    motorSetVars_M1.controlTicksPWM);

    systemVars.flagEnableSystem = true; // TODO Remove this line for AC power input


    motorVars_M1.flagEnableOffsetCalc = true;

    // run offset calibration for motor 1
    runMotor1OffsetsCalculation(motorHandle_M1);

    // enable global interrupts
    HAL_enableGlobalInts(halHandle);

    // enable debug interrupts
    HAL_enableDebugInt(halHandle);

    HAL_enableCtrlInts(halHandle);

    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    EINT;
    ERTM;

    // initialize variables
    systemVars.powerRelayWaitTime_ms = POWER_RELAY_WAIT_TIME_ms;
    systemVars.timerBase_1ms = 0;


    // Waiting for enable system flag to be set
    while(systemVars.flagEnableSystem == false)
    {
        //Signal Sight background operation for streaming and polling
        // SIGNALSIGHT_sendPlotData();
        // SIGNALSIGHT_captureAndSendPollingData();

        if(HAL_getCPUTimerStatus(halHandle, HAL_CPU_TIMER0))
        {
            HAL_clearCPUTimerFlag(halHandle, HAL_CPU_TIMER0);

            systemVars.timerBase_1ms++;

            if(systemVars.timerBase_1ms > systemVars.powerRelayWaitTime_ms)
            {
                systemVars.flagEnableSystem = true;
                systemVars.timerBase_1ms = 0;
            }
        }
    }

    motorVars_M1.flagInitializeDone = true;

    while(systemVars.flagEnableSystem == true)
    {
        //Signal Sight background operation for streaming and polling
        // SIGNALSIGHT_sendPlotData();
        // SIGNALSIGHT_captureAndSendPollingData();

        // loop while the enable system flag is true
        systemVars.mainLoopCnt++;
        
        // 1ms time base
        if(HAL_getCPUTimerStatus(halHandle, HAL_CPU_TIMER0))
        {
            HAL_clearCPUTimerFlag(halHandle, HAL_CPU_TIMER0);

            systemVars.timerBase_1ms++;

            switch(systemVars.timerBase_1ms)
            {
                case 1:     // motor 1 protection check
                    runMotorMonitor(motorHandle_M1);
                    break;
                case 2:
                    // calculate the current/voltage RMS value
                    calculateRMSData(motorHandle_M1);

                    // calculate motor protection value
                    calcMotorOverCurrentThreshold(motorHandle_M1);
                    break;
                case 3:
                    // Tune the gains of the controllers
                    tuneControllerGains(motorHandle_M1);
                    updateFASTParameters(motorHandle_M1);
                    break;
                case 4:     // calculate motor protection value
                    calcMotorOverCurrentThreshold(motorHandle_M1);
                    break;
                case 5:     // system control
                    systemVars.timerBase_1ms = 0;
                    systemVars.timerCnt_5ms++;
                    break;
            }

            CPU_TIME_calcCPUWidthRatio(cpuTimeHandle);  
        }       // 1ms Timer
        
        // runs control for motor 1
        runMotor1Control(motorHandle_M1);    // No time base

    } // end of while() loop

    // disable the PWM
    HAL_disablePWM(motorHandle_M1->halMtrHandle);

} // end of main() function

//
//-- end of this file ----------------------------------------------------------
//
