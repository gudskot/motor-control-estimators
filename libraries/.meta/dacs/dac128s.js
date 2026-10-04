let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let references = system.getScript("/libraries/MCSDKLibraryReferences.js");

let longDescription = "DAC128S Module"

let config = [
    
]

function onValidate(inst, validation) {

}

var dac128sModule = {
    mcsdkLibraryName: "DAC128S",
    displayName: "DAC128S",
    longDescription: longDescription,
    defaultInstanceName: "myDAC128S",
    description: "DAC128S configuration",
    templates: {
        mcsdk_libraries_h           : "/libraries/dacs/dac128s/dac128s.mcsdk_libraries.h.xdt",
        mcsdk_libraries_c           : "/libraries/dacs/dac128s/dac128s.mcsdk_libraries.c.xdt",
        mcsdk_libraries_opt         : "/libraries/dacs/dac128s/dac128s.mcsdk_libraries.opt.xdt",
        mcsdk_libraries_cmd_genlibs : "/libraries/dacs/dac128s/dac128s.mcsdk_libraries.cmd.genlibs.xdt",
    },
    config: config,
    references: [
        references.getReferencePath("DAC128S")
    ],
    validate    : onValidate,
};

exports = dac128sModule;