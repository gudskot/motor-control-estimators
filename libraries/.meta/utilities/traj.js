let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let references = system.getScript("/libraries/MCSDKLibraryReferences.js")

var libraryCategory = "utilities"
var librarySourceFileName = "traj"
var mcsdkLibraryName = "TRAJ"

let config = [
    {
        name: "targetValue",
        displayName: "Target Value for the trajectory",
        default: 0
    },
    {
        name: "intValue",
        displayName: "Intermediate Value along Trajectory",
        default: 0
    },
    {
        name: "minValue",
        displayName: "Minimum Value for the traj gen",
        default: 0
    },
    {
        name: "maxValue",
        displayName: "Maximum Value for the traj gen",
        default: 0
    },
    {
        name: "maxDelta",
        displayName: "Maximum delta Value for the traj gen",
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
        references.getReferencePath("TRAJ")
    ],
    validate                    : onValidate,
};




exports = mod;