
-- NOTE: This script uses the "bit" and "romloader_usb" lua libraries. Both
-- are part of the "Muhkuh" experimental distribution.

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


	-- Download the binary.
	aAttr = flasher.download(tPlugin, "../targets/", progress)

	-- Use parallel flash on unit 0, chipselect 0.
	strDevDesc = flasher.detect(tPlugin, aAttr, flasher.BUS_Parflash, 0, 0, ulDevDescAdr)
	if strDevDesc==nil then
		error("Failed to get a device description!")
	end

	-- Get erase area.
	local ulDataFirst, ulDataEnd, ulEraseFirst, ulEraseEnd
	ulDataFirst = 0x00020080
	ulDataEnd = 0x00021000
	ulEraseFirst,ulEraseEnd = flasher.getEraseArea(tPlugin, aAttr, ulDataFirst, ulDataEnd)
	if ulEraseFirst==nil or ulEraseEnd==nil then
		error("Failed to get the erase area!")
	end
	print(string.format("Area:  [0x%08x, 0x%08x[", ulDataFirst, ulDataEnd))
	print(string.format("Erase: [0x%08x, 0x%08x[", ulEraseFirst, ulEraseEnd))

	-- Check if the area is erased.
	local fIsErased
	fIsErased = flasher.isErased(tPlugin, aAttr, ulEraseStart, ulEraseEnd)
	if fIsErased==nil then
		error("Failed to check if the area is erased!")
	elseif fIsErased==true then
		print("!ALL CLEAN! The area is erased.")
	else
		print("!!!DIRTY!!! The area must be erased before flashing!")
	end

	-- disconnect the plugin
	tPlugin:Disconnect()

	-- free the plugin
	tPlugin = nil
end
