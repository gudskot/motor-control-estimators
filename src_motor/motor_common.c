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
//! \file   /solutions/universal_motorcontrol_lab/common/source/motor_comm.c
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

//! \brief calculate motor over current threshold
void calcMotorOverCurrentThreshold(MOTOR_Handle handle)
{
    MOTOR_Vars_t *obj = (MOTOR_Vars_t *)handle;
    MOTOR_SetVars_t *objSets = (MOTOR_SetVars_t *)(obj->motorSetsHandle);

    float32_t overCurrent_A;
    
    overCurrent_A = (objSets->overCurrent_A > objSets->maxPeakCurrent_A) ?
                     objSets->maxPeakCurrent_A : objSets->overCurrent_A;
    int16_t cmpValue = (int16_t)(overCurrent_A * objSets->currentInv_sf);

    objSets->dacCMPValH = obj->adcData.offset_I_ad.value[0] + cmpValue;
    objSets->dacCMPValH = (objSets->dacCMPValH > 4095U) ?
                           4095U : objSets->dacCMPValH;

    objSets->dacCMPValL = (cmpValue < obj->adcData.offset_I_ad.value[0]) ?
                           (obj->adcData.offset_I_ad.value[0] - cmpValue) : 1U;
    return;
}


//! \brief checks motor faults
void checkMotorFaults(MOTOR_Handle handle)
{
    MOTOR_Vars_t *obj = (MOTOR_Vars_t *)handle;
    MOTOR_SetVars_t *objSets = (MOTOR_SetVars_t *)(handle->motorSetsHandle);

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
        
    return;
}

// Sets up control parameters for stopping motor
// pwm and estimator are not turned off
void stopMotorControl(MOTOR_Handle handle)
{
    MOTOR_Vars_t *obj = (MOTOR_Vars_t *)handle;
    obj->speed_int_Hz = 0.0f;

    // configure the speed reference trajectory (Hz)
    TRAJ_setTargetValue(obj->trajHandle_spd, 0.0f);
    TRAJ_setIntValue(obj->trajHandle_spd, 0.0f);

    obj->flagRunIdentAndOnLine = false;


    if(obj->controlStatus >= MOTOR_CHARGE)
    {
        obj->controlStatus = MOTOR_STOP_IDLE;
    }

    SVGEN_setMode(obj->svgenHandle, SVM_COM_C);

    obj->restartTimesCnt = 0;

    obj->flagStartRsOnLine = false;

    return;
}

// Sets up control parameters for restarting motor
void restartMotorControl(MOTOR_Handle handle)
{
    MOTOR_Vars_t *obj = (MOTOR_Vars_t *)handle;

    USER_Params *objUser = (USER_Params *)(handle->userParamsHandle);
    MOTOR_SetVars_t *objSets = (MOTOR_SetVars_t *)(handle->motorSetsHandle);

    if(obj->flagEnableMotorIdentify == true)
    {
        obj->estimatorMode = ESTIMATOR_MODE_FAST;


        obj->flagMotorIdentified = false;
        obj->flagSetupController = false;
        obj->svmMode = SVM_COM_C;
        obj->flagEnableFWC = false;
        obj->flagEnableMTPA = false;

        obj->speedRef_Hz = objUser->fluxExcFreq_Hz;
        obj->faultMtrMask.all = MTR_FAULT_ENABLE_OC_OUV;

        objUser->flag_bypassMotorId = false;

        // disable interrupts
        DINT;
        __asm("  NOP");

        // set the default estimator parameters
        EST_setParams(obj->estHandle, obj->userParamsHandle);

        // enable interrupts
        EINT;
        __asm("  NOP");

        obj->flagEnableMotorIdentify = false;
    }
    else
    {
        obj->flagMotorIdentified = EST_isMotorIdentified(obj->estHandle);
        obj->faultMtrMask.all = objSets->faultMtrMask.all;
    }



    if(obj->flagEnableFlyingStart == true)
    {
        obj->controlStatus = MOTOR_SEEK_POS;
    }
    else
    {
        obj->controlStatus = MOTOR_ALIGNMENT;
    }



    obj->speed_int_Hz = 0.0f;
    
    // configure the speed reference trajectory (Hz)
    TRAJ_setTargetValue(obj->trajHandle_spd, 0.0f);
    TRAJ_setIntValue(obj->trajHandle_spd, 0.0f);

    obj->speedAbs_Hz = 0.0f;
    obj->speedFilter_Hz = 0.0f;

    obj->Is_ffwd_A = 0.0f;
    obj->IdInj_A = 0.0f;
    obj->IqInj_A = 0.0f; 

    SVGEN_setMode(obj->svgenHandle, SVM_COM_C);

    obj->flagRunIdentAndOnLine = true;
    obj->stateRunTimeCnt = 0;
    obj->startSumTimesCnt++;
    obj->flagStartRsOnLine = false;

    return;
}

// Resets motor control parameters for restarting motor
void resetMotorControl(MOTOR_Handle handle)
{
    MOTOR_Vars_t *obj = (MOTOR_Vars_t *)handle;

    if(obj->flagEnableFlyingStart == false)
    {
        // disable the estimator
        EST_disable(obj->estHandle);

        // disable the trajectory generator
        EST_disableTraj(obj->estHandle);
        TRAJ_setIntValue(obj->trajHandle_spd, 0.0f);
    }
    else
    {
        TRAJ_setIntValue(obj->trajHandle_spd, obj->speed_Hz);
        obj->stateRunTimeCnt = 0;
        obj->flagStateFlyingStart = false;
    }

    TRAJ_setTargetValue(obj->trajHandle_spd, 0.0f);

    // disable the PWM
    HAL_disablePWM(obj->halMtrHandle);

    // clear integral outputs of the controllers
    PI_setRefValue(obj->piHandle_Id, 0.0f);
    PI_setRefValue(obj->piHandle_Iq, 0.0f);
    PI_setRefValue(obj->piHandle_spd, 0.0f);

    PI_setUi(obj->piHandle_Id, 0.0f);
    PI_setUi(obj->piHandle_Iq, 0.0f);
    PI_setUi(obj->piHandle_spd, 0.0f);


    // clear current references
    obj->Idq_out_A.value[0] = 0.0f;
    obj->Idq_out_A.value[1] = 0.0f;

    obj->IdRated_A = 0.0f;
    obj->IsRef_A = 0.0f;

    obj->angleCurrent_rad = 0.0f;


    obj->stateRunTimeCnt = 0;
    obj->motorStallTimeCnt = 0;
    obj->startupFailTimeCnt = 0;
    
    obj->overSpeedTimeCnt = 0;
    obj->overLoadTimeCnt = 0;
    obj->lostPhaseTimeCnt = 0;
    obj->unbalanceTimeCnt = 0;

    SVGEN_setMode(obj->svgenHandle, SVM_COM_C);

    obj->controlStatus = MOTOR_STOP_IDLE;

    return;
}

// timer base is 5ms
void runMotorMonitor(MOTOR_Handle handle)
{
    MOTOR_Vars_t *obj = (MOTOR_Vars_t *)handle;
    MOTOR_SetVars_t *objSets = (MOTOR_SetVars_t *)(obj->motorSetsHandle);


    if(obj->flagEnableRsOnLine == true)
    {
        if(obj->RsOnlineMode == RSONLINE_CONTINUE)
        {
            obj->flagStartRsOnLine = true;
        }
        else if(obj->RsOnlineTimeCnt == 0) // obj->RsOnlineMode is RSONLINE_INTERVAL
        {
            if(EST_getFlag_enableRsOnLine(obj->estHandle) == true)
            {
                obj->RsOnlineTimeCnt = objSets->RsOnlineWaitTimeSet;
                obj->flagStartRsOnLine = false;
            }
            else
            {
                obj->RsOnlineTimeCnt = objSets->RsOnlineWorkTimeSet;
                obj->flagStartRsOnLine = true;
            }
        }
        else
        {
            obj->RsOnlineTimeCnt--;
        }
    } else {
        obj->flagStartRsOnLine = false;
        obj->RsOnlineTimeCnt = 0;
    }

    if(obj->stopWaitTimeCnt > 0)
    {
        obj->stopWaitTimeCnt--;
    }

    // Check if DC bus voltage is over threshold
    if(obj->adcData.VdcBus_V > objSets->overVoltageFault_V)
    {
        if(obj->overVoltageTimeCnt > objSets->voltageFaultTimeSet)
        {
            obj->faultMtrNow.bit.overVoltage = 1;
        }
        else
        {
            obj->overVoltageTimeCnt++;
        }
    }
    else if(obj->adcData.VdcBus_V < objSets->overVoltageNorm_V)
    {
        if(obj->overVoltageTimeCnt == 0)
        {
            obj->faultMtrNow.bit.overVoltage = 0;
        }
        else
        {
            obj->overVoltageTimeCnt--;
        }
    }

    // Check if DC bus voltage is under threshold
    if(obj->adcData.VdcBus_V < objSets->underVoltageFault_V)
    {
        if(obj->underVoltageTimeCnt > objSets->voltageFaultTimeSet)
        {
            obj->faultMtrNow.bit.underVoltage = 1;
        }
        else
        {
            obj->underVoltageTimeCnt++;
        }
    }
    else if(obj->adcData.VdcBus_V > objSets->underVoltageNorm_V)
    {
        if(obj->underVoltageTimeCnt == 0)
        {
            obj->faultMtrNow.bit.underVoltage = 0;
        }
        else
        {
            obj->underVoltageTimeCnt--;
        }
    }

    // check these faults when motor is running
    if(obj->controlStatus >= MOTOR_CL_RUNNING)
    {
        // Over Load Check
        if(obj->powerActive_W > objSets->overLoadSet_W)
        {
            if(obj->overLoadTimeCnt > objSets->overLoadTimeSet)
            {
                obj->faultMtrNow.bit.overLoad = 1;
                obj->overLoadTimeCnt = 0;
            }
            else
            {
                obj->overLoadTimeCnt++;
            }
        }
        else if(obj->overLoadTimeCnt > 0)
        {
            obj->overLoadTimeCnt--;
        }

        // Motor Stall
        if( (obj->Is_A > objSets->stallCurrentSet_A)
                && (obj->speedAbs_Hz < objSets->speedFailMinSet_Hz))
        {
            if(obj->motorStallTimeCnt > objSets->motorStallTimeSet)
            {
                obj->faultMtrNow.bit.motorStall = 1;
                obj->motorStallTimeCnt = 0;
            }
            else
            {
                obj->motorStallTimeCnt++;
            }
        }
        else if(obj->motorStallTimeCnt > 0)
        {
            obj->motorStallTimeCnt--;
        }

        // (obj->torque_Nm < objSets->toqueFailMinSet_Nm)
        // Motor Lost Phase Fault Check
        if( (obj->speedAbs_Hz > objSets->speedFailMinSet_Hz) &&
            ( (obj->Irms_A[0] < objSets->lostPhaseSet_A) ||
              (obj->Irms_A[1] < objSets->lostPhaseSet_A) ||
              (obj->Irms_A[2] < objSets->lostPhaseSet_A)) )
        {
            if(obj->lostPhaseTimeCnt > objSets->lostPhaseTimeSet)
            {
                obj->faultMtrNow.bit.motorLostPhase = 1;
                obj->lostPhaseTimeCnt = 0;
            }
            else
            {
                obj->lostPhaseTimeCnt++;
            }
        }
        else if(obj->lostPhaseTimeCnt > 0)
        {
            obj->lostPhaseTimeCnt--;
        }

        // Only when the torque is great than a setting value
        if(obj->Is_A > objSets->IsFailedChekSet_A)
        {
            // Motor Phase Current Unbalance
            if(obj->unbalanceRatio > objSets->unbalanceRatioSet)
            {
                if(obj->unbalanceTimeCnt > objSets->unbalanceTimeSet)
                {
                    obj->faultMtrNow.bit.currentUnbalance = 1;
                    obj->unbalanceTimeCnt = 0;
                }
                else
                {
                    obj->unbalanceTimeCnt++;
                }
            }
            else if(obj->unbalanceTimeCnt > 0)
            {
                obj->unbalanceTimeCnt--;
            }

            // Motor Over speed
            if(obj->speedAbs_Hz > objSets->speedFailMaxSet_Hz)
            {
                if(obj->overSpeedTimeCnt > objSets->overSpeedTimeSet)
                {
                    obj->faultMtrNow.bit.overSpeed = 1;
                    obj->overSpeedTimeCnt = 0;
                }
                else
                {
                    obj->overSpeedTimeCnt++;
                }
            }
            else if(obj->overSpeedTimeCnt > 0)
            {
                obj->overSpeedTimeCnt--;
            }

            // Motor Startup Failed
            if( (obj->Is_A < objSets->stallCurrentSet_A)
               && (obj->speedAbs_Hz < objSets->speedFailMinSet_Hz))
            {
                if(obj->startupFailTimeCnt > objSets->startupFailTimeSet)
                {
                    obj->faultMtrNow.bit.startupFailed = 1;
                    obj->startupFailTimeCnt = 0;
                }
                else
                {
                    obj->startupFailTimeCnt++;
                }
            }
            else if(obj->startupFailTimeCnt > 0)
            {
                obj->startupFailTimeCnt--;
            }

        } // obj->Is_A > objSets->IsFailedChekSet_A
    } // obj->operateState == OPERATE_State_Run

    return;
}

void collectRMSData(MOTOR_Handle handle)
{
    MOTOR_Vars_t *obj = (MOTOR_Vars_t *)handle;

    obj->IrmsCalSum[0] += obj->adcData.I_A.value[0] * obj->adcData.I_A.value[0];
    obj->IrmsCalSum[1] += obj->adcData.I_A.value[1] * obj->adcData.I_A.value[1];
    obj->IrmsCalSum[2] += obj->adcData.I_A.value[2] * obj->adcData.I_A.value[2];

    obj->VIrmsIsrCnt++;

    if(obj->VIrmsIsrCnt > obj->VIrmsIsrSet)
    {
        obj->IrmsPrdSum[0] = obj->IrmsCalSum[0];
        obj->IrmsPrdSum[1] = obj->IrmsCalSum[1];
        obj->IrmsPrdSum[2] = obj->IrmsCalSum[2];

        obj->IrmsCalSum[0] = 0.0f;
        obj->IrmsCalSum[1] = 0.0f;
        obj->IrmsCalSum[2] = 0.0f;

        obj->VIrmsIsrCnt = 0;
        obj->flagVIrmsCal = true;
    }
}

void calculateRMSData(MOTOR_Handle handle)
{
    MOTOR_Vars_t *obj = (MOTOR_Vars_t *)handle;

    float32_t IrmsMax_A, IrmsMin_A, VIrmsIsrSet;

    if(obj->flagVIrmsCal == true)
    {
        obj->flagVIrmsCal = false;

        obj->Irms_A[0] =
                sqrtf(obj->IrmsPrdSum[0] * obj->IrmsCalSF);

        obj->Irms_A[1] =
                sqrtf(obj->IrmsPrdSum[1] * obj->IrmsCalSF);

        obj->Irms_A[2] =
                sqrtf(obj->IrmsPrdSum[2] * obj->IrmsCalSF);

        if(obj->Irms_A[0] > obj->Irms_A[1])
        {
            IrmsMax_A = obj->Irms_A[0];
            IrmsMin_A = obj->Irms_A[1];
        }
        else
        {
            IrmsMax_A = obj->Irms_A[1];
            IrmsMin_A = obj->Irms_A[0];
        }

        IrmsMax_A = (obj->Irms_A[2] > IrmsMax_A) ? obj->Irms_A[2] : IrmsMax_A;
        IrmsMin_A = (obj->Irms_A[2] < IrmsMin_A) ? obj->Irms_A[2] : IrmsMin_A;

        if(obj->speedAbs_Hz != 0.0f)
        {
            VIrmsIsrSet = obj->VIrmsIsrScale / obj->speedAbs_Hz;

            VIrmsIsrSet = (VIrmsIsrSet > obj->VIrmsIsrScale) ?
                    obj->VIrmsIsrScale : VIrmsIsrSet;

            VIrmsIsrSet = (VIrmsIsrSet != 0) ?
                    VIrmsIsrSet: obj->VIrmsIsrScale;
        }
        else
        {
            VIrmsIsrSet = obj->VIrmsIsrScale;
        }

        obj->IrmsCalSF = 1.0f / VIrmsIsrSet;
        obj->VIrmsIsrSet = (uint16_t)(VIrmsIsrSet);

        obj->unbalanceRatio =
                (IrmsMax_A - IrmsMin_A) / (IrmsMax_A + IrmsMin_A);
    }
}

// setupCurrentControllers()
void setupCurrentControllers(MOTOR_Handle handle)
{
    MOTOR_Vars_t *obj = (MOTOR_Vars_t *)handle;
    USER_Params *objUser = (USER_Params *)(handle->userParamsHandle);

    float32_t RoverL_Kp_sf = objUser->RoverL_Kp_sf;
    float32_t dcBus_nominal_V = objUser->dcBus_nominal_V;
    float32_t maxCurrent_A = objUser->maxCurrent_A;
    float32_t RoverL_min_rps = objUser->RoverL_min_rps;
    float32_t currentCtrlPeriod_sec =
                (float32_t)objUser->numCtrlTicksPerCurrentTick /
                    objUser->ctrlFreq_Hz;

    float32_t outMax_V = objUser->Vd_sf * objUser->maxVsMag_V;
    float32_t Kp = RoverL_Kp_sf * dcBus_nominal_V / maxCurrent_A;
    float32_t Ki = RoverL_min_rps * currentCtrlPeriod_sec;

    // set the Id controller
    PI_setGains(obj->piHandle_Id, Kp, Ki);
    PI_setUi(obj->piHandle_Id, 0.0f);
    PI_setRefValue(obj->piHandle_Id, 0.0f);
    PI_setFbackValue(obj->piHandle_Id, 0.0f);
    PI_setFfwdValue(obj->piHandle_Id, 0.0f);
    PI_setMinMax(obj->piHandle_Id, -outMax_V, outMax_V);

    // set the Iq controller
    PI_setGains(obj->piHandle_Iq, Kp, Ki);
    PI_setUi(obj->piHandle_Iq, 0.0f);
    PI_setRefValue(obj->piHandle_Iq, 0.0f);
    PI_setFbackValue(obj->piHandle_Iq, 0.0f);
    PI_setFfwdValue(obj->piHandle_Iq, 0.0f);
    PI_setMinMax(obj->piHandle_Iq, -outMax_V, outMax_V);

    return;
} // end of setupCurrentControllers() function

void setupControllers(MOTOR_Handle handle)
{
    MOTOR_Vars_t *obj = (MOTOR_Vars_t *)handle;
    USER_Params *objUser = (USER_Params *)(handle->userParamsHandle);

    float32_t Ls_d_H = objUser->motor_Ls_d_H;
    float32_t Ls_q_H = objUser->motor_Ls_q_H;

    float32_t Rs_Ohm = objUser->motor_Rs_Ohm;
    float32_t RdoverLd_rps = Rs_Ohm / Ls_d_H;
    float32_t RqoverLq_rps = Rs_Ohm / Ls_q_H;

    float32_t BWc_rps = objUser->BWc_rps;
    float32_t currentCtrlPeriod_sec =
                (float32_t)objUser->numCtrlTicksPerCurrentTick /
                objUser->ctrlFreq_Hz;

    float32_t outMax_V = objUser->Vd_sf *
            objUser->maxVsMag_V;

    float32_t Kp_Id = Ls_d_H * BWc_rps;
    float32_t Ki_Id = 0.25f * RdoverLd_rps * currentCtrlPeriod_sec;

    float32_t Kp_Iq = Ls_q_H * BWc_rps;
    float32_t Ki_Iq = 0.25f * RqoverLq_rps * currentCtrlPeriod_sec;

    // set the Id controller
    PI_setGains(obj->piHandle_Id, Kp_Id, Ki_Id);
    PI_setUi(obj->piHandle_Id, 0.0f);
    PI_setRefValue(obj->piHandle_Id, 0.0f);
    PI_setFbackValue(obj->piHandle_Id, 0.0f);
    PI_setFfwdValue(obj->piHandle_Id, 0.0f);
    PI_setMinMax(obj->piHandle_Id, -outMax_V, outMax_V);

    // set the Iq controller
    PI_setGains(obj->piHandle_Iq, Kp_Iq, Ki_Iq);

    PI_setUi(obj->piHandle_Iq, 0.0f);
    PI_setRefValue(obj->piHandle_Iq, 0.0f);
    PI_setFbackValue(obj->piHandle_Iq, 0.0f);
    PI_setFfwdValue(obj->piHandle_Iq, 0.0f);
    PI_setMinMax(obj->piHandle_Iq, 0.0f, 0.0f);

    // set the speed controller
    if(objUser->Kctrl_Wb_p_kgm2 <= 0.01f)
    {
        float32_t Kp_spd1 = 2.5f * objUser->maxCurrent_A / objUser->maxFrequency_Hz;
        float32_t Ki_spd1 = 5.0f * objUser->maxCurrent_A * objUser->ctrlPeriod_sec;

        PI_setGains(obj->piHandle_spd, Kp_spd1, Ki_spd1);
    }
    else
    {
        float32_t speedCtrlPeriod_sec =
            (float32_t)objUser->numCtrlTicksPerSpeedTick /
            objUser->ctrlFreq_Hz;

        float32_t BWdelta = objUser->BWdelta;

        float32_t Kctrl_Wb_p_kgm2 = objUser->Kctrl_Wb_p_kgm2;

        float32_t Kp_spd = BWc_rps / (BWdelta * Kctrl_Wb_p_kgm2);
        float32_t Ki_spd = BWc_rps * speedCtrlPeriod_sec / (BWdelta * BWdelta);

        PI_setGains(obj->piHandle_spd, Kp_spd, Ki_spd);
    }

    PI_setUi(obj->piHandle_spd, 0.0f);
    PI_setRefValue(obj->piHandle_spd, 0.0f);
    PI_setFbackValue(obj->piHandle_spd, 0.0f);
    PI_setFfwdValue(obj->piHandle_spd, 0.0f);
    PI_setMinMax(obj->piHandle_spd,
                 -objUser->maxCurrent_A,
                 objUser->maxCurrent_A);

             
    // copy the Id, Iq and speed controller parameters to motorVars
    getControllers(handle);


    return;
} // end of setupControllers() function



void runRsOnLine(MOTOR_Handle handle)
{
    MOTOR_Vars_t *obj = (MOTOR_Vars_t *)handle;
    MOTOR_SetVars_t *objSets = (MOTOR_SetVars_t *)(handle->motorSetsHandle);

    // execute Rs OnLine code
    if(obj->flagRunIdentAndOnLine == true)
    {
        if((EST_getState(obj->estHandle) == EST_STATE_ONLINE) &&
                (obj->flagStartRsOnLine == true) && (obj->controlStatus >= MOTOR_CTRL_RUN))
        {
            EST_setFlag_enableRsOnLine(obj->estHandle, true);

            EST_setRsOnLineId_mag_A(obj->estHandle, objSets->RsOnLineCurrent_A);

            float32_t RsError_Ohm = obj->RsOnLine_Ohm - obj->Rs_Ohm;

            if(fabsf(RsError_Ohm) < (objSets->Rs_Ohm * 0.15f))
            {
                EST_setFlag_updateRs(obj->estHandle, true);
            }
        }
        else
        {
            EST_setRsOnLineId_mag_A(obj->estHandle, 0.0f);
            EST_setRsOnLineId_A(obj->estHandle, 0.0f);
            EST_setRsOnLine_Ohm(obj->estHandle, EST_getRs_Ohm(obj->estHandle));

            EST_setFlag_enableRsOnLine(obj->estHandle, false);
            EST_setFlag_updateRs(obj->estHandle, false);
        }
    }

    return;
} // end of runRsOnLine() function


// update motor control variables
void updateGlobalVariables(MOTOR_Handle handle)
{
    MOTOR_Vars_t *obj = (MOTOR_Vars_t *)handle;

    MOTOR_SetVars_t *objSets = (MOTOR_SetVars_t *)(handle->motorSetsHandle);
    USER_Params *objUser = (USER_Params *)(handle->userParamsHandle);

    // get the states
    obj->estState = EST_getState(obj->estHandle);
    obj->trajState = EST_getTrajState(obj->estHandle);

    // get the stator resistance
    obj->Rs_Ohm = EST_getRs_Ohm(obj->estHandle);

    // get the stator inductance in the direct coordinate direction
    obj->Ls_d_H = EST_getLs_d_H(obj->estHandle);

    // get the stator inductance in the quadrature coordinate direction
    obj->Ls_q_H = EST_getLs_q_H(obj->estHandle);

    // get the flux, V/Hz
    if((objUser->flag_bypassMotorId == true) || (obj->estState >= EST_STATE_RAMPUP))
    {
        obj->flux_Wb   = EST_getFlux_Wb(obj->estHandle);
        obj->flux_VpHz = EST_getFlux_Wb(obj->estHandle) * MATH_TWO_PI;
    }

    if(obj->flagMotorIdentified == false)
    {
        objSets->Rs_Ohm = obj->Rs_Ohm;
        objSets->Ls_d_H = obj->Ls_d_H;
        objSets->Ls_q_H = obj->Ls_q_H;
        objSets->flux_VpHz = obj->flux_VpHz;
    }

    // get the rated magnetizing current value
    obj->magneticCurrent_A = EST_getIdRated_A(obj->estHandle);

    // get the stator resistance estimate from RsOnLine
    obj->RsOnLine_Ohm = EST_getRsOnLine_Ohm(obj->estHandle);

    // get R/L
    obj->RoverL_rps = EST_getRoverL_rps(obj->estHandle);

    // get the torque estimate
    obj->torque_Nm = EST_computeTorque_Nm(obj->estHandle);

    // Calculate the motor output power
    obj->powerMotor_W = EST_computePower_W(obj->estHandle);

    // obj->powerReal_W = obj->torque_Nm * obj->speedAbs_Hz * obj->power_sf;

    // Calculate the RMS stator current
    obj->Is_A = sqrtf(obj->Idq_in_A.value[0] * obj->Idq_in_A.value[0] +
                      obj->Idq_in_A.value[1] * obj->Idq_in_A.value[1]);

    // Calculate the RMS stator voltage
    obj->Vs_V = sqrtf(obj->Vdq_out_V.value[0] * obj->Vdq_out_V.value[0] +
                      obj->Vdq_out_V.value[1] * obj->Vdq_out_V.value[1]);
    
    // Add a filter to calculate the motor input power
    obj->powerActive_W = (obj->Vdq_out_V.value[0] * obj->Idq_in_A.value[0] +
                          obj->Vdq_out_V.value[1] * obj->Idq_in_A.value[1]) * 1.5f;

    return;
} // end of updateGlobalVariables() function

//! \brief     Sets the number of current sensors
//! \param[in] handle             The Clarke (CLARKE) handle
//! \param[in] numCurrentSensors  The number of current sensors
void setupClarke_I(CLARKE_Handle handle, const uint16_t numCurrentSensors)
{
    float32_t alpha_sf, beta_sf;

    // initialize the Clarke transform module for current
    if(3 == numCurrentSensors)
    {
        alpha_sf = MATH_ONE_OVER_THREE;
        beta_sf = MATH_ONE_OVER_SQRT_THREE;
    }
    else if(2 == numCurrentSensors)
    {
        alpha_sf = 1.0f;
        beta_sf = MATH_ONE_OVER_SQRT_THREE;
    }
    else
    {
        alpha_sf = 0.0f;
        beta_sf = 0.0f;
    }

    // set the parameters
    CLARKE_setScaleFactors(handle, alpha_sf, beta_sf);
    CLARKE_setNumSensors(handle, numCurrentSensors);

    return;
} // end of setupClarke_I() function

//! \brief     Sets the number of voltage sensors
//! \param[in] handle             The Clarke (CLARKE) handle
//! \param[in] numVoltageSensors  The number of voltage sensors
void setupClarke_V(CLARKE_Handle handle,const uint16_t numVoltageSensors)
{
    float32_t alpha_sf,beta_sf;

    // initialize the Clarke transform module for voltage
    if(numVoltageSensors == 3)
    {
        alpha_sf = MATH_ONE_OVER_THREE;
        beta_sf = MATH_ONE_OVER_SQRT_THREE;
    }
    else
    {
        alpha_sf = 0.0f;
        beta_sf = 0.0f;
    }

    // set the parameters
    CLARKE_setScaleFactors(handle, alpha_sf, beta_sf);
    CLARKE_setNumSensors(handle, numVoltageSensors);

    return;
} // end of setupClarke_V() function





//! \brief  Tune the gains of the controllers according to the speed or load
void tuneControllerGains(MOTOR_Handle handle)
{
    MOTOR_Vars_t *obj = (MOTOR_Vars_t *)handle;
    MOTOR_SetVars_t *objSets = (MOTOR_SetVars_t *)(handle->motorSetsHandle);
    float32_t Kp_spd_mid_sf, Ki_spd_mid_sf;

    if(obj->flagEnableTuneController == true)
    {
        if(obj->flagMotorIdentified == true)
        {
            if(obj->controlStatus == MOTOR_CTRL_RUN)
            {
                if(obj->speedAbs_Hz < objSets->Gain_speed_low_Hz)
                {
                    objSets->Kp_spd = objSets->Kp_spd_set * objSets->Kp_spd_low_sf;
                    objSets->Ki_spd = objSets->Ki_spd_set * objSets->Ki_spd_low_sf;
                }
                else if(obj->speedAbs_Hz > objSets->Gain_speed_high_Hz)
                {
                    objSets->Kp_spd = objSets->Kp_spd_set * objSets->Kp_spd_high_sf;
                    objSets->Ki_spd = objSets->Ki_spd_set * objSets->Ki_spd_high_sf;
                }
                else
                {
                    Kp_spd_mid_sf = objSets->Kp_spd_low_sf +
                            (obj->speedAbs_Hz - objSets->Gain_speed_low_Hz) * objSets->Kp_spd_slope_sf;
                    Ki_spd_mid_sf = objSets->Ki_spd_low_sf +
                            (obj->speedAbs_Hz - objSets->Gain_speed_low_Hz) * objSets->Ki_spd_slope_sf;

                    objSets->Kp_spd = objSets->Kp_spd_set * Kp_spd_mid_sf;
                    objSets->Ki_spd = objSets->Ki_spd_set * Ki_spd_mid_sf;
                }

                objSets->Kp_Iq = objSets->Kp_Iq_set * objSets->Kp_Iq_sf;
                objSets->Ki_Iq = objSets->Ki_Iq_set * objSets->Ki_Iq_sf;

                objSets->Kp_Id = objSets->Kp_Id_set * objSets->Kp_Id_sf;
                objSets->Ki_Id = objSets->Ki_Id_set * objSets->Ki_Id_sf;


            }
            else if(obj->controlStatus <= MOTOR_CL_RUNNING)
            {
                objSets->Kp_spd = objSets->Kp_spd_set * objSets->Kp_spd_start_sf;
                objSets->Ki_spd = objSets->Ki_spd_set * objSets->Ki_spd_start_sf;

                objSets->Kp_Id = objSets->Kp_Id_set * objSets->Kp_Id_sf;
                objSets->Ki_Id = objSets->Ki_Id_set * objSets->Ki_Id_sf;

                objSets->Kp_Iq = objSets->Kp_Iq_set * objSets->Kp_Iq_sf;
                objSets->Ki_Iq = objSets->Ki_Iq_set * objSets->Ki_Iq_sf;

            }
        }
    }

    return;
}

//! \brief  set the coefficient of the controllers gains
void setupControllerSF(MOTOR_Handle handle)
{
    MOTOR_SetVars_t *objSets = (MOTOR_SetVars_t *)(handle->motorSetsHandle);

    objSets->Gain_speed_low_Hz = USER_MOTOR1_GAIN_SPEED_LOW_Hz;
    objSets->Gain_speed_high_Hz = USER_MOTOR1_GAIN_SPEED_HIGH_Hz;

    objSets->Kp_spd_high_sf = USER_MOTOR1_KP_SPD_HIGH_SF;
    objSets->Ki_spd_high_sf = USER_MOTOR1_KI_SPD_HIGH_SF;

    objSets->Kp_spd_low_sf = USER_MOTOR1_KP_SPD_LOW_SF;
    objSets->Ki_spd_low_sf = USER_MOTOR1_KI_SPD_LOW_SF;

    objSets->Kp_Iq_sf = USER_MOTOR1_KP_IQ_SF;
    objSets->Ki_Iq_sf = USER_MOTOR1_KI_IQ_SF;

    objSets->Kp_Id_sf = USER_MOTOR1_KP_ID_SF;
    objSets->Ki_Id_sf = USER_MOTOR1_KI_ID_SF;

    objSets->Kp_spd_start_sf = USER_MOTOR1_KP_SPD_START_SF;
    objSets->Ki_spd_start_sf = USER_MOTOR1_KI_SPD_START_SF;


    objSets->Kp_spd_slope_sf = (USER_MOTOR1_KP_SPD_HIGH_SF - USER_MOTOR1_KP_SPD_LOW_SF) /
                                (USER_MOTOR1_GAIN_SPEED_HIGH_Hz - USER_MOTOR1_GAIN_SPEED_LOW_Hz);
    objSets->Ki_spd_slope_sf = (USER_MOTOR1_KI_SPD_HIGH_SF - USER_MOTOR1_KI_SPD_LOW_SF) /
                                (USER_MOTOR1_GAIN_SPEED_HIGH_Hz - USER_MOTOR1_GAIN_SPEED_LOW_Hz);
    return;
}   // End of setupControllerSF()

//! \brief  update the coefficient of the controllers gains
void updateControllerSF(MOTOR_Handle handle)
{
    MOTOR_SetVars_t *objSets = (MOTOR_SetVars_t *)(handle->motorSetsHandle);

    objSets->Kp_spd_slope_sf = (objSets->Kp_spd_high_sf - objSets->Kp_spd_low_sf) /
                                (objSets->Gain_speed_high_Hz - objSets->Gain_speed_low_Hz);
    objSets->Ki_spd_slope_sf = (objSets->Ki_spd_high_sf - objSets->Ki_spd_low_sf) /
                                (objSets->Gain_speed_high_Hz - objSets->Gain_speed_low_Hz);
    return;
}   // End of updateControllerSF()


//! \brief  update the coefficient of the controllers gains
void updateFASTParameters(MOTOR_Handle handle)
{
    MOTOR_Vars_t *obj = (MOTOR_Vars_t *)handle;
    MOTOR_SetVars_t *objSets = (MOTOR_SetVars_t *)(handle->motorSetsHandle);

    obj->angleESTDelayed_sf = objSets->angleESTDelayed_sf * objSets->ctrlPeriod_sec;

    if(motorVars_M1.controlStatus == MOTOR_STOP_IDLE)
    {
        // set the scale factor for high frequency low inductance motor
        EST_setOneOverFluxGain_sf(obj->estHandle,
                                  obj->userParamsHandle, objSets->fluxFilterCoef);

        EST_setFreqLFP_sf(obj->estHandle,
                          obj->userParamsHandle, objSets->speedFilterCoef);

        EST_setBemf_sf(obj->estHandle,
                       obj->userParamsHandle, objSets->bemfFilterCoef);
    }

    return;
}

//
//-- end of this file ----------------------------------------------------------
//
