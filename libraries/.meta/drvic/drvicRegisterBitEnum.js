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
        name: "bitValue",
        displayName: "Bit Value",
        description: "Bit Value",
        default: 0,
    },
    {
        name: "description",
        displayName: "Enum Description",
        description: "Enum Description",
        default: "Register Bit Enum Description",
    },
    {
        name: "enableBitEnum",
        displayName: "Initialize register to this enum?",
        description: "Initialize register to this enum?",
        default: false,
    },
]

function modules(inst) {
    let staticOwnedInstances = []

    return staticOwnedInstances
}

function moduleInstances(inst) {
    let ownedInstances = []

    return ownedInstances
}

function onValidate(inst, validation) {

}

var drvicRegisterBitEnumModule = {
    displayName: "Driver Register Bit Enum",
    defaultInstanceName: "myDRVRegisterBitEnum",
    description: "Driver Register Bit Enum",
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

exports = drvicRegisterBitEnumModule;