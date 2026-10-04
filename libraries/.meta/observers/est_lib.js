let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let references = system.getScript("/libraries/MCSDKLibraryReferences.js")

var libraryCategory = "observers"
var librarySourceFileName = "est_lib"
var mcsdkLibraryName = "EST_LIB"

let config = [
    {
        name: "estLibVariant",
        displayName: "Estimator Library Variant",
        default: "fast_full_lib",
        options: [
            { name: "fast_full_lib", displayName: "FAST Full" }, 
            { name: "fast_full_s32_fpu", displayName: "FAST Full Single Motor" },
            { name: "fast_f64_full_lib", displayName: "FAST Full F64" },
            { name: "fast_simple_lib", displayName: "FAST Simple" },
            { name: "fast_pmsm_lib" , displayName: "FAST PMSM" },
        ]
    },
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
    validate                    : onValidate,
};




exports = mod;