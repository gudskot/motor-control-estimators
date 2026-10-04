let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let references = system.getScript("/libraries/MCSDKLibraryReferences.js")

var libraryCategory = "control"
var librarySourceFileName = "fwc"
var mcsdkLibraryName = "FWC"

let config = [
    // {
    //     name: "pi_fwc",
    //     displayName: "FWC PI Controller",
    //     config : [
    //         {
    //             name: "kpVal",
    //             displayName: "Proportional Gain (Kp)",
    //             default: 0
    //         },
    //         {
    //             name: "kiVal",
    //             displayName: "Integral Gain (KI)",
    //             default: 0
    //         },
    //         {
    //             name: "max_angle",
    //             displayName: "Maximum FWC Angle (rad)",
    //             default: 0
    //         }
    //     ]
    // },
    // {
    //     name: "angleCurrent_rad",
    //     displayName: "Current Phase Angle",
    //     default: 0
    // },
    // {
    //     name: "flagEnable",
    //     displayName: "Controller Flag Enable ",
    //     default: false
    // },
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
        references.getReferencePath("FWC")
    ],
    validate                    : onValidate,
};




exports = mod;