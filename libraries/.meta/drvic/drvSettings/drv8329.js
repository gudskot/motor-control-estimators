let Common = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let references = system.getScript("/libraries/MCSDKLibraryReferences.js");

let drv8329Pins = [
    {
        $name: "POT",
        function: "unused",
    },
    {
        $name: "nFAULT",
        function: "unused",
    },
    {
        $name: "MCU_LED",
        function: "unused",
    },
    {
        $name: "DRVOFF",
        function: "unused",
    },
]

function getDRV8329HwSettings(inst) {
    return {
        $name: "DRV8329_HW_Interface",
        hiddenTextFieldForPinArgs: JSON.stringify(drv8329Pins),
	}
}

exports = {
    getDRV8329HwSettings,
};