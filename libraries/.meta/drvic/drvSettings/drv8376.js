let Common = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let references = system.getScript("/libraries/MCSDKLibraryReferences.js");

let drv8376Registers = [
    {
        $name: "DEV_STS",
        registerName: "Device Status Register",
        offset: 0x0,
        registerType: "status",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "FAULT",
                description: "Device Fault status",
                bitWidth: 1,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "OTF",
                description: "Overtemperature Fault Status",
                bitWidth: 1,
                startBit: 1,
                enumEnable: false,
            },
            {
                $name: "UVP",
                description: "Supply Undervoltage Status",
                bitWidth: 1,
                startBit: 2,
                enumEnable: false,
            },
            {
                $name: "OVP",
                description: "Over Voltage Status",
                bitWidth: 1,
                startBit: 3,
                enumEnable: false,
            },
            {
                $name: "OCP",
                description: "Overcurrent Status",
                bitWidth: 1,
                startBit: 5,
                enumEnable: false,
            },
            {
                $name: "SPIFLT",
                description: "SPI Fault status",
                bitWidth: 1,
                startBit: 6,
                enumEnable: false,
            },
            {
                $name: "RESET",
                description: "Device Reset status",
                bitWidth: 1,
                startBit: 7,
                enumEnable: false,
            },
            {
                $name: "SYSFLT",
                description: "OTP Read fault occurred",
                bitWidth: 1,
                startBit: 8,
                enumEnable: false,
            },
            {
                $name: "DNRDY_STS",
                description: "Device Not Ready Status",
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
                description: "Overtemperature Shutdown Raw Fault Status",
                bitWidth: 1,
                startBit: 1,
                enumEnable: false,
            },
            {
                $name: "UVP_RSTS",
                description: "CP Undervoltage Raw Fault Status",
                bitWidth: 1,
                startBit: 2,
                enumEnable: false,
            },
            {
                $name: "OVP_RSTS",
                description: "Over Voltage Raw Fault Status",
                bitWidth: 1,
                startBit: 3,
                enumEnable: false,
            },
            {
                $name: "OCP_RSTS",
                description: "Overcurrent Fault Raw Status",
                bitWidth: 1,
                startBit: 5,
                enumEnable: false,
            },
            {
                $name: "SPIFLT_RSTS",
                description: "SPI Fault status",
                bitWidth: 1,
                startBit: 6,
                enumEnable: false,
            },
            {
                $name: "RESET_RSTS",
                description: "Device power on status",
                bitWidth: 1,
                startBit: 7,
                enumEnable: false,
            },
            {
                $name: "SYSFLT_RSTS",
                description: "OTP Read fault occurred",
                bitWidth: 1,
                startBit: 8,
                enumEnable: false,
            },
            {
                $name: "DNRDY_RSTS",
                description: "Device Not Ready Status",
                bitWidth: 1,
                startBit: 9,
                enumEnable: false,
            },
            {
                $name: "OTW_RSTS",
                description: "OT Warning Raw Status",
                bitWidth: 1,
                startBit: 11,
                enumEnable: false,
            },
            {
                $name: "DRVOFF_RSTS",
                description: "Status of DRV_OFF pin",
                bitWidth: 1,
                startBit: 12,
                enumEnable: false,
            },
            {
                $name: "DEV_RSTS_PARITY",
                description: "Parity Bit if SPI_PEN is set to '1' otherwise reserved",
                bitWidth: 1,
                startBit: 15,
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
                $name: "OTSD",
                description: "Overtemperature Shutdown Fault status",
                bitWidth: 1,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "OTW",
                description: "Overtemperature Warning Fault status",
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
                $name: "CP_UV",
                description: "Charge Pump Undervoltage fault status",
                bitWidth: 1,
                startBit: 4,
                enumEnable: false,
            },
            {
                $name: "VM_OV",
                description: "Vm Over Voltage Fault Status",
                bitWidth: 1,
                startBit: 6,
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
                description: "Overcurrent Status on Low-side switch of OUTA",
                bitWidth: 1,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "OCPB_LS",
                description: "Overcurrent Status on Low-side switch of OUTB",
                bitWidth: 1,
                startBit: 1,
                enumEnable: false,
            },
            {
                $name: "OCPC_LS",
                description: "Overcurrent Status on Low-side switch of OUTC",
                bitWidth: 1,
                startBit: 2,
                enumEnable: false,
            },
            {
                $name: "OCPA_HS",
                description: "Overcurrent Status on High-side switch of OUTA",
                bitWidth: 1,
                startBit: 4,
                enumEnable: false,
            },
            {
                $name: "OCPB_HS",
                description: "Overcurrent Status on High-side switch of OUTB",
                bitWidth: 1,
                startBit: 5,
                enumEnable: false,
            },
            {
                $name: "OCPC_HS",
                description: "Overcurrent Status on High-side switch of OUTC",
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
                description: "SPI Frame Error",
                bitWidth: 1,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "SPI_PARITY",
                description: "SPI Parity Error",
                bitWidth: 1,
                startBit: 2,
                enumEnable: false,
            },
            {
                $name: "OTPLD_ERR",
                description: "OTP CRC error during load",
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
                $name: "OTW_MODE",
                description: "Overtemperature Warning Fault mode",
                bitWidth: 1,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "OCP_MODE",
                description: "Overcurrent Protection Fault mode",
                bitWidth: 2,
                startBit: 4,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "OCP_MODE_LATCH",
                        bitValue: 0,
                        description: "Over Current causes a latched fault"
                    },
                    {
                        $name: "OCP_MODE_RETRY",
                        bitValue: 1,
                        description: "Over Current causes an automatic retrying fault"
                    },
                    {
                        $name: "OCP_MODE_REPORT_ONLY",
                        bitValue: 2,
                        description: "Over Current is report only but no action is taken"
                    },
                    {
                        $name: "OCP_MODE_NO_REPORT",
                        bitValue: 3,
                        description: "Over Current is not reported and no action is taken"
                    },
                ])
            },
            {
                $name: "SPIFLT_MODE",
                description: "SPI Fault mode",
                bitWidth: 1,
                startBit: 7,
                enumEnable: false,
            },
            {
                $name: "OVP_MODE",
                description: "Over Voltage Protection Fault mode",
                bitWidth: 1,
                startBit: 9,
                enumEnable: false,
            },
            {
                $name: "ILIMFLT_MODE",
                description: "ILIMIT Fault mode",
                bitWidth: 1,
                startBit: 13,
                enumEnable: false,
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
        $name: "DRVF_CTRL",
        registerName: "Driver Fault Control Register",
        offset: 0x13,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "OCP_LVL",
                description: "OCP Level",
                bitWidth: 1,
                startBit: 0,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "OCP_LVL_4p5A",
                        bitValue: 0,
                        description: "4.5A"
                    },
                    {
                        $name: "OCP_LVL_2p5A",
                        bitValue: 1,
                        description: "2.5A"
                    },
                ])
            },
            {
                $name: "OCP_TRETRY",
                description: "OCP Retry Time",
                bitWidth: 1,
                startBit: 2,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "OCP_TRETRY_5ms",
                        bitValue: 0,
                        description: "5ms"
                    },
                    {
                        $name: "OCP_TRETRY_500ms",
                        bitValue: 1,
                        description: "500ms"
                    },
                ])
            },
            {
                $name: "OCP_DEG",
                description: "OCP Deglitch time",
                bitWidth: 2,
                startBit: 4,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "OCP_DEG_0p60us",
                        bitValue: 0,
                        description: "OCP Deglitch time is 0.6 µs"
                    },
                    {
                        $name: "OCP_DEG_1p25us",
                        bitValue: 1,
                        description: "OCP Deglitch time is 1.25 µs"
                    },
                    {
                        $name: "OCP_DEG_1p60us",
                        bitValue: 2,
                        description: "OCP Deglitch time is 1.6 µs"
                    },
                    {
                        $name: "OCP_DEG_2p00us",
                        bitValue: 3,
                        description: "OCP Deglitch time is 2 µs"
                    },
                ])
            },
            {
                $name: "OVP_SEL",
                description: "Overvoltage level setting",
                bitWidth: 1,
                startBit: 8,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "OVP_SEL_65V",
                        bitValue: 0,
                        description: "VM overvoltage level is 65V"
                    },
                    {
                        $name: "OVP_SEL_35V",
                        bitValue: 1,
                        description: "VM overvoltage level is 35V"
                    },
                ])
            },
            {
                $name: "DRVF_CTRL_PARITY",
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
            {
                $name: "FLT_CLR_PARITY",
                description: "Parity Bit if SPI_PEN is set to '1' otherwise reserved",
                bitWidth: 1,
                startBit: 15,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "PWM_CTRL1",
        registerName: "PWM Control Register 1",
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
                        $name: "PWM_MODE_6_MODE",
                        bitValue: 0,
                        description: "6x mode"
                    },
                    {
                        $name: "PWM_MODE_6_MODE2",
                        bitValue: 1,
                        description: "6x mode"
                    },
                    {
                        $name: "PWM_MODE_3_MODE",
                        bitValue: 2,
                        description: "3x mode"
                    },
                    {
                        $name: "PWM_MODE_3_MODE2",
                        bitValue: 3,
                        description: "3x mode"
                    },
                ])
            },
            {
                $name: "EN_ASR",
                description: "Actie Demag Enable",
                bitWidth: 1,
                startBit: 2,
                enumEnable: false,
            },
            {
                $name: "EN_AAR",
                description: "Enable AAR where LS FET gets turned off when current goes negative",
                bitWidth: 1,
                startBit: 3,
                enumEnable: false,
            },
            {
                $name: "ILIM_MODE",
                description: "Current limit recirculation settings",
                bitWidth: 1,
                startBit: 5,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "ILIM_MODE_BRAKE",
                        bitValue: 0,
                        description: "Current recirculation through FETs (Brake mode)"
                    },
                    {
                        $name: "ILIM_MODE_COAST",
                        bitValue: 1,
                        description: "Current recirculation through diodes (coast mode)"
                    },
                ])
            },
            {
                $name: "PWM_100_FREQ_SEL",
                description: "Frequency of PWM at 100% Duty cycle",
                bitWidth: 2,
                startBit: 6,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "PWM_100_FREQ_SEL_20KHz",
                        bitValue: 0,
                        description: "20KHz"
                    },
                    {
                        $name: "PWM_100_FREQ_SEL_40KHz",
                        bitValue: 1,
                        description: "40KHz"
                    },
                    {
                        $name: "PWM_100_FREQ_SEL_10KHz",
                        bitValue: 2,
                        description: "10KHz"
                    },
                    {
                        $name: "PWM_100_FREQ_SEL_NONE",
                        bitValue: 3,
                        description: "None"
                    },
                ])
            },
            {
                $name: "PWM_CTRL1_PARITY",
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
                        $name: "SLEW_RATE_1100V",
                        bitValue: 0,
                        description: "Slew rate is 1100 V/uS"
                    },
                    {
                        $name: "SLEW_RATE_500V",
                        bitValue: 1,
                        description: "Slew rate is 500 V/uS"
                    },
                    {
                        $name: "SLEW_RATE_250V",
                        bitValue: 2,
                        description: "Slew rate is 250 V/uS"
                    },
                    {
                        $name: "SLEW_RATE_50V",
                        bitValue: 3,
                        description: "Slew rate is 50 V/uS"
                    },
                ])
            },
            {
                $name: "AD_COMP_TH_LS",
                description: "Active demag low side comparator threshold",
                bitWidth: 1,
                startBit: 2,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "AD_COMP_TH_LS_100mA",
                        bitValue: 0,
                        description: "Active demag comparator threshold is 100mA"
                    },
                    {
                        $name: "AD_COMP_TH_LS_150mA",
                        bitValue: 1,
                        description: "Active demag comparator threshold is 150mA"
                    },
                ])
            },
            {
                $name: "AD_COMP_TH_HS",
                description: "Active demag high side comparator threshold",
                bitWidth: 1,
                startBit: 3,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "AD_COMP_TH_HS_100mA",
                        bitValue: 0,
                        description: "Active demag comparator threshold is 100mA"
                    },
                    {
                        $name: "AD_COMP_TH_HS_150mA",
                        bitValue: 1,
                        description: "Active demag comparator threshold is 150mA"
                    },
                ])
            },
            {
                $name: "ADMAG_TMARGIN",
                description: "Wait time before determining HiZ. N*4*100ns",
                bitWidth: 4,
                startBit: 4,
                enumEnable: false,
            },
            {
                $name: "ILIM_BLANK_SEL",
                description: "Current Limit Blanking Time Selection",
                bitWidth: 3,
                startBit: 8,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "ILIM_BLANK_SEL_5p5us_1p8us",
                        bitValue: 0,
                        description: "5.5us for slew rate of 50 and 1.8us for all other slew rates"
                    },
                    {
                        $name: "ILIM_BLANK_SEL_6p0us_2p3us",
                        bitValue: 1,
                        description: "6.0us for slew rate of 50 and 2.3us for all other slew rates"
                    },
                    {
                        $name: "ILIM_BLANK_SEL_6p5us_2p8us",
                        bitValue: 2,
                        description: "6.5us for slew rate of 50 and 2.8us for all other slew rates"
                    },
                    {
                        $name: "ILIM_BLANK_SEL_7p5us_3p8us",
                        bitValue: 3,
                        description: "7.5us for slew rate of 50 and 3.8us for all other slew rates"
                    },
                ])
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
                        $name: "CSA_GAIN_0p4VpA",
                        bitValue: 0,
                        description: "CSA gain is 0.4 V/A"
                    },
                    {
                        $name: "CSA_GAIN_1p0VpA",
                        bitValue: 1,
                        description: "CSA gain is 1.0 V/A"
                    },
                    {
                        $name: "CSA_GAIN_2p5VpA",
                        bitValue: 2,
                        description: "CSA gain is 2.5 V/A"
                    },
                    {
                        $name: "CSA_GAIN_5p0VpA",
                        bitValue: 3,
                        description: "CSA gain is 5.0 V/A"
                    },
                ])
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
                $name: "SDO_ODEN",
                description: "SDO in Open Drain Mode",
                bitWidth: 1,
                startBit: 10,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "SDO_ODEN_PUSH_PULL",
                        bitValue: 0,
                        description: "SDO in Push Pull Mode"
                    },
                    {
                        $name: "SDO_ODEN_OPEN_DRAIN",
                        bitValue: 1,
                        description: "SDO in Open Drain Mode"
                    },
                ])
            },
            {
                $name: "SDO_VSEL",
                description: "SDO Output Voltage Select",
                bitWidth: 1,
                startBit: 11,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "SDO_VSEL_AVDD",
                        bitValue: 0,
                        description: "AVDD"
                    },
                    {
                        $name: "SDO_VSEL_GVDD",
                        bitValue: 1,
                        description: "GVDD"
                    },
                ])
            },
            {
                $name: "WRITE_KEY",
                description: "0x5 Write Key Specific to this register",
                bitWidth: 3,
                startBit: 12,
                enumEnable: false,
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

function getDRV8376SpiSettings(inst) {
    return {
        $name: "DRV8376_SPI_Interface",
        spiFrameSize: "24bits",
        rwSelect24Bits: [16],
        readBitValue: 1,
        writeBitValue: 0,
        addressSelect24Bits: [22, 21, 20, 19, 18, 17],
        dataSelect24Bits: [14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0],
        crcMode: "parity",
        crcSelect24Bits: [23, 15],
        hiddenTextFieldForRegisterArgs: JSON.stringify(drv8376Registers),
	}
}

exports = {
	getDRV8376SpiSettings,
};