let Common = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let references = system.getScript("/libraries/MCSDKLibraryReferences.js");

let drv8320Registers = [
    {
        $name: "FLT_STS1",
        registerName: "Fault Status Register 1",
        offset: 0x0,
        registerType: "status",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "VDS_LC",
                description: "Indicates VDS overcurrent fault on the C low-side MOSFET",
                bitWidth: 1,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "VDS_HC",
                description: "Indicates VDS overcurrent fault on the C high-side MOSFET",
                bitWidth: 1,
                startBit: 1,
                enumEnable: false,
            },
            {
                $name: "VDS_LB",
                description: "Indicates VDS overcurrent fault on the B low-side MOSFET",
                bitWidth: 1,
                startBit: 2,
                enumEnable: false,
            },
            {
                $name: "VDS_HB",
                description: "Indicates VDS overcurrent fault on the B high-side MOSFET",
                bitWidth: 1,
                startBit: 3,
                enumEnable: false,
            },
            {
                $name: "VDS_LA",
                description: "Indicates VDS overcurrent fault on the A low-side MOSFET",
                bitWidth: 1,
                startBit: 4,
                enumEnable: false,
            },
            {
                $name: "VDS_HA",
                description: "Indicates VDS overcurrent fault on the A high-side MOSFET",
                bitWidth: 1,
                startBit: 5,
                enumEnable: false,
            },
            {
                $name: "OTSD",
                description: "Indicates overtemperature shutdown",
                bitWidth: 1,
                startBit: 6,
                enumEnable: false,
            },
            {
                $name: "UVLO",
                description: "Indicates undervoltage lockout fault condition",
                bitWidth: 1,
                startBit: 7,
                enumEnable: false,
            },
            {
                $name: "GDF",
                description: "Indicates gate drive fault condition",
                bitWidth: 1,
                startBit: 8,
                enumEnable: false,
            },
            {
                $name: "VDS_OCP",
                description: "Indicates VDS monitor overcurrent fault condition",
                bitWidth: 1,
                startBit: 9,
                enumEnable: false,
            },
            {
                $name: "FAULT",
                description: "Logic OR of FAULT status registers. Mirrors nFAULT pin.",
                bitWidth: 1,
                startBit: 10,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "FLT_STS2",
        registerName: "Fault Status Register 2",
        offset: 0x1,
        registerType: "status",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "VGS_LC",
                description: "Indicates gate drive fault on the C low-side MOSFET",
                bitWidth: 1,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "VGS_HC",
                description: "Indicates gate drive fault on the C high-side MOSFET",
                bitWidth: 1,
                startBit: 1,
                enumEnable: false,
            },
            {
                $name: "VGS_LB",
                description: "Indicates gate drive fault on the B low-side MOSFET",
                bitWidth: 1,
                startBit: 2,
                enumEnable: false,
            },
            {
                $name: "VGS_HB",
                description: "Indicates gate drive fault on the B high-side MOSFET",
                bitWidth: 1,
                startBit: 3,
                enumEnable: false,
            },
            {
                $name: "VGS_LA",
                description: "Indicates gate drive fault on the A low-side MOSFET",
                bitWidth: 1,
                startBit: 4,
                enumEnable: false,
            },
            {
                $name: "VGS_HA",
                description: "Indicates gate drive fault on the A high-side MOSFET",
                bitWidth: 1,
                startBit: 5,
                enumEnable: false,
            },
            {
                $name: "CPUV",
                description: "Indicates charge pump undervoltage fault condition",
                bitWidth: 1,
                startBit: 6,
                enumEnable: false,
            },
            {
                $name: "OTW",
                description: "Indicates overtemperature warning",
                bitWidth: 1,
                startBit: 7,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "DRV_CTRL",
        registerName: "Driver Control Register",
        offset: 0x2,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "CLR_FLT",
                description: "Write a 1 to this bit to clear latched fault bits.",
                bitWidth: 1,
                startBit: 0,
                enumEnable: false,
            },
            {
                $name: "BRAKE",
                description: "Write a 1 to this bit to turn on all three low-side MOSFETs in 1x PWM mode.",
                bitWidth: 1,
                startBit: 1,
                enumEnable: false,
            },
            {
                $name: "COAST",
                description: "Write a 1 to this bit to put all MOSFETsin the Hi-Z state",
                bitWidth: 1,
                startBit: 2,
                enumEnable: false,
            },
            {
                $name: "PWM_DIR",
                description: "In 1x PWM mode this bit is ORed with the INHC (DIR) input",
                bitWidth: 1,
                startBit: 3,
                enumEnable: false,
            },
            {
                $name: "PWM_COM",
                description: "1x PWM mode uses asynchronous rectification (diode freewheeling)",
                bitWidth: 1,
                startBit: 4,
                enumEnable: false,
            },
            {
                $name: "PWM_MODE",
                description: "PWM Mode",
                bitWidth: 2,
                startBit: 5,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "PWM_MODE_6",
                        bitValue: 0,
                        description: "PWM_MODE = 6 inputs"
                    },
                    {
                        $name: "PWM_MODE_3",
                        bitValue: 1,
                        description: "PWM_MODE = 3 inputs"
                    },
                    {
                        $name: "PWM_MODE_1",
                        bitValue: 2,
                        description: "PWM_MODE = 1 input"
                    },
                ])
            },
            {
                $name: "OTW_REP",
                description: "OTW is reported on nFAULT and the FAULT bit",
                bitWidth: 1,
                startBit: 7,
                enumEnable: false,
            },
            {
                $name: "DIS_GDF",
                description: "Gate drive fault is disabled",
                bitWidth: 1,
                startBit: 8,
                enumEnable: false,
            },
            {
                $name: "DIS_CPUV",
                description: "Charge pump UVLO fault is disabled",
                bitWidth: 1,
                startBit: 9,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "GD_HS_CTRL",
        registerName: "Gate Drive HS Register",
        offset: 0x3,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "IDRIVEN_HS",
                description: "Adjustable peak sink gate-current for the high-side MOSFET",
                bitWidth: 4,
                startBit: 0,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "ISINK_HS_0P020_A",
                        bitValue: 0,
                        description: "IDRIVEN_HS = 0.020A"
                    },
                    {
                        $name: "ISINK_HS_0P060_A",
                        bitValue: 1,
                        description: "IDRIVEN_HS = 0.060A"
                    },
                    {
                        $name: "ISINK_HS_0P120_A",
                        bitValue: 2,
                        description: "IDRIVEN_HS = 0.120A"
                    },
                    {
                        $name: "ISINK_HS_0P160_A",
                        bitValue: 3,
                        description: "IDRIVEN_HS = 0.160A"
                    },
                    {
                        $name: "ISINK_HS_0P240_A",
                        bitValue: 4,
                        description: "IDRIVEN_HS = 0.240A"
                    },
                    {
                        $name: "ISINK_HS_0P280_A",
                        bitValue: 5,
                        description: "IDRIVEN_HS = 0.280A"
                    },
                    {
                        $name: "ISINK_HS_0P340_A",
                        bitValue: 6,
                        description: "IDRIVEN_HS = 0.340A"
                    },
                    {
                        $name: "ISINK_HS_0P380_A",
                        bitValue: 7,
                        description: "IDRIVEN_HS = 0.380A"
                    },
                    {
                        $name: "ISINK_HS_0P520_A",
                        bitValue: 8,
                        description: "IDRIVEN_HS = 0.520A"
                    },
                    {
                        $name: "ISINK_HS_0P660_A",
                        bitValue: 9,
                        description: "IDRIVEN_HS = 0.660A"
                    },
                    {
                        $name: "ISINK_HS_0P740_A",
                        bitValue: 10,
                        description: "IDRIVEN_HS = 0.740A"
                    },
                    {
                        $name: "ISINK_HS_0P880_A",
                        bitValue: 11,
                        description: "IDRIVEN_HS = 0.880A"
                    },
                    {
                        $name: "ISINK_HS_1P140_A",
                        bitValue: 12,
                        description: "IDRIVEN_HS = 1.140A"
                    },
                    {
                        $name: "ISINK_HS_1P360_A",
                        bitValue: 13,
                        description: "IDRIVEN_HS = 1.360A"
                    },
                    {
                        $name: "ISINK_HS_1P640_A",
                        bitValue: 14,
                        description: "IDRIVEN_HS = 1.640A"
                    },
                    {
                        $name: "ISINK_HS_2P000_A",
                        bitValue: 15,
                        description: "IDRIVEN_HS = 2.000A"
                    },
                ])
            },
            {
                $name: "IDRIVEP_HS",
                description: "Adjustable peak source gate-current for the high-side MOSFET",
                bitWidth: 4,
                startBit: 4,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "ISOUR_HS_0P010_A",
                        bitValue: 0,
                        description: "IDRIVEP_HS = 0.010A"
                    },
                    {
                        $name: "ISOUR_HS_0P030_A",
                        bitValue: 1,
                        description: "IDRIVEP_HS = 0.030A"
                    },
                    {
                        $name: "ISOUR_HS_0P060_A",
                        bitValue: 2,
                        description: "IDRIVEP_HS = 0.060A"
                    },
                    {
                        $name: "ISOUR_HS_0P080_A",
                        bitValue: 3,
                        description: "IDRIVEP_HS = 0.080A"
                    },
                    {
                        $name: "ISOUR_HS_0P120_A",
                        bitValue: 4,
                        description: "IDRIVEP_HS = 0.120A"
                    },
                    {
                        $name: "ISOUR_HS_0P140_A",
                        bitValue: 5,
                        description: "IDRIVEP_HS = 0.140A"
                    },
                    {
                        $name: "ISOUR_HS_0P170_A",
                        bitValue: 6,
                        description: "IDRIVEP_HS = 0.170A"
                    },
                    {
                        $name: "ISOUR_HS_0P190_A",
                        bitValue: 7,
                        description: "IDRIVEP_HS = 0.190A"
                    },
                    {
                        $name: "ISOUR_HS_0P260_A",
                        bitValue: 8,
                        description: "IDRIVEP_HS = 0.260A"
                    },
                    {
                        $name: "ISOUR_HS_0P330_A",
                        bitValue: 9,
                        description: "IDRIVEP_HS = 0.330A"
                    },
                    {
                        $name: "ISOUR_HS_0P370_A",
                        bitValue: 10,
                        description: "IDRIVEP_HS = 0.370A"
                    },
                    {
                        $name: "ISOUR_HS_0P440_A",
                        bitValue: 11,
                        description: "IDRIVEP_HS = 0.440A"
                    },
                    {
                        $name: "ISOUR_HS_0P570_A",
                        bitValue: 12,
                        description: "IDRIVEP_HS = 0.570A"
                    },
                    {
                        $name: "ISOUR_HS_0P680_A",
                        bitValue: 13,
                        description: "IDRIVEP_HS = 0.680A"
                    },
                    {
                        $name: "ISOUR_HS_0P820_A",
                        bitValue: 14,
                        description: "IDRIVEP_HS = 0.820A"
                    },
                    {
                        $name: "ISOUR_HS_1P000_A",
                        bitValue: 15,
                        description: "IDRIVEP_HS = 1.000A"
                    },
                ])
            },
            {
                $name: "LOCK",
                description: "Write 110b to lock the settings by ignoring further register writes except to these bits and address 0x02 bits 0-2",
                bitWidth: 3,
                startBit: 8,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "LOCK_UNLOCK",
                        bitValue: 3,
                        description: "Unlock settings"
                    },
                    {
                        $name: "LOCK_LOCK",
                        bitValue: 6,
                        description: "Lock settings"
                    },
                ])
            },
        ])
    },
    {
        $name: "GD_LS_CTRL",
        registerName: "Gate Drive LS Register",
        offset: 0x4,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "IDRIVEN_LS",
                description: "Adjustable peak sink gate-current for the low-side MOSFET",
                bitWidth: 4,
                startBit: 0,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "ISINK_LS_0P020_A",
                        bitValue: 0,
                        description: "IDRIVEN_LS = 0.020A"
                    },
                    {
                        $name: "ISINK_LS_0P060_A",
                        bitValue: 1,
                        description: "IDRIVEN_LS = 0.060A"
                    },
                    {
                        $name: "ISINK_LS_0P120_A",
                        bitValue: 2,
                        description: "IDRIVEN_LS = 0.120A"
                    },
                    {
                        $name: "ISINK_LS_0P160_A",
                        bitValue: 3,
                        description: "IDRIVEN_LS = 0.160A"
                    },
                    {
                        $name: "ISINK_LS_0P240_A",
                        bitValue: 4,
                        description: "IDRIVEN_LS = 0.240A"
                    },
                    {
                        $name: "ISINK_LS_0P280_A",
                        bitValue: 5,
                        description: "IDRIVEN_LS = 0.280A"
                    },
                    {
                        $name: "ISINK_LS_0P340_A",
                        bitValue: 6,
                        description: "IDRIVEN_LS = 0.340A"
                    },
                    {
                        $name: "ISINK_LS_0P380_A",
                        bitValue: 7,
                        description: "IDRIVEN_LS = 0.380A"
                    },
                    {
                        $name: "ISINK_LS_0P520_A",
                        bitValue: 8,
                        description: "IDRIVEN_LS = 0.520A"
                    },
                    {
                        $name: "ISINK_LS_0P660_A",
                        bitValue: 9,
                        description: "IDRIVEN_LS = 0.660A"
                    },
                    {
                        $name: "ISINK_LS_0P740_A",
                        bitValue: 10,
                        description: "IDRIVEN_LS = 0.740A"
                    },
                    {
                        $name: "ISINK_LS_0P880_A",
                        bitValue: 11,
                        description: "IDRIVEN_LS = 0.880A"
                    },
                    {
                        $name: "ISINK_LS_1P140_A",
                        bitValue: 12,
                        description: "IDRIVEN_LS = 1.140A"
                    },
                    {
                        $name: "ISINK_LS_1P360_A",
                        bitValue: 13,
                        description: "IDRIVEN_LS = 1.360A"
                    },
                    {
                        $name: "ISINK_LS_1P640_A",
                        bitValue: 14,
                        description: "IDRIVEN_LS = 1.640A"
                    },
                    {
                        $name: "ISINK_LS_2P000_A",
                        bitValue: 15,
                        description: "IDRIVEN_LS = 2.000A"
                    },
                ])
            },
            {
                $name: "IDRIVEP_LS",
                description: "Adjustable peak source gate-current for the low-side MOSFET",
                bitWidth: 4,
                startBit: 4,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "ISOUR_LS_0P010_A",
                        bitValue: 0,
                        description: "IDRIVEP_LS = 0.010A"
                    },
                    {
                        $name: "ISOUR_LS_0P030_A",
                        bitValue: 1,
                        description: "IDRIVEP_LS = 0.030A"
                    },
                    {
                        $name: "ISOUR_LS_0P060_A",
                        bitValue: 2,
                        description: "IDRIVEP_LS = 0.060A"
                    },
                    {
                        $name: "ISOUR_LS_0P080_A",
                        bitValue: 3,
                        description: "IDRIVEP_LS = 0.080A"
                    },
                    {
                        $name: "ISOUR_LS_0P120_A",
                        bitValue: 4,
                        description: "IDRIVEP_LS = 0.120A"
                    },
                    {
                        $name: "ISOUR_LS_0P140_A",
                        bitValue: 5,
                        description: "IDRIVEP_LS = 0.140A"
                    },
                    {
                        $name: "ISOUR_LS_0P170_A",
                        bitValue: 6,
                        description: "IDRIVEP_LS = 0.170A"
                    },
                    {
                        $name: "ISOUR_LS_0P190_A",
                        bitValue: 7,
                        description: "IDRIVEP_LS = 0.190A"
                    },
                    {
                        $name: "ISOUR_LS_0P260_A",
                        bitValue: 8,
                        description: "IDRIVEP_LS = 0.260A"
                    },
                    {
                        $name: "ISOUR_LS_0P330_A",
                        bitValue: 9,
                        description: "IDRIVEP_LS = 0.330A"
                    },
                    {
                        $name: "ISOUR_LS_0P370_A",
                        bitValue: 10,
                        description: "IDRIVEP_LS = 0.370A"
                    },
                    {
                        $name: "ISOUR_LS_0P440_A",
                        bitValue: 11,
                        description: "IDRIVEP_LS = 0.440A"
                    },
                    {
                        $name: "ISOUR_LS_0P570_A",
                        bitValue: 12,
                        description: "IDRIVEP_LS = 0.570A"
                    },
                    {
                        $name: "ISOUR_LS_0P680_A",
                        bitValue: 13,
                        description: "IDRIVEP_LS = 0.680A"
                    },
                    {
                        $name: "ISOUR_LS_0P820_A",
                        bitValue: 14,
                        description: "IDRIVEP_LS = 0.820A"
                    },
                    {
                        $name: "ISOUR_LS_1P000_A",
                        bitValue: 15,
                        description: "IDRIVEP_LS = 1.000A"
                    },
                ])
            },
            {
                $name: "TDRIVE",
                description: "Peak gate-current drive time",
                bitWidth: 2,
                startBit: 8,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "TSOUR_500_NS",
                        bitValue: 0,
                        description: "TDRIVE = 500ns"
                    },
                    {
                        $name: "TSOUR_1000_NS",
                        bitValue: 1,
                        description: "TDRIVE = 1000ns"
                    },
                    {
                        $name: "TSOUR_2000_NS",
                        bitValue: 2,
                        description: "TDRIVE = 2000ns"
                    },
                    {
                        $name: "TSOUR_4000_NS",
                        bitValue: 3,
                        description: "TDRIVE = 4000ns"
                    },
                ])
            },
            {
                $name: "CBC",
                description: "Cycle-by-cycle operation",
                bitWidth: 1,
                startBit: 10,
                enumEnable: false,
            },
        ])
    },
    {
        $name: "OCP_CTRL",
        registerName: "OCP Control Register",
        offset: 0x5,
        registerType: "control",
        hiddenTextFieldForBitArgs: JSON.stringify([
            {
                $name: "VDS_LVL",
                description: "VDS overcurrent threshold level",
                bitWidth: 4,
                startBit: 0,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "VDS_LEVEL_0P060_V",
                        bitValue: 0,
                        description: "VDS_LVL = 0.060V"
                    },
                    {
                        $name: "VDS_LEVEL_0P130_V",
                        bitValue: 1,
                        description: "VDS_LVL = 0.130V"
                    },
                    {
                        $name: "VDS_LEVEL_0P200_V",
                        bitValue: 2,
                        description: "VDS_LVL = 0.200V"
                    },
                    {
                        $name: "VDS_LEVEL_0P260_V",
                        bitValue: 3,
                        description: "VDS_LVL = 0.260V"
                    },
                    {
                        $name: "VDS_LEVEL_0P310_V",
                        bitValue: 4,
                        description: "VDS_LVL = 0.310V"
                    },
                    {
                        $name: "VDS_LEVEL_0P450_V",
                        bitValue: 5,
                        description: "VDS_LVL = 0.450V"
                    },
                    {
                        $name: "VDS_LEVEL_0P530_V",
                        bitValue: 6,
                        description: "VDS_LVL = 0.530V"
                    },
                    {
                        $name: "VDS_LEVEL_0P600_V",
                        bitValue: 7,
                        description: "VDS_LVL = 0.600V"
                    },
                    {
                        $name: "VDS_LEVEL_0P680_V",
                        bitValue: 8,
                        description: "VDS_LVL = 0.680V"
                    },
                    {
                        $name: "VDS_LEVEL_0P750_V",
                        bitValue: 9,
                        description: "VDS_LVL = 0.750V"
                    },
                    {
                        $name: "VDS_LEVEL_0P940_V",
                        bitValue: 10,
                        description: "VDS_LVL = 0.940V"
                    },
                    {
                        $name: "VDS_LEVEL_1P130_V",
                        bitValue: 11,
                        description: "VDS_LVL = 1.130V"
                    },
                    {
                        $name: "VDS_LEVEL_1P300_V",
                        bitValue: 12,
                        description: "VDS_LVL = 1.300V"
                    },
                    {
                        $name: "VDS_LEVEL_1P500_V",
                        bitValue: 13,
                        description: "VDS_LVL = 1.500V"
                    },
                    {
                        $name: "VDS_LEVEL_1P700_V",
                        bitValue: 14,
                        description: "VDS_LVL = 1.700V"
                    },
                    {
                        $name: "VDS_LEVEL_1P880_V",
                        bitValue: 15,
                        description: "VDS_LVL = 1.880V"
                    },
                ])
            },
            {
                $name: "OCP_DEG",
                description: "Overcurrent deglitch time",
                bitWidth: 2,
                startBit: 4,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "VDSDEG_2_US",
                        bitValue: 0,
                        description: "OCP_DEG = 2us"
                    },
                    {
                        $name: "VDSDEG_4_US",
                        bitValue: 1,
                        description: "OCP_DEG = 4us"
                    },
                    {
                        $name: "VDSDEG_6_US",
                        bitValue: 2,
                        description: "OCP_DEG = 6us"
                    },
                    {
                        $name: "VDSDEG_8_US",
                        bitValue: 3,
                        description: "OCP_DEG = 8us"
                    },
                ])
            },
            {
                $name: "OCP_MODE",
                description: "Overcurrent mode",
                bitWidth: 2,
                startBit: 6,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "LATCHED_SHUTDOWN",
                        bitValue: 0,
                        description: "OCP_MODE = Latched fault"
                    },
                    {
                        $name: "AUTOMATIC_RETRY",
                        bitValue: 1,
                        description: "OCP_MODE = Automatic Retry"
                    },
                    {
                        $name: "REPORT_ONLY",
                        bitValue: 2,
                        description: "OCP_MODE = Report only"
                    },
                    {
                        $name: "DISABLE_OCP",
                        bitValue: 3,
                        description: "OCP_MODE = Disabled"
                    },
                ])
            },
            {
                $name: "DEAD_TIME",
                description: "Dead time",
                bitWidth: 2,
                startBit: 8,
                enumEnable: true,
                hiddenTextFieldForEnumArgs: JSON.stringify([
                    {
                        $name: "DEAD_TIME_50_NS",
                        bitValue: 0,
                        description: "DEAD_TIME = 50ns"
                    },
                    {
                        $name: "DEAD_TIME_100_NS",
                        bitValue: 1,
                        description: "DEAD_TIME = 100ns"
                    },
                    {
                        $name: "DEAD_TIME_200_NS",
                        bitValue: 2,
                        description: "DEAD_TIME = 200ns"
                    },
                    {
                        $name: "DEAD_TIME_400_NS",
                        bitValue: 3,
                        description: "DEAD_TIME = 400ns"
                    },
                ])
            },
            {
                $name: "TRETRY",
                description: "VDS_OCP and SEN_OCP retry time",
                bitWidth: 1,
                startBit: 10,
                enumEnable: false,
            },
        ])
    },
]

function getDRV8320SpiSettings(inst) {
    return {
        $name: "DRV8320_SPI_Interface",
        spiFrameSize: "16bits",
        rwSelect16Bits: [15],
        readBitValue: 1,
        writeBitValue: 0,
        addressSelect16Bits: [14, 13, 12, 11],
        dataSelect16Bits: [10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0],
        crcMode: "none",
        hiddenTextFieldForRegisterArgs: JSON.stringify(drv8320Registers),
	}
}

exports = {
	getDRV8320SpiSettings,
};