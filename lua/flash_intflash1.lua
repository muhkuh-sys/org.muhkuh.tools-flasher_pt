require("muhkuh_cli_init")
require("flasher")


if #arg~=1 then
	error("Missing parameter: file to flash.")
end
strFileName = arg[1]


tPlugin = tester.getCommonPlugin()
if not tPlugin then
	error("No plugin selected, nothing to do!")
end


-- Flash the file.
local tBus = flasher.BUS_IFlash
local ulUnit = 1
local ulChipSelect = 0
flasher.simple_flasher(tPlugin, strFileName, tBus, ulUnit, ulChipSelect, "netx/")

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

