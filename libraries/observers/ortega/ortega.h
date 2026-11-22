/*
*
* 16.11.2026
*
* Ortega nonlinear flux observer + PLL (SPM motor, Ld = Lq).
*
* Observer (Ortega):
*     dx/dt = v - Rs*i + (gamma/2) * eta(x) * (psi^2 - |eta(x)|^2),   eta(x) = x - Ls*i
* x is the total stator flux linkage in the alpha-beta frame, |eta(x)| = psi on the true state.
*
* Deviations from the paper (all on purpose, see the thesis notes):
*  - forward Euler at the ISR rate;
*  - the gain is set as Gamma = gamma * psi^2 [1/s] (gamma itself is unchanged);
*  - the PLL code is phase detector works on the flux vector.
*
* Angle and speed as in the original papers: the FOC angle is atan2(eta), 
* the speed comes from the PLL used as a PI tracking estimator. 
* The PLL angle (thetaEst) is not used by the FOC, it is kept for logging.
*
*/

#ifndef _ORTEGA_H_
#define _ORTEGA_H_

#include <stddef.h>

#ifdef __TMS320C28XX_CLA__
#include "libraries/math/src/float/CLAmath.h"
#else
#include <math.h>
#endif

#include "libraries/math/include/math.h"

#include "userParams.h"

// **************************************************************************
// the defines

//! Upper limit of Gamma*Ts. Euler on the radial dynamics needs Gamma*Ts < 2 near the circle,
//! but far from it the local rate is (3*|eta|^2/psi^2 - 1)*Gamma/2, which is 13*Gamma at
//! |eta| = 3*psi (the largest |eta| after the error enters the paper's disk |x_err| <= 2*psi)
#define ORTEGA_GAMMA_TS_MAX     (0.15f)

// **************************************************************************
// the typedefs

//! \brief Defines the ORTEGA observer object
//!
typedef struct _ORTEGA_Obj_
{
    float32_t scaleFreq_Hz;   // base frequency, Hz
    float32_t speed_sf;       // speed PU scale factor
    float32_t voltage_sf;     // Vdcbus [V] -> phase voltage [V] (1/3, no PU here)

    float32_t Ts;             // sampling period, s
    float32_t base_wTs;       // BASE_FREQ * Ts

    // motor model, SI
    float32_t Rs_Ohm;
    float32_t Ls_H;
    float32_t flux_Wb;        // psi, magnet flux linkage amplitude
    float32_t flux2_Wb2;      // psi^2
    float32_t TsRs;           // Ts * Rs

    // gain: Gamma = gamma * psi^2 is the radial error bandwidth, rad/s
    float32_t gammaN_rps;     // Gamma
    float32_t gamma;          // gamma = Gamma / psi^2, 1/(Wb^2 s), as in the paper
    float32_t kGamma;         // Ts * gamma / 2

    // inputs, kept for logging
    float32_t Valpha_V;       // reconstructed stationary phase voltage, V
    float32_t Vbeta_V;
    float32_t Ialpha_A;       // measured stator current, A
    float32_t Ibeta_A;

    // observer state and intermediate values (all at the sampling instant k)
    float32_t xAlpha_Wb;      // x_hat, total stator flux estimate
    float32_t xBeta_Wb;
    float32_t etaAlpha_Wb;    // eta(x_hat) = x_hat - Ls*i, estimated magnet flux vector
    float32_t etaBeta_Wb;
    float32_t etaMag_Wb;      // |eta|, converges to psi
    float32_t fluxErr_Wb2;    // psi^2 - |eta|^2, the gradient term
    float32_t thetaRaw_rad;   // atan2(eta_beta, eta_alpha), [-pi, pi]

    // PLL
    float32_t thetaErr;
    float32_t thetaErrSF;     // 1/(2*pi)
    float32_t theta;          // PLL angle, pu of a turn
    float32_t thetaDelta;     // angle increment factor
    float32_t thetaEst;       // PLL angle, rad, [-pi, pi]

    float32_t speedEst;
    float32_t speedFlt;

    float32_t pll_Out;
    float32_t pll_Umax;
    float32_t pll_Umin;
    float32_t pll_ui;
    float32_t pll_Kp;
    float32_t pll_KpMax;      // PLL Kp schedule
    float32_t pll_KpMin;
    float32_t pll_KpSF;
    float32_t pll_Ki;

    float32_t speedRef;       // reference speed (pu), used only by the Kp schedule

    float32_t lpf_b0;
    float32_t lpf_a1;
    float32_t lpfFc_Hz;
} ORTEGA_Obj;

//! \brief Defines the ORTEGA handle
//!
typedef struct _ORTEGA_Obj_ *ORTEGA_Handle;

// **************************************************************************
// the function prototypes

//! \brief     Initializes the ORTEGA observer
//! \param[in] pMemory   A pointer to the memory for the ORTEGA object
//! \param[in] numBytes  The number of bytes allocated for the ORTEGA object
//! \return    The ORTEGA handle
extern ORTEGA_Handle ORTEGA_init(void *pMemory, const size_t numBytes);

//! \brief     Resets the observer and PLL states to defaults
extern void ORTEGA_resetParams(ORTEGA_Handle handle);

//! \brief     Takes Ts, Rs, Ls, psi and scale factors from user parameters
extern void ORTEGA_setParams(ORTEGA_Handle handle, const USER_Params *pUserParams);

//! \brief     Sets the observer gain
//! \param[in] gammaN_rps  Gamma = gamma * psi^2, rad/s (clamped to ORTEGA_GAMMA_TS_MAX / Ts)
extern void ORTEGA_setGain(ORTEGA_Handle handle, const float32_t gammaN_rps);

//! \brief     Sets the PLL Kp schedule
extern void ORTEGA_setPLLParams(ORTEGA_Handle handle, const float32_t pll_KpMax,
                                const float32_t pll_KpMin, const float32_t pll_KpSF);

//! \brief     Updates pll_Kp from speedRef
extern void ORTEGA_updatePLLParams(ORTEGA_Handle handle);

//! \brief     Sets the speed filter cut-off and recalculates its coefficients
extern void ORTEGA_setSpeedFilterFreq(ORTEGA_Handle handle, const float32_t lpfFc_Hz);

//! \brief     Recalculates the speed filter coefficients from lpfFc_Hz
extern void ORTEGA_updateFilterParams(ORTEGA_Handle handle);

static inline void ORTEGA_setPLLKp(ORTEGA_Handle handle, const float32_t pll_Kp)
{
    ORTEGA_Obj *obj = (ORTEGA_Obj *)handle;

    obj->pll_Kp = pll_Kp;

    return;
}

static inline void ORTEGA_setPLLKi(ORTEGA_Handle handle, const float32_t pll_Ki)
{
    ORTEGA_Obj *obj = (ORTEGA_Obj *)handle;

    obj->pll_Ki = pll_Ki;

    return;
}

static inline void ORTEGA_setSpeedRef(ORTEGA_Handle handle, const float32_t speedRef_Hz)
{
    ORTEGA_Obj *obj = (ORTEGA_Obj *)handle;

    obj->speedRef = speedRef_Hz * obj->speed_sf;

    return;
}

//! \brief     Places the flux estimate on the circle |eta| = psi at angle theta_rad,
//!            using the last current sample: x_hat = Ls*i + psi*[cos, sin].
//!            This only chooses the initial condition, the observer itself is unchanged
static inline void ORTEGA_setFluxAngle(ORTEGA_Handle handle, const float32_t theta_rad)
{
    ORTEGA_Obj *obj = (ORTEGA_Obj *)handle;

    float32_t thetaPu = theta_rad * MATH_ONE_OVER_TWO_PI;

    obj->xAlpha_Wb = obj->Ls_H * obj->Ialpha_A + obj->flux_Wb * __cospuf32(thetaPu);
    obj->xBeta_Wb  = obj->Ls_H * obj->Ibeta_A  + obj->flux_Wb * __sinpuf32(thetaPu);

    return;
}

//! \brief     Puts the flux estimate on the circle at angle 0 and zeroes the PLL integrator.
//!            x_hat = 0 is avoided on purpose: eta = 0 is an (unstable) equilibrium of the
//!            observer, with i = 0 the estimate would stay there until noise pushes it out
static inline void ORTEGA_resetStates(ORTEGA_Handle handle)
{
    ORTEGA_Obj *obj = (ORTEGA_Obj *)handle;

    obj->Ialpha_A  = 0.0f;
    obj->Ibeta_A   = 0.0f;
    obj->xAlpha_Wb = obj->flux_Wb;
    obj->xBeta_Wb  = 0.0f;
    obj->pll_ui    = 0.0f;

    return;
}

//! \brief     Sets the PLL angle (rad), used for the handover from the forced angle
static inline void ORTEGA_setAnglePu(ORTEGA_Handle handle, const float32_t theta_rad)
{
    ORTEGA_Obj *obj = (ORTEGA_Obj *)handle;

    obj->theta = theta_rad * MATH_ONE_OVER_TWO_PI;

    return;
}

//! \brief     Sets the PLL speed (Hz), used for the handover from the forced angle
static inline void ORTEGA_setPLLSpeedPu(ORTEGA_Handle handle, const float32_t speed_Hz)
{
    ORTEGA_Obj *obj = (ORTEGA_Obj *)handle;

    // the PI integrator is seeded too, otherwise the speed collapses on the first step
    obj->speedFlt = speed_Hz * obj->speed_sf;
    obj->speedEst = speed_Hz * obj->speed_sf;
    obj->pll_Out  = speed_Hz * obj->speed_sf;
    obj->pll_ui   = speed_Hz * obj->speed_sf;

    return;
}

static inline float32_t ORTEGA_getSpeed_Hz(ORTEGA_Handle handle)
{
    ORTEGA_Obj *obj = (ORTEGA_Obj *)handle;

    return(obj->speedEst * obj->scaleFreq_Hz);
}

static inline float32_t ORTEGA_getSpeedPLL_Hz(ORTEGA_Handle handle)
{
    ORTEGA_Obj *obj = (ORTEGA_Obj *)handle;

    return(obj->speedFlt * obj->scaleFreq_Hz);
}

static inline float32_t ORTEGA_getAnglePLL(ORTEGA_Handle handle)
{
    ORTEGA_Obj *obj = (ORTEGA_Obj *)handle;

    return(obj->thetaEst);
}

//! \brief     Angle of eta(x_hat) at the current sampling instant, rad, no PLL
static inline float32_t ORTEGA_getAngleRaw(ORTEGA_Handle handle)
{
    ORTEGA_Obj *obj = (ORTEGA_Obj *)handle;

    return(obj->thetaRaw_rad);
}

static inline float32_t ORTEGA_getFluxMag_Wb(ORTEGA_Handle handle)
{
    ORTEGA_Obj *obj = (ORTEGA_Obj *)handle;

    return(obj->etaMag_Wb);
}

//! \brief     Runs the ORTEGA observer
//! \param[in] Vdcbus      The dc bus voltage, V
//! \param[in] pVabc_pu    The pointer to the modulation functions applied in this PWM period
//! \param[in] pIabVec     The pointer to the measured alpha-beta currents, A
static inline void ORTEGA_run(ORTEGA_Handle handle,
                        float32_t Vdcbus, MATH_vec3 *pVabc_pu, MATH_vec2 *pIabVec)
{
    ORTEGA_Obj *obj = (ORTEGA_Obj *)handle;

    // Reconstruction voltage_sf = 1/3 gives volts instead of PU
    float32_t Vtemp   = Vdcbus * obj->voltage_sf;

    float32_t VphaseA = Vtemp *
            (pVabc_pu->value[0] * 2.0f - pVabc_pu->value[1] - pVabc_pu->value[2]);

    float32_t VphaseB = Vtemp *
            (pVabc_pu->value[1] * 2.0f - pVabc_pu->value[0] - pVabc_pu->value[2]);

    obj->Valpha_V = VphaseA;
    obj->Vbeta_V  = (VphaseA + VphaseB * 2.0f) * MATH_ONE_OVER_SQRT_THREE;

    obj->Ialpha_A = pIabVec->value[0];
    obj->Ibeta_A  = pIabVec->value[1];

    // eta and the angle use x_hat[k] and i[k], so the angle belongs to the sampling instant
    obj->etaAlpha_Wb = obj->xAlpha_Wb - obj->Ls_H * obj->Ialpha_A;
    obj->etaBeta_Wb  = obj->xBeta_Wb  - obj->Ls_H * obj->Ibeta_A;

    float32_t eta2 = obj->etaAlpha_Wb * obj->etaAlpha_Wb + obj->etaBeta_Wb * obj->etaBeta_Wb;

    obj->etaMag_Wb   = sqrtf(eta2);
    obj->fluxErr_Wb2 = obj->flux2_Wb2 - eta2;

    obj->thetaRaw_rad = __atan2(obj->etaBeta_Wb, obj->etaAlpha_Wb);

    // x_hat[k+1]: v is the average voltage of the period [k, k+1], so the v*Ts part is exact,
    // only the R*i and the gradient terms are rectangle-rule approximations
    float32_t corr = obj->kGamma * obj->fluxErr_Wb2;

    obj->xAlpha_Wb += obj->Ts * obj->Valpha_V - obj->TsRs * obj->Ialpha_A
                    + corr * obj->etaAlpha_Wb;
    obj->xBeta_Wb  += obj->Ts * obj->Vbeta_V  - obj->TsRs * obj->Ibeta_A
                    + corr * obj->etaBeta_Wb;

    // Phase detector on the flux vector: sin(theta - thetaPll) = eta x [cos, sin] / |eta|
    float32_t pllSine   = __sinpuf32(obj->theta);
    float32_t pllCosine = __cospuf32(obj->theta);

    obj->thetaErr = (obj->etaBeta_Wb * pllCosine - obj->etaAlpha_Wb * pllSine) *
                    obj->thetaErrSF / (obj->etaMag_Wb + 1.0e-9f);

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
}   // end of ORTEGA_run() function

#endif // end of _ORTEGA_H_ definition
