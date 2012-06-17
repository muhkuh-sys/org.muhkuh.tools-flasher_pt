require("romloader_usb")
require("romloader_uart")

require("muhkuh")
require("select_plugin_cli")
require("tester_cli")

require("flasher")


__MUHKUH_WORKING_FOLDER = "./"


tPlugin = tester.getCommonPlugin()
if tPlugin==nil then
	error("No plugin selected, nothing to do!")
end

-- connect the plugin
tPlugin:Connect()


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


local strDevDesc
local ulEraseStart
local ulEraseEnd


-- Download the binary.
aAttr = flasher.download(tPlugin, "../targets/", tester.progress)

-- Use SPI Flash CS0.
strDevDesc = flasher.detect(tPlugin, aAttr, flasher.BUS_Spi, 0, 0)
if not strDevDesc then
	error("Failed to get a device description!")
end

-- show the device description
print("This is the device description:")
tester.hexdump(strDevDesc)

-- disconnect the plugin
tPlugin:Disconnect()

