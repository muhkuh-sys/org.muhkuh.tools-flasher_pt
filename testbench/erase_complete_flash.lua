
-- NOTE: This script uses the "bit" and "romloader_usb" lua libraries. Both
-- are part of the "Muhkuh" experimental distribution.

--require("romloader_baka")
require("romloader_usb")

require("flasher")


local function progress(cnt,max)
	print(string.format("%d%% (%d/%d)", cnt*100/max, cnt, max))
	return true
end

local function callback(a,b)
	print(string.format("'%s'", a))
	return true
end


-- Muhkuh V1 emu function: read binary file into string.
--   returns the file or raises an error
if not muhkuh then
	muhkuh = {}
end
function muhkuh.load(strName)
	print("reading file " .. strName)
	local bin
	local f, msg = io.open(strName, "rb")
	if f then
		bin = f:read("*all")
		f:close()
		print(bin:len() .. " bytes read")
		return bin
	else
		error(msg)
	end
end


local function hexdump(strData, iBytesPerRow)
	local iCnt
	local iByteCnt
	local strDump


	if not iBytesPerRow then
		iBytesPerRow = 16
	end

	iByteCnt = 0
	for iCnt=1,strData:len() do
		if iByteCnt==0 then
			strDump = string.format("%08X :", iCnt-1)
		end
		strDump = strDump .. string.format(" %02X", strData:byte(iCnt))
		iByteCnt = iByteCnt + 1
		if iByteCnt==iBytesPerRow then
			iByteCnt = 0
			print(strDump)
		end
	end
	if iByteCnt~=0 then
		print(strDump)
	end
end




-- show all providers
print("Available plugins:")
for i,v in ipairs(__MUHKUH_PLUGINS) do
	local strID
	local tVer
	strID = v:GetID()
	tVer = v:GetVersion()
	print(string.format("%d: %s, v%d.%d.%d", i, strID, tVer.uiVersionMajor, tVer.uiVersionMinor, tVer.uiVersionSub))
end


-- detect all interfaces
aDetectedInterfaces = {}
for i,v in ipairs(__MUHKUH_PLUGINS) do
	local iDetected
	print(string.format("Detecting interfaces with plugin %s", v:GetID()))
	iDetected = v:DetectInterfaces(aDetectedInterfaces)
	print(string.format("Found %d interfaces with plugin %s", iDetected, v:GetID()))
end
print(string.format("Found a total of %d interfaces with %d plugins", #aDetectedInterfaces, #__MUHKUH_PLUGINS))


if #aDetectedInterfaces==0 then
	print("No interfaces detected, nothing to do...")
else
	-- select a list entry
	iIndex = 1

	-- create the plugin
	tPlugin = aDetectedInterfaces[iIndex]:Create()
	-- connect the plugin
	tPlugin:Connect()

	local strDevDesc
	local ulEraseStart
	local ulEraseEnd


	-- Download the binary.
	aAttr = flasher.download(tPlugin, "../targets/", progress)

	-- Use SPI Flash CS0.
	strDevDesc = flasher.detect(tPlugin, aAttr, flasher.BUS_Spi, 0, 0, ulDevDescAdr)
	if not strDevDesc then
		error("Failed to get a device description!")
	end

	-- show the device description
	--hexdump(strDevDesc)

	-- erase the first page
	ulEraseStart, ulEraseEnd = flasher.getEraseArea(tPlugin, aAttr, 0, 4194304)
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

	-- free the plugin
	tPlugin = nil
end
