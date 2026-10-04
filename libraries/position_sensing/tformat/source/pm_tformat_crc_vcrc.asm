;;###############################################################################
;;! \file tformat_crc_vcrc.asm
;;!
;;! \brief  T-format CRC generation using the VCRC
;;!
;//###########################################################################
;//
;// $Copyright:
;// Copyright (C) 2017-2026 Texas Instruments Incorporated
;//     http://www.ti.com/ ALL RIGHTS RESERVED
;// $
;//###########################################################################

;;*****************************************************************************
;; global defines
;;*****************************************************************************
;; CRC Routine defines

PSIZE				.set	(8-1)	; 8-bits
DSIZE				.set	(8-1)	; 8-bits
CRCPOLY				.set	0x1		; x^8 + 1
LOCAL_FRAME_SIZE	.set    2


	.if __TI_EABI__
	.asg tformat_getTxCRCbyVCRC, _tformat_getTxCRCbyVCRC
	.endif
;;*****************************************************************************
;; globals
;;*****************************************************************************
    .global _tformat_getTxCRCbyVCRC

;;*****************************************************************************
;; function definitions
;;*****************************************************************************
    .text
;;*****************************************************************************
;;
;; Calculate T-format CRC for transmitted data
;;

_tformat_getTxCRCbyVCRC

;; Register Usage:
;;   XAR4:         Points to the CRC message buffer
;;

    VCRCCLR
   	VMOVZI  		 VCRCPOLY, #CRCPOLY
   	VSETCRCSIZE      #DSIZE:#PSIZE
    VSETCRCMSGFLIP
    VCRCL			*XAR4
    NOP
    NOP
    VCRCH			*XAR4++
    NOP
    NOP
    VCRCL			*XAR4
    NOP
    NOP
    VCRCH			*XAR4++
    NOP
    NOP
    VCLRCRCMSGFLIP
    VMOV32      	@ACC, VCRC
    LRETR

;; End of file
