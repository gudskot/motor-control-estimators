let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let references = system.getScript("/libraries/MCSDKLibraryReferences.js")

var libraryCategory = "utilities"
var librarySourceFileName = "diagnostic"
var mcsdkLibraryName = "DIAGNOSTIC"

let longDescription = `
The diagnostic utility is used for formatting buffers so that they can be graphed using the CCS graphing tool. To utilize this structure in the main file, make sure
to include the graph.h header file.
`

let config = [

]

function onValidate(inst, validation) {

}

var mod = {
    mcsdkLibraryName            : mcsdkLibraryName,
    displayName                 : mcsdkLibraryName,
    defaultInstanceName         : "my" + mcsdkLibraryName,
    description                 : mcsdkLibraryName + " short description",
    maxInstances                : 1,
    longDescription             : longDescription,
    templates: {
        mcsdk_libraries_h           : "/libraries/" + libraryCategory + "/" + librarySourceFileName + "/" + librarySourceFileName + ".mcsdk_libraries.h.xdt",
        mcsdk_libraries_c           : "/libraries/" + libraryCategory + "/" + librarySourceFileName + "/" + librarySourceFileName + ".mcsdk_libraries.c.xdt",
        mcsdk_libraries_opt         : "/libraries/" + libraryCategory + "/" + librarySourceFileName + "/" + librarySourceFileName + ".mcsdk_libraries.opt.xdt",
        mcsdk_libraries_cmd_genlibs : "/libraries/" + libraryCategory + "/" + librarySourceFileName + "/" + librarySourceFileName + ".mcsdk_libraries.cmd.genlibs.xdt",
    },
    config                      : config,
    references : [
        references.getReferencePath("DIAGNOSTIC")
    ],
    validate                    : onValidate,
};




exports = mod;