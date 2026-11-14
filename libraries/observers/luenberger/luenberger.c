/*
*
* Created by Dmytro Khymytsia
* 09.11.2026
*
* Luenberger back-EMF observer + PLL, setup functions
*
*/

// **************************************************************************
// the includes
#include <stddef.h>
#include <string.h>

#include "luenberger.h"

// **************************************************************************
// the functions

LUEN_Handle LUEN_init(void *pMemory, const size_t numBytes)
{
    if(numBytes < sizeof(LUEN_Obj))
    {
        return((LUEN_Handle)NULL);
    }

    memset(pMemory, 0, sizeof(LUEN_Obj));

    return((LUEN_Handle)pMemory);
}   // end of LUEN_init() function

//------------------------------------------------------------------------------
void LUEN_resetParams(LUEN_Handle handle)
{
    LUEN_Obj *obj = (LUEN_Obj *)handle;

    LUEN_resetStates(handle);

    obj->speedEst = 0.0f;
    obj->speedFlt = 0.0f;
    obj->pll_Out  = 0.0f;
    obj->theta    = 0.0f;
    obj->thetaEst = 0.0f;
    obj->pll_Kp   = obj->pll_KpMin;

    return;
}

//------------------------------------------------------------------------------
void LUEN_setParams(LUEN_Handle handle, const USER_Params *pUserParams)
{
    LUEN_Obj *obj = (LUEN_Obj *)handle;

    // scale factors
    obj->scaleFreq_Hz = pUserParams->maxFrequency_Hz;

    obj->speed_sf   = 1.0f / pUserParams->maxFrequency_Hz;
    obj->voltage_sf = (MATH_ONE_OVER_THREE / 4096.0f) / pUserParams->voltage_sf;
    obj->current_sf = (1.0f / 4096.0f) / pUserParams->current_sf;

    obj->Ts         = pUserParams->ctrlPeriod_sec;
    obj->base_wTs   = obj->Ts * obj->scaleFreq_Hz;
    obj->thetaDelta = obj->scaleFreq_Hz * obj->Ts;
    obj->thetaErrSF = MATH_ONE_OVER_TWO_PI;

    obj->pll_Kp   = obj->pll_KpMin;
    obj->pll_ui   = 0.0f;
    obj->pll_Ki   = 0.0f;
    obj->pll_Umax = 1.0f;
    obj->pll_Umin = -1.0f;

    LUEN_resetStates(handle);

    // R-L plant in per unit, forward Euler
    float32_t motor_Rs = pUserParams->motor_Rs_Ohm;
    float32_t motor_Ls = pUserParams->motor_Ls_d_H;

    float32_t baseVIs = (pUserParams->voltage_sf * obj->Ts) / pUserParams->current_sf;

    obj->Fplant = 1.0f - (motor_Rs / motor_Ls * obj->Ts);
    obj->Gplant = baseVIs / motor_Ls;

    LUEN_updateFilterParams(handle);

    return;
}

//------------------------------------------------------------------------------
void LUEN_setBandwidth(LUEN_Handle handle, const USER_Params *pUserParams,
                       const float32_t omega_o, const float32_t zeta)
{
    LUEN_Obj *obj = (LUEN_Obj *)handle;

    float32_t motor_Rs = pUserParams->motor_Rs_Ohm;
    float32_t motor_Ls = pUserParams->motor_Ls_d_H;

    // Forward Euler is accurate only while omega_o * Ts is well below 1,
    // so the bandwidth is clamped (0.3 is a rule of thumb, not a derived limit)
    float32_t wo    = omega_o;
    float32_t woMax = 0.3f / obj->Ts;

    if(wo > woMax)
    {
        wo = woMax;
    }

    // Pole placement of the (current, EMF) pair at w = 0:
    // s^2 + (Rs/Ls + l1) * s - l2/Ls = 0   ->   l1 = 2*zeta*wo - Rs/Ls,  l2 = -Ls*wo^2
    float32_t l1 = 2.0f * zeta * wo - motor_Rs / motor_Ls;
    float32_t l2 = -motor_Ls * wo * wo;

    // To per-unit and per step (EMF gain scales with Ibase / Vbase)
    obj->K1 = obj->Ts * l1;
    obj->K2 = obj->Ts * l2 * (pUserParams->current_sf / pUserParams->voltage_sf);

    return;
}

//------------------------------------------------------------------------------
void LUEN_setPLLParams(LUEN_Handle handle, const float32_t pll_KpMax,
                       const float32_t pll_KpMin, const float32_t pll_KpSF)
{
    LUEN_Obj *obj = (LUEN_Obj *)handle;

    obj->pll_KpMax = pll_KpMax;
    obj->pll_KpMin = pll_KpMin;
    obj->pll_KpSF  = pll_KpSF;

    return;
}

//------------------------------------------------------------------------------
void LUEN_updatePLLParams(LUEN_Handle handle)
{
    LUEN_Obj *obj = (LUEN_Obj *)handle;

    float32_t speedRefAbs = fabsf(obj->speedRef);

    obj->pll_Kp = obj->pll_KpMin + obj->pll_KpSF * speedRefAbs;
    obj->pll_Kp = __fsat(obj->pll_Kp, obj->pll_KpMax, obj->pll_KpMin);

    return;
}

//------------------------------------------------------------------------------
void LUEN_setSpeedFilterFreq(LUEN_Handle handle, const float32_t lpfFc_Hz)
{
    LUEN_Obj *obj = (LUEN_Obj *)handle;

    obj->lpfFc_Hz = lpfFc_Hz;

    LUEN_updateFilterParams(handle);

    return;
}

//------------------------------------------------------------------------------
void LUEN_updateFilterParams(LUEN_Handle handle)
{
    LUEN_Obj *obj = (LUEN_Obj *)handle;

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
