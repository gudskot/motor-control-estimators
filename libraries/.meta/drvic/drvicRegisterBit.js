let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let references = system.getScript("/libraries/MCSDKLibraryReferences.js");

let list0to7 = [
    { name: 0 },
    { name: 1 },
    { name: 2 },
    { name: 3 },
    { name: 4 },
    { name: 5 },
    { name: 6 },
    { name: 7 },
]

let list0to15 = [
    { name: 0 },
    { name: 1 },
    { name: 2 },
    { name: 3 },
    { name: 4 },
    { name: 5 },
    { name: 6 },
    { name: 7 },
    { name: 8 },
    { name: 9 },
    { name: 10 },
    { name: 11 },
    { name: 12 },
    { name: 13 },
    { name: 14 },
    { name: 15 },
]

let list1to8 = [
    { name: 1 },
    { name: 2 },
    { name: 3 },
    { name: 4 },
    { name: 5 },
    { name: 6 },
    { name: 7 },
    { name: 8 },
]

let list1to16 = [
    { name: 1 },
    { name: 2 },
    { name: 3 },
    { name: 4 },
    { name: 5 },
    { name: 6 },
    { name: 7 },
    { name: 8 },
    { name: 9 },
    { name: 10 },
    { name: 11 },
    { name: 12 },
    { name: 13 },
    { name: 14 },
    { name: 15 },
    { name: 16 },

]

function onChangeBitWidth(inst, ui) {
    ui["endBit"].hidden = inst["bitWidth"] <= 1;
}

let config = [
    {
        name: "$name",
        hidden: false,
        description: "Name your Register Bit. This should match exactly with the bit name in the motor driver's datasheet register map. Note that FAULT is a reserved keyword. Register bits with the FAULT keyword will be monitored during the motor driver initialization routine"
    },
    {
        name: "description",
        displayName: "Bit Description",
        description: "Bit Description",
        default: "Bit Description",
    },
    {
        name: "bitWidth",
        displayName: "Bit Width",
        description: "Bit Width",
        default: 1,
        options: list1to16,
        onChange: onChangeBitWidth,
    },
    {
        name: "startBit",
        displayName: "Start Bit",
        description: "Start Bit",
        default: 0,
        options: list0to15,
    },
    {
        name: "endBit",
        displayName: "End Bit",
        description: "End Bit",
        default: 0,
        hidden: true,
        getValue: (inst) => {
            return (parseInt((inst.startBit + inst.bitWidth - 1)))
        },
    },
    {
        name: "enumEnable",
        displayName: "Define custom enum?",
        description: "Defines a custom enumeration in the motor driver interface header file",
        default: false,
    },
    {
        name: "hiddenTextFieldForEnumArgs",
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

    if (inst.enumEnable) {
        ownedInstances.push({
            name: "drvicRegisterBitEnum",      
            displayName: "Register Bit Enums",
            moduleName: "/libraries/drvic/drvicRegisterBitEnum.js",
            useArray: true,
            minInstanceCount: Object.keys(JSON.parse(inst.hiddenTextFieldForEnumArgs)).length,
            maxInstanceCount: Math.pow(2,inst.bitWidth),
            collapsed: false,
            fixedRequiredArgs: JSON.parse(inst.hiddenTextFieldForEnumArgs),
            requiredArgs: {
            }
        })
    }

    return ownedInstances
}

function onValidate(inst, validation) {
    // Verify that no bits do not exceed register size
    if (inst.endBit > 15) {
        validation.logError(
            "End bit cannot be greater than 15",
            inst, "endBit");
    }

    // Append notice regarding FAULT keyword
    if (inst.$name.toLowerCase() == "fault") {
        validation.logInfo(
            "Register bit named with FAULT keyword will be monitored during motor driver initialization",
            inst, "$name");    
    }
}

var drvicRegisterBitModule = {
    displayName: "Driver Register Bit",
    defaultInstanceName: "myDRVRegisterBit",
    description: "Driver Register Bit",
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

exports = drvicRegisterBitModule;