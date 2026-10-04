let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let references = system.getScript("/libraries/MCSDKLibraryReferences.js");

let config = [
    {
        name: "$name",
        hidden: false,
        description: "Name your DRVIC module. Support for more than one DRVIC (corresponding to multiple motors) will be added in future releases of the tool."
    },
    {
        name: "hiddenTextFieldForPinArgs",
        displayName: "Instance Adder Arguments (JSON)",
        hidden: true,
        default: JSON.stringify([]),
    },
]

function modules(inst) {
    let staticOwnedInstances = []

    return staticOwnedInstances
}

function moduleInstances(inst) {
    let ownedInstances = []

    ownedInstances.push({
        name: "drvicPin",      
        displayName: "Driver Interface Pins",
        moduleName: "/libraries/drvic/drvicPin.js",
        useArray: true,
        minInstanceCount: Object.keys(JSON.parse(inst.hiddenTextFieldForPinArgs)).length,
        collapsed: false,
        fixedRequiredArgs: JSON.parse(inst.hiddenTextFieldForPinArgs),
        requiredArgs: {
        }
    })

    // ownedInstances.push({
    //     name: "drvicGPIO",
    //     displayName: "GPIO Configuration",
    //     moduleName: "/driverlib/gpio.js",
    //     requiredArgs : {
    //         $name: "DRV_IC_GPIO"
    //     },
    // })

    return ownedInstances
}

function onValidate(inst, validation) {

}

var drvicHardwareInterfaceModule = {
    displayName: "Driver Hardware Interface",
    defaultInstanceName: "myDRVHardwareInterface",
    description: "Driver Hardware Interface",
    config: config,
    moduleInstances: moduleInstances,
    modules: modules,
    templates: {
        // [transferCommon.getTransferPath() + "signalsight/hash/target/signalsight_hash.c.xdt"]: "",
        // [transferCommon.getTransferPath() + "signalsight/hash/target/signalsight_hash.h.xdt"]: "",
        // [transferCommon.getTransferPath() + "signalsight/hash/host/signalsight_hash.json.xdt"]: "",
    },
    validate: onValidate
};

exports = drvicHardwareInterfaceModule;