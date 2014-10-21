require("muhkuh_cli_init")
require("flasher")


tPlugin = tester.getCommonPlugin()
if not tPlugin then
	error("No plugin selected, nothing to do!")
end

-- Download the binary.
local aAttr = flasher.download(tPlugin, "netx/", progress)

-- Use parallel flash on unit 0, chipselect 0.
strDevDesc = flasher.detect(tPlugin, aAttr, flasher.BUS_Parflash, 0, 0, ulDevDescAdr)
if not strDevDesc then
	error("Failed to get a device description!")
end

-- Get erase area.
ulDataFirst = 0x00020080
ulDataEnd = 0x00021000
ulEraseFirst,ulEraseEnd = flasher.getEraseArea(tPlugin, aAttr, ulDataFirst, ulDataEnd)
print(string.format("Area:  [0x%08x, 0x%08x[", ulDataFirst, ulDataEnd))
print(string.format("Erase: [0x%08x, 0x%08x[", ulEraseFirst, ulEraseEnd))

-- disconnect the plugin
tPlugin:Disconnect()
