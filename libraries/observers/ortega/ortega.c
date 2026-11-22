/*
*
* 16.11.2026
*
* Ortega nonlinear flux observer + PLL, setup functions.
* The flux observer works in SI (Wb, V, A).
*
*/

// **************************************************************************
// the includes
#include <stddef.h>
#include <string.h>

#include "ortega.h"

// **************************************************************************
// the functions

ORTEGA_Handle ORTEGA_init(void *pMemory, const size_t numBytes)
{
    if(numBytes < sizeof(ORTEGA_Obj))
    {
        return((ORTEGA_Handle)NULL);
    }

    memset(pMemory, 0, sizeof(ORTEGA_Obj));

    return((ORTEGA_Handle)pMemory);
}   // end of ORTEGA_init() function

//------------------------------------------------------------------------------
void ORTEGA_resetParams(ORTEGA_Handle handle)
{
    ORTEGA_Obj *obj = (ORTEGA_Obj *)handle;

    ORTEGA_resetStates(handle);

    obj->speedEst = 0.0f;
    obj->speedFlt = 0.0f;
    obj->pll_Out  = 0.0f;
    obj->theta    = 0.0f;
    obj->thetaEst = 0.0f;
    obj->pll_Kp   = obj->pll_KpMin;

    return;
}

//------------------------------------------------------------------------------
void ORTEGA_setParams(ORTEGA_Handle handle, const USER_Params *pUserParams)
{
    ORTEGA_Obj *obj = (ORTEGA_Obj *)handle;

    // scale factors, PLL side identical to LUEN
    obj->scaleFreq_Hz = pUserParams->maxFrequency_Hz;

    obj->speed_sf   = 1.0f / pUserParams->maxFrequency_Hz;
    obj->voltage_sf = MATH_ONE_OVER_THREE;

    obj->Ts         = pUserParams->ctrlPeriod_sec;
    obj->base_wTs   = obj->Ts * obj->scaleFreq_Hz;
    obj->thetaDelta = obj->scaleFreq_Hz * obj->Ts;
    obj->thetaErrSF = MATH_ONE_OVER_TWO_PI;

    obj->pll_Kp   = obj->pll_KpMin;
    obj->pll_ui   = 0.0f;
    obj->pll_Ki   = 0.0f;
    obj->pll_Umax = 1.0f;
    obj->pll_Umin = -1.0f;

    // motor model, SPM: Ld = Lq, motor_Ls_d_H is used
    obj->Rs_Ohm    = pUserParams->motor_Rs_Ohm;
    obj->Ls_H      = pUserParams->motor_Ls_d_H;
    obj->flux_Wb   = pUserParams->motor_ratedFlux_Wb;
    obj->flux2_Wb2 = obj->flux_Wb * obj->flux_Wb;
    obj->TsRs      = obj->Ts * obj->Rs_Ohm;

    // gamma depends on psi^2, so it is recomputed whenever psi changes
    ORTEGA_setGain(handle, obj->gammaN_rps);

    ORTEGA_resetStates(handle);

    ORTEGA_updateFilterParams(handle);

    return;
}

//------------------------------------------------------------------------------
void ORTEGA_setGain(ORTEGA_Handle handle, const float32_t gammaN_rps)
{
    ORTEGA_Obj *obj = (ORTEGA_Obj *)handle;

    float32_t G = gammaN_rps;

    // Ts is still 0 if setGain is called before setParams, setParams clamps it later
    if((obj->Ts > 0.0f) && (G > (ORTEGA_GAMMA_TS_MAX / obj->Ts)))
    {
        G = ORTEGA_GAMMA_TS_MAX / obj->Ts;
    }
    else if(G < 0.0f)
    {
        G = 0.0f;
    }

    obj->gammaN_rps = G;

    if(obj->flux2_Wb2 > 0.0f)
    {
        obj->gamma  = G / obj->flux2_Wb2;
        obj->kGamma = 0.5f * obj->Ts * obj->gamma;
    }
    else
    {
        // psi not known yet (setGain called before setParams)
        obj->gamma  = 0.0f;
        obj->kGamma = 0.0f;
    }

    return;
}

//------------------------------------------------------------------------------
void ORTEGA_setPLLParams(ORTEGA_Handle handle, const float32_t pll_KpMax,
                         const float32_t pll_KpMin, const float32_t pll_KpSF)
{
    ORTEGA_Obj *obj = (ORTEGA_Obj *)handle;

    obj->pll_KpMax = pll_KpMax;
    obj->pll_KpMin = pll_KpMin;
    obj->pll_KpSF  = pll_KpSF;

    return;
}

//------------------------------------------------------------------------------
void ORTEGA_updatePLLParams(ORTEGA_Handle handle)
{
    ORTEGA_Obj *obj = (ORTEGA_Obj *)handle;

    float32_t speedRefAbs = fabsf(obj->speedRef);

    obj->pll_Kp = obj->pll_KpMin + obj->pll_KpSF * speedRefAbs;
    obj->pll_Kp = __fsat(obj->pll_Kp, obj->pll_KpMax, obj->pll_KpMin);

    return;
}

//------------------------------------------------------------------------------
void ORTEGA_setSpeedFilterFreq(ORTEGA_Handle handle, const float32_t lpfFc_Hz)
{
    ORTEGA_Obj *obj = (ORTEGA_Obj *)handle;

    obj->lpfFc_Hz = lpfFc_Hz;

    ORTEGA_updateFilterParams(handle);

    return;
}

//------------------------------------------------------------------------------
void ORTEGA_updateFilterParams(ORTEGA_Handle handle)
{
    ORTEGA_Obj *obj = (ORTEGA_Obj *)handle;

    if(obj->lpfFc_Hz <= 0.0f)
    {
        // no filter, otherwise a1 = 1 and b0 = 0 would freeze speedFlt
        obj->lpf_a1 = 0.0f;
        obj->lpf_b0 = 1.0f;
    }
    else
    {
        float32_t tempVarLpf = obj->lpfFc_Hz * MATH_TWO_PI * obj->Ts;

        obj->lpf_a1 = 1.0f / (1.0f + tempVarLpf);
        obj->lpf_b0 = 1.0f - obj->lpf_a1;
    }

    return;
}

// end of file
