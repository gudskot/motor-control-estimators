//#############################################################################
//
// FILE:   pto_qepdiv.h
//
// TITLE:  Prototypes and Definitions for the Position Manager PTO
//         QEPDiv Library
//
//
//#############################################################################
// $Copyright:
// Copyright (C) 2017-2026 Texas Instruments Incorporated
//     http://www.ti.com/ ALL RIGHTS RESERVED
// $
//#############################################################################

#ifndef PTO_QEPDIV_H
#define PTO_QEPDIV_H

//
// Library of functions
//
#include <stdint.h>

//
// Function Prototypes
//
extern void pto_qepdiv_setupPeriph(void);
extern uint16_t pto_qepdiv_config(uint16_t divider, uint16_t indexWidth);
extern void pto_qepdiv_startOperation(uint16_t run);
extern void pto_qepdiv_reset(void);
extern void pto_qepdiv_initCLBXBAR(void);
extern void pto_qepdiv_resetCLB(void);

#endif // PTO_QEPDIV_H

//
// End of File
//
