let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let references = system.getScript("/libraries/MCSDKLibraryReferences.js")

var libraryCategory = "observers"
var librarySourceFileName = "ssipd"
var mcsdkLibraryName = "SSIPD"

let config = [
    // {
    //     name: "VdSet_V",
    //     displayName: "Output-Set Voltage",
    //     default: 0
    // },
    // {
    //     name: "VdInject_V",
    //     displayName: "Output-Injection Voltage",
    //     default: 0
    // },
    // {
    //     name: "IsTemp_A",
    //     displayName: "IsTemp_A",
    //     default: 0
    // },
    // {
    //     name: "IsPeak_A",
    //     displayName: "IsPeak_A",
    //     default: 0
    // },
    // {
    //     name: "angleTemp_rad",
    //     displayName: "Detection Temperature Angle",
    //     default: 0
    // },
    // {
    //     name: "angleCmd_rad",
    //     displayName: "Detection Command Angle",
    //     default: 0
    // },
    // {
    //     name: "angleOut_rad",
    //     displayName: "Detection Output Angle",
    //     default: 0
    // },
    // {
    //     name: "angleInc_rad",
    //     displayName: "Detection Delta Angle",
    //     default: 0
    // },
    // {
    //     name: "angleMax_rad",
    //     displayName: "Detection Maximum Angle",
    //     default: 0
    // },
    // {
    //     name: "pulseWidth",
    //     displayName: "Pulse Width",
    //     default: 0
    // },
    // {
    //     name: "pulseCount",
    //     displayName: "Pulse Count",
    //     default: 0
    // },
    // {
    //     name: "flagDirection",
    //     displayName: "Flag Direction",
    //     default: false
    // },
    // {
    //     name: "flagEnablePWM",
    //     displayName: "Flag Enable PWM",
    //     default: false
    // },
    // {
    //     name: "flagDoneStatus",
    //     displayName: "Flag Done Statis",
    //     default: false
    // },
    // {
    //     name: "flagRunState",
    //     displayName: "Flag Run State",
    //     default: false
    // }
]

function onValidate(inst, validation) {

}

var mod = {
    mcsdkLibraryName            : mcsdkLibraryName,
    displayName                 : mcsdkLibraryName,
    defaultInstanceName         : "my" + mcsdkLibraryName,
    description                 : mcsdkLibraryName + " short description",
    longDescription             :  mcsdkLibraryName + " long description",
    templates: {
        mcsdk_libraries_h           : "/libraries/" + libraryCategory + "/" + librarySourceFileName + "/" + librarySourceFileName + ".mcsdk_libraries.h.xdt",
        mcsdk_libraries_c           : "/libraries/" + libraryCategory + "/" + librarySourceFileName + "/" + librarySourceFileName + ".mcsdk_libraries.c.xdt",
        mcsdk_libraries_opt         : "/libraries/" + libraryCategory + "/" + librarySourceFileName + "/" + librarySourceFileName + ".mcsdk_libraries.opt.xdt",
        mcsdk_libraries_cmd_genlibs : "/libraries/" + libraryCategory + "/" + librarySourceFileName + "/" + librarySourceFileName + ".mcsdk_libraries.cmd.genlibs.xdt",
    },
    config                      : config,
    references : [
        references.getReferencePath("SSIPD")
    ],
    validate                    : onValidate,
};




exports = mod;