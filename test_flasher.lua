
-- NOTE: This script uses the "bit" and "romloader_usb" lua libraries. Both
-- are part of the "Muhkuh" experimental distribution.

--require("romloader_baka")
require("romloader_usb")

require("flasher")


-- strFlasherBin_nx500 = "flasher_netx500.bin"
strFlasherBin_nx500 = "flasher_netx5_500.bin"


local function progress(cnt,max)
	print(string.format("%d%% (%d/%d)", cnt*100/max, cnt, max))
	return true
end

local function callback(a,b)
	print(string.format("'%s'", a))
	return true
end

local function get_rnd_data(len)
	local data = ""
	for i=1,len do
		data = data .. string.char(math.random(0,255))
	end
	return data
end

-- read binary file into string
-- returns the file or nil, message
function loadBin(strName)
	print("reading file " .. strName)
	local bin
	local f, msg = io.open(strName, "rb")
	if f then
		bin = f:read("*all")
		f:close()
		print(bin:len() .. " bytes read")
		return bin
	else
		return nil, msg
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

	-- try to load netx500 binary
	strBin, msg = loadBin(strFlasherBin_nx500)
	if not strBin then
		print("failed to load flasher binary: " .. msg)
		print("skipping call test.")
	else
		local strDevDesc
		local ulDevDescAdr = 0x00018100
		local ulEraseStart
		local ulEraseEnd


		-- download binary to 0x00008000
		tPlugin:write_image(0x00008000, strBin, progress, string.len(strBin))

		strDevDesc = flasher.detect(tPlugin, 2, 1, ulDevDescAdr)
--		strDevDesc = flasher.detect(tPlugin, 2, 2, ulDevDescAdr)
--		strDevDesc = flasher.detect(tPlugin, 2, 4, ulDevDescAdr)
		if not strDevDesc then
			print("Failed to get a device description!")
		else
			-- show the device description
			hexdump(strDevDesc)

			-- erase the first 64KBytes
			ulEraseStart, ulEraseEnd = flasher.getEraseArea(tPlugin, ulDevDescAdr, 0, 65536)
			if not ulEraseStart then
				print("Failed to get erase areas!")
			else
				local fIsErased


				print(string.format("Checking area 0x%08x-0x%08x...", ulEraseStart, ulEraseEnd))
				fIsErased = flasher.isErased(tPlugin, ulDevDescAdr, ulEraseStart, ulEraseEnd)
				if fIsErased==nil then
					print("failed to check the area!")
				else
					local fIsOk


					if fIsErased==true then
						print("The area is already erased.")
						fIsOk = true
					else
						print("The area is not erased. Erasing it now...")
						fIsOk = flasher.erase(tPlugin, ulDevDescAdr, ulEraseStart, ulEraseEnd)
						if not fIsOk then
							print("Failed to erase the area!")
						else
							fIsErased = flasher.isErased(tPlugin, ulDevDescAdr, ulEraseStart, ulEraseEnd)
							if not fIsErased then
								print("No error reported, but the area is not erased!")
								fIsOk = false
							end
						end
					end

					if fIsOk==true then
						print("Writing area...")
						-- TODO: Write area in little chunks. For this test it's a 64K chunk so ot does not matter.
						fIsOk = flasher.flash(tPlugin, ulDevDescAdr, 0, 65536, 0x00200000)
					end
				end
			end
		end
	end

	-- disconnect the plugin
	tPlugin:Disconnect()

	-- free the plugin
	tPlugin = nil
end
