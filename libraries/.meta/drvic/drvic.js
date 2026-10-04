let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let references = system.getScript("/libraries/MCSDKLibraryReferences.js");
let { drvBoards, getDrvSpiSettings, getDrvHwSettings } = system.getScript("/libraries/drvic/drvSettings/drvSettings.js")

let longDescription = "This driver interface module allows the ability to customize the interface between the motor control software and the motor driver chip. This interface can be configured as either a hardware interface or a SPI communication interface."

let spiBoards = [
    drvBoards.DRV8311S,
    drvBoards.DRV8316R, 
    drvBoards.DRV8317S,
    drvBoards.DRV8320RS,
    drvBoards.DRV8323RS,
    drvBoards.DRV8334,
    drvBoards.DRV8353RS,
    drvBoards.DRV8376S,
]

let hardwareBoards = [
    drvBoards.DRV7308,
    drvBoards.DRV8323RH,
    drvBoards.DRV8329A,
]

function onChangeMotorDriver(inst, ui) {
    ui["interfaceType"].readOnly = inst["motorDriver"] != "custom";
    ui["driverName"].hidden = inst["motorDriver"] != "custom";

    if (spiBoards.includes(inst["motorDriver"])) {
        inst["interfaceType"] = "spi"
    } else if (hardwareBoards.includes(inst["motorDriver"])) {
        inst["interfaceType"] = "hardware"
    }
}

let config = [
    {
        name: "$name",
        hidden: false,
        description: "Name your DRVIC module. Support for more than one DRVIC (corresponding to multiple motors) will be added in future releases of the tool."
    },
    {
        name: "motorDriver",
        displayName: "Motor Driver",
        description: "Motor Driver",
        default: "custom",
        options: [
            { name: "custom", displayName: "CUSTOM", description: "CUSTOM" },
            // { name: drvBoards.DRV8311S, displayName: "DRV8311 SPI", description: "DRV8311S" },
            { name: drvBoards.DRV8316R, displayName: "DRV8316 SPI", description: "DRV8316R" },
            // { name: drvBoards.DRV8317S, displayName: "DRV8317 SPI", description: "DRV8317S" },
            { name: drvBoards.DRV8320RS, displayName: "DRV8320 SPI", description: "DRV8320RS" },
            { name: drvBoards.DRV8323RS, displayName: "DRV8323 SPI", description: "DRV8323RS" },
            { name: drvBoards.DRV8334, displayName: "DRV8334 SPI", description: "DRV8334" },
            // { name: drvBoards.DRV8353RS, displayName: "DRV8353 SPI", description: "DRV8353RS" },
            { name: drvBoards.DRV8376S, displayName: "DRV8376 SPI", description: "DRV8376S" },
            { name: drvBoards.DRV7308, displayName: "DRV7308 Hardware", description: "DRV7308" },
            { name: drvBoards.DRV8323RH, displayName: "DRV8323 Hardware", description: "DRV8323RH" },
            { name: drvBoards.DRV8329A, displayName: "DRV8329 Hardware", description: "DRV8329A" },
        ],
        onChange: onChangeMotorDriver,
    },
    {
        name: "driverName",
        displayName: "Motor Driver Name",
        description: "Motor Driver Name",
        default: "DRV",
        hidden: false,
    },
    {
        name: "interfaceType",
        displayName: "Interface Type",
        description: "Interface Type",
        default: "hardware",
        options: [
            { name: "hardware", displayName: "HARDWARE", description: "Hardware" },
            { name: "spi", displayName: "SPI", description: "SPI Communication" },
        ],
    },
]

function modules(inst) {
    var staticOwnedInstances = []

    return staticOwnedInstances
}

function moduleInstances(inst) {
    let ownedInstances = []

    let args_requiredArgs = "args"
    if (inst.motorDriver != "custom") {
        args_requiredArgs = "requiredArgs"
    }

    // Only some motor drivers have a SPI interface
    if (inst.interfaceType == "spi") {
        let spiInterfaceModule = {
            name: "spiInterface",
            displayName: "Driver SPI Interface",
            moduleName: "/libraries/drvic/drvicSpiInterface.js",
            collapsed: false,
            requiredArgs: {
            }
        }

        let additionalSpiInterfaceSettings = getDrvSpiSettings(inst);
        spiInterfaceModule[args_requiredArgs] = {
            ...spiInterfaceModule[args_requiredArgs],
            ...additionalSpiInterfaceSettings
        }

        ownedInstances.push(spiInterfaceModule)
    }

    // All motor drivers should have ability to add a hardware interface connection
    let hwInterfaceModule = {
        name: "hardwareInterface",
        displayName: "Driver Hardware Interface",
        moduleName: "/libraries/drvic/drvicHardwareInterface.js",
        collapsed: false,
        requiredArgs: {
        }
    }

    let additionalHwInterfaceSettings = getDrvHwSettings(inst);
    hwInterfaceModule[args_requiredArgs] = {
        ...hwInterfaceModule[args_requiredArgs],
        ...additionalHwInterfaceSettings
    }

    ownedInstances.push(hwInterfaceModule)

    return ownedInstances
}

function onValidate(inst, validation) {

}

var drvicModule = {
    mcsdkLibraryName: "DRVIC",
    displayName: "Driver Interface (BETA)",
    longDescription: longDescription,
    defaultInstanceName: "myDRV",
    description: "DRV interface configuration",
    maxInstances: 1,
    templates: {
        mcsdk_libraries_h           : "/libraries/drvic/drvic/drvic.mcsdk_libraries.h.xdt",
        mcsdk_libraries_c           : "/libraries/drvic/drvic/drvic.mcsdk_libraries.c.xdt",
        mcsdk_libraries_opt         : "/libraries/drvic/drvic/drvic.mcsdk_libraries.opt.xdt",
        mcsdk_libraries_cmd_genlibs : "/libraries/drvic/drvic/drvic.mcsdk_libraries.cmd.genlibs.xdt",
    },
    config: config,
    references: [
    ],
    moduleInstances: moduleInstances,
    modules: modules,
    validate: onValidate,
};

exports = drvicModule;