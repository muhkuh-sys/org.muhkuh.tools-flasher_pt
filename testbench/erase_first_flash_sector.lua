require("romloader_eth")
require("romloader_usb")
require("romloader_uart")

require("muhkuh")
require("select_plugin_cli")
require("tester_cli")

require("flasher")


__MUHKUH_WORKING_FOLDER = "./"

tPlugin = tester.getCommonPlugin()
if not tPlugin then
	error("No plugin selected, nothing to do!")
end

local strDevDesc
local ulEraseStart
local ulEraseEnd


-- Download the binary.
aAttr = flasher.download(tPlugin, "../targets/", tester.progress)

-- Use SPI Flash CS0.
strDevDesc = flasher.detect(tPlugin, aAttr, flasher.BUS_Spi, 0, 0, ulDevDescAdr)
if not strDevDesc then
	error("Failed to get a device description!")
end

-- show the device description
--hexdump(strDevDesc)

-- Get the erase area for the range 0 .. 1.
ulEraseStart, ulEraseEnd = flasher.getEraseArea(tPlugin, aAttr, 0, 1)
if not ulEraseStart then
	error("Failed to get erase areas!")
end
print(string.format("The first erase area is: 0x%08x-0x%08x", ulEraseStart, ulEraseEnd))

-- Check if the erase area is already clear.
local fIsErased
print(string.format("Is area 0x%08x-0x%08x already erased?", ulEraseStart, ulEraseEnd))
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
	print("Erase finished!")

	fIsErased = flasher.isErased(tPlugin, aAttr, ulEraseStart, ulEraseEnd)
	if not fIsErased then
		error("No error reported, but the area is not erased!")
	end
	print("The first erase area is clear now!")
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

-- Disconnect the plugin.
tester.closeCommonPlugin()

