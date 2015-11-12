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

-- Get the size of the complete flash.
ulFlashSize = flasher.getFlashSize(tPlugin, aAttr, tester.callback, tester.callback_progress)

-- Loop over the complete flash size.
local ulAddressCnt = 0
local atEraseBlocks = {}

while ulAddressCnt<ulFlashSize do
	-- Get erase area.
	ulEraseFirst,ulEraseEnd = flasher.getEraseArea(tPlugin, aAttr, ulAddressCnt, ulAddressCnt+1)
	
	local tValues = {erase_start=ulEraseFirst, erase_end=ulEraseEnd}
	table.insert(atEraseBlocks, tValues)
	
	-- Move to the next block.
	ulAddressCnt = ulEraseEnd
end

-- Print all erase blocks.
for iCnt,tValues in ipairs(atEraseBlocks) do
	print(string.format("%03d: [0x%08x, 0x%08x[", iCnt-1, tValues.erase_start, tValues.erase_end))
end

-- disconnect the plugin
tPlugin:Disconnect()
