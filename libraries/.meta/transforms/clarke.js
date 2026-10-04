let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let references = system.getScript("/libraries/MCSDKLibraryReferences.js");

var libraryCategory = "transforms"
var librarySourceFileName = "clarke"
var mcsdkLibraryName = "CLARKE"

let config = [
    // {
    //     name: "numberOfSensors",
    //     displayName: "Number of Sensors",
    //     default: 3
    // },
    // {
    //     name: "alphaScaleFactor",
    //     displayName: "Alpha Scale Factor",
    //     default: 0.33
    // },
    // {
    //     name: "betaScaleFactor",
    //     displayName: "Beta Scale Factor",
    //     default: 0.577
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
    references: [
        references.getReferencePath("CLARKE")
    ],
    config                      : config,
    validate                    : onValidate,
};




exports = mod;