let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let references = system.getScript("/libraries/MCSDKLibraryReferences.js");

var libraryCategory = "control"
var librarySourceFileName = "pi"
var mcsdkLibraryName = "PI"

let config = [
//    {
//         name: "kpVal",
//         displayName: "Proportional Gain (Kp)",
//         default: 0
//     },
//     {
//         name: "kiVal",
//         displayName: "Integral Gain (KI)",
//         default: 0
//     },
//     {
//         name: "uiVal",
//         displayName: "Integrator Start Value (Ui)",
//         default: 0
//     },
//     {
//         name: "refVal",
//         displayName: "Reference Input (refValue)",
//         default: 0
//     },
//     {
//         name: "feedbackVal",
//         displayName: "Feedback Input (fbackValue)",
//         default: 0
//     },
//     {
//         name: "feedforwardVal",
//         displayName: "Feedforward Input (ffwdValue)",
//         default: 0
//     },
//     {
//         name: "outMinVal",
//         displayName: "Minimum Output (outMin)",
//         default: 0
//     },
//     {
//         name: "outMaxVal",
//         displayName: "Maximum Output (outMax)",
//         default: 0
//     },
]

function onValidate(inst, validation) {}

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
        references.getReferencePath("PI")
    ],
    config                      : config,
    validate                    : onValidate,
};
exports = mod;