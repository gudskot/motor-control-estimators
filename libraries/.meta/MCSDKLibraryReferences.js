var currnetSDKProductPath = system.getProducts()[0].path
var sdkPath = system.utils.path.join(currnetSDKProductPath + "../../../")
sdkPath = sdkPath.replace(new RegExp('\\' + system.utils.path.sep, 'g'), '/')
var sfra_gui_path = sdkPath + "/solutions/sensorless_motor_control_syscfg/common/source/sfra_gui.c"

var references = [
	{
		name: "DCLINKSS",
		path: "../libraries/control/dclink_ss/source/dclink_ss.c",
		alwaysInclude : false
	},
	{
		name: "FWC",
		path: "../libraries/control/fwc/source/fwc.c",
		alwaysInclude : false
	},
	{
		name: "MTPA",
		path: "../libraries/control/mtpa/source/mtpa.c",
		alwaysInclude : false
	},
	{
		name: "PI",
		path: "../libraries/control/pi/source/pi.c",
		alwaysInclude : false
	},
	{
		name: "PID",
		path: "../libraries/control/pid/source/pid.c",
		alwaysInclude : false
	},
	{
		name: "VS_FREQ",
		path: "../libraries/control/vs_freq/source/vs_freq.c",
		alwaysInclude : false
	},
	{
		name: "VSF",
		path: "../libraries/control/vsf/source/vsf.c",
		alwaysInclude : false
	},
	{
		name: "DAC128S",
		path: "../libraries/dacs/dac128s085/source/dac128s085.c",
		alwaysInclude : false
	},
	{
		name: "DRV8316",
		path: "../libraries/drvic/drv8316/source/drv8316s.c",
		alwaysInclude : false
	},
	{
		name: "DRV8323",
		path: "../libraries/drvic/drv8323/source/drv8323s.c",
		alwaysInclude : false
	},
	{
		name: "DRV8353",
		path: "../libraries/drvic/drv8353/source/drv8353s.c",
		alwaysInclude : false
	},
	{
		name: "Filter_FO",
		path: "../libraries/filter/filter_fo/source/filter_fo.c",
		alwaysInclude : false
	},
	{
		name: "ENCODER",
		path: "../libraries/observers/encoder/source/encoder.c",
		alwaysInclude : false
	},
	{
		name: "ESMO",
		path: "../libraries/observers/esmo/source/esmo.c",
		alwaysInclude : false
	},
	// {
	// 	name: "EST",
	// 	path: "../libraries/observers/est/source/est.c",
	// 	alwaysInclude : false
	// },
	{
		name: "HALL",
		path: "../libraries/observers/hall/source/hall.c",
		alwaysInclude : false
	},
	{
		name: "ISBLDC",
		path: "../libraries/observers/isbldc/source/isbldc.c",
		alwaysInclude : false
	},
	{
		name: "SLIP",
		path: "../libraries/observers/slip/source/slip.c",
		alwaysInclude : false
	},
	{
		name: "SPEED_OBSERVER",
		path: "../libraries/observers/speed_observer/source/speed_observer.c",
		alwaysInclude : false
	},
	{
		name: "SPEED_CALC",
		path: "../libraries/observers/speedcalc/source/speedcalc.c",
		alwaysInclude : false
	},
	{
		name: "SPEED_FR",
		path: "../libraries/observers/speedfr/source/speedfr.c",
		alwaysInclude : false
	},
	{
		name: "SSIPD",
		path: "../libraries/observers/ssipd/source/ssipd.c",
		alwaysInclude : false
	},
	{
		name: "Offset",
		path: "../libraries/filter/offset/source/offset.c",
		alwaysInclude : false
	},
	{
		name: "CLARKE",
		path: "../libraries/transforms/clarke/source/clarke.c",
		alwaysInclude : false
	},	
	{
		name: "PARK",
		path: "../libraries/transforms/park/source/park.c",
		alwaysInclude : false
	},	
	{
		name: "IPARK",
		path: "../libraries/transforms/ipark/source/ipark.c",
		alwaysInclude : false
	},	
	{
		name: "SVGEN",
		path: "../libraries/transforms/svgen/source/svgen.c",
		alwaysInclude : false
	},	
	{
		name: "SVGEN_CURRENT",
		path: "../libraries/transforms/svgen/source/svgen_current.c",
		alwaysInclude : false
	},
	{
		name: "ANGLE_GEN",
		path: "../libraries/utilities/angle_gen/source/angle_gen.c",
		alwaysInclude : false
	},
	{
		name: "CPU_TIME",
		path: "../libraries/utilities/cpu_time/source/cpu_time.c",
		alwaysInclude : false
	},
	{
		name: "DATALOG",
		path: "../libraries/utilities/datalog/source/datalog.c",
		alwaysInclude : false
	},
	{
		name: "DATALOG_IF",
		path: "../libraries/utilities/datalog/source/datalogIF.c",
		alwaysInclude : false
	},
	{
		name: "DATALOG_2CH",
		path: "../libraries/utilities/datalog/source/dlog_2ch_f.c",
		alwaysInclude : false
	},
	{
		name: "DATALOG_4CH",
		path: "../libraries/utilities/datalog/source/dlog_4ch_f.c",
		alwaysInclude : false
	},
	{
		name: "DATALOG_6CH",
		path: "../libraries/utilities/datalog/source/dlog_6ch_f.c",
		alwaysInclude : false
	},
	{
		name: "DIAGNOSTIC",
		path: "../libraries/utilities/diagnostic/source/graph.c",
		alwaysInclude : false
	},
	{
		name: "STEP_RESPONSE",
		path: "../libraries/utilities/step_response/source/step_response.c",
		alwaysInclude : false
	},
	{
		name: "TRAJ",
		path: "../libraries/utilities/traj/source/traj.c",
		alwaysInclude : false
	},
	{
		name: "VOLTS",
		path: "../libraries/transforms/volts/source/volt_recons.c",
		alwaysInclude : false
	},
	{
		name: "SFRA",
		path: "../libraries/sfra/gui/source/sfra_gui_scicomms_driverlib.c",
		alwaysInclude : false
	},
	{
		name: "SFRA_GUI",
		path: sfra_gui_path,
		alwaysInclude : false
	},
]

function getReferencePath(name)
{
	for (var ref of references)
	{
		if (ref.name == name)
		{
			return ref.path
		}
	}
}

var componentReferences = []
for (var ref of references)
{
	componentReferences.push({
		path: ref.path,
		alwaysInclude: ref.alwaysInclude
	})
}

exports = {
	references: references,
	getReferencePath: getReferencePath,
	componentReferences: componentReferences
}