let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let references = system.getScript("/libraries/MCSDKLibraryReferences.js")

var libraryCategory = "control"
var librarySourceFileName = "mtpa"
var mcsdkLibraryName = "MTPA"

let config = [
    // {
    //     name: "Idq_ref_A",
    //     displayName: "Current reference d/q axis",
    //     default: 0
    // },
    // {
    //     name: "angleCurrent_rad",
    //     displayName: "Vector Is Angle",
    //     default: 0
    // },
    // {
    //     name: "Is_ref_A",
    //     displayName: "Vector Is Ref",
    //     default: 0
    // },
    // {
    //     name: "kconst",
    //     displayName: "K constant",
    //     default: 0
    // },
    // {
    //     name: "gconst",
    //     displayName: "G constant",
    //     default: 0
    // },
    // {
    //     name: "deltaIs_Ld_A",
    //     displayName: "Maximum Is Delta for Ld",
    //     default: 0
    // },
    // {
    //     name: "deltaIs_Lq_A",
    //     displayName: "Maximum Is Delta for Lq",
    //     default: 0
    // },
    // {
    //     name: "indexMax_Ld",
    //     displayName: "Maximum Is Index for Ld",
    //     default: 0
    // },
    // {
    //     name: "indexMax_Lq",
    //     displayName: "Maximum Is Index for Lq",
    //     default: 0
    // },
    // {
    //     name: "flagEnable",
    //     displayName: "Controller Flag Enable",
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
        references.getReferencePath("MTPA")
    ],
    validate                    : onValidate,
};




exports = mod;