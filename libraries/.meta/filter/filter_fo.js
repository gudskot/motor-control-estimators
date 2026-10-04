let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let references = system.getScript("/libraries/MCSDKLibraryReferences.js");

let longDescription = "y[n] = b0x[n] + b1x[n-1] - a1y[n-1]"

let config = [
    {
        name: "a1",
        displayName: "Denominator Coeff a1",
        description: "Filter coefficient for z^(-1)",
        default: 0
    },
    {
        name: "b0",
        displayName: "Numerator Coeff b0",
        description: "Filter coefficient for z^0",
        default: 0
    },
    {
        name: "b1",
        displayName: "Numerator Coeff b1",
        description: "Filter coefficient for z^(-1)",
        default: 0
    },
    {
        name: "x1",
        displayName: "Initial Condition x1",
        description: "Input value at time sample n=-1",
        default: 0
    },
    {
        name: "y1",
        displayName: "Initial Condition y1",
        description: "Output value at time sample n=-1",
        default: 0
    },
]

function onValidate(inst, validation) {

}

var filterfoModule = {
    mcsdkLibraryName: "FILTER_FO",
    displayName: "FILTER FO",
    longDescription: longDescription,
    defaultInstanceName: "myFilterFo",
    description: "Filter first order",
    templates: {
        mcsdk_libraries_h           : "/libraries/filter/filter_fo/filter_fo.mcsdk_libraries.h.xdt",
        mcsdk_libraries_c           : "/libraries/filter/filter_fo/filter_fo.mcsdk_libraries.c.xdt",
        mcsdk_libraries_opt         : "/libraries/filter/filter_fo/filter_fo.mcsdk_libraries.opt.xdt",
        mcsdk_libraries_cmd_genlibs : "/libraries/filter/filter_fo/filter_fo.mcsdk_libraries.cmd.genlibs.xdt",
    },
    config: config,
    references: [
        references.getReferencePath("Filter_FO")
    ],
    validate    : onValidate,
};

exports = filterfoModule;