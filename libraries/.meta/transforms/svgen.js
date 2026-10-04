let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let references = system.getScript("/libraries/MCSDKLibraryReferences.js");

var libraryCategory = "transforms"
var librarySourceFileName = "svgen"
var mcsdkLibraryName = "SVGEN"

let config = [
    // {
    //     name: "oneOverDcBus_invV",
    //     displayName: "The inverse DC bus voltage value",
    //     default: 0
    // },
    // {
    //     name: "sector",
    //     displayName: "Sector value of space vecto",
    //     default: 0
    // },
    {
        name: "svmMode",
        displayName: "Mode of SVGEN",
        default: "SVM_COM_C",
        options: [
            { name: "SVM_COM_C", description: "SVPWM common SVM mode" },
            { name: "SVM_MIN_C", description: "DPWM minimum SVM mode" },
            { name: "SVM_MAX_C", description: "DPWM maximum SVM mode" },
            { name: "SVM_DQ_S", description: "SVPWM standard DQ mode" },
        ],
    }
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
    references: [
        references.getReferencePath("SVGEN"),
        references.getReferencePath("SVGEN_CURRENT")
    ],
    config                      : config,
    validate                    : onValidate,
};




exports = mod;