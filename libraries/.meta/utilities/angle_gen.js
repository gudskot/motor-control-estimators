let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let references = system.getScript("/libraries/MCSDKLibraryReferences.js")

var libraryCategory = "utilities"
var librarySourceFileName = "angle_gen"
var mcsdkLibraryName = "ANGLE_GEN"

let config = [
    {
        name: "frequency_Hz",
        displayName: "Freq Input Value",
        default: 0
    },
    {
        name: "angleDeltaFactor",
        displayName: "Predetermined value for angle compensation",
        default: 0
    },
    {
        name: "angleDelta_rad",
        displayName: "Angle Delta Value",
        default: 0
    },
    {
        name: "angle_rad",
        displayName: "Angle Output Value",
        default: 0
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
    config                      : config,
    references : [
        references.getReferencePath("ANGLE_GEN")
    ],
    validate                    : onValidate,
};




exports = mod;