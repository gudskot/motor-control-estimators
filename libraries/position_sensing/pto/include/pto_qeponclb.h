//#############################################################################
//
// FILE:   pto_qeponclb.h
//
// TITLE:  Prototypes and Definitions for the Position Manager PTO
//         QEPonCLB Library
//
//
//#############################################################################
// $Copyright:
// Copyright (C) 2017-2026 Texas Instruments Incorporated
//     http://www.ti.com/ ALL RIGHTS RESERVED
// $
//#############################################################################

#ifndef PTO_QEPONCLB_H
#define PTO_QEPONCLB_H

//
// Library of functions
//
#include <stdint.h>

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "clb.h"

//
// Function Prototypes
//
void pto_qeponclb_setupPeriph(uint32_t maxPosition);
void pto_qeponclb_initCLBQEP(uint32_t maxPosition);
void pto_qeponclb_initCLBXBAR(void);

//*****************************************************************************
//
//! Configure Position Counter maximum
//!
//! \param clbBase is the base address of the CLB
//! \param maxPosition is the maximum of the position counter
//!
//! This function configures the maximum counter position within the CLB.
//!
//! \return None
//
//*****************************************************************************
static inline void
pto_qeponclb_configMaxCounterPos(uint32_t clbBase, uint32_t maxPosition)
{
    CLB_configCounterLoadMatch(clbBase, CLB_CTR0, maxPosition-1, maxPosition, 0xFFFFFFFF);
}

//*****************************************************************************
//
//! Enable QEPonCLB
//!
//! \param clbBase is the base address of the CLB
//! \param enableCapture is the GPREG bit corresponding to enable CLBQEP
//!
//! This function enables the QEPonCLB example.
//!
//! \return None
//
//*****************************************************************************
static inline void
pto_qeponclb_enableCLBQEP(uint32_t clbBase, uint32_t enableCapture)
{
    CLB_setGPREG(clbBase, enableCapture);
}

//*****************************************************************************
//
//! Reset QEPonCLB
//!
//! \param clbBase is the base address of the CLB
//! \param resetCounter is the GPREG bit corresponding to reset CLBQEP
//!
//! This function resets the QEPonCLB example.
//!
//! \return None
//
//*****************************************************************************
static inline void
pto_qeponclb_resetCLBQEP(uint32_t clbBase, uint32_t resetCounter)
{
    CLB_setGPREG(clbBase, resetCounter);
}

//*****************************************************************************
//
//! Get the value of COUNTER0
//!
//! \param clbBase is the base address of the CLB
//!
//! This function is a runtime function to be called when wanting
//! to capture the value of COUNTER0 of the CLB.
//!
//! \return counterVal return the COUNTER0 value of the CLB
//
//*****************************************************************************
static inline uint32_t
pto_qeponclb_getCounterVal(uint32_t clbBase)
{
    uint32_t counterVal;
    counterVal = CLB_getRegister(clbBase, CLB_REG_CTR_C0);
    return(counterVal);
}

//*****************************************************************************
//
//! Get the position of CLBQEP
//!
//! \param clbBase is the base address of the CLB
//!
//! This function is a runtime function to be called when wanting
//! to capture the position of CLBQEP from the CLB.
//!
//! \return clbqepPos return the data (CLBQEP position) pushed by the HLC
//
//*****************************************************************************
static inline uint32_t
pto_qeponclb_getCLBQEPPos(uint32_t clbBase)
{
    uint32_t clbqepPos;
    clbqepPos = HWREG(clbBase + CLB_DATAEXCH + CLB_O_PUSH(0));
    return(clbqepPos);
}

//*****************************************************************************
//
//! Clear the CLB's FIFO pointer
//!
//! \param clbBase is the base address of the CLB
//!
//! This function is a runtime function to be called when needing
//! to clear the FIFO pointer of the CLB. This needs to be called
//! subsequently after reading a FIFO value pushed by the HLC so
//! that the next PUSH will be in the correct position.
//!
//! \return None
//
//*****************************************************************************
static inline void
pto_qeponclb_clearFIFOptr(uint32_t clbBase)
{
    HWREG(clbBase + CLB_LOGICCTL + CLB_O_BUF_PTR) = 0U;
}

#endif // PTO_QEPONCLB_H

//
// End of File
//
