require("romloader_eth")
require("romloader_usb")
require("romloader_uart")

require("muhkuh")
require("select_plugin_cli")
require("tester_cli")

require("flasher")


__MUHKUH_WORKING_FOLDER = "./"


if #arg~=1 then
	error("Missing parameter: file to flash.")
end
strFileName = arg[1]


tPlugin = tester.getCommonPlugin()
if not tPlugin then
	error("No plugin selected, nothing to do!")
end


-- Flash the file.
tBus = flasher.BUS_Spi
ulUnit = 0
ulChipSelect = 0
flasher.simple_flasher(tPlugin, strFileName, tBus, ulUnit, ulChipSelect, "../targets/")

print("")
print(" #######  ##    ## ")
print("##     ## ##   ##  ")
print("##     ## ##  ##   ")
print("##     ## #####    ")
print("##     ## ##  ##   ")
print("##     ## ##   ##  ")
print(" #######  ##    ## ")
print("")

-- Disconnect the plugin.
tester.closeCommonPlugin()

