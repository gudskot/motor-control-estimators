/*
*
* Created by Dmytro Khymytsia
* 09.11.2026
*
* Luenberger back-EMF observer + PLL (SPM motor, Ld = Lq)
* The FOC angle is atan2 of the estimated back-EMF (thetaRaw_rad), the PLL gives the speed
* (also used inside the rotating EMF model). The PLL angle is kept for logging
*
*/

#ifndef _LUEN_H_
#define _LUEN_H_

#include <stddef.h>

#ifdef __TMS320C28XX_CLA__
#include "libraries/math/src/float/CLAmath.h"
#else
#include <math.h>
#endif

#include "libraries/math/include/math.h"

#include "userParams.h"

// **************************************************************************
// the typedefs

//! \brief Defines the LUEN observer object
//!
typedef struct _LUEN_Obj_
{
    float32_t scaleFreq_Hz;   // base frequency, Hz
    float32_t speed_sf;       // speed PU scale factor
    float32_t voltage_sf;     // voltage PU scale factor
    float32_t current_sf;     // current PU scale factor

    float32_t Ts;             // sampling period, s
    float32_t base_wTs;       // BASE_FREQ * Ts

    // discretised R-L plant: i[k+1] = Fplant * i[k] + Gplant * (v - e)
    float32_t Fplant;
    float32_t Gplant;

    // observer gains (per step, PU), computed in LUEN_setBandwidth
    // K1 = Ts * l1,  K2 = Ts * l2 * Ibase / Vbase,  K2 must be negative
    float32_t K1;             // current correction
    float32_t K2;             // EMF correction

    float32_t Valpha;         // reconstructed stationary phase voltage (pu)
    float32_t Vbeta;

    float32_t EstIalpha;      // estimated stator current
    float32_t EstIbeta;
    float32_t IalphaError;    // measured - estimated, kept for logging
    float32_t IbetaError;

    float32_t Ealpha;         // estimated back-EMF
    float32_t Ebeta;
    float32_t Ed;
    float32_t Eq;
    float32_t Eq_mag;

    float32_t thetaErr;
    float32_t thetaErrSF;     // 1/(2*pi)
    float32_t theta;          // PLL angle, pu of a turn
    float32_t thetaDelta;     // angle increment factor, set in setParams
    float32_t thetaEst;       // PLL angle, rad, [-pi, pi]
    float32_t thetaRaw_rad;   // rotor angle from atan2 of the back-EMF, rad, [-pi, pi], used by the FOC

    float32_t speedEst;
    float32_t speedFlt;

    float32_t pll_Out;
    float32_t pll_Umax;
    float32_t pll_Umin;
    float32_t pll_ui;
    float32_t pll_Kp;
    float32_t pll_KpMax;      // PLL Kp schedule: Kp = KpMin + KpSF * |speedRef|
    float32_t pll_KpMin;
    float32_t pll_KpSF;
    float32_t pll_Ki;

    float32_t speedRef;       // reference speed (pu), used only by the Kp schedule

    float32_t lpf_b0;
    float32_t lpf_a1;
    float32_t lpfFc_Hz;
} LUEN_Obj;

//! \brief Defines the LUEN handle
//!
typedef struct _LUEN_Obj_ *LUEN_Handle;

// **************************************************************************
// the function prototypes

//! \brief     Initializes the LUEN observer
//! \param[in] pMemory   A pointer to the memory for the LUEN object
//! \param[in] numBytes  The number of bytes allocated for the LUEN object
//! \return    The LUEN handle
extern LUEN_Handle LUEN_init(void *pMemory, const size_t numBytes);

//! \brief     Resets all parameters and states to defaults
extern void LUEN_resetParams(LUEN_Handle handle);

//! \brief     Computes scale factors and the plant model from user parameters
extern void LUEN_setParams(LUEN_Handle handle, const USER_Params *pUserParams);

//! \brief     Computes K1, K2 from the observer bandwidth and damping
//! \param[in] omega_o   Observer bandwidth, rad/s (clamped to 0.3 / Ts)
//! \param[in] zeta      Damping, 0.7 is a usual start
extern void LUEN_setBandwidth(LUEN_Handle handle, const USER_Params *pUserParams,
                              const float32_t omega_o, const float32_t zeta);

//! \brief     Sets the PLL Kp schedule
extern void LUEN_setPLLParams(LUEN_Handle handle, const float32_t pll_KpMax,
                              const float32_t pll_KpMin, const float32_t pll_KpSF);

//! \brief     Updates pll_Kp from speedRef
extern void LUEN_updatePLLParams(LUEN_Handle handle);

//! \brief     Sets the speed filter cut-off and recalculates its coefficients
extern void LUEN_setSpeedFilterFreq(LUEN_Handle handle, const float32_t lpfFc_Hz);

//! \brief     Recalculates the speed filter coefficients from lpfFc_Hz
extern void LUEN_updateFilterParams(LUEN_Handle handle);

//! \brief     Sets the observer gains directly (per step, PU)
static inline void LUEN_setGains(LUEN_Handle handle, const float32_t K1, const float32_t K2)
{
    LUEN_Obj *obj = (LUEN_Obj *)handle;

    obj->K1 = K1;
    obj->K2 = K2;

    return;
}

static inline void LUEN_setPLLKp(LUEN_Handle handle, const float32_t pll_Kp)
{
    LUEN_Obj *obj = (LUEN_Obj *)handle;

    obj->pll_Kp = pll_Kp;

    return;
}

static inline void LUEN_setPLLKi(LUEN_Handle handle, const float32_t pll_Ki)
{
    LUEN_Obj *obj = (LUEN_Obj *)handle;

    obj->pll_Ki = pll_Ki;

    return;
}

static inline void LUEN_setSpeedRef(LUEN_Handle handle, const float32_t speedRef_Hz)
{
    LUEN_Obj *obj = (LUEN_Obj *)handle;

    obj->speedRef = speedRef_Hz * obj->speed_sf;

    return;
}

//! \brief     Zeroes the observer states
static inline void LUEN_resetStates(LUEN_Handle handle)
{
    LUEN_Obj *obj = (LUEN_Obj *)handle;

    obj->EstIalpha = 0.0f;
    obj->EstIbeta  = 0.0f;
    obj->Ealpha    = 0.0f;
    obj->Ebeta     = 0.0f;
    obj->pll_ui    = 0.0f;

    return;
}

//! \brief     Sets the PLL angle (rad), used for the handover from the forced angle
static inline void LUEN_setAnglePu(LUEN_Handle handle, const float32_t theta_rad)
{
    LUEN_Obj *obj = (LUEN_Obj *)handle;

    obj->theta = theta_rad * MATH_ONE_OVER_TWO_PI;

    return;
}

//! \brief     Sets the PLL speed (Hz), used for the handover from the forced angle
static inline void LUEN_setPLLSpeedPu(LUEN_Handle handle, const float32_t speed_Hz)
{
    LUEN_Obj *obj = (LUEN_Obj *)handle;

    // the PI integrator is seeded too, otherwise the speed collapses on the first step
    obj->speedFlt = speed_Hz * obj->speed_sf;
    obj->speedEst = speed_Hz * obj->speed_sf;
    obj->pll_Out  = speed_Hz * obj->speed_sf;
    obj->pll_ui   = speed_Hz * obj->speed_sf;

    return;
}

static inline float32_t LUEN_getSpeed_Hz(LUEN_Handle handle)
{
    LUEN_Obj *obj = (LUEN_Obj *)handle;

    return(obj->speedEst * obj->scaleFreq_Hz);
}

static inline float32_t LUEN_getSpeedPLL_Hz(LUEN_Handle handle)
{
    LUEN_Obj *obj = (LUEN_Obj *)handle;

    return(obj->speedFlt * obj->scaleFreq_Hz);
}

static inline float32_t LUEN_getAnglePLL(LUEN_Handle handle)
{
    LUEN_Obj *obj = (LUEN_Obj *)handle;

    return(obj->thetaEst);
}

//! \brief     Rotor angle from atan2 of the estimated back-EMF, rad, no PLL in the path
static inline float32_t LUEN_getAngleRaw(LUEN_Handle handle)
{
    LUEN_Obj *obj = (LUEN_Obj *)handle;

    return(obj->thetaRaw_rad);
}

//! \brief     Runs the LUEN observer
//! \param[in] Vdcbus      The dc bus voltage
//! \param[in] pVabc_pu    The pointer to the modulation functions (PU)
//! \param[in] pIabVec     The pointer to the measured phase currents
static inline void LUEN_run(LUEN_Handle handle,
                      float32_t Vdcbus, MATH_vec3 *pVabc_pu, MATH_vec2 *pIabVec)
{
    LUEN_Obj *obj = (LUEN_Obj *)handle;

    // Phase voltages are reconstructed from the modulation functions, not measured
    float32_t Vtemp   = Vdcbus * obj->voltage_sf;

    float32_t VphaseA = Vtemp *
            (pVabc_pu->value[0] * 2.0f - pVabc_pu->value[1] - pVabc_pu->value[2]);

    float32_t VphaseB = Vtemp *
            (pVabc_pu->value[1] * 2.0f - pVabc_pu->value[0] - pVabc_pu->value[2]);

    obj->Valpha = VphaseA;
    obj->Vbeta  = (VphaseA + VphaseB * 2.0f) * MATH_ONE_OVER_SQRT_THREE;

    // Current error, measured minus estimated
    obj->IalphaError = pIabVec->value[0] * obj->current_sf - obj->EstIalpha;
    obj->IbetaError  = pIabVec->value[1] * obj->current_sf - obj->EstIbeta;

    // EMF vector rotates by w*Ts per step: de/dt = w * [-e_beta, e_alpha]
    float32_t wTs = MATH_TWO_PI * obj->speedFlt * obj->base_wTs;

    float32_t Ea = obj->Ealpha;
    float32_t Eb = obj->Ebeta;

    // Both updates use the old EMF (explicit Euler)
    obj->EstIalpha = obj->Fplant * obj->EstIalpha + obj->Gplant * (obj->Valpha - Ea)
                   + obj->K1 * obj->IalphaError;
    obj->EstIbeta  = obj->Fplant * obj->EstIbeta  + obj->Gplant * (obj->Vbeta  - Eb)
                   + obj->K1 * obj->IbetaError;

    obj->Ealpha = Ea - wTs * Eb + obj->K2 * obj->IalphaError;
    obj->Ebeta  = Eb + wTs * Ea + obj->K2 * obj->IbetaError;

    // e = w*psi*[-sin(theta), cos(theta)]: the EMF leads the rotor flux by 90 deg and changes
    // sign with the rotation direction, the direction is taken from the PLL speed
    if(obj->speedFlt >= 0.0f)
    {
        obj->thetaRaw_rad = __atan2(-obj->Ealpha, obj->Ebeta);
    }
    else
    {
        obj->thetaRaw_rad = __atan2(obj->Ealpha, -obj->Ebeta);
    }

    float32_t pllSine   = __sinpuf32(obj->theta);
    float32_t pllCosine = __cospuf32(obj->theta);

    obj->Ed     = obj->Ealpha * pllCosine + obj->Ebeta  * pllSine;
    obj->Eq     = obj->Ebeta  * pllCosine - obj->Ealpha * pllSine;
    obj->Eq_mag = sqrtf(obj->Ealpha * obj->Ealpha + obj->Ebeta * obj->Ebeta);

    // The sign follows the rotation direction
    float32_t thetaErrSF = obj->thetaErrSF;

    if(obj->Eq >= 0.0f)
    {
        thetaErrSF = -obj->thetaErrSF;
    }

    obj->thetaErr = obj->Ed * thetaErrSF / (obj->Eq_mag + 1.0e-9f);

    obj->pll_ui  = (obj->pll_Ki * obj->thetaErr) + obj->pll_ui;
    obj->pll_Out = __fsat((obj->pll_Kp * obj->thetaErr + obj->pll_ui),
                          obj->pll_Umax, obj->pll_Umin);

    obj->speedEst = (obj->pll_Out + obj->speedEst) * 0.5f;
    obj->speedFlt = obj->lpf_b0 * obj->pll_Out + obj->lpf_a1 * obj->speedFlt;

    obj->theta = obj->theta + obj->speedFlt * obj->thetaDelta;

    if(obj->theta > 1.0f)
    {
        obj->theta -= 1.0f;
    }
    else if(obj->theta < -1.0f)
    {
        obj->theta += 1.0f;
    }

    obj->thetaEst = obj->theta * MATH_TWO_PI;

    if(obj->thetaEst > MATH_PI)
    {
        obj->thetaEst -= MATH_TWO_PI;
    }
    else if(obj->thetaEst < (-MATH_PI))
    {
        obj->thetaEst += MATH_TWO_PI;
    }

    return;
}

#endif // end of LUEN_run() function
