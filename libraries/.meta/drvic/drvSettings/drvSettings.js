let Common = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let references = system.getScript("/libraries/MCSDKLibraryReferences.js");

let drv7308 = system.getScript("/libraries/drvic/drvSettings/drv7308.js")
let drv8311 = system.getScript("/libraries/drvic/drvSettings/drv8311.js")
let drv8316 = system.getScript("/libraries/drvic/drvSettings/drv8316.js")
let drv8317 = system.getScript("/libraries/drvic/drvSettings/drv8317.js")
let drv8320 = system.getScript("/libraries/drvic/drvSettings/drv8320.js")
let drv8323 = system.getScript("/libraries/drvic/drvSettings/drv8323.js")
let drv8329 = system.getScript("/libraries/drvic/drvSettings/drv8329.js")
let drv8334 = system.getScript("/libraries/drvic/drvSettings/drv8334.js")
let drv8353 = system.getScript("/libraries/drvic/drvSettings/drv8353.js")
let drv8376 = system.getScript("/libraries/drvic/drvSettings/drv8376.js")

let drvBoards = {
    DRV7308: "DRV7308",
    DRV8311S: "DRV8311S",
    DRV8316R: "DRV8316R",
    DRV8317S: "DRV8317S",
    DRV8320RS: "DRV8320RS",
    DRV8323RH: "DRV8323RH",
    DRV8323RS: "DRV8323RS",
    DRV8329A: "DRV8329A",
    DRV8334: "DRV8334",
    DRV8353RS: "DRV8353RS",
    DRV8376S: "DRV8376S",
}

function getDrvSpiSettings(inst) {
    let drvSpiSettings = {};

    switch (inst.motorDriver) {
        case drvBoards.DRV8311S:
            drvSpiSettings = drv8311.getDRV8311SpiSettings(inst)
            break;
        case drvBoards.DRV8316R:
            drvSpiSettings = drv8316.getDRV8316SpiSettings(inst)
            break;
        case drvBoards.DRV8317S:
            drvSpiSettings = drv8317.getDRV8317SpiSettings(inst)
            break;
        case drvBoards.DRV8320RS:
            drvSpiSettings = drv8320.getDRV8320SpiSettings(inst)
            break;    
        case drvBoards.DRV8323RS:
            drvSpiSettings = drv8323.getDRV8323SpiSettings(inst)
            break;
        case drvBoards.DRV8334:
            drvSpiSettings = drv8334.getDRV8334SpiSettings(inst)
            break;
        case drvBoards.DRV8353RS:
            drvSpiSettings = drv8353.getDRV8353SpiSettings(inst)
            break;
        case drvBoards.DRV8376S:
            drvSpiSettings = drv8376.getDRV8376SpiSettings(inst)
            break;
        default:
            break;
    }

	return drvSpiSettings;
}

function getDrvHwSettings(inst) {
    let drvHwSettings = {};

    switch (inst.motorDriver) {
        case drvBoards.DRV7308:
            drvHwSettings = drv7308.getDRV7308HwSettings(inst)
            break;
        case drvBoards.DRV8323RH:
            drvHwSettings = drv8323.getDRV8323RhHwSettings(inst)
            break;
        case drvBoards.DRV8323RS:
            drvHwSettings = drv8323.getDRV8323RsHwSettings(inst)
            break;
        case drvBoards.DRV8329A:
            drvHwSettings = drv8329.getDRV8329HwSettings(inst)
            break;
        default:
            break;
    }

    return drvHwSettings;
}

exports = {
    drvBoards,
	getDrvSpiSettings,
    getDrvHwSettings,
};

/* Notes for future implementation
We should NOT use enableBitEnum: true in the drvSettings js files, since this prevents customers from enabling and disabling the registers on their own.
UMCL project should be the one to enable these options when the DRVIC gets pulled as an instance module. For now, the below are the settings which were originally configured:

drv8311 enabledEnums: ["REG_LOCK_UNLOCK"] 
drv8316 enabledEnums: ["REG_LOCK_UNLOCK", "CLR_FLT_CLEAR", "PWM_MODE_6_N", "SLEW_50V", "CSA_GAIN_0p15VpA", "BUCK_DIS_DISABLE", "BUCK_SEL_3p3V"] 
drv8317 enabledEnums: ["REG_LOCK_UNLOCK"] 
drv8320 enabledEnums: ["LOCK_UNLOCK"] 
drv8323 enabledEnums: ["PWM_MODE_6", "OTW_REP_REPORT", "LOCK_UNLOCK", "VDS_LEVEL_1P700_V", "AUTOMATIC_RETRY", "DEAD_TIME_100_NS", "CSA_GAIN_10VPV", "LS_REF_SHX_TO_SPX", "VREF_DIV_2", "CSA_FET_SPX"] 
drv8334 enabledEnums: ["LOCK_UNLOCK"] 
drv8353 enabledEnums: ["ISINK_HS_1P640_A", "ISOUR_HS_0P820_A", "LOCK_UNLOCK", "ISINK_LS_1P640_A", "ISOUR_LS_0P820_A", "VDS_LEVEL_1P500_V", "LATCHED_SHUTDOWN", "DEAD_TIME_100_NS", "CSA_GAIN_10VPV", "LS_REF_SHX_TO_SPX", "VREF_DIV_2", "CSA_FET_SPX"] 
drv8376 enabledEnums: ["REG_LOCK_UNLOCK"] 
*/