require("muhkuh_cli_init")
require("flasher")


tPlugin = tester.getCommonPlugin()
if not tPlugin then
	error("No plugin selected, nothing to do!")
end


-- Download the binary.
local aAttr = flasher.download(tPlugin, "netx/", tester.callback_progress)

-- Use SPI Flash CS0.
local fOk = flasher.detect(tPlugin, aAttr, flasher.BUS_Spi, 0, 0)
if not fOk then
	error("Failed to get a device description!")
end

-- Get the complete devicesize.
ulFlashSize = flasher.getFlashSize(tPlugin, aAttr, tester.callback, tester.callback_progress)
print(string.format("The device size is: 0x%08x", ulFlashSize))

-- Erase the complete device.
ulEraseStart, ulEraseEnd = flasher.getEraseArea(tPlugin, aAttr, 0, ulFlashSize)
if not ulEraseStart then
	error("Failed to get erase areas!")
end

local fIsErased
print(string.format("Checking area 0x%08x-0x%08x...", ulEraseStart, ulEraseEnd))
fIsErased = flasher.isErased(tPlugin, aAttr, ulEraseStart, ulEraseEnd)
if fIsErased==nil then
	error("failed to check the area!")
end


if fIsErased==true then
	print("The area is already erased.")
else
	print("The area is not erased. Erasing it now...")
	local fIsOk = flasher.erase(tPlugin, aAttr, ulEraseStart, ulEraseEnd)
	if not fIsOk then
		error("Failed to erase the area!")
	end

	fIsErased = flasher.isErased(tPlugin, aAttr, ulEraseStart, ulEraseEnd)
	if not fIsErased then
		error("No error reported, but the area is not erased!")
	end
end

-- disconnect the plugin
tPlugin:Disconnect()
