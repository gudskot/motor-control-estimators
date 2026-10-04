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

#include "board.h"

//*****************************************************************************
//
// Board Configurations
// Initializes the rest of the modules. 
// Call this function in your application if you wish to do all module 
// initialization.
// If you wish to not use some of the initializations, instead of the 
// Board_init use the individual Module_inits
//
//*****************************************************************************
void Board_init()
{
	EALLOW;

	PinMux_init();
	SYSCTL_init();
	INPUTXBAR_init();
	SYNC_init();
	ASYSCTL_init();
	ADC_init();
	CMPSS_init();
	CPUTIMER_init();
	EPWM_init();
	EPWMXBAR_init();
	GPIO_init();
	SCI_init();
	INTERRUPT_init();

	EDIS;
}

//*****************************************************************************
//
// PINMUX Configurations
//
//*****************************************************************************
void PinMux_init()
{
	//
	// PinMux for modules assigned to CPU1
	//
	
	//
	// ANALOG -> myANALOGPinMux0 Pinmux
	//
	// Analog PinMux for A0, B15, C15, DACA_OUT
	GPIO_setPinConfig(GPIO_231_GPIO231);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(231, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A2, B6, C9, PGA1_INP, GPIO224
	GPIO_setPinConfig(GPIO_224_GPIO224);
	// AGPIO -> Analog mode selected
	GPIO_setAnalogMode(224, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A3, B9, C7, PGA1_INM
	GPIO_setPinConfig(GPIO_229_GPIO229);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(229, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A4, B8
	GPIO_setPinConfig(GPIO_225_GPIO225);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(225, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A5
	GPIO_setPinConfig(GPIO_249_GPIO249);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(249, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A6, D14, E14, GPIO228
	GPIO_setPinConfig(GPIO_228_GPIO228);
	// AGPIO -> Analog mode selected
	GPIO_setAnalogMode(228, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A7, B30, C3, D12, E30
	GPIO_setPinConfig(GPIO_245_GPIO245);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(245, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A8
	GPIO_setPinConfig(GPIO_240_GPIO240);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(240, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A9, GPIO227
	GPIO_setPinConfig(GPIO_227_GPIO227);
	// AGPIO -> Analog mode selected
	GPIO_setAnalogMode(227, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A10, B1, C10, GPIO230
	GPIO_setPinConfig(GPIO_230_GPIO230);
	// AGPIO -> Analog mode selected
	GPIO_setAnalogMode(230, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A11, B10, C0, PGA2_OUT
	GPIO_setPinConfig(GPIO_237_GPIO237);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(237, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A12, C5
	GPIO_setPinConfig(GPIO_238_GPIO238);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(238, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A14, B14, C4, PGA1_OUT
	GPIO_setPinConfig(GPIO_239_GPIO239);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(239, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A16, B16, C16, GPIO28
	GPIO_setPinConfig(GPIO_28_GPIO28);
	// AGPIO -> Analog mode selected
	GPIO_setAnalogMode(28, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A17, B17, C17, GPIO20
	GPIO_setPinConfig(GPIO_20_GPIO20);
	// AGPIO -> Analog mode selected
	GPIO_setAnalogMode(20, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A18, B18, C18, GPIO21
	GPIO_setPinConfig(GPIO_21_GPIO21);
	// AGPIO -> Analog mode selected
	GPIO_setAnalogMode(21, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A19, B19, C19, GPIO13
	GPIO_setPinConfig(GPIO_13_GPIO13);
	// AGPIO -> Analog mode selected
	GPIO_setAnalogMode(13, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A20, B20, C20, GPIO12
	GPIO_setPinConfig(GPIO_12_GPIO12);
	// AGPIO -> Analog mode selected
	GPIO_setAnalogMode(12, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A25, D3, E3, GPIO17
	GPIO_setPinConfig(GPIO_17_GPIO17);
	// AGPIO -> Analog mode selected
	GPIO_setAnalogMode(17, GPIO_ANALOG_ENABLED);
	// Analog PinMux for B0, C11, GPIO253
	GPIO_setPinConfig(GPIO_253_GPIO253);
	// AGPIO -> Analog mode selected
	GPIO_setAnalogMode(253, GPIO_ANALOG_ENABLED);
	// Analog PinMux for B2, C6, E12, GPIO226
	GPIO_setPinConfig(GPIO_226_GPIO226);
	// AGPIO -> Analog mode selected
	GPIO_setAnalogMode(226, GPIO_ANALOG_ENABLED);
	// Analog PinMux for B3, PGA2_INP, GPIO242
	GPIO_setPinConfig(GPIO_242_GPIO242);
	// AGPIO -> Analog mode selected
	GPIO_setAnalogMode(242, GPIO_ANALOG_ENABLED);
	// Analog PinMux for B4, C8, GPIO236
	GPIO_setPinConfig(GPIO_236_GPIO236);
	// AGPIO -> Analog mode selected
	GPIO_setAnalogMode(236, GPIO_ANALOG_ENABLED);
	// Analog PinMux for B5, D15, E15, PGA3_OUT
	GPIO_setPinConfig(GPIO_252_GPIO252);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(252, GPIO_ANALOG_ENABLED);
	// Analog PinMux for B11, D16, E16, PGA3_INM
	GPIO_setPinConfig(GPIO_251_GPIO251);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(251, GPIO_ANALOG_ENABLED);
	// Analog PinMux for B12, C2, PGA2_INM
	GPIO_setPinConfig(GPIO_244_GPIO244);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(244, GPIO_ANALOG_ENABLED);
	// Analog PinMux for B24, D1, E1, GPIO33
	GPIO_setPinConfig(GPIO_33_GPIO33);
	// AGPIO -> Analog mode selected
	GPIO_setAnalogMode(33, GPIO_ANALOG_ENABLED);
	// Analog PinMux for C1, E11, PGA3_INP
	GPIO_setPinConfig(GPIO_248_GPIO248);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(248, GPIO_ANALOG_ENABLED);
	// Analog PinMux for C14, GPIO247
	GPIO_setPinConfig(GPIO_247_GPIO247);
	// AGPIO -> Analog mode selected
	GPIO_setAnalogMode(247, GPIO_ANALOG_ENABLED);
	// Analog PinMux for C24, D2, E2, GPIO16
	GPIO_setPinConfig(GPIO_16_GPIO16);
	// AGPIO -> Analog mode selected
	GPIO_setAnalogMode(16, GPIO_ANALOG_ENABLED);
	// Analog PinMux for D20, E20, VREFHI
	GPIO_setPinConfig(GPIO_234_GPIO234);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(234, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A13, B13, C13, D13, E13, VREFLO
	GPIO_setPinConfig(GPIO_235_GPIO235);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(235, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A1, B7, D11, CMP1_DACL
	GPIO_setPinConfig(GPIO_232_GPIO232);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(232, GPIO_ANALOG_ENABLED);
	//
	// EPWM1 -> MTR1_EPWM_U Pinmux
	//
	GPIO_setPinConfig(MTR1_EPWM_U_EPWMA_PIN_CONFIG);
	GPIO_setPadConfig(MTR1_EPWM_U_EPWMA_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(MTR1_EPWM_U_EPWMA_GPIO, GPIO_QUAL_SYNC);

	GPIO_setPinConfig(MTR1_EPWM_U_EPWMB_PIN_CONFIG);
	GPIO_setPadConfig(MTR1_EPWM_U_EPWMB_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(MTR1_EPWM_U_EPWMB_GPIO, GPIO_QUAL_SYNC);

	//
	// EPWM2 -> MTR1_EPWM_V Pinmux
	//
	GPIO_setPinConfig(MTR1_EPWM_V_EPWMA_PIN_CONFIG);
	GPIO_setPadConfig(MTR1_EPWM_V_EPWMA_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(MTR1_EPWM_V_EPWMA_GPIO, GPIO_QUAL_SYNC);

	GPIO_setPinConfig(MTR1_EPWM_V_EPWMB_PIN_CONFIG);
	GPIO_setPadConfig(MTR1_EPWM_V_EPWMB_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(MTR1_EPWM_V_EPWMB_GPIO, GPIO_QUAL_SYNC);

	//
	// EPWM6 -> MTR1_EPWM_W Pinmux
	//
	GPIO_setPinConfig(MTR1_EPWM_W_EPWMA_PIN_CONFIG);
	GPIO_setPadConfig(MTR1_EPWM_W_EPWMA_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(MTR1_EPWM_W_EPWMA_GPIO, GPIO_QUAL_SYNC);

	GPIO_setPinConfig(MTR1_EPWM_W_EPWMB_PIN_CONFIG);
	// AGPIO -> GPIO mode selected
	GPIO_setAnalogMode(11, GPIO_ANALOG_DISABLED);
	GPIO_setPadConfig(MTR1_EPWM_W_EPWMB_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(MTR1_EPWM_W_EPWMB_GPIO, GPIO_QUAL_SYNC);

	// GPIO29 -> MTR1_GATE_EN_GPIO Pinmux
	GPIO_setPinConfig(GPIO_29_GPIO29);
	// GPIO22 -> MTR1_GATE_MODE_GPIO Pinmux
	GPIO_setPinConfig(GPIO_22_GPIO22);
	// GPIO47 -> MTR1_GATE_GAIN_GPIO Pinmux
	GPIO_setPinConfig(GPIO_47_GPIO47);
	// GPIO48 -> MTR1_GATE_CAL_GPIO Pinmux
	GPIO_setPinConfig(GPIO_48_GPIO48);
	// B25, D4, E4, GPIO24 -> MTR1_PM_nFAULT_GPIO Pinmux
	GPIO_setPinConfig(GPIO_24_GPIO24);
	// AGPIO -> GPIO mode selected
	GPIO_setAnalogMode(24, GPIO_ANALOG_DISABLED);
	//
	// SCIB -> MotorControlWorkbench_transferLayer_SCI Pinmux
	//
	GPIO_setPinConfig(MotorControlWorkbench_transferLayer_SCI_SCIRX_PIN_CONFIG);
	GPIO_setPadConfig(MotorControlWorkbench_transferLayer_SCI_SCIRX_GPIO, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
	GPIO_setQualificationMode(MotorControlWorkbench_transferLayer_SCI_SCIRX_GPIO, GPIO_QUAL_ASYNC);

	GPIO_setPinConfig(MotorControlWorkbench_transferLayer_SCI_SCITX_PIN_CONFIG);
	GPIO_setPadConfig(MotorControlWorkbench_transferLayer_SCI_SCITX_GPIO, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
	GPIO_setQualificationMode(MotorControlWorkbench_transferLayer_SCI_SCITX_GPIO, GPIO_QUAL_ASYNC);


}

//*****************************************************************************
//
// ADC Configurations
//
//*****************************************************************************
void ADC_init(){
	MTR1_ADCA_init();
	MTR1_VDC_init();
	MTR1_ADCC_init();
}

void MTR1_ADCA_init(){
	//
	// ADC Initialization: Write ADC configurations and power up the ADC
	//
	// Set the analog voltage reference selection and ADC module's offset trims.
	// This function sets the analog voltage reference to internal (with the reference voltage of 1.65V or 2.5V) or external for ADC
	// which is same as ASysCtl APIs.
	//
	ADC_setVREF(MTR1_ADCA_BASE, ADC_REFERENCE_INTERNAL, ADC_REFERENCE_3_3V);
	//
	// Configures the analog-to-digital converter module prescaler.
	//
	ADC_setPrescaler(MTR1_ADCA_BASE, ADC_CLK_DIV_2_0);
	//
	// Sets the timing of the end-of-conversion pulse
	//
	ADC_setInterruptPulseMode(MTR1_ADCA_BASE, ADC_PULSE_END_OF_ACQ_WIN);
	//
	// Sets the timing of early interrupt generation.
	//
	ADC_setInterruptCycleOffset(MTR1_ADCA_BASE, 0U);
	//
	// Powers up the analog-to-digital converter core.
	//
	ADC_enableConverter(MTR1_ADCA_BASE);
	//
	// Delay for 1ms to allow ADC time to power up
	//
	DEVICE_DELAY_US(5000);
	//
	// Enable alternate timings for DMA trigger
	//
	ADC_enableAltDMATiming(MTR1_ADCA_BASE);
	//
	// SOC Configuration: Setup ADC EPWM channel and trigger settings
	//
	// Disables SOC burst mode.
	//
	ADC_disableBurstMode(MTR1_ADCA_BASE);
	//
	// Sets the priority mode of the SOCs.
	//
	ADC_setSOCPriority(MTR1_ADCA_BASE, ADC_PRI_ALL_HIPRI);
	//
	// Start of Conversion 0 Configuration
	//
	//
	// Disables Sample Capacitor to reset after each conversion.
	//
	ADC_disableSampleCAPReset(MTR1_ADCA_BASE, ADC_SOC_NUMBER0);
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 0
	//	  	Trigger			: ADC_TRIGGER_EPWM1_SOCA
	//	  	Channel			: ADC_CH_ADCIN2
	//	 	Sample Window	: 18 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(MTR1_ADCA_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN2, 18U);
	ADC_setInterruptSOCTrigger(MTR1_ADCA_BASE, ADC_SOC_NUMBER0, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 1 Configuration
	//
	//
	// Disables Sample Capacitor to reset after each conversion.
	//
	ADC_disableSampleCAPReset(MTR1_ADCA_BASE, ADC_SOC_NUMBER1);
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 1
	//	  	Trigger			: ADC_TRIGGER_EPWM1_SOCA
	//	  	Channel			: ADC_CH_ADCIN6
	//	 	Sample Window	: 26 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(MTR1_ADCA_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN6, 26U);
	ADC_setInterruptSOCTrigger(MTR1_ADCA_BASE, ADC_SOC_NUMBER1, ADC_INT_SOC_TRIGGER_NONE);
			
	//
	// PPB Configuration: Configure high and low limits detection for ADCPPB
	//
	// Post Processing Block 1 Configuration
	// 		Configures a post-processing block (PPB) in the ADC.
	// 		PPB Number				: 1
	// 		SOC/EOC number			: 0
	// 		Calibration Offset		: 0
	// 		Reference Offset		: 0
	// 		Two's Complement		: Disabled
	// 		Trip High Limit			: 0
	// 		Trip Low Limit			: 0
	// 		Clear PPB Event Flags	: Disabled
	// 		Accumulation Limit		: 0
	// 		SyncInput Source		: ADC_SYNCIN_DISABLE
	// 		Comparator Source		: ADC_PPB_COMPSOURCE_RESULT
	// 		Right Shift				: 0
	// 		Absolute value				: false
	//
	ADC_setupPPB(MTR1_ADCA_BASE, ADC_PPB_NUMBER1, ADC_SOC_NUMBER0);
	ADC_disablePPBEvent(MTR1_ADCA_BASE, ADC_PPB_NUMBER1, (ADC_EVT_TRIPHI | ADC_EVT_TRIPLO | ADC_EVT_ZERO));
	ADC_disablePPBEventInterrupt(MTR1_ADCA_BASE, ADC_PPB_NUMBER1, (ADC_EVT_TRIPHI | ADC_EVT_TRIPLO | ADC_EVT_ZERO));
	ADC_setPPBCalibrationOffset(MTR1_ADCA_BASE, ADC_PPB_NUMBER1, 0);
	ADC_setPPBReferenceOffset(MTR1_ADCA_BASE, ADC_PPB_NUMBER1, 0);
	ADC_disablePPBTwosComplement(MTR1_ADCA_BASE, ADC_PPB_NUMBER1);
	ADC_setPPBTripLimits(MTR1_ADCA_BASE, ADC_PPB_NUMBER1, 0, 0);
	ADC_disablePPBEventCBCClear(MTR1_ADCA_BASE, ADC_PPB_NUMBER1);
	ADC_setPPBCountLimit(MTR1_ADCA_BASE, ADC_PPB_NUMBER1,0);
	ADC_selectPPBSyncInput(MTR1_ADCA_BASE, ADC_PPB_NUMBER1,ADC_SYNCIN_DISABLE);
	ADC_selectPPBCompareSource(MTR1_ADCA_BASE, ADC_PPB_NUMBER1,ADC_PPB_COMPSOURCE_RESULT);
	ADC_setPPBShiftValue(MTR1_ADCA_BASE, ADC_PPB_NUMBER1,0);
	ADC_disablePPBAbsoluteValue(MTR1_ADCA_BASE, ADC_PPB_NUMBER1);
}

void MTR1_VDC_init(){
	//
	// ADC Initialization: Write ADC configurations and power up the ADC
	//
	// Set the analog voltage reference selection and ADC module's offset trims.
	// This function sets the analog voltage reference to internal (with the reference voltage of 1.65V or 2.5V) or external for ADC
	// which is same as ASysCtl APIs.
	//
	ADC_setVREF(MTR1_VDC_BASE, ADC_REFERENCE_INTERNAL, ADC_REFERENCE_3_3V);
	//
	// Configures the analog-to-digital converter module prescaler.
	//
	ADC_setPrescaler(MTR1_VDC_BASE, ADC_CLK_DIV_2_0);
	//
	// Sets the timing of the end-of-conversion pulse
	//
	ADC_setInterruptPulseMode(MTR1_VDC_BASE, ADC_PULSE_END_OF_CONV);
	//
	// Powers up the analog-to-digital converter core.
	//
	ADC_enableConverter(MTR1_VDC_BASE);
	//
	// Delay for 1ms to allow ADC time to power up
	//
	DEVICE_DELAY_US(5000);
	//
	// Enable alternate timings for DMA trigger
	//
	ADC_enableAltDMATiming(MTR1_VDC_BASE);
	//
	// SOC Configuration: Setup ADC EPWM channel and trigger settings
	//
	// Disables SOC burst mode.
	//
	ADC_disableBurstMode(MTR1_VDC_BASE);
	//
	// Sets the priority mode of the SOCs.
	//
	ADC_setSOCPriority(MTR1_VDC_BASE, ADC_PRI_ALL_HIPRI);
	//
	// Start of Conversion 0 Configuration
	//
	//
	// Disables Sample Capacitor to reset after each conversion.
	//
	ADC_disableSampleCAPReset(MTR1_VDC_BASE, ADC_SOC_NUMBER0);
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 0
	//	  	Trigger			: ADC_TRIGGER_EPWM1_SOCA
	//	  	Channel			: ADC_CH_ADCIN3
	//	 	Sample Window	: 18 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(MTR1_VDC_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN3, 18U);
	ADC_setInterruptSOCTrigger(MTR1_VDC_BASE, ADC_SOC_NUMBER0, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 1 Configuration
	//
	//
	// Disables Sample Capacitor to reset after each conversion.
	//
	ADC_disableSampleCAPReset(MTR1_VDC_BASE, ADC_SOC_NUMBER1);
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 1
	//	  	Trigger			: ADC_TRIGGER_EPWM1_SOCA
	//	  	Channel			: ADC_CH_ADCIN2
	//	 	Sample Window	: 26 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(MTR1_VDC_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN2, 26U);
	ADC_setInterruptSOCTrigger(MTR1_VDC_BASE, ADC_SOC_NUMBER1, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 2 Configuration
	//
	//
	// Disables Sample Capacitor to reset after each conversion.
	//
	ADC_disableSampleCAPReset(MTR1_VDC_BASE, ADC_SOC_NUMBER2);
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 2
	//	  	Trigger			: ADC_TRIGGER_EPWM1_SOCA
	//	  	Channel			: ADC_CH_ADCIN11
	//	 	Sample Window	: 26 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(MTR1_VDC_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN11, 26U);
	ADC_setInterruptSOCTrigger(MTR1_VDC_BASE, ADC_SOC_NUMBER2, ADC_INT_SOC_TRIGGER_NONE);
	//
	// ADC Interrupt 1 Configuration
	// 		Source	: ADC_INT_TRIGGER_EOC2
	// 		Interrupt Source: enabled
	// 		Continuous Mode	: disabled
	//
	//
	ADC_setInterruptSource(MTR1_VDC_BASE, ADC_INT_NUMBER1, ADC_INT_TRIGGER_EOC2);
	ADC_clearInterruptStatus(MTR1_VDC_BASE, ADC_INT_NUMBER1);
	ADC_disableContinuousMode(MTR1_VDC_BASE, ADC_INT_NUMBER1);
	ADC_enableInterrupt(MTR1_VDC_BASE, ADC_INT_NUMBER1);
			
	//
	// PPB Configuration: Configure high and low limits detection for ADCPPB
	//
	// Post Processing Block 1 Configuration
	// 		Configures a post-processing block (PPB) in the ADC.
	// 		PPB Number				: 1
	// 		SOC/EOC number			: 0
	// 		Calibration Offset		: 0
	// 		Reference Offset		: 0
	// 		Two's Complement		: Disabled
	// 		Trip High Limit			: 0
	// 		Trip Low Limit			: 0
	// 		Clear PPB Event Flags	: Disabled
	// 		Accumulation Limit		: 0
	// 		SyncInput Source		: ADC_SYNCIN_DISABLE
	// 		Comparator Source		: ADC_PPB_COMPSOURCE_RESULT
	// 		Right Shift				: 0
	// 		Absolute value				: false
	//
	ADC_setupPPB(MTR1_VDC_BASE, ADC_PPB_NUMBER1, ADC_SOC_NUMBER0);
	ADC_disablePPBEvent(MTR1_VDC_BASE, ADC_PPB_NUMBER1, (ADC_EVT_TRIPHI | ADC_EVT_TRIPLO | ADC_EVT_ZERO));
	ADC_disablePPBEventInterrupt(MTR1_VDC_BASE, ADC_PPB_NUMBER1, (ADC_EVT_TRIPHI | ADC_EVT_TRIPLO | ADC_EVT_ZERO));
	ADC_setPPBCalibrationOffset(MTR1_VDC_BASE, ADC_PPB_NUMBER1, 0);
	ADC_setPPBReferenceOffset(MTR1_VDC_BASE, ADC_PPB_NUMBER1, 0);
	ADC_disablePPBTwosComplement(MTR1_VDC_BASE, ADC_PPB_NUMBER1);
	ADC_setPPBTripLimits(MTR1_VDC_BASE, ADC_PPB_NUMBER1, 0, 0);
	ADC_disablePPBEventCBCClear(MTR1_VDC_BASE, ADC_PPB_NUMBER1);
	ADC_setPPBCountLimit(MTR1_VDC_BASE, ADC_PPB_NUMBER1,0);
	ADC_selectPPBSyncInput(MTR1_VDC_BASE, ADC_PPB_NUMBER1,ADC_SYNCIN_DISABLE);
	ADC_selectPPBCompareSource(MTR1_VDC_BASE, ADC_PPB_NUMBER1,ADC_PPB_COMPSOURCE_RESULT);
	ADC_setPPBShiftValue(MTR1_VDC_BASE, ADC_PPB_NUMBER1,0);
	ADC_disablePPBAbsoluteValue(MTR1_VDC_BASE, ADC_PPB_NUMBER1);
}

void MTR1_ADCC_init(){
	//
	// ADC Initialization: Write ADC configurations and power up the ADC
	//
	// Set the analog voltage reference selection and ADC module's offset trims.
	// This function sets the analog voltage reference to internal (with the reference voltage of 1.65V or 2.5V) or external for ADC
	// which is same as ASysCtl APIs.
	//
	ADC_setVREF(MTR1_ADCC_BASE, ADC_REFERENCE_INTERNAL, ADC_REFERENCE_3_3V);
	//
	// Configures the analog-to-digital converter module prescaler.
	//
	ADC_setPrescaler(MTR1_ADCC_BASE, ADC_CLK_DIV_2_0);
	//
	// Sets the timing of the end-of-conversion pulse
	//
	ADC_setInterruptPulseMode(MTR1_ADCC_BASE, ADC_PULSE_END_OF_ACQ_WIN);
	//
	// Sets the timing of early interrupt generation.
	//
	ADC_setInterruptCycleOffset(MTR1_ADCC_BASE, 0U);
	//
	// Powers up the analog-to-digital converter core.
	//
	ADC_enableConverter(MTR1_ADCC_BASE);
	//
	// Delay for 1ms to allow ADC time to power up
	//
	DEVICE_DELAY_US(5000);
	//
	// Enable alternate timings for DMA trigger
	//
	ADC_enableAltDMATiming(MTR1_ADCC_BASE);
	//
	// SOC Configuration: Setup ADC EPWM channel and trigger settings
	//
	// Disables SOC burst mode.
	//
	ADC_disableBurstMode(MTR1_ADCC_BASE);
	//
	// Sets the priority mode of the SOCs.
	//
	ADC_setSOCPriority(MTR1_ADCC_BASE, ADC_PRI_ALL_HIPRI);
	//
	// Start of Conversion 0 Configuration
	//
	//
	// Disables Sample Capacitor to reset after each conversion.
	//
	ADC_disableSampleCAPReset(MTR1_ADCC_BASE, ADC_SOC_NUMBER0);
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 0
	//	  	Trigger			: ADC_TRIGGER_EPWM1_SOCA
	//	  	Channel			: ADC_CH_ADCIN4
	//	 	Sample Window	: 18 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(MTR1_ADCC_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN4, 18U);
	ADC_setInterruptSOCTrigger(MTR1_ADCC_BASE, ADC_SOC_NUMBER0, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 1 Configuration
	//
	//
	// Disables Sample Capacitor to reset after each conversion.
	//
	ADC_disableSampleCAPReset(MTR1_ADCC_BASE, ADC_SOC_NUMBER1);
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 1
	//	  	Trigger			: ADC_TRIGGER_EPWM1_SOCA
	//	  	Channel			: ADC_CH_ADCIN0
	//	 	Sample Window	: 26 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(MTR1_ADCC_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN0, 26U);
	ADC_setInterruptSOCTrigger(MTR1_ADCC_BASE, ADC_SOC_NUMBER1, ADC_INT_SOC_TRIGGER_NONE);
			
	//
	// PPB Configuration: Configure high and low limits detection for ADCPPB
	//
	// Post Processing Block 1 Configuration
	// 		Configures a post-processing block (PPB) in the ADC.
	// 		PPB Number				: 1
	// 		SOC/EOC number			: 0
	// 		Calibration Offset		: 0
	// 		Reference Offset		: 0
	// 		Two's Complement		: Disabled
	// 		Trip High Limit			: 0
	// 		Trip Low Limit			: 0
	// 		Clear PPB Event Flags	: Disabled
	// 		Accumulation Limit		: 0
	// 		SyncInput Source		: ADC_SYNCIN_DISABLE
	// 		Comparator Source		: ADC_PPB_COMPSOURCE_RESULT
	// 		Right Shift				: 0
	// 		Absolute value				: false
	//
	ADC_setupPPB(MTR1_ADCC_BASE, ADC_PPB_NUMBER1, ADC_SOC_NUMBER0);
	ADC_disablePPBEvent(MTR1_ADCC_BASE, ADC_PPB_NUMBER1, (ADC_EVT_TRIPHI | ADC_EVT_TRIPLO | ADC_EVT_ZERO));
	ADC_disablePPBEventInterrupt(MTR1_ADCC_BASE, ADC_PPB_NUMBER1, (ADC_EVT_TRIPHI | ADC_EVT_TRIPLO | ADC_EVT_ZERO));
	ADC_setPPBCalibrationOffset(MTR1_ADCC_BASE, ADC_PPB_NUMBER1, 0);
	ADC_setPPBReferenceOffset(MTR1_ADCC_BASE, ADC_PPB_NUMBER1, 0);
	ADC_disablePPBTwosComplement(MTR1_ADCC_BASE, ADC_PPB_NUMBER1);
	ADC_setPPBTripLimits(MTR1_ADCC_BASE, ADC_PPB_NUMBER1, 0, 0);
	ADC_disablePPBEventCBCClear(MTR1_ADCC_BASE, ADC_PPB_NUMBER1);
	ADC_setPPBCountLimit(MTR1_ADCC_BASE, ADC_PPB_NUMBER1,0);
	ADC_selectPPBSyncInput(MTR1_ADCC_BASE, ADC_PPB_NUMBER1,ADC_SYNCIN_DISABLE);
	ADC_selectPPBCompareSource(MTR1_ADCC_BASE, ADC_PPB_NUMBER1,ADC_PPB_COMPSOURCE_RESULT);
	ADC_setPPBShiftValue(MTR1_ADCC_BASE, ADC_PPB_NUMBER1,0);
	ADC_disablePPBAbsoluteValue(MTR1_ADCC_BASE, ADC_PPB_NUMBER1);
}


//*****************************************************************************
//
// ASYSCTL Configurations
//
//*****************************************************************************
void ASYSCTL_init(){
	//
	// asysctl initialization
	//
	// Enables the temperature sensor output to the ADC.
	//
	ASysCtl_enableTemperatureSensor();
	DEVICE_DELAY_US(500);
	//
	// Set the analog voltage reference selection to internal.
	//
	ASysCtl_setAnalogReferenceInternal( ASYSCTL_ANAREF_INTREF_ADCA | ASYSCTL_ANAREF_INTREF_ADCB | ASYSCTL_ANAREF_INTREF_ADCC | ASYSCTL_ANAREF_INTREF_ADCD | ASYSCTL_ANAREF_INTREF_ADCE );

	//
	// Set the internal analog voltage reference selection to 1.65V.
	//
	ASysCtl_setAnalogReference1P65( ASYSCTL_ANAREF_ADCA | ASYSCTL_ANAREF_ADCB | ASYSCTL_ANAREF_ADCC | ASYSCTL_ANAREF_ADCD | ASYSCTL_ANAREF_ADCE );
}

//*****************************************************************************
//
// CMPSS Configurations
//
//*****************************************************************************
void CMPSS_init(){
	cmpss_CMPSS3_init();
	cmpss_CMPSS1_init();
}

void cmpss_CMPSS3_init(){
    //
    // Select the value for CMP3HPMXSEL.
    //
    ASysCtl_selectCMPHPMux(ASYSCTL_CMPHPMUX_SELECT_3,3U);
    //
    // Select the value for CMP3LPMXSEL.
    //
    ASysCtl_selectCMPLPMux(ASYSCTL_CMPLPMUX_SELECT_3,4U);
    //
    // Sets the configuration for the high comparator.
    //
    CMPSS_configHighComparator(cmpss_CMPSS3_BASE,(CMPSS_INSRC_DAC));
    //
    // Sets the configuration for the low comparator.
    //
    CMPSS_configLowComparator(cmpss_CMPSS3_BASE,(CMPSS_INSRC_DAC | CMPSS_INV_INVERTED));
    //
    // Sets the configuration for the internal comparator DACs.
    //
    CMPSS_configDACHigh(cmpss_CMPSS3_BASE,(CMPSS_DACVAL_SYSCLK | CMPSS_DACSRC_SHDW));
    CMPSS_configDACLow(cmpss_CMPSS3_BASE, CMPSS_DACSRC_SHDW);
    //
    // Sets the value of the internal DAC of the high comparator.
    //
    CMPSS_setDACValueHigh(cmpss_CMPSS3_BASE,3000U);
    //
    // Sets the value of the internal DAC of the low comparator.
    //
    CMPSS_setDACValueLow(cmpss_CMPSS3_BASE,250U);
    //
    //  Configures the digital filter of the high comparator.
    //
    CMPSS_configFilterHigh(cmpss_CMPSS3_BASE, 32U, 32U, 30U);
    //
    // Configures the digital filter of the low comparator.
    //
    CMPSS_configFilterLow(cmpss_CMPSS3_BASE, 32U, 32U, 30U);
    //
    // Initializes the digital filter of the high comparator.
    //
    CMPSS_initFilterHigh(cmpss_CMPSS3_BASE);
    //
    // Initializes the digital filter of the low comparator.
    //
    CMPSS_initFilterLow(cmpss_CMPSS3_BASE);
    //
    // Sets the output signal configuration for the high comparator.
    //
    CMPSS_configOutputsHigh(cmpss_CMPSS3_BASE,(CMPSS_TRIPOUT_FILTER | CMPSS_TRIP_FILTER));
    //
    // Sets the output signal configuration for the low comparator.
    //
    CMPSS_configOutputsLow(cmpss_CMPSS3_BASE,(CMPSS_TRIPOUT_FILTER | CMPSS_TRIP_FILTER));
    //
    // Sets the comparator hysteresis settings.
    //
    CMPSS_setHysteresis(cmpss_CMPSS3_BASE,0U);
    //
    // Configures the comparator subsystem's high ramp generator.
    //
    CMPSS_configRampHigh(cmpss_CMPSS3_BASE, CMPSS_RAMP_DIR_DOWN, 0U,0U,0U,1U,true);
    //
    // Configures the comparator subsystem's low ramp generator.
    //
    CMPSS_configRampLow(cmpss_CMPSS3_BASE, CMPSS_RAMP_DIR_DOWN, 0U,0U,0U,1U,true);
    //
    // Configures the high comparator's ramp generator clock divider
    //
    CMPSS_setRampClockDividerHigh(cmpss_CMPSS3_BASE, CMPSS_RAMP_CLOCK_DIV1);
    //
    // Configures the low comparator's ramp generator clock divider
    //
    CMPSS_setRampClockDividerLow(cmpss_CMPSS3_BASE, CMPSS_RAMP_CLOCK_DIV1);
    //
    // Disables reset of HIGH comparator digital filter output latch on PWMSYNC
    //
    CMPSS_disableLatchResetOnPWMSYNCHigh(cmpss_CMPSS3_BASE);
    //
    // Disables reset of LOW comparator digital filter output latch on PWMSYNC
    //
    CMPSS_disableLatchResetOnPWMSYNCLow(cmpss_CMPSS3_BASE);
    //
    // Sets the ePWM module blanking signal that holds trip in reset.
    //
    CMPSS_configBlanking(cmpss_CMPSS3_BASE,1U);
    //
    // Disables an ePWM blanking signal from holding trip in reset.
    //
    CMPSS_disableBlanking(cmpss_CMPSS3_BASE);
    //
    // Configures whether or not the digital filter latches are reset by PWMSYNC
    //
    CMPSS_configLatchOnPWMSYNC(cmpss_CMPSS3_BASE,false,false);
    //
    // Enables the CMPSS module.
    //
    CMPSS_enableModule(cmpss_CMPSS3_BASE);
    //
    // Delay for CMPSS DAC to power up.
    //
    DEVICE_DELAY_US(500);
    //
    // Causes a software reset of the high comparator digital filter output latch.
    //
    CMPSS_clearFilterLatchHigh(cmpss_CMPSS3_BASE);
    //
    // Causes a software reset of the low comparator digital filter output latch.
    //
    CMPSS_clearFilterLatchLow(cmpss_CMPSS3_BASE);
}
void cmpss_CMPSS1_init(){
    //
    // Select the value for CMP1HPMXSEL.
    //
    ASysCtl_selectCMPHPMux(ASYSCTL_CMPHPMUX_SELECT_1,0U);
    //
    // Select the value for CMP1LPMXSEL.
    //
    ASysCtl_selectCMPLPMux(ASYSCTL_CMPLPMUX_SELECT_1,0U);
    //
    // Sets the configuration for the high comparator.
    //
    CMPSS_configHighComparator(cmpss_CMPSS1_BASE,(CMPSS_INSRC_DAC));
    //
    // Sets the configuration for the low comparator.
    //
    CMPSS_configLowComparator(cmpss_CMPSS1_BASE,(CMPSS_INSRC_DAC | CMPSS_INV_INVERTED));
    //
    // Sets the configuration for the internal comparator DACs.
    //
    CMPSS_configDACHigh(cmpss_CMPSS1_BASE,(CMPSS_DACVAL_SYSCLK | CMPSS_DACSRC_SHDW));
    CMPSS_configDACLow(cmpss_CMPSS1_BASE, CMPSS_DACSRC_SHDW);
    //
    // Sets the value of the internal DAC of the high comparator.
    //
    CMPSS_setDACValueHigh(cmpss_CMPSS1_BASE,3000U);
    //
    // Sets the value of the internal DAC of the low comparator.
    //
    CMPSS_setDACValueLow(cmpss_CMPSS1_BASE,0U);
    //
    //  Configures the digital filter of the high comparator.
    //
    CMPSS_configFilterHigh(cmpss_CMPSS1_BASE, 32U, 32U, 30U);
    //
    // Configures the digital filter of the low comparator.
    //
    CMPSS_configFilterLow(cmpss_CMPSS1_BASE, 32U, 32U, 30U);
    //
    // Initializes the digital filter of the high comparator.
    //
    CMPSS_initFilterHigh(cmpss_CMPSS1_BASE);
    //
    // Initializes the digital filter of the low comparator.
    //
    CMPSS_initFilterLow(cmpss_CMPSS1_BASE);
    //
    // Sets the output signal configuration for the high comparator.
    //
    CMPSS_configOutputsHigh(cmpss_CMPSS1_BASE,(CMPSS_TRIPOUT_FILTER | CMPSS_TRIP_FILTER));
    //
    // Sets the output signal configuration for the low comparator.
    //
    CMPSS_configOutputsLow(cmpss_CMPSS1_BASE,(CMPSS_TRIPOUT_FILTER | CMPSS_TRIP_FILTER));
    //
    // Sets the comparator hysteresis settings.
    //
    CMPSS_setHysteresis(cmpss_CMPSS1_BASE,0U);
    //
    // Configures the comparator subsystem's high ramp generator.
    //
    CMPSS_configRampHigh(cmpss_CMPSS1_BASE, CMPSS_RAMP_DIR_DOWN, 0U,0U,0U,1U,true);
    //
    // Configures the comparator subsystem's low ramp generator.
    //
    CMPSS_configRampLow(cmpss_CMPSS1_BASE, CMPSS_RAMP_DIR_DOWN, 0U,0U,0U,1U,true);
    //
    // Configures the high comparator's ramp generator clock divider
    //
    CMPSS_setRampClockDividerHigh(cmpss_CMPSS1_BASE, CMPSS_RAMP_CLOCK_DIV1);
    //
    // Configures the low comparator's ramp generator clock divider
    //
    CMPSS_setRampClockDividerLow(cmpss_CMPSS1_BASE, CMPSS_RAMP_CLOCK_DIV1);
    //
    // Disables reset of HIGH comparator digital filter output latch on PWMSYNC
    //
    CMPSS_disableLatchResetOnPWMSYNCHigh(cmpss_CMPSS1_BASE);
    //
    // Disables reset of LOW comparator digital filter output latch on PWMSYNC
    //
    CMPSS_disableLatchResetOnPWMSYNCLow(cmpss_CMPSS1_BASE);
    //
    // Sets the ePWM module blanking signal that holds trip in reset.
    //
    CMPSS_configBlanking(cmpss_CMPSS1_BASE,1U);
    //
    // Disables an ePWM blanking signal from holding trip in reset.
    //
    CMPSS_disableBlanking(cmpss_CMPSS1_BASE);
    //
    // Configures whether or not the digital filter latches are reset by PWMSYNC
    //
    CMPSS_configLatchOnPWMSYNC(cmpss_CMPSS1_BASE,false,false);
    //
    // Enables the CMPSS module.
    //
    CMPSS_enableModule(cmpss_CMPSS1_BASE);
    //
    // Delay for CMPSS DAC to power up.
    //
    DEVICE_DELAY_US(500);
    //
    // Causes a software reset of the high comparator digital filter output latch.
    //
    CMPSS_clearFilterLatchHigh(cmpss_CMPSS1_BASE);
    //
    // Causes a software reset of the low comparator digital filter output latch.
    //
    CMPSS_clearFilterLatchLow(cmpss_CMPSS1_BASE);
}

//*****************************************************************************
//
// CPUTIMER Configurations
//
//*****************************************************************************
void CPUTIMER_init(){
	BACKGROUND_TIMER_init();
	CPU_USAGE_TIMER_init();
	SYS_RTOS_TIMER_init();
}

void BACKGROUND_TIMER_init(){
	CPUTimer_setEmulationMode(BACKGROUND_TIMER_BASE, CPUTIMER_EMULATIONMODE_RUNFREE);
	CPUTimer_setPreScaler(BACKGROUND_TIMER_BASE, 0U);
	CPUTimer_setPeriod(BACKGROUND_TIMER_BASE, 100000U);
	CPUTimer_enableInterrupt(BACKGROUND_TIMER_BASE);
	CPUTimer_stopTimer(BACKGROUND_TIMER_BASE);

	CPUTimer_reloadTimerCounter(BACKGROUND_TIMER_BASE);
	CPUTimer_startTimer(BACKGROUND_TIMER_BASE);
}
void CPU_USAGE_TIMER_init(){
	CPUTimer_setEmulationMode(CPU_USAGE_TIMER_BASE, CPUTIMER_EMULATIONMODE_RUNFREE);
	CPUTimer_setPreScaler(CPU_USAGE_TIMER_BASE, 0U);
	CPUTimer_setPeriod(CPU_USAGE_TIMER_BASE, 4294967295U);
	CPUTimer_enableInterrupt(CPU_USAGE_TIMER_BASE);
	CPUTimer_stopTimer(CPU_USAGE_TIMER_BASE);

	CPUTimer_reloadTimerCounter(CPU_USAGE_TIMER_BASE);
	CPUTimer_startTimer(CPU_USAGE_TIMER_BASE);
}
void SYS_RTOS_TIMER_init(){
	CPUTimer_setEmulationMode(SYS_RTOS_TIMER_BASE, CPUTIMER_EMULATIONMODE_RUNFREE);
	CPUTimer_selectClockSource(SYS_RTOS_TIMER_BASE, CPUTIMER_CLOCK_SOURCE_SYS, CPUTIMER_CLOCK_PRESCALER_1);
	CPUTimer_setPreScaler(SYS_RTOS_TIMER_BASE, 0U);
	CPUTimer_setPeriod(SYS_RTOS_TIMER_BASE, 1U);
	CPUTimer_disableInterrupt(SYS_RTOS_TIMER_BASE);
	CPUTimer_stopTimer(SYS_RTOS_TIMER_BASE);

	CPUTimer_reloadTimerCounter(SYS_RTOS_TIMER_BASE);
}

//*****************************************************************************
//
// EPWM Configurations
//
//*****************************************************************************
void EPWM_init(){
    EPWM_setEmulationMode(MTR1_EPWM_U_BASE, EPWM_EMULATION_FREE_RUN);	
    EPWM_setClockPrescaler(MTR1_EPWM_U_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);	
    EPWM_setTimeBasePeriod(MTR1_EPWM_U_BASE, 65535);	
    EPWM_setTimeBaseCounter(MTR1_EPWM_U_BASE, 0);	
    EPWM_setTimeBaseCounterMode(MTR1_EPWM_U_BASE, EPWM_COUNTER_MODE_UP_DOWN);	
    EPWM_setCountModeAfterSync(MTR1_EPWM_U_BASE, EPWM_COUNT_MODE_UP_AFTER_SYNC);	
    EPWM_disablePhaseShiftLoad(MTR1_EPWM_U_BASE);	
    EPWM_setPhaseShift(MTR1_EPWM_U_BASE, 0);	
    EPWM_setCounterCompareValue(MTR1_EPWM_U_BASE, EPWM_COUNTER_COMPARE_A, 5);	
    EPWM_setCounterCompareShadowLoadMode(MTR1_EPWM_U_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_setCounterCompareValue(MTR1_EPWM_U_BASE, EPWM_COUNTER_COMPARE_B, 5);	
    EPWM_setCounterCompareShadowLoadMode(MTR1_EPWM_U_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_setCounterCompareValue(MTR1_EPWM_U_BASE, EPWM_COUNTER_COMPARE_C, 5);	
    EPWM_setCounterCompareValue(MTR1_EPWM_U_BASE, EPWM_COUNTER_COMPARE_D, 5);	
    EPWM_setActionQualifierShadowLoadMode(MTR1_EPWM_U_BASE, EPWM_ACTION_QUALIFIER_A, EPWM_AQ_LOAD_ON_CNTR_ZERO);	
    EPWM_setActionQualifierAction(MTR1_EPWM_U_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(MTR1_EPWM_U_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(MTR1_EPWM_U_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(MTR1_EPWM_U_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(MTR1_EPWM_U_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(MTR1_EPWM_U_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_setActionQualifierShadowLoadMode(MTR1_EPWM_U_BASE, EPWM_ACTION_QUALIFIER_B, EPWM_AQ_LOAD_ON_CNTR_ZERO);	
    EPWM_setActionQualifierAction(MTR1_EPWM_U_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(MTR1_EPWM_U_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(MTR1_EPWM_U_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(MTR1_EPWM_U_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(MTR1_EPWM_U_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(MTR1_EPWM_U_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_setDeadBandDelayPolarity(MTR1_EPWM_U_BASE, EPWM_DB_FED, EPWM_DB_POLARITY_ACTIVE_LOW);	
    EPWM_setDeadBandDelayMode(MTR1_EPWM_U_BASE, EPWM_DB_RED, true);	
    EPWM_setRisingEdgeDelayCountShadowLoadMode(MTR1_EPWM_U_BASE, EPWM_RED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableRisingEdgeDelayCountShadowLoadMode(MTR1_EPWM_U_BASE);	
    EPWM_setRisingEdgeDelayCount(MTR1_EPWM_U_BASE, 10);	
    EPWM_setDeadBandDelayMode(MTR1_EPWM_U_BASE, EPWM_DB_FED, true);	
    EPWM_setFallingEdgeDelayCountShadowLoadMode(MTR1_EPWM_U_BASE, EPWM_FED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableFallingEdgeDelayCountShadowLoadMode(MTR1_EPWM_U_BASE);	
    EPWM_setFallingEdgeDelayCount(MTR1_EPWM_U_BASE, 10);	
    EPWM_enableTripZoneSignals(MTR1_EPWM_U_BASE, EPWM_TZ_SIGNAL_DCAEVT1 | EPWM_TZ_SIGNAL_DCBEVT1 | EPWM_TZ_SIGNAL_OSHT1);	
    EPWM_selectDigitalCompareTripInput(MTR1_EPWM_U_BASE, EPWM_DC_TRIP_COMBINATION, EPWM_DC_TYPE_DCAH);	
    EPWM_enableDigitalCompareTripCombinationInput(MTR1_EPWM_U_BASE, EPWM_DC_COMBINATIONAL_TRIPIN7, EPWM_DC_TYPE_DCAH);	
    EPWM_selectDigitalCompareTripInput(MTR1_EPWM_U_BASE, EPWM_DC_TRIP_COMBINATION, EPWM_DC_TYPE_DCAL);	
    EPWM_enableDigitalCompareTripCombinationInput(MTR1_EPWM_U_BASE, EPWM_DC_COMBINATIONAL_TRIPIN7, EPWM_DC_TYPE_DCAL);	
    EPWM_setTripZoneDigitalCompareEventCondition(MTR1_EPWM_U_BASE, EPWM_TZ_DC_OUTPUT_A1, EPWM_TZ_EVENT_DCXH_HIGH);	
    EPWM_setTripZoneDigitalCompareEventCondition(MTR1_EPWM_U_BASE, EPWM_TZ_DC_OUTPUT_A2, EPWM_TZ_EVENT_DCXH_HIGH);	
    EPWM_setDigitalCompareEventSource(MTR1_EPWM_U_BASE, EPWM_DC_MODULE_A, EPWM_DC_EVENT_1, EPWM_DC_EVENT_SOURCE_FILT_SIGNAL);	
    EPWM_setDigitalCompareEventSource(MTR1_EPWM_U_BASE, EPWM_DC_MODULE_A, EPWM_DC_EVENT_2, EPWM_DC_EVENT_SOURCE_FILT_SIGNAL);	
    EPWM_selectDigitalCompareTripInput(MTR1_EPWM_U_BASE, EPWM_DC_TRIP_COMBINATION, EPWM_DC_TYPE_DCBH);	
    EPWM_enableDigitalCompareTripCombinationInput(MTR1_EPWM_U_BASE, EPWM_DC_COMBINATIONAL_TRIPIN7, EPWM_DC_TYPE_DCBH);	
    EPWM_selectDigitalCompareTripInput(MTR1_EPWM_U_BASE, EPWM_DC_TRIP_COMBINATION, EPWM_DC_TYPE_DCBL);	
    EPWM_enableDigitalCompareTripCombinationInput(MTR1_EPWM_U_BASE, EPWM_DC_COMBINATIONAL_TRIPIN7, EPWM_DC_TYPE_DCBL);	
    EPWM_setTripZoneDigitalCompareEventCondition(MTR1_EPWM_U_BASE, EPWM_TZ_DC_OUTPUT_B1, EPWM_TZ_EVENT_DCXH_HIGH);	
    EPWM_setTripZoneDigitalCompareEventCondition(MTR1_EPWM_U_BASE, EPWM_TZ_DC_OUTPUT_B2, EPWM_TZ_EVENT_DCXH_HIGH);	
    EPWM_setDigitalCompareEventSource(MTR1_EPWM_U_BASE, EPWM_DC_MODULE_B, EPWM_DC_EVENT_1, EPWM_DC_EVENT_SOURCE_FILT_SIGNAL);	
    EPWM_setDigitalCompareEventSource(MTR1_EPWM_U_BASE, EPWM_DC_MODULE_B, EPWM_DC_EVENT_2, EPWM_DC_EVENT_SOURCE_FILT_SIGNAL);	
    EPWM_enableInterrupt(MTR1_EPWM_U_BASE);	
    EPWM_setInterruptSource(MTR1_EPWM_U_BASE, EPWM_INT_TBCTR_ZERO);	
    EPWM_setInterruptEventCount(MTR1_EPWM_U_BASE, 1);	
    EPWM_enableADCTrigger(MTR1_EPWM_U_BASE, EPWM_SOC_A);	
    EPWM_setADCTriggerSource(MTR1_EPWM_U_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_D_CMPC);	
    EPWM_setADCTriggerEventPrescale(MTR1_EPWM_U_BASE, EPWM_SOC_A, 1);	
    EPWM_enableADCTrigger(MTR1_EPWM_U_BASE, EPWM_SOC_B);	
    EPWM_setADCTriggerSource(MTR1_EPWM_U_BASE, EPWM_SOC_B, EPWM_SOC_TBCTR_D_CMPD);	
    EPWM_setADCTriggerEventPrescale(MTR1_EPWM_U_BASE, EPWM_SOC_B, 1);	
    EPWM_setEmulationMode(MTR1_EPWM_V_BASE, EPWM_EMULATION_FREE_RUN);	
    EPWM_setClockPrescaler(MTR1_EPWM_V_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);	
    EPWM_setTimeBasePeriod(MTR1_EPWM_V_BASE, 65535);	
    EPWM_setTimeBaseCounter(MTR1_EPWM_V_BASE, 0);	
    EPWM_setTimeBaseCounterMode(MTR1_EPWM_V_BASE, EPWM_COUNTER_MODE_UP_DOWN);	
    EPWM_setCountModeAfterSync(MTR1_EPWM_V_BASE, EPWM_COUNT_MODE_UP_AFTER_SYNC);	
    EPWM_disablePhaseShiftLoad(MTR1_EPWM_V_BASE);	
    EPWM_setPhaseShift(MTR1_EPWM_V_BASE, 0);	
    EPWM_setCounterCompareValue(MTR1_EPWM_V_BASE, EPWM_COUNTER_COMPARE_A, 5);	
    EPWM_setCounterCompareShadowLoadMode(MTR1_EPWM_V_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_setCounterCompareValue(MTR1_EPWM_V_BASE, EPWM_COUNTER_COMPARE_B, 5);	
    EPWM_setCounterCompareShadowLoadMode(MTR1_EPWM_V_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_setCounterCompareValue(MTR1_EPWM_V_BASE, EPWM_COUNTER_COMPARE_C, 5);	
    EPWM_setCounterCompareValue(MTR1_EPWM_V_BASE, EPWM_COUNTER_COMPARE_D, 5);	
    EPWM_setActionQualifierShadowLoadMode(MTR1_EPWM_V_BASE, EPWM_ACTION_QUALIFIER_A, EPWM_AQ_LOAD_ON_CNTR_ZERO);	
    EPWM_setActionQualifierAction(MTR1_EPWM_V_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(MTR1_EPWM_V_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(MTR1_EPWM_V_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(MTR1_EPWM_V_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(MTR1_EPWM_V_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(MTR1_EPWM_V_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_setActionQualifierShadowLoadMode(MTR1_EPWM_V_BASE, EPWM_ACTION_QUALIFIER_B, EPWM_AQ_LOAD_ON_CNTR_ZERO);	
    EPWM_setActionQualifierAction(MTR1_EPWM_V_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(MTR1_EPWM_V_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(MTR1_EPWM_V_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(MTR1_EPWM_V_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(MTR1_EPWM_V_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(MTR1_EPWM_V_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_setDeadBandDelayPolarity(MTR1_EPWM_V_BASE, EPWM_DB_FED, EPWM_DB_POLARITY_ACTIVE_LOW);	
    EPWM_setDeadBandDelayMode(MTR1_EPWM_V_BASE, EPWM_DB_RED, true);	
    EPWM_setRisingEdgeDelayCountShadowLoadMode(MTR1_EPWM_V_BASE, EPWM_RED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableRisingEdgeDelayCountShadowLoadMode(MTR1_EPWM_V_BASE);	
    EPWM_setRisingEdgeDelayCount(MTR1_EPWM_V_BASE, 10);	
    EPWM_setDeadBandDelayMode(MTR1_EPWM_V_BASE, EPWM_DB_FED, true);	
    EPWM_setFallingEdgeDelayCountShadowLoadMode(MTR1_EPWM_V_BASE, EPWM_FED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableFallingEdgeDelayCountShadowLoadMode(MTR1_EPWM_V_BASE);	
    EPWM_setFallingEdgeDelayCount(MTR1_EPWM_V_BASE, 10);	
    EPWM_enableTripZoneSignals(MTR1_EPWM_V_BASE, EPWM_TZ_SIGNAL_DCAEVT1 | EPWM_TZ_SIGNAL_DCBEVT1 | EPWM_TZ_SIGNAL_OSHT1);	
    EPWM_selectDigitalCompareTripInput(MTR1_EPWM_V_BASE, EPWM_DC_TRIP_COMBINATION, EPWM_DC_TYPE_DCAH);	
    EPWM_enableDigitalCompareTripCombinationInput(MTR1_EPWM_V_BASE, EPWM_DC_COMBINATIONAL_TRIPIN7, EPWM_DC_TYPE_DCAH);	
    EPWM_selectDigitalCompareTripInput(MTR1_EPWM_V_BASE, EPWM_DC_TRIP_COMBINATION, EPWM_DC_TYPE_DCAL);	
    EPWM_enableDigitalCompareTripCombinationInput(MTR1_EPWM_V_BASE, EPWM_DC_COMBINATIONAL_TRIPIN7, EPWM_DC_TYPE_DCAL);	
    EPWM_setTripZoneDigitalCompareEventCondition(MTR1_EPWM_V_BASE, EPWM_TZ_DC_OUTPUT_A1, EPWM_TZ_EVENT_DCXH_HIGH);	
    EPWM_setTripZoneDigitalCompareEventCondition(MTR1_EPWM_V_BASE, EPWM_TZ_DC_OUTPUT_A2, EPWM_TZ_EVENT_DCXH_HIGH);	
    EPWM_setDigitalCompareEventSource(MTR1_EPWM_V_BASE, EPWM_DC_MODULE_A, EPWM_DC_EVENT_1, EPWM_DC_EVENT_SOURCE_FILT_SIGNAL);	
    EPWM_setDigitalCompareEventSource(MTR1_EPWM_V_BASE, EPWM_DC_MODULE_A, EPWM_DC_EVENT_2, EPWM_DC_EVENT_SOURCE_FILT_SIGNAL);	
    EPWM_selectDigitalCompareTripInput(MTR1_EPWM_V_BASE, EPWM_DC_TRIP_COMBINATION, EPWM_DC_TYPE_DCBH);	
    EPWM_enableDigitalCompareTripCombinationInput(MTR1_EPWM_V_BASE, EPWM_DC_COMBINATIONAL_TRIPIN7, EPWM_DC_TYPE_DCBH);	
    EPWM_selectDigitalCompareTripInput(MTR1_EPWM_V_BASE, EPWM_DC_TRIP_COMBINATION, EPWM_DC_TYPE_DCBL);	
    EPWM_enableDigitalCompareTripCombinationInput(MTR1_EPWM_V_BASE, EPWM_DC_COMBINATIONAL_TRIPIN7, EPWM_DC_TYPE_DCBL);	
    EPWM_setTripZoneDigitalCompareEventCondition(MTR1_EPWM_V_BASE, EPWM_TZ_DC_OUTPUT_B1, EPWM_TZ_EVENT_DCXH_HIGH);	
    EPWM_setTripZoneDigitalCompareEventCondition(MTR1_EPWM_V_BASE, EPWM_TZ_DC_OUTPUT_B2, EPWM_TZ_EVENT_DCXH_HIGH);	
    EPWM_setDigitalCompareEventSource(MTR1_EPWM_V_BASE, EPWM_DC_MODULE_B, EPWM_DC_EVENT_1, EPWM_DC_EVENT_SOURCE_FILT_SIGNAL);	
    EPWM_setDigitalCompareEventSource(MTR1_EPWM_V_BASE, EPWM_DC_MODULE_B, EPWM_DC_EVENT_2, EPWM_DC_EVENT_SOURCE_FILT_SIGNAL);	
    EPWM_enableInterrupt(MTR1_EPWM_V_BASE);	
    EPWM_setInterruptSource(MTR1_EPWM_V_BASE, EPWM_INT_TBCTR_ZERO);	
    EPWM_setInterruptEventCount(MTR1_EPWM_V_BASE, 1);	
    EPWM_enableADCTrigger(MTR1_EPWM_V_BASE, EPWM_SOC_A);	
    EPWM_setADCTriggerSource(MTR1_EPWM_V_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_D_CMPC);	
    EPWM_setADCTriggerEventPrescale(MTR1_EPWM_V_BASE, EPWM_SOC_A, 1);	
    EPWM_enableADCTrigger(MTR1_EPWM_V_BASE, EPWM_SOC_B);	
    EPWM_setADCTriggerSource(MTR1_EPWM_V_BASE, EPWM_SOC_B, EPWM_SOC_TBCTR_D_CMPD);	
    EPWM_setADCTriggerEventPrescale(MTR1_EPWM_V_BASE, EPWM_SOC_B, 1);	
    EPWM_setEmulationMode(MTR1_EPWM_W_BASE, EPWM_EMULATION_FREE_RUN);	
    EPWM_setClockPrescaler(MTR1_EPWM_W_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);	
    EPWM_setTimeBasePeriod(MTR1_EPWM_W_BASE, 65535);	
    EPWM_setTimeBaseCounter(MTR1_EPWM_W_BASE, 0);	
    EPWM_setTimeBaseCounterMode(MTR1_EPWM_W_BASE, EPWM_COUNTER_MODE_UP_DOWN);	
    EPWM_setCountModeAfterSync(MTR1_EPWM_W_BASE, EPWM_COUNT_MODE_UP_AFTER_SYNC);	
    EPWM_disablePhaseShiftLoad(MTR1_EPWM_W_BASE);	
    EPWM_setPhaseShift(MTR1_EPWM_W_BASE, 0);	
    EPWM_setCounterCompareValue(MTR1_EPWM_W_BASE, EPWM_COUNTER_COMPARE_A, 5);	
    EPWM_setCounterCompareShadowLoadMode(MTR1_EPWM_W_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_setCounterCompareValue(MTR1_EPWM_W_BASE, EPWM_COUNTER_COMPARE_B, 5);	
    EPWM_setCounterCompareShadowLoadMode(MTR1_EPWM_W_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_setCounterCompareValue(MTR1_EPWM_W_BASE, EPWM_COUNTER_COMPARE_C, 5);	
    EPWM_setCounterCompareValue(MTR1_EPWM_W_BASE, EPWM_COUNTER_COMPARE_D, 5);	
    EPWM_setActionQualifierShadowLoadMode(MTR1_EPWM_W_BASE, EPWM_ACTION_QUALIFIER_A, EPWM_AQ_LOAD_ON_CNTR_ZERO);	
    EPWM_setActionQualifierAction(MTR1_EPWM_W_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(MTR1_EPWM_W_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(MTR1_EPWM_W_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(MTR1_EPWM_W_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(MTR1_EPWM_W_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(MTR1_EPWM_W_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_setActionQualifierShadowLoadMode(MTR1_EPWM_W_BASE, EPWM_ACTION_QUALIFIER_B, EPWM_AQ_LOAD_ON_CNTR_ZERO);	
    EPWM_setActionQualifierAction(MTR1_EPWM_W_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(MTR1_EPWM_W_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(MTR1_EPWM_W_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(MTR1_EPWM_W_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(MTR1_EPWM_W_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(MTR1_EPWM_W_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_setDeadBandDelayPolarity(MTR1_EPWM_W_BASE, EPWM_DB_FED, EPWM_DB_POLARITY_ACTIVE_LOW);	
    EPWM_setDeadBandDelayMode(MTR1_EPWM_W_BASE, EPWM_DB_RED, true);	
    EPWM_setRisingEdgeDelayCountShadowLoadMode(MTR1_EPWM_W_BASE, EPWM_RED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableRisingEdgeDelayCountShadowLoadMode(MTR1_EPWM_W_BASE);	
    EPWM_setRisingEdgeDelayCount(MTR1_EPWM_W_BASE, 10);	
    EPWM_setDeadBandDelayMode(MTR1_EPWM_W_BASE, EPWM_DB_FED, true);	
    EPWM_setFallingEdgeDelayCountShadowLoadMode(MTR1_EPWM_W_BASE, EPWM_FED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableFallingEdgeDelayCountShadowLoadMode(MTR1_EPWM_W_BASE);	
    EPWM_setFallingEdgeDelayCount(MTR1_EPWM_W_BASE, 10);	
    EPWM_enableTripZoneSignals(MTR1_EPWM_W_BASE, EPWM_TZ_SIGNAL_DCAEVT1 | EPWM_TZ_SIGNAL_DCBEVT1 | EPWM_TZ_SIGNAL_OSHT1);	
    EPWM_selectDigitalCompareTripInput(MTR1_EPWM_W_BASE, EPWM_DC_TRIP_COMBINATION, EPWM_DC_TYPE_DCAH);	
    EPWM_enableDigitalCompareTripCombinationInput(MTR1_EPWM_W_BASE, EPWM_DC_COMBINATIONAL_TRIPIN7, EPWM_DC_TYPE_DCAH);	
    EPWM_selectDigitalCompareTripInput(MTR1_EPWM_W_BASE, EPWM_DC_TRIP_COMBINATION, EPWM_DC_TYPE_DCAL);	
    EPWM_enableDigitalCompareTripCombinationInput(MTR1_EPWM_W_BASE, EPWM_DC_COMBINATIONAL_TRIPIN7, EPWM_DC_TYPE_DCAL);	
    EPWM_setTripZoneDigitalCompareEventCondition(MTR1_EPWM_W_BASE, EPWM_TZ_DC_OUTPUT_A1, EPWM_TZ_EVENT_DCXH_HIGH);	
    EPWM_setTripZoneDigitalCompareEventCondition(MTR1_EPWM_W_BASE, EPWM_TZ_DC_OUTPUT_A2, EPWM_TZ_EVENT_DCXH_HIGH);	
    EPWM_setDigitalCompareEventSource(MTR1_EPWM_W_BASE, EPWM_DC_MODULE_A, EPWM_DC_EVENT_1, EPWM_DC_EVENT_SOURCE_FILT_SIGNAL);	
    EPWM_setDigitalCompareEventSource(MTR1_EPWM_W_BASE, EPWM_DC_MODULE_A, EPWM_DC_EVENT_2, EPWM_DC_EVENT_SOURCE_FILT_SIGNAL);	
    EPWM_selectDigitalCompareTripInput(MTR1_EPWM_W_BASE, EPWM_DC_TRIP_COMBINATION, EPWM_DC_TYPE_DCBH);	
    EPWM_enableDigitalCompareTripCombinationInput(MTR1_EPWM_W_BASE, EPWM_DC_COMBINATIONAL_TRIPIN7, EPWM_DC_TYPE_DCBH);	
    EPWM_selectDigitalCompareTripInput(MTR1_EPWM_W_BASE, EPWM_DC_TRIP_COMBINATION, EPWM_DC_TYPE_DCBL);	
    EPWM_enableDigitalCompareTripCombinationInput(MTR1_EPWM_W_BASE, EPWM_DC_COMBINATIONAL_TRIPIN7, EPWM_DC_TYPE_DCBL);	
    EPWM_setTripZoneDigitalCompareEventCondition(MTR1_EPWM_W_BASE, EPWM_TZ_DC_OUTPUT_B1, EPWM_TZ_EVENT_DCXH_HIGH);	
    EPWM_setTripZoneDigitalCompareEventCondition(MTR1_EPWM_W_BASE, EPWM_TZ_DC_OUTPUT_B2, EPWM_TZ_EVENT_DCXH_HIGH);	
    EPWM_setDigitalCompareEventSource(MTR1_EPWM_W_BASE, EPWM_DC_MODULE_B, EPWM_DC_EVENT_1, EPWM_DC_EVENT_SOURCE_FILT_SIGNAL);	
    EPWM_setDigitalCompareEventSource(MTR1_EPWM_W_BASE, EPWM_DC_MODULE_B, EPWM_DC_EVENT_2, EPWM_DC_EVENT_SOURCE_FILT_SIGNAL);	
    EPWM_enableInterrupt(MTR1_EPWM_W_BASE);	
    EPWM_setInterruptSource(MTR1_EPWM_W_BASE, EPWM_INT_TBCTR_ZERO);	
    EPWM_setInterruptEventCount(MTR1_EPWM_W_BASE, 1);	
    EPWM_enableADCTrigger(MTR1_EPWM_W_BASE, EPWM_SOC_A);	
    EPWM_setADCTriggerSource(MTR1_EPWM_W_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_D_CMPC);	
    EPWM_setADCTriggerEventPrescale(MTR1_EPWM_W_BASE, EPWM_SOC_A, 1);	
    EPWM_enableADCTrigger(MTR1_EPWM_W_BASE, EPWM_SOC_B);	
    EPWM_setADCTriggerSource(MTR1_EPWM_W_BASE, EPWM_SOC_B, EPWM_SOC_TBCTR_D_CMPD);	
    EPWM_setADCTriggerEventPrescale(MTR1_EPWM_W_BASE, EPWM_SOC_B, 1);	
}

//*****************************************************************************
//
// EPWMXBAR Configurations
//
//*****************************************************************************
void EPWMXBAR_init(){
	MTR1_IS_TRIP_CMPSS_init();
}

void MTR1_IS_TRIP_CMPSS_init(){
		
	XBAR_setEPWMMuxConfig(MTR1_IS_TRIP_CMPSS, XBAR_EPWM_MUX00_CMPSS1_CTRIPH);
	XBAR_setEPWMMuxConfig(MTR1_IS_TRIP_CMPSS, XBAR_EPWM_MUX04_CMPSS3_CTRIPH_OR_L);
	XBAR_enableEPWMMux(MTR1_IS_TRIP_CMPSS, XBAR_MUX00 | XBAR_MUX04);
}

//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************
void GPIO_init(){
	MTR1_GATE_EN_GPIO_init();
	MTR1_GATE_MODE_GPIO_init();
	MTR1_GATE_GAIN_GPIO_init();
	MTR1_GATE_CAL_GPIO_init();
	MTR1_PM_nFAULT_GPIO_init();
}

void MTR1_GATE_EN_GPIO_init(){
	GPIO_writePin(MTR1_GATE_EN_GPIO, 1);
	GPIO_setPadConfig(MTR1_GATE_EN_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(MTR1_GATE_EN_GPIO, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(MTR1_GATE_EN_GPIO, GPIO_DIR_MODE_OUT);
	GPIO_setControllerCore(MTR1_GATE_EN_GPIO, GPIO_CORE_CPU1);
}
void MTR1_GATE_MODE_GPIO_init(){
	GPIO_writePin(MTR1_GATE_MODE_GPIO, 0);
	GPIO_setPadConfig(MTR1_GATE_MODE_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(MTR1_GATE_MODE_GPIO, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(MTR1_GATE_MODE_GPIO, GPIO_DIR_MODE_OUT);
	GPIO_setControllerCore(MTR1_GATE_MODE_GPIO, GPIO_CORE_CPU1);
}
void MTR1_GATE_GAIN_GPIO_init(){
	GPIO_setPadConfig(MTR1_GATE_GAIN_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(MTR1_GATE_GAIN_GPIO, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(MTR1_GATE_GAIN_GPIO, GPIO_DIR_MODE_IN);
	GPIO_setControllerCore(MTR1_GATE_GAIN_GPIO, GPIO_CORE_CPU1);
}
void MTR1_GATE_CAL_GPIO_init(){
	GPIO_setPadConfig(MTR1_GATE_CAL_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(MTR1_GATE_CAL_GPIO, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(MTR1_GATE_CAL_GPIO, GPIO_DIR_MODE_IN);
	GPIO_setControllerCore(MTR1_GATE_CAL_GPIO, GPIO_CORE_CPU1);
}
void MTR1_PM_nFAULT_GPIO_init(){
	GPIO_setPadConfig(MTR1_PM_nFAULT_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(MTR1_PM_nFAULT_GPIO, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(MTR1_PM_nFAULT_GPIO, GPIO_DIR_MODE_IN);
	GPIO_setControllerCore(MTR1_PM_nFAULT_GPIO, GPIO_CORE_CPU1);
}

//*****************************************************************************
//
// INPUTXBAR Configurations
//
//*****************************************************************************
void INPUTXBAR_init(){
	motor1_XBAR_INPUT1_init();
}

void motor1_XBAR_INPUT1_init(){
	XBAR_setInputPin(INPUTXBAR_BASE, motor1_XBAR_INPUT1_INPUT, motor1_XBAR_INPUT1_SOURCE);
}

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************
void INTERRUPT_init(){
	
	// Interrupt Settings for INT_MotorControlWorkbench_transferLayer_SCI_RX
	// ISR need to be defined for the registered interrupts
	// Interrupt_register(INT_MotorControlWorkbench_transferLayer_SCI_RX, &INT_MotorControlWorkbench_transferLayer_SCI_RX_ISR);
	// Interrupt_enable(INT_MotorControlWorkbench_transferLayer_SCI_RX);
	
	// Interrupt Settings for INT_MotorControlWorkbench_transferLayer_SCI_TX
	// ISR need to be defined for the registered interrupts
	// Interrupt_register(INT_MotorControlWorkbench_transferLayer_SCI_TX, &INT_MotorControlWorkbench_transferLayer_SCI_TX_ISR);
	// Interrupt_disable(INT_MotorControlWorkbench_transferLayer_SCI_TX);
	
	// Interrupt Settings for INT_MTR1_VDC_1
	// ISR need to be defined for the registered interrupts
	Interrupt_register(INT_MTR1_VDC_1, &INT_MTR1_VDC_1_ISR);
	Interrupt_disable(INT_MTR1_VDC_1);
}
//*****************************************************************************
//
// SCI Configurations
//
//*****************************************************************************
void SCI_init(){
	MotorControlWorkbench_transferLayer_SCI_init();
}

void MotorControlWorkbench_transferLayer_SCI_init(){
	SCI_clearInterruptStatus(MotorControlWorkbench_transferLayer_SCI_BASE, SCI_INT_RXFF | SCI_INT_TXFF | SCI_INT_FE | SCI_INT_OE | SCI_INT_PE | SCI_INT_RXERR | SCI_INT_RXRDY_BRKDT | SCI_INT_TXRDY);
	SCI_clearOverflowStatus(MotorControlWorkbench_transferLayer_SCI_BASE);
	SCI_resetTxFIFO(MotorControlWorkbench_transferLayer_SCI_BASE);
	SCI_resetRxFIFO(MotorControlWorkbench_transferLayer_SCI_BASE);
	SCI_resetChannels(MotorControlWorkbench_transferLayer_SCI_BASE);
	SCI_setConfig(MotorControlWorkbench_transferLayer_SCI_BASE, DEVICE_LSPCLK_FREQ, MotorControlWorkbench_transferLayer_SCI_BAUDRATE, (SCI_CONFIG_WLEN_8|SCI_CONFIG_STOP_ONE|SCI_CONFIG_PAR_NONE));
	SCI_disableLoopback(MotorControlWorkbench_transferLayer_SCI_BASE);
	SCI_performSoftwareReset(MotorControlWorkbench_transferLayer_SCI_BASE);
	SCI_enableInterrupt(MotorControlWorkbench_transferLayer_SCI_BASE, SCI_INT_RXFF);
	SCI_setFIFOInterruptLevel(MotorControlWorkbench_transferLayer_SCI_BASE, SCI_FIFO_TX0, SCI_FIFO_RX16);
	SCI_enableFIFO(MotorControlWorkbench_transferLayer_SCI_BASE);
	SCI_enableModule(MotorControlWorkbench_transferLayer_SCI_BASE);
}

//*****************************************************************************
//
// SYNC Scheme Configurations
//
//*****************************************************************************
void SYNC_init(){
	SysCtl_setSyncOutputConfig(SYSCTL_SYNC_OUT_SRC_EPWM1SYNCOUT);
	//
	// SOCA
	//
	SysCtl_enableExtADCSOCSource(0);
	//
	// SOCB
	//
	SysCtl_enableExtADCSOCSource(0);
}
//*****************************************************************************
//
// SYSCTL Configurations
//
//*****************************************************************************
void SYSCTL_init(){
	//
    // sysctl initialization
	//
    SysCtl_setStandbyQualificationPeriod(2);
    SysCtl_configureType(SYSCTL_USBTYPE, 0, 0);
    SysCtl_configureType(SYSCTL_ECAPTYPE, 0, 0);
    SysCtl_selectErrPinPolarity(0);

    SysCtl_disableMCD();


    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_ADCA, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_ADCA, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_ADCA, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_ADCB, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_ADCB, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_ADCB, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_ADCC, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_ADCC, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_ADCC, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_ADCD, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_ADCD, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_ADCD, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_ADCE, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_ADCE, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_ADCE, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CMPSS1, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CMPSS1, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CMPSS1, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CMPSS2, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CMPSS2, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CMPSS2, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CMPSS3, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CMPSS3, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CMPSS3, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CMPSS4, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CMPSS4, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CMPSS4, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_DACA, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_DACA, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_DACA, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_PGA1, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_PGA1, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_PGA1, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_PGA2, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_PGA2, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_PGA2, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_PGA3, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_PGA3, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_PGA3, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EPWM1, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EPWM1, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EPWM1, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EPWM2, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EPWM2, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EPWM2, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EPWM3, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EPWM3, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EPWM3, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EPWM4, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EPWM4, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EPWM4, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EPWM5, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EPWM5, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EPWM5, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EPWM6, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EPWM6, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EPWM6, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EPWM7, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EPWM7, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EPWM7, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EPWM8, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EPWM8, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EPWM8, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EPWM9, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EPWM9, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EPWM9, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EPWM10, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EPWM10, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EPWM10, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EPWM11, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EPWM11, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EPWM11, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EPWM12, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EPWM12, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EPWM12, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EQEP1, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EQEP1, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EQEP1, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EQEP2, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EQEP2, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EQEP2, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EQEP3, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EQEP3, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_EQEP3, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_ECAP1, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_ECAP1, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_ECAP1, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_ECAP2, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_ECAP2, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_ECAP2, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CLB1, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CLB1, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CLB1, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CLB2, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CLB2, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CLB2, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_SCIA, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_SCIA, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_SCIA, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_SCIB, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_SCIB, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_SCIB, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_SCIC, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_SCIC, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_SCIC, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_SPIA, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_SPIA, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_SPIA, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_SPIB, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_SPIB, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_SPIB, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_I2CA, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_I2CA, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_I2CA, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_I2CB, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_I2CB, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_I2CB, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_PMBUSA, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_PMBUSA, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_PMBUSA, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_LINA, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_LINA, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_LINA, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_MCANA, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_MCANA, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_MCANA, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_MCANB, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_MCANB, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_MCANB, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_FSIATX, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_FSIATX, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_FSIATX, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_FSIARX, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_FSIARX, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_FSIARX, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_USBA, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_USBA, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_USBA, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_HRPWMA, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_HRPWMA, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_HRPWMA, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_AESA, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_AESA, 
        SYSCTL_ACCESS_CLA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_AESA, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CLA1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DMA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TIMER0);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TIMER1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TIMER2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_HRCAL);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ERAD);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM3);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM4);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM5);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM6);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM7);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM8);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM9);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM10);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM11);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM12);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EQEP1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EQEP2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EQEP3);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SCIA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SCIB);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SCIC);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SPIA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SPIB);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_I2CA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_I2CB);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_MCANA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_MCANB);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_USBA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_NPU);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCB);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCC);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCD);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCE);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CMPSS1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CMPSS2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CMPSS3);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CMPSS4);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PGA1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PGA2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PGA3);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DACA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CLB1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CLB2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_FSITXA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_FSIRXA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_LINA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PMBUSA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DCC0);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DCC1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_AESA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPG1);



}

