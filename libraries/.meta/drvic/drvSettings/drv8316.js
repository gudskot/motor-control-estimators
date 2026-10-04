let Common = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let references = system.getScript("/libraries/MCSDKLibraryReferences.js");

let drv8316Registers = [
    {
        $name: "IC_STS",
        registerName: "IC Status Register",
        offset: 0x0,
        registerType: "status",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "FAULT",
                description: "Device Fault Bit",
                bitWidth: 1,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "OT",
                description: "Overtemperature Fault Status Bit",
                bitWidth: 1,
                startBit: 1,
                enumEnable: false,
            },
            {
                $name: "OVP",
                description: "Supply Overvoltage Protection Status Bit",
                bitWidth: 1,
                startBit: 2,
                enumEnable: false,
            },
            {
                $name: "NPOR",
                description: "Supply Power On Reset Bit",
                bitWidth: 1,
                startBit: 3,
                enumEnable: false,
            },
            {
                $name: "OCP",
                description: "Over Current Protection Status Bit",
                bitWidth: 1,
                startBit: 4,
                enumEnable: false,
            },
            {
                $name: "SPI_FLT",
                description: "SPI Fault Bit",
                bitWidth: 1,
                startBit: 5,
                enumEnable: false,
            },
            {
                $name: "BK_FLT",
                description: "Buck Fault Bit",
                bitWidth: 1,
                startBit: 6,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "STS1",
        registerName: "Status Register 1",
        offset: 0x1,
        registerType: "status",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "OCP_LA",
                description: "Overcurrent Status on Low-side switch of OUTA",
                bitWidth: 1,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "OCP_HA",
                description: "Overcurrent Status on High-side switch of OUTA",
                bitWidth: 1,
                startBit: 1,
                enumEnable: false,
            },
            {
                $name: "OCP_LB",
                description: "Overcurrent Status on Low-side switch of OUTB",
                bitWidth: 1,
                startBit: 2,
                enumEnable: false,
            },
            {
                $name: "OCP_HB",
                description: "Overcurrent Status on High-side switch of OUTB",
                bitWidth: 1,
                startBit: 3,
                enumEnable: false,
            },
            {
                $name: "OCP_LC",
                description: "Overcurrent Status on Low-side switch of OUTC",
                bitWidth: 1,
                startBit: 4,
                enumEnable: false,
            },
            {
                $name: "OCP_HC",
                description: "Overcurrent Status on High-side switch of OUTC",
                bitWidth: 1,
                startBit: 5,
                enumEnable: false,
            },
            {
                $name: "OTS",
                description: "Overtemperature Shutdown Status Bit",
                bitWidth: 1,
                startBit: 6,
                enumEnable: false,
            },
            {
                $name: "OTW",
                description: "Overtemperature Warning Status Bit",
                bitWidth: 1,
                startBit: 7,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "STS2",
        registerName: "Status Register 2",
        offset: 0x2,
        registerType: "status",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "SPI_ADDR_FLT",
                description: "SPI Address Error Bit",
                bitWidth: 1,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "SPI_SCLK_FLT",
                description: "SPI Clock Framing Error Bit",
                bitWidth: 1,
                startBit: 1,
                enumEnable: false,
            },
            {
                $name: "SPI_PARITY",
                description: "SPI Parity Error Bit",
                bitWidth: 1,
                startBit: 2,
                enumEnable: false,
            },
            {
                $name: "VCP_UV",
                description: "Charge Pump Undervoltage Status Bit",
                bitWidth: 1,
                startBit: 3,
                enumEnable: false,
            },
            {
                $name: "BUCK_UV",
                description: "Buck Regulator Undervoltage Staus Bit",
                bitWidth: 1,
                startBit: 4,
                enumEnable: false,
            },
            {
                $name: "BUCK_OCP",
                description: "Buck Regulator Overcurrent Staus Bit",
                bitWidth: 1,
                startBit: 5,
                enumEnable: false,
            },
            {
                $name: "OTP_ERR",
                description: "One Time Programmabilty Error",
                bitWidth: 1,
                startBit: 6,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "CTRL1",
        registerName: "Control Register 1",
        offset: 0x3,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "REG_LOCK",
                description: "Register Lock Bits",
                bitWidth: 3,
                startBit: 0,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "REG_LOCK_UNLOCK",
                        bitValue: 3,
                        description: "Write 011b to this register to unlock all registers"
                    },
                    {
                        $name: "REG_LOCK_LOCK",
                        bitValue: 6,
                        description: "Write 110b to lock the settings by ignoring further register writes except to these bits and address 0x03h bits 2-0",
                    },
                ])
            },
        ])
    },
    {
        $name: "CTRL2",
        registerName: "Control Register 2",
        offset: 0x4,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "CLR_FLT",
                description: "Clear Fault",
                bitWidth: 1,
                startBit: 0,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "CLR_FLT_NO",
                        bitValue: 0,
                        description: "No clear fault command is issued"
                    },
                    {
                        $name: "CLR_FLT_CLEAR",
                        bitValue: 1,
                        description: "To clear the latched fault bits"
                    },
                ])
            },
            {
                $name: "PWM_MODE",
                description: "Device Mode Selection",
                bitWidth: 2,
                startBit: 1,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "PWM_MODE_6_N",
                        bitValue: 0,
                        description: "PWM_MODE = 6 inputs"
                    },
                    {
                        $name: "PWM_MODE_6_LC",
                        bitValue: 1,
                        description: "PWM_MODE = 6 inputs with current limit"
                    },
                    {
                        $name: "PWM_MODE_3_N",
                        bitValue: 2,
                        description: "PWM_MODE = 3 inputs"
                    },
                    {
                        $name: "PWM_MODE_3_LC",
                        bitValue: 3,
                        description: "PWM_MODE = 3 inputs with current limit"
                    },
                ])
            },
            {
                $name: "SLEW",
                description: "Slew Rate Settings",
                bitWidth: 2,
                startBit: 3,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "SLEW_25V",
                        bitValue: 0,
                        description: "Slew rate is 25 V/uS"
                    },
                    {
                        $name: "SLEW_50V",
                        bitValue: 1,
                        description: "Slew rate is 50 V/uS"
                    },
                    {
                        $name: "SLEW_150V",
                        bitValue: 2,
                        description: "Slew rate is 150 V/uS"
                    },
                    {
                        $name: "SLEW_200V",
                        bitValue: 3,
                        description: "Slew rate is 200 V/uS"
                    },
                ])
            },
            {
                $name: "SDO_MODE",
                description: "SDO Mode Setting",
                bitWidth: 1,
                startBit: 5,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "SDO_MODE_OPEN_DRAIN",
                        bitValue: 0,
                        description: "SDO IO in Open Drain Mode"
                    },
                    {
                        $name: "SDO_MODE_PUSH_PULL",
                        bitValue: 1,
                        description: "SDO IO in Push Pull Mode"
                    },
                ])
            },
        ])
    },
    {
        $name: "CTRL3",
        registerName: "Control Register 3",
        offset: 0x5,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "OTW_REP",
                description: "Overtemperature Warning Reporting Bit",
                bitWidth: 1,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "OVP_EN",
                description: "Overvoltage Enable Bit",
                bitWidth: 1,
                startBit: 2,
                enumEnable: false,
            },
            {
                $name: "OVP_SEL",
                description: "Overvoltage Level Setting",
                bitWidth: 1,
                startBit: 3,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "OVP_SEL_32V",
                        bitValue: 0,
                        description: "VM overvoltage level is 32-V"
                    },
                    {
                        $name: "OVP_SEL_20V",
                        bitValue: 1,
                        description: "VM overvoltage level is 20-V"
                    },
                ])
            },
            {
                $name: "PWM_100_DUTY_SEL",
                description: "Freqency of PWM at 100% Duty Cycle",
                bitWidth: 1,
                startBit: 4,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "PWM_100_DUTY_SEL_20KHz",
                        bitValue: 0,
                        description: "20KHz"
                    },
                    {
                        $name: "PWM_100_DUTY_SEL_40KHz",
                        bitValue: 1,
                        description: "40KHz"
                    },
                ])
            },
        ])
    },
    {
        $name: "CTRL4",
        registerName: "Control Register 4",
        offset: 0x6,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "OCP_MODE",
                description: "OCP Fault Options",
                bitWidth: 2,
                startBit: 0,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "OCP_MODE_LATCH",
                        bitValue: 0,
                        description: "Overcurrent causes a latched fault"
                    },
                    {
                        $name: "OCP_MODE_RETRY",
                        bitValue: 1,
                        description: "Overcurrent causes an automatic retrying fault"
                    },
                    {
                        $name: "OCP_MODE_REPORT",
                        bitValue: 2,
                        description: "Overcurrent is report only but no action is taken"
                    },
                    {
                        $name: "OCP_MODE_NO",
                        bitValue: 3,
                        description: "Overcurrent is not reported and no action is taken"
                    },
                ])
            },
            {
                $name: "OCP_LVL",
                description: "Overcurrent Level Setting",
                bitWidth: 1,
                startBit: 2,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "OCP_LVL_16A",
                        bitValue: 0,
                        description: "16A"
                    },
                    {
                        $name: "OCP_LVL_24A",
                        bitValue: 1,
                        description: "24A"
                    },
                ])
            },
            {
                $name: "OCP_RETRY",
                description: "OCP Retry Time Settings",
                bitWidth: 1,
                startBit: 3,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "OCP_RETRY_5ms",
                        bitValue: 0,
                        description: "OCP retry time is 5 ms"
                    },
                    {
                        $name: "OCP_RETRY_500ms",
                        bitValue: 1,
                        description: "OCP retry time is 500 ms"
                    },
                ])
            },
            {
                $name: "OCP_DEG",
                description: "OCP Deglitch Time Settings",
                bitWidth: 2,
                startBit: 4,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "OCP_DEG_0p2us",
                        bitValue: 0,
                        description: "OCP deglitch time is 0.2 μs"
                    },
                    {
                        $name: "OCP_DEG_0p6us",
                        bitValue: 1,
                        description: "OCP deglitch time is 0.6 μs"
                    },
                    {
                        $name: "OCP_DEG_1p1us",
                        bitValue: 2,
                        description: "OCP deglitch time is 1.1 μs"
                    },
                    {
                        $name: "OCP_DEG_1p6us",
                        bitValue: 3,
                        description: "OCP deglitch time is 1.6 μs"
                    },
                ])
            },
            {
                $name: "OCP_CBC",
                description: "OCP PWM Cycle Operation Bit",
                bitWidth: 1,
                startBit: 6,
                enumEnable: false,
            },
            {
                $name: "DRV_OFF",
                description: "Driver OFF Bit",
                bitWidth: 1,
                startBit: 7,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "CTRL5",
        registerName: "Control Register 5",
        offset: 0x7,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "CSA_GAIN",
                description: "Current Sense Amplifier's Gain Settings",
                bitWidth: 2,
                startBit: 0,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "CSA_GAIN_0p15VpA",
                        bitValue: 0,
                        description: "CSA gain is 0.15 V/A"
                    },
                    {
                        $name: "CSA_GAIN_0p30VpA",
                        bitValue: 1,
                        description: "CSA gain is 0.30 V/A"
                    },
                    {
                        $name: "CSA_GAIN_0p60VpA",
                        bitValue: 2,
                        description: "CSA gain is 0.60 V/A"
                    },
                    {
                        $name: "CSA_GAIN_1p20VpA",
                        bitValue: 3,
                        description: "CSA gain is 1.20 V/A"
                    },
                ])
            },
            {
                $name: "EN_ASR",
                description: "Active Synchronous Rectification Enable Bit",
                bitWidth: 1,
                startBit: 2,
                enumEnable: false,
            },
            {
                $name: "EN_AAR",
                description: "Active Asynshronous Rectification Enable Bit",
                bitWidth: 1,
                startBit: 3,
                enumEnable: false,
            },
            {
                $name: "ILIM_RECIR",
                description: "Current Limit Recirculation Settings",
                bitWidth: 1,
                startBit: 6,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "ILIM_RECIR_Brake",
                        bitValue: 0,
                        description: "Current recirculation through FETs (Brake Mode)"
                    },
                    {
                        $name: "ILIM_RECIR_Coast",
                        bitValue: 1,
                        description: "Current recirculation through diodes (Coast Mode)"
                    },
                ])
            },
        ])
    },
    {
        $name: "CTRL6",
        registerName: "Control Register 6",
        offset: 0x8,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "BUCK_DIS",
                description: "Buck Disable Bit",
                bitWidth: 1,
                startBit: 0,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "BUCK_DIS_ENABLE",
                        bitValue: 0,
                        description: "Buck regulator is enabled"
                    },
                    {
                        $name: "BUCK_DIS_DISABLE",
                        bitValue: 1,
                        description: "Buck regulator is disabled"
                    },
                ])                
            },
            {
                $name: "BUCK_SEL",
                description: "Buck Voltage Selection",
                bitWidth: 2,
                startBit: 1,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "BUCK_SEL_3p3V",
                        bitValue: 0,
                        description: "Buck voltage is 3.3 V"
                    },
                    {
                        $name: "BUCK_SEL_5p0V",
                        bitValue: 1,
                        description: "Buck voltage is 5.0 V"
                    },
                    {
                        $name: "BUCK_SEL_4p0V",
                        bitValue: 2,
                        description: "Buck voltage is 4.0 V"
                    },
                    {
                        $name: "BUCK_SEL_5p7V",
                        bitValue: 3,
                        description: "Buck voltage is 5.7 V"
                    },
                ])
            },
            {
                $name: "BUCK_CL",
                description: "Buck Current Limit Setting",
                bitWidth: 1,
                startBit: 3,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "BUCK_CL_600mA",
                        bitValue: 0,
                        description: "Buck regulator current limit is set to 600 mA"
                    },
                    {
                        $name: "BUCK_CL_150mA",
                        bitValue: 1,
                        description: "Buck regulator current limit is set to 150 mA"
                    },
                ])
            },
            {
                $name: "BUCK_PS_DIS",
                description: "Buck Power Sequencing Disable Bit",
                bitWidth: 1,
                startBit: 4,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "CTRL10",
        registerName: "Control Register 10",
        offset: 0xC,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "DLY_TARGET",
                description: "Delay Target for Driver Delay Compensation",
                bitWidth: 4,
                startBit: 0,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "DLY_TARGET_0p0us",
                        bitValue: 0,
                        description: "Delay is 0 us"
                    },
                    {
                        $name: "DLY_TARGET_0p4us",
                        bitValue: 1,
                        description: "Delay is 0.4 us"
                    },
                    {
                        $name: "DLY_TARGET_0p6us",
                        bitValue: 2,
                        description: "Delay is 0.6 us"
                    },
                    {
                        $name: "DLY_TARGET_0p8us",
                        bitValue: 3,
                        description: "Delay is 0.8 us"
                    },
                    {
                        $name: "DLY_TARGET_1p0us",
                        bitValue: 4,
                        description: "Delay is 1.0 us"
                    },
                    {
                        $name: "DLY_TARGET_1p2us",
                        bitValue: 5,
                        description: "Delay is 1.2 us"
                    },
                    {
                        $name: "DLY_TARGET_1p4us",
                        bitValue: 6,
                        description: "Delay is 1.4 us"
                    },
                    {
                        $name: "DLY_TARGET_1p6us",
                        bitValue: 7,
                        description: "Delay is 1.6 us"
                    },
                    {
                        $name: "DLY_TARGET_1p8us",
                        bitValue: 8,
                        description: "Delay is 1.8 us"
                    },
                    {
                        $name: "DLY_TARGET_2p0us",
                        bitValue: 9,
                        description: "Delay is 2.0 us"
                    },
                    {
                        $name: "DLY_TARGET_2p2us",
                        bitValue: 10,
                        description: "Delay is 2.2 us"
                    },
                    {
                        $name: "DLY_TARGET_2p4us",
                        bitValue: 11,
                        description: "Delay is 2.4 us"
                    },
                    {
                        $name: "DLY_TARGET_2p6us",
                        bitValue: 12,
                        description: "Delay is 2.6 us"
                    },
                    {
                        $name: "DLY_TARGET_2p8us",
                        bitValue: 13,
                        description: "Delay is 2.8 us"
                    },
                    {
                        $name: "DLY_TARGET_3p0us",
                        bitValue: 14,
                        description: "Delay is 3.0 us"
                    },
                    {
                        $name: "DLY_TARGET_3p2us",
                        bitValue: 15,
                        description: "Delay is 3.2 us"
                    },
                ])
            },
            {
                $name: "DLYCMP_EN",
                description: "Driver Delay Compensation enable",
                bitWidth: 1,
                startBit: 4,
                enumEnable: false,
            },
        ])
    },
]

function getDRV8316SpiSettings(inst) {
    return {
        $name: "DRV8316_SPI_Interface",
        spiFrameSize: "16bits",
        rwSelect16Bits: [15],
        readBitValue: 1,
        writeBitValue: 0,
        addressSelect16Bits: [14, 13, 12, 11, 10, 9],
        dataSelect16Bits: [7, 6, 5, 4, 3, 2, 1, 0],
        crcMode: "parity",
        crcSelect16Bits: [8],
        hiddenTextFieldForRegisterArgs: JSON.stringify(drv8316Registers),
	}
}

exports = {
	getDRV8316SpiSettings,
};