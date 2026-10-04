let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let references = system.getScript("/libraries/MCSDKLibraryReferences.js");

let list7to0 = [
    { name: 7 },
    { name: 6 },
    { name: 5 },
    { name: 4 },
    { name: 3 },
    { name: 2 },
    { name: 1 },
    { name: 0 },
]

let list15to0 = [
    { name: 15 },
    { name: 14 },
    { name: 13 },
    { name: 12 },
    { name: 11 },
    { name: 10 },
    { name: 9 },
    { name: 8 },
    { name: 7 },
    { name: 6 },
    { name: 5 },
    { name: 4 },
    { name: 3 },
    { name: 2 },
    { name: 1 },
    { name: 0 },
]

let list23to0 = [
    { name: 23 },
    { name: 22 },
    { name: 21 },
    { name: 20 },
    { name: 19 },
    { name: 18 },
    { name: 17 },
    { name: 16 },
    { name: 15 },
    { name: 14 },
    { name: 13 },
    { name: 12 },
    { name: 11 },
    { name: 10 },
    { name: 9 },
    { name: 8 },
    { name: 7 },
    { name: 6 },
    { name: 5 },
    { name: 4 },
    { name: 3 },
    { name: 2 },
    { name: 1 },
    { name: 0 },
]

let list31to0 = [
    { name: 31 },
    { name: 30 },
    { name: 29 },
    { name: 28 },
    { name: 27 },
    { name: 26 },
    { name: 25 },
    { name: 24 },
    { name: 23 },
    { name: 22 },
    { name: 21 },
    { name: 20 },
    { name: 19 },
    { name: 18 },
    { name: 17 },
    { name: 16 },
    { name: 15 },
    { name: 14 },
    { name: 13 },
    { name: 12 },
    { name: 11 },
    { name: 10 },
    { name: 9 },
    { name: 8 },
    { name: 7 },
    { name: 6 },
    { name: 5 },
    { name: 4 },
    { name: 3 },
    { name: 2 },
    { name: 1 },
    { name: 0 },
]

function onChangeUi(inst, ui) {
    switch (inst["spiFrameSize"]) {
        case "8bits":
            ui["rwSelect8Bits"].hidden = false
            ui["addressSelect8Bits"].hidden = false
            ui["dataSelect8Bits"].hidden = false

            ui["rwSelect16Bits"].hidden = true
            ui["rwSelect24Bits"].hidden = true
            ui["rwSelect32Bits"].hidden = true
            ui["addressSelect16Bits"].hidden = true
            ui["addressSelect24Bits"].hidden = true
            ui["addressSelect32Bits"].hidden = true
            ui["dataSelect16Bits"].hidden = true
            ui["dataSelect24Bits"].hidden = true
            ui["dataSelect32Bits"].hidden = true

            if (inst["crcMode"] == "none") {
                ui["crcSelect8Bits"].hidden = true
                ui["crcSelect16Bits"].hidden = true
                ui["crcSelect24Bits"].hidden = true
                ui["crcSelect32Bits"].hidden = true    
                ui["crcMask"].hidden = true
                ui["crcInitValue"].hidden = true
                ui["crcPolynomial"].hidden = true
            } else if (inst["crcMode"] == "parity") {
                ui["crcSelect8Bits"].hidden = false
                ui["crcSelect16Bits"].hidden = true
                ui["crcSelect24Bits"].hidden = true
                ui["crcSelect32Bits"].hidden = true    
                ui["crcMask"].hidden = false
                ui["crcInitValue"].hidden = true
                ui["crcPolynomial"].hidden = true
            } else if (inst["crcMode"] == "crc") {
                ui["crcSelect8Bits"].hidden = false
                ui["crcSelect16Bits"].hidden = true
                ui["crcSelect24Bits"].hidden = true
                ui["crcSelect32Bits"].hidden = true    
                ui["crcMask"].hidden = false
                ui["crcInitValue"].hidden = false
                ui["crcPolynomial"].hidden = false
            }        
            break;
        case "16bits":
            ui["rwSelect16Bits"].hidden = false
            ui["addressSelect16Bits"].hidden = false
            ui["dataSelect16Bits"].hidden = false

            ui["rwSelect8Bits"].hidden = true
            ui["rwSelect24Bits"].hidden = true
            ui["rwSelect32Bits"].hidden = true
            ui["addressSelect8Bits"].hidden = true
            ui["addressSelect24Bits"].hidden = true
            ui["addressSelect32Bits"].hidden = true
            ui["dataSelect8Bits"].hidden = true
            ui["dataSelect24Bits"].hidden = true
            ui["dataSelect32Bits"].hidden = true

            if (inst["crcMode"] == "none") {
                ui["crcSelect8Bits"].hidden = true
                ui["crcSelect16Bits"].hidden = true
                ui["crcSelect24Bits"].hidden = true
                ui["crcSelect32Bits"].hidden = true    
                ui["crcMask"].hidden = true
                ui["crcInitValue"].hidden = true
                ui["crcPolynomial"].hidden = true
            } else if (inst["crcMode"] == "parity") {
                ui["crcSelect8Bits"].hidden = true
                ui["crcSelect16Bits"].hidden = false
                ui["crcSelect24Bits"].hidden = true
                ui["crcSelect32Bits"].hidden = true    
                ui["crcMask"].hidden = false
                ui["crcInitValue"].hidden = true
                ui["crcPolynomial"].hidden = true
            } else if (inst["crcMode"] == "crc") {
                ui["crcSelect8Bits"].hidden = true
                ui["crcSelect16Bits"].hidden = false
                ui["crcSelect24Bits"].hidden = true
                ui["crcSelect32Bits"].hidden = true    
                ui["crcMask"].hidden = false
                ui["crcInitValue"].hidden = false
                ui["crcPolynomial"].hidden = false
            }        
            break;
        case "24bits":
            ui["rwSelect24Bits"].hidden = false
            ui["addressSelect24Bits"].hidden = false
            ui["dataSelect24Bits"].hidden = false

            ui["rwSelect8Bits"].hidden = true
            ui["rwSelect16Bits"].hidden = true
            ui["rwSelect32Bits"].hidden = true
            ui["addressSelect8Bits"].hidden = true
            ui["addressSelect16Bits"].hidden = true
            ui["addressSelect32Bits"].hidden = true
            ui["dataSelect8Bits"].hidden = true
            ui["dataSelect16Bits"].hidden = true
            ui["dataSelect32Bits"].hidden = true

            if (inst["crcMode"] == "none") {
                ui["crcSelect8Bits"].hidden = true
                ui["crcSelect16Bits"].hidden = true
                ui["crcSelect24Bits"].hidden = true
                ui["crcSelect32Bits"].hidden = true    
                ui["crcMask"].hidden = true
                ui["crcInitValue"].hidden = true
                ui["crcPolynomial"].hidden = true
            } else if (inst["crcMode"] == "parity") {
                ui["crcSelect8Bits"].hidden = true
                ui["crcSelect16Bits"].hidden = true
                ui["crcSelect24Bits"].hidden = false
                ui["crcSelect32Bits"].hidden = true    
                ui["crcMask"].hidden = false
                ui["crcInitValue"].hidden = true
                ui["crcPolynomial"].hidden = true
            } else if (inst["crcMode"] == "crc") {
                ui["crcSelect8Bits"].hidden = true
                ui["crcSelect16Bits"].hidden = true
                ui["crcSelect24Bits"].hidden = false
                ui["crcSelect32Bits"].hidden = true    
                ui["crcMask"].hidden = false
                ui["crcInitValue"].hidden = false
                ui["crcPolynomial"].hidden = false
            }      
            break;
        case "32bits":
            ui["rwSelect32Bits"].hidden = false
            ui["addressSelect32Bits"].hidden = false
            ui["dataSelect32Bits"].hidden = false

            ui["rwSelect8Bits"].hidden = true
            ui["rwSelect16Bits"].hidden = true
            ui["rwSelect24Bits"].hidden = true
            ui["addressSelect8Bits"].hidden = true
            ui["addressSelect16Bits"].hidden = true
            ui["addressSelect24Bits"].hidden = true
            ui["dataSelect8Bits"].hidden = true
            ui["dataSelect16Bits"].hidden = true
            ui["dataSelect24Bits"].hidden = true

            if (inst["crcMode"] == "none") {
                ui["crcSelect8Bits"].hidden = true
                ui["crcSelect16Bits"].hidden = true
                ui["crcSelect24Bits"].hidden = true
                ui["crcSelect32Bits"].hidden = true    
                ui["crcMask"].hidden = true
                ui["crcInitValue"].hidden = true
                ui["crcPolynomial"].hidden = true
            } else if (inst["crcMode"] == "parity") {
                ui["crcSelect8Bits"].hidden = true
                ui["crcSelect16Bits"].hidden = true
                ui["crcSelect24Bits"].hidden = true
                ui["crcSelect32Bits"].hidden = false    
                ui["crcMask"].hidden = false
                ui["crcInitValue"].hidden = true
                ui["crcPolynomial"].hidden = true
            } else if (inst["crcMode"] == "crc") {
                ui["crcSelect8Bits"].hidden = true
                ui["crcSelect16Bits"].hidden = true
                ui["crcSelect24Bits"].hidden = true
                ui["crcSelect32Bits"].hidden = false    
                ui["crcMask"].hidden = false
                ui["crcInitValue"].hidden = false
                ui["crcPolynomial"].hidden = false
            }      
            break; 
        default:
            break;
    }
}

function onChangeSpiFrameSize(inst, ui) {
    onChangeUi(inst, ui)
}

function onChangeCrcMode(inst, ui) {
    onChangeUi(inst, ui)
}

function getMask(bitSelectArray, maskWidth) {
    return `0x${bitSelectArray.reduce((acc, val) => acc + Math.pow(2, val), 0).toString(16).padStart(maskWidth, "0").toUpperCase()}`
}

let config = [
    {
        name: "$name",
        hidden: false,
        description: "Name your DRVIC module. Support for more than one DRVIC (corresponding to multiple motors) will be added in future releases of the tool.",
    },
    {
        name: "spiFrameSize",
        displayName: "SPI Frame Size",
        description: "SPI Frame Size",
        default: "8bits",
        options: [
            { name: "8bits", displayName: "8 Bits", description: "8 Bits" },
            { name: "16bits", displayName: "16 Bits", description: "16 Bits" },
            { name: "24bits", displayName: "24 Bits", description: "24 Bits" },
            { name: "32bits", displayName: "32 Bits", description: "32 Bits" },
        ],
        onChange: onChangeSpiFrameSize,
    },
    {
        name: "GROUP_READ_WRITE",
        config: [
            {
                name: "rwSelect8Bits",
                displayName: "Read/Write Bits",
                description: "Read/Write Bits",
                minSelections: 0,
                default: [],
                hidden: false,
                options: list7to0,
            },
            {
                name: "rwSelect16Bits",
                displayName: "Read/Write Bits",
                description: "Read/Write Bits",
                minSelections: 0,
                default: [],
                hidden: true,
                options: list15to0,
            },
            {
                name: "rwSelect24Bits",
                displayName: "Read/Write Bits",
                description: "Read/Write Bits",
                minSelections: 0,
                default: [],
                hidden: true,
                options: list23to0,
            },
            {
                name: "rwSelect32Bits",
                displayName: "Read/Write Bits",
                description: "Read/Write Bits",
                minSelections: 0,
                default: [],
                hidden: true,
                options: list31to0,
            },
            {
                name: "rwSelectBits",
                minSelections: 0,
                default: [],
                hidden: true,
                options: list31to0,
                getValue: (inst) => {
                    let rwSelectBits = []
                    switch (inst["spiFrameSize"]) {
                        case "8bits":
                            rwSelectBits = inst["rwSelect8Bits"]
                            break;
                        case "16bits":
                            rwSelectBits = inst["rwSelect16Bits"]
                            break;
                        case "24bits":
                            rwSelectBits = inst["rwSelect24Bits"]
                            break;
                        case "32bits":
                            rwSelectBits = inst["rwSelect32Bits"]
                            break; 
                        default:
                            break;
                    }
                    return rwSelectBits
                }
            },
            {
                name: "rwMask",
                displayName: "Read/Write Mask",
                description: "Read/Write Mask",
                default: "0x0",
                getValue: (inst) => {
                    let rwMask = "0x0"
                    switch (inst["spiFrameSize"]) {
                        case "8bits":
                            rwMask = getMask(inst["rwSelect8Bits"], 2)
                            break;
                        case "16bits":
                            rwMask = getMask(inst["rwSelect16Bits"], 4)
                            break;
                        case "24bits":
                            rwMask = getMask(inst["rwSelect24Bits"], 6)
                            break;
                        case "32bits":
                            rwMask = getMask(inst["rwSelect32Bits"], 8)
                            break; 
                        default:
                            break;
                    }
                    return rwMask
                },
            }, 
            {
                name: "readBitValue",
                displayName: "Read/Write Bit Value for Read",
                description: "Read/Write Bit Value for Read",
                default: 1,
                options: [
                    { name: 0 },
                    { name: 1 },
                ],
            },
            {
                name: "writeBitValue",
                displayName: "Read/Write Bit Value for Write",
                description: "Read/Write Bit Value for Write",
                default: 0,
                options: [
                    { name: 0 },
                    { name: 1 },
                ],
            },   
        ]
    },
    {
        name: "GROUP_ADDRESS",
        config: [
            {
                name: "addressSelect8Bits",
                displayName: "Address Bits",
                description: "Address Bits",
                minSelections: 0,
                default: [],
                hidden: false,
                options: list7to0,
            },
            {
                name: "addressSelect16Bits",
                displayName: "Address Bits",
                description: "Address Bits",
                minSelections: 0,
                default: [],
                hidden: true,
                options: list15to0,
            },
            {
                name: "addressSelect24Bits",
                displayName: "Address Bits",
                description: "Address Bits",
                minSelections: 0,
                default: [],
                hidden: true,
                options: list23to0,
            },
            {
                name: "addressSelect32Bits",
                displayName: "Address Bits",
                description: "Address Bits",
                minSelections: 0,
                default: [],
                hidden: true,
                options: list31to0,
            },
            {
                name: "addressSelectBits",
                minSelections: 0,
                default: [],
                hidden: true,
                options: list31to0,
                getValue: (inst) => {
                    let addressSelectBits = []
                    switch (inst["spiFrameSize"]) {
                        case "8bits":
                            addressSelectBits = inst["addressSelect8Bits"]
                            break;
                        case "16bits":
                            addressSelectBits = inst["addressSelect16Bits"]
                            break;
                        case "24bits":
                            addressSelectBits = inst["addressSelect24Bits"]
                            break;
                        case "32bits":
                            addressSelectBits = inst["addressSelect32Bits"]
                            break; 
                        default:
                            break;
                    }
                    return addressSelectBits
                }
            },
            {
                name: "addressMask",
                displayName: "Address Mask",
                description: "Address Mask",
                default: "0x0",
                getValue: (inst) => {
                    let addressMask = "0x0"
                    switch (inst["spiFrameSize"]) {
                        case "8bits":
                            addressMask = getMask(inst["addressSelect8Bits"], 2)
                            break;
                        case "16bits":
                            addressMask = getMask(inst["addressSelect16Bits"], 4)
                            break;
                        case "24bits":
                            addressMask = getMask(inst["addressSelect24Bits"], 6)
                            break;
                        case "32bits":
                            addressMask = getMask(inst["addressSelect32Bits"], 8)
                            break; 
                        default:
                            break;
                    }
                    return addressMask
                },
            },        
        ]
    },
    {
        name: "GROUP_DATA",
        config: [
            {
                name: "dataSelect8Bits",
                displayName: "Data Bits",
                description: "Data Bits",
                minSelections: 0,
                default: [],
                hidden: false,
                options: list7to0,
            },
            {
                name: "dataSelect16Bits",
                displayName: "Data Bits",
                description: "Data Bits",
                minSelections: 0,
                default: [],
                hidden: true,
                options: list15to0,
            },
            {
                name: "dataSelect24Bits",
                displayName: "Data Bits",
                description: "Data Bits",
                minSelections: 0,
                default: [],
                hidden: true,
                options: list23to0,
            },
            {
                name: "dataSelect32Bits",
                displayName: "Data Bits",
                description: "Data Bits",
                minSelections: 0,
                default: [],
                hidden: true,
                options: list31to0,
            },
            {
                name: "dataSelectBits",
                minSelections: 0,
                default: [],
                hidden: true,
                options: list31to0,
                getValue: (inst) => {
                    let dataSelectBits = []
                    switch (inst["spiFrameSize"]) {
                        case "8bits":
                            dataSelectBits = inst["dataSelect8Bits"]
                            break;
                        case "16bits":
                            dataSelectBits = inst["dataSelect16Bits"]
                            break;
                        case "24bits":
                            dataSelectBits = inst["dataSelect24Bits"]
                            break;
                        case "32bits":
                            dataSelectBits = inst["dataSelect32Bits"]
                            break; 
                        default:
                            break;
                    }
                    return dataSelectBits
                }
            },
            {
                name: "dataMask",
                displayName: "Data Mask",
                description: "Data Mask",
                default: "0x0",
                getValue: (inst) => {
                    let dataMask = "0x0"
                    switch (inst["spiFrameSize"]) {
                        case "8bits":
                            dataMask = getMask(inst["dataSelect8Bits"], 2)
                            break;
                        case "16bits":
                            dataMask = getMask(inst["dataSelect16Bits"], 4)
                            break;
                        case "24bits":
                            dataMask = getMask(inst["dataSelect24Bits"], 6)
                            break;
                        case "32bits":
                            dataMask = getMask(inst["dataSelect32Bits"], 8)
                            break; 
                        default:
                            break;
                    }
                    return dataMask
                },
            },        
        ]
    },
    {
        name: "GROUP_CRC",
        config: [
            {
                name: "crcMode",
                displayName: "CRC Mode",
                description: "CRC Mode",
                default: "none",
                options: [
                    { name: "none", displayName: "No CRC", description: "No CRC" },
                    { name: "parity", displayName: "Single Bit Parity", description: "Single Bit Parity" },
                    { name: "crc", displayName: "Polynomial CRC", description: "Polynomial CRC" },
                ],
                onChange: onChangeCrcMode,
            },
            {
                name: "crcSelect8Bits",
                displayName: "CRC Bits",
                description: "CRC Bits",
                minSelections: 0,
                default: [],
                hidden: true,
                options: list7to0,
            },
            {
                name: "crcSelect16Bits",
                displayName: "CRC Bits",
                description: "CRC Bits",
                minSelections: 0,
                default: [],
                hidden: true,
                options: list15to0,
            },
            {
                name: "crcSelect24Bits",
                displayName: "CRC Bits",
                description: "CRC Bits",
                minSelections: 0,
                default: [],
                hidden: true,
                options: list23to0,
            },
            {
                name: "crcSelect32Bits",
                displayName: "CRC Bits",
                description: "CRC Bits",
                minSelections: 0,
                default: [],
                hidden: true,
                options: list31to0,
            },
            {
                name: "crcSelectBits",
                minSelections: 0,
                default: [],
                hidden: true,
                options: list31to0,
                getValue: (inst) => {
                    let crcSelectBits = []
                    switch (inst["spiFrameSize"]) {
                        case "8bits":
                            crcSelectBits = inst["crcSelect8Bits"]
                            break;
                        case "16bits":
                            crcSelectBits = inst["crcSelect16Bits"]
                            break;
                        case "24bits":
                            crcSelectBits = inst["crcSelect24Bits"]
                            break;
                        case "32bits":
                            crcSelectBits = inst["crcSelect32Bits"]
                            break; 
                        default:
                            break;
                    }
                    return crcSelectBits
                }
            },
            {
                name: "crcMask",
                displayName: "CRC Mask",
                description: "CRC Mask",
                hidden: true,
                default: "0x0",
                getValue: (inst) => {
                    let crcMask = "0x0"
                    switch (inst["spiFrameSize"]) {
                        case "8bits":
                            crcMask = getMask(inst["crcSelect8Bits"], 2)
                            break;
                        case "16bits":
                            crcMask = getMask(inst["crcSelect16Bits"], 4)
                            break;
                        case "24bits":
                            crcMask = getMask(inst["crcSelect24Bits"], 6)
                            break;
                        case "32bits":
                            crcMask = getMask(inst["crcSelect32Bits"], 8)
                            break; 
                        default:
                            break;
                    }
                    return crcMask
                },
            },
            {
                name: "crcInitValue",
                displayName: "CRC Initial Value",
                description: "CRC Initial Value",
                hidden: true,
                default: "0x0",
            },
            {
                name: "crcPolynomial",
                displayName: "CRC Polynomial",
                description: "CRC Polynomial",
                hidden: true,
                default: "0x0",
            },        
        ]
    },
    {
        name: "hiddenTextFieldForRegisterArgs",
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
        name: "drvicRegister",      
        displayName: "Memory Map Registers",
        moduleName: "/libraries/drvic/drvicRegister.js",
        useArray: true,
        minInstanceCount: Object.keys(JSON.parse(inst.hiddenTextFieldForRegisterArgs)).length,
        collapsed: false,
        fixedRequiredArgs: JSON.parse(inst.hiddenTextFieldForRegisterArgs),
        requiredArgs: {
        }
    })

    ownedInstances.push({
        name: "drvicSPI",      
        displayName: "SPI Configuration",
        moduleName: "/driverlib/spi.js",
        requiredArgs: {
            $name : "MTR1_SPI",
            transferProtocol: "SPI_PROT_POL0PHA0",
            mode: "SPI_MODE_CONTROLLER",
            emulationMode: "SPI_EMULATION_FREE_RUN",
            dataWidth: "16",
            useFifo: true,
            loopback: false,
        },
        args: {
            bitRate: 1000000,
        }
    })

    return ownedInstances
}

function onValidate(inst, validation) {
    const hasDuplicates = arr => new Set(arr).size !== arr.length;
    let allBits;

    switch (inst.spiFrameSize) {
        case "8bits":
            allBits = ["rwSelect8Bits", "addressSelect8Bits", "dataSelect8Bits"]
            if (inst.crcMode != "none") allBits.push("crcSelect8Bits")
            break;
        case "16bits":
            allBits = ["rwSelect16Bits", "addressSelect16Bits", "dataSelect16Bits"]
            if (inst.crcMode != "none") allBits.push("crcSelect16Bits")
            break;
        case "24bits":
            allBits = ["rwSelect24Bits", "addressSelect24Bits", "dataSelect24Bits"]
            if (inst.crcMode != "none") allBits.push("crcSelect24Bits")
            break;
        case "32bits":
            allBits = ["rwSelect32Bits", "addressSelect32Bits", "dataSelect32Bits"]
            if (inst.crcMode != "none") allBits.push("crcSelect32Bits")
            break; 
        default:
            break;
    }
    
    // Verify that no bits in SPI frame are being duplicated across multiple masks
    const combinedArray = [inst[allBits[0]], inst[allBits[1]], inst[allBits[2]]]
    if (inst.crcMode != "none") combinedArray.push(inst[allBits[3]])
    if (hasDuplicates(combinedArray.flat())) {
        allBits.forEach((e) => {
            validation.logError("Cannot repeat bits in SPI frame", inst, e)    
        })
    }

    if (inst[allBits[0]].length > 1) {
        validation.logWarning("Read/Write bit is typically only a single bit in the SPI frame", inst, allBits[0])
    }

    if (inst.readBitValue == inst.writeBitValue) {
        validation.logError("Read Bit Value cannot be the same as Write Bit Value", inst, "readBitValue")
        validation.logError("Read Bit Value cannot be the same as Write Bit Value", inst, "writeBitValue")
    }
}

var drvicSpiInterfaceModule = {
    displayName: "Driver SPI Interface",
    defaultInstanceName: "myDRVSPIInterface",
    description: "Driver SPI Interface",
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

exports = drvicSpiInterfaceModule;