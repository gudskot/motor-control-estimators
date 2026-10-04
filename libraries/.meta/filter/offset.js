let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let references = system.getScript("/libraries/MCSDKLibraryReferences.js");

var libraryCategory = "filter"
var librarySourceFileName = "offset"
var mcsdkLibraryName = "OFFSET"

let config = [
    // {
    //     name: "offsetVal",
    //     displayName: "Offset Value",
    //     default: 0
    // },
    // {
    //     name : "enableSetBeta",
    //     displayName : "Enable Beta Configuration",
    //     default : false,
    //     onChange : onChangeBeta
    // },
    // {
    //     name: "betaRadVal",
    //     displayName: "Beta Value (Radians)",
    //     longDescription : "Sets a0, b0, and b1",
    //     hidden : true,
    //     default: 0
    // },
    // {
    //     name : "enableSetInitCond",
    //     displayName : "Enable Initial Condition Configuration",
    //     default : false,
    //     onChange : onChangeInit
    // },
    // {
    //     name: "initVal",
    //     displayName: "Initial Condition",
    //     longDescription : "Sets x1 and y1",
    //     hidden : true,
    //     default: 0
    // },
]

function onChangeBeta(inst, ui)
{
    ui.betaRadVal.hidden = !inst.enableSetBeta;
}
function onChangeInit(inst, ui)
{
    ui.initVal.hidden = !inst.enableSetInitCond;
}
function moduleInstances (inst)
{
    var filterFOInstance;

    if((inst.enableSetBeta == true) && (inst.enableSetInitCond == true))
    {
        filterFOInstance = {
            displayName: "FILTER FO",
            name: "FILTER_FO",
            moduleName: "/libraries/filter/filter_fo.js",
            requiredArgs: {
                a1  : ((inst.betaRadVal - 2.0) / (inst.betaRadVal + 2.0)),
                b0  : (inst.betaRadVal / (inst.betaRadVal + 2.0)),
                b1  : (inst.betaRadVal / (inst.betaRadVal + 2.0)),
                x1  : inst.initVal,
                y1  : inst.initVal
            }
        };
    }
    else if(inst.enableSetBeta == true)
    {
        filterFOInstance = {
            displayName: "FILTER FO",
            name: "FILTER_FO",
            moduleName: "/libraries/filter/filter_fo.js",
            requiredArgs: {
                a1  : ((inst.betaRadVal - 2.0) / (inst.betaRadVal + 2.0)),
                b0  : (inst.betaRadVal / (inst.betaRadVal + 2.0)),
                b1  : (inst.betaRadVal / (inst.betaRadVal + 2.0))
            }
        };
    }
    else if(inst.enableSetInitCond == true)
    {
        filterFOInstance = {
            displayName: "FILTER FO",
            name: "FILTER_FO",
            moduleName: "/libraries/filter/filter_fo.js",
            requiredArgs: {
                x1  : inst.initVal,
                y1  : inst.initVal
            }
        };
    }
    else
    {
        filterFOInstance = {
            displayName: "FILTER FO",
            name: "FILTER_FO",
            moduleName: "/libraries/filter/filter_fo.js",
        };
    }
    return [filterFOInstance];
}

function onValidate(inst, validation) {
    //console.log(inst.FILTER_FO.$name);
    //Common.printDebugObject(inst.FILTER_FO.$name);
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
        references.getReferencePath("Offset")
    ],
    moduleInstances: moduleInstances,
    config                      : config,
    validate                    : onValidate,
};
exports = mod;