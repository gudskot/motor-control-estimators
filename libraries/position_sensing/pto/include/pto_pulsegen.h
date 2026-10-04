//#############################################################################
//
// FILE:   pto_pulsegen.h
//
// TITLE:  Prototypes and Definitions for the Position Manager PTO
//         Pulsegen Library
//
//
//#############################################################################
// $Copyright:
// Copyright (C) 2017-2026 Texas Instruments Incorporated
//     http://www.ti.com/ ALL RIGHTS RESERVED
// $
//#############################################################################

#ifndef PTO_PULSEGEN_H
#define PTO_PULSEGEN_H

//
// Library of functions
//
#include <stdint.h>

//
// Function Prototypes
//
extern void pto_pulsegen_setupPeriph(void);
extern uint16_t pto_pulsegen_runPulseGen(
        uint32_t pulseLo,
        uint32_t pulseHi,
        uint32_t ptoActivePeriod,
        uint32_t ptoFullPeriod,
        uint32_t ptoInterruptTime,
        uint16_t ptoDirection,
        uint16_t run);
extern void pto_pulsegen_startOperation(void);
extern void pto_pulsegen_initCLBXBAR(void);
extern void pto_pulsegen_resetCLB(void);
extern void pto_pulsegen_reset(void);

#endif // PTO_PULSEGEN_H

//
// End of File
//
