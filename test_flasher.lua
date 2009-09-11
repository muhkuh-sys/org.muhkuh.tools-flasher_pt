
-- NOTE: This script uses the "bit" and "romloader_usb" lua libraries. Both
-- are part of the "Muhkuh" experimental distribution.

require("bit")
--require("romloader_baka")
require("romloader_usb")

strFlasherBin_nx500 = "flasher_netx500.bin"


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


local function set_parameterblock(tPlugin, ulAddress, aulParameters)
	local strBin = ""


	for i,v in ipairs(aulParameters) do
		strBin = strBin .. string.char( bit.band(v,0xff), bit.band(bit.rshift(v,8),0xff), bit.band(bit.rshift(v,16),0xff), bit.band(bit.rshift(v,24),0xff) )
	end
	tPlugin:write_image(ulAddress, strBin, progress, string.len(strBin))
end


local function flash_detect(tPlugin, tBus, ulChipSelect, ulDevDescAdr)
	local parameter_block = 0x00018000
	local dev_desc_adr = 0x00018080
	local ulValue
	local aulParameter
	local strDevDesc = nil


	aulParameter = {}
	-- set the parameter
	aulParameter[1] = 0xffffffff
	aulParameter[2] = parameter_block+0x0c
	aulParameter[3] = 0x00000000
	-- set the extended parameter
	aulParameter[4] = 0x00020000					-- parameter version: 2.0
	aulParameter[5] = 5						-- operation mode: detect
	aulParameter[6] = tBus						-- device: spi flash
	aulParameter[7] = ulChipSelect					-- chip select: 1
	aulParameter[8] = ulDevDescAdr					-- data block for the device description

	set_parameterblock(tPlugin, parameter_block, aulParameter)


	tPlugin:call(0x00008000, parameter_block, callback, 2)

	-- get the result
	ulValue = tPlugin:read_data32(parameter_block+0x00)
	print(string.format("call finished with result 0x%08x", ulValue))
	if ulValue==0 then
		-- check the device description
		ulValue = tPlugin:read_data32(ulDevDescAdr)
		if ulValue==0 then
			print("the device desription is not valid, nothing detected.")
		else
			local ulSize
			local ulVersion

			-- get the size of the returned data
			ulSize = tPlugin:read_data32(ulDevDescAdr+0x04)
			if ulSize<16 then
				print("the device description claims to be valid, but has a strange size.")
			else
				-- read the interface version of the returned data
				ulVersion = tPlugin:read_data32(ulDevDescAdr+0x08)
				if ulVersion~=0x00020000 then
					-- the version does not match the expected value
					print(string.format("the device description has a strange interface version."))
				else
					-- get the device description
					strDevDesc = tPlugin:read_image(ulDevDescAdr, ulSize, progress, ulSize)
				end
			end
		end
	end

	return strDevDesc
end


local function flash_erase(tPlugin, ulDevDescAdr, ulStartAdr, ulLastAdr)
	local parameter_block = 0x00018000
	local dev_desc_adr = 0x00018080
	local ulValue
	local aulParameter
	local strDevDesc = nil


	aulParameter = {}
	-- set the parameter
	aulParameter[1] = 0xffffffff
	aulParameter[2] = parameter_block+0x0c
	aulParameter[3] = 0x00000000
	-- set the extended parameter
	aulParameter[4] = 0x00020000					-- parameter version: 2.0
	aulParameter[5] = 7						-- operation mode: 
	aulParameter[6] = tBus						-- device: spi flash
	aulParameter[7] = ulChipSelect					-- chip select: 1
	aulParameter[8] = ulDevDescAdr					-- data block for the device description

	set_parameterblock(tPlugin, parameter_block, aulParameter)


	tPlugin:call(0x00008000, parameter_block, callback, 2)

	-- get the result
	ulValue = tPlugin:read_data32(parameter_block+0x00)
	print(string.format("call finished with result 0x%08x", ulValue))

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


		-- download binary to 0x00008000
		tPlugin:write_image(0x00008000, strBin, progress, string.len(strBin))

		strDevDesc = flash_detect(tPlugin, 2, 1, ulDevDescAdr)
--		strDevDesc = flash_detect(tPlugin, 2, 2, ulDevDescAdr)
--		strDevDesc = flash_detect(tPlugin, 2, 4, ulDevDescAdr)
		if not strDevDesc then
			print("Failed to get a device description!")
		else
			-- show the device description
			hexdump(strDevDesc)

			-- erase the first 64KBytes
			flash_erase(tPlugin, ulDevDescAdr, 0, 65535)
		end

	end

	-- disconnect the plugin
	tPlugin:Disconnect()

	-- free the plugin
	tPlugin = nil
end
