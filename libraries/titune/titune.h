/*
 *  Copyright (C) 2025 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
//*****************************************************************************
/*
 *  Created on: Feb 6, 2026
 *  Author: a0508081
 */
//*****************************************************************************

#ifndef LIBRARIES_TITUNE_H_
#define LIBRARIES_TITUNE_H_

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

#include "pi.h"
#include "park.h"
#include "ipark.h"
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "userParams.h"
#include "user_mtr1.h"
#include "libraries/math/include/math.h"
#include "libraries/utilities/types/include/types.h"

#if defined(MOTOR1_TI_TUNE)
// **************************************************************************
//// the defines
// **************************************************************************
// Timer can be handled in background loop or ISR
#define TI_TUNE_STATE_DELAY_COUNT       1000U

// maximum board voltage based on max measurable ADC voltage after scaling down.
#define TI_TUNE_USER_M1_ADC_FULL_SCALE_VOLTAGE_V            USER_M1_ADC_FULL_SCALE_VOLTAGE_V

// the rated voltage of the motor, V
#define TITUNE_USER_MOTOR1_RATED_VOLTAGE_PH_V               USER_MOTOR1_RATED_VOLTAGE_V

// Max Rate Phase current of the Motor
#define TI_TUNE_USER_MOTOR1_MAX_CURRENT_A                   USER_MOTOR1_MAX_CURRENT_A

// Rated Electrical Speed of the Motor in Hertz
#define TI_TUNE_ELECTRICAL_FREQ_BASE_HZ                     (100)

// PWM Frequency /ISR execution to Current loop execution rate
#define TI_TUNE_USER_M1_NUM_ISR_TICKS_PER_TORQUE_TICK        (1)

// PWM Frequency/ ISR execution to speed loop execution rate
#define TI_TUNE_USER_M1_NUM_ISR_TICKS_PER_SPEED_TICK        (10)

// Pulse Width Modulation (PWM) period, usec , (1 / PWM_Frequency)
#define TI_TUNE_USER_M1_PWM_PERIOD_sec                      USER_M1_PWM_PERIOD_sec

#define TI_TUNE_USER_M1_TORQUE_LOOP_PERIOD_sec              (TI_TUNE_USER_M1_PWM_PERIOD_sec * TI_TUNE_USER_M1_NUM_ISR_TICKS_PER_TORQUE_TICK)

#define TI_TUNE_SPEED_CUT_OFF_FREQ                          (10)

#define TI_TUNE_TORQUE_LOOP_CUT_OFF_FREQ                    (MATH_TWO_PI * 10.0f)

// Maximum Phase voltage Peak possible for SVPWM output
#define TI_TUNE_USER_M1_MAX_VS_MAG_PU                       (0.576f)

// Pole Pairs of Motor - Not mandatory
#define TI_TUNE_USER_MOTOR1_POLE_PAIRS                      USER_MOTOR1_NUM_POLE_PAIRS

// Timer can be handled in background loop or ISR
#define TI_TUNE_STATE_DELAY_COUNT       1000U
#define d_axis                          1
#define q_axis                          2

#define Ind_Mtr                         1
#define IPMSM_Mtr                       2
#define SYNRM_Mtr                       3

// Parameter: Number. Inductance LUT size.
#define LDQ_TEST_NUMBER (4)

//*****************************************************************************
//! \brief Enumeration for the TiTune state machine
//*****************************************************************************
typedef enum {
    TiTune_STATE_IDLE,            //!< idle state

    TiTune_STATE_LDQ_SETUP,       //!< LDQ set-up state
    TiTune_STATE_LDQ_EST,         //!< estimation of d�axis and q�axis inductance state, Ld/Lq
    TiTune_STATE_LDQ_DONE,        //!< LDQ done state

    TiTune_STATE_RS_SETUP,        //!< Rs set-up state
    TiTune_STATE_RS_EST,          //!< estimation of stator resistance state, Rs
    TiTune_STATE_RS_DONE,         //!< Rs done state

    TiTune_STATE_SAT_LDQ_SETUP,   //!< Saturated LDQ set-up state
    TiTune_STATE_SAT_LDQ_EST,     //!< estimation of saturated d�axis and q�axis inductance state, Ld/Lq
    TiTune_STATE_SAT_LDQ_DONE,    //!< Saturated LDQ done state

    TiTune_STATE_INERTIA_SETUP,   //!< motor inertia set-up state
    TiTune_STATE_INERTIA_EST,     //!< estimation of motor inertia state, J
    TiTune_STATE_INERTIA_DONE,    //!< motor inertia done state

    TiTune_STATE_FLUX_SETUP,      //!< motor flux linkage set-up state
    TiTune_STATE_FLUX_EST,        //!< estimation of motor flux linkage state
    TiTune_STATE_FLUX_DONE,       //!< motor flux linkage done state

    TiTune_STATE_OBSERVER_SETUP,  //!< Update the Observer Parameters

    TiTune_STATE_DONE,            //!< done state

    TiTune_NUMSTATES              //!< Number of TiTune routine states
} TiTune_State_e;


//*****************************************************************************
//! brief Defines the TiTune object
//*****************************************************************************
typedef struct _TiTune_LDQ_Obj_
{
    bool VariableInit;
    float32_t VoltageFound;
    float32_t VoltageNotFound;
    float32_t VolMinAssigned;
    float32_t VolMaxAssigned;
    float32_t ExecuteEnable;
    float32_t InjVolHalfPrdSampleNo;
    float32_t InjSampleCounter;
    float32_t InjPrdCounter;
    float32_t FirstLdqEstCheck;
    float32_t FirstVolMaxLimHitCheck;
    float32_t FirstFreqMinLimHitCheck;
    float32_t InjVolAngleStep;
    float32_t InjVolMagn;
    float32_t InjVolFreq;
    float32_t InjVolAngle;
    float32_t InjVolAngle_ZOHComp;
    float32_t ElecThetaUnsat;
    float32_t MinSearchVol;
    float32_t MaxSearchVol;
    float32_t InputGainDFT;
    float32_t CosDFT;
    float32_t SinDFT;
    float32_t VdRealDFT;
    float32_t VdImagDFT;
    float32_t IdRealDFT;
    float32_t IdImagDFT;
    float32_t IqRealDFT;
    float32_t IqImagDFT;
    float32_t VdMagnDFT;
    float32_t IdMagnDFT;
    float32_t IqMagnDFT;
    float32_t IsMagn;
    float32_t Lpu;
    float32_t VdPhaseDFT;
    float32_t IdPhaseDFT;

    float32_t InjVolHalfPrdSampleNoMax;
    float32_t InjVolHalfPrdSampleNoInit;
    float32_t InjSettlePrd;
    float32_t AngIntgGain;
    float32_t ElecThetaStep;
    float32_t InjVolMagnInit;
    float32_t IsMagnMinLim;
    float32_t IsMagnMaxLim;
    float32_t InjVolMagnMaxLim;
    float32_t Vdc_Base;
    float32_t Vph_Base;
    float32_t I_Base;
    float32_t F_Base;

    float32_t Udc;
    float32_t IdFbk;
    float32_t IqFbk;

    float32_t InjVol;
    float32_t ElecTheta;
    float32_t LminApprox;
    float32_t LmaxApprox;
    float32_t InitialRotorAngle;
    float32_t Finish;

    float32_t X_base;
    float32_t flux_base;
    float32_t Lam_PM;
    float32_t inductance_base;

    float32_t ld_Final;
    float32_t lq_Final;
} TiTune_LDQ_Obj;

//***************************************************************************************************************************************************************************
//Defines the TiTune_Rs object
//***************************************************************************************************************************************************************************

typedef struct _TiTune_Rs_Obj_
{
    bool VariableInit;
    float32_t AveragerEnable;
    float32_t TimeOutError;
    float32_t Mode;
    float32_t Div2Counter;
    float32_t CtrlCycleCounter;
    float32_t AveragerInputGain;
    float32_t IdFbk_Average;
    float32_t VdRef_Average;
    float32_t IdFbkAve_Mode1;
    float32_t VdRefAve_Mode1;
    float32_t IdErrFiltered;

    uint32_t  AveragingSize;
    float32_t Wait4SettleCurrent;
    float32_t MaxTime4Settle;
    float32_t TestCurrent1;
    float32_t TestCurrent2;
    float32_t IdErrLim4Settle;
    float32_t LPF_IdErr_Gain;
    float32_t Vdc_Base;
    float32_t Vph_Base;
    float32_t I_Base;
    float32_t F_Base;
    int32_t i12;

    float32_t IdFbk;
    float32_t VdRef;
    float32_t VdistGain;
    float32_t VdistGain1;

    float32_t IdRef;
    float32_t Rs;
    float32_t Vdist;
    float32_t Finish;

    float32_t X_base;
    float32_t Rs_Final;
    float32_t impedance_base;
} TiTune_Rs_Obj;

/*************************************************************************************************************************************************************************************/
// Defines the TiTune_SatLDQ object
/*************************************************************************************************************************************************************************************/
typedef struct _TiTune_SatLDQ_Obj_
{
    bool VariableInit;
    float32_t ExecuteEnable;
    float32_t InjSineEnable;
    int16_t CurrentSign;
    uint16_t Axis;
    uint16_t OpPtNo;
    uint16_t EstStep;
    uint32_t CtrlCycleCounter;
    uint32_t InjSampleCounter;
    uint32_t InjSinePrdCounter;
    uint32_t InjCurHalfPrdSampleNo;
    uint32_t dcCurHalfPrdSampleNo;

    float32_t InjCurAngle;
    float32_t InjCurAngleStep;
    float32_t InputGainDFT;
    float32_t InjCurFreq;
    float32_t VmagnDFT;
    float32_t VphaseDFT;
    float32_t ImagnDFT;
    float32_t IphaseDFT;
    float32_t CosDFT;
    float32_t SinDFT;
    float32_t VrealDFT;
    float32_t VimagDFT;
    float32_t IrealDFT;
    float32_t IimagDFT;
    float32_t Lest;

    uint16_t MotorType;
    uint32_t Nbase;
    uint32_t InjSettleWait_PrdNo;
    uint32_t dcSettleWait_SampleNo;
    float32_t InjCurFreqInit;
    float32_t InjCurMagn;
    float32_t IrefDCStep;

    float32_t Ifbk;
    float32_t Vref;

    float32_t Finish;
    float32_t Iref;
    float32_t Lsigma [LDQ_TEST_NUMBER+1];
    float32_t Ld [2 * LDQ_TEST_NUMBER+1];
    float32_t Lq [2 * LDQ_TEST_NUMBER+1];

    float32_t Ld_Final [2 * LDQ_TEST_NUMBER+1];
    float32_t Lq_Final [2 * LDQ_TEST_NUMBER+1];

    float32_t Vdc_Base;
    float32_t Vph_Base;
    float32_t I_Base;
    float32_t F_Base;

    float32_t X_base;
    float32_t flux_base;
    float32_t Lam_PM;
    float32_t inductance_base;

} TiTune_SatLDQ_Obj;

/*************************************************************************************************************************************************************************************/
// Defines the TiTune_Flux object
/*************************************************************************************************************************************************************************************/
typedef struct _TiTune_Flux_Obj_
{
    bool VariableInit;
    float32_t TimeOutError;
    float32_t SpeedRampArrives;
    float32_t MagnFluxEstEn;
    float32_t SlowDownEn;
    float32_t CtrlCycleCounter;
    float32_t AveragerInputGain;
    float32_t SpeedErrFiltered;
    float32_t IqFbkDerivative;
    float32_t IqFbkPast;
    float32_t SpeedFbk_Average;
    float32_t BackEMF_Average;

    uint32_t AveragingSize;
    float32_t WaitingTime2Settle_Speed;
    float32_t MaxTime4Settle;
    float32_t TestSpeed;
    float32_t SpeedErrLim4Settle;
    float32_t Rs;
    float32_t Lq;
    float32_t TimePU;
    float32_t LPF_IqDeriv_Gain;
    float32_t LPF_SpeedErr_Gain;

    float32_t SpeedFbk;
    float32_t IqFbk;
    float32_t VqRef;

    float32_t SpeedRef;
    float32_t MagnFlux;
    float32_t Finish;

    float32_t Vph_Base;
    float32_t I_Base;
    float32_t F_Base;

    float32_t BASE_FREQ;

    float32_t X_base;
    float32_t flux_base;
    float32_t Flux_Final;

} TiTune_Flux_Obj;

//*****************************************************************************
//
//! brief Defines the PI controller object
//
//*****************************************************************************
typedef struct _TiTune_J_Obj_
{
    bool VariableInit;
    uint16_t ResetRiseFallCounters;
    uint16_t TorqueFound;
    uint16_t TorqueNotFoundError;
    uint16_t IqMinAssigned;
    uint16_t IqMaxAssigned;
    uint16_t EnableCheckingHighTorque;
    uint16_t Prepare4Est;
    uint16_t EstimationEn;
    int16_t  TorqueSign;
    uint16_t MaxIqHitCounter;
    uint16_t MaxSpdHitCounter;
    uint16_t MaxSpdHitCounter_Resettable;
    uint32_t SampleCounterDFT;
    uint32_t SampleSizeDFT;
    uint16_t FinishedTestPeriodCounter;
    uint16_t DownSampleCounter;
    uint16_t DownSampleRatio;
    uint32_t SpdRiseCounter;
    uint32_t SpdFallCounter;
    uint32_t RiseTime4Est;
    uint32_t FallTime4Est;

    float32_t MinSearchIq;
    float32_t MaxSearchIq;
    float32_t InjSpeedFreq;
    float32_t AngleDFT;
    float32_t AngleStepDFT;
    float32_t InputGainDFT;
    float32_t SpdMagnDFT;
    float32_t SpdPhaseDFT;
    float32_t IqMagnDFT;
    float32_t IqPhaseDFT;
    float32_t CosDFT;
    float32_t SinDFT;
    float32_t SpdRealDFT;
    float32_t SpdImagDFT;
    float32_t IqRealDFT;
    float32_t IqImagDFT;

    uint32_t RiseTimeMin;
    uint32_t RiseTimeMax;
    uint32_t SettlePeriod;
    uint32_t MaxSampleSizeDFT;
    float32_t Nbase;
    float32_t SpdMinLim;
    float32_t SpdMaxLim;
    float32_t IqMaxLim;
    float32_t IqInit;

    float32_t SpdFbk;
    float32_t IqFbk;

    float32_t IqRef;
    float32_t InertiaOverFlux;
    uint16_t Finish;

    float32_t Vdc_Base;
    float32_t Vph_Base;
    float32_t I_Base;
    float32_t F_Base;

    float32_t X_base;
    float32_t flux_base;
    float32_t J_eq_base;
    float32_t J_base;
    float32_t Lam_PM;
    float32_t P_Base;
    float32_t Inertia_Final;
    float32_t Tau_Base;
    float32_t friction_base;
    float32_t inductance_base;
    float32_t inertia_base;
    float32_t power_base;
    float32_t torque_base;
} TiTune_J_Obj;

//***************************************************************************************************************************************************************************
//      Defines the TiTune_LDQ handle
//***************************************************************************************************************************************************************************

typedef struct _TiTune_LDQ_Obj_ *TiTune_LDQ_Handle;

//***************************************************************************************************************************************************************************
//      Defines the TiTune_Rs handle
//***************************************************************************************************************************************************************************

typedef struct _TiTune_Rs_Obj_ *TiTune_Rs_Handle;

/*****************************************************************************/
//  Defines the TiTune_SatLDQ handle
/*****************************************************************************/

typedef struct _TiTune_SatLDQ_Obj_ *TiTune_SatLDQ_Handle;

/*****************************************************************************/
//  Defines the TiTune_Flux handle
/*****************************************************************************/

typedef struct _TiTune_Flux_Obj_ *TiTune_Flux_Handle;

//*****************************************************************************
//
//! brief Defines the Inertia handle
//
//*****************************************************************************
typedef struct _TiTune_J_Obj_ *TiTune_J_Handle;

//*****************************************************************************
//
//! brief Defines the TiTune object
//
//*****************************************************************************
typedef struct _TiTune_Obj_
{
    bool TiTune_enable;

    // the handle for the speed PI controller
    PI_Obj        TiTune_PI_Speed;

    // the handle for the Id PI controller
    PI_Obj     TiTune_PI_Id;

    // the handle for the Iq PI controller
    PI_Obj     TiTune_PI_Iq;

    // the reference current on d&q rotation axis
    MATH_Vec2 IdqRef_A;

    // the reference output current on d&q rotation axis
    MATH_Vec2 Idq_out_A;

    /* Library Parameters */
    volatile TiTune_State_e TiTune_state;

    uint32_t TiTune_count;

    TiTune_LDQ_Obj TiTune_LDQ;
    TiTune_LDQ_Handle TiTune_LDQ_handler;

    TiTune_J_Obj TiTune_J;
    TiTune_J_Handle TiTune_J_handler;

    TiTune_Rs_Obj TiTune_Rs;
    TiTune_Rs_Handle TiTune_Rs_handler;

    TiTune_SatLDQ_Obj TiTune_SatLDQ;
    TiTune_SatLDQ_Handle TiTune_SatLDQ_handler;

    TiTune_Flux_Obj TiTune_Flux;
    TiTune_Flux_Handle TiTune_Flux_handler;

    /* Inputs of TI_Tune_Methods */
    float32_t VdcBus_V;                     // Supplied DC Bus voltage

    float32_t TiTune_FOC_Angle_in_rad;      // Angle to be fed from the Estimated position of the rotor.

    float32_t TiTune_Speed_in_Hz;           // The Input Estimated Speed to Ti Tune Block

    MATH_Vec2 TiTune_Iab_in_A;              // the Alpha Beta Currents from Clarke are referenced with this pointer

    /* Outputs of TI_TUNE method */
    MATH_Vec2 Ti_Tune_Out_Vab_V;            // the output control voltage on Alpha beta Voltages

    /* Working variables of TI_TUNE method */
    MATH_Vec2 Ti_Tune_phasor;               // output phasor cos and sine angles

    float32_t TiTune_Rs_IPD_Angle;          // Angle to be fed from the Initial position of the rotor.

    MATH_Vec2 Ti_Tune_Out_Vdq_V;            // the output control voltage on d&q axis - need Global access for Ls

    MATH_Vec2  TiTune_Idq_in_A;             // the D & Q axis current are converter from 3-phase sampling input current of motor

} TiTune_Obj;

//*****************************************************************************
//
//! brief Defines the TiTune handle
//
//*****************************************************************************
typedef struct _TiTune_Obj_ *TiTune_Handle;

//*****************************************************************************
//
//! brief Object declarations
//
//*****************************************************************************
extern TiTune_Obj    TiTune_M1;

extern TiTune_Handle TiTune_handler;

//*****************************************************************************

//*****************************************************************************
// the function prototypes

//*****************************************************************************
//
//! brief     Initializes the TiTune
//!
//! param[in] pMemory   A pointer to the memory for the TiTune object
//!
//! param[in] numBytes  The number of bytes allocated for the TiTune
//!
//! return    The TiTune object handle
//
//*****************************************************************************
extern TiTune_Handle TiTune_init(void *pMemory, const size_t numBytes);

//*****************************************************************************
//
//! \brief     Sets the TiTune parameters
//!
//! \param[in] handle        The TiTune handle
//!
//*****************************************************************************
extern void TiTune_setParams(TiTune_Handle handle);

//*****************************************************************************
//
//! \brief     State machine handler function for TI Tune Routines
//!
//! \param[in] handle        The TiTune handle
//!
//*****************************************************************************
extern void TiTune_Run_stateMachine(TiTune_Handle handle);

//*****************************************************************************
//
//! \brief     Current Controller functions for TI Tune Routines
//!
//! \param[in] handle        The TiTune handle
//!
//*****************************************************************************
extern void TiTune_Run_Current_Control(TiTune_Handle handle);

//*****************************************************************************
//
//! \brief     Speed Controller functions for TI Tune Routines
//!
//! \param[in] handle        The TiTune handle
//!
//*****************************************************************************
extern void TiTune_Run_Speed_Control(TiTune_Handle handle);

//*****************************************************************************
//
//! \brief     Initialization, parameter setting and run functions for Saturated inductances
//
//*****************************************************************************
extern TiTune_SatLDQ_Handle TiTune_SatLDQ_init(void *pMemory, const size_t numBytes);

extern void TiTune_SatLDQ_setParams(TiTune_SatLDQ_Handle handle);

//*****************************************************************************
//
//! \brief     Initialization, parameter setting and run functions for inductances
//
//*****************************************************************************
extern TiTune_LDQ_Handle TiTune_LDQ_init(void *pMemory, const size_t numBytes);

extern void TiTune_LDQ_setParams(TiTune_LDQ_Handle handle);

extern void TiTune_LDQ_run(TiTune_LDQ_Handle handle,
                              const float32_t vdc_ref,
                              const float32_t id_fb,
                              const float32_t iq_fb);

//*****************************************************************************
//
//! \brief     Initialization, parameter setting and run functions for resistance estimation
//
//*****************************************************************************
extern TiTune_Rs_Handle TiTune_Rs_init(void *pMemory, const size_t numBytes);

extern void TiTune_Rs_setParams(TiTune_Rs_Handle handle);

extern void TiTune_Rs_run(TiTune_Rs_Handle handle,
                          const float32_t v_dist_gain,
                          const float32_t id_fb,
                          const float32_t vd_fb);

//*****************************************************************************
//
//! \brief     Initialization, parameter setting and run functions for flux estimation
//
//*****************************************************************************
extern TiTune_Flux_Handle TiTune_Flux_init(void *pMemory, const size_t numBytes);

extern void TiTune_Flux_setParams(TiTune_Flux_Handle flux_handle);

extern void TiTune_Flux_run(TiTune_Flux_Handle handle,
                            const float32_t MechSpeed,
                            const float32_t iq_fb,
                            const float32_t Vq_fb);

//*****************************************************************************
//
//! \brief     Initialization, parameter setting and run functions for Inertia estimation
//
//*****************************************************************************
extern TiTune_J_Handle TiTune_J_init(void *pMemory, const size_t numBytes);

extern void TiTune_J_setParams(TiTune_J_Handle handle);

extern void TiTune_J_run(TiTune_J_Handle handle,
                                const float32_t Speed_fb,
                                const float32_t iq_fb);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // MOTOR1_TI_TUNE

#endif // LIBRARIES_TITUNE_H_

//
//-- end of this file ----------------------------------------------------------
//
