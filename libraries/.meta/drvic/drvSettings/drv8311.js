let Common = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let references = system.getScript("/libraries/MCSDKLibraryReferences.js");

let drv8311Registers = [
    {
        $name: "DEV_STS1",
        registerName: "Device Status 1 Register",
        offset: 0x0,
        registerType: "status",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "FAULT",
                description: "Device Fault Status",
                bitWidth: 1,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "OT",
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
                $name: "OCP",
                description: "Driver Overcurrent Protection Status",
                bitWidth: 1,
                startBit: 5,
                enumEnable: false,
            },
            {
                $name: "SPI_FLT",
                description: "SPI Fault Status",
                bitWidth: 1,
                startBit: 6,
                enumEnable: false,
            },
            {
                $name: "RESET",
                description: "Supply Power On Reset Status",
                bitWidth: 1,
                startBit: 7,
                enumEnable: false,
            },
            {
                $name: "OTP_FLT",
                description: "OTP read fault",
                bitWidth: 1,
                startBit: 8,
                enumEnable: false,
            },
            {
                $name: "DEV_STS1_PARITY",
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
                description: "Overtemperature Shutdown Fault Status",
                bitWidth: 1,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "OTW",
                description: "Overtemperature Warning Status",
                bitWidth: 1,
                startBit: 1,
                enumEnable: false,
            },
            {
                $name: "OTS_AVDD",
                description: "AVDD LDO Overtemperature Fault Status",
                bitWidth: 1,
                startBit: 2,
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
                $name: "VINAVDD_UV",
                description: "VIN_AVDD Undervoltage Fault Status",
                bitWidth: 1,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "AVDD_UV",
                description: "AVDD LDO Undervoltage Fault Status",
                bitWidth: 1,
                startBit: 2,
                enumEnable: false,
            },
            {
                $name: "CP_UV",
                description: "Charge Pump Undervoltage Fault Status",
                bitWidth: 1,
                startBit: 4,
                enumEnable: false,
            },
            {
                $name: "CSAREF_UV",
                description: "CSA REF Undervoltage Fault Status",
                bitWidth: 1,
                startBit: 5,
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
                description: "Overcurrent Status on Low-side MOSFET of OUTA",
                bitWidth: 1,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "OCPB_LS",
                description: "Overcurrent Status on Low-side MOSFET of OUTB",
                bitWidth: 1,
                startBit: 1,
                enumEnable: false,
            },
            {
                $name: "OCPC_LS",
                description: "Overcurrent Status on Low-side MOSFET of OUTC",
                bitWidth: 1,
                startBit: 2,
                enumEnable: false,
            },
            {
                $name: "OCPA_HS",
                description: "Overcurrent Status on High-side MOSFET of OUTA",
                bitWidth: 1,
                startBit: 4,
                enumEnable: false,
            },
            {
                $name: "OCPB_HS",
                description: "Overcurrent Status on High-side MOSFET of OUTB",
                bitWidth: 1,
                startBit: 5,
                enumEnable: false,
            },
            {
                $name: "OCPC_HS",
                description: "Overcurrent Status on High-side MOSFET of OUTC",
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
        $name: "SYS_STS",
        registerName: "System Status Register",
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
                $name: "BUS_CNT",
                description: "SPI Bus Contention Error",
                bitWidth: 1,
                startBit: 1,
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
                description: "OTP Read Error",
                bitWidth: 1,
                startBit: 4,
                enumEnable: false,
            },
            {
                $name: "SYS_STS_PARITY",
                description: "Parity Bit if SPI_PEN is set to '1' otherwise reserved",
                bitWidth: 1,
                startBit: 15,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "PWM_SYNC_PRD_REG",
        registerName: "PWM Sync Period Register",
        offset: 0xC,
        registerType: "status",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "PWM_SYNC_PRD",
                description: "12-bit output indicating period of PWM_SYNC signal",
                bitWidth: 12,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "PWM_SYNC_PRD_PARITY",
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
                $name: "OTSD_MODE",
                description: "Overtemperature Fault mode",
                bitWidth: 2,
                startBit: 0,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "OTSD_MODE_SLOW_RETRY",
                        bitValue: 0,
                        description: "Report on nFault, predriver HiZ, auto recovery with Slow Retry time (in ms)"
                    },
                    {
                        $name: "OTSD_MODE_FAST_RETRY",
                        bitValue: 1,
                        description: "Report on nFault, predriver HiZ, auto recovery with Fast Retry time (in ms)"
                    },
                ])
            },
            {
                $name: "UVP_MODE",
                description: "Undervoltage Protection Fault mode",
                bitWidth: 2,
                startBit: 2,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "UVP_MODE_SLOW_RETRY",
                        bitValue: 0,
                        description: "Report on nFault, predriver HiZ, auto recovery with Slow Retry time (in ms)"
                    },
                    {
                        $name: "UVP_MODE_FAST_RETRY",
                        bitValue: 1,
                        description: "Report on nFault, predriver HiZ, auto recovery with Fast Retry time (in ms)"
                    },
                ])
            },
            {
                $name: "OCP_MODE",
                description: "Overcurrent Protection Fault mode",
                bitWidth: 3,
                startBit: 4,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "OCP_MODE_SLOW_RETRY",
                        bitValue: 0,
                        description: "Report on nFault, predriver HiZ, auto recovery with Slow Retry time (in ms)"
                    },
                    {
                        $name: "OCP_MODE_FAST_RETRY",
                        bitValue: 1,
                        description: "Report on nFault, predriver HiZ, auto recovery with Fast Retry time (in ms)"
                    },
                    {
                        $name: "OCP_MODE_LATCH",
                        bitValue: 2,
                        description: "Report on nFault, predriver HiZ, Latched Fault"
                    },
                    {
                        $name: "OCP_MODE_NO",
                        bitValue: 3,
                        description: "Report on nFault, No action on predriver"
                    },
                    {
                        $name: "OCP_MODE_DISABLE",
                        bitValue: 7,
                        description: "Disabled"
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
                $name: "OTPFLT_MODE",
                description: "System Fault Mode",
                bitWidth: 1,
                startBit: 8,
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
        $name: "SYSF_CTRL",
        registerName: "System Fault Control Register",
        offset: 0x12,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "CSAREFUV_EN",
                description: "CSAREF Undervoltage Fault Enable",
                bitWidth: 1,
                startBit: 5,
                enumEnable: false,
            },
            {
                $name: "OTW_EN",
                description: "Overtemperature Warning Fault Enable",
                bitWidth: 1,
                startBit: 9,
                enumEnable: false,
            },
            {
                $name: "OTAVDD_EN",
                description: "AVDD Overtemperature Fault Enable",
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
        $name: "DRVF_CTRL",
        registerName: "Driver Fault Control Register",
        offset: 0x13,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "OCP_LVL",
                description: "OCP Level Settings",
                bitWidth: 1,
                startBit: 0,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "OCP_LVL_9A",
                        bitValue: 0,
                        description: "OCP level is 9 A (TYP)"
                    },
                    {
                        $name: "OCP_LVL_5A",
                        bitValue: 1,
                        description: "OCP level is 5 A (TYP)"
                    },
                ])
            },
            {
                $name: "OCP_TBLANK",
                description: "OCP Blanking time",
                bitWidth: 2,
                startBit: 2,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "OCP_TBLANK_0p2us",
                        bitValue: 0,
                        description: "OCP blanking time is 0.2 μs"
                    },
                    {
                        $name: "OCP_TBLANK_0p5us",
                        bitValue: 1,
                        description: "OCP blanking time is 0.5 μs"
                    },
                    {
                        $name: "OCP_TBLANK_0p8us",
                        bitValue: 2,
                        description: "OCP blanking time is 0.8 μs"
                    },
                    {
                        $name: "OCP_TBLANK_1p0us",
                        bitValue: 3,
                        description: "OCP blanking time is 1.0 μs"
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
                        $name: "OCP_DEG_0p2us",
                        bitValue: 0,
                        description: "OCP deglitch time is 0.2 μs"
                    },
                    {
                        $name: "OCP_DEG_0p5us",
                        bitValue: 1,
                        description: "OCP deglitch time is 0.5 μs"
                    },
                    {
                        $name: "OCP_DEG_0p8us",
                        bitValue: 2,
                        description: "OCP deglitch time is 0.8 μs"
                    },
                    {
                        $name: "OCP_DEG_1p0us",
                        bitValue: 3,
                        description: "OCP deglitch time is 1.0 μs"
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
        $name: "FLT_TCTRL",
        registerName: "Fault Timing Control Register",
        offset: 0x16,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "FAST_TRETRY",
                description: "Fast Recovery Retry Time from Fault Condition",
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
                description: "Slow Recovery Retry Time from Fault Condition",
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
                description: "Clear Fault",
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
        $name: "PWMG_PERIOD",
        registerName: "PWM_GEN Period Register",
        offset: 0x18,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "PWM_PRD_OUT",
                description: "12-bit Period for output PWM signals in PWM Generation Mode",
                bitWidth: 12,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "PWMG_PERIOD_PARITY",
                description: "Parity Bit if SPI_PEN is set to '1' otherwise reserved",
                bitWidth: 1,
                startBit: 15,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "PWMG_A_DUTY",
        registerName: "PWM_GEN A Duty Register",
        offset: 0x19,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "PWM_DUTY_OUTA",
                description: "12-bit Duty Cycle for Phase A output in PWM Generation Mode",
                bitWidth: 12,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "PWMG_A_DUTY_PARITY",
                description: "Parity Bit if SPI_PEN is set to '1' otherwise reserved",
                bitWidth: 1,
                startBit: 15,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "PWMG_B_DUTY",
        registerName: "PWM_GEN B Duty Register",
        offset: 0x1A,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "PWM_DUTY_OUTB",
                description: "12-bit Duty Cycle for Phase B output in PWM Generation Mode",
                bitWidth: 12,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "PWMG_B_DUTY_PARITY",
                description: "Parity Bit if SPI_PEN is set to '1' otherwise reserved",
                bitWidth: 1,
                startBit: 15,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "PWMG_C_DUTY",
        registerName: "PWM_GEN C Duty Register",
        offset: 0x1B,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "PWM_DUTY_OUTC",
                description: "12-bit Duty Cycle for Phase C output in PWM Generation Mode",
                bitWidth: 12,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "PWMG_C_DUTY_PARITY",
                description: "Parity Bit if SPI_PEN is set to '1' otherwise reserved",
                bitWidth: 1,
                startBit: 15,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "PWM_STATE",
        registerName: "PWM State Register",
        offset: 0x1C,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "PWMA_STATE",
                description: "Phase A Driver Output control",
                bitWidth: 3,
                startBit: 0,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "PWMA_STATE_HI_OFF_LOW_OFF",
                        bitValue: 0,
                        description: "High Side is OFF, Low Side is OFF"
                    },
                    {
                        $name: "PWMA_STATE_HI_OFF_LOW_ON",
                        bitValue: 1,
                        description: "High Side is OFF, Low Side is forced ON"
                    },
                    {
                        $name: "PWMA_STATE_HI_ON_LOW_OFF",
                        bitValue: 2,
                        description: "High Side is forced ON, Low Side is OFF"
                    },
                    {
                        $name: "PWMA_STATE_HI_OFF_LOW_PWM",
                        bitValue: 5,
                        description: "High Side is OFF, Low Side PWM"
                    },
                    {
                        $name: "PWMA_STATE_HI_PWM_LOW_OFF",
                        bitValue: 6,
                        description: "High Side PWM, Low Side is OFF"
                    },
                    {
                        $name: "PWMA_STATE_HI_PWM_LOW_nPWM",
                        bitValue: 7,
                        description: "High Side PWM, Low Side !PWM"
                    },
                ])
            },
            {
                $name: "PWMB_STATE",
                description: "Phase B Driver Output control",
                bitWidth: 3,
                startBit: 4,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "PWMB_STATE_HI_OFF_LOW_OFF",
                        bitValue: 0,
                        description: "High Side is OFF, Low Side is OFF"
                    },
                    {
                        $name: "PWMB_STATE_HI_OFF_LOW_ON",
                        bitValue: 1,
                        description: "High Side is OFF, Low Side is forced ON"
                    },
                    {
                        $name: "PWMB_STATE_HI_ON_LOW_OFF",
                        bitValue: 2,
                        description: "High Side is forced ON, Low Side is OFF"
                    },
                    {
                        $name: "PWMB_STATE_HI_OFF_LOW_PWM",
                        bitValue: 5,
                        description: "High Side is OFF, Low Side PWM"
                    },
                    {
                        $name: "PWMB_STATE_HI_PWM_LOW_OFF",
                        bitValue: 6,
                        description: "High Side PWM, Low Side is OFF"
                    },
                    {
                        $name: "PWMB_STATE_HI_PWM_LOW_nPWM",
                        bitValue: 7,
                        description: "High Side PWM, Low Side !PWM"
                    },
                ])
            },
            {
                $name: "PWMC_STATE",
                description: "Phase C Driver Output control",
                bitWidth: 3,
                startBit: 8,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "PWMC_STATE_HI_OFF_LOW_OFF",
                        bitValue: 0,
                        description: "High Side is OFF, Low Side is OFF"
                    },
                    {
                        $name: "PWMC_STATE_HI_OFF_LOW_ON",
                        bitValue: 1,
                        description: "High Side is OFF, Low Side is forced ON"
                    },
                    {
                        $name: "PWMC_STATE_HI_ON_LOW_OFF",
                        bitValue: 2,
                        description: "High Side is forced ON, Low Side is OFF"
                    },
                    {
                        $name: "PWMC_STATE_HI_OFF_LOW_PWM",
                        bitValue: 5,
                        description: "High Side is OFF, Low Side PWM"
                    },
                    {
                        $name: "PWMC_STATE_HI_PWM_LOW_OFF",
                        bitValue: 6,
                        description: "High Side PWM, Low Side is OFF"
                    },
                    {
                        $name: "PWMC_STATE_HI_PWM_LOW_nPWM",
                        bitValue: 7,
                        description: "High Side PWM, Low Side !PWM"
                    },
                ])
            },
            {
                $name: "PWM_STATE_PARITY",
                description: "Parity Bit if SPI_PEN is set to '1' otherwise reserved",
                bitWidth: 1,
                startBit: 15,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "PWMG_CTRL",
        registerName: "PWM_GEN Control Register",
        offset: 0x1D,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "SPISYNC_ACRCY",
                description: "Number of SPI Clock Cycle require for synchronizing the Oscillator",
                bitWidth: 2,
                startBit: 0,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "SPISYNC_ACRCY_64_CLK",
                        bitValue: 0,
                        description: "64 Clock Cycles (2%)"
                    },
                    {
                        $name: "SPISYNC_ACRCY_128_CLK",
                        bitValue: 1,
                        description: "128 Clock Cycles (1%)"
                    },
                    {
                        $name: "SPISYNC_ACRCY_256_CLK",
                        bitValue: 2,
                        description: "256 Clock Cycles (1%)"
                    },
                    {
                        $name: "SPISYNC_ACRCY_512_CLK",
                        bitValue: 3,
                        description: "512 Clock Cycles (1%)"
                    },
                ])
            },
            {
                $name: "SPICLK_FREQ_SYNC",
                description: "SPI Clock Frequency for synchronizing the Oscillator",
                bitWidth: 3,
                startBit: 2,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "SPICLK_FREQ_SYNC_1p00_MHz",
                        bitValue: 0,
                        description: "1 MHz"
                    },
                    {
                        $name: "SPICLK_FREQ_SYNC_1p25_MHz",
                        bitValue: 1,
                        description: "1.25 MHz"
                    },
                    {
                        $name: "SPICLK_FREQ_SYNC_2p00_MHz",
                        bitValue: 2,
                        description: "2 MHz"
                    },
                    {
                        $name: "SPICLK_FREQ_SYNC_2p50_MHz",
                        bitValue: 3,
                        description: "2.5 MHz"
                    },
                    {
                        $name: "SPICLK_FREQ_SYNC_4p00_MHz",
                        bitValue: 4,
                        description: "4 MHz"
                    },
                    {
                        $name: "SPICLK_FREQ_SYNC_5p00_MHz",
                        bitValue: 5,
                        description: "5 MHz"
                    },
                    {
                        $name: "SPICLK_FREQ_SYNC_8p00_MHz",
                        bitValue: 6,
                        description: "8 MHz"
                    },
                    {
                        $name: "SPICLK_FREQ_SYNC_10p00_MHz",
                        bitValue: 7,
                        description: "10 MHz"
                    },
                ])
            },
            {
                $name: "PWM_OSC_SYNC",
                description: "Oscillator synchronization and PWM_SYNC control",
                bitWidth: 3,
                startBit: 5,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "PWM_OSC_SYNC_DISABLE0",
                        bitValue: 0,
                        description: "Oscillator synchronization is disabled"
                    },
                    {
                        $name: "PWM_OSC_SYNC_PRD_CAL",
                        bitValue: 1,
                        description: "PWM_SYNC_PRD indicates period of PWM_SYNC signal and can be used to calibrate PWM period"
                    },
                    {
                        $name: "PWM_OSC_SYNC_PRD",
                        bitValue: 2,
                        description: "PWM_SYNC used to set PWM period"
                    },
                    {
                        $name: "PWM_OSC_SYNC_DISABLE3",
                        bitValue: 3,
                        description: "Oscillator synchronization is disabled"
                    },
                    {
                        $name: "PWM_OSC_SYNC_DISABLE4",
                        bitValue: 4,
                        description: "Oscillator synchronization is disabled"
                    },
                    {
                        $name: "PWM_OSC_SYNC_OSC",
                        bitValue: 5,
                        description: "PWM_SYNC used for oscillator synchronization (only 20 kHz frequency supported)"
                    },
                    {
                        $name: "PWM_OSC_SYNC_OSC_PRD",
                        bitValue: 6,
                        description: "PWM_SYNC used for oscillator synchronization and setting PWM period (only 20 kHz frequency supported)"
                    },
                    {
                        $name: "PWM_OSC_SYNC_SCLK",
                        bitValue: 7,
                        description: "SPI Clock pin SCLK used for oscillator synchronization (Configure SPICLK_FREQ_SYNC)"
                    },
                ])
            },
            {
                $name: "PWMCNTR_MODE",
                description: "PWM Gen counter mode",
                bitWidth: 2,
                startBit: 8,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "PWMCNTR_MODE_UP_DOWN",
                        bitValue: 0,
                        description: "Up and Down"
                    },
                    {
                        $name: "PWMCNTR_MODE_UP",
                        bitValue: 1,
                        description: "Up"
                    },
                    {
                        $name: "PWMCNTR_MODE_DOWN",
                        bitValue: 2,
                        description: "Down"
                    },
                    {
                        $name: "PWMCNTR_MODE_NO_ACTION",
                        bitValue: 3,
                        description: "No action"
                    },
                ])
            },
            {
                $name: "PWM_EN",
                description: "Enable 3X Internal mode PWM Generation",
                bitWidth: 1,
                startBit: 10,
                enumEnable: false,
            },
            {
                $name: "PWMG_CTRL_PARITY",
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
                        $name: "PWM_MODE_6_RES",
                        bitValue: 0,
                        description: "6x mode"
                    },
                    {
                        $name: "PWM_MODE_6",
                        bitValue: 1,
                        description: "6x mode"
                    },
                    {
                        $name: "PWM_MODE_3",
                        bitValue: 2,
                        description: "3x mode"
                    },
                    {
                        $name: "PWM_MODE_GEN",
                        bitValue: 3,
                        description: "PWM Generation mode"
                    },
                ])
            },
            {
                $name: "SSC_DIS",
                description: "Disable Spread Spectrum Modulation for internal Oscillator",
                bitWidth: 1,
                startBit: 2,
                enumEnable: false,
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
                        $name: "SLEW_RATE_35V",
                        bitValue: 0,
                        description: "Slew rate is 35 V/uS"
                    },
                    {
                        $name: "SLEW_RATE_75V",
                        bitValue: 1,
                        description: "Slew rate is 75 V/uS"
                    },
                    {
                        $name: "SLEW_RATE_180V",
                        bitValue: 2,
                        description: "Slew rate is 180 V/uS"
                    },
                    {
                        $name: "SLEW_RATE_230V",
                        bitValue: 3,
                        description: "Slew rate is 230 V/uS"
                    },
                ])
            },
            {
                $name: "TDEAD_CTRL",
                description: "Deadtime insertion control",
                bitWidth: 3,
                startBit: 4,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "TDEAD_CTRL_NO",
                        bitValue: 0,
                        description: "No deadtime (Handshake Only)"
                    },
                    {
                        $name: "TDEAD_CTRL_200ns",
                        bitValue: 1,
                        description: "200ns"
                    },
                    {
                        $name: "TDEAD_CTRL_400ns",
                        bitValue: 2,
                        description: "400ns"
                    },
                    {
                        $name: "TDEAD_CTRL_600ns",
                        bitValue: 3,
                        description: "600ns"
                    },
                    {
                        $name: "TDEAD_CTRL_800ns",
                        bitValue: 4,
                        description: "800ns"
                    },
                    {
                        $name: "TDEAD_CTRL_1p0us",
                        bitValue: 5,
                        description: "1us"
                    },
                    {
                        $name: "TDEAD_CTRL_1p2us",
                        bitValue: 6,
                        description: "1.2us"
                    },
                    {
                        $name: "TDEAD_CTRL_1p4us",
                        bitValue: 7,
                        description: "1.4us"
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
                description: "Current Sense Amplifier Gain settings",
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
                description: "Current Sense Amplifier Enable",
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
                description: "Parity Enable for both SPI and tSPI",
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

function getDRV8311SpiSettings(inst) {
    return {
        $name: "DRV8311_SPI_Interface",
        spiFrameSize: "24bits",
        rwSelect24Bits: [23],
        readBitValue: 1,
        writeBitValue: 0,
        addressSelect24Bits: [22, 21, 20, 19, 18, 17],
        dataSelect24Bits: [14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0],
        crcMode: "parity",
        crcSelect24Bits: [16, 15],
        hiddenTextFieldForRegisterArgs: JSON.stringify(drv8311Registers),
	}
}

exports = {
	getDRV8311SpiSettings,
};