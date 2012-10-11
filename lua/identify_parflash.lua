require("flasher")

tPlugin = tester.getCommonPlugin()
if tPlugin==nil then
	error("No plugin selected, nothing to do!")
end

-- Download the binary.
local aAttr = flasher.download(tPlugin, "netx/", progress)

-- Use parallel flash on unit 0, chipselect 0.
local tBus = flasher.BUS_Parflash
local ulUnit = 0
local ulChipSelect = 0
fOk = flasher.detect(tPlugin, aAttr, tBus, ulUnit, ulChipSelect, ulDevDescAdr)
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
