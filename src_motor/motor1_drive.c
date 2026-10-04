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
//! \file   /solutions/universal_motorcontrol_lab/common/source/motor1_drive.c
//!
//! \brief  This project is used to implement motor control with FAST, eSMO
//!         Encoder, and Hall sensors based sensored/sensorless-FOC.
//!         Supports multiple TI EVM boards
//!
//
//
// include the related header files
//
#include "sys_settings.h"
#include "sys_main.h"
#include "motor1_drive.h"

#pragma CODE_SECTION(motor1CtrlISR, "ctrlfuncs");
#pragma INTERRUPT(motor1CtrlISR, {HPI});

// the globals

//!< the hardware abstraction layer object to motor control
volatile MOTOR_Handle motorHandle_M1;
#pragma DATA_SECTION(motorHandle_M1, "ptr_data");

HAL_MTR_Obj    halMtr_M1;
#pragma DATA_SECTION(halMtr_M1, "hal_data");

volatile MOTOR_Vars_t motorVars_M1;
#pragma DATA_SECTION(motorVars_M1, "ctrl_data");

MOTOR_CtrlVars_t motorCtrlVars_M1;
#pragma DATA_SECTION(motorCtrlVars_M1, "ctrl_data");

MOTOR_SetVars_t motorSetVars_M1;
#pragma DATA_SECTION(motorSetVars_M1, "ctrl_data");  

//!< the voltage Clarke transform object
CLARKE_Obj    clarke_V_M1;
#pragma DATA_SECTION(clarke_V_M1, "foc_data");

//!< the current Clarke transform object
CLARKE_Obj    clarke_I_M1;
#pragma DATA_SECTION(clarke_I_M1, "foc_data");

//!< the inverse Park transform object
IPARK_Obj     ipark_V_M1;
#pragma DATA_SECTION(ipark_V_M1, "foc_data");

//!< the Park transform object
PARK_Obj      park_I_M1;
#pragma DATA_SECTION(park_I_M1, "foc_data");

//!< the Park transform object
PARK_Obj      park_V_M1;
#pragma DATA_SECTION(park_V_M1, "foc_data");

//!< the current reference trajectory object
TRAJ_Obj     traj_Is_M1;
#pragma DATA_SECTION(traj_Is_M1, "foc_data");

//!< the Id PI controller object
PI_Obj        pi_Id_M1;
#pragma DATA_SECTION(pi_Id_M1, "foc_data");

//!< the Iq PI controller object
PI_Obj        pi_Iq_M1;
#pragma DATA_SECTION(pi_Iq_M1, "foc_data");

//!< the speed PI controller object
PI_Obj        pi_spd_M1;
#pragma DATA_SECTION(pi_spd_M1, "foc_data");

//!< the space vector generator object
SVGEN_Obj     svgen_M1;
#pragma DATA_SECTION(svgen_M1, "foc_data");

//!< the speed reference trajectory object
TRAJ_Obj     traj_spd_M1;
#pragma DATA_SECTION(traj_spd_M1, "foc_data");
#if (DMC_BUILDLEVEL <= DMC_LEVEL_3)
//!< the Angle Generate onject for open loop control
ANGLE_GEN_Obj    angleGen_M1;
#pragma DATA_SECTION(angleGen_M1, "foc_data");
#endif // (DMC_BUILDLEVEL <= DMC_LEVEL_3)

#if (DMC_BUILDLEVEL == DMC_LEVEL_2)
//!< the Vs per Freq object for open loop control
VS_FREQ_Obj    VsFreq_M1;
#pragma DATA_SECTION(VsFreq_M1, "foc_data");
#endif // (DMC_BUILDLEVEL == DMC_LEVEL_2)






// the control handles for motor 1
void initMotor1Handles(MOTOR_Handle handle)
{
    MOTOR_Vars_t *obj = (MOTOR_Vars_t *)handle;
    
    // initialize the driver
    obj->halMtrHandle = HAL_MTR1_init(&halMtr_M1, sizeof(halMtr_M1));
    halHandle->mtrHandle = (motorHandle_M1->halMtrHandle);
    
    obj->motorCtrlHandle = &motorCtrlVars_M1;
    obj->motorSetsHandle = &motorSetVars_M1;
    obj->userParamsHandle = &userParams_M1;






#if (DMC_BUILDLEVEL <= DMC_LEVEL_3)
    // initialize the angle generate module
    obj->angleGenHandle = ANGLE_GEN_init(&angleGen_M1, sizeof(angleGen_M1));
#endif // (DMC_BUILDLEVEL <= DMC_LEVEL_3)

#if (DMC_BUILDLEVEL == DMC_LEVEL_2)
    // initialize the Vs per Freq module
    obj->VsFreqHandle = VS_FREQ_init(&VsFreq_M1, sizeof(VsFreq_M1));
#endif // (DMC_BUILDLEVEL == DMC_LEVEL_2)





    // initialize the Clarke modules
    obj->clarkeHandle_V = CLARKE_init(&clarke_V_M1, sizeof(clarke_V_M1));

    // initialize the Clarke modules
    obj->clarkeHandle_I = CLARKE_init(&clarke_I_M1, sizeof(clarke_I_M1));

    // initialize the inverse Park module
    obj->iparkHandle_V = IPARK_init(&ipark_V_M1, sizeof(ipark_V_M1));

    // initialize the Park module
    obj->parkHandle_I = PARK_init(&park_I_M1, sizeof(park_I_M1));

    // initialize the Park module
    obj->parkHandle_V = PARK_init(&park_V_M1, sizeof(park_V_M1));

    // initialize the PI controllers
    obj->piHandle_spd = PI_init(&pi_spd_M1, sizeof(pi_spd_M1));
    obj->piHandle_Id  = PI_init(&pi_Id_M1, sizeof(pi_Id_M1));
    obj->piHandle_Iq  = PI_init(&pi_Iq_M1, sizeof(pi_Iq_M1));

    // initialize the speed reference trajectory
    obj->trajHandle_spd = TRAJ_init(&traj_spd_M1, sizeof(traj_spd_M1));

    // initialize the current reference trajectory
    obj->trajHandle_Is = TRAJ_init(&traj_Is_M1, sizeof(traj_Is_M1));

    // initialize the space vector generator module
    obj->svgenHandle = SVGEN_init(&svgen_M1, sizeof(svgen_M1));





    // initialize the estimator
    obj->estHandle = EST_initEst(MTR_1);

    return;
}

// initialize control parameters for motor 1
void initMotor1CtrlParameters(MOTOR_Handle handle)
{
    MOTOR_Vars_t *obj = (MOTOR_Vars_t *)handle;
    MOTOR_SetVars_t *objSets = (MOTOR_SetVars_t *)(handle->motorSetsHandle);

    USER_Params *objUser = (USER_Params *)(handle->userParamsHandle);

    // initialize the user parameters
    USER_setParams_priv(obj->userParamsHandle);

    objSets->estFreq_Hz = USER_M1_ISR_FREQ_Hz;
    objSets->motorModel = M1_Teknic_M2310PL;

    objSets->voltageFilter_Hz = USER_M1_VOLTAGE_FILTER_POLE_Hz;

    objSets->ctrlPeriod_sec = USER_M1_CTRL_PERIOD_sec;
    objSets->ctrlFreq_Hz = USER_M1_ISR_FREQ_Hz;

    objSets->overCurrentTimesSet = USER_M1_OVER_CURRENT_TIMES_SET;
    objSets->overLoadTimeSet = USER_M1_OVER_LOAD_TIME_SET;
    objSets->motorStallTimeSet = USER_M1_STALL_TIME_SET;
    objSets->voltageFaultTimeSet = USER_M1_VOLTAGE_FAULT_TIME_SET;
    objSets->startupFailTimeSet = USER_M1_STARTUP_FAIL_TIME_SET;

    obj->operateMode = OPERATE_MODE_SPEED;

    objSets->flyingStartTimeDelay = (uint16_t)(objSets->ctrlFreq_Hz * 0.001f);  // 1ms
    // objSets->alignTimeDelay = (uint16_t)(objSets->ctrlFreq_Hz * USER_M1_ALIGN_TIME_S);
    objSets->alignTimeDelay = (uint16_t)(objSets->ctrlFreq_Hz * 2.0f);
    objSets->forceRunTimeDelay = (uint16_t)(objSets->ctrlFreq_Hz * 1.0f);       // 1.0s
    objSets->startupTimeDelay = (uint16_t)(objSets->ctrlFreq_Hz * 2.0f);        // 2.0s

    objSets->motor_type = USER_MOTOR1_TYPE;
    objSets->numPolePairs = USER_MOTOR1_NUM_POLE_PAIRS;
    objSets->Rs_Ohm = USER_MOTOR1_Rs_Ohm;
    objSets->Ls_d_H = USER_MOTOR1_Ls_d_H;
    objSets->Ls_q_H = USER_MOTOR1_Ls_q_H;
    objSets->flux_VpHz = USER_MOTOR1_RATED_FLUX_VpHz;

        
    objSets->voltageScale_V = USER_M1_ADC_FULL_SCALE_VOLTAGE_V;
    objSets->currentScale_A = USER_M1_ADC_FULL_SCALE_CURRENT_A;
    objSets->pwmControl_kHz = USER_M1_PWM_FREQ_kHz;
    objSets->controlTicksPWM = USER_M1_NUM_PWM_TICKS_PER_ISR_TICK;
    objSets->speedTicksControl = USER_M1_NUM_ISR_TICKS_PER_SPEED_TICK;

    objSets->maxFrequency_Hz = USER_MOTOR1_FREQ_MAX_Hz;
    objSets->maxCurrentSet_A = USER_MOTOR1_MAX_CURRENT_A;
    objSets->maxVoltage_V = USER_M1_NOMINAL_DC_BUS_VOLTAGE_V;
    objSets->maxPeakCurrent_A = USER_M1_ADC_FULL_SCALE_CURRENT_A * 0.4975f;
    objSets->maxVsMag_pu = USER_M1_MAX_VS_MAG_PU;

    objSets->maxCurrentResEst_A = USER_MOTOR1_RES_EST_CURRENT_A;
    objSets->maxCurrentIndEst_A = USER_MOTOR1_IND_EST_CURRENT_A;
    objSets->fluxExcFreq_Hz = USER_MOTOR1_FLUX_EXC_FREQ_Hz;

    objSets->Ls_d_Icomp_coef = USER_MOTOR1_Ls_d_COMP_COEF / USER_MOTOR1_MAX_CURRENT_A;
    objSets->Ls_q_Icomp_coef = USER_MOTOR1_Ls_q_COMP_COEF / USER_MOTOR1_MAX_CURRENT_A;
    objSets->Ls_min_H = USER_MOTOR1_Ls_d_H * USER_MOTOR1_Ls_MIN_NUM_COEF;

    objSets->RsOnLineCurrent_A = 0.1f * USER_MOTOR1_MAX_CURRENT_A;
    objSets->RsOnLine_Rdelta_Ohm = 0.00002f;
    objSets->RsOnLine_Adelta_rad = 0.0005f;

    objSets->fluxFilterCoef = USER_M1_EST_FLUX_HF_SF;
    objSets->speedFilterCoef = USER_M1_EST_FREQ_HF_SF;
    objSets->bemfFilterCoef = USER_M1_EST_BEMF_HF_SF;
    objSets->speedPole_rps = USER_M1_SPEED_POLE_rps;
    objSets->directionPole_rps = USER_M1_DIRECTION_POLE_rps;
    objSets->fluxPole_rps = USER_M1_FLUX_POLE_rps;
    objSets->angleESTDelayed_sf = 0.5f;     // 0.5f
    objSets->anglePLLDelayed_sf = 0.2f;     // 0.2f

    objSets->currentInv_sf = USER_M1_CURRENT_INV_SF;
    objSets->overCurrent_A = USER_MOTOR1_OVER_CURRENT_A;
    objSets->overLoadSet_W = USER_M1_OVER_LOAD_POWER_W;

    objSets->lostPhaseSet_A = USER_M1_LOST_PHASE_CURRENT_A;
    objSets->unbalanceRatioSet = USER_M1_UNBALANCE_RATIO;
    objSets->stallCurrentSet_A = USER_M1_STALL_CURRENT_A;
    objSets->speedFailMaxSet_Hz = USER_M1_FAIL_SPEED_MAX_HZ;
    objSets->speedFailMinSet_Hz = USER_M1_FAIL_SPEED_MIN_HZ;
    objSets->IsFailedChekSet_A = USER_M1_FAULT_CHECK_CURRENT_A;
    objSets->toqueFailMinSet_Nm = USER_M1_TORQUE_FAILED_SET;

    objSets->overVoltageFault_V = USER_M1_OVER_VOLTAGE_FAULT_V;
    objSets->overVoltageNorm_V = USER_M1_OVER_VOLTAGE_NORM_V;
    objSets->underVoltageFault_V = USER_M1_UNDER_VOLTAGE_FAULT_V;
    objSets->underVoltageNorm_V = USER_M1_UNDER_VOLTAGE_NORM_V;

    objSets->fluxCurrent_A = USER_MOTOR1_FLUX_CURRENT_A;
    objSets->alignCurrent_A = USER_MOTOR1_ALIGN_CURRENT_A;
    objSets->startCurrent_A = USER_MOTOR1_STARTUP_CURRENT_A;
    objSets->brakingCurrent_A = USER_MOTOR1_MAX_CURRENT_A;

    objSets->accelStart_Hzps = USER_MOTOR1_ACCEL_START_Hzps;
    objSets->accelStop_Hzps = USER_MOTOR1_ACCEL_STOP_Hzps;
    objSets->accelRun_Hzps = USER_MOTOR1_ACCEL_RUN_Hzps;
    objSets->speedFlyingStart_Hz = USER_MOTOR1_SPEED_FS_Hz;
    objSets->speedForce_Hz = USER_MOTOR1_SPEED_FORCE_Hz;
    objSets->speedStart_Hz = USER_MOTOR1_SPEED_START_Hz;

    objSets->VsRef_pu = USER_M1_VS_REF_MAG_PU;
    objSets->Kp_fwc = USER_M1_FWC_KP;
    objSets->Ki_fwc = USER_M1_FWC_KI;
    objSets->angleFWCMax_rad = USER_M1_FWC_MAX_ANGLE_RAD;

    objSets->overModulation = USER_M1_MAX_VS_MAG_PU;


    
    objSets->restartWaitTimeSet = USER_M1_RESTART_WAIT_TIME_SET;
    objSets->stopWaitTimeSet = USER_M1_STOP_WAIT_TIME_SET;

    objSets->overSpeedTimeSet = USER_M1_OVER_SPEED_TIME_SET;    
    objSets->unbalanceTimeSet = USER_M1_UNBALANCE_TIME_SET;
    objSets->lostPhaseTimeSet = USER_M1_LOST_PHASE_TIME_SET;
    objSets->restartTimesSet = USER_M1_START_TIMES_SET;

    objSets->faultMtrMask.all = MTR1_FAULT_MASK_SET;

    objSets->dacCMPValH = 2048U + 1024U;    // set default positive peak value
    objSets->dacCMPValL = 2048U - 1024U;    // set default negative peak value

    // initialize the user parameters
    USER_setMotor1Params(obj->userParamsHandle, obj->motorSetsHandle);

    // set the driver parameters
    HAL_MTR_setParams(obj->halMtrHandle, obj->userParamsHandle);

    objSets->Kp_spd = 0.05f;
    objSets->Ki_spd = 0.005f;

    objSets->accelerationSet_Hzps = USER_MOTOR1_ACCEL_RUN_Hzps;

    obj->accelerationSet_Hzps = USER_MOTOR1_ACCEL_RUN_Hzps;
    obj->accelerationMax_Hzps = USER_MOTOR1_ACCEL_RUN_Hzps;

    obj->operationMode = OPERATE_MODE_SPEED;
    obj->flyingStartMode = FLYINGSTART_MODE_STANDBY; // FLYINGSTART_MODE_STANDBY, FLYINGSTART_MODE_HALT
    obj->RsOnlineMode = RSONLINE_CONTINUE;

    obj->IsSet_A = USER_MOTOR1_TORQUE_CURRENT_A;
    obj->anglePhaseAdj_rad = MATH_PI * 0.001f;

    obj->stopWaitTimeCnt = 0;
    obj->flagEnableRestart = false;

    obj->faultMtrMask.all = MTR1_FAULT_MASK_SET;

    if(objUser->flag_bypassMotorId == true)
    {
        // obj->svmMode = SVM_MIN_C;
        obj->svmMode = SVM_COM_C;
        obj->flagEnableFWC = true;
    } else {
        obj->svmMode = SVM_COM_C;
        obj->flagEnableFWC = false;
    }

    obj->flagEnableForceAngle = true;

    // true - enables flying start, false - disables flying start
    obj->flagEnableFlyingStart = true;

    // true - enables SSIPD start, false - disables SSIPD
    obj->flagEnableSSIPD = false;
    
    obj->flagEnableSpeedCtrl = true;
    obj->flagEnableCurrentCtrl = true;

    obj->estState = EST_STATE_IDLE;
    obj->trajState = EST_TRAJ_STATE_IDLE;

    obj->estimatorMode = ESTIMATOR_MODE_FAST;

    obj->flagEnableAlignment = false;

    obj->speedEST_Hz = 0.0f;
    obj->angleEST_rad = 0.0f;

    obj->speedAbs_Hz = 0.0f;
    obj->speedFilter_Hz = 0.0f;
    obj->speed_int_Hz = 0.0f;
    obj->speed_Hz = 0.0f;

    obj->angleFOC_rad = 0.0f;
    obj->angleGen_rad = 0.0f;


#if (DMC_BUILDLEVEL == DMC_LEVEL_1)
    // output PWM teste
    obj->VabcTest_pu.value[0] = 0.0f;
    obj->VabcTest_pu.value[1] = 0.0f;
    obj->VabcTest_pu.value[2] = 0.0f;    
#endif // (DMC_BUILDLEVEL == DMC_LEVEL_1)


    // configure the speed reference trajectory (Hz)
    TRAJ_setTargetValue(obj->trajHandle_spd, 0.0f);
    TRAJ_setIntValue(obj->trajHandle_spd, 0.0f);

    // configure the current reference trajectory (Hz)
    TRAJ_setTargetValue(obj->trajHandle_Is, 0.0f);
    TRAJ_setIntValue(obj->trajHandle_Is, 0.0f);

    SVGEN_setMode(obj->svgenHandle, SVM_COM_C);

    // for Rs re-calculation
    obj->flagEnableRsRecalc = false;
    obj->flagEnableLsUpdate = false;

    // for Rs online calibration
    obj->flagStartRsOnLine = false;    


#if (DMC_BUILDLEVEL <= DMC_LEVEL_3)
    // initialize the angle generate module
    ANGLE_GEN_setParams(obj->angleGenHandle, objSets->ctrlPeriod_sec);
#endif // (DMC_BUILDLEVEL <= DMC_LEVEL_3)

#if (DMC_BUILDLEVEL <= DMC_LEVEL_3)
    obj->Idq_set_A.value[0] = 0.0f;
    obj->Idq_set_A.value[1] = objSets->startCurrent_A;
#endif // (DMC_BUILDLEVEL <= DMC_LEVEL_3)

#if (DMC_BUILDLEVEL == DMC_LEVEL_2)
    VS_FREQ_setVsMagPu(obj->VsFreqHandle, objSets->maxVsMag_pu);

    VS_FREQ_setMaxFreq(obj->VsFreqHandle, USER_MOTOR1_FREQ_MAX_Hz);

    VS_FREQ_setProfile(obj->VsFreqHandle,
                        USER_MOTOR1_FREQ_LOW_Hz, USER_MOTOR1_FREQ_HIGH_Hz,
                        USER_MOTOR1_VOLT_MIN_V, USER_MOTOR1_VOLT_MAX_V);    
#endif // (DMC_BUILDLEVEL == DMC_LEVEL_2)
    

    

    
    // setup the coefficient of the controllers gains
    setupControllerSF(handle);


    obj->angleOLStep_deg = USER_M1_ANGLE_OL_STEP_DEG;
    obj->iqTarget_CLStartStep_sfps = USER_M1_IQTARGET_CLSTARTSTEP_SFPS;
    obj->spdThresh_OLEnd_Hz = USER_M1_SPDTHRESH_OLEND_HZ;

    return;
}   // end of initMotor1CtrlParameters() function

// update control parameters for motor 1
void resetMotor1CtrlParameters(MOTOR_Handle handle)     // size=0x13b->0xd2
{
    MOTOR_Vars_t *obj = (MOTOR_Vars_t *)handle;
    MOTOR_SetVars_t *objSets = (MOTOR_SetVars_t *)(handle->motorSetsHandle);
    USER_Params *objUser = (USER_Params *)(handle->userParamsHandle);
    HAL_MTR_Obj *objHalMtr = (HAL_MTR_Obj *)(handle->halMtrHandle);

    // disable the PWM
    HAL_disablePWM(obj->halMtrHandle);


    objSets->pwmPeriod_usec = 1000.0f / objSets->pwmControl_kHz;
    objSets->ctrlPeriod_sec = (objSets->pwmPeriod_usec / objSets->controlTicksPWM) *
                            ( 1.0f / 1000.0f/ 1000.0f);
                            
    objSets->maxAccel_Hzps = objSets->accelRun_Hzps;
//    objSets->alignTimeDelay = (uint16_t)(objUser->ctrlFreq_Hz * USER_M1_ALIGN_TIME_S);
    objSets->alignTimeDelay = (uint16_t)(objSets->ctrlFreq_Hz * 0.1f);

    objSets->currentInv_sf = (4096.0f / objSets->currentScale_A);

    objSets->voltage_sf = objSets->voltageScale_V * ADC_ONE_OVER_FULL_RANGE;
    objSets->current_sf = objSets->currentScale_A * ADC_ONE_OVER_FULL_RANGE;
    obj->adcData.current_sf = objSets->current_sf * USER_M1_SIGN_CURRENT_SF;

    if(objHalMtr->adcData.current_sf > 0.0f)
    {
        motorVars_M1.CurrentSenDir = CS_DIR_POSTIVE;
    }
    else
    {
        motorVars_M1.CurrentSenDir = CS_DIR_NEGATIVE;
    }

    obj->adcData.voltage_sf = objSets->voltage_sf;
    obj->adcData.dcBusvoltage_sf = objSets->voltage_sf;

    obj->VIrmsIsrScale = objSets->ctrlFreq_Hz;
    obj->power_sf = MATH_TWO_PI / objSets->numPolePairs;

    objSets->maxCurrent_A = objSets->maxCurrentSet_A;

    // initialize the user parameters
    USER_setMotor1Params(obj->userParamsHandle, obj->motorSetsHandle);

    obj->maxVsMag_pu = objUser->maxVsMag_pu;

    obj->numCtrlTicksPerSpeedTick = objUser->numCtrlTicksPerSpeedTick;


    obj->VsRef_pu = objSets->VsRef_pu;
    obj->VsRef_V = obj->VsRef_pu * USER_M1_NOMINAL_DC_BUS_VOLTAGE_V;
    obj->IsSet_A = USER_MOTOR1_TORQUE_CURRENT_A;

    HAL_setNumCurrentSensors(obj->halMtrHandle, objUser->numCurrentSensors);
    HAL_setNumVoltageSensors(obj->halMtrHandle, objUser->numVoltageSensors);

    // set the Clarke parameters
    setupClarke_I(obj->clarkeHandle_I, objUser->numCurrentSensors);

    TRAJ_setMinValue(obj->trajHandle_spd, -objSets->maxFrequency_Hz);
    TRAJ_setMaxValue(obj->trajHandle_spd, objSets->maxFrequency_Hz);
    TRAJ_setMaxDelta(obj->trajHandle_spd, (objSets->maxAccel_Hzps * objUser->ctrlPeriod_sec));

    TRAJ_setMinValue(obj->trajHandle_Is, -objSets->maxCurrentSet_A);
    TRAJ_setMaxValue(obj->trajHandle_Is, objSets->maxCurrentSet_A);
    TRAJ_setMaxDelta(obj->trajHandle_Is, (objSets->maxCurrentSet_A * 0.001f * objUser->ctrlPeriod_sec));




    // set the default estimator parameters
    EST_setParams(obj->estHandle, obj->userParamsHandle);
    EST_setFlag_enableForceAngle(obj->estHandle, obj->flagEnableForceAngle);
    EST_setFlag_enableRsRecalc(obj->estHandle, obj->flagEnableRsRecalc);

    // set the scale factor for high frequency low inductance motor
    EST_setOneOverFluxGain_sf(obj->estHandle,
                                obj->userParamsHandle, USER_M1_EST_FLUX_HF_SF);
    EST_setFreqLFP_sf(obj->estHandle,
                        obj->userParamsHandle, USER_M1_EST_FREQ_HF_SF);
    EST_setBemf_sf(obj->estHandle,
                    obj->userParamsHandle, USER_M1_EST_BEMF_HF_SF);

    objSets->Ls_d_comp_H = EST_getLs_d_H(obj->estHandle);
    objSets->Ls_q_comp_H = EST_getLs_q_H(obj->estHandle);

    // if motor is an induction motor, configure default state of PowerWarp
    if(objUser->motor_type == MOTOR_TYPE_INDUCTION)
    {
        EST_setFlag_enablePowerWarp(obj->estHandle, obj->flagEnablePowerWarp);
        EST_setFlag_bypassLockRotor(obj->estHandle, obj->flagBypassLockRotor);
    }

    // set the Clarke parameters
    setupClarke_V(obj->clarkeHandle_V, objUser->numVoltageSensors);    



    #define DEADBAND_usec 1.100f
    #define NOISE_WINDOW_usec 1.55f
    #define ADC_SAMPLE_usec 0.602863597f
    HAL_setTriggerPrams(&(obj->pwmData), USER_SYSTEM_FREQ_MHz,
                        DEADBAND_usec,
                        NOISE_WINDOW_usec,
                        ADC_SAMPLE_usec);        
    HAL_getPWMPeriod(obj->halMtrHandle, &(obj->pwmData));





    


    // setup the controllers, speed, d/q-axis current pid regulator
    setupControllers(handle);

    // update the coefficient of the controllers gains
    updateControllerSF(handle);

    obj->flagMotorIdentified = EST_isMotorIdentified(obj->estHandle);

    obj->flagEnableTuneController = true;

    return;
}   // end of initMotor1CtrlParameters() function

void runMotor1OffsetsCalculation(MOTOR_Handle handle)
{
    MOTOR_Vars_t *obj = (MOTOR_Vars_t *)handle;
    MOTOR_SetVars_t *objSets = (MOTOR_SetVars_t *)(handle->motorSetsHandle);

    // Offsets in phase current sensing
    ADC_setPPBReferenceOffset(MTR1_IU_ADC_BASE, MTR1_IU_ADC_PPB_NUM,
            USER_M1_IA_OFFSET_AD);

    ADC_setPPBReferenceOffset(MTR1_IV_ADC_BASE, MTR1_IV_ADC_PPB_NUM,
            USER_M1_IB_OFFSET_AD);

    ADC_setPPBReferenceOffset(MTR1_IW_ADC_BASE, MTR1_IW_ADC_PPB_NUM,
            USER_M1_IC_OFFSET_AD);    

    obj->adcData.offset_I_ad.value[0]  = USER_M1_IA_OFFSET_AD;
    obj->adcData.offset_I_ad.value[1]  = USER_M1_IB_OFFSET_AD;
    obj->adcData.offset_I_ad.value[2]  = USER_M1_IC_OFFSET_AD;
    
    // Offsets in phase voltage sensing
    obj->adcData.offset_V_sf.value[0]  = USER_M1_VA_OFFSET_SF;
    obj->adcData.offset_V_sf.value[1]  = USER_M1_VB_OFFSET_SF;
    obj->adcData.offset_V_sf.value[2]  = USER_M1_VC_OFFSET_SF;

    // calculate motor protection value
    calcMotorOverCurrentThreshold(handle);

    HAL_setMtrCMPSSDACValue(obj->halMtrHandle,
                            objSets->dacCMPValH, objSets->dacCMPValL);

    if(obj->flagEnableOffsetCalc == true)
    {
        float32_t offsetK1 = 0.998001f;  // Offset filter coefficient K1: 0.05/(T+0.05);
        float32_t offsetK2 = 0.001999f;  // Offset filter coefficient K2: T/(T+0.05);
        float32_t invCurrentSf = 1.0f / obj->adcData.current_sf;
        float32_t invVdcbus;

        uint16_t offsetCnt;

        DEVICE_DELAY_US(2.0f);   // delay 2us
        ADC_setPPBReferenceOffset(MTR1_IU_ADC_BASE, MTR1_IU_ADC_PPB_NUM, 0);
        ADC_setPPBReferenceOffset(MTR1_IV_ADC_BASE, MTR1_IV_ADC_PPB_NUM, 0);
        ADC_setPPBReferenceOffset(MTR1_IW_ADC_BASE, MTR1_IW_ADC_PPB_NUM, 0);

        obj->adcData.offset_I_ad.value[0] =
            obj->adcData.offset_I_ad.value[0] * obj->adcData.current_sf;
        obj->adcData.offset_I_ad.value[1] =
            obj->adcData.offset_I_ad.value[1] * obj->adcData.current_sf;
        obj->adcData.offset_I_ad.value[2] =
            obj->adcData.offset_I_ad.value[2] * obj->adcData.current_sf;

        // Set the 3-phase output PWMs to 50% duty cycle
        obj->pwmData.Vabc_pu.value[0] = 0.0f;
        obj->pwmData.Vabc_pu.value[1] = 0.0f;
        obj->pwmData.Vabc_pu.value[2] = 0.0f;
        
        // write the PWM compare values
        HAL_writePWMData(obj->halMtrHandle, &obj->pwmData);



        // enable the PWM
        HAL_enablePWM(obj->halMtrHandle);
        HAL_clearMtrFaultStatus(obj->halMtrHandle);

        for(offsetCnt = 0; offsetCnt < 21000; offsetCnt++)
        {
            // clear the ADC interrupt flag
            ADC_clearInterruptStatus(MTR1_ADC_INT_BASE, MTR1_ADC_INT_NUM);

            while(ADC_getInterruptStatus(MTR1_ADC_INT_BASE, MTR1_ADC_INT_NUM) == false);


            HAL_readMtr1ADCData(&obj->adcData);

            if(offsetCnt >= 1000)       // Ignore the first 1000 times
            {
                // Offsets in phase current sensing
                obj->adcData.offset_I_ad.value[0] =
                        offsetK1 * obj->adcData.offset_I_ad.value[0] +
                        obj->adcData.I_A.value[0] * offsetK2;

                obj->adcData.offset_I_ad.value[1] =
                        offsetK1 * obj->adcData.offset_I_ad.value[1] +
                        obj->adcData.I_A.value[1] * offsetK2;

                obj->adcData.offset_I_ad.value[2] =
                        offsetK1 * obj->adcData.offset_I_ad.value[2] +
                        obj->adcData.I_A.value[2] * offsetK2;

                invVdcbus = 1.0f / obj->adcData.VdcBus_V;

                // Offsets in phase voltage sensing
                obj->adcData.offset_V_sf.value[0] =
                         offsetK1 * obj->adcData.offset_V_sf.value[0] +
                         (invVdcbus * obj->adcData.V_V.value[0]) * offsetK2;

                obj->adcData.offset_V_sf.value[1] =
                         offsetK1 * obj->adcData.offset_V_sf.value[1] +
                         (invVdcbus * obj->adcData.V_V.value[1]) * offsetK2;

                obj->adcData.offset_V_sf.value[2] =
                         offsetK1 * obj->adcData.offset_V_sf.value[2] +
                         (invVdcbus * obj->adcData.V_V.value[2]) * offsetK2;
            }
            else if (offsetCnt <= 1000)
            {
                // enable the PWM
                HAL_enablePWM(obj->halMtrHandle);
            }
        } // for()

        // disable the PWM
        HAL_disablePWM(obj->halMtrHandle);

        obj->adcData.offset_I_ad.value[0] =
            obj->adcData.offset_I_ad.value[0] * invCurrentSf;
        obj->adcData.offset_I_ad.value[1] =
            obj->adcData.offset_I_ad.value[1] * invCurrentSf;
        obj->adcData.offset_I_ad.value[2] =
            obj->adcData.offset_I_ad.value[2] * invCurrentSf;

        ADC_setPPBReferenceOffset(MTR1_IU_ADC_BASE, MTR1_IU_ADC_PPB_NUM, (uint16_t)obj->adcData.offset_I_ad.value[0]);
        ADC_setPPBReferenceOffset(MTR1_IV_ADC_BASE, MTR1_IV_ADC_PPB_NUM, (uint16_t)obj->adcData.offset_I_ad.value[1]);
        ADC_setPPBReferenceOffset(MTR1_IW_ADC_BASE, MTR1_IW_ADC_PPB_NUM, (uint16_t)obj->adcData.offset_I_ad.value[2]);
    }   // flagEnableOffsetCalc = true

    // Check current and voltage offset
    if( (obj->adcData.offset_I_ad.value[0] > USER_M1_IA_OFFSET_AD_MAX) ||
        (obj->adcData.offset_I_ad.value[0] < USER_M1_IA_OFFSET_AD_MIN) )
    {
        obj->faultMtrNow.bit.currentOffset = 1;
    }

    if( (obj->adcData.offset_I_ad.value[1] > USER_M1_IB_OFFSET_AD_MAX) ||
        (obj->adcData.offset_I_ad.value[1] < USER_M1_IB_OFFSET_AD_MIN) )
    {
        obj->faultMtrNow.bit.currentOffset = 1;
    }

    if( (obj->adcData.offset_I_ad.value[2] > USER_M1_IC_OFFSET_AD_MAX) ||
        (obj->adcData.offset_I_ad.value[2] < USER_M1_IC_OFFSET_AD_MIN) )
    {
        obj->faultMtrNow.bit.currentOffset = 1;
    }

    if( (obj->adcData.offset_V_sf.value[0] > USER_M1_VA_OFFSET_SF_MAX) ||
        (obj->adcData.offset_V_sf.value[0] < USER_M1_VA_OFFSET_SF_MIN) )
    {
        obj->faultMtrNow.bit.voltageOffset = 1;
    }

    if( (obj->adcData.offset_V_sf.value[1] > USER_M1_VB_OFFSET_SF_MAX) ||
        (obj->adcData.offset_V_sf.value[1] < USER_M1_VB_OFFSET_SF_MIN) )
    {
        obj->faultMtrNow.bit.voltageOffset = 1;
    }

    if( (obj->adcData.offset_V_sf.value[2] > USER_M1_VC_OFFSET_SF_MAX) ||
        (obj->adcData.offset_V_sf.value[2] < USER_M1_VC_OFFSET_SF_MIN) )
    {
        obj->faultMtrNow.bit.voltageOffset = 1;
    }

    if((obj->faultMtrNow.bit.voltageOffset == 0) &&
            (obj->faultMtrNow.bit.currentOffset == 0))
    {
        obj->flagEnableOffsetCalc = false;
    }

    // acknowledge the ADC interrupt
    HAL_ackMtr1ADCInt();   

    return;
} // end of runMotor1OffsetsCalculation() function

// always call  this function in the background loop when the background is free
void runMotor1Control(MOTOR_Handle handle)
{
    MOTOR_Vars_t *obj = (MOTOR_Vars_t *)handle;
    MOTOR_SetVars_t *objSets = (MOTOR_SetVars_t *)(obj->motorSetsHandle);
    USER_Params *objUser = (USER_Params *)(obj->userParamsHandle);

    if(HAL_getPwmEnableStatus(obj->halMtrHandle) == true)
    {
        if(HAL_getMtrTripFaults(obj->halMtrHandle) != 0)
        {
            obj->faultMtrNow.bit.moduleOverCurrent = 1;
        }
    }

    obj->faultMtrPrev.all |= obj->faultMtrNow.all;
    obj->faultMtrUse.all = obj->faultMtrNow.all & obj->faultMtrMask.all;

    HAL_setMtrCMPSSDACValue(obj->halMtrHandle,
                            objSets->dacCMPValH, objSets->dacCMPValL);

    if(obj->flagClearFaults == true)
    {
        HAL_clearMtrFaultStatus(obj->halMtrHandle);
        obj->faultMtrNow.all &= MTR_FAULT_CLEAR;
        obj->flagClearFaults = false;
    } 


    if(obj->flagEnableRunAndIdentify == true)
    {
        obj->speedRef_Hz = obj->speedSet_Hz;
        obj->accelerationMax_Hzps = obj->accelerationSet_Hzps;

 
        // Had some faults to stop the motor
        if(obj->faultMtrUse.all != 0)
        {
            if(obj->flagRunIdentAndOnLine == true)
            {
                obj->flagRunIdentAndOnLine = false;
                obj->controlStatus = MOTOR_FAULT_STOP;

                obj->stopWaitTimeCnt = objSets->restartWaitTimeSet;
                obj->restartTimesCnt++;

                if(obj->flagEnableRestart == false)
                {
                    obj->flagEnableRunAndIdentify = false;
                    obj->stopWaitTimeCnt = 0;
                }
            }
            else if(obj->stopWaitTimeCnt == 0)
            {
                if(obj->restartTimesCnt < objSets->restartTimesSet)
                {
                    obj->flagClearFaults = 1;
                }
                else
                {
                    obj->flagEnableRunAndIdentify = false;
                }
            }
        }
        // Restart
        else if((obj->flagRunIdentAndOnLine == false) &&
                (obj->stopWaitTimeCnt == 0))
        {
            restartMotorControl(handle);
        }
    }
    // if(obj->flagEnableRunAndIdentify == false)
    else if(obj->flagRunIdentAndOnLine == true)
    {
        obj->speedRef_Hz = 0.0f;
       
        stopMotorControl(handle);

        if(obj->flagEnableFlyingStart == false)
        {
            obj->stopWaitTimeCnt = objSets->stopWaitTimeSet;
        }
        else
        {
            obj->stopWaitTimeCnt = 0;
        }
    }
    else
    {
    }

    // enable or disable bypassLockRotor flag
    if(objUser->motor_type == MOTOR_TYPE_INDUCTION && (obj->flagMotorIdentified == true))
    {
        EST_setFlag_bypassLockRotor(obj->estHandle,
                                    obj->flagBypassLockRotor);
    }

    if(obj->flagRunIdentAndOnLine == true)      // Start the motor
    {
        if(HAL_getPwmEnableStatus(obj->halMtrHandle) == false)
        {
            // enable the estimator
            EST_enable(obj->estHandle);

            // enable the trajectory generator
            EST_enableTraj(obj->estHandle);

            // enable the PWM
            HAL_enablePWM(obj->halMtrHandle);
        }
        
        if(obj->flagMotorIdentified == true)
        {
            if(obj->speedRef_Hz > 0.0f)
            {
                obj->direction = 1.0f;
            }
            else
            {
                obj->direction = -1.0f;
            }
            // enable or disable force angle
            EST_setFlag_enableForceAngle(obj->estHandle, obj->flagEnableForceAngle);

            // enable or disable stator resistance (Rs) re-calculation
            EST_setFlag_enableRsRecalc(obj->estHandle, obj->flagEnableRsRecalc);

            // Sets the target speed for the speed trajectory
            TRAJ_setTargetValue(obj->trajHandle_spd, obj->speedRef_Hz);

            if((fabsf(obj->speed_Hz) > objSets->speedStart_Hz) ||
                    (obj->controlStatus == MOTOR_CTRL_RUN))
            {
                // Inject the current for debugging
                obj->IdInj_A = objSets->IdInj_A;
                obj->IqInj_A = objSets->IqInj_A;

                obj->accelerationMax_Hzps = obj->accelerationSet_Hzps;

                if(obj->controlStatus == MOTOR_CL_RUNNING)
                {
                    if(obj->stateRunTimeCnt == objSets->startupTimeDelay)
                    {
                        obj->Idq_out_A.value[0] = 0.0f;
                        obj->controlStatus = MOTOR_CTRL_RUN;
                    }
                }
                
                if(obj->flagEnableLsUpdate ==  true)
                {
                    // Calculate the Ld and Lq which reduce with current
                    objSets->Ls_d_comp_H = objUser->motor_Ls_d_H * (1.0f - obj->Is_A * objSets->Ls_d_Icomp_coef);
                    objSets->Ls_q_comp_H = objUser->motor_Ls_q_H * (1.0f - obj->Is_A * objSets->Ls_q_Icomp_coef);

                    if(objSets->Ls_d_comp_H < objSets->Ls_min_H)
                    {
                        objSets->Ls_d_comp_H = objSets->Ls_min_H;
                    }

                    if(objSets->Ls_q_comp_H < objSets->Ls_min_H)
                    {
                        objSets->Ls_q_comp_H = objSets->Ls_min_H;
                    }

                    // Update the Ld and Lq for motor control
                    EST_setLs_d_H(obj->estHandle, objSets->Ls_d_comp_H);
                    EST_setLs_q_H(obj->estHandle, objSets->Ls_q_comp_H);
                }

                PI_setMinMax(obj->piHandle_spd, -objSets->maxCurrent_A, objSets->maxCurrent_A);
                SVGEN_setMode(obj->svgenHandle, obj->svmMode);
            }
            else    // Start to run the motor
            {
                obj->accelerationMax_Hzps = objSets->accelStart_Hzps;

                if(obj->speed_int_Hz >= 0.0f)
                {
                    PI_setMinMax(obj->piHandle_spd, 0.0f, obj->IsSet_A);
                }
                else
                {
                    PI_setMinMax(obj->piHandle_spd, -obj->IsSet_A, 0.0f);
                }
            }

            //  Sets the acceleration / deceleration for the speed trajectory
            TRAJ_setMaxDelta(obj->trajHandle_spd,
                (obj->accelerationMax_Hzps * objUser->ctrlPeriod_sec));              
        }

        // Identification
#if (DMC_BUILDLEVEL == DMC_LEVEL_3)
        obj->Idq_out_A.value[0] = obj->Idq_set_A.value[0];
        obj->Idq_out_A.value[1] = obj->Idq_set_A.value[1] * obj->direction;
#endif // (DMC_BUILDLEVEL == DMC_LEVEL_3)
    }
    else
    {
        // reset motor control parameters
        resetMotorControl(handle);
    }

    // check the trajectory generator
    if(EST_isTrajError(obj->estHandle) == true)
    {
        // disable the PWM
        HAL_disablePWM(obj->halMtrHandle);
    }
    else    // (EST_isTrajError(obj->estHandle) == false)
    {
        // update the trajectory generator state
        EST_updateTrajState(obj->estHandle);
    }       // (EST_isTrajError(obj->estHandle) == false)

    // check the estimator
    if(EST_isError(obj->estHandle) == true)
    {
        // disable the PWM
        HAL_disablePWM(obj->halMtrHandle);
    }
    else    // (EST_isError(obj->estHandle) == false)
    {
        bool flagEstStateChanged = false;

        float32_t Id_target_A = EST_getIntValue_Id_A(obj->estHandle);

        if(obj->flagMotorIdentified == true)
        {
            flagEstStateChanged = EST_updateState(obj->estHandle, 0.0f);
        }
        else    // obj->flagMotorIdentified = false
        {
            flagEstStateChanged = EST_updateState(obj->estHandle, Id_target_A);
        }       // obj->flagMotorIdentified = false

        if(flagEstStateChanged == true)
        {
            // configure the trajectory generator, enter once every state
            EST_configureTraj(obj->estHandle);

            if(obj->flagMotorIdentified == false)
            {
                // configure the controllers, enter once every state
                EST_configureTrajState(obj->estHandle, obj->userParamsHandle,
                                       obj->piHandle_spd,
                                       obj->piHandle_Id, obj->piHandle_Iq);
            }

            if((EST_isLockRotor(obj->estHandle) == true) ||
                    ( (EST_isMotorIdentified(obj->estHandle) == true)
                                && (EST_isIdle(obj->estHandle) == true) ) )
            {
                if(EST_isMotorIdentified(obj->estHandle) == true)
                {
                    obj->flagMotorIdentified = true;

                    // clear the flag
                    obj->flagRunIdentAndOnLine = false;
                    obj->flagEnableRunAndIdentify = false;
                        
                    obj->controlStatus = MOTOR_STOP_IDLE;

                    // disable the estimator
                    EST_disable(obj->estHandle);

                    // enable the trajectory generator
                    EST_disableTraj(obj->estHandle);

                    obj->faultMtrUse.all = 0x0000;
                    obj->faultMtrNow.all = 0x0000;
                }

                if(objUser->motor_type == MOTOR_TYPE_INDUCTION)
                {
                    // clear the flag
                    obj->flagRunIdentAndOnLine = false;
                    obj->flagEnableRunAndIdentify = false;
                }
            }
        }
    }


    if(obj->flagMotorIdentified == true)
    {
        if(obj->flagSetupController == true)
        {
            // update the controller
            updateControllers(handle);


        }
        else
        {
            obj->flagSetupController = true;

            setupControllers(handle);
        }

    }
    // run Rs online
    runRsOnLine(handle);
    // update the global variables
    updateGlobalVariables(handle);


    return;
}   // end of the runMOTOR1Control() function

#define SAMPLE_SKIP 0
int skipNum = 0;

__interrupt void motor1CtrlISR(void)
{
    motorVars_M1.ISRCount++;

    //Capture data every SAMPLE_SKIP number of ISRs
    if(skipNum == SAMPLE_SKIP){
        skipNum = 0;
        // SIGNALSIGHT_capturePlotData();
    }
    else{
        skipNum++;
    }

    MOTOR_Vars_t *obj = (MOTOR_Vars_t *)motorHandle_M1;
    MOTOR_SetVars_t *objSets = (MOTOR_SetVars_t *)(obj->motorSetsHandle);

    // acknowledge the ADC interrupt
    HAL_ackMtr1ADCInt();

    // read the ADC data with offsets
    HAL_readMtr1ADCData(&obj->adcData);

//------------------------------------------------------------------------------
// 180-degree Sinusoidal Sensorless-FOC
//******************************************************************************
  




    // sensorless-FOC
    MATH_Vec2 phasor;

#if (DMC_BUILDLEVEL <= DMC_LEVEL_3)
    ANGLE_GEN_run(obj->angleGenHandle, obj->speed_int_Hz);
    obj->angleGen_rad = ANGLE_GEN_getAngle(obj->angleGenHandle);
#endif // (DMC_BUILDLEVEL <= DMC_LEVEL_3)

    // remove offsets
    obj->adcData.V_V.value[0] -=
            obj->adcData.offset_V_sf.value[0] * obj->adcData.VdcBus_V;

    obj->adcData.V_V.value[1] -=
            obj->adcData.offset_V_sf.value[1] * obj->adcData.VdcBus_V;

    obj->adcData.V_V.value[2] -=
            obj->adcData.offset_V_sf.value[2] * obj->adcData.VdcBus_V;


    // run Clarke transform on voltage
    CLARKE_run_threeInput(obj->clarkeHandle_V,
               &obj->adcData.V_V, &obj->estInputData.Vab_V);
    // run Clarke transform on current
    CLARKE_run_threeInput(obj->clarkeHandle_I,
                          &obj->adcData.I_A, &obj->estInputData.Iab_A);

    // store the input data into a buffer
    obj->estInputData.dcBus_V = obj->adcData.VdcBus_V;

    // configure the trajectory generator
    EST_run(obj->estHandle, &obj->estInputData, &obj->estOutputData);

    // compute angle with delay compensation
    obj->angleESTCOMP_rad =
            obj->angleESTDelayed_sf * obj->estOutputData.fm_lp_rps;

    obj->angleEST_rad =
            MATH_incrAngle(obj->estOutputData.angle_rad, obj->angleESTCOMP_rad);
    obj->speedEST_Hz = EST_getFm_lp_Hz(obj->estHandle);
    obj->speed_Hz = obj->speedEST_Hz;
    obj->oneOverDcBus_invV = obj->estOutputData.oneOverDcBus_invV;

    if(((EST_isMotorIdentified(obj->estHandle) == false) ||
            (EST_getState(obj->estHandle) == EST_STATE_RS)) &&
            (EST_isEnabled(obj->estHandle) == true))
    {   
        obj->Idq_out_A.value[0] = 0.0f;
        obj->controlStatus = MOTOR_CTRL_RUN;

        // run identification or Rs Recalibration
        // setup the trajectory generator
        EST_setupTrajState(obj->estHandle,
                           obj->Idq_out_A.value[1],
                           obj->speedRef_Hz,
                           0.0);

        // run the trajectories
        EST_runTraj(obj->estHandle);

        obj->IdRated_A = EST_getIntValue_Id_A(obj->estHandle);

        // store the input data into a buffer
        obj->estInputData.speed_ref_Hz = EST_getIntValue_spd_Hz(obj->estHandle);
        obj->speed_int_Hz = obj->estInputData.speed_ref_Hz;

        obj->enableSpeedCtrl = EST_doSpeedCtrl(obj->estHandle);
        obj->enableCurrentCtrl = EST_doCurrentCtrl(obj->estHandle);

    }
    else if(obj->flagMotorIdentified == true)   // Normal Running
    {
        if(obj->flagRunIdentAndOnLine == true)
        {
            // run a trajectory for speed reference,
            // so the reference changes with a ramp instead of a step
            TRAJ_run(obj->trajHandle_spd);
            obj->enableCurrentCtrl = obj->flagEnableCurrentCtrl;
            obj->enableSpeedCtrl = obj->flagEnableSpeedCtrl;


            // get Id reference for Rs OnLine
            obj->IdRated_A = EST_getIdRated_A(obj->estHandle);
        }
        else
        {
            obj->enableSpeedCtrl = false;
            obj->enableCurrentCtrl = false;
        }
        obj->speed_int_Hz = TRAJ_getIntValue(obj->trajHandle_spd);
    }

    obj->estInputData.speed_ref_Hz = obj->speed_int_Hz;
    
    obj->speedFilter_Hz = obj->speedFilter_Hz *0.875f + obj->speed_Hz * 0.125f;
    obj->speedAbs_Hz = fabsf(obj->speedFilter_Hz);

    // Running state
    obj->stateRunTimeCnt++;

    if(obj->controlStatus >= MOTOR_CL_RUNNING)
    {
        obj->angleFOC_rad = obj->angleEST_rad;
    }
    else if(obj->controlStatus == MOTOR_OL_START)
    {
        obj->angleFOC_rad = obj->angleEST_rad;
        obj->controlStatus = MOTOR_CL_RUNNING;

    }
    else if(obj->controlStatus == MOTOR_ALIGNMENT)
    {
        obj->angleFOC_rad = 0.0f;
        obj->enableSpeedCtrl = false;


        obj->IsRef_A = 0.0f;
        obj->Idq_out_A.value[0] = objSets->alignCurrent_A;
        obj->Idq_out_A.value[1] = 0.0f;

        TRAJ_setIntValue(obj->trajHandle_spd, 0.0f);

        if((obj->stateRunTimeCnt > objSets->alignTimeDelay) ||
                 (obj->flagEnableAlignment == false))    
        {
            obj->stateRunTimeCnt = 0;
            obj->controlStatus = MOTOR_OL_START;
            obj->Idq_out_A.value[0] = objSets->fluxCurrent_A;

            EST_setAngle_rad(obj->estHandle, obj->angleFOC_rad);

            PI_setUi(obj->piHandle_spd, objSets->alignCurrent_A);

        }                        
    }
    else if(obj->controlStatus == MOTOR_SEEK_POS)
    {
        obj->enableSpeedCtrl = false;


        obj->IsRef_A = 0.0f;
        obj->Idq_out_A.value[0] = 0.0f;
        obj->Idq_out_A.value[1] = 0.0f;

        obj->angleFOC_rad = obj->angleEST_rad;

        if(obj->stateRunTimeCnt > objSets->flyingStartTimeDelay)
        {
            obj->stateRunTimeCnt = 0;
            obj->counterSpeed = 0;

            if(obj->speedAbs_Hz > objSets->speedFlyingStart_Hz)
            {
                if(obj->speedRef_Hz > 0.0f)
                {
                    obj->speed_int_Hz = obj->speed_Hz + 10.0f;
                }
                else
                {
                    obj->speed_int_Hz = obj->speed_Hz - 10.0f;
                }

                TRAJ_setIntValue(obj->trajHandle_spd, obj->speed_int_Hz);
                PI_setUi(obj->piHandle_spd, 0.0f);


                obj->controlStatus = MOTOR_CL_RUNNING;
            }
            else
            {
                obj->controlStatus = MOTOR_ALIGNMENT;
            }
        }
    }


#if (DMC_BUILDLEVEL <= DMC_LEVEL_3)
    obj->angleFOC_rad = obj->angleGen_rad;
#endif // (DMC_BUILDLEVEL <= DMC_LEVEL_3)

    // compute the sin/cos phasor
    phasor.value[0] = __cos(obj->angleFOC_rad);
    phasor.value[1] = __sin(obj->angleFOC_rad);

    // set the phasor in the Park transform
    PARK_setPhasor(obj->parkHandle_I, &phasor);

    // run the Park transform
    PARK_run(obj->parkHandle_I, &(obj->estInputData.Iab_A),
             (MATH_vec2 *)&(obj->Idq_in_A));

// End of MOTOR1_FAST
//------------------------------------------------------------------------------

//---------- Common Speed and Current Loop for all observers -------------------
#if (DMC_BUILDLEVEL >= DMC_LEVEL_4)
    


    // run the speed controller
    obj->counterSpeed++;

    if(obj->counterSpeed >= obj->numCtrlTicksPerSpeedTick)
    {
        obj->counterSpeed = 0;

        if(obj->enableSpeedCtrl == true)
        {
            obj->Is_ffwd_A = 0.0f;
            PI_run_series(obj->piHandle_spd,
                   obj->speed_int_Hz, obj->speed_Hz,
                   obj->Is_ffwd_A, (float32_t *)&obj->IsRef_A);
        }    // (obj->enableSpeedCtrl == true)
        else if((obj->controlStatus >= MOTOR_CL_RUNNING) &&
                (obj->flagMotorIdentified == true))
        {
            if(obj->speed_int_Hz > 0.0f)
            {
                obj->IsRef_A = obj->IsSet_A;
            }
            else
            {
                obj->IsRef_A = -obj->IsSet_A;
            }

            // for switching back speed closed-loop control
            PI_setUi(obj->piHandle_spd, obj->IsRef_A);
        }
    }

    obj->Idq_out_A.value[1] = obj->IsRef_A;

    obj->IdqRef_A.value[0] = obj->Idq_out_A.value[0] + obj->IdRated_A + obj->IdInj_A;

    // update Id reference for Rs OnLine
    EST_updateId_ref_A(obj->estHandle, &obj->IdqRef_A.value[0]);

    obj->IdqRef_A.value[1] = obj->Idq_out_A.value[1] + obj->IqInj_A;
#endif // (DMC_BUILDLEVEL >= DMC_LEVEL_4)
#if (DMC_BUILDLEVEL == DMC_LEVEL_3)
    obj->IdqRef_A.value[0] = obj->Idq_set_A.value[0];
    obj->IdqRef_A.value[1] = obj->Idq_set_A.value[1];
#endif // (DMC_BUILDLEVEL == DMC_LEVEL_3)

    if(obj->enableCurrentCtrl == true)
    {
        obj->Vdq_ffwd_V.value[0] = 0.0f;
        obj->Vdq_ffwd_V.value[1] = 0.0f;

        // Maximum voltage output
        obj->VsMax_V = obj->maxVsMag_pu * obj->adcData.VdcBus_V;
        PI_setMinMax(obj->piHandle_Id, -obj->VsMax_V, obj->VsMax_V);
        

        // run the Id controller
        PI_run_series(obj->piHandle_Id,
                      obj->IdqRef_A.value[0], obj->Idq_in_A.value[0],
                      obj->Vdq_ffwd_V.value[0], (float32_t*)&obj->Vdq_out_V.value[0]);

        // calculate Iq controller limits
        float32_t outMax_V = __sqrt((obj->VsMax_V * obj->VsMax_V) -
                          (obj->Vdq_out_V.value[0] * obj->Vdq_out_V.value[0]));

        PI_setMinMax(obj->piHandle_Iq, -outMax_V, outMax_V);

        // run the Iq controller
        PI_run_series(obj->piHandle_Iq,
                      obj->IdqRef_A.value[1], obj->Idq_in_A.value[1],
                      obj->Vdq_ffwd_V.value[1], (float32_t*)&obj->Vdq_out_V.value[1]);

        // set the Id reference value in the estimator
        EST_setId_ref_A(obj->estHandle, obj->IdqRef_A.value[0]);
        EST_setIq_ref_A(obj->estHandle, obj->IdqRef_A.value[1]);
    }

#if (DMC_BUILDLEVEL == DMC_LEVEL_2)
    VS_FREQ_run(obj->VsFreqHandle, obj->speed_int_Hz);
    obj->Vdq_out_V.value[0] = VS_FREQ_getVd_out(obj->VsFreqHandle);
    obj->Vdq_out_V.value[1] = VS_FREQ_getVq_out(obj->VsFreqHandle);
#endif // (DMC_BUILDLEVEL == DMC_LEVEL_2)


    // set the phasor in the inverse Park transform
    IPARK_setPhasor(obj->iparkHandle_V, &phasor);

    // run the inverse Park module
    IPARK_run(obj->iparkHandle_V,
              &obj->Vdq_out_V, &obj->Vab_out_V);

    // setup the space vector generator (SVGEN) module
    SVGEN_setup(obj->svgenHandle, obj->estOutputData.oneOverDcBus_invV);
    
    // run the space vector generator (SVGEN) module
    SVGEN_run(obj->svgenHandle,
              &obj->Vab_out_V, &(obj->pwmData.Vabc_pu));


#if (DMC_BUILDLEVEL == DMC_LEVEL_1)
    // output 50%
    obj->pwmData.Vabc_pu.value[0] = 0.0f;
    obj->pwmData.Vabc_pu.value[1] = 0.0f;
    obj->pwmData.Vabc_pu.value[2] = 0.0f;
#endif // (DMC_BUILDLEVEL == DMC_LEVEL_1)

    if(HAL_getPwmEnableStatus(obj->halMtrHandle) == false)
    {
        // clear PWM data
        obj->pwmData.Vabc_pu.value[0] = 0.0f;
        obj->pwmData.Vabc_pu.value[1] = 0.0f;
        obj->pwmData.Vabc_pu.value[2] = 0.0f;
    }

    // write the PWM compare values
    HAL_writePWMData(obj->halMtrHandle, &(obj->pwmData));


    // Collect current and voltage data to calculate the RMS value
    collectRMSData(motorHandle_M1);








        
    return;
} // end of motor1CtrlISR() function

//
//-- end of this file ----------------------------------------------------------
//
