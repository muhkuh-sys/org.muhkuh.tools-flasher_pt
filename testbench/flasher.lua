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
require("tester")
local progress = tester.callback_progress
local callback = tester.callback


BUS_Parflash    = 0             -- parallel flash
BUS_Spi         = 1             -- serial flash on spi bus


OPERATION_MODE_Flash             = 0
OPERATION_MODE_Erase             = 1
OPERATION_MODE_Read              = 2
OPERATION_MODE_Verify            = 3
OPERATION_MODE_Checksum          = 4     -- Build a checksum over the contents of a specified area of a device.
OPERATION_MODE_Detect            = 5     -- Detect a device.
OPERATION_MODE_IsErased          = 6     -- Check if the specified area of a device is erased.
OPERATION_MODE_GetEraseArea      = 7     -- Expand an area to the erase block borders.
OPERATION_MODE_GetBoardInfo      = 8     -- Get bus and unit information.


MSK_SQI_CFG_IDLE_IO1_OE          = 0x01
SRT_SQI_CFG_IDLE_IO1_OE          = 0
MSK_SQI_CFG_IDLE_IO1_OUT         = 0x02
SRT_SQI_CFG_IDLE_IO1_OUT         = 1
MSK_SQI_CFG_IDLE_IO2_OE          = 0x04
SRT_SQI_CFG_IDLE_IO2_OE          = 2
MSK_SQI_CFG_IDLE_IO2_OUT         = 0x08
SRT_SQI_CFG_IDLE_IO2_OUT         = 3
MSK_SQI_CFG_IDLE_IO3_OE          = 0x10
SRT_SQI_CFG_IDLE_IO3_OE          = 4
MSK_SQI_CFG_IDLE_IO3_OUT         = 0x20
SRT_SQI_CFG_IDLE_IO3_OUT         = 5



-- Download flasher.
-- tPlugin plugin object with an active connection
-- strPrefix path to flasher binaries
-- fnCallback callback to call while downloading the flasher
--
-- - Load the flasher binary according to the chip type the
--    plugin is connected to
-- - Extract header information from the flasher
--   (static information about code/exec/buffer addresses)
-- - Download the flasher to the specified address
-- - Returns header information

function download(tPlugin, strPrefix, fnCallback)
	-- Get the chiptyp.
	local tAsicTyp = tPlugin:GetChiptyp()
	local aAttr = {}

	-- Get the binary for the ASIC.
	print(string.format("detected chip type: %d %s", tAsicTyp, tPlugin:GetChiptypName(tAsicTyp)))
	if tAsicTyp==romloader_usb.ROMLOADER_CHIPTYP_NETX50 then
		aAttr.strBinaryName = strPrefix .. "flasher_netx50.bin"
	elseif tAsicTyp==romloader_usb.ROMLOADER_CHIPTYP_NETX100 or tAsicTyp==romloader_usb.ROMLOADER_CHIPTYP_NETX500 then
		aAttr.strBinaryName = strPrefix .. "flasher_netx500.bin"
	elseif tAsicTyp==romloader_usb.ROMLOADER_CHIPTYP_NETX10 then
		aAttr.strBinaryName = strPrefix .. "flasher_netx10.bin"
	else
		error("Unknown chiptyp! " .. tostring(tAsicTyp))
	end

	-- Try to load the binary.
	strData, msg = muhkuh.load(aAttr.strBinaryName)
	if not strData then
		error("Failed to load binary '" .. aAttr.strBinaryName .. "': " .. msg)
	else
		print(string.format("loaded file %s, %d bytes", aAttr.strBinaryName, strData:len()))
		-- Get the load and exec address from the binary.
		aAttr.ulLoadAddress = strData:byte(33) + strData:byte(34)*0x00000100 + strData:byte(35)*0x00010000 + strData:byte(36)*0x01000000
		aAttr.ulExecAddress = strData:byte(37) + strData:byte(38)*0x00000100 + strData:byte(39)*0x00010000 + strData:byte(40)*0x01000000
		aAttr.ulParameter   = strData:byte(41) + strData:byte(42)*0x00000100 + strData:byte(43)*0x00010000 + strData:byte(44)*0x01000000
		aAttr.ulDeviceDesc  = strData:byte(45) + strData:byte(46)*0x00000100 + strData:byte(47)*0x00010000 + strData:byte(48)*0x01000000
		aAttr.ulBufferAdr   = strData:byte(49) + strData:byte(50)*0x00000100 + strData:byte(51)*0x00010000 + strData:byte(52)*0x01000000
		aAttr.ulBufferEnd   = strData:byte(53) + strData:byte(54)*0x00000100 + strData:byte(55)*0x00010000 + strData:byte(56)*0x01000000
		aAttr.ulBufferLen   = aAttr.ulBufferEnd - aAttr.ulBufferAdr

		-- Show the information:
		print(string.format("parameter:          0x%08x\n", aAttr.ulParameter))
		print(string.format("device description: 0x%08x\n", aAttr.ulDeviceDesc))
		print(string.format("buffer start:       0x%08x\n", aAttr.ulBufferAdr))
		print(string.format("buffer end:         0x%08x\n", aAttr.ulBufferEnd))

		-- download binary
		print(string.format("downloading %s to 0x%08x", aAttr.strBinaryName, aAttr.ulLoadAddress))
		tPlugin:write_image(aAttr.ulLoadAddress, strData, fnCallback, string.len(strData))
		
		return aAttr
	end
end


local function set_parameterblock(tPlugin, ulAddress, aulParameters)
	local strBin = ""
	for i,v in ipairs(aulParameters) do
		strBin = strBin .. string.char( bit.band(v,0xff), bit.band(bit.rshift(v,8),0xff), bit.band(bit.rshift(v,16),0xff), bit.band(bit.rshift(v,24),0xff) )
	end
	tPlugin:write_image(ulAddress, strBin, progress, string.len(strBin))
end

function callFlasher(tPlugin, aAttr, aulParams)
	-- set the parameters
	local aulParameter = {}
	aulParameter[1] = 0xffffffff             -- placeholder for return vallue, will be 0 if ok
	aulParameter[2] = aAttr.ulParameter+0x0c -- pointer to actual parameters
	aulParameter[3] = 0x00000000             -- unused
	                                         -- extended parameters
	aulParameter[4] = 0x00020000             -- parameter version: 2.0
	for i=1, #aulParams do
		aulParameter[4+i] = aulParams[i]     -- actual parameters for the particular function
	end

	set_parameterblock(tPlugin, aAttr.ulParameter, aulParameter)
	
	-- call
	tPlugin:call(aAttr.ulExecAddress, aAttr.ulParameter, callback, 2)
	
	-- get the return value (ok/failed)
	-- any further return values must be read by the calling function
	ulValue = tPlugin:read_data32(aAttr.ulParameter+0x00)
	print(string.format("call finished with result 0x%08x", ulValue))
	return ulValue
end


function flash(tPlugin, aAttr, ulStartAdr, ulDataByteSize, ulDataAddress)
	local aulParameter = 
	{
		OPERATION_MODE_Flash,
		aAttr.ulDeviceDesc,
		ulStartAdr,
		ulDataByteSize,
		ulDataAddress
	}
	local ulValue = callFlasher(tPlugin, aAttr, aulParameter)
	return ulValue == 0
end

-- ulStartAdr = address in Flash, ulDataAddress = address in buffer
function read(tPlugin, aAttr, ulFlashStartOffset, ulFlashEndOffset, ulBufferAddress)
	local aulParameter = 
	{
		OPERATION_MODE_Read,
		aAttr.ulDeviceDesc,
		ulFlashStartOffset,
		ulFlashEndOffset,
		ulBufferAddress
	}
	local ulValue = callFlasher(tPlugin, aAttr, aulParameter)
	return ulValue == 0
end


-- ulStartAdr = address in Flash, ulDataAddress = address in buffer
function verify(tPlugin, aAttr, ulFlashStartOffset, ulFlashEndOffset, ulBufferAddress)
	local fEqual = false
	local aulParameter = 
	{
		OPERATION_MODE_Verify,
		aAttr.ulDeviceDesc,
		ulFlashStartOffset,
		ulFlashEndOffset,
		ulBufferAddress
	}
	local ulValue = callFlasher(tPlugin, aAttr, aulParameter)
	
	if ulValue==0 then
		ulValue = tPlugin:read_data32(aAttr.ulParameter+0x08)
		fEqual = (ulValue==0)
	end
	
	return fEqual
end



function erase(tPlugin, aAttr, ulEraseStart, ulEraseEnd)
	local aulParameter = 
	{
		OPERATION_MODE_Erase,                          -- operation mode: erase
		aAttr.ulDeviceDesc,                            -- data block for the device description
		ulEraseStart,
		ulEraseEnd
	}
	local ulValue = callFlasher(tPlugin, aAttr, aulParameter)
	return ulValue == 0
end



-- ulDevDescAdr is unused
function detect(tPlugin, aAttr, tBus, ulUnit, ulChipSelect, ulDevDescAdr)
	local ulValue
	local aulParameter
	local strDevDesc = nil
	local ulIdleCfg


	ulIdleCfg = 
	  MSK_SQI_CFG_IDLE_IO1_OE + MSK_SQI_CFG_IDLE_IO1_OUT 
	+ MSK_SQI_CFG_IDLE_IO2_OE + MSK_SQI_CFG_IDLE_IO2_OUT 
	+ MSK_SQI_CFG_IDLE_IO3_OE + MSK_SQI_CFG_IDLE_IO3_OUT

	aulParameter = 
	{
		OPERATION_MODE_Detect,                -- operation mode: detect
		tBus,                                 -- device: spi flash
		ulUnit,                               -- unit
		ulChipSelect,                         -- chip select: 1
		1000,                                 -- initial speed in kHz (1000 -> 1MHz)
		ulIdleCfg,                            -- idle config
		3,                                    -- mode
		0xffffffff,                           -- mmio config
		aAttr.ulDeviceDesc                    -- data block for the device description
	}
	
	ulValue = callFlasher(tPlugin, aAttr, aulParameter)
	
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



function getEraseArea(tPlugin, aAttr, ulStartAdr, ulEndAdr)
	local ulValue
	local aulParameter
	local ulEraseStart
	local ulEraseEnd

	aulParameter = 
	{
		OPERATION_MODE_GetEraseArea,           -- operation mode: get erase area
		aAttr.ulDeviceDesc,                    -- data block for the device description
		ulStartAdr,
		ulEndAdr
	}
	
	ulValue = callFlasher(tPlugin, aAttr, aulParameter)
	if ulValue==0 then
		ulEraseStart = tPlugin:read_data32(aAttr.ulParameter+0x18)
		ulEraseEnd = tPlugin:read_data32(aAttr.ulParameter+0x1c)
	end

	return ulEraseStart, ulEraseEnd
end

function isErased(tPlugin, aAttr, ulEraseStart, ulEraseEnd)
	local fIsErased = false

	local aulParameter = 
	{
		OPERATION_MODE_IsErased,               -- operation mode: isErased
		aAttr.ulDeviceDesc,                    -- data block for the device description
		ulEraseStart,
		ulEraseEnd
	}
	
	local ulValue = callFlasher(tPlugin, aAttr, aulParameter)
	if ulValue==0 then
		ulValue = tPlugin:read_data32(aAttr.ulParameter+0x08)
		fIsErased = (ulValue==0xff)
	end

	return fIsErased
end


local function getInfoBlock(tPlugin, aAttr, ulBusIdx, ulUnitIdx)
	local aResult = nil
	
	local aulParameter = 
	{
		OPERATION_MODE_GetBoardInfo,           -- operation mode: get board info
		ulBusIdx,
		ulUnitIdx,
		aAttr.ulBufferAdr,
		aAttr.ulBufferLen
	}
	
	local ulValue = callFlasher(tPlugin, aAttr, aulParameter)

	if ulValue==0 then
		-- Get the size of the board description.
		local sizInfoMax = tPlugin:read_data32(aAttr.ulParameter+0x08)
		if sizInfoMax>0 then
			-- Get the board information.
			strInfo = tPlugin:read_image(aAttr.ulBufferAdr, sizInfoMax, progress, sizInfoMax)

			-- Get the number of entries.
			local sizEntryNum = strInfo:byte(1)
			aResult = {}
			-- Loop over all entries.
			strNames = strInfo:sub(2)
			for strIdx,strName in string.gmatch(strNames, "(.)([^%z]+)%z") do
				table.insert(aResult, { iIdx=strIdx:byte(1), strName=strName })
			end
		end
	end

	return aResult
end


function getBoardInfo(tPlugin, aAttr)
	-- Get the bus infos.
	local aBoardInfo = getInfoBlock(tPlugin, aAttr, 0xffffffff, 0xffffffff)
	for iCnt,aBusInfo in ipairs(aBoardInfo) do
		-- Get the unit info.
		local aUnitInfo = getInfoBlock(tPlugin, aAttr, aBusInfo.iIdx, 0xffffffff)
		aBusInfo.aUnitInfo = aUnitInfo
	end

	return aBoardInfo
end


