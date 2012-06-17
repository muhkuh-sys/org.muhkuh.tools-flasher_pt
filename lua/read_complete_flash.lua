require("romloader_eth")
require("romloader_usb")
require("romloader_uart")

require("muhkuh")
require("select_plugin_cli")
require("tester_cli")

require("flasher")


__MUHKUH_WORKING_FOLDER = "./"


if #arg~=1 then
	error("Missing parameter: image file name.")
end
strFileName = arg[1]



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

-- Get the erase area for the range 0 .. 1.
ulEraseStart, ulEraseEnd = flasher.getEraseArea(tPlugin, aAttr, 0, 1)
if not ulEraseStart then
	error("Failed to get erase areas!")
end
print(string.format("The first erase area is: 0x%08x-0x%08x", ulEraseStart, ulEraseEnd))


-- Get the complete devicesize.
ulFlashSize = flasher.getFlashSize(tPlugin, aAttr, tester.callback, tester.callback_progress)
print(string.format("The device size is: 0x%08x", ulFlashSize))

-- Read the complete flash.
strFlashContents, strMessage = flasher.readArea(tPlugin, aAttr, 0, ulFlashSize, tester.callback, tester.callback_progress)
if not strFlashContents then
	error("Failed to read the flash: " .. strMessage)
end

-- Save the flash contents.
local tFile, strMsg = io.open(strFileName, "wb")
if not tFile then
	error("Failed to open file " .. strName .. " for writing: " .. strMsg)
end

tFile:write(strFlashContents)
tFile:close()

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

