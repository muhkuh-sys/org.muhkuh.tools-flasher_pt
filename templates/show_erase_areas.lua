------------------------------------------------------------------------------
--
-- This script shows the complete erase sector table of a parallel flash.
--  It first tries to detect a parallel flash. Then it reads the device
--  descriptor. The erase sector table is dumped for all sectors.
--
------------------------------------------------------------------------------

require("muhkuh_cli_init")
require("flasher")


local function get_dword(strData, ulOffset)
	return strData:byte(ulOffset) + strData:byte(ulOffset+1)*0x00000100 + strData:byte(ulOffset+2)*0x00010000 + strData:byte(ulOffset+3)*0x01000000
end


tPlugin = tester.getCommonPlugin()
if not tPlugin then
	error("No plugin selected, nothing to do!")
end

-- Download the binary.
local aAttr = flasher.download(tPlugin, "netx/", progress)

-- Use parallel flash on unit 0, chipselect 0.
local fOk = flasher.detect(tPlugin, aAttr, flasher.BUS_Parflash, 0, 0, ulDevDescAdr)
if not fOk then
	error("Failed to detect the flash!")
end

-- Read the device descriptor. This includes the erase areas.
local strDevDesc = flasher.readDeviceDescriptor(tPlugin, aAttr)
if not strDevDesc then
	error("Failed to read the device description!")
end

-- Disconnect the plugin.
tPlugin:Disconnect()


local ulSectors = get_dword(strDevDesc, ${OFFSETOF_tagFLASH_DEVICE_ulSectorCnt}+1)
print(string.format("Found %d sectors.", ulSectors))

-- Iterate over the erase areas.
for ulCnt=0,ulSectors-1 do
	local ulOffset = get_dword(strDevDesc, 1+${OFFSETOF_DEVICE_DESCRIPTION_STRUCT_uInfo}+${OFFSETOF_tagFLASH_DEVICE_atSectors}+(${SIZEOF_SECTOR_INFO_STRUCT}*ulCnt)+${OFFSETOF_SECTOR_INFO_STRUCT_ulOffset})
	local ulSize   = get_dword(strDevDesc, 1+${OFFSETOF_DEVICE_DESCRIPTION_STRUCT_uInfo}+${OFFSETOF_tagFLASH_DEVICE_atSectors}+(${SIZEOF_SECTOR_INFO_STRUCT}*ulCnt)+${OFFSETOF_SECTOR_INFO_STRUCT_ulSize})
	print(string.format("  %03d: 0x%08x 0x%08x", ulCnt, ulOffset, ulSize))
end

