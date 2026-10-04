/*
 * Copyright (c) 2020 Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef BOARD_H
#define BOARD_H

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

//
// Included Files
//

#include "driverlib.h"
#include "device.h"

//*****************************************************************************
//
// PinMux Configurations
//
//*****************************************************************************

//
// ANALOG -> myANALOGPinMux0 Pinmux
//

//
// EPWM1 -> MTR1_EPWM_U Pinmux
//
//
// EPWM1_A - GPIO Settings
//
#define GPIO_PIN_EPWM1_A 0
#define MTR1_EPWM_U_EPWMA_GPIO 0
#define MTR1_EPWM_U_EPWMA_PIN_CONFIG GPIO_0_EPWM1_A
//
// EPWM1_B - GPIO Settings
//
#define GPIO_PIN_EPWM1_B 1
#define MTR1_EPWM_U_EPWMB_GPIO 1
#define MTR1_EPWM_U_EPWMB_PIN_CONFIG GPIO_1_EPWM1_B

//
// EPWM2 -> MTR1_EPWM_V Pinmux
//
//
// EPWM2_A - GPIO Settings
//
#define GPIO_PIN_EPWM2_A 2
#define MTR1_EPWM_V_EPWMA_GPIO 2
#define MTR1_EPWM_V_EPWMA_PIN_CONFIG GPIO_2_EPWM2_A
//
// EPWM2_B - GPIO Settings
//
#define GPIO_PIN_EPWM2_B 3
#define MTR1_EPWM_V_EPWMB_GPIO 3
#define MTR1_EPWM_V_EPWMB_PIN_CONFIG GPIO_3_EPWM2_B

//
// EPWM6 -> MTR1_EPWM_W Pinmux
//
//
// EPWM6_A - GPIO Settings
//
#define GPIO_PIN_EPWM6_A 10
#define MTR1_EPWM_W_EPWMA_GPIO 10
#define MTR1_EPWM_W_EPWMA_PIN_CONFIG GPIO_10_EPWM6_A
//
// EPWM6_B - GPIO Settings
//
#define GPIO_PIN_EPWM6_B 11
#define MTR1_EPWM_W_EPWMB_GPIO 11
#define MTR1_EPWM_W_EPWMB_PIN_CONFIG GPIO_11_EPWM6_B
//
// GPIO29 - GPIO Settings
//
#define MTR1_GATE_EN_GPIO_GPIO_PIN_CONFIG GPIO_29_GPIO29
//
// GPIO22 - GPIO Settings
//
#define MTR1_GATE_MODE_GPIO_GPIO_PIN_CONFIG GPIO_22_GPIO22
//
// GPIO47 - GPIO Settings
//
#define MTR1_GATE_GAIN_GPIO_GPIO_PIN_CONFIG GPIO_47_GPIO47
//
// GPIO48 - GPIO Settings
//
#define MTR1_GATE_CAL_GPIO_GPIO_PIN_CONFIG GPIO_48_GPIO48
//
// GPIO24 - GPIO Settings
//
#define MTR1_PM_nFAULT_GPIO_GPIO_PIN_CONFIG GPIO_24_GPIO24

//
// SCIB -> MotorControlWorkbench_transferLayer_SCI Pinmux
//
//
// SCIB_RX - GPIO Settings
//
#define GPIO_PIN_SCIB_RX 15
#define MotorControlWorkbench_transferLayer_SCI_SCIRX_GPIO 15
#define MotorControlWorkbench_transferLayer_SCI_SCIRX_PIN_CONFIG GPIO_15_SCIB_RX
//
// SCIB_TX - GPIO Settings
//
#define GPIO_PIN_SCIB_TX 56
#define MotorControlWorkbench_transferLayer_SCI_SCITX_GPIO 56
#define MotorControlWorkbench_transferLayer_SCI_SCITX_PIN_CONFIG GPIO_56_SCIB_TX

//*****************************************************************************
//
// ADC Configurations
//
//*****************************************************************************
#define MTR1_ADCA_BASE ADCA_BASE
#define MTR1_ADCA_RESULT_BASE ADCARESULT_BASE
#define MTR1_IV_ADC_SOC_NUM ADC_SOC_NUMBER0
#define MTR1_IV_ADC_SOC_NUM_FORCE ADC_FORCE_SOC0
#define MTR1_IV_ADC_SOC_NUM_ADC_BASE ADCA_BASE
#define MTR1_IV_ADC_SOC_NUM_RESULT_BASE ADCARESULT_BASE
#define MTR1_IV_ADC_SOC_NUM_SAMPLE_WINDOW 120
#define MTR1_IV_ADC_SOC_NUM_TRIGGER_SOURCE ADC_TRIGGER_EPWM1_SOCA
#define MTR1_IV_ADC_SOC_NUM_CHANNEL ADC_CH_ADCIN2
#define MTR1_VU_ADC_SOC_NUM ADC_SOC_NUMBER1
#define MTR1_VU_ADC_SOC_NUM_FORCE ADC_FORCE_SOC1
#define MTR1_VU_ADC_SOC_NUM_ADC_BASE ADCA_BASE
#define MTR1_VU_ADC_SOC_NUM_RESULT_BASE ADCARESULT_BASE
#define MTR1_VU_ADC_SOC_NUM_SAMPLE_WINDOW 173.33333333333334
#define MTR1_VU_ADC_SOC_NUM_TRIGGER_SOURCE ADC_TRIGGER_EPWM1_SOCA
#define MTR1_VU_ADC_SOC_NUM_CHANNEL ADC_CH_ADCIN6
#define MTR1_IV_ADC_PPB_NUM ADC_PPB_NUMBER1
#define MTR1_IV_ADC_PPB_NUM_SOC ADC_SOC_NUMBER0
void MTR1_ADCA_init();

#define MTR1_VDC_BASE ADCB_BASE
#define MTR1_VDC_RESULT_BASE ADCBRESULT_BASE
#define MTR1_IU_ADC_SOC_NUM ADC_SOC_NUMBER0
#define MTR1_IU_ADC_SOC_NUM_FORCE ADC_FORCE_SOC0
#define MTR1_IU_ADC_SOC_NUM_ADC_BASE ADCB_BASE
#define MTR1_IU_ADC_SOC_NUM_RESULT_BASE ADCBRESULT_BASE
#define MTR1_IU_ADC_SOC_NUM_SAMPLE_WINDOW 120
#define MTR1_IU_ADC_SOC_NUM_TRIGGER_SOURCE ADC_TRIGGER_EPWM1_SOCA
#define MTR1_IU_ADC_SOC_NUM_CHANNEL ADC_CH_ADCIN3
#define MTR1_VV_ADC_SOC_NUM ADC_SOC_NUMBER1
#define MTR1_VV_ADC_SOC_NUM_FORCE ADC_FORCE_SOC1
#define MTR1_VV_ADC_SOC_NUM_ADC_BASE ADCB_BASE
#define MTR1_VV_ADC_SOC_NUM_RESULT_BASE ADCBRESULT_BASE
#define MTR1_VV_ADC_SOC_NUM_SAMPLE_WINDOW 173.33333333333334
#define MTR1_VV_ADC_SOC_NUM_TRIGGER_SOURCE ADC_TRIGGER_EPWM1_SOCA
#define MTR1_VV_ADC_SOC_NUM_CHANNEL ADC_CH_ADCIN2
#define MTR1_VDC_ADC_SOC_NUM ADC_SOC_NUMBER2
#define MTR1_VDC_ADC_SOC_NUM_FORCE ADC_FORCE_SOC2
#define MTR1_VDC_ADC_SOC_NUM_ADC_BASE ADCB_BASE
#define MTR1_VDC_ADC_SOC_NUM_RESULT_BASE ADCBRESULT_BASE
#define MTR1_VDC_ADC_SOC_NUM_SAMPLE_WINDOW 173.33333333333334
#define MTR1_VDC_ADC_SOC_NUM_TRIGGER_SOURCE ADC_TRIGGER_EPWM1_SOCA
#define MTR1_VDC_ADC_SOC_NUM_CHANNEL ADC_CH_ADCIN11
#define MTR1_IU_ADC_PPB_NUM ADC_PPB_NUMBER1
#define MTR1_IU_ADC_PPB_NUM_SOC ADC_SOC_NUMBER0
void MTR1_VDC_init();

#define MTR1_ADCC_BASE ADCC_BASE
#define MTR1_ADCC_RESULT_BASE ADCCRESULT_BASE
#define MTR1_IW_ADC_SOC_NUM ADC_SOC_NUMBER0
#define MTR1_IW_ADC_SOC_NUM_FORCE ADC_FORCE_SOC0
#define MTR1_IW_ADC_SOC_NUM_ADC_BASE ADCC_BASE
#define MTR1_IW_ADC_SOC_NUM_RESULT_BASE ADCCRESULT_BASE
#define MTR1_IW_ADC_SOC_NUM_SAMPLE_WINDOW 120
#define MTR1_IW_ADC_SOC_NUM_TRIGGER_SOURCE ADC_TRIGGER_EPWM1_SOCA
#define MTR1_IW_ADC_SOC_NUM_CHANNEL ADC_CH_ADCIN4
#define MTR1_VW_ADC_SOC_NUM ADC_SOC_NUMBER1
#define MTR1_VW_ADC_SOC_NUM_FORCE ADC_FORCE_SOC1
#define MTR1_VW_ADC_SOC_NUM_ADC_BASE ADCC_BASE
#define MTR1_VW_ADC_SOC_NUM_RESULT_BASE ADCCRESULT_BASE
#define MTR1_VW_ADC_SOC_NUM_SAMPLE_WINDOW 173.33333333333334
#define MTR1_VW_ADC_SOC_NUM_TRIGGER_SOURCE ADC_TRIGGER_EPWM1_SOCA
#define MTR1_VW_ADC_SOC_NUM_CHANNEL ADC_CH_ADCIN0
#define MTR1_IW_ADC_PPB_NUM ADC_PPB_NUMBER1
#define MTR1_IW_ADC_PPB_NUM_SOC ADC_SOC_NUMBER0
void MTR1_ADCC_init();


//*****************************************************************************
//
// ASYSCTL Configurations
//
//*****************************************************************************

//*****************************************************************************
//
// CMPSS Configurations
//
//*****************************************************************************
#define cmpss_CMPSS3_BASE CMPSS3_BASE
#define MTR1_CMPSS_U_BASE CMPSS3_BASE    
#define MTR1_CMPSS_W_BASE CMPSS3_BASE    
void cmpss_CMPSS3_init();
#define cmpss_CMPSS1_BASE CMPSS1_BASE
#define MTR1_CMPSS_V_BASE CMPSS1_BASE    
#define cmpss_CMPSS1_LOW_COMP_BASE CMPSS1_BASE    
void cmpss_CMPSS1_init();

//*****************************************************************************
//
// CPUTIMER Configurations
//
//*****************************************************************************
#define BACKGROUND_TIMER_BASE CPUTIMER0_BASE
void BACKGROUND_TIMER_init();
#define CPU_USAGE_TIMER_BASE CPUTIMER1_BASE
void CPU_USAGE_TIMER_init();
#define SYS_RTOS_TIMER_BASE CPUTIMER2_BASE
void SYS_RTOS_TIMER_init();

//*****************************************************************************
//
// EPWM Configurations
//
//*****************************************************************************
#define MTR1_EPWM_U_BASE EPWM1_BASE
#define MTR1_EPWM_U_TBPRD 65535
#define MTR1_EPWM_U_COUNTER_MODE EPWM_COUNTER_MODE_UP_DOWN
#define MTR1_EPWM_U_TBPHS 0
#define MTR1_EPWM_U_CMPA 5
#define MTR1_EPWM_U_CMPB 5
#define MTR1_EPWM_U_CMPC 5
#define MTR1_EPWM_U_CMPD 5
#define MTR1_EPWM_U_DBRED 10
#define MTR1_EPWM_U_DBFED 10
#define MTR1_EPWM_U_TZA_ACTION EPWM_TZ_ACTION_HIGH_Z
#define MTR1_EPWM_U_TZB_ACTION EPWM_TZ_ACTION_HIGH_Z
#define MTR1_EPWM_U_OSHT_SOURCES (EPWM_TZ_SIGNAL_DCAEVT1 | EPWM_TZ_SIGNAL_DCBEVT1 | EPWM_TZ_SIGNAL_OSHT1)
#define MTR1_EPWM_U_INTERRUPT_SOURCE EPWM_INT_TBCTR_ZERO
#define MTR1_EPWM_V_BASE EPWM2_BASE
#define MTR1_EPWM_V_TBPRD 65535
#define MTR1_EPWM_V_COUNTER_MODE EPWM_COUNTER_MODE_UP_DOWN
#define MTR1_EPWM_V_TBPHS 0
#define MTR1_EPWM_V_CMPA 5
#define MTR1_EPWM_V_CMPB 5
#define MTR1_EPWM_V_CMPC 5
#define MTR1_EPWM_V_CMPD 5
#define MTR1_EPWM_V_DBRED 10
#define MTR1_EPWM_V_DBFED 10
#define MTR1_EPWM_V_TZA_ACTION EPWM_TZ_ACTION_HIGH_Z
#define MTR1_EPWM_V_TZB_ACTION EPWM_TZ_ACTION_HIGH_Z
#define MTR1_EPWM_V_OSHT_SOURCES (EPWM_TZ_SIGNAL_DCAEVT1 | EPWM_TZ_SIGNAL_DCBEVT1 | EPWM_TZ_SIGNAL_OSHT1)
#define MTR1_EPWM_V_INTERRUPT_SOURCE EPWM_INT_TBCTR_ZERO
#define MTR1_EPWM_W_BASE EPWM6_BASE
#define MTR1_EPWM_W_TBPRD 65535
#define MTR1_EPWM_W_COUNTER_MODE EPWM_COUNTER_MODE_UP_DOWN
#define MTR1_EPWM_W_TBPHS 0
#define MTR1_EPWM_W_CMPA 5
#define MTR1_EPWM_W_CMPB 5
#define MTR1_EPWM_W_CMPC 5
#define MTR1_EPWM_W_CMPD 5
#define MTR1_EPWM_W_DBRED 10
#define MTR1_EPWM_W_DBFED 10
#define MTR1_EPWM_W_TZA_ACTION EPWM_TZ_ACTION_HIGH_Z
#define MTR1_EPWM_W_TZB_ACTION EPWM_TZ_ACTION_HIGH_Z
#define MTR1_EPWM_W_OSHT_SOURCES (EPWM_TZ_SIGNAL_DCAEVT1 | EPWM_TZ_SIGNAL_DCBEVT1 | EPWM_TZ_SIGNAL_OSHT1)
#define MTR1_EPWM_W_INTERRUPT_SOURCE EPWM_INT_TBCTR_ZERO

//*****************************************************************************
//
// EPWMXBAR Configurations
//
//*****************************************************************************
void MTR1_IS_TRIP_CMPSS_init();
#define MTR1_IS_TRIP_CMPSS XBAR_TRIP7
#define MTR1_IS_TRIP_CMPSS_ENABLED_MUXES (XBAR_MUX00 | XBAR_MUX04)

//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************
#define MTR1_GATE_EN_GPIO 29
void MTR1_GATE_EN_GPIO_init();
#define MTR1_GATE_MODE_GPIO 22
void MTR1_GATE_MODE_GPIO_init();
#define MTR1_GATE_GAIN_GPIO 47
void MTR1_GATE_GAIN_GPIO_init();
#define MTR1_GATE_CAL_GPIO 48
void MTR1_GATE_CAL_GPIO_init();
#define MTR1_PM_nFAULT_GPIO 24
void MTR1_PM_nFAULT_GPIO_init();

//*****************************************************************************
//
// INPUTXBAR Configurations
//
//*****************************************************************************
#define motor1_XBAR_INPUT1_SOURCE 24
#define motor1_XBAR_INPUT1_INPUT XBAR_INPUT1
void motor1_XBAR_INPUT1_init();

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************

// Interrupt Settings for INT_MotorControlWorkbench_transferLayer_SCI_RX
// ISR need to be defined for the registered interrupts
#define INT_MotorControlWorkbench_transferLayer_SCI_RX INT_SCIB_RX
#define INT_MotorControlWorkbench_transferLayer_SCI_RX_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP9
extern __interrupt void INT_MotorControlWorkbench_transferLayer_SCI_RX_ISR(void);

// Interrupt Settings for INT_MotorControlWorkbench_transferLayer_SCI_TX
// ISR need to be defined for the registered interrupts
#define INT_MotorControlWorkbench_transferLayer_SCI_TX INT_SCIB_TX
#define INT_MotorControlWorkbench_transferLayer_SCI_TX_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP9
extern __interrupt void INT_MotorControlWorkbench_transferLayer_SCI_TX_ISR(void);

// Interrupt Settings for INT_MTR1_VDC_1
// ISR need to be defined for the registered interrupts
#define INT_MTR1_VDC_1 INT_ADCB1
#define INT_MTR1_VDC_1_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP1
extern __interrupt void INT_MTR1_VDC_1_ISR(void);

//*****************************************************************************
//
// SCI Configurations
//
//*****************************************************************************
#define MotorControlWorkbench_transferLayer_SCI_BASE SCIB_BASE
#define MotorControlWorkbench_transferLayer_SCI_BAUDRATE 4687500
#define MotorControlWorkbench_transferLayer_SCI_CONFIG_WLEN SCI_CONFIG_WLEN_8
#define MotorControlWorkbench_transferLayer_SCI_CONFIG_STOP SCI_CONFIG_STOP_ONE
#define MotorControlWorkbench_transferLayer_SCI_CONFIG_PAR SCI_CONFIG_PAR_NONE
#define MotorControlWorkbench_transferLayer_SCI_FIFO_TX_LVL SCI_FIFO_TX0
#define MotorControlWorkbench_transferLayer_SCI_FIFO_RX_LVL SCI_FIFO_RX16
void MotorControlWorkbench_transferLayer_SCI_init();

//*****************************************************************************
//
// SYNC Scheme Configurations
//
//*****************************************************************************

//*****************************************************************************
//
// SYSCTL Configurations
//
//*****************************************************************************

//*****************************************************************************
//
// Board Configurations
//
//*****************************************************************************
void	Board_init();
void	ADC_init();
void	ASYSCTL_init();
void	CMPSS_init();
void	CPUTIMER_init();
void	EPWM_init();
void	EPWMXBAR_init();
void	GPIO_init();
void	INPUTXBAR_init();
void	INTERRUPT_init();
void	SCI_init();
void	SYNC_init();
void	SYSCTL_init();
void	PinMux_init();

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif  // end of BOARD_H definition
