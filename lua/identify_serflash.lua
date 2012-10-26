require("flasher")

tPlugin = tester.getCommonPlugin()
if tPlugin==nil then
	error("No plugin selected, nothing to do!")
end

--[[
-- Unlock ASIC CTRL
ulKey = tPlugin:read_data32(0x1018c17c)
tPlugin:write_data32(0x1018c17c, ulKey)
-- Activate SQI mode.
tPlugin:write_data32(0x1018c108, 0x00800000)
-- Check if SQI mode is really active.
ulValue = tPlugin:read_data32(0x1018c108)
if ulValue~=0x00800000 then
	error("Failed to set SQI mode!")
end
--]]

-- Download the binary.
local aAttr = flasher.download(tPlugin, "netx/", tester.progress)

-- Use SPI Flash CS0.
local fOk = flasher.detect(tPlugin, aAttr, flasher.BUS_Spi, 0, 0)
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
