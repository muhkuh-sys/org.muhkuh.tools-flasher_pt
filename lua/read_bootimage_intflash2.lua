require("muhkuh_cli_init")
require("flasher")

local function get_dword(strData, ulOffset)
	return string.byte(strData,ulOffset) + string.byte(strData,ulOffset+1)*0x00000100 + string.byte(strData,ulOffset+2)*0x00010000 + string.byte(strData,ulOffset+3)*0x01000000
end



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

-- Use IFlash0 main memory.
local tBus = flasher.BUS_IFlash
local ulUnit = 2
local ulChipSelect = 0
local fOk = flasher.detect(tPlugin, aAttr, tBus, ulUnit, ulChipSelect)
if not fOk then
	error("Failed to detect a SPI flash!")
end

-- Get the complete devicesize.
ulFlashSize = flasher.getFlashSize(tPlugin, aAttr, tester.callback, tester.callback_progress)
print(string.format("The device size is: 0x%08x", ulFlashSize))

-- Read the boot block.
strBootBlock, strMessage = flasher.readArea(tPlugin, aAttr, 0, 64, tester.callback, tester.callback_progress)
if not strBootBlock then
	error("Failed to read the bootblock: " .. strMessage)
end

-- Check the flash magic.
-- NOTE: ignore the first byte. It can be 0x00, 0x08, 0x16 or 0x32.
ulMagic = get_dword(strBootBlock, 0+1)
print(string.format("Magic: 0x%08x", ulMagic))

local aucMagic = {
	[romloader.ROMLOADER_CHIPTYP_NETX500]          = string.char(0xaf, 0xbe, 0xf8),
	[romloader.ROMLOADER_CHIPTYP_NETX100]          = string.char(0xaf, 0xbe, 0xf8),
	[romloader.ROMLOADER_CHIPTYP_NETX50]           = string.char(0xaf, 0xbe, 0xf8),
	[romloader.ROMLOADER_CHIPTYP_NETX10]           = string.char(0xaf, 0xbe, 0xf8),
	[romloader.ROMLOADER_CHIPTYP_NETX56]           = string.char(0xaf, 0xbe, 0xf8),
	[romloader.ROMLOADER_CHIPTYP_NETX56B]          = string.char(0xaf, 0xbe, 0xf8),
	[romloader.ROMLOADER_CHIPTYP_NETX4000_RELAXED] = string.char(0xaf, 0xbe, 0xf3),
	[romloader.ROMLOADER_CHIPTYP_NETX4000_FULL]    = string.char(0xaf, 0xbe, 0xf3),
	[romloader.ROMLOADER_CHIPTYP_NETX4100_SMALL]   = string.char(0xaf, 0xbe, 0xf3),
	[romloader.ROMLOADER_CHIPTYP_NETX90_MPW]       = string.char(0xaf, 0xbe, 0xf3),
}
local iChiptype = tPlugin:GetChiptyp()
strMagic = aucMagic[iChiptype]
if not strMagic then
	error("Unknown chiptyp! " .. tostring(iChiptype))
end
print("Expected magic:")
tester.hexdump(strMagic)
if strBootBlock:sub(2,4)~=strMagic then
	error("Magic not found!")
end

-- Get the firmware size in bytes.
sizFirmwareBytes = get_dword(strBootBlock, 16+1) * 4
print(string.format("Firmware size: %d bytes", sizFirmwareBytes))

-- Read the firmware.
strFirmware, strMessage = flasher.readArea(tPlugin, aAttr, 64, sizFirmwareBytes, tester.callback, tester.callback_progress)
if not strFirmware then
	error("Failed to read the firmware: " .. strMessage)
end

-- Save the flash contents.
local tFile, strMsg = io.open(strFileName, "wb")
if not tFile then
	error("Failed to open file " .. strName .. " for writing: " .. strMsg)
end

tFile:write(strBootBlock)
tFile:write(strFirmware)
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

