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


#ifndef HAL_H
#define HAL_H


//! \file   \solutions\universal_motorcontrol_lab\f28002x\drivers\include\hal.h
//! \brief  Contains public interface to various functions related
//!         to the HAL object
//!

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
#include "userParams.h"
#include "board.h"
// #include "mcsdk_libraries.h"

// platforms
#include "hal_obj.h"

#include "svgen_current.h"


// the globals
extern HAL_Handle    halHandle;
extern HAL_Obj       hal;
extern volatile uint16_t mtrPIEIER;
extern volatile uint16_t mtrIER;

#ifdef _FLASH
extern uint32_t loadStart_ctrlfuncs;
extern uint32_t loadEnd_ctrlfuncs;
extern uint32_t loadSize_ctrlfuncs;
extern uint32_t runStart_ctrlfuncs;
extern uint32_t runEnd_ctrlfuncs;
extern uint32_t runSize_ctrlfuncs;
#endif  // _FLASH

extern uint32_t loadStart_est_data;
extern uint32_t loadEnd_est_data;
extern uint32_t loadSize_est_data;

extern uint32_t loadStart_hal_data;
extern uint32_t loadEnd_hal_data;
extern uint32_t loadSize_hal_data;

extern uint32_t loadStart_user_data;
extern uint32_t loadEnd_user_data;
extern uint32_t loadSize_user_data;

extern uint32_t loadStart_foc_data;
extern uint32_t loadEnd_foc_data;
extern uint32_t loadSize_foc_data;

extern uint32_t loadStart_sys_data;
extern uint32_t loadEnd_sys_data;
extern uint32_t loadSize_sys_data;

extern uint32_t loadStart_vibc_data;
extern uint32_t loadEnd_vibc_data;
extern uint32_t loadSize_vibc_data;

extern uint32_t loadStart_dmaBuf_data;
extern uint32_t loadEnd_dmaBuf_data;
extern uint32_t loadSize_dmaBuf_data;

extern uint32_t loadStart_ctrl_data;
extern uint32_t loadEnd_ctrl_data;
extern uint32_t loadSize_ctrl_data;

extern uint32_t loadStart_datalog_data;
extern uint32_t loadEnd_datalog_data;
extern uint32_t loadSize_datalog_data;

extern uint32_t loadStart_SFRA_F32_Data;
extern uint32_t loadEnd_SFRA_F32_Data;
extern uint32_t loadSize_SFRA_F32_Data;

// **************************************************************************
// the defines
//
#define motor1CtrlISR               INT_MTR1_VDC_1_ISR

//! Trip Zones all interrupt
//!
#define HAL_TZFLAG_INTERRUPT_ALL    EPWM_TZ_INTERRUPT_DCBEVT2 |                \
                                    EPWM_TZ_INTERRUPT_DCBEVT1 |                \
                                    EPWM_TZ_INTERRUPT_DCAEVT2 |                \
                                    EPWM_TZ_INTERRUPT_DCAEVT1 |                \
                                    EPWM_TZ_INTERRUPT_OST |                    \
                                    EPWM_TZ_INTERRUPT_CBC

#define HAL_TZSEL_SIGNALS_ALL       EPWM_TZ_SIGNAL_CBC1 |                      \
                                    EPWM_TZ_SIGNAL_CBC2 |                      \
                                    EPWM_TZ_SIGNAL_CBC3 |                      \
                                    EPWM_TZ_SIGNAL_CBC4 |                      \
                                    EPWM_TZ_SIGNAL_CBC5 |                      \
                                    EPWM_TZ_SIGNAL_CBC6 |                      \
                                    EPWM_TZ_SIGNAL_DCAEVT2 |                   \
                                    EPWM_TZ_SIGNAL_DCBEVT2 |                   \
                                    EPWM_TZ_SIGNAL_OSHT1 |                     \
                                    EPWM_TZ_SIGNAL_OSHT2 |                     \
                                    EPWM_TZ_SIGNAL_OSHT3 |                     \
                                    EPWM_TZ_SIGNAL_OSHT4 |                     \
                                    EPWM_TZ_SIGNAL_OSHT5 |                     \
                                    EPWM_TZ_SIGNAL_OSHT6 |                     \
                                    EPWM_TZ_SIGNAL_DCAEVT1 |                   \
                                    EPWM_TZ_SIGNAL_DCBEVT1

//
// defines common to all devices and board configurations
//
// ADC, Three-shunt
#define MTR1_IU_ADC_BASE        MTR1_IU_ADC_SOC_NUM_ADC_BASE          
#define MTR1_IV_ADC_BASE        MTR1_IV_ADC_SOC_NUM_ADC_BASE          
#define MTR1_IW_ADC_BASE        MTR1_IW_ADC_SOC_NUM_ADC_BASE

#define MTR1_IU_ADCRES_BASE     MTR1_IU_ADC_SOC_NUM_RESULT_BASE
#define MTR1_IV_ADCRES_BASE     MTR1_IV_ADC_SOC_NUM_RESULT_BASE
#define MTR1_IW_ADCRES_BASE     MTR1_IW_ADC_SOC_NUM_RESULT_BASE

#define MTR1_IU_ADC_CH_NUM      MTR1_IU_ADC_SOC_NUM_CHANNEL
#define MTR1_IV_ADC_CH_NUM      MTR1_IV_ADC_SOC_NUM_CHANNEL
#define MTR1_IW_ADC_CH_NUM      MTR1_IW_ADC_SOC_NUM_CHANNEL

// ADC - Voltage, Phase and dc-bus
#define MTR1_VU_ADC_BASE        MTR1_VU_ADC_SOC_NUM_ADC_BASE          
#define MTR1_VV_ADC_BASE        MTR1_VV_ADC_SOC_NUM_ADC_BASE        
#define MTR1_VW_ADC_BASE        MTR1_VW_ADC_SOC_NUM_ADC_BASE          
#define MTR1_VDC_ADC_BASE       MTR1_VDC_ADC_SOC_NUM_ADC_BASE

#define MTR1_VU_ADCRES_BASE     MTR1_VU_ADC_SOC_NUM_RESULT_BASE
#define MTR1_VV_ADCRES_BASE     MTR1_VV_ADC_SOC_NUM_RESULT_BASE
#define MTR1_VW_ADCRES_BASE     MTR1_VW_ADC_SOC_NUM_RESULT_BASE
#define MTR1_VDC_ADCRES_BASE    MTR1_VDC_ADC_SOC_NUM_RESULT_BASE

#define MTR1_VU_ADC_CH_NUM      MTR1_VU_ADC_SOC_NUM_CHANNEL
#define MTR1_VV_ADC_CH_NUM      MTR1_VV_ADC_SOC_NUM_CHANNEL
#define MTR1_VW_ADC_CH_NUM      MTR1_VW_ADC_SOC_NUM_CHANNEL
#define MTR1_VDC_ADC_CH_NUM     MTR1_VDC_ADC_SOC_NUM_CHANNEL


// interrupt
#define MTR1_PWM_INT_BASE       MTR1_EPWM_U_BASE
#define MTR1_ADC_INT_BASE       MTR1_VDC_ADC_BASE
#define MTR1_ADC_INT_NUM        ADC_INT_NUMBER1
#define MTR1_ADC_INT_SOC        MTR1_VDC_ADC_SOC_NUM_ADC_BASE

#define MTR1_PIE_INT_NUM        INT_MTR1_VDC_1
#define MTR1_INT_ACK_GROUP      INT_MTR1_VDC_1_INTERRUPT_ACK_GROUP

//------------------------------------------------------------------------------

//! \brief Defines the PWM deadband rising edge delay count (system clocks)
#define MTR1_PWM_DBRED_CNT      (uint16_t)((0.050 * (float32_t)USER_SYSTEM_FREQ_MHz))          // 50ns

//! \brief Defines the PWM deadband falling edge delay count (system clocks)
#define MTR1_PWM_DBFED_CNT      (uint16_t)((0.050 * (float32_t)USER_SYSTEM_FREQ_MHz))          // 50ns


// End of BSXL8323RH_REVB

//! \brief Defines the function to turn LEDs off
//!
#define HAL_turnLEDOff              HAL_setGPIOHigh

//! \brief Defines the function to turn LEDs on
//!
#define HAL_turnLEDOn               HAL_setGPIOLow

//! \brief Defines the function to toggle LEDs
//!
#define HAL_toggleLED               HAL_toggleGPIO

//! \brief Defines the function to turn on power relay
//!
#define HAL_turnOnPowerRelay        HAL_setGPIOHigh

//! \brief Defines the function to turn off power relay
//!
#define HAL_turnOffPowerRelay       HAL_setGPIOLow

typedef enum
{
    HAL_GPIO_LED1C   = 20,   //!< GPIO pin number for LaunchPad LED 1
    HAL_GPIO_LED2C   = 21,   //!< GPIO pin number for LaunchPad LED 2
    HAL_GPIO_LED1B   = 15,   //!< GPIO pin number for BoostxlPak LED 1
    HAL_GPIO_LED2B   = 31,   //!< GPIO pin number for BoostxlPak LED 2
} HAL_GPIO_Number_e;

//! \brief Enumeration for the sensor types
//!
typedef enum
{
    HAL_SENSORTYPE_CURRENT = 0,  //!< Enumeration for current sensor
    HAL_SENSORTYPE_VOLTAGE = 1   //!< Enumeration for voltage sensor
} HAL_SensorType_e;

//! \brief Enumeration for the QEP setup
//!
typedef enum
{
    HAL_QEP_QEP1=0,  //!< Select QEP1
    HAL_QEP_QEP2=1   //!< Select QEP2
} HAL_QEPSelect_e;

//! \brief Enumeration for the CPU Timer
//!
typedef enum
{
    HAL_CPU_TIMER0 = 0,  //!< Select CPU Timer0
    HAL_CPU_TIMER1 = 1,  //!< Select CPU Timer1
    HAL_CPU_TIMER2 = 2   //!< Select CPU Timer2
} HAL_CPUTimerNum_e;

// **************************************************************************
// the function prototypes

// the interrupt ISR for motor control
extern __interrupt void motor1CtrlISR(void);


//! \brief     Acknowledges an interrupt from the ADC so that another ADC
//!            interrupt can happen again.
//! \param[in] handle     The hardware abstraction layer (HAL) handle
static inline void HAL_ackMtr1ADCInt(void)
{

    // clear the ADC interrupt flag
    ADC_clearInterruptStatus(MTR1_ADC_INT_BASE, MTR1_ADC_INT_NUM);

    // Acknowledge interrupt from PIE group
    Interrupt_clearACKGroup(MTR1_INT_ACK_GROUP);

    return;
} // end of HAL_ackADCInt() function


//! \brief      Disables global interrupts
//! \param[in]  handle  The hardware abstraction layer (HAL) handle
extern void HAL_disableGlobalInts(HAL_Handle handle);

//! \brief      Enables the ADC interrupts
//! \details    Enables the ADC interrupt in the PIE, and CPU.  Enables the 
//!             interrupt to be sent from the ADC peripheral.
//! \param[in]  handle  The hardware abstraction layer (HAL) handle
extern void HAL_enableADCInts(HAL_Handle handle);

//! \brief      Enables the ADC interrupts
//! \details    Enables the ADC interrupt in the PIE, and CPU.  Enables the 
//!             interrupt to be sent from the ADC peripheral.
//! \param[in]  handle  The hardware abstraction layer (HAL) handle
extern void HAL_enableCtrlInts(HAL_Handle handle);


//! \brief      Enables the ADC interrupts without CPU interrupts
//! \details    Enables the ADC interrupts to only trigger CLA, and without
//!             interrupting the CPU
//! \param[in]  handle  The hardware abstraction layer (HAL) handle
extern void HAL_enableADCIntsToTriggerCLA(HAL_Handle handle);


//! \brief      Enables the debug interrupt
//! \details    The debug interrupt is used for the real-time debugger.  It is
//!             not needed if the real-time debugger is not used.  Clears
//!             bit 1 of ST1.
//! \param[in]  handle  The hardware abstraction layer (HAL) handle
extern void HAL_enableDebugInt(HAL_Handle handle);


//! \brief     Enables global interrupts
//! \param[in] handle  The hardware abstraction layer (HAL) handle
extern void HAL_enableGlobalInts(HAL_Handle handle);

//! \brief     Gets the PWM duty cycle times
//! \param[in] handle       The hardware abstraction layer (HAL) handle
//! \param[in] pDutyCycles  A pointer to memory for the duty cycle durations
static inline void
HAL_getDutyCycles(HAL_MTR_Handle handle,uint16_t *pDutyCycles)
{
  HAL_MTR_Obj *obj = (HAL_MTR_Obj *)handle;
  pDutyCycles[0] = EPWM_getCounterCompareValue(obj->pwmHandle[0],
                                               EPWM_COUNTER_COMPARE_A);
  pDutyCycles[1] = EPWM_getCounterCompareValue(obj->pwmHandle[1],
                                               EPWM_COUNTER_COMPARE_A);
  pDutyCycles[2] = EPWM_getCounterCompareValue(obj->pwmHandle[2],
                                               EPWM_COUNTER_COMPARE_A);
  return;
} // end of HAL_getDutyCycles() function

//! \brief     Gets the number of current sensors
//! \param[in] handle  The hardware abstraction layer (HAL) handle
//! \return    The number of current sensors
static inline uint16_t HAL_getNumCurrentSensors(HAL_MTR_Handle handle)
{
  HAL_MTR_Obj *obj = (HAL_MTR_Obj *)handle;
  
  return(obj->numCurrentSensors);
} // end of HAL_getNumCurrentSensors() function


//! \brief     Gets the number of voltage sensors
//! \param[in] handle  The hardware abstraction layer (HAL) handle
//! \return    The number of voltage sensors
static inline uint16_t HAL_getNumVoltageSensors(HAL_MTR_Handle handle)
{
  HAL_MTR_Obj *obj = (HAL_MTR_Obj *)handle;

  return(obj->numVoltageSensors);
} // end of HAL_getNumVoltageSensors() function

//! \brief     Gets the pwm enable status
//! \param[in]  handle  The hardware abstraction layer (HAL) handle
//! \return    The pwm enable
static inline bool HAL_getPwmEnableStatus(HAL_MTR_Handle handle)
{
  HAL_MTR_Obj *obj = (HAL_MTR_Obj *)handle;

  return(obj->flagEnablePWM);
} // end of HAL_getPwmStatus() function


//! \brief     Get the period of EPWM time-base module
//! \param[in] handle  The hardware abstraction layer (HAL) handle
//! \return    The periode of EPWM time-base module
static inline uint16_t
HAL_getTimeBasePeriod(HAL_MTR_Handle handle)
{
    HAL_MTR_Obj *obj = (HAL_MTR_Obj *)handle;
    return(EPWM_getTimeBasePeriod(obj->pwmHandle[0]));
} // end of HAL_getTimeBasePeriod() function

//! \brief      Initializes the hardware abstraction layer (HAL) object
//! \details    Initializes all handles to the microcontroller peripherals.
//!             Returns a handle to the HAL object.
//! \param[in]  pMemory   A pointer to the memory for the hardware abstraction layer object
//! \param[in]  numBytes  The number of bytes allocated for the hardware abstraction layer object, bytes
//! \return     The hardware abstraction layer (HAL) object handle
extern HAL_Handle HAL_init(void *pMemory,const size_t numBytes);


//! \brief      Initializes the hardware abstraction layer (HAL) object
//! \details    Initializes all handles to the microcontroller peripherals.
//!             Returns a handle to the HAL_MTR object.
//! \param[in]  pMemory   A pointer to the memory for the hardware abstraction layer object
//! \param[in]  numBytes  The number of bytes allocated for the hardware abstraction layer object, bytes
//! \return     The hardware abstraction layer (HAL_MTR) object handle
extern HAL_MTR_Handle HAL_MTR1_init(void *pMemory, const size_t numBytes);


//! \brief      Initializes the interrupt vector table
//! \details    Points the ISR to the function mainISR.
//! \param[in]  handle  The hardware abstraction layer (HAL) handle
static inline void HAL_initIntVectorTable(HAL_Handle handle)
{
    // Motor_1->ADCA_INT1
    Interrupt_register(MTR1_PIE_INT_NUM, &motor1CtrlISR);


    return;
} // end of HAL_initIntVectorTable() function

//! \brief      Reads the ADC data with offset
//! \details    Reads in the ADC result registers and scales the values
//!             according to the settings in user_m1.h or user_m2.h.
//!             The structure gAdcData holds three phase voltages,
//!             three line currents, and one DC bus voltage.
//! \param[in]  handle    The hardware abstraction layer (HAL) handle
//! \param[in]  pADCData  A pointer to the ADC data buffer
static inline void
HAL_readMtr1ADCData(HAL_ADCData_t *pADCData)
{
    float32_t value;                // Single-shunt, full 3-shunt

    // convert phase A current
    value = (float32_t)ADC_readPPBResult(MTR1_IU_ADC_SOC_NUM_RESULT_BASE, MTR1_IU_ADC_PPB_NUM);
    pADCData->I_A.value[0] = value * pADCData->current_sf;

    // convert phase B current
    value = (float32_t)ADC_readPPBResult(MTR1_IV_ADC_SOC_NUM_RESULT_BASE, MTR1_IV_ADC_PPB_NUM);
    pADCData->I_A.value[1] = value * pADCData->current_sf;

    // convert phase C current
    value = (float32_t)ADC_readPPBResult(MTR1_IW_ADC_SOC_NUM_RESULT_BASE, MTR1_IW_ADC_PPB_NUM);
    pADCData->I_A.value[2] = value * pADCData->current_sf;

    // convert phase A voltage
    value = (float32_t)ADC_readResult(MTR1_VU_ADC_SOC_NUM_RESULT_BASE, MTR1_VU_ADC_SOC_NUM);
    pADCData->V_V.value[0] = value * pADCData->voltage_sf;

    // convert phase B voltage
    value = (float32_t)ADC_readResult(MTR1_VV_ADC_SOC_NUM_RESULT_BASE, MTR1_VV_ADC_SOC_NUM);
    pADCData->V_V.value[1] = value * pADCData->voltage_sf;

    // convert phase C voltage
    value = (float32_t)ADC_readResult(MTR1_VW_ADC_SOC_NUM_RESULT_BASE, MTR1_VW_ADC_SOC_NUM);
    pADCData->V_V.value[2] = value * pADCData->voltage_sf;

    // convert dc bus voltage
    value = (float32_t)ADC_readResult(MTR1_VDC_ADC_SOC_NUM_RESULT_BASE, MTR1_VDC_ADC_SOC_NUM);
    pADCData->VdcBus_V = value * pADCData->dcBusvoltage_sf;


    return;
} // end of HAL_readMtr1ADCData() functions

//! \brief     Reads the timer count
//! \param[in] handle       The hardware abstraction layer (HAL) handle
//! \param[in] timerNumber  The timer number, 0,1 or 2
//! \return    The timer count
static inline uint32_t
HAL_readTimerCnt(HAL_Handle handle,const uint16_t timerNumber)
{
    HAL_Obj *obj = (HAL_Obj *)handle;

    uint32_t timerCnt = CPUTimer_getTimerCount(obj->timerHandle[timerNumber]);

    return(timerCnt);
} // end of HAL_readTimerCnt() function

//! \brief     Sets the GPIO pin high
//! \param[in] handle      The hardware abstraction layer (HAL) handle
//! \param[in] gpioNumber  The GPIO number
static inline void HAL_setGPIOHigh(HAL_Handle handle,const uint32_t gpioNumber)
{

  // set GPIO high
  GPIO_writePin(gpioNumber, 1);

  return;
} // end of HAL_setGPIOHigh() function

//! \brief     Read the GPIO pin
//! \param[in] handle      The hardware abstraction layer (HAL) handle
//! \param[in] gpioNumber  The GPIO number
//! \return    The GPIO pin
static inline uint32_t
HAL_readGPIOData(HAL_Handle handle,const uint32_t gpioNumber)
{
    uint32_t gpioPinData;

    // set GPIO high
    gpioPinData = GPIO_readPin(gpioNumber);

    return(gpioPinData);
} // end of HAL_readGPIOData() function

//! \brief     Sets the GPIO pin low
//! \param[in] handle      The hardware abstraction layer (HAL) handle
//! \param[in] gpioNumber  The GPIO number
static inline void HAL_setGPIOLow(HAL_Handle handle,const uint32_t gpioNumber)
{
    // set GPIO low
    GPIO_writePin(gpioNumber, 0);

    return;
} // end of HAL_setGPIOLow() function

//! \brief     Sets the value of the internal DAC of the high comparator
//! \param[in] handle      The hardware abstraction layer (HAL) handle
//! \param[in] cmpssNumber The CMPSS number
//! \param[in] dacValue    The DAC value of the high comparator
static inline void
HAL_setCMPSSDACValueHigh(HAL_MTR_Handle handle,
                         const uint16_t cmpssNumber, uint16_t dacValue)
{
    HAL_MTR_Obj *obj = (HAL_MTR_Obj *)handle;

    // set GPIO low
    CMPSS_setDACValueHigh(obj->cmpssHandle[cmpssNumber], dacValue);

    return;
} // end of HAL_setCMPSSDACValueHigh() function

//! \brief     Sets the value of the internal DAC of the low comparator
//! \param[in] handle      The hardware abstraction layer (HAL) handle
//! \param[in] cmpssNumber The CMPSS number
//! \param[in] dacValue    The DAC value of the low comparator
static inline void
HAL_setCMPSSDACValueLow(HAL_MTR_Handle handle,
                        const uint16_t cmpssNumber, uint16_t dacValue)
{
  HAL_MTR_Obj *obj = (HAL_MTR_Obj *)handle;

  // set GPIO low
  CMPSS_setDACValueLow(obj->cmpssHandle[cmpssNumber], dacValue);

  return;
} // end of HAL_setCMPSSDACValueLow() function

//! \brief     Sets the number of voltage sensors
//! \param[in] handle             The hardware abstraction layer (HAL) handle
//! \param[in] numVoltageSensors  The number of voltage sensors
static inline void
HAL_setNumVoltageSensors(HAL_MTR_Handle handle,const uint16_t numVoltageSensors)
{
  HAL_MTR_Obj *obj = (HAL_MTR_Obj *)handle;

  obj->numVoltageSensors = numVoltageSensors;

  return;
} // end of HAL_setNumVoltageSensors() function

//! \brief     Sets the number of current sensors
//! \param[in] handle             The hardware abstraction layer (HAL) handle
//! \param[in] numCurrentSensors  The number of current sensors
static inline void
HAL_setNumCurrentSensors(HAL_MTR_Handle handle,const uint16_t numCurrentSensors)
{
  HAL_MTR_Obj *obj = (HAL_MTR_Obj *)handle;

  obj->numCurrentSensors = numCurrentSensors;

  return;
} // end of HAL_setNumCurrentSensors() function

//! \brief      Sets the hardware abstraction layer parameters
//! \details    Sets up the microcontroller peripherals.  Creates all of the scale
//!             factors for the ADC voltage and current conversions.  Sets the initial
//!             offset values for voltage and current measurements.
//! \param[in]  handle       The hardware abstraction layer (HAL) handle
extern void HAL_setParams(HAL_Handle handle);

//! \brief      Sets the hardware abstraction layer parameters
//! \details    Sets up the microcontroller peripherals.  Creates all of the scale
//!             factors for the ADC voltage and current conversions.  Sets the initial
//!             offset values for voltage and current measurements.
//! \param[in]  handle       The hardware abstraction layer (HAL) handle
extern void HAL_MTR_setParams(HAL_MTR_Handle handle, USER_Params *pUserParams);


//! \brief      Enables the gate driver
//! \details    Provides the correct timing to enable the gate driver
//! \param[in]  handle  The hardware abstraction layer (HAL) handle
extern void HAL_enableDRV(HAL_MTR_Handle handle);



//! \brief     Sets up the CPU timer for time base
//! \param[in] handle          The hardware abstraction layer (HAL) handle
//! \param[in] timeBaseFreq_Hz The time base frequency, MHz
extern void HAL_setupTimeBaseTimer(HAL_Handle handle,
                                   const float32_t timeBaseFreq_Hz);

//! \brief     Sets up the timers for CPU usage diagnostics
//! \param[in] handle          The hardware abstraction layer (HAL) handle
extern void HAL_setupCPUUsageTimer(HAL_Handle handle);     


//! Sets the CPU timer period count.
//! \param base is the base address of the timer module.
//! \param timerCount is the CPU timer timer count.
static inline void HAL_setCPUTimerCount(HAL_Handle halHandle, uint32_t timerCount)
{
    HAL_Obj   *obj = (HAL_Obj *)halHandle;

    //
    // Load the MSB timer Count
    //
    HWREG(obj->timerHandle[1] + CPUTIMER_O_TIM) = timerCount;

    return;
}                                

//! \brief     Sets up the timers
//! \param[in] handle          The hardware abstraction layer (HAL) handle
//! \param[in] cpuTimerNumber  The CPU timer number
static inline void
HAL_clearCPUTimerFlag(HAL_Handle halHandle, const uint16_t cpuTimerNumber)
{
    HAL_Obj   *obj = (HAL_Obj *)halHandle;

    CPUTimer_clearOverflowFlag(obj->timerHandle[cpuTimerNumber]);

    return;
}   // end of HAL_clearTimerFlag() function

//! \brief     Gets CPU Timer status
//! \param[in] handle          The hardware abstraction layer (HAL) handle
//! \param[in] cpuTimerNumber  The CPU timer number
static inline bool
HAL_getCPUTimerStatus(HAL_Handle halHandle, const uint16_t cpuTimerNumber)
{
    HAL_Obj   *obj = (HAL_Obj *)halHandle;

    return (CPUTimer_getTimerOverflowStatus(obj->timerHandle[cpuTimerNumber]));
}

//! \brief     Sets up the DMA
//! \param[in] N/A
void HAL_setupDMA(void);



//! \brief     Toggles the GPIO pin
//! \param[in] handle      The hardware abstraction layer (HAL) handle
//! \param[in] gpioNumber  The GPIO number
static inline void HAL_toggleGPIO(HAL_Handle handle,const uint32_t gpioNumber)
{

    // set GPIO high
    GPIO_togglePin(gpioNumber);

    return;
} // end of HAL_toggleGPIO() function


//! \brief     Sets up the PIE (Peripheral Interrupt Expansion)
//! \param[in] handle  The hardware abstraction layer (HAL) handle
extern void HAL_setupPIE(HAL_Handle handle);

//! Setup the EPWM Run-Time Parameters
extern void HAL_setupPWMs(HAL_MTR_Handle handle);


//! \brief     Sets up the QEP peripheral
//! \param[in] handle  The hardware abstraction layer (HAL) handle
extern void HAL_setupQEP(HAL_MTR_Handle handle);



//! \brief     Writes DAC data to the PWM comparators for DAC output
//! \param[in] handle    The hardware abstraction layer (HAL) handle
//! \param[in] pPWMDACData  The pointer to the DAC data
void HAL_setPWMDACParameters(HAL_Handle handle, HAL_PWMDACData_t *pPWMDACData);

//! \brief
//! \param[in]
//! \param[in]
void HAL_clearDataRAM(void *pMemory, uint16_t lengthMemory);

//! \brief     Reads PWM period register
//! \param[in] handle     The hardware abstraction layer (HAL) handle
//! \param[in] pwmNumber  The PWM number
//! \return    The PWM period value
static inline uint16_t
HAL_readPWMPeriod(HAL_MTR_Handle handle,const uint16_t pwmNumber)
{
  HAL_MTR_Obj *obj = (HAL_MTR_Obj *)handle;

  // the period value to be returned
  uint16_t pwmPeriodValue;
  pwmPeriodValue = EPWM_getTimeBasePeriod(obj->pwmHandle[pwmNumber]);

  return(pwmPeriodValue);
} // end of HAL_readPWMPeriod() function

//! \brief     Writes PWM data to the PWM comparators for motor control
//! \param[in] handle    The hardware abstraction layer (HAL) handle
//! \param[in] pPWMData  The pointer to the PWM data
static inline void
HAL_writePWMData(HAL_MTR_Handle handle, HAL_PWMData_t *pPWMData)
{
    HAL_MTR_Obj *obj = (HAL_MTR_Obj *)handle;

    float32_t period = (float32_t)(EPWM_getTimeBasePeriod(obj->pwmHandle[0]));
    uint16_t pwmCnt;

    for(pwmCnt=0; pwmCnt<3; pwmCnt++)
    {
        // compute the value
        float32_t V_pu = -pPWMData->Vabc_pu.value[pwmCnt];      // Negative
        float32_t V_sat_pu = __fsat(V_pu, 0.5f, -0.5f);         // -0.5~0.5
        float32_t V_sat_dc_pu = V_sat_pu + 0.5f;                // 0~1.0
        pPWMData->cmpValue[pwmCnt]  = (int16_t)(V_sat_dc_pu * period);  //

        if(pPWMData->cmpValue[pwmCnt] < pPWMData->minCMPValue)
        {
            pPWMData->cmpValue[pwmCnt] = pPWMData->minCMPValue;
        }

        // write the PWM data value
        EPWM_setCounterCompareValue(obj->pwmHandle[pwmCnt],
                                    EPWM_COUNTER_COMPARE_A,
                                    pPWMData->cmpValue[pwmCnt]);

        EPWM_setCounterCompareValue(obj->pwmHandle[pwmCnt],
                                    EPWM_COUNTER_COMPARE_B,
                                    pPWMData->cmpValue[pwmCnt]);
    }


    return;
} // end of HAL_writePWMData() function


//! \brief      Enables the PWM devices for motor control
//! \details    Turns on the outputs of the EPWM peripheral which will allow
//!             the power switches to be controlled.
//! \param[in]  handle  The hardware abstraction layer (HAL) handle
static inline void HAL_enablePWM(HAL_MTR_Handle handle)
{
    HAL_MTR_Obj *obj = (HAL_MTR_Obj *)handle;

    // Clear any comparator digital filter output latch
    CMPSS_clearFilterLatchHigh(obj->cmpssHandle[0]);
    CMPSS_clearFilterLatchLow(obj->cmpssHandle[0]);

    CMPSS_clearFilterLatchHigh(obj->cmpssHandle[1]);
    CMPSS_clearFilterLatchLow(obj->cmpssHandle[1]);

    CMPSS_clearFilterLatchHigh(obj->cmpssHandle[2]);
    CMPSS_clearFilterLatchLow(obj->cmpssHandle[2]);

    // Clear any Trip Zone flag
    EPWM_clearTripZoneFlag(obj->pwmHandle[0], HAL_TZFLAG_INTERRUPT_ALL);
    EPWM_clearTripZoneFlag(obj->pwmHandle[1], HAL_TZFLAG_INTERRUPT_ALL);
    EPWM_clearTripZoneFlag(obj->pwmHandle[2], HAL_TZFLAG_INTERRUPT_ALL);

    obj->flagEnablePWM = true;

    return;
} // end of HAL_enablePWM() function

//! \brief      Enables the PWM for braking
//! \details    Turns on the outputs of the EPWM peripheral which will allow
//!             the power switches to be controlled.
//! \param[in]  handle  The hardware abstraction layer (HAL) handle
static inline void HAL_enableBrakePWM(HAL_MTR_Handle handle)
{
    HAL_MTR_Obj *obj = (HAL_MTR_Obj *)handle;
    uint16_t  cnt;


    for(cnt=0; cnt<3; cnt++)
    {
        // setup the Action-qualifier Continuous Software Force Register (AQCSFRC)
         EPWM_setActionQualifierContSWForceAction(obj->pwmHandle[cnt],
                                                  EPWM_AQ_OUTPUT_A,
                                                  EPWM_AQ_SW_OUTPUT_LOW);

        // setup the Action-qualifier Continuous Software Force Register (AQCSFRC)
         EPWM_setActionQualifierContSWForceAction(obj->pwmHandle[cnt],
                                                  EPWM_AQ_OUTPUT_B,
                                                  EPWM_AQ_SW_OUTPUT_HIGH);

         // setup the Dead-Band Generator Control Register (DBCTL)
         EPWM_setDeadBandDelayMode(obj->pwmHandle[cnt], EPWM_DB_RED, false);
         EPWM_setDeadBandDelayMode(obj->pwmHandle[cnt], EPWM_DB_FED, false);
    }


    obj->flagEnablePWM = false;

    return;
} // end of HAL_enableBrakePWM() function

//! \brief      Enables the PWM for braking
//! \details    Turns on the outputs of the EPWM peripheral which will allow
//!             the power switches to be controlled.
//! \param[in]  handle  The hardware abstraction layer (HAL) handle
static inline void HAL_exitBrakeResetPWM(HAL_MTR_Handle handle)
{
    HAL_MTR_Obj *obj = (HAL_MTR_Obj *)handle;
    uint16_t  cnt;


    for(cnt=0; cnt<3; cnt++)
    {
        // setup the Dead-Band Generator Control Register (DBCTL)
        EPWM_setDeadBandDelayMode(obj->pwmHandle[cnt], EPWM_DB_RED, true);
        EPWM_setDeadBandDelayMode(obj->pwmHandle[cnt], EPWM_DB_FED, true);

        // setup the Action-qualifier Continuous Software Force Register (AQCSFRC)
         EPWM_setActionQualifierContSWForceAction(obj->pwmHandle[cnt],
                                                  EPWM_AQ_OUTPUT_A,
                                                  EPWM_AQ_SW_DISABLED);

        // setup the Action-qualifier Continuous Software Force Register (AQCSFRC)
         EPWM_setActionQualifierContSWForceAction(obj->pwmHandle[cnt],
                                                  EPWM_AQ_OUTPUT_B,
                                                  EPWM_AQ_SW_DISABLED);
    }


    obj->flagEnablePWM = false;

    return;
} // end of HAL_exitBrakeResetPWM() function

//! \brief      clear fault status of motor control
//! \details
//! \param[in]  handle  The hardware abstraction layer (HAL) handle
static inline void HAL_clearMtrFaultStatus(HAL_MTR_Handle handle)
{
    HAL_MTR_Obj *obj = (HAL_MTR_Obj *)handle;

    // Clear any comparator digital filter output latch
    CMPSS_clearFilterLatchHigh(obj->cmpssHandle[0]);

    CMPSS_clearFilterLatchHigh(obj->cmpssHandle[1]);
    CMPSS_clearFilterLatchLow(obj->cmpssHandle[1]);

    CMPSS_clearFilterLatchLow(obj->cmpssHandle[2]);

    // Clear any Trip Zone flag
    // Clear any Trip Zone flag
    EPWM_clearTripZoneFlag(obj->pwmHandle[0], HAL_TZFLAG_INTERRUPT_ALL);
    EPWM_clearTripZoneFlag(obj->pwmHandle[1], HAL_TZFLAG_INTERRUPT_ALL);
    EPWM_clearTripZoneFlag(obj->pwmHandle[2], HAL_TZFLAG_INTERRUPT_ALL);
    return;
} // end of HAL_clearMtrFaultStatus() function

//! \brief      Disables the PWM device for motor control
//! \details    Turns off the outputs of the EPWM peripherals which will put
//!             the power switches into a high impedance state.
//! \param[in]  handle  The hardware abstraction layer (HAL) handle
static inline void HAL_disablePWM(HAL_MTR_Handle handle)
{
    HAL_MTR_Obj *obj = (HAL_MTR_Obj *)handle;

    EPWM_forceTripZoneEvent(obj->pwmHandle[0], EPWM_TZ_FORCE_EVENT_OST);
    EPWM_forceTripZoneEvent(obj->pwmHandle[1], EPWM_TZ_FORCE_EVENT_OST);
    EPWM_forceTripZoneEvent(obj->pwmHandle[2], EPWM_TZ_FORCE_EVENT_OST);


    obj->flagEnablePWM = false;

    return;
} // end of HAL_disablePWM() function

//! \brief     Sets up the PWMs (Pulse Width Modulators)
//! \param[in] handle          The hardware abstraction layer (HAL) handle
static inline uint32_t HAL_getMtrTripFaults(HAL_MTR_Handle handle)
{
    HAL_MTR_Obj *obj = (HAL_MTR_Obj *)handle;
    uint32_t tripFault = 0;

    tripFault = (EPWM_getTripZoneFlagStatus(obj->pwmHandle[0]) &
            (EPWM_TZ_FLAG_OST | EPWM_TZ_FLAG_DCAEVT1 | EPWM_TZ_FLAG_DCAEVT2)) |
                    (EPWM_getTripZoneFlagStatus(obj->pwmHandle[1]) &
            (EPWM_TZ_FLAG_OST | EPWM_TZ_FLAG_DCAEVT1 | EPWM_TZ_FLAG_DCAEVT2)) |
                    (EPWM_getTripZoneFlagStatus(obj->pwmHandle[2]) &
            (EPWM_TZ_FLAG_OST | EPWM_TZ_FLAG_DCAEVT1 | EPWM_TZ_FLAG_DCAEVT2));

    return(tripFault);
}

//! \brief     Sets up the PWMs (Pulse Width Modulators)
//! \param[in] handle          The hardware abstraction layer (HAL) handle
extern void HAL_setMtrCMPSSDACValue(HAL_MTR_Handle handle,
                               const uint16_t dacValH, const uint16_t dacValL);




//! \brief     Update the PWMs (Pulse Width Modulators) period
//! \param[in] handle          The hardware abstraction layer (HAL) handle
extern void HAL_updatePWMsPeriod(HAL_MTR_Handle handle,
                         float32_t pwmControl_kHz, uint16_t controlTicksPWM);

//! \brief     Sets up the PWMs (Pulse Width Modulators)
//! \param[in] handle          The hardware abstraction layer (HAL) handle
extern void HAL_setupPWMs(HAL_MTR_Handle handle);

//! \brief     Sets up the PWMs (Pulse Width Modulators)
//! \param[in] handle          The hardware abstraction layer (HAL) handle
extern void HAL_resetPWMs(HAL_MTR_Handle handle);

//! \brief     Sets up the PWMs (Pulse Width Modulators)
//! \param[in] handle          The hardware abstraction layer (HAL) handle
extern void HAL_setMtrCMPSSDACValue(HAL_MTR_Handle handle,
                               const uint16_t dacValH, const uint16_t dacValL);

//! \brief     Set trigger point in the middle of the low side pulse
//! \param[in] handle    The hardware abstraction layer (HAL) handle
//! \param[in] deadband     The setting deadband for mosfet gate driver
//! \param[in] noisewindow  The noise window
//! \param[in] adcSample_us The adc sample time
//! \param[in] muxSwitch_us If present, PGA mux switching time
//! \param[in] PGA_settlingTime_us If present, PGA mux settling time
//! \param[in] switchInstruction_cycles If present, number of cycles for a PGA mux switch write via DMA or ISR
extern void HAL_setTriggerPrams(HAL_PWMData_t *pPWMData, const float32_t systemFreq_MHz,
                                const float32_t deadband_us, const float32_t noiseWindow_us,
                                const float32_t adcSample_us);

//! \brief     Get PWM period
//! \param[in] handle    The hardware abstraction layer (HAL) handle
extern void HAL_getPWMPeriod(HAL_MTR_Handle handle, HAL_PWMData_t *pPWMData);

//! \brief     Sets up the gate driver for inverter board
//! \param[in] handle  The hardware abstraction layer (HAL) handle
extern bool HAL_MTR_setGateDriver(HAL_MTR_Handle handle);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif

