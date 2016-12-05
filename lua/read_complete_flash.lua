require("muhkuh_cli_init")
require("flasher")


if #arg~=1 then
	error("Missing parameter: image file name.")
end
strFileName = arg[1]



tPlugin = tester.getCommonPlugin()
if not tPlugin then
	error("No plugin selected, nothing to do!")
end

-- Download the binary.
aAttr = flasher.download(tPlugin, "netx/", tester.progress)

-- Use SPI Flash CS0.
local fOk = flasher.detect(tPlugin, aAttr, flasher.BUS_Spi, 0, 0)
if not fOk then
	error("Failed to get a device description!")
end

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

