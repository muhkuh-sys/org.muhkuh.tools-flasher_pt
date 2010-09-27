-----------------------------------------------------------------------------
--   Copyright (C) 2009 by Christoph Thelen                                --
--   doc_bacardi@users.sourceforge.net                                     --
--                                                                         --
--   This program is free software; you can redistribute it and/or modify  --
--   it under the terms of the GNU General Public License as published by  --
--   the Free Software Foundation; either version 2 of the License, or     --
--   (at your option) any later version.                                   --
--                                                                         --
--   This program is distributed in the hope that it will be useful,       --
--   but WITHOUT ANY WARRANTY; without even the implied warranty of        --
--   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         --
--   GNU General Public License for more details.                          --
--                                                                         --
--   You should have received a copy of the GNU General Public License     --
--   along with this program; if not, write to the                         --
--   Free Software Foundation, Inc.,                                       --
--   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             --
-----------------------------------------------------------------------------

module("flasher", package.seeall)

require("bit")

BUS_Parflash    = 0             -- parallel flash
BUS_Spi         = 1             -- serial flash on spi bus


OPERATION_MODE_Flash             = 0
OPERATION_MODE_Erase             = 1
OPERATION_MODE_Read              = 2
OPERATION_MODE_Verify            = 3
OPERATION_MODE_Checksum          = 4     -- Build a checksum over the contents of a specified area of a device.
OPERATION_MODE_Detect            = 5     -- Detect a device.
OPERATION_MODE_IsErased          = 6     -- Check if the specified area of a device is erased.
OPERATION_MODE_GetEraseArea      = 7


local function progress(cnt,max)
	print(string.format("%d%% (%d/%d)", cnt*100/max, cnt, max))
	return true
end

local function callback(a,b)
	print(string.format("'%s'", a))
	return true
end


local function set_parameterblock(tPlugin, ulAddress, aulParameters)
	local strBin = ""


	for i,v in ipairs(aulParameters) do
		strBin = strBin .. string.char( bit.band(v,0xff), bit.band(bit.rshift(v,8),0xff), bit.band(bit.rshift(v,16),0xff), bit.band(bit.rshift(v,24),0xff) )
	end
	tPlugin:write_image(ulAddress, strBin, progress, string.len(strBin))
end


function download(tPlugin, strPrefix, fnCallback)
	-- Get the chiptyp.
	local tAsicTyp = tPlugin:GetChiptyp()
	print(tAsicTyp)
	print(romloader_usb.ROMLOADER_CHIPTYP_NETX50)
	print(romloader_usb.ROMLOADER_CHIPTYP_NETX100)
	print(romloader_usb.ROMLOADER_CHIPTYP_NETX500)
	local aAttr = {}

	-- Get the binary for the ASIC.
	if tAsicTyp==romloader_usb.ROMLOADER_CHIPTYP_NETX50 then
		aAttr.strBinaryName = strPrefix .. "flasher_netx50.bin"
		aAttr.ulParameter   = 0x00017000
		aAttr.ulDeviceDesc  = 0x00017100
	elseif tAsicTyp==romloader_usb.ROMLOADER_CHIPTYP_NETX100 or tAsicTyp==romloader_usb.ROMLOADER_CHIPTYP_NETX500 then
		aAttr.strBinaryName = strPrefix .. "flasher_netx500.bin"
		aAttr.ulParameter   = 0x00017000
		aAttr.ulDeviceDesc  = 0x00017100
	elseif tAsicTyp==romloader_usb.ROMLOADER_CHIPTYP_NETX10 then
		aAttr.strBinaryName = strPrefix .. "flasher_netx10.bin"
		aAttr.ulParameter   = 0x04038000
		aAttr.ulDeviceDesc  = 0x04038100
	else
		error("Unknown chiptyp!")
	end

	-- Try to load the binary.
	strData, msg = muhkuh.load(aAttr.strBinaryName)
	if not strData then
		error("Failed to load binary '" .. aAttr.strBinaryName .. "': " .. msg)
	else
		-- Get the load and exec address from the binary.
		aAttr.ulLoadAddress = strData:byte(33) + strData:byte(34)*0x00000100 + strData:byte(35)*0x00010000 + strData:byte(36)*0x01000000
		aAttr.ulExecAddress = strData:byte(37) + strData:byte(38)*0x00000100 + strData:byte(39)*0x00010000 + strData:byte(40)*0x01000000

		-- download binary
		print(string.format("downloading %s to 0x%08x", aAttr.strBinaryName, aAttr.ulLoadAddress))
		tPlugin:write_image(aAttr.ulLoadAddress, strData, fnCallback, string.len(strData))
		return aAttr
	end
end


function flash(tPlugin, aAttr, ulStartAdr, ulDataByteSize, ulDataAddress)
	local ulValue
	local aulParameter
	local fIsOk


	aulParameter = {}
	-- set the parameter
	aulParameter[1] = 0xffffffff
	aulParameter[2] = aAttr.ulParameter+0x0c
	aulParameter[3] = 0x00000000
	-- set the extended parameter
	aulParameter[4] = 0x00020000					-- parameter version: 2.0
	aulParameter[5] = OPERATION_MODE_Flash				-- operation mode: Flash
	aulParameter[6] = aAttr.ulDeviceDesc				-- data block for the device description
	aulParameter[7] = ulStartAdr
	aulParameter[8] = ulDataByteSize
	aulParameter[9] = ulDataAddress

	set_parameterblock(tPlugin, aAttr.ulParameter, aulParameter)

	tPlugin:call(aAttr.ulExecAddress, aAttr.ulParameter, callback, 2)

	-- get the result
	ulValue = tPlugin:read_data32(aAttr.ulParameter+0x00)
	print(string.format("call finished with result 0x%08x", ulValue))
	fIsOk = (ulValue==0)

	return fIsOk
end



function erase(tPlugin, aAttr, ulEraseStart, ulEraseEnd)
	local ulValue
	local aulParameter
	local fIsOk


	aulParameter = {}
	-- set the parameter
	aulParameter[1] = 0xffffffff
	aulParameter[2] = aAttr.ulParameter+0x0c
	aulParameter[3] = 0x00000000
	-- set the extended parameter
	aulParameter[4] = 0x00020000					-- parameter version: 2.0
	aulParameter[5] = OPERATION_MODE_Erase				-- operation mode: erase
	aulParameter[6] = aAttr.ulDeviceDesc				-- data block for the device description
	aulParameter[7] = ulEraseStart
	aulParameter[8] = ulEraseEnd

	set_parameterblock(tPlugin, aAttr.ulParameter, aulParameter)


	tPlugin:call(aAttr.ulExecAddress, aAttr.ulParameter, callback, 2)

	-- get the result
	ulValue = tPlugin:read_data32(aAttr.ulParameter+0x00)
	print(string.format("call finished with result 0x%08x", ulValue))
	fIsOk = (ulValue==0)

	return fIsOk
end



function detect(tPlugin, aAttr, tBus, ulUnit, ulChipSelect, ulDevDescAdr)
	local ulValue
	local aulParameter
	local strDevDesc = nil


	aulParameter = {}
	-- set the parameter
	aulParameter[ 1] = 0xffffffff
	aulParameter[ 2] = aAttr.ulParameter+0x0c
	aulParameter[ 3] = 0x00000000
	-- set the extended parameter
	aulParameter[ 4] = 0x00020000				-- parameter version: 2.0
	aulParameter[ 5] = OPERATION_MODE_Detect			-- operation mode: detect
	aulParameter[ 6] = tBus					-- device: spi flash
	aulParameter[ 7] = ulUnit				-- unit
	aulParameter[ 8] = ulChipSelect				-- chip select: 1
	aulParameter[ 9] = 1000					-- initial speed in kHz (1000 -> 1MHz)
	aulParameter[10] = 0					-- idle config
	aulParameter[11] = 3					-- mode
	aulParameter[12] = 0xffffffff				-- mmio config
	aulParameter[13] = aAttr.ulDeviceDesc			-- data block for the device description

	set_parameterblock(tPlugin, aAttr.ulParameter, aulParameter)


	tPlugin:call(aAttr.ulExecAddress, aAttr.ulParameter, callback, 2)

	-- get the result
	ulValue = tPlugin:read_data32(aAttr.ulParameter+0x00)
	print(string.format("call finished with result 0x%08x", ulValue))
	if ulValue==0 then
		-- check the device description
		ulValue = tPlugin:read_data32(aAttr.ulDeviceDesc)
		if ulValue==0 then
			print("the device desription is not valid, nothing detected.")
		else
			local ulSize
			local ulVersion

			-- get the size of the returned data
			ulSize = tPlugin:read_data32(aAttr.ulDeviceDesc+0x04)
			if ulSize<16 then
				print("the device description claims to be valid, but has a strange size.")
			else
				-- read the interface version of the returned data
				ulVersion = tPlugin:read_data32(aAttr.ulDeviceDesc+0x08)
				if ulVersion~=0x00020000 then
					-- the version does not match the expected value
					print(string.format("the device description has a strange interface version."))
				else
					-- get the device description
					strDevDesc = tPlugin:read_image(aAttr.ulDeviceDesc, ulSize, progress, ulSize)
				end
			end
		end
	end

	return strDevDesc
end



function getEraseArea(tPlugin, aAttr, ulStartAdr, ulLastAdr)
	local ulValue
	local aulParameter
	local ulEraseStart
	local ulEraseEnd


	aulParameter = {}
	-- set the parameter
	aulParameter[1] = 0xffffffff
	aulParameter[2] = aAttr.ulParameter+0x0c
	aulParameter[3] = 0x00000000
	-- set the extended parameter
	aulParameter[4] = 0x00020000				-- parameter version: 2.0
	aulParameter[5] = OPERATION_MODE_GetEraseArea		-- operation mode: get erase area
	aulParameter[6] = aAttr.ulDeviceDesc			-- data block for the device description
	aulParameter[7] = ulStartAdr
	aulParameter[8] = ulLastAdr


	set_parameterblock(tPlugin, aAttr.ulParameter, aulParameter)


	tPlugin:call(aAttr.ulExecAddress, aAttr.ulParameter, callback, 2)

	-- get the result
	ulValue = tPlugin:read_data32(aAttr.ulParameter+0x00)
	print(string.format("call finished with result 0x%08x", ulValue))
	if ulValue==0 then
		-- check the device description
		ulEraseStart = tPlugin:read_data32(aAttr.ulParameter+0x18)
		ulEraseEnd = tPlugin:read_data32(aAttr.ulParameter+0x1c)
	end

	return ulEraseStart, ulEraseEnd
end



function isErased(tPlugin, aAttr, ulEraseStart, ulEraseEnd)
	local parameter_block = 0x00018000
	local dev_desc_adr = 0x00018080
	local ulValue
	local aulParameter
	local ulEraseStart
	local ulEraseEnd
	local fIsErased


	aulParameter = {}
	-- set the parameter
	aulParameter[1] = 0xffffffff
	aulParameter[2] = aAttr.ulParameter+0x0c
	aulParameter[3] = 0x00000000
	-- set the extended parameter
	aulParameter[4] = 0x00020000					-- parameter version: 2.0
	aulParameter[5] = OPERATION_MODE_IsErased			-- operation mode: isErased
	aulParameter[6] = aAttr.ulDeviceDesc				-- data block for the device description
	aulParameter[7] = ulEraseStart
	aulParameter[8] = ulEraseEnd

	set_parameterblock(tPlugin, aAttr.ulParameter, aulParameter)


	tPlugin:call(aAttr.ulExecAddress, aAttr.ulParameter, callback, 2)

	-- get the result
	ulValue = tPlugin:read_data32(aAttr.ulParameter+0x00)
	print(string.format("call finished with result 0x%08x", ulValue))
	if ulValue==0 then
		-- check the device description
		ulValue = tPlugin:read_data32(aAttr.ulParameter+0x08)
		fIsErased = (ulValue==0xff)
	end

	return fIsErased
end

