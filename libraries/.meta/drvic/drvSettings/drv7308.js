let Common = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let references = system.getScript("/libraries/MCSDKLibraryReferences.js");

let drv7308Pins = [
    {
        $name: "BRAKE",
        function: "unused",
    },
    {
        $name: "EN",
        function: "unused",
    },
    {
        $name: "nFAULT",
        function: "unused",
    },
    {
        $name: "VTEMP",
        function: "unused",
    },
]

function getDRV7308HwSettings(inst) {
    return {
        $name: "DRV7308_HW_Interface",
        hiddenTextFieldForPinArgs: JSON.stringify(drv7308Pins),
	}
}

exports = {
    getDRV7308HwSettings,
};