require("muhkuh_cli_init")
require("flasher")

tPlugin = tester.getCommonPlugin()
if tPlugin==nil then
	error("No plugin selected, nothing to do!")
end

-- Download the binary.
local aAttr = flasher.download(tPlugin, "netx/", tester.progress)

-- Use SPI Flash CS0.
local fOk = flasher.detect(tPlugin, aAttr, flasher.BUS_IFlash, 0, 0)
if not fOk then
	error("Failed to get a device description!")
end

print("")
print(" #######  ##    ## ")
print("##     ## ##   ##  ")
print("##     ## ##  ##   ")
print("##     ## #####    ")
print("##     ## ##  ##   ")
print("##     ## ##   ##  ")
print(" #######  ##    ## ")
print("")

-- disconnect the plugin
tPlugin:Disconnect()
