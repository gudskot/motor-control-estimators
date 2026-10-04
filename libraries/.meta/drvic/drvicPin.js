let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let references = system.getScript("/libraries/MCSDKLibraryReferences.js");

function onChangeFunction(inst, ui) {
    switch (inst.function) {
        case "custom":
            ui["polarity"].hidden = false;
            ui["toggle"].hidden = false;
            ui["delay"].hidden = false;
            break;
        case "unused":
            ui["polarity"].hidden = true;
            ui["toggle"].hidden = true;
            ui["delay"].hidden = true;
            break;
        case "brake":
            ui["polarity"].hidden = false;
            ui["toggle"].hidden = false;
            ui["delay"].hidden = true;
            break;
        case "enable":
            ui["polarity"].hidden = false;
            ui["toggle"].hidden = false;
            ui["delay"].hidden = false;
            break;
        case "fault":
            ui["polarity"].hidden = false;
            ui["toggle"].hidden = false;
            ui["delay"].hidden = true;
            break;
        case "led":
            ui["polarity"].hidden = false;
            ui["toggle"].hidden = false;
            ui["delay"].hidden = true;
            break;
        case "mode":
            ui["polarity"].hidden = false;
            ui["toggle"].hidden = false;
            ui["delay"].hidden = true;
            break;
        case "sleep":
            ui["polarity"].hidden = false;
            ui["toggle"].hidden = false;
            ui["delay"].hidden = false;
            break;
        default:
            break;
    }
}

let config = [
    {
        name: "$name",
        hidden: false,
        description: "Name your DRVIC module. Support for more than one DRVIC (corresponding to multiple motors) will be added in future releases of the tool."
    },
    {
        name: "function",
        displayName: "Pin Function",
        description: "Pin Function",
        default: "unused",
        options: [
            { name: "custom", displayName: "CUSTOM", description: "CUSTOM" },
            { name: "unused", displayName: "Unused", description: "Unused" },
            { name: "brake", displayName: "Brake", description: "Brake" },
            { name: "enable", displayName: "Enable", description: "Enable" },
            { name: "fault", displayName: "Fault", description: "Fault" },
            { name: "led", displayName: "LED", description: "LED" },
            { name: "mode", displayName: "Mode", description: "Mode" },
            { name: "sleep", displayName: "Sleep", description: "Sleep" },
            { name: "chipSelect", displayName: "Chip Select", description: "Chip Select" },
        ],
        onChange: onChangeFunction,
    },
    {
        name: "polarity",
        displayName: "Pin Polarity",
        description: "Pin Polarity",
        default: "activeHigh",
        hidden: true,
        options: [
            { name: "activeHigh", displayName: "Active High", description: "Active High" },
            { name: "activeLow", displayName: "Active Low", description: "Active Low" },
        ],    
    },
    {
        name: "toggle",
        displayName: "Toggle Pin",
        description: "Toggle Pin",
        default: false,
        hidden: true,
    },
    {
        name: "delay",
        displayName: "Delay (μs)",
        description: "Delay, in μs, after toggling pin",
        default: 0,
        hidden: true,
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

var drvicPinModule = {
    displayName: "Driver Pin",
    defaultInstanceName: "myDRVPin",
    description: "Driver Pin",
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

exports = drvicPinModule;