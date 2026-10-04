let Common   = system.getScript("/driverlib/Common.js");
let references = system.getScript("/libraries/MCSDKLibraryReferences.js");

let CATEGORY_CONTROL = "Control";
let CATEGORY_FILTER = "Filter";
let CATEGORY_OBSERVERS = "Observers";
let CATEGORY_TRANSFORMS = "Transforms";
let CATEGORY_UTILITIES = "Utilities";
let CATEGORY_DAC = "DAC";
let CATEGORY_SFRA = "SFRA";
let CATEGORY_DRVIC = "Motor Driver";


var supported_modules_control = [];
var supported_modules_filter = [];
var supported_modules_observers = [];
var supported_modules_transforms = [];
var supported_modules_utilities = [];
var supported_modules_dac = [];
var supported_modules_sfra = [];
var supported_modules_drvic = [];

var supported_modules = {};
supported_modules[CATEGORY_CONTROL] = supported_modules_control
supported_modules[CATEGORY_FILTER] = supported_modules_filter
supported_modules[CATEGORY_OBSERVERS] = supported_modules_observers
supported_modules[CATEGORY_TRANSFORMS] = supported_modules_transforms
supported_modules[CATEGORY_UTILITIES] = supported_modules_utilities
supported_modules[CATEGORY_DAC] = supported_modules_dac
supported_modules[CATEGORY_SFRA] = supported_modules_sfra
supported_modules[CATEGORY_DRVIC] = supported_modules_drvic

var supported_library_moduleFile = [
    { moduleCategory: CATEGORY_FILTER  ,  moduleName : "FILTER_FO", moduleFile : "/libraries/filter/filter_fo.js"},
    { moduleCategory: CATEGORY_FILTER  ,  moduleName : "OFFSET", moduleFile : "/libraries/filter/offset.js"},
    { moduleCategory: CATEGORY_FILTER  ,  moduleName : "CTRL", moduleFile : "/libraries/control/ctrl.js"},
    { moduleCategory: CATEGORY_CONTROL ,  moduleName : "DCLINK_SS", moduleFile : "/libraries/control/dclink_ss.js"},
    { moduleCategory: CATEGORY_CONTROL ,  moduleName : "FWC", moduleFile : "/libraries/control/fwc.js"},
    { moduleCategory: CATEGORY_CONTROL ,  moduleName : "MTPA", moduleFile : "/libraries/control/mtpa.js"},
    { moduleCategory: CATEGORY_CONTROL ,  moduleName : "PI", moduleFile : "/libraries/control/pi.js"},
    { moduleCategory: CATEGORY_CONTROL ,  moduleName : "PID", moduleFile : "/libraries/control/pid.js"},
    { moduleCategory: CATEGORY_CONTROL ,  moduleName : "VS_FREQ", moduleFile : "/libraries/control/vs_freq.js"},
    { moduleCategory: CATEGORY_CONTROL ,  moduleName : "VSF", moduleFile : "/libraries/control/vsf.js"},
    { moduleCategory: CATEGORY_OBSERVERS ,  moduleName : "ENCODER", moduleFile : "/libraries/observers/encoder.js"},
    { moduleCategory: CATEGORY_OBSERVERS ,  moduleName : "ESMO", moduleFile : "/libraries/observers/esmo.js"},
    { moduleCategory: CATEGORY_OBSERVERS ,  moduleName : "EST", moduleFile : "/libraries/observers/est.js"},
    { moduleCategory: CATEGORY_OBSERVERS ,  moduleName : "EST_LIB", moduleFile : "/libraries/observers/est_lib.js"},
    { moduleCategory: CATEGORY_OBSERVERS ,  moduleName : "FAST", moduleFile : "/libraries/observers/fast.js"},
    { moduleCategory: CATEGORY_OBSERVERS ,  moduleName : "HALL", moduleFile : "/libraries/observers/hall.js"},
    { moduleCategory: CATEGORY_OBSERVERS ,  moduleName : "ISBLDC", moduleFile : "/libraries/observers/isbldc.js"},
    { moduleCategory: CATEGORY_OBSERVERS ,  moduleName : "MPID", moduleFile : "/libraries/observers/mpid.js"},
    { moduleCategory: CATEGORY_OBSERVERS ,  moduleName : "SLIP", moduleFile : "/libraries/observers/slip.js"},
    { moduleCategory: CATEGORY_OBSERVERS ,  moduleName : "SPEED_OBSERVER", moduleFile : "/libraries/observers/speed_observer.js"},
    { moduleCategory: CATEGORY_OBSERVERS ,  moduleName : "SPEEDCALC", moduleFile : "/libraries/observers/speedcalc.js"},
    { moduleCategory: CATEGORY_OBSERVERS ,  moduleName : "SPEEDFR", moduleFile : "/libraries/observers/speedfr.js"},
    { moduleCategory: CATEGORY_OBSERVERS ,  moduleName : "SSIPD", moduleFile : "/libraries/observers/ssipd.js"},
    { moduleCategory: CATEGORY_SFRA,        moduleName : "SFRA", moduleFile : "/libraries/sfra/sfra.js"},
    { moduleCategory: CATEGORY_TRANSFORMS ,  moduleName : "CLARKE", moduleFile : "/libraries/transforms/clarke.js"},
    { moduleCategory: CATEGORY_TRANSFORMS ,  moduleName : "IPARK", moduleFile : "/libraries/transforms/ipark.js"},
    { moduleCategory: CATEGORY_TRANSFORMS ,  moduleName : "PARK", moduleFile : "/libraries/transforms/park.js"},
    { moduleCategory: CATEGORY_TRANSFORMS ,  moduleName : "SVGEN", moduleFile : "/libraries/transforms/svgen.js"},
    { moduleCategory: CATEGORY_TRANSFORMS ,  moduleName : "VOLTS", moduleFile : "/libraries/transforms/volts.js"},
    { moduleCategory: CATEGORY_UTILITIES ,  moduleName : "ANGLE_GEN", moduleFile : "/libraries/utilities/angle_gen.js"},
    { moduleCategory: CATEGORY_UTILITIES ,  moduleName : "CPU_TIME", moduleFile : "/libraries/utilities/cpu_time.js"},
    { moduleCategory: CATEGORY_UTILITIES ,  moduleName : "DATALOG", moduleFile : "/libraries/utilities/datalog.js"},
    { moduleCategory: CATEGORY_UTILITIES ,  moduleName : "DIAGNOSTIC", moduleFile : "/libraries/utilities/diagnostic.js"},
    { moduleCategory: CATEGORY_UTILITIES ,  moduleName : "MATH_BLOCKS", moduleFile : "/libraries/utilities/math_blocks.js"},
    { moduleCategory: CATEGORY_UTILITIES ,  moduleName : "MOD6CNT", moduleFile : "/libraries/utilities/mod6cnt.js"},
    { moduleCategory: CATEGORY_UTILITIES ,  moduleName : "QUEUE", moduleFile : "/libraries/utilities/queue.js"},
    { moduleCategory: CATEGORY_UTILITIES ,  moduleName : "RIMPULSE", moduleFile : "/libraries/utilities/rimpulse.js"},
    { moduleCategory: CATEGORY_UTILITIES ,  moduleName : "STEP_RESPONSE", moduleFile : "/libraries/utilities/step_response.js"},
    { moduleCategory: CATEGORY_UTILITIES ,  moduleName : "TRAJ", moduleFile : "/libraries/utilities/traj.js"},
    { moduleCategory: CATEGORY_DAC       ,  moduleName : "DAC128S", moduleFile : "/libraries/dacs/dac128s.js"},
    { moduleCategory: CATEGORY_DRVIC     ,  moduleName : "DRVIC", moduleFile : "/libraries/drvic/drvic.js"},
];

var device_specific_modules = [

]

for (var library_moduleFile in supported_library_moduleFile)
{
    supported_modules[supported_library_moduleFile[library_moduleFile].moduleCategory].
        push(supported_library_moduleFile[library_moduleFile].moduleFile)
}


for (var device_specific_modules_index in device_specific_modules)
{   
    if (device_specific_modules[device_specific_modules_index].
        devices.includes(Common.getDeviceName()))
    {
        supported_modules[device_specific_modules[device_specific_modules_index].moduleCategory].
            push(device_specific_modules[device_specific_modules_index].moduleFile)
    }
}

exports = {
    displayName: "Motor Control Libraries",
    topModules: [

        {
            displayName: "Motor Control Libraries",
            description: "Motor Control Libraries",
            categories: [
                {
                    displayName: CATEGORY_CONTROL,
                    modules: supported_modules[CATEGORY_CONTROL]
                },
                {
                    displayName: CATEGORY_DRVIC,
                    modules: supported_modules[CATEGORY_DRVIC]
                },
                {
                    displayName: CATEGORY_FILTER,
                    modules: supported_modules[CATEGORY_FILTER]
                },
                {
                    displayName: CATEGORY_OBSERVERS,
                    modules: supported_modules[CATEGORY_OBSERVERS]
                },
                {
                    displayName: CATEGORY_SFRA,
                    modules: supported_modules[CATEGORY_SFRA]
                },
                {
                    displayName: CATEGORY_TRANSFORMS,
                    modules: supported_modules[CATEGORY_TRANSFORMS]
                },
                {
                    displayName: CATEGORY_UTILITIES,
                    modules: supported_modules[CATEGORY_UTILITIES]
                },
                {
                    displayName: CATEGORY_DAC,
                    modules: supported_modules[CATEGORY_DAC]
                },
            ]
        },
    ],
    references: references.componentReferences,
    templates: [

        {
            name      : "/libraries/mcsdk_libraries.cmd.genlibs.xdt",
            outputPath: "mcsdk_libraries.cmd.genlibs",
            alwaysRun : true
        },
        {
            name      : "/libraries/mcsdk_libraries.opt.xdt",
            outputPath: "mcsdk_libraries.opt",
            alwaysRun : true
        },
        {
            name      : "/libraries/mcsdk_libraries.c.xdt",
            outputPath: "mcsdk_libraries.c",
            alwaysRun : true
        },
        {
            name      : "/libraries/mcsdk_libraries.h.xdt",
            outputPath: "mcsdk_libraries.h",
            alwaysRun : true
        },
    ],
    
}