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
        name: "registerName",
        displayName: "Register Name",
        description: "Register Name",
        default: "DRV Status Register",
    },
    {
        name: "offset",
        displayName: "Offset",
        description: "Offset",
        default: 0,
    },
    {
        name: "registerType",
        displayName: "Register Type",
        description: "Register Type",
        default: "status",
        options: [
            { name: "status", displayName: "STATUS", description: "STATUS" },
            { name: "control", displayName: "CONTROL", description: "CONTROL" },
        ],    
    },
    {
        name: "hiddenTextFieldForBitArgs",
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
        name: "drvicRegisterBit",      
        displayName: "Register Bits",
        moduleName: "/libraries/drvic/drvicRegisterBit.js",
        useArray: true,
        minInstanceCount: Object.keys(JSON.parse(inst.hiddenTextFieldForBitArgs)).length,
        collapsed: false,
        fixedRequiredArgs: JSON.parse(inst.hiddenTextFieldForBitArgs),
        requiredArgs: {
        }
    })

    return ownedInstances
}

function onValidate(inst, validation) {
}

var drvicRegisterModule = {
    displayName: "Driver Register",
    defaultInstanceName: "myDRVRegister",
    description: "Driver Register",
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

exports = drvicRegisterModule;