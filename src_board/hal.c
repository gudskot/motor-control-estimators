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
// the includes
//
#include "user.h"

// platforms
#include "hal.h"
#include "hal_obj.h"


#ifdef _FLASH
#pragma CODE_SECTION(Flash_initModule, ".TI.ramfunc");
#endif

// **************************************************************************
// the defines


// **************************************************************************
// the globals
HAL_Handle    halHandle;      //!< the handle for the hardware abstraction layer
HAL_Obj       hal;            //!< the hardware abstraction layer object
#pragma DATA_SECTION(halHandle, "hal_data");
#pragma DATA_SECTION(hal, "hal_data");

// **************************************************************************
// the functions

void HAL_disableGlobalInts(HAL_Handle handle)
{
    // disable global interrupts
    Interrupt_disableGlobal();

    return;
} // end of HAL_disableGlobalInts() function

void HAL_disableWdog(HAL_Handle halHandle)
{
    // disable watchdog
    SysCtl_disableWatchdog();

    return;
} // end of HAL_disableWdog() function

void HAL_enableADCInts(HAL_Handle handle)
{
    // enable the ADC interrupts for motor_1
    ADC_enableInterrupt(MTR1_ADC_INT_BASE, MTR1_ADC_INT_NUM);


    return;
} // end of HAL_enableCtrlInts() function

void HAL_enableCtrlInts(HAL_Handle handle)
{
    // enable the PIE interrupts associated with the ADC interrupts
    Interrupt_enable(MTR1_PIE_INT_NUM);    // motor_1

    return;
} // end of HAL_enableCtrlInts() function

void HAL_enableDebugInt(HAL_Handle handle)
{

    // enable debug events
    ERTM;

    return;
} // end of HAL_enableDebugInt() function

void HAL_enableGlobalInts(HAL_Handle handle)
{

    // enable global interrupts
    Interrupt_enableGlobal();

    return;
} // end of HAL_enableGlobalInts() function


HAL_Handle HAL_init(void *pMemory,const size_t numBytes)
{
    HAL_Handle handle;
    HAL_Obj *obj;

    if(numBytes < sizeof(HAL_Obj))
    {
        return((HAL_Handle)NULL);
    }

    // assign the handle
    handle = (HAL_Handle)pMemory;

    // assign the object
    obj = (HAL_Obj *)handle;

    // Two ADC modules in this device
    // initialize the ADC handles
    obj->adcHandle[0] = ADCA_BASE;
    obj->adcHandle[1] = ADCB_BASE;
    obj->adcHandle[2] = ADCC_BASE;

    // initialize the ADC results
    obj->adcResult[0] = ADCARESULT_BASE;
    obj->adcResult[1] = ADCBRESULT_BASE;
    obj->adcResult[2] = ADCCRESULT_BASE;


    // No DAC modules in this device
    // No CLA module in this device

    // initialize SCI handle
    obj->sciHandle[0] = SCIA_BASE;             //!< the SCIA handle


    // initialize SPI handle
    obj->spiHandle = SPIA_BASE;          //!< the SPIA handle for DAC128S or AI Sensor

    // initialize timer handles
    obj->timerHandle[0] = CPUTIMER0_BASE;
    obj->timerHandle[1] = CPUTIMER1_BASE;
    obj->timerHandle[2] = CPUTIMER2_BASE;

    // initialize DMA handle
    obj->dmaHandle = DMA_BASE;              //!< the DMA handle
    obj->dmaChHandle[0] = DMA_CH1_BASE;     //!< the DMA Channel handle
    obj->dmaChHandle[1] = DMA_CH2_BASE;     //!< the DMA Channel handle


    return(handle);
} // end of HAL_init() function

HAL_MTR_Handle HAL_MTR1_init(void *pMemory, const size_t numBytes)
{
    HAL_MTR_Handle handle;
    HAL_MTR_Obj *obj;

    if(numBytes < sizeof(HAL_MTR_Obj))
    {
        return((HAL_MTR_Handle)NULL);
    }

    // assign the handle
    handle = (HAL_MTR_Handle)pMemory;

    // assign the object
    obj = (HAL_MTR_Obj *)handle;

    // initialize PWM handles for Motor 1
    obj->pwmHandle[0] = MTR1_EPWM_U_BASE;        //!< the PWM handle
    obj->pwmHandle[1] = MTR1_EPWM_V_BASE;        //!< the PWM handle
    obj->pwmHandle[2] = MTR1_EPWM_W_BASE;        //!< the PWM handle


    // initialize CMPSS handles
    obj->cmpssHandle[0] = MTR1_CMPSS_U_BASE;    //!< the CMPSS handle
    obj->cmpssHandle[1] = MTR1_CMPSS_V_BASE;    //!< the CMPSS handle
    obj->cmpssHandle[2] = MTR1_CMPSS_W_BASE;    //!< the CMPSS handle


    // No PGA modules in this device


    // Assign gateEnableGPIO
    obj->gateEnableGPIO = MTR1_GATE_EN_GPIO;

    // initialize the DRV8320 interface
    obj->drv8320Handle = DRV8320_init(&obj->drv8320);
    HAL_setupGate(handle);


    obj->motorNum = MTR_1;

    return(handle);
} // end of HAL_MTR1_init() function

void HAL_setParams(HAL_Handle handle)
{
    // disable global interrupts
    Interrupt_disableGlobal();

#ifdef _FLASH
    //
    // Copy time critical code and flash setup code to RAM. This includes the
    // following functions: InitFlash();
    //
    // The RamfuncsLoadStart, RamfuncsLoadSize, and RamfuncsRunStart symbols
    // are created by the linker. Refer to the device .cmd file.
    //
    memcpy(&runStart_ctrlfuncs, &loadStart_ctrlfuncs, (size_t)&loadSize_ctrlfuncs);
#endif  // _FLASH




    return;
} // end of HAL_setParams() function

void HAL_MTR_setParams(HAL_MTR_Handle handle, USER_Params *pUserParams)
{
    HAL_setNumCurrentSensors(handle, pUserParams->numCurrentSensors);
    HAL_setNumVoltageSensors(handle, pUserParams->numVoltageSensors);

    // setup the PWMs
    HAL_setupPWMs(handle);




    // disable the PWM
    HAL_disablePWM(handle);

    // DRV8320 is enabled and configured later in HAL_MTR_setGateDriver()

    return;
} // end of HAL_MTR_setParams() function




void HAL_setupGate(HAL_MTR_Handle handle)
{
    HAL_MTR_Obj *obj = (HAL_MTR_Obj *)handle;

    obj->gateEnableGPIO = MTR1_GATE_EN_GPIO;

    DRV8320_setSPIHandle(obj->drv8320Handle, MTR1_DRV_SPI_BASE);
    DRV8320_setGPIOCSNumber(obj->drv8320Handle, MTR1_DRV_SPI_CS_GPIO);
    DRV8320_setGPIONumber(obj->drv8320Handle, MTR1_GATE_EN_GPIO);

    return;
} // HAL_setupGate() function




void HAL_enableDRV(HAL_MTR_Handle handle)
{
    HAL_MTR_Obj *obj = (HAL_MTR_Obj *)handle;

    // EN = 1, waits until the FAULT bit clears (with timeout)
    DRV8320_enable(obj->drv8320Handle);

    return;
} // HAL_enableDRV() function

void HAL_writeDRVData(HAL_MTR_Handle handle, DRV8320_SPIVars_t *drv8320SPIVars)
{
    HAL_MTR_Obj *obj = (HAL_MTR_Obj *)handle;

    DRV8320_writeData(obj->drv8320Handle, drv8320SPIVars);

    return;
} // HAL_writeDRVData() function

void HAL_readDRVData(HAL_MTR_Handle handle, DRV8320_SPIVars_t *drv8320SPIVars)
{
    HAL_MTR_Obj *obj = (HAL_MTR_Obj *)handle;

    DRV8320_readData(obj->drv8320Handle, drv8320SPIVars);

    return;
} // HAL_readDRVData() function

void HAL_updatePWMsPeriod(HAL_MTR_Handle handle,
                          float32_t pwmControl_kHz, uint16_t controlTicksPWM)
{
    HAL_MTR_Obj    *obj = (HAL_MTR_Obj *)handle;

    obj->pwmPeriodCycles = (uint16_t)((USER_SYSTEM_FREQ_MHz * 1000.0f / 2.0f)/ pwmControl_kHz);
    obj->numPWMTicksPerISRTick = controlTicksPWM;

    // since the PWM is configured as an up/down counter, the period register is
    // set to one-half of the desired PWM period
    EPWM_setTimeBasePeriod(obj->pwmHandle[0], obj->pwmPeriodCycles);
    EPWM_setTimeBasePeriod(obj->pwmHandle[1], obj->pwmPeriodCycles);
    EPWM_setTimeBasePeriod(obj->pwmHandle[2], obj->pwmPeriodCycles);

    // setup the Event Trigger Prescale Register (ETPS)
    if(obj->numPWMTicksPerISRTick > 15)
    {
        obj->numPWMTicksPerISRTick = 15;
    }
    else if(obj->numPWMTicksPerISRTick < 1)
    {
        obj->numPWMTicksPerISRTick = 1;
    }

    EPWM_setInterruptEventCount(obj->pwmHandle[0], obj->numPWMTicksPerISRTick);

    EPWM_setADCTriggerEventPrescale(obj->pwmHandle[0], EPWM_SOC_A,
                                    obj->numPWMTicksPerISRTick);
    EPWM_setADCTriggerEventPrescale(obj->pwmHandle[0], EPWM_SOC_B,
                                    obj->numPWMTicksPerISRTick);


    return;
}

void HAL_setupPWMs(HAL_MTR_Handle handle)
{
    HAL_MTR_Obj    *obj = (HAL_MTR_Obj *)handle;
    uint16_t  cnt;

    obj->pwmPeriodCycles = (uint16_t)(USER_M1_PWM_TBPRD_NUM);
    obj->numPWMTicksPerISRTick = USER_M1_NUM_PWM_TICKS_PER_ISR_TICK;

    // disable the ePWM module time base clock sync signal
    // to synchronize all of the PWMs
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    // turns off the outputs of the EPWM peripherals which will put the power
    // switches into a high impedance state.
    EPWM_forceTripZoneEvent(obj->pwmHandle[0], EPWM_TZ_FORCE_EVENT_OST);
    EPWM_forceTripZoneEvent(obj->pwmHandle[1], EPWM_TZ_FORCE_EVENT_OST);
    EPWM_forceTripZoneEvent(obj->pwmHandle[2], EPWM_TZ_FORCE_EVENT_OST);

    for(cnt=0; cnt<3; cnt++)
    {
        // setup the Time-Base Control Register (TBCTL)
        EPWM_setTimeBaseCounterMode(obj->pwmHandle[cnt],
                                    EPWM_COUNTER_MODE_UP_DOWN);

        EPWM_disablePhaseShiftLoad(obj->pwmHandle[cnt]);

        EPWM_setPeriodLoadMode(obj->pwmHandle[cnt], EPWM_PERIOD_DIRECT_LOAD);

        EPWM_enableSyncOutPulseSource(obj->pwmHandle[cnt],
            EPWM_SYNC_OUT_PULSE_ON_SOFTWARE);

        EPWM_setClockPrescaler(obj->pwmHandle[cnt], EPWM_CLOCK_DIVIDER_1,
                                 EPWM_HSCLOCK_DIVIDER_1);

        EPWM_setCountModeAfterSync(obj->pwmHandle[cnt],
                                   EPWM_COUNT_MODE_UP_AFTER_SYNC);

        EPWM_setEmulationMode(obj->pwmHandle[cnt], EPWM_EMULATION_FREE_RUN);

        // setup the Timer-Based Phase Register (TBPHS)
        EPWM_setPhaseShift(obj->pwmHandle[cnt], 0);

        // setup the Time-Base Counter Register (TBCTR)
        EPWM_setTimeBaseCounter(obj->pwmHandle[cnt], 0);

        // setup the Time-Base Period Register (TBPRD)
        // set to zero initially
        EPWM_setTimeBasePeriod(obj->pwmHandle[cnt], 0);

        // setup the Counter-Compare Control Register (CMPCTL)
        EPWM_setCounterCompareShadowLoadMode(obj->pwmHandle[cnt],
                                             EPWM_COUNTER_COMPARE_A,
                                             EPWM_COMP_LOAD_ON_CNTR_ZERO);

        EPWM_setCounterCompareShadowLoadMode(obj->pwmHandle[cnt],
                                             EPWM_COUNTER_COMPARE_B,
                                             EPWM_COMP_LOAD_ON_CNTR_ZERO);

        EPWM_setCounterCompareShadowLoadMode(obj->pwmHandle[cnt],
                                             EPWM_COUNTER_COMPARE_C,
                                             EPWM_COMP_LOAD_ON_CNTR_ZERO);

        EPWM_setCounterCompareShadowLoadMode(obj->pwmHandle[cnt],
                                             EPWM_COUNTER_COMPARE_D,
                                             EPWM_COMP_LOAD_ON_CNTR_ZERO);


        // setup the Action-Qualifier Output A Register (AQCTLA)
        EPWM_setActionQualifierAction(obj->pwmHandle[cnt],
                                      EPWM_AQ_OUTPUT_A,
                                      EPWM_AQ_OUTPUT_HIGH,
                                      EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);

        EPWM_setActionQualifierAction(obj->pwmHandle[cnt],
                                      EPWM_AQ_OUTPUT_A,
                                      EPWM_AQ_OUTPUT_HIGH,
                                      EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);

        EPWM_setActionQualifierAction(obj->pwmHandle[cnt],
                                      EPWM_AQ_OUTPUT_A,
                                      EPWM_AQ_OUTPUT_LOW,
                                      EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);

        EPWM_setActionQualifierAction(obj->pwmHandle[cnt],
                                      EPWM_AQ_OUTPUT_A,
                                      EPWM_AQ_OUTPUT_LOW,
                                      EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);


        // setup the Dead-Band Generator Control Register (DBCTL)
        EPWM_setDeadBandDelayMode(obj->pwmHandle[cnt], EPWM_DB_RED, true);
        EPWM_setDeadBandDelayMode(obj->pwmHandle[cnt], EPWM_DB_FED, true);

        // select EPWMA as the input to the dead band generator
        EPWM_setRisingEdgeDeadBandDelayInput(obj->pwmHandle[cnt],
                                             EPWM_DB_INPUT_EPWMA);

        // configure the right polarity for active high complementary config.
        EPWM_setDeadBandDelayPolarity(obj->pwmHandle[cnt],
                                      EPWM_DB_RED,
                                      EPWM_DB_POLARITY_ACTIVE_HIGH);
        EPWM_setDeadBandDelayPolarity(obj->pwmHandle[cnt],
                                      EPWM_DB_FED,
                                      EPWM_DB_POLARITY_ACTIVE_LOW);

        // setup the Dead-Band Rising Edge Delay Register (DBRED)
        EPWM_setRisingEdgeDelayCount(obj->pwmHandle[cnt], MTR1_PWM_DBRED_CNT);

        // setup the Dead-Band Falling Edge Delay Register (DBFED)
        EPWM_setFallingEdgeDelayCount(obj->pwmHandle[cnt], MTR1_PWM_DBFED_CNT);


        // setup the PWM-Chopper Control Register (PCCTL)
        EPWM_disableChopper(obj->pwmHandle[cnt]);

        // Trip zone sources (CMPSS + nFAULT) are configured in Board_init();
        // do NOT disable them here, otherwise OCP and nFAULT stop working.

        // What the OST/CBC events do with the outputs (as in the TI reference HAL):
        // TZA forces EPWMxA (INHx), TZB forces EPWMxB (INLx). Both low = both
        // switches of the half-bridge off (DRV8320 6x mode: INHx = INLx = 0).
        EPWM_setTripZoneAction(obj->pwmHandle[cnt],
                               EPWM_TZ_ACTION_EVENT_TZA,
                               EPWM_TZ_ACTION_LOW);
        EPWM_setTripZoneAction(obj->pwmHandle[cnt],
                               EPWM_TZ_ACTION_EVENT_TZB,
                               EPWM_TZ_ACTION_LOW);
    }

    // setup the Event Trigger Selection Register (ETSEL)
    EPWM_setInterruptSource(obj->pwmHandle[0], EPWM_INT_TBCTR_ZERO);

    EPWM_enableInterrupt(obj->pwmHandle[0]);

    EPWM_setADCTriggerSource(obj->pwmHandle[0],
                             EPWM_SOC_A, EPWM_SOC_TBCTR_D_CMPC);

    EPWM_enableADCTrigger(obj->pwmHandle[0], EPWM_SOC_A);

    // setup the Event Trigger Prescale Register (ETPS)
    if(obj->numPWMTicksPerISRTick > 15)
    {
        obj->numPWMTicksPerISRTick = 15;
    }
    else if(obj->numPWMTicksPerISRTick < 1)
    {
        obj->numPWMTicksPerISRTick = 1;
    }

    EPWM_setInterruptEventCount(obj->pwmHandle[0], obj->numPWMTicksPerISRTick);

    EPWM_setADCTriggerEventPrescale(obj->pwmHandle[0], EPWM_SOC_A,
                                    obj->numPWMTicksPerISRTick);
    EPWM_setADCTriggerEventPrescale(obj->pwmHandle[0], EPWM_SOC_B,
                                    obj->numPWMTicksPerISRTick);


    // setup the Event Trigger Clear Register (ETCLR)
    EPWM_clearEventTriggerInterruptFlag(obj->pwmHandle[0]);
    EPWM_clearADCTriggerFlag(obj->pwmHandle[0], EPWM_SOC_A);
    EPWM_clearADCTriggerFlag(obj->pwmHandle[0], EPWM_SOC_B);

    // since the PWM is configured as an up/down counter, the period register is
    // set to one-half of the desired PWM period
    EPWM_setTimeBasePeriod(obj->pwmHandle[0], obj->pwmPeriodCycles);
    EPWM_setTimeBasePeriod(obj->pwmHandle[1], obj->pwmPeriodCycles);
    EPWM_setTimeBasePeriod(obj->pwmHandle[2], obj->pwmPeriodCycles);

    // write the PWM data value  for ADC trigger
    EPWM_setCounterCompareValue(obj->pwmHandle[0], EPWM_COUNTER_COMPARE_C, 10);

    // write the PWM data value  for ADC trigger

    return;
}


void HAL_setupTimeBaseTimer(HAL_Handle handle, const float32_t timeBaseFreq_Hz)
{
    HAL_Obj  *obj = (HAL_Obj *)handle;

    uint32_t timerPeriod = (uint32_t)((USER_SYSTEM_FREQ_MHz * 1000.0f *1000.0f) /
                                      timeBaseFreq_Hz);

    // use timer 0 for CPU usage diagnostics
    CPUTimer_setPreScaler(obj->timerHandle[0], 0);

    CPUTimer_setEmulationMode(obj->timerHandle[0],
                              CPUTIMER_EMULATIONMODE_RUNFREE);

    CPUTimer_setPeriod(obj->timerHandle[0], timerPeriod);

    CPUTimer_startTimer(obj->timerHandle[0]);

    return;
}  // end of HAL_setupTimeBaseTimer() function

#pragma CODE_SECTION(HAL_setupCPUUsageTimer, "sysfuncs");
void HAL_setupCPUUsageTimer(HAL_Handle handle)
{
    HAL_Obj  *obj = (HAL_Obj *)handle;

    // use timer 2 for CPU usage diagnostics
    CPUTimer_setPreScaler(obj->timerHandle[1], 0);

    CPUTimer_setEmulationMode(obj->timerHandle[1],
                              CPUTIMER_EMULATIONMODE_RUNFREE);

    CPUTimer_setPeriod(obj->timerHandle[1], 0xFFFFFFFF);

    CPUTimer_startTimer(obj->timerHandle[1]);

    return;
}  // end of HAL_setupCPUUsageTimer() function



void HAL_clearDataRAM(void *pMemory, uint16_t lengthMemory)
{
    uint16_t *pMemoryStart;
    uint16_t loopCount, loopLength;

    pMemoryStart = pMemory;
    loopLength = lengthMemory;

    for(loopCount = 0; loopCount < loopLength; loopCount++)
    {
        *(pMemoryStart + loopCount) = 0x0000;
    }
}   //end of HAL_clearDataRAM() function

void HAL_setMtrCMPSSDACValue(HAL_MTR_Handle handle,
                             const uint16_t dacValH, const uint16_t dacValL)
{
    HAL_MTR_Obj *obj = (HAL_MTR_Obj *)handle;

    // every phase has its own CMPSS with both comparators (+ and - overcurrent)
    CMPSS_setDACValueHigh(obj->cmpssHandle[0], dacValH);
    CMPSS_setDACValueLow(obj->cmpssHandle[0], dacValL);

    CMPSS_setDACValueHigh(obj->cmpssHandle[1], dacValH);
    CMPSS_setDACValueLow(obj->cmpssHandle[1], dacValL);

    CMPSS_setDACValueHigh(obj->cmpssHandle[2], dacValH);
    CMPSS_setDACValueLow(obj->cmpssHandle[2], dacValL);

    return;
}

void HAL_setTriggerPrams(HAL_PWMData_t *pPWMData, const float32_t systemFreq_MHz,
                   const float32_t deadband_us, const float32_t noiseWindow_us,
                   const float32_t adcSample_us)
{
    uint16_t deadband =  (uint16_t)(deadband_us * systemFreq_MHz);
    uint16_t noiseWindow =  (uint16_t)(noiseWindow_us * systemFreq_MHz);
    uint16_t adcSample =  (uint16_t)(adcSample_us * systemFreq_MHz);

    pPWMData->deadband = deadband;
    pPWMData->noiseWindow = noiseWindow;
    pPWMData->adcSample = adcSample;

    pPWMData->minCMPValue = deadband + noiseWindow + adcSample;

    return;
}   // end of HAL_setTriggerPrams() function

void HAL_getPWMPeriod(HAL_MTR_Handle handle, HAL_PWMData_t *pPWMData)
{
    HAL_MTR_Obj *obj = (HAL_MTR_Obj *)handle;

    pPWMData->periods = (float32_t)(EPWM_getTimeBasePeriod(obj->pwmHandle[0]));

    return;
}   // end of HAL_getPWMPeriod() function
    
// DRV8320 register settings
// TODO: IDRIVE/TDRIVE must match your MOSFETs (Qg) - start from what the
//       IDRIVE resistor gave on the DRV8323RH board.
#define DRV_IDRIVEP_HS      DRV8320_ISOUR_HS_0P260_A
#define DRV_IDRIVEN_HS      DRV8320_ISINK_HS_0P520_A
#define DRV_IDRIVEP_LS      DRV8320_ISOUR_LS_0P260_A
#define DRV_IDRIVEN_LS      DRV8320_ISINK_LS_0P520_A
#define DRV_TDRIVE          DRV8320_TSOUR_4000_NS
#define DRV_VDS_LVL         DRV8320_VDS_LEVEL_0P750_V
#define DRV_OCP_DEG         DRV8320_VDSDEG_4_US
#define DRV_OCP_MODE        DRV8320_LATCHED_SHUTDOWN
#define DRV_DEAD_TIME       DRV8320_DEADTIME_100_NS

// returns true on FAULT (main writes it into faultMtrNow.bit.gateDriver)
bool HAL_MTR_setGateDriver(HAL_MTR_Handle handle)
{
    HAL_MTR_Obj *obj = (HAL_MTR_Obj *)handle;
    DRV8320_SPIVars_t *drv = &obj->drvSPIVars;
    bool driverFault = false;

    DRV8320_resetEnableTimeout(obj->drv8320Handle);
    DRV8320_resetRxTimeout(obj->drv8320Handle);

    // EN = 1, then wait for the DRV wake-up time before configuring it
    HAL_enableDRV(handle);
    DEVICE_DELAY_US(1000U);

    // read all registers -> drvSPIVars
    DRV8320_setupSPI(obj->drv8320Handle, drv);

    // registers are writable only when LOCK = unlocked
    drv->Ctrl_Reg_02.CLR_FLT   = true;
    drv->Ctrl_Reg_02.BRAKE     = false;
    drv->Ctrl_Reg_02.COAST     = false;
    drv->Ctrl_Reg_02.PWM_MODE  = DRV8320_PWMMODE_6;
    drv->Ctrl_Reg_02.OTW_REP   = true;
    drv->Ctrl_Reg_02.DIS_GDF   = false;
    drv->Ctrl_Reg_02.DIS_CPUV  = false;

    drv->Ctrl_Reg_03.LOCK       = DRV8320_LOCK_UNLOCK;
    drv->Ctrl_Reg_03.IDRIVEP_HS = DRV_IDRIVEP_HS;
    drv->Ctrl_Reg_03.IDRIVEN_HS = DRV_IDRIVEN_HS;

    drv->Ctrl_Reg_04.CBC        = false;
    drv->Ctrl_Reg_04.TDRIVE     = DRV_TDRIVE;
    drv->Ctrl_Reg_04.IDRIVEP_LS = DRV_IDRIVEP_LS;
    drv->Ctrl_Reg_04.IDRIVEN_LS = DRV_IDRIVEN_LS;

    drv->Ctrl_Reg_05.TRETRY    = false;
    drv->Ctrl_Reg_05.DEAD_TIME = DRV_DEAD_TIME;
    drv->Ctrl_Reg_05.OCP_MODE  = DRV_OCP_MODE;
    drv->Ctrl_Reg_05.OCP_DEG   = DRV_OCP_DEG;
    drv->Ctrl_Reg_05.VDS_LVL   = DRV_VDS_LVL;

    drv->writeCmd = true;
    HAL_writeDRVData(handle, drv);

    DEVICE_DELAY_US(100U);

    // readback: what the DRV really has, plus status registers
    drv->readCmd = true;
    HAL_readDRVData(handle, drv);
    drv->readCmd = false;

    // CLR_FLT is self-clearing, so it is not compared
    if((drv->Ctrl_Reg_02.PWM_MODE   != DRV8320_PWMMODE_6) ||
       (drv->Ctrl_Reg_03.IDRIVEP_HS != DRV_IDRIVEP_HS)    ||
       (drv->Ctrl_Reg_03.IDRIVEN_HS != DRV_IDRIVEN_HS)    ||
       (drv->Ctrl_Reg_04.IDRIVEP_LS != DRV_IDRIVEP_LS)    ||
       (drv->Ctrl_Reg_04.IDRIVEN_LS != DRV_IDRIVEN_LS)    ||
       (drv->Ctrl_Reg_04.TDRIVE     != DRV_TDRIVE)        ||
       (drv->Ctrl_Reg_05.VDS_LVL    != DRV_VDS_LVL)       ||
       (drv->Ctrl_Reg_05.OCP_DEG    != DRV_OCP_DEG)       ||
       (drv->Ctrl_Reg_05.OCP_MODE   != DRV_OCP_MODE)      ||
       (drv->Ctrl_Reg_05.DEAD_TIME  != DRV_DEAD_TIME))
    {
        driverFault = true;     // SPI does not work or the write was rejected
    }

    // enableTimeOut only says FAULT was set before CLR_FLT, so it is not
    // checked here; the status after CLR_FLT is what matters
    if(drv->Stat_Reg_00.FAULT || obj->drv8320.rxTimeOut)
    {
        driverFault = true;
    }

    return(driverFault);
}

