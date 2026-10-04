let Common = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let references = system.getScript("/libraries/MCSDKLibraryReferences.js");

let drv8334Registers = [
    {
        $name: "IC_STAT1",
        registerName: "IC Status Register 1",
        offset: 0x0,
        registerType: "status",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "DRV_STAT",
                description: "Indicates Driver Enable Status. Mirrors ENABLE_DRV register bit",
                bitWidth: 1,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "OTW",
                description: "Overtemperature Warning Status Bit",
                bitWidth: 1,
                startBit: 1,
                enumEnable: false,
            },
            {
                $name: "UV",
                description: "Logic OR of supply voltage undervoltage detection",
                bitWidth: 1,
                startBit: 8,
                enumEnable: false,
            },
            {
                $name: "OV",
                description: "Logic OR of supply voltage overvoltage detection",
                bitWidth: 1,
                startBit: 9,
                enumEnable: false,
            },
            {
                $name: "SNS_OCP",
                description: "Logic OR of Sense overcurrent detection",
                bitWidth: 1,
                startBit: 10,
                enumEnable: false,
            },
            {
                $name: "VGS",
                description: "Logic OR of VGS detection",
                bitWidth: 1,
                startBit: 11,
                enumEnable: false,
            },
            {
                $name: "VDS",
                description: "Logic OR of VDS overcurrent detection",
                bitWidth: 1,
                startBit: 12,
                enumEnable: false,
            },
            {
                $name: "WARN",
                description: "Logic OR of WARN status, except OTW",
                bitWidth: 1,
                startBit: 13,
                enumEnable: false,
            },
            {
                $name: "FAULT",
                description: "Logic OR of FAULT status registers. Mirrors nFAULT pin",
                bitWidth: 1,
                startBit: 14,
                enumEnable: false,
            },
            {
                $name: "SPI_OK",
                description: "No SPI Fault is detected",
                bitWidth: 1,
                startBit: 15,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "IC_STAT2",
        registerName: "IC Status Register 2",
        offset: 0x1,
        registerType: "status",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "VDS_LC",
                description: "VDS Overcurrent Status on the C Low-side MOSFET",
                bitWidth: 1,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "VDS_HC",
                description: "VDS Overcurrent Status on the C High-side MOSFET",
                bitWidth: 1,
                startBit: 1,
                enumEnable: false,
            },
            {
                $name: "VDS_LB",
                description: "VDS Overcurrent Status on the B Low-side MOSFET",
                bitWidth: 1,
                startBit: 2,
                enumEnable: false,
            },
            {
                $name: "VDS_HB",
                description: "VDS Overcurrent Status on the B High-side MOSFET",
                bitWidth: 1,
                startBit: 3,
                enumEnable: false,
            },
            {
                $name: "VDS_LA",
                description: "VDS Overcurrent Status on the A Low-side MOSFET",
                bitWidth: 1,
                startBit: 4,
                enumEnable: false,
            },
            {
                $name: "VDS_HA",
                description: "VDS Overcurrent Status on the A High-side MOSFET",
                bitWidth: 1,
                startBit: 5,
                enumEnable: false,
            },
            {
                $name: "SNS_OCP_C",
                description: "Overcurrent on External Sense Resistor Status Bit on phase C",
                bitWidth: 1,
                startBit: 8,
                enumEnable: false,
            },
            {
                $name: "SNS_OCP_B",
                description: "Overcurrent on External Sense Resistor Status Bit on phase B",
                bitWidth: 1,
                startBit: 9,
                enumEnable: false,
            },
            {
                $name: "SNS_OCP_A",
                description: "Overcurrent on External Sense Resistor Status Bit on phase A",
                bitWidth: 1,
                startBit: 10,
                enumEnable: false,
            },
            {
                $name: "CBC_ST",
                description: "VDS and SNS_OCP monitor Cycle By Cycle (CBC) counter activity status",
                bitWidth: 1,
                startBit: 15,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "IC_STAT3",
        registerName: "IC Status Register 3",
        offset: 0x2,
        registerType: "status",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "VGS_LC",
                description: "Gate driver fault status on the C Low-side MOSFET",
                bitWidth: 1,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "VGS_HC",
                description: "Gate driver fault status on the C High-side MOSFET",
                bitWidth: 1,
                startBit: 1,
                enumEnable: false,
            },
            {
                $name: "VGS_LB",
                description: "Gate driver fault status on the B Low-side MOSFET",
                bitWidth: 1,
                startBit: 2,
                enumEnable: false,
            },
            {
                $name: "VGS_HB",
                description: "Gate driver fault status on the B High-side MOSFET",
                bitWidth: 1,
                startBit: 3,
                enumEnable: false,
            },
            {
                $name: "VGS_LA",
                description: "Gate driver fault status on the A Low-side MOSFET",
                bitWidth: 1,
                startBit: 4,
                enumEnable: false,
            },
            {
                $name: "VGS_HA",
                description: "Gate driver fault status on the A High-side MOSFET",
                bitWidth: 1,
                startBit: 5,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "IC_STAT4",
        registerName: "IC Status Register 4",
        offset: 0x3,
        registerType: "status",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "BSTC_UV",
                description: "BST undervoltage on the C High-side MOSFET",
                bitWidth: 1,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "BSTC_OV",
                description: "BST overvoltage on the C High-side MOSFET",
                bitWidth: 1,
                startBit: 1,
                enumEnable: false,
            },
            {
                $name: "BSTB_UV",
                description: "BST undervoltage on the B High-side MOSFET",
                bitWidth: 1,
                startBit: 2,
                enumEnable: false,
            },
            {
                $name: "BSTB_OV",
                description: "BST overvoltage on the B High-side MOSFET",
                bitWidth: 1,
                startBit: 3,
                enumEnable: false,
            },
            {
                $name: "BSTA_UV",
                description: "BST undervoltage on the A High-side MOSFET",
                bitWidth: 1,
                startBit: 4,
                enumEnable: false,
            },
            {
                $name: "BSTA_OV",
                description: "BST overvoltage on the A High-side MOSFET",
                bitWidth: 1,
                startBit: 5,
                enumEnable: false,
            },
            {
                $name: "GVDD_UV",
                description: "GVDD undervoltage status",
                bitWidth: 1,
                startBit: 8,
                enumEnable: false,
            },
            {
                $name: "GVDD_OV",
                description: "GVDD overvoltage status",
                bitWidth: 1,
                startBit: 9,
                enumEnable: false,
            },
            {
                $name: "VCP_UV",
                description: "VCP undervoltage status",
                bitWidth: 1,
                startBit: 10,
                enumEnable: false,
            },
            {
                $name: "VCP_OV",
                description: "VCP overvoltage status",
                bitWidth: 1,
                startBit: 11,
                enumEnable: false,
            },
            {
                $name: "VDRAIN_UV",
                description: "VDRAIN undervoltage status",
                bitWidth: 1,
                startBit: 12,
                enumEnable: false,
            },
            {
                $name: "VDRAIN_OV",
                description: "VDRAIN overvoltage status",
                bitWidth: 1,
                startBit: 13,
                enumEnable: false,
            },
            {
                $name: "PVDD_UV",
                description: "PVDD undervoltage status",
                bitWidth: 1,
                startBit: 14,
                enumEnable: false,
            },
            {
                $name: "PVDD_OV",
                description: "PVDD overvoltage status",
                bitWidth: 1,
                startBit: 15,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "IC_STAT5",
        registerName: "IC Status Register 5",
        offset: 0x4,
        registerType: "status",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "DEADT_FLT",
                description: "Dead time violation",
                bitWidth: 1,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "STP_FLT",
                description: "Shoot Through Protection violation",
                bitWidth: 1,
                startBit: 1,
                enumEnable: false,
            },
            {
                $name: "OTP_USR_CRC_FLT",
                description: "USER OTP CRC fault",
                bitWidth: 1,
                startBit: 3,
                enumEnable: false,
            },
            {
                $name: "OTP_CRC_FLT",
                description: "OTP CRC fault bit",
                bitWidth: 1,
                startBit: 4,
                enumEnable: false,
            },
            {
                $name: "SPI_CLK_FLT",
                description: "SPI Clock Framing fault bit",
                bitWidth: 1,
                startBit: 5,
                enumEnable: false,
            },
            {
                $name: "SPI_ADDR_FLT",
                description: "SPI Address fault bit",
                bitWidth: 1,
                startBit: 6,
                enumEnable: false,
            },
            {
                $name: "SPI_CRC_FLT",
                description: "SPI CRC fault bit",
                bitWidth: 1,
                startBit: 7,
                enumEnable: false,
            },
            {
                $name: "WDT_FLT",
                description: "Watch dog timer fault bit",
                bitWidth: 1,
                startBit: 8,
                enumEnable: false,
            },
            {
                $name: "OTSD",
                description: "Overtemperature shutdown status",
                bitWidth: 1,
                startBit: 9,
                enumEnable: false,
            },
            {
                $name: "GVDD_CP_LDO",
                description: "GVDD operating mode status",
                bitWidth: 1,
                startBit: 10,
                enumEnable: false,
            },
            {
                $name: "PVDD_UVW",
                description: "PVDD undervoltage warning status",
                bitWidth: 1,
                startBit: 14,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "IC_STAT6",
        registerName: "IC Status Register 6",
        offset: 0x5,
        registerType: "status",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "CLK_MON_FLT",
                description: "Clock monitor fault status",
                bitWidth: 1,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "DEV_MODE_FLT",
                description: "Device mode fault status",
                bitWidth: 1,
                startBit: 3,
                enumEnable: false,
            },
            {
                $name: "ABIST_FLT",
                description: "Analog BIST fault status",
                bitWidth: 1,
                startBit: 4,
                enumEnable: false,
            },
            {
                $name: "DVDD_OV",
                description: "DVDD overvoltage status",
                bitWidth: 1,
                startBit: 7,
                enumEnable: false,
            },
            {
                $name: "VDDSDO_UV",
                description: "Device internal regulator VDDSDO regulator undervoltage status",
                bitWidth: 1,
                startBit: 9,
                enumEnable: false,
            },
            {
                $name: "VREF_UV",
                description: "VREF input undervoltage status",
                bitWidth: 1,
                startBit: 10,
                enumEnable: false,
            },
            {
                $name: "VREF_OV",
                description: "VREF input overvoltage status",
                bitWidth: 1,
                startBit: 11,
                enumEnable: false,
            },
            {
                $name: "PHCC_FLT",
                description: "Indicates phase comparator fault of PHCC",
                bitWidth: 1,
                startBit: 13,
                enumEnable: false,
            },
            {
                $name: "PHCB_FLT",
                description: "Indicates phase comparator fault of PHCB",
                bitWidth: 1,
                startBit: 14,
                enumEnable: false,
            },
            {
                $name: "PHCA_FLT",
                description: "Indicates phase comparator fault of PHCA",
                bitWidth: 1,
                startBit: 15,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "IC_CTRL1",
        registerName: "IC Control Register 1",
        offset: 0x1A,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "VDDSDO_SEL",
                description: "VDDSDO regulator output selection bit",
                bitWidth: 1,
                startBit: 0,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "VDDSDO_SEL_3V3",
                        bitValue: 0,
                        description: "SDO/PHCx 3.3V mode"
                    },
                    {
                        $name: "VDDSDO_SEL_5V0",
                        bitValue: 1,
                        description: "SDO/PHCx 5V mode"
                    },
                ])
            },
        ])
    },
    {
        $name: "IC_CTRL2",
        registerName: "IC Control Register 2",
        offset: 0x1B,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "CLR_FLT",
                description: "Clear fault",
                bitWidth: 1,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "LOCK",
                description: "Lock and unlock the register setting",
                bitWidth: 3,
                startBit: 1,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "LOCK_UNLOCK",
                        bitValue: 3,
                        description: "Unlock all the registers"
                    },
                    {
                        $name: "LOCK_LOCK",
                        bitValue: 6,
                        description: "Lock the settings by ignoring further register writes except to these bits"
                    },
                ])
            },
            {
                $name: "VCP_MODE",
                description: "VCP/TCP mode control",
                bitWidth: 2,
                startBit: 6,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "VCP_MODE_NORMAL_SW_ENABLE",
                        bitValue: 0,
                        description: "Normal VCP/TCP operation. VCP/TCP is enabled at power up. TCP SW is enabled when SPI ENABLE_DRV is 0"
                    },
                    {
                        $name: "VCP_MODE_PUMP_ACTIVE",
                        bitValue: 1,
                        description: "VCP/CPTH-SHx switch is disabled. VCP/TCP charge pump clock is active"
                    },
                    {
                        $name: "VCP_MODE_SHUTDOWN",
                        bitValue: 2,
                        description: "VCP/TCP shutdown. Both VCP/CPTH-SHx switch and VCP/TCP charge pump clock are disabled"
                    },
                    {
                        $name: "VCP_MODE_NORMAL_SW_DISABLE",
                        bitValue: 3,
                        description: "Normal VCP/TCP operation. VCP/TCP is enabled at power up. TCP SW is disabled when SPI ENABLE_DRV is 0"
                    },
                ])
            },
            {
                $name: "GVDD_MODE",
                description: "GVDD Charge pump LDO mode control",
                bitWidth: 1,
                startBit: 8,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "GVDD_MODE_NORMAL",
                        bitValue: 0,
                        description: "Normal GVDD operation. Charge pump mode and LDO mode are controlled by device"
                    },
                    {
                        $name: "GVDD_MODE_LDO",
                        bitValue: 1,
                        description: "LDO mode. GVDD charge pump clock is disabled (charge pump switching operation is disabled)"
                    },
                ])
            },
            {
                $name: "DIS_GVDD_SS",
                description: "Disable GVDD Charge pump soft start",
                bitWidth: 1,
                startBit: 9,
                enumEnable: false,
            },
            {
                $name: "CSA_AZ_DIS",
                description: "Current Sense Amplifier Auto Zero function disable",
                bitWidth: 1,
                startBit: 10,
                enumEnable: false,
            },
            {
                $name: "CSA_EN",
                description: "Current Sense Amplifier Enable",
                bitWidth: 1,
                startBit: 11,
                enumEnable: false,
            },
            {
                $name: "CLKMON_EN",
                description: "Clock monitor enable",
                bitWidth: 1,
                startBit: 12,
                enumEnable: false,
            },
            {
                $name: "CFG_CRC_EN",
                description: "Enable configuration data CRC function",
                bitWidth: 1,
                startBit: 13,
                enumEnable: false,
            },
            {
                $name: "MODE_NSLEEP",
                description: "nSLEEP Mode",
                bitWidth: 1,
                startBit: 14,
                enumEnable: false,
            },
            {
                $name: "ENABLE_DRV",
                description: "Enable predriver bit",
                bitWidth: 1,
                startBit: 15,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "IC_CTRL3",
        registerName: "IC Control Register 3",
        offset: 0x1C,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "OTSD_MODE",
                description: "Overtemperature shutdown mode",
                bitWidth: 2,
                startBit: 0,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "OTSD_MODE_WARNING",
                        bitValue: 0,
                        description: "Warning mode"
                    },
                    {
                        $name: "OTSD_MODE_SHUTDOWN",
                        bitValue: 1,
                        description: "Fault (shutdown) mode"
                    },
                    {
                        $name: "OTSD_MODE_NONE",
                        bitValue: 2,
                        description: "No report. No shutdown"
                    },
                    {
                        $name: "OTSD_MODE_NONE2",
                        bitValue: 3,
                        description: "No report. No shutdown"
                    },
                ])
            },
            {
                $name: "OT_LVL",
                description: "Overtemperature shutdown threshold selection",
                bitWidth: 1,
                startBit: 3,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "OT_LVL_GRADE1",
                        bitValue: 0,
                        description: "Grade 1 mode"
                    },
                    {
                        $name: "OT_LVL_GRADE0",
                        bitValue: 1,
                        description: "Grade 0 mode"
                    },
                ])
            },
            {
                $name: "DRVOFF_PDSEL_LS",
                description: "DROVFF Pull-down select for low-side gate driver",
                bitWidth: 1,
                startBit: 8,
                enumEnable: false,
            },
            {
                $name: "DRVOFF_PDSEL_HS",
                description: "DROVFF Pull-down select for high-side gate driver",
                bitWidth: 1,
                startBit: 9,
                enumEnable: false,
            },
            {
                $name: "TCP_EN_DLY",
                description: "Delay time to activate trickle charge pump after the device detects PWM inactive (INHx=INLx=Low)",
                bitWidth: 1,
                startBit: 10,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "TCP_EN_DLY_100us",
                        bitValue: 0,
                        description: "100us (typ)"
                    },
                    {
                        $name: "TCP_EN_DLY_250us",
                        bitValue: 1,
                        description: "250us (typ)"
                    },
                ])
            },
            {
                $name: "DIS_SSC",
                description: "TI Internal design parameter: No change is required unless notified by TI",
                bitWidth: 1,
                startBit: 12,
                enumEnable: false,
            },
            {
                $name: "WARN_MODE",
                description: "Warning nFAULT mode",
                bitWidth: 1,
                startBit: 14,
                enumEnable: false,
            },
            {
                $name: "SPI_CRC_EN",
                description: "SPI CRC Enable",
                bitWidth: 1,
                startBit: 15,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "GD_CTRL1",
        registerName: "Gate Drive Control Register 1",
        offset: 0x1E,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "DEADT_MODE_6X",
                description: "Dead Time Violation Response Mode for 6 PWM mode only",
                bitWidth: 2,
                startBit: 0,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "DEADT_MODE_6X_ENABLE",
                        bitValue: 0,
                        description: "Dead-time protection is enabled"
                    },
                    {
                        $name: "DEADT_MODE_6X_ENABLE_NO_REPORT",
                        bitValue: 1,
                        description: "Dead-time protection is enabled but no reporting is performed"
                    },
                    {
                        $name: "DEADT_MODE_6X_DISABLE",
                        bitValue: 2,
                        description: "Dead-time protection is disabled"
                    },
                    {
                        $name: "DEADT_MODE_6X_ENABLE_SPI_FLT",
                        bitValue: 3,
                        description: "Dead-time protection is enabled and SPI fault is set but no nFAULT reporting is performed"
                    },
                ])
            },
            {
                $name: "DEADT_MODE",
                description: "Dead Time Insertion Mode",
                bitWidth: 1,
                startBit: 2,
                enumEnable: false,
            },
            {
                $name: "DEADT",
                description: "Gate driver dead time",
                bitWidth: 3,
                startBit: 3,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "DEADT_70ns",
                        bitValue: 0,
                        description: "70ns"
                    },
                    {
                        $name: "DEADT_200ns",
                        bitValue: 1,
                        description: "200ns"
                    },
                    {
                        $name: "DEADT_300ns",
                        bitValue: 2,
                        description: "300ns"
                    },
                    {
                        $name: "DEADT_500ns",
                        bitValue: 3,
                        description: "500ns"
                    },
                    {
                        $name: "DEADT_750ns",
                        bitValue: 4,
                        description: "750ns"
                    },
                    {
                        $name: "DEADT_1000ns",
                        bitValue: 5,
                        description: "1000ns"
                    },
                    {
                        $name: "DEADT_1500ns",
                        bitValue: 6,
                        description: "1500ns"
                    },
                    {
                        $name: "DEADT_2000ns",
                        bitValue: 7,
                        description: "2000ns"
                    },
                ])
            },
            {
                $name: "STP_MODE",
                description: "Shoot-through protection report mode",
                bitWidth: 1,
                startBit: 7,
                enumEnable: false,
            },
            {
                $name: "SGD_TMP_EN",
                description: "Enable dynamic temperature control of Smart Gate Drive",
                bitWidth: 1,
                startBit: 8,
                enumEnable: false,
            },
            {
                $name: "SGD_MODE",
                description: "Smart Gate Drive mode",
                bitWidth: 2,
                startBit: 9,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "SGD_MODE_FIXED",
                        bitValue: 0,
                        description: "Smart Gate Drive with fixed peak current control. TDRVN_D is not valid and ignored"
                    },
                    {
                        $name: "SGD_MODE_DYNAMIC",
                        bitValue: 1,
                        description: "Smart Gate Drive with dynamic peak current control. TDRVN_D is enabled"
                    },
                ])
            },
            {
                $name: "PWM_MODE",
                description: "PWM mode",
                bitWidth: 3,
                startBit: 12,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "PWM_MODE_6_MODE0",
                        bitValue: 0,
                        description: "6x PWM mode (INHx/INLx)"
                    },
                    {
                        $name: "PWM_MODE_3",
                        bitValue: 1,
                        description: "3x PWM mode with INLx enable control"
                    },
                    {
                        $name: "PWM_MODE_3_SPI",
                        bitValue: 2,
                        description: "3x PWM mode with SPI enable control (DRVEN_x)"
                    },
                    {
                        $name: "PWM_MODE_1",
                        bitValue: 3,
                        description: "1x PWM mode (INHx/INLx)"
                    },
                    {
                        $name: "PWM_MODE_SPI",
                        bitValue: 5,
                        description: "SPI Gate Drive Mode"
                    },
                    {
                        $name: "PWM_MODE_6_MODE6",
                        bitValue: 6,
                        description: "6x PWM mode (INHx/INLx)"
                    },
                    {
                        $name: "PWM_MODE_6_MODE7",
                        bitValue: 7,
                        description: "6x PWM mode (INHx/INLx)"
                    },
                ])
            },
        ])
    },
    {
        $name: "GD_CTRL2",
        registerName: "Gate Drive Control Register 2",
        offset: 0x1F,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "TDRVN",
                description: "Peak sink pull down drive timing",
                bitWidth: 4,
                startBit: 0,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "TDRVN_0p143us",
                        bitValue: 0,
                        description: "0.143us"
                    },
                    {
                        $name: "TDRVN_0p179us",
                        bitValue: 1,
                        description: "0.179us"
                    },
                    {
                        $name: "TDRVN_0p321us",
                        bitValue: 2,
                        description: "0.321us"
                    },
                    {
                        $name: "TDRVN_0p464us",
                        bitValue: 3,
                        description: "0.464us"
                    },
                    {
                        $name: "TDRVN_0p607us",
                        bitValue: 4,
                        description: "0.607us"
                    },
                    {
                        $name: "TDRVN_0p750us",
                        bitValue: 5,
                        description: "0.750us"
                    },
                    {
                        $name: "TDRVN_0p893us",
                        bitValue: 6,
                        description: "0.893us"
                    },
                    {
                        $name: "TDRVN_1p036us",
                        bitValue: 7,
                        description: "1.036us"
                    },
                    {
                        $name: "TDRVN_1p321us",
                        bitValue: 8,
                        description: "1.321us"
                    },
                    {
                        $name: "TDRVN_1p607us",
                        bitValue: 9,
                        description: "1.607us"
                    },
                    {
                        $name: "TDRVN_1p893us",
                        bitValue: 10,
                        description: "1.893us"
                    },
                    {
                        $name: "TDRVN_2p179us",
                        bitValue: 11,
                        description: "2.179us"
                    },
                    {
                        $name: "TDRVN_2p536us",
                        bitValue: 12,
                        description: "2.536us"
                    },
                    {
                        $name: "TDRVN_2p964us",
                        bitValue: 13,
                        description: "2.964us"
                    },
                    {
                        $name: "TDRVN_3p393us",
                        bitValue: 14,
                        description: "3.393us"
                    },
                    {
                        $name: "TDRVN_3p821us",
                        bitValue: 15,
                        description: "3.821us"
                    },
                ])
            },
            {
                $name: "TDRVN_D",
                description: "Peak sink pull down pre-discharge timing",
                bitWidth: 4,
                startBit: 4,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "TDRVN_D_0p070us",
                        bitValue: 0,
                        description: "70ns"
                    },
                    {
                        $name: "TDRVN_D_0p140us",
                        bitValue: 1,
                        description: "140ns"
                    },
                    {
                        $name: "TDRVN_D_0p211us",
                        bitValue: 2,
                        description: "211ns"
                    },
                    {
                        $name: "TDRVN_D_0p281us",
                        bitValue: 3,
                        description: "281ns"
                    },
                    {
                        $name: "TDRVN_D_0p351us",
                        bitValue: 4,
                        description: "351ns"
                    },
                    {
                        $name: "TDRVN_D_0p421us",
                        bitValue: 5,
                        description: "421ns"
                    },
                    {
                        $name: "TDRVN_D_0p491us",
                        bitValue: 6,
                        description: "491ns"
                    },
                    {
                        $name: "TDRVN_D_0p561us",
                        bitValue: 7,
                        description: "561ns"
                    },
                    {
                        $name: "TDRVN_D_0p632us",
                        bitValue: 8,
                        description: "632ns"
                    },
                    {
                        $name: "TDRVN_D_0p702us",
                        bitValue: 9,
                        description: "702ns"
                    },
                    {
                        $name: "TDRVN_D_0p772us",
                        bitValue: 10,
                        description: "772ns"
                    },
                    {
                        $name: "TDRVN_D_0p842us",
                        bitValue: 11,
                        description: "842ns"
                    },
                    {
                        $name: "TDRVN_D_0p912us",
                        bitValue: 12,
                        description: "912ns"
                    },
                    {
                        $name: "TDRVN_D_0p982us",
                        bitValue: 13,
                        description: "982ns"
                    },
                    {
                        $name: "TDRVN_D_1p053us",
                        bitValue: 14,
                        description: "1053ns"
                    },
                    {
                        $name: "TDRVN_D_1p123us",
                        bitValue: 15,
                        description: "1123ns"
                    },
                ])
            },
            {
                $name: "TDRVP",
                description: "Peak source pull up drive timing",
                bitWidth: 4,
                startBit: 8,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "TDRVP_0p143us",
                        bitValue: 0,
                        description: "0.143us"
                    },
                    {
                        $name: "TDRVP_0p179us",
                        bitValue: 1,
                        description: "0.179us"
                    },
                    {
                        $name: "TDRVP_0p321us",
                        bitValue: 2,
                        description: "0.321us"
                    },
                    {
                        $name: "TDRVP_0p464us",
                        bitValue: 3,
                        description: "0.464us"
                    },
                    {
                        $name: "TDRVP_0p607us",
                        bitValue: 4,
                        description: "0.607us"
                    },
                    {
                        $name: "TDRVP_0p750us",
                        bitValue: 5,
                        description: "0.750us"
                    },
                    {
                        $name: "TDRVP_0p893us",
                        bitValue: 6,
                        description: "0.893us"
                    },
                    {
                        $name: "TDRVP_1p036us",
                        bitValue: 7,
                        description: "1.036us"
                    },
                    {
                        $name: "TDRVP_1p321us",
                        bitValue: 8,
                        description: "1.321us"
                    },
                    {
                        $name: "TDRVP_1p607us",
                        bitValue: 9,
                        description: "1.607us"
                    },
                    {
                        $name: "TDRVP_1p893us",
                        bitValue: 10,
                        description: "1.893us"
                    },
                    {
                        $name: "TDRVP_2p179us",
                        bitValue: 11,
                        description: "2.179us"
                    },
                    {
                        $name: "TDRVP_2p536us",
                        bitValue: 12,
                        description: "2.536us"
                    },
                    {
                        $name: "TDRVP_2p964us",
                        bitValue: 13,
                        description: "2.964us"
                    },
                    {
                        $name: "TDRVP_3p393us",
                        bitValue: 14,
                        description: "3.393us"
                    },
                    {
                        $name: "TDRVP_3p821us",
                        bitValue: 15,
                        description: "3.821us"
                    },
                ])
            },
        ])
    },
    {
        $name: "GD_CTRL3",
        registerName: "Gate Drive Control Register 3",
        offset: 0x21,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "IDRVN_SD",
                description: "Smart shutdown drive current",
                bitWidth: 6,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "TDRVN_SDD",
                description: "Smart shutdown discharge timing",
                bitWidth: 4,
                startBit: 8,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "TDRVN_SDD_0p070us",
                        bitValue: 0,
                        description: "70ns"
                    },
                    {
                        $name: "TDRVN_SDD_0p140us",
                        bitValue: 1,
                        description: "140ns"
                    },
                    {
                        $name: "TDRVN_SDD_0p211us",
                        bitValue: 2,
                        description: "211ns"
                    },
                    {
                        $name: "TDRVN_SDD_0p281us",
                        bitValue: 3,
                        description: "281ns"
                    },
                    {
                        $name: "TDRVN_SDD_0p351us",
                        bitValue: 4,
                        description: "351ns"
                    },
                    {
                        $name: "TDRVN_SDD_0p421us",
                        bitValue: 5,
                        description: "421ns"
                    },
                    {
                        $name: "TDRVN_SDD_0p491us",
                        bitValue: 6,
                        description: "491ns"
                    },
                    {
                        $name: "TDRVN_SDD_0p561us",
                        bitValue: 7,
                        description: "561ns"
                    },
                    {
                        $name: "TDRVN_SDD_0p632us",
                        bitValue: 8,
                        description: "632ns"
                    },
                    {
                        $name: "TDRVN_SDD_0p702us",
                        bitValue: 9,
                        description: "702ns"
                    },
                    {
                        $name: "TDRVN_SDD_0p772us",
                        bitValue: 10,
                        description: "772ns"
                    },
                    {
                        $name: "TDRVN_SDD_0p842us",
                        bitValue: 11,
                        description: "842ns"
                    },
                    {
                        $name: "TDRVN_SDD_0p912us",
                        bitValue: 12,
                        description: "912ns"
                    },
                    {
                        $name: "TDRVN_SDD_0p982us",
                        bitValue: 13,
                        description: "982ns"
                    },
                    {
                        $name: "TDRVN_SDD_1p053us",
                        bitValue: 14,
                        description: "1053ns"
                    },
                    {
                        $name: "TDRVN_SDD_1p123us",
                        bitValue: 15,
                        description: "1123ns"
                    },
                ])
            },
        ])
    },
    {
        $name: "GD_CTRL3B",
        registerName: "Gate Drive Control Register 3B",
        offset: 0x22,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "IDRVN_D_L",
                description: "Peak sink pull down pre-discharge current for low-side gate driver",
                bitWidth: 6,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "IDRVN_D_H",
                description: "Peak sink pull down pre-discharge current for high-side gate driver",
                bitWidth: 6,
                startBit: 8,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "GD_CTRL4",
        registerName: "Gate Drive Control Register 4",
        offset: 0x23,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "DRV_GLC",
                description: "Drive GLC by SPI command",
                bitWidth: 1,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "DRV_GLB",
                description: "Drive GLB by SPI command",
                bitWidth: 1,
                startBit: 1,
                enumEnable: false,
            },
            {
                $name: "DRV_GLA",
                description: "Drive GLA by SPI command",
                bitWidth: 1,
                startBit: 2,
                enumEnable: false,
            },
            {
                $name: "DRV_GHC",
                description: "Drive GHC by SPI command",
                bitWidth: 1,
                startBit: 3,
                enumEnable: false,
            },
            {
                $name: "DRV_GHB",
                description: "Drive GHB by SPI command",
                bitWidth: 1,
                startBit: 4,
                enumEnable: false,
            },
            {
                $name: "DRV_GHA",
                description: "Drive GHA by SPI command",
                bitWidth: 1,
                startBit: 5,
                enumEnable: false,
            },
            {
                $name: "IHOLD_SEL",
                description: "Select IHOLD pull-up and pull-down current",
                bitWidth: 1,
                startBit: 8,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "IHOLD_SEL_500mA_1000mA",
                        bitValue: 0,
                        description: "IHOLD pull-up/down 500mA/1000mA (typ)"
                    },
                    {
                        $name: "IHOLD_SEL_260mA_260mA",
                        bitValue: 1,
                        description: "IHOLD pull-up/down 260mA/260mA (typ)"
                    },
                ])
            },
            {
                $name: "IDRVP_CFG",
                description: "IDRVP configuration mode",
                bitWidth: 1,
                startBit: 9,
                enumEnable: false,
            },
            {
                $name: "PWM1X_BRAKE",
                description: "1x PWM output configuration",
                bitWidth: 2,
                startBit: 12,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "PWM1X_BRAKE_NORMAL",
                        bitValue: 0,
                        description: "Outputs follow commanded inputs"
                    },
                    {
                        $name: "PWM1X_BRAKE_LS_ON",
                        bitValue: 1,
                        description: "Turn on all three low-side MOSFETs"
                    },
                    {
                        $name: "PWM1X_BRAKE_HS_ON",
                        bitValue: 2,
                        description: "Turn on all three high-side MOSFETs"
                    },
                    {
                        $name: "PWM1X_BRAKE_COAST",
                        bitValue: 3,
                        description: "Turn off all six MOSFETs (coast)"
                    },
                ])
            },
            {
                $name: "PWM1X_DIR",
                description: "1x PWM Direction",
                bitWidth: 1,
                startBit: 14,
                enumEnable: false,
            },
            {
                $name: "PWM1X_COM",
                description: "1x PWM Commutation Control",
                bitWidth: 1,
                startBit: 15,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "PWM1X_COM_SYNC",
                        bitValue: 0,
                        description: "1x PWM mode uses synchronous rectification"
                    },
                    {
                        $name: "PWM1X_COM_ASYNC",
                        bitValue: 1,
                        description: "1x PWM mode uses asynchronous rectification"
                    },
                ])
            },
        ])
    },
    {
        $name: "GD_CTRL5",
        registerName: "Gate Drive Control Register 5",
        offset: 0x24,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "DRVEN_C",
                description: "DRVEN_C = 0 enforces GHC and GLC low with active pull down without shutdown sequence",
                bitWidth: 1,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "DRVEN_B",
                description: "DRVEN_B = 0 enforces GHB and GLB low with active pull down without shutdown sequence",
                bitWidth: 1,
                startBit: 1,
                enumEnable: false,
            },
            {
                $name: "DRVEN_A",
                description: "DRVEN_A = 0 enforces GHA and GLA low with active pull down without shutdown sequence",
                bitWidth: 1,
                startBit: 2,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "GD_CTRL6",
        registerName: "Gate Drive Control Register 6",
        offset: 0x25,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "IDRVP_L",
                description: "Low-side peak source pull up current",
                bitWidth: 6,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "IDRVP_H",
                description: "High-side peak source pull up current",
                bitWidth: 6,
                startBit: 8,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "GD_CTRL7",
        registerName: "Gate Drive Control Register 7",
        offset: 0x26,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "IDRVN_L",
                description: "Low-side peak sink pull down current",
                bitWidth: 6,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "IDRV_RATIO_L",
                description: "Low-side IDRVP and IDRVN ratio",
                bitWidth: 2,
                startBit: 6,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "IDRV_RATIO_L_1p00",
                        bitValue: 0,
                        description: "IDRVP is IDRVN x 1"
                    },
                    {
                        $name: "IDRV_RATIO_L_0p75",
                        bitValue: 1,
                        description: "IDRVP is IDRVN x 0.75"
                    },
                    {
                        $name: "IDRV_RATIO_L_0p50",
                        bitValue: 2,
                        description: "IDRVP is IDRVN x 0.5"
                    },
                    {
                        $name: "IDRV_RATIO_L_0p25",
                        bitValue: 3,
                        description: "IDRVP is IDRVN x 0.25"
                    },
                ])
            },
            {
                $name: "IDRVN_H",
                description: "High-side peak sink pull down current",
                bitWidth: 6,
                startBit: 8,
                enumEnable: false,
            },
            {
                $name: "IDRV_RATIO_H",
                description: "High-side IDRVP and IDRVN ratio",
                bitWidth: 2,
                startBit: 14,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "IDRV_RATIO_H_1p00",
                        bitValue: 0,
                        description: "IDRVP is IDRVN x 1"
                    },
                    {
                        $name: "IDRV_RATIO_H_0p75",
                        bitValue: 1,
                        description: "IDRVP is IDRVN x 0.75"
                    },
                    {
                        $name: "IDRV_RATIO_H_0p50",
                        bitValue: 2,
                        description: "IDRVP is IDRVN x 0.5"
                    },
                    {
                        $name: "IDRV_RATIO_H_0p25",
                        bitValue: 3,
                        description: "IDRVP is IDRVN x 0.25"
                    },
                ])
            },
        ])
    },
    {
        $name: "CSA_CTRL",
        registerName: "CSA Control Registe",
        offset: 0x29,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "CSA_GAIN_C",
                description: "CSA Gain of SOC",
                bitWidth: 4,
                startBit: 0,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "CSA_GAIN_C_5VpA",
                        bitValue: 0,
                        description: "5"
                    },
                    {
                        $name: "CSA_GAIN_C_10VpA",
                        bitValue: 1,
                        description: "10"
                    },
                    {
                        $name: "CSA_GAIN_C_12VpA",
                        bitValue: 2,
                        description: "12"
                    },
                    {
                        $name: "CSA_GAIN_C_16VpA",
                        bitValue: 3,
                        description: "16"
                    },
                    {
                        $name: "CSA_GAIN_C_20VpA",
                        bitValue: 4,
                        description: "20"
                    },
                    {
                        $name: "CSA_GAIN_C_23VpA",
                        bitValue: 5,
                        description: "23"
                    },
                    {
                        $name: "CSA_GAIN_C_25VpA",
                        bitValue: 6,
                        description: "25"
                    },
                    {
                        $name: "CSA_GAIN_C_30VpA",
                        bitValue: 7,
                        description: "30"
                    },
                    {
                        $name: "CSA_GAIN_C_40VpA",
                        bitValue: 8,
                        description: "40"
                    },
                ])
            },
            {
                $name: "CSA_GAIN_B",
                description: "CSA Gain of SOB",
                bitWidth: 4,
                startBit: 4,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "CSA_GAIN_B_5VpA",
                        bitValue: 0,
                        description: "5"
                    },
                    {
                        $name: "CSA_GAIN_B_10VpA",
                        bitValue: 1,
                        description: "10"
                    },
                    {
                        $name: "CSA_GAIN_B_12VpA",
                        bitValue: 2,
                        description: "12"
                    },
                    {
                        $name: "CSA_GAIN_B_16VpA",
                        bitValue: 3,
                        description: "16"
                    },
                    {
                        $name: "CSA_GAIN_B_20VpA",
                        bitValue: 4,
                        description: "20"
                    },
                    {
                        $name: "CSA_GAIN_B_23VpA",
                        bitValue: 5,
                        description: "23"
                    },
                    {
                        $name: "CSA_GAIN_B_25VpA",
                        bitValue: 6,
                        description: "25"
                    },
                    {
                        $name: "CSA_GAIN_B_30VpA",
                        bitValue: 7,
                        description: "30"
                    },
                    {
                        $name: "CSA_GAIN_B_40VpA",
                        bitValue: 8,
                        description: "40"
                    },
                ])
            },
            {
                $name: "CSA_GAIN_A",
                description: "CSA Gain of SOA",
                bitWidth: 4,
                startBit: 8,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "CSA_GAIN_A_5VpA",
                        bitValue: 0,
                        description: "5"
                    },
                    {
                        $name: "CSA_GAIN_A_10VpA",
                        bitValue: 1,
                        description: "10"
                    },
                    {
                        $name: "CSA_GAIN_A_12VpA",
                        bitValue: 2,
                        description: "12"
                    },
                    {
                        $name: "CSA_GAIN_A_16VpA",
                        bitValue: 3,
                        description: "16"
                    },
                    {
                        $name: "CSA_GAIN_A_20VpA",
                        bitValue: 4,
                        description: "20"
                    },
                    {
                        $name: "CSA_GAIN_A_23VpA",
                        bitValue: 5,
                        description: "23"
                    },
                    {
                        $name: "CSA_GAIN_A_25VpA",
                        bitValue: 6,
                        description: "25"
                    },
                    {
                        $name: "CSA_GAIN_A_30VpA",
                        bitValue: 7,
                        description: "30"
                    },
                    {
                        $name: "CSA_GAIN_A_40VpA",
                        bitValue: 8,
                        description: "40"
                    },
                ])
            },
            {
                $name: "AREF_DIV",
                description: "VREF dividing ratio",
                bitWidth: 1,
                startBit: 15,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "AREF_DIV_1_OVER_2",
                        bitValue: 0,
                        description: "1/2"
                    },
                    {
                        $name: "AREF_DIV_1_OVER_8",
                        bitValue: 1,
                        description: "1/8"
                    },
                ])
            },
        ])
    },
    {
        $name: "MON_CTRL1",
        registerName: "Monitor Control Register 1",
        offset: 0x2B,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "PVDD_OV_MODE",
                description: "PVDD OV threshold monitor mode",
                bitWidth: 1,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "PVDD_OV_LVL",
                description: "PVDD OV threshold level",
                bitWidth: 2,
                startBit: 1,
                enumEnable: false,
            },
            {
                $name: "PVDD_UVW_LVL",
                description: "PVDD UV Warning threshold level",
                bitWidth: 1,
                startBit: 3,
                enumEnable: false,
            },
            {
                $name: "VCP_UV_MODE",
                description: "VCP monitor mode of under voltage monitor",
                bitWidth: 1,
                startBit: 4,
                enumEnable: false,
            },
            {
                $name: "VCP_OV_MODE",
                description: "VCP monitor mode of over voltage monitor",
                bitWidth: 1,
                startBit: 5,
                enumEnable: false,
            },
            {
                $name: "GVDD_UV_MODE",
                description: "GVDD monitor mode of under voltage monitor",
                bitWidth: 1,
                startBit: 6,
                enumEnable: false,
            },
            {
                $name: "GVDD_OV_MODE",
                description: "GVDD monitor mode of over voltage monitor",
                bitWidth: 1,
                startBit: 7,
                enumEnable: false,
            },
            {
                $name: "DVDD_OV_MODE",
                description: "DVDD monitor mode of over voltage monitor",
                bitWidth: 1,
                startBit: 8,
                enumEnable: false,
            },
            {
                $name: "BST_UV_LVL",
                description: "BST pin undervoltage threshold level VBST_UV",
                bitWidth: 1,
                startBit: 9,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "BST_UV_LVL_4p2V",
                        bitValue: 0,
                        description: "4.2V (typ)"
                    },
                    {
                        $name: "BST_UV_LVL_7p2V",
                        bitValue: 1,
                        description: "7.2V (typ)"
                    },
                ])
            },
            {
                $name: "BST_UV_MODE",
                description: "BST pin monitor mode",
                bitWidth: 1,
                startBit: 10,
                enumEnable: false,
            },
            {
                $name: "BST_UV_LATCH",
                description: "BST pin undervoltage latch mode",
                bitWidth: 1,
                startBit: 11,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "BST_UV_LATCH_REAL_TIME",
                        bitValue: 0,
                        description: "BST_UV is real time monitor"
                    },
                    {
                        $name: "BST_UV_LATCH_LATCH",
                        bitValue: 1,
                        description: "BST_UV is latched when under voltage condition is detected"
                    },
                ])
            },
            {
                $name: "BST_OV_MODE",
                description: "BST pin overvoltage monitor mode",
                bitWidth: 1,
                startBit: 12,
                enumEnable: false,
            },
            {
                $name: "VDRAIN_MON_MODE",
                description: "VDRAIN monitor mode for under and over voltage monitors",
                bitWidth: 1,
                startBit: 13,
                enumEnable: false,
            },
            {
                $name: "VDRAIN_OV_LVL",
                description: "VDRAIN Overvoltage threshold level",
                bitWidth: 2,
                startBit: 14,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "VDRAIN_OV_LVL_29p5V",
                        bitValue: 0,
                        description: "29.5V (typ)"
                    },
                    {
                        $name: "VDRAIN_OV_LVL_34p5V",
                        bitValue: 1,
                        description: "34.5V (typ)"
                    },
                    {
                        $name: "VDRAIN_OV_LVL_53p5V",
                        bitValue: 2,
                        description: "53.5V (typ)"
                    },
                    {
                        $name: "VDRAIN_OV_LVL_53p5V_2",
                        bitValue: 3,
                        description: "53.5V (typ)"
                    },
                ])
            },
        ])
    },
    {
        $name: "MON_CTRL2",
        registerName: "Monitor Control Register 2",
        offset: 0x2C,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "VGS_DEG",
                description: "VGS monitor deglitch time",
                bitWidth: 3,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "VGS_BLK",
                description: "VGS monitor blanking time",
                bitWidth: 3,
                startBit: 3,
                enumEnable: false,
            },
            {
                $name: "VGS_MODE",
                description: "VGS monitor mode",
                bitWidth: 2,
                startBit: 6,
                enumEnable: false,
            },
            {
                $name: "VDS_DEG",
                description: "VDS overcurrent deglitch time",
                bitWidth: 3,
                startBit: 8,
                enumEnable: false,
            },
            {
                $name: "VDS_BLK",
                description: "VDS overcurrent blanking time",
                bitWidth: 3,
                startBit: 11,
                enumEnable: false,
            },
            {
                $name: "VDS_MODE",
                description: "VDS overcurrent mode",
                bitWidth: 2,
                startBit: 14,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "MON_CTRL3",
        registerName: "Monitor Control Register 3",
        offset: 0x2D,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "SNS_OCP_DEG",
                description: "Deglitch time of VSENSE overcurrent protection (Rshunt monitor)",
                bitWidth: 2,
                startBit: 0,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "SNS_OCP_DEG_2us",
                        bitValue: 0,
                        description: "2.0us (typ)"
                    },
                    {
                        $name: "SNS_OCP_DEG_4us",
                        bitValue: 1,
                        description: "4.0us (typ)"
                    },
                    {
                        $name: "SNS_OCP_DEG_6us",
                        bitValue: 2,
                        description: "6.0us (typ)"
                    },
                    {
                        $name: "SNS_OCP_DEG_10us",
                        bitValue: 3,
                        description: "10.0us (typ)"
                    },
                ])
            },
            {
                $name: "SNS_OCP_LVL",
                description: "Threshold voltage of VSENSE overcurrent protection (Rshunt monitor)",
                bitWidth: 3,
                startBit: 3,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "SNS_OCP_LVL_50mV",
                        bitValue: 0,
                        description: "50mV (typ)"
                    },
                    {
                        $name: "SNS_OCP_LVL_75mV",
                        bitValue: 1,
                        description: "75mV (typ)"
                    },
                    {
                        $name: "SNS_OCP_LVL_100mV",
                        bitValue: 2,
                        description: "100mV (typ)"
                    },
                    {
                        $name: "SNS_OCP_LVL_125mV",
                        bitValue: 3,
                        description: "125mV (typ)"
                    },
                    {
                        $name: "SNS_OCP_LVL_150mV",
                        bitValue: 4,
                        description: "150mV (typ)"
                    },
                    {
                        $name: "SNS_OCP_LVL_200mV",
                        bitValue: 5,
                        description: "200mV (typ)"
                    },
                    {
                        $name: "SNS_OCP_LVL_300mV",
                        bitValue: 6,
                        description: "300mV (typ)"
                    },
                    {
                        $name: "SNS_OCP_LVL_500mV",
                        bitValue: 7,
                        description: "500mV (typ)"
                    },
                ])
            },
            {
                $name: "SNS_OCP_MODE",
                description: "Monitor mode of VSENSE overcurrent protection (Rshunt monitor)",
                bitWidth: 2,
                startBit: 6,
                enumEnable: false,
            },
            {
                $name: "VGS_LVL",
                description: "Gate voltage monitor threshold level when INLx/INHx = High",
                bitWidth: 1,
                startBit: 8,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "VGS_LVL_5p7V",
                        bitValue: 0,
                        description: "5.7V (typ)"
                    },
                    {
                        $name: "VGS_LVL_7p7V",
                        bitValue: 1,
                        description: "7.7V (typ)"
                    },
                ])
            },
        ])
    },
    {
        $name: "MON_CTRL4",
        registerName: "Monitor Control Register 4",
        offset: 0x2E,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "WDT_EN",
                description: "Watchdog Time Enable",
                bitWidth: 1,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "WDT_W",
                description: "Watchdog Timer window tWDL (lower window) and tWDU (upper window)",
                bitWidth: 2,
                startBit: 1,
                enumEnable: false,
            },
            {
                $name: "WDT_MODE",
                description: "Watchdog Time MODE",
                bitWidth: 1,
                startBit: 3,
                enumEnable: false,
            },
            {
                $name: "WDT_CNT",
                description: "Watchdog Time Fault Count",
                bitWidth: 1,
                startBit: 4,
                enumEnable: false,
            },
            {
                $name: "WDT_FLT_MODE",
                description: "Watchdog Time Fault Mode",
                bitWidth: 1,
                startBit: 5,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "MON_CTRL5",
        registerName: "Monitor Control Register 5",
        offset: 0x2F,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "PHC_TH",
                description: "Phase Comparator threshold",
                bitWidth: 1,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "PHC_OUTEN",
                description: "Phase Output buffer enable",
                bitWidth: 1,
                startBit: 1,
                enumEnable: false,
            },
            {
                $name: "PHC_COMPEN",
                description: "Phase Comparator enable",
                bitWidth: 1,
                startBit: 2,
                enumEnable: false,
            },
            {
                $name: "PHC_MON_MODE",
                description: "Phase Comparator fault monitor mode",
                bitWidth: 1,
                startBit: 3,
                enumEnable: false,
            },
            {
                $name: "PHC_OUTDG_SEL",
                description: "Phase Comparator output (PHCx device pin) deglitch time selection",
                bitWidth: 1,
                startBit: 4,
                enumEnable: false,
            },
            {
                $name: "VREF_MON_MODE",
                description: "VREF monitor mode for under and over voltage monitors",
                bitWidth: 1,
                startBit: 11,
                enumEnable: false,
            },
            {
                $name: "VREF_MON_LVL",
                description: "VREF (CSA reference voltage) undervoltage and overvoltage monitor threshold level",
                bitWidth: 1,
                startBit: 12,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "VREF_MON_LVL_3V3",
                        bitValue: 0,
                        description: "Target nominal voltage of VREF is 3.3V"
                    },
                    {
                        $name: "VVREF_MON_LVL_5V0",
                        bitValue: 1,
                        description: "Target nominal voltage of VREF is 5V"
                    },
                ])
            },
            {
                $name: "VDDSDO_MON_LVL",
                description: "VDDSDO (Power supply of SDO) undervoltage and overvoltage monitor level",
                bitWidth: 1,
                startBit: 13,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "VDDSDO_MON_LVL_3V3",
                        bitValue: 0,
                        description: "3.3V mode"
                    },
                    {
                        $name: "VDDSDO_MON_LVL_5V0",
                        bitValue: 1,
                        description: "5V mode"
                    },
                ])
            },
        ])
    },
    {
        $name: "MON_CTRL6",
        registerName: "Monitor Control Register 6",
        offset: 0x30,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "VDS_LVL_LS",
                description: "VDS overcurrent threshold for low-side MOSFETs",
                bitWidth: 4,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "VDS_LVL_HS",
                description: "VDS overcurrent threshold for high-side MOSFETs",
                bitWidth: 4,
                startBit: 4,
                enumEnable: false,
            },
            {
                $name: "CBC_CNT",
                description: "Cycle By Cycle shutdown retry count selection",
                bitWidth: 1,
                startBit: 11,
                enumEnable: false,
            },
            {
                $name: "CBC",
                description: "Cycle By Cycle shutdown retry mode enable",
                bitWidth: 1,
                startBit: 12,
                enumEnable: false,
            },
            {
                $name: "ALL_CH",
                description: "All channel shutdown enable",
                bitWidth: 1,
                startBit: 13,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "DIAG_CTRL1",
        registerName: "Diagnostic Control Register 1",
        offset: 0x33,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "PHDEN_LC",
                description: "Phase Diagnostic switch enable on low-side channel C (SHC-GND)",
                bitWidth: 1,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "PHDEN_HC",
                description: "Phase Diagnostic switch enable on high-side channel C (VDRAIN-SHC)",
                bitWidth: 1,
                startBit: 1,
                enumEnable: false,
            },
            {
                $name: "PHDEN_LB",
                description: "Phase Diagnostic switch enable on low-side channel B (SHB-GND)",
                bitWidth: 1,
                startBit: 2,
                enumEnable: false,
            },
            {
                $name: "PHDEN_HB",
                description: "Phase Diagnostic switch enable on high-side channel B (VDRAIN-SHB)",
                bitWidth: 1,
                startBit: 3,
                enumEnable: false,
            },
            {
                $name: "PHDEN_LA",
                description: "Phase Diagnostic switch enable on low-side channel A (SHA-GND)",
                bitWidth: 1,
                startBit: 4,
                enumEnable: false,
            },
            {
                $name: "PHDEN_HA",
                description: "Phase Diagnostic switch enable on high-side channel A (VDRAIN-SHA)",
                bitWidth: 1,
                startBit: 5,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "SPI_TEST_REG",
        registerName: "SPI Test Register",
        offset: 0x36,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "SPI_TEST",
                description: "SPI Test register",
                bitWidth: 16,
                startBit: 0,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "OTP_USR",
        registerName: "OTP User Control Register",
        offset: 0x48,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "OTP_USR_PRG",
                description: "Program User OTP",
                bitWidth: 1,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "OTP_USR_P_ACC",
                description: "Access control of User OTP Program and User OTP Verification",
                bitWidth: 3,
                startBit: 1,
                enumEnable: false,
            },
            {
                $name: "OTP_USR_P_VER",
                description: "Enables memory verification of User OTP Program",
                bitWidth: 1,
                startBit: 4,
                enumEnable: false,
            },
        ])
    },
]

function getDRV8334SpiSettings(inst) {
    return {
        $name: "DRV8334_SPI_Interface",
        spiFrameSize: "32bits",
        rwSelect32Bits: [24],
        readBitValue: 1,
        writeBitValue: 0,
        addressSelect32Bits: [31, 30, 29, 28, 27, 26, 25],
        dataSelect32Bits: [23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8],
        crcMode: "crc",
        crcSelect32Bits: [7, 6, 5, 4, 3, 2, 1, 0],
        crcInitValue: "0xFF",
        crcPolynomial: "0x2F",
        hiddenTextFieldForRegisterArgs: JSON.stringify(drv8334Registers),
	}
}

exports = {
	getDRV8334SpiSettings,
};