let Common = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let references = system.getScript("/libraries/MCSDKLibraryReferences.js");

let drv8317Registers = [
    {
        $name: "DEV_STS",
        registerName: "Device Status Register",
        offset: 0x0,
        registerType: "status",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "FAULT",
                description: "Device fault status",
                bitWidth: 1,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "OTF",
                description: "Over temperature fault status",
                bitWidth: 1,
                startBit: 1,
                enumEnable: false,
            },
            {
                $name: "UVP",
                description: "Supply under voltage status",
                bitWidth: 1,
                startBit: 2,
                enumEnable: false,
            },
            {
                $name: "OVP",
                description: "Over voltage status",
                bitWidth: 1,
                startBit: 3,
                enumEnable: false,
            },
            {
                $name: "UVW",
                description: "VM under voltage warning fault status",
                bitWidth: 1,
                startBit: 4,
                enumEnable: false,
            },
            {
                $name: "OCP",
                description: "Driver over current Status",
                bitWidth: 1,
                startBit: 5,
                enumEnable: false,
            },
            {
                $name: "SPIFLT",
                description: "SPI fault status",
                bitWidth: 1,
                startBit: 6,
                enumEnable: false,
            },
            {
                $name: "RESET",
                description: "Device power on status",
                bitWidth: 1,
                startBit: 7,
                enumEnable: false,
            },
            {
                $name: "SYSFLT",
                description: "OTP read fault occurred",
                bitWidth: 1,
                startBit: 8,
                enumEnable: false,
            },
            {
                $name: "DNRDY_STS",
                description: "Device not ready status",
                bitWidth: 1,
                startBit: 9,
                enumEnable: false,
            },
            {
                $name: "DEV_STS_PARITY",
                description: "Parity Bit if SPI_PEN is set to '1' otherwise reserved",
                bitWidth: 1,
                startBit: 15,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "DEV_RSTS",
        registerName: "Device Raw Status Register",
        offset: 0x2,
        registerType: "status",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "OTF_RSTS",
                description: "Over temperature fault raw status",
                bitWidth: 1,
                startBit: 1,
                enumEnable: false,
            },
            {
                $name: "UVP_RSTS",
                description: "Under voltage protection fault raw status",
                bitWidth: 1,
                startBit: 2,
                enumEnable: false,
            },
            {
                $name: "OVP_RSTS",
                description: "Over voltage protection fault raw status",
                bitWidth: 1,
                startBit: 3,
                enumEnable: false,
            },
            {
                $name: "VMUV_WRSTS",
                description: "VM under voltage warning fault raw status",
                bitWidth: 1,
                startBit: 4,
                enumEnable: false,
            },
            {
                $name: "OCP_RSTS",
                description: "Driver OCP raw status",
                bitWidth: 1,
                startBit: 5,
                enumEnable: false,
            },
            {
                $name: "SPIF_RSTS",
                description: "SPI fault raw status",
                bitWidth: 1,
                startBit: 6,
                enumEnable: false,
            },
            {
                $name: "SYSF_RSTS",
                description: "OTP parity error during load, raw status",
                bitWidth: 1,
                startBit: 8,
                enumEnable: false,
            },
            {
                $name: "DNRDY_RSTS",
                description: "Device not ready indicator",
                bitWidth: 1,
                startBit: 9,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "OT_STS",
        registerName: "Over Temperature Status Register",
        offset: 0x4,
        registerType: "status",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "OTS_FET",
                description: "FET over temperature shutdown fault status",
                bitWidth: 1,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "OTW_FET",
                description: "FET over temperature warning fault status",
                bitWidth: 1,
                startBit: 1,
                enumEnable: false,
            },
            {
                $name: "OT_STS_PARITY",
                description: "Parity Bit if SPI_PEN is set to '1' otherwise reserved",
                bitWidth: 1,
                startBit: 15,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "SUP_STS",
        registerName: "Supply Status Register",
        offset: 0x5,
        registerType: "status",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "VM_UV",
                description: "VM under voltage fault status",
                bitWidth: 1,
                startBit: 1,
                enumEnable: false,
            },
            {
                $name: "CP_UV",
                description: "Charge pump under voltage fault status",
                bitWidth: 1,
                startBit: 4,
                enumEnable: false,
            },
            {
                $name: "VM_OV",
                description: "VM over voltage fault status",
                bitWidth: 1,
                startBit: 6,
                enumEnable: false,
            },
            {
                $name: "VMUV_WARN",
                description: "VM under voltage warning fault status",
                bitWidth: 1,
                startBit: 7,
                enumEnable: false,
            },
            {
                $name: "SUP_STS_PARITY",
                description: "Parity Bit if SPI_PEN is set to '1' otherwise reserved",
                bitWidth: 1,
                startBit: 15,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "DRV_STS",
        registerName: "Driver Status Register",
        offset: 0x6,
        registerType: "status",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "OCPA_LS",
                description: "Over current status on low-side MOSFET of OUTA",
                bitWidth: 1,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "OCPB_LS",
                description: "Over current status on low-side MOSFET of OUTB",
                bitWidth: 1,
                startBit: 1,
                enumEnable: false,
            },
            {
                $name: "OCPC_LS",
                description: "Over current status on low-side MOSFET of OUTC",
                bitWidth: 1,
                startBit: 2,
                enumEnable: false,
            },
            {
                $name: "OCPA_HS",
                description: "Over current status on high-side MOSFET of OUTA",
                bitWidth: 1,
                startBit: 4,
                enumEnable: false,
            },
            {
                $name: "OCPB_HS",
                description: "Over current status on high-side MOSFET of OUTB",
                bitWidth: 1,
                startBit: 5,
                enumEnable: false,
            },
            {
                $name: "OCPC_HS",
                description: "Over current status on high-side MOSFET of OUTC",
                bitWidth: 1,
                startBit: 6,
                enumEnable: false,
            },
            {
                $name: "DRV_STS_PARITY",
                description: "Parity Bit if SPI_PEN is set to '1' otherwise reserved",
                bitWidth: 1,
                startBit: 15,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "SYSIF_STS",
        registerName: "System Interface Status Register",
        offset: 0x7,
        registerType: "status",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "FRM_ERR",
                description: "SPI frame error",
                bitWidth: 1,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "BUS_CNT",
                description: "SPI bus contention error",
                bitWidth: 1,
                startBit: 1,
                enumEnable: false,
            },
            {
                $name: "SPI_PARITY",
                description: "SPI parity error",
                bitWidth: 1,
                startBit: 2,
                enumEnable: false,
            },
            {
                $name: "OTPLD_ERR",
                description: "OTP parity error during load",
                bitWidth: 1,
                startBit: 4,
                enumEnable: false,
            },
            {
                $name: "SYSIF_STS_PARITY",
                description: "Parity Bit if SPI_PEN is set to '1' otherwise reserved",
                bitWidth: 1,
                startBit: 15,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "FLT_MODE",
        registerName: "Fault Mode Register",
        offset: 0x10,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "OTF_MODE",
                description: "Over temperature fault mode",
                bitWidth: 2,
                startBit: 0,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "OTF_MODE_SLOW_RETRY",
                        bitValue: 0,
                        description: "Report on nFAULT, Latch into status register, pre-driver Hi-Z, auto recover with Slow Retry time (in ms)"
                    },
                    {
                        $name: "OTF_MODE_FAST_RETRY",
                        bitValue: 1,
                        description: "Report on nFAULT, Latch into status register, pre-driver Hi-Z, auto recover with Fast Retry time (in ms)"
                    },
                ])
            },
            {
                $name: "UVP_MODE",
                description: "Under voltage protection fault mode",
                bitWidth: 2,
                startBit: 2,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "UVP_MODE_SLOW_RETRY",
                        bitValue: 0,
                        description: "Report on nFAULT, Latch into status register, pre-driver Hi-Z, auto recovery with slow retry time (in ms) "
                    },
                    {
                        $name: "UVP_MODE_FAST_RETRY",
                        bitValue: 1,
                        description: "Report on nFAULT, Latch into status register, pre-driver Hi-Z, auto recovery with fast retry time (in ms)"
                    },
                ])
            },
            {
                $name: "OCP_MODE",
                description: "Over current protection fault mode",
                bitWidth: 3,
                startBit: 4,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "OCP_MODE_SLOW_RETRY",
                        bitValue: 0,
                        description: "Report on nFAULT, Latch into status register, pre-driver Hi-Z, auto recovery with slow retry time (in ms)"
                    },
                    {
                        $name: "OCP_MODE_FAST_RETRY",
                        bitValue: 1,
                        description: "Report on nFAULT, Latch into status register, pre-driver Hi-Z, auto recovery with fast retry time (in ms)"
                    },
                    {
                        $name: "OCP_MODE_WAIT",
                        bitValue: 2,
                        description: "Report on nFAULT, Latch into status register, pre-driver Hi-Z, no auto recovery, wait for CLR_FLT"
                    },
                    {
                        $name: "OCP_MODE_NO",
                        bitValue: 3,
                        description: "Report on nFAULT, Latch into status register, No action on pre-driver"
                    },
                ])
            },
            {
                $name: "SPIFLT_MODE",
                description: "SPI fault mode",
                bitWidth: 1,
                startBit: 7,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "SPIFLT_MODE_LATCH",
                        bitValue: 0,
                        description: "Report on nFAULT, latch into status register, no action on pre-driver"
                    },
                    {
                        $name: "SPIFLT_MODE_DISABLE",
                        bitValue: 1,
                        description: "Disabled"
                    },
                ])
            },
            {
                $name: "OVP_MODE",
                description: "Over voltage protection fault mode",
                bitWidth: 2,
                startBit: 9,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "OVP_MODE_SLOW_RETRY",
                        bitValue: 0,
                        description: "Report on nFAULT, latch into status register, pre-driver Hi-Z, auto recovery with slow retry time (in ms)"
                    },
                    {
                        $name: "OVP_MODE_FAST_RETRY",
                        bitValue: 1,
                        description: "Report on nFAULT, latch into status register, pre-driver Hi-Z, auto recovery with fast retry time (in ms)"
                    },
                ])
            },
            {
                $name: "VMUV_WARN_MODE",
                description: "VM under voltage warning fault mode",
                bitWidth: 2,
                startBit: 11,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "VMUV_WARN_MODE_SLOW_RETRY",
                        bitValue: 0,
                        description: "Report on nFAULT, latch into status register, pre-driver Hi-Z, auto recovery with slow retry time (in ms) "
                    },
                    {
                        $name: "VMUV_WARN_MODE_FAST_RETRY",
                        bitValue: 1,
                        description: "Report on nFAULT, latch into status register, pre-driver Hi-Z, auto recovery with fast retry time (in ms)"
                    },
                    {
                        $name: "VMUV_WARN_MODE_NO",
                        bitValue: 2,
                        description: "Report on nFAULT, latch into status register, no action on pre-driver"
                    },
                    {
                        $name: "VMUV_WARN_MODE_DISABLE",
                        bitValue: 3,
                        description: "Disabled"
                    },
                ])
            },
            {
                $name: "FLT_MODE_PARITY",
                description: "Parity Bit if SPI_PEN is set to '1' otherwise reserved",
                bitWidth: 1,
                startBit: 15,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "SYSF_CTRL",
        registerName: "System Fault Control Register",
        offset: 0x12,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "VMUV_WARN_EN",
                description: "VM under voltage warn fault enable",
                bitWidth: 1,
                startBit: 7,
                enumEnable: false,
            },
            {
                $name: "OTW_FET_EN",
                description: "FET over temperature warning fault enable",
                bitWidth: 1,
                startBit: 9,
                enumEnable: false,
            },
            {
                $name: "DNRDY_EN",
                description: "Device not ready fault enable",
                bitWidth: 1,
                startBit: 10,
                enumEnable: false,
            },
            {
                $name: "SYSF_CTRL_PARITY",
                description: "Parity Bit if SPI_PEN is set to '1' otherwise reserved",
                bitWidth: 1,
                startBit: 15,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "DRVF_TCTRL",
        registerName: "Driver Fault Control Register",
        offset: 0x13,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "VMUV_WARN_TDG",
                description: "VM under voltage warning deglitch time",
                bitWidth: 2,
                startBit: 0,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "VMUV_WARN_TDG_0p3us",
                        bitValue: 0,
                        description: "0.3 µs"
                    },
                    {
                        $name: "VMUV_WARN_TDG_0p6us",
                        bitValue: 1,
                        description: "0.6 µs"
                    },
                    {
                        $name: "VMUV_WARN_TDG_0p9us",
                        bitValue: 2,
                        description: "0.9 µs"
                    },
                    {
                        $name: "VMUV_WARN_TDG_2p0us",
                        bitValue: 3,
                        description: "2 µs"
                    },
                ])
            },
            {
                $name: "OCP_TBLANK",
                description: "OCP blanking time",
                bitWidth: 2,
                startBit: 2,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "OCP_TBLANK_0p3us",
                        bitValue: 0,
                        description: "0.3 µs"
                    },
                    {
                        $name: "OCP_TBLANK_0p7us",
                        bitValue: 1,
                        description: "0.7 µs"
                    },
                    {
                        $name: "OCP_TBLANK_2p0us",
                        bitValue: 2,
                        description: "2 µs"
                    },
                    {
                        $name: "OCP_TBLANK_1p2us",
                        bitValue: 3,
                        description: "1.2 µs"
                    },
                ])
            },
            {
                $name: "OCP_DEG",
                description: "OCP deglitch time",
                bitWidth: 2,
                startBit: 4,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "OCP_DEG_0p3us",
                        bitValue: 0,
                        description: "0.3 µs"
                    },
                    {
                        $name: "OCP_DEG_0p6us",
                        bitValue: 1,
                        description: "0.6 µs"
                    },
                    {
                        $name: "OCP_DEG_0p9us",
                        bitValue: 2,
                        description: "0.9 µs"
                    },
                    {
                        $name: "OCP_DEG_1p2us",
                        bitValue: 3,
                        description: "1.2 µs"
                    },
                ])
            },
            {
                $name: "DRVF_TCTRL_PARITY",
                description: "Parity Bit if SPI_PEN is set to '1' otherwise reserved",
                bitWidth: 1,
                startBit: 15,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "FLT_TCTRL",
        registerName: "Fault Timing Control Register",
        offset: 0x16,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "FAST_TRETRY",
                description: "Retry time (typical) for fast recovery from fault condition",
                bitWidth: 2,
                startBit: 0,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "FAST_TRETRY_0p5ms",
                        bitValue: 0,
                        description: "0.5ms"
                    },
                    {
                        $name: "FAST_TRETRY_1p0ms",
                        bitValue: 1,
                        description: "1ms"
                    },
                    {
                        $name: "FAST_TRETRY_2p0ms",
                        bitValue: 2,
                        description: "2ms"
                    },
                    {
                        $name: "FAST_TRETRY_5p0ms",
                        bitValue: 3,
                        description: "5ms"
                    },
                ])
            },
            {
                $name: "SLOW_TRETRY",
                description: "Retry time (typical) for slow recovery from fault condition",
                bitWidth: 2,
                startBit: 2,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "SLOW_TRETRY_0p5s",
                        bitValue: 0,
                        description: "0.5s"
                    },
                    {
                        $name: "SLOW_TRETRY_1p0s",
                        bitValue: 1,
                        description: "1s"
                    },
                    {
                        $name: "SLOW_TRETRY_2p0s",
                        bitValue: 2,
                        description: "2s"
                    },
                    {
                        $name: "SLOW_TRETRY_5p0s",
                        bitValue: 3,
                        description: "5s"
                    },
                ])
            },
            {
                $name: "FLT_TCTRL_PARITY",
                description: "Parity Bit if SPI_PEN is set to '1' otherwise reserved",
                bitWidth: 1,
                startBit: 15,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "FLT_CLR_REG",
        registerName: "Fault Clear Register",
        offset: 0x17,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "FLT_CLR",
                description: "Clear latched faults",
                bitWidth: 1,
                startBit: 0,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "VMUV_WARN_THR",
        registerName: "VM Under Voltage Warn Threshold Register",
        offset: 0x18,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "VMUV_WARN_FTH",
                description: "VM under voltage warning falling threshold",
                bitWidth: 4,
                startBit: 0,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "VMUV_WARN_FTH_5p4V",
                        bitValue: 0x0,
                        description: "5.4V"
                    },
                    {
                        $name: "VMUV_WARN_FTH_6p0V",
                        bitValue: 0x1,
                        description: "6.0V"
                    },
                    {
                        $name: "VMUV_WARN_FTH_6p6V",
                        bitValue: 0x2,
                        description: "6.6V "
                    },
                    {
                        $name: "VMUV_WARN_FTH_7p2V",
                        bitValue: 0x3,
                        description: "7.2V"
                    },
                    {
                        $name: "VMUV_WARN_FTH_7p8V",
                        bitValue: 0x4,
                        description: "7.8V"
                    },
                    {
                        $name: "VMUV_WARN_FTH_8p4V",
                        bitValue: 0x5,
                        description: "8.4V"
                    },
                    {
                        $name: "VMUV_WARN_FTH_9p0V",
                        bitValue: 0x6,
                        description: "9.0V"
                    },
                    {
                        $name: "VMUV_WARN_FTH_9p6V",
                        bitValue: 0x7,
                        description: "9.6V"
                    },
                    {
                        $name: "VMUV_WARN_FTH_10p2V",
                        bitValue: 0x8,
                        description: "10.2V"
                    },
                    {
                        $name: "VMUV_WARN_FTH_10p8V",
                        bitValue: 0x9,
                        description: "10.8V"
                    },
                    {
                        $name: "VMUV_WARN_FTH_11p4V",
                        bitValue: 0xA,
                        description: "11.4V"
                    },
                    {
                        $name: "VMUV_WARN_FTH_12p0V",
                        bitValue: 0xB,
                        description: "12.0V"
                    },
                    {
                        $name: "VMUV_WARN_FTH_13p2V",
                        bitValue: 0xC,
                        description: "13.2V"
                    },
                    {
                        $name: "VMUV_WARN_FTH_14p4V",
                        bitValue: 0xD,
                        description: "14.4V"
                    },
                    {
                        $name: "VMUV_WARN_FTH_15p6V",
                        bitValue: 0xE,
                        description: "15.6V"
                    },
                    {
                        $name: "VMUV_WARN_FTH_16p8V",
                        bitValue: 0xF,
                        description: "16.8V"
                    },
                ])
            },
            {
                $name: "VMUV_WARN_RTH",
                description: "VM under voltage warning rising threshold",
                bitWidth: 4,
                startBit: 4,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "VMUV_WARN_RTH_5p62V",
                        bitValue: 0x0,
                        description: "5.62V"
                    },
                    {
                        $name: "VMUV_WARN_RTH_6p25V",
                        bitValue: 0x1,
                        description: "6.25V"
                    },
                    {
                        $name: "VMUV_WARN_RTH_6p87V",
                        bitValue: 0x2,
                        description: "6.87V "
                    },
                    {
                        $name: "VMUV_WARN_RTH_7p50V",
                        bitValue: 0x3,
                        description: "7.5V"
                    },
                    {
                        $name: "VMUV_WARN_RTH_8p12V",
                        bitValue: 0x4,
                        description: "8.12V"
                    },
                    {
                        $name: "VMUV_WARN_RTH_8p75V",
                        bitValue: 0x5,
                        description: "8.75V"
                    },
                    {
                        $name: "VMUV_WARN_RTH_9p37V",
                        bitValue: 0x6,
                        description: "9.37V"
                    },
                    {
                        $name: "VMUV_WARN_RTH_10p00V",
                        bitValue: 0x7,
                        description: "10.00V"
                    },
                    {
                        $name: "VMUV_WARN_RTH_10p62V",
                        bitValue: 0x8,
                        description: "10.62V"
                    },
                    {
                        $name: "VMUV_WARN_RTH_11p25V",
                        bitValue: 0x9,
                        description: "11.25V"
                    },
                    {
                        $name: "VMUV_WARN_RTH_11p87V",
                        bitValue: 0xA,
                        description: "11.87V"
                    },
                    {
                        $name: "VMUV_WARN_RTH_12p50V",
                        bitValue: 0xB,
                        description: "12.5V"
                    },
                    {
                        $name: "VMUV_WARN_RTH_13p75V",
                        bitValue: 0xC,
                        description: "13.75V"
                    },
                    {
                        $name: "VMUV_WARN_RTH_15p00V",
                        bitValue: 0xD,
                        description: "15.00V"
                    },
                    {
                        $name: "VMUV_WARN_RTH_16p25V",
                        bitValue: 0xE,
                        description: "16.25V"
                    },
                    {
                        $name: "VMUV_WARN_RTH_17p50V",
                        bitValue: 0xF,
                        description: "17.5V"
                    },
                ])
            },
            {
                $name: "VMUV_WARN_THR_PARITY",
                description: "Parity Bit if SPI_PEN is set to '1' otherwise reserved",
                bitWidth: 1,
                startBit: 15,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "PWM_CTRL",
        registerName: "PWM Control Register",
        offset: 0x20,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "PWM_MODE",
                description: "PWM mode selection",
                bitWidth: 2,
                startBit: 0,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "PWM_MODE_6",
                        bitValue: 0,
                        description: "6x mode"
                    },
                    {
                        $name: "PWM_MODE_6D",
                        bitValue: 1,
                        description: "6x direct mode"
                    },
                    {
                        $name: "PWM_MODE_3",
                        bitValue: 2,
                        description: "3x mode"
                    },
                    {
                        $name: "PWM_MODE_3D",
                        bitValue: 3,
                        description: "3x direct mode"
                    },
                ])
            },
            {
                $name: "SSC_DIS",
                description: "Disable SSC on oscillator",
                bitWidth: 1,
                startBit: 2,
                enumEnable: false,
            },
            {
                $name: "PWM_CTRL_PARITY",
                description: "Parity Bit if SPI_PEN is set to '1' otherwise reserved",
                bitWidth: 1,
                startBit: 15,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "DRV_CTRL",
        registerName: "Predriver Control Register",
        offset: 0x22,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "SLEW_RATE",
                description: "Slew rate settings",
                bitWidth: 2,
                startBit: 0,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "SLEW_RATE_25V",
                        bitValue: 0,
                        description: "Slew rate is 25 V/uS"
                    },
                    {
                        $name: "SLEW_RATE_50V",
                        bitValue: 1,
                        description: "Slew rate is 50 V/uS"
                    },
                    {
                        $name: "SLEW_RATE_125V",
                        bitValue: 2,
                        description: "Slew rate is 125 V/uS"
                    },
                    {
                        $name: "SLEW_RATE_200V",
                        bitValue: 3,
                        description: "Slew rate is 200 V/uS"
                    },
                ])
            },
            {
                $name: "DLYCMP_EN",
                description: "Driver Delay Compensation enable",
                bitWidth: 1,
                startBit: 7,
                enumEnable: false,
            },
            {
                $name: "DLY_TARGET",
                description: "Delay Target : DLY_TARGET * 0.2µs",
                bitWidth: 4,
                startBit: 8,
                enumEnable: false,
            },
            {
                $name: "DRV_CTRL_PARITY",
                description: "Parity Bit if SPI_PEN is set to '1' otherwise reserved",
                bitWidth: 1,
                startBit: 15,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "CSA_CTRL",
        registerName: "CSA Control Register",
        offset: 0x23,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "CSA_GAIN",
                description: "CSA Gain settings",
                bitWidth: 2,
                startBit: 0,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "CSA_GAIN_0p25VpA",
                        bitValue: 0,
                        description: "CSA gain is 0.25 V/A"
                    },
                    {
                        $name: "CSA_GAIN_0p50VpA",
                        bitValue: 1,
                        description: "CSA gain is 0.5 V/A"
                    },
                    {
                        $name: "CSA_GAIN_1p00VpA",
                        bitValue: 2,
                        description: "CSA gain is 1 V/A"
                    },
                    {
                        $name: "CSA_GAIN_2p00VpA",
                        bitValue: 3,
                        description: "CSA gain is 2 V/A"
                    },
                ])
            },
            {
                $name: "CSA_EN",
                description: "Enable CSA",
                bitWidth: 1,
                startBit: 3,
                enumEnable: false,
            },
            {
                $name: "CSA_CTRL_PARITY",
                description: "Parity Bit if SPI_PEN is set to '1' otherwise reserved",
                bitWidth: 1,
                startBit: 15,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "SYS_CTRL",
        registerName: "System Control Register",
        offset: 0x3F,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "SPI_PEN",
                description: "Parity Enable for SPI",
                bitWidth: 1,
                startBit: 6,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "SPI_PEN_DISABLE",
                        bitValue: 0,
                        description: "Parity Disabled"
                    },
                    {
                        $name: "SPI_PEN_ENABLE",
                        bitValue: 1,
                        description: "Parity Enabled"
                    },
                ])
            },
            {
                $name: "REG_LOCK",
                description: "Register Lock Bit",
                bitWidth: 1,
                startBit: 7,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "REG_LOCK_UNLOCK",
                        bitValue: 0,
                        description: "Registers Unlocked"
                    },
                    {
                        $name: "REG_LOCK_LOCK",
                        bitValue: 1,
                        description: "Registers Locked"
                    },
                ])
            },
            {
                $name: "SYS_CTRL_PARITY",
                description: "Parity Bit if SPI_PEN is set to '1' otherwise reserved",
                bitWidth: 1,
                startBit: 15,
                enumEnable: false,
            },
        ])
    },
]

function getDRV8317SpiSettings(inst) {
    return {
        $name: "DRV8317_SPI_Interface",
        spiFrameSize: "24bits",
        rwSelect24Bits: [23],
        readBitValue: 1,
        writeBitValue: 0,
        addressSelect24Bits: [22, 21, 20, 19, 18, 17],
        dataSelect24Bits: [14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0],
        crcMode: "parity",
        crcSelect24Bits: [16, 15],
        hiddenTextFieldForRegisterArgs: JSON.stringify(drv8317Registers),
	}
}

exports = {
	getDRV8317SpiSettings,
};