module("flasher", package.seeall)

-----------------------------------------------------------------------------
--   Copyright (C) 2019 by Christoph Thelen                                --
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
-- 
-- Description:
--   flasher.lua: flasher interface routines
--
-----------------------------------------------------------------------------

require("bit")
require("romloader")


-----------------------------------------------------------------------------
--                           Definitions
-----------------------------------------------------------------------------

BUS_Parflash    = ${BUS_ParFlash}             -- parallel flash
BUS_Spi         = ${BUS_SPI}             -- serial flash on spi bus
BUS_IFlash      = ${BUS_IFlash}             -- internal flash
BUS_SDIO        = ${BUS_SDIO}             -- SD/EMMC




OPERATION_MODE_Flash             = ${OPERATION_MODE_Flash}
OPERATION_MODE_Erase             = ${OPERATION_MODE_Erase}
OPERATION_MODE_Read              = ${OPERATION_MODE_Read}
OPERATION_MODE_Verify            = ${OPERATION_MODE_Verify}
OPERATION_MODE_Checksum          = ${OPERATION_MODE_Checksum}     -- Build a checksum over the contents of a specified area of a device.
OPERATION_MODE_Detect            = ${OPERATION_MODE_Detect}     -- Detect a device.
OPERATION_MODE_IsErased          = ${OPERATION_MODE_IsErased}     -- Check if the specified area of a device is erased.
OPERATION_MODE_GetEraseArea      = ${OPERATION_MODE_GetEraseArea}     -- Expand an area to the erase block borders.
OPERATION_MODE_GetBoardInfo      = ${OPERATION_MODE_GetBoardInfo}     -- Get bus and unit information.
OPERATION_MODE_EasyErase         = ${OPERATION_MODE_EasyErase}     -- A combination of GetEraseArea, IsErased and Erase.
OPERATION_MODE_SpiMacroPlayer    = ${OPERATION_MODE_SpiMacroPlayer}    -- A debug mode to send commands to a SPI flash.


MSK_SQI_CFG_IDLE_IO1_OE          = ${MSK_SQI_CFG_IDLE_IO1_OE}
SRT_SQI_CFG_IDLE_IO1_OE          = ${SRT_SQI_CFG_IDLE_IO1_OE}
MSK_SQI_CFG_IDLE_IO1_OUT         = ${MSK_SQI_CFG_IDLE_IO1_OUT}
SRT_SQI_CFG_IDLE_IO1_OUT         = ${SRT_SQI_CFG_IDLE_IO1_OUT}
MSK_SQI_CFG_IDLE_IO2_OE          = ${MSK_SQI_CFG_IDLE_IO2_OE}
SRT_SQI_CFG_IDLE_IO2_OE          = ${SRT_SQI_CFG_IDLE_IO2_OE}
MSK_SQI_CFG_IDLE_IO2_OUT         = ${MSK_SQI_CFG_IDLE_IO2_OUT}
SRT_SQI_CFG_IDLE_IO2_OUT         = ${SRT_SQI_CFG_IDLE_IO2_OUT}
MSK_SQI_CFG_IDLE_IO3_OE          = ${MSK_SQI_CFG_IDLE_IO3_OE}
SRT_SQI_CFG_IDLE_IO3_OE          = ${SRT_SQI_CFG_IDLE_IO3_OE}
MSK_SQI_CFG_IDLE_IO3_OUT         = ${MSK_SQI_CFG_IDLE_IO3_OUT}
SRT_SQI_CFG_IDLE_IO3_OUT         = ${SRT_SQI_CFG_IDLE_IO3_OUT}


SMC_INITIALIZE                   = ${SMC_INITIALIZE}
SMC_CHIP_SELECT                  = ${SMC_CHIP_SELECT}
SMC_EXCHANGE_DATA                = ${SMC_EXCHANGE_DATA}
SMC_SEND_DATA                    = ${SMC_SEND_DATA}
SMC_RECEIVE_DATA                 = ${SMC_RECEIVE_DATA}
SMC_SEND_IDLE_BYTES              = ${SMC_SEND_IDLE_BYTES}


FLASHER_INTERFACE_VERSION        = ${FLASHER_INTERFACE_VERSION}


--------------------------------------------------------------------------
-- callback/progress functions, 
-- read/write image, call
--------------------------------------------------------------------------


local ulProgressLastTime    = 0
local fProgressLastPercent  = 0
local ulProgressLastMax     = nil
PROGRESS_STEP_PERCENT       = 10

function default_callback_progress(ulCnt, ulMax)
	local fPercent = ulCnt * 100 / ulMax
	local ulTime = os.time()
	if ulProgressLastMax ~= ulMax
		or ulCnt == 0
		or ulCnt == ulMax
		or fProgressLastPercent - fPercent > PROGRESS_STEP_PERCENT
		or ulTime - ulProgressLastTime > 1 then
			fProgressLastPercent = fPercent
			ulProgressLastMax = ulMax
			ulProgressLastTime = ulTime
			print(string.format("%d%% (%d/%d)", fPercent, ulCnt, ulMax))
	end
	return true
end


function default_callback_message(a,b)
	if type(a)=="string" then
		local strCnt, strMax = string.match(a, "%% ([%x%X]+)/([%x%X]+)")
		if strCnt and strMax then
			local ulCnt = tonumber(strCnt, 16)
			local ulMax = tonumber(strMax, 16)
			if ulCnt and ulMax then
				return default_callback_progress(ulCnt, ulMax)
			end
		end
		io.write("[netx] ")
		local strLastChar = string.sub(a, -1)
		if strLastChar == "\r" or strLastChar == "\n" then
			io.write(a)
		else
			print(a)
		end
	end
	return true
end

function write_image(tPlugin, ulAddress, strData, fnCallbackProgress)
	return tPlugin:write_image(ulAddress, strData, fnCallbackProgress or default_callback_progress, strData:len())
end

function read_image(tPlugin, ulAddress, ulSize, fnCallbackProgress)
	return tPlugin:read_image(ulAddress, ulSize, fnCallbackProgress or default_callback_progress, ulSize)
end

function call(tPlugin, ulExecAddress, ulParameterAddress, fnCallbackMessage)
	return tPlugin:call(ulExecAddress, ulParameterAddress, fnCallbackMessage or default_callback_message, 2)
end

-----------------------------------------------------------------------------
--                    Downloading the flasher
-----------------------------------------------------------------------------

-- prefix must include a trailing backslash if it's a directory
function get_flasher_binary_path(iChiptype, strPathPrefix, fDebug)
	local strNetxName = nil
	local strDebug = fDebug and "_debug" or ""
	local strPrefix = strPathPrefix or ""

	-- First catch the unlikely case that "iChiptype" is nil.
	-- Otherwise each ROMLOADER_CHIPTYP_* which is also nil will match.
	if iChiptype==nil then
		strNetxName = nil
	elseif iChiptype==romloader.ROMLOADER_CHIPTYP_NETX500 or iChiptype==romloader.ROMLOADER_CHIPTYP_NETX100 then
		strNetxName = 'netx500'
	elseif iChiptype==romloader.ROMLOADER_CHIPTYP_NETX50 then
		strNetxName = 'netx50'
	elseif iChiptype==romloader.ROMLOADER_CHIPTYP_NETX10 then
		strNetxName = 'netx10'
	elseif iChiptype==romloader.ROMLOADER_CHIPTYP_NETX56 or iChiptype==romloader.ROMLOADER_CHIPTYP_NETX56B then
		strNetxName = 'netx56'
	elseif iChiptype==romloader.ROMLOADER_CHIPTYP_NETX4000_RELAXED or iChiptype==romloader.ROMLOADER_CHIPTYP_NETX4000_FULL or iChiptype==romloader.ROMLOADER_CHIPTYP_NETX4100_SMALL then
		strNetxName = 'netx4000'
	elseif iChiptype==romloader.ROMLOADER_CHIPTYP_NETX90_MPW then
		strNetxName = 'netx90_mpw'
	elseif iChiptype==romloader.ROMLOADER_CHIPTYP_NETX90 or iChiptype==romloader.ROMLOADER_CHIPTYP_NETX90B then
		strNetxName = 'netx90'
	elseif iChiptype==romloader.ROMLOADER_CHIPTYP_NETIOLA or iChiptype==romloader.ROMLOADER_CHIPTYP_NETIOLB then
		strNetxName = 'netiol'
	end
	if not strNetxName then
		error("Unknown chiptyp! " .. tostring(iChiptype))
	end
	
	local strPath = strPrefix .. "flasher_" .. strNetxName .. strDebug .. ".bin"
	return strPath
end


local function get_dword(strData, ulOffset)
	return strData:byte(ulOffset) + strData:byte(ulOffset+1)*0x00000100 + strData:byte(ulOffset+2)*0x00010000 + strData:byte(ulOffset+3)*0x01000000
end


-- Extract header information from the flasher binary
-- information about code/exec/buffer addresses
function get_flasher_binary_attributes(strData)
	local aAttr = {}
	
	-- Get the load and exec address from the binary.
	aAttr.ulLoadAddress = get_dword(strData, ${OFFSETOF_FLASHER_VERSION_STRUCT_pulLoadAddress} + 1)
	aAttr.ulExecAddress = get_dword(strData, ${OFFSETOF_FLASHER_VERSION_STRUCT_pfnExecutionAddress} + 1)
	aAttr.ulParameter   = get_dword(strData, ${OFFSETOF_FLASHER_VERSION_STRUCT_pucBuffer_Parameter} + 1)
	aAttr.ulDeviceDesc  = get_dword(strData, ${OFFSETOF_FLASHER_VERSION_STRUCT_pucBuffer_DeviceDescription} + 1)
	aAttr.ulBufferAdr   = get_dword(strData, ${OFFSETOF_FLASHER_VERSION_STRUCT_pucBuffer_Data} + 1)
	aAttr.ulBufferEnd   = get_dword(strData, ${OFFSETOF_FLASHER_VERSION_STRUCT_pucBuffer_End} + 1)
	aAttr.ulBufferLen   = aAttr.ulBufferEnd - aAttr.ulBufferAdr

	-- Show the information:
	print(string.format("parameter:          0x%08x", aAttr.ulParameter))
	print(string.format("device description: 0x%08x", aAttr.ulDeviceDesc))
	print(string.format("buffer start:       0x%08x", aAttr.ulBufferAdr))
	print(string.format("buffer end:         0x%08x", aAttr.ulBufferEnd))

	return aAttr
end


-- download binary to netX. Extracts and returns the header information.
-- Download a netx binary.
-- Returns the binary's attribute list.
function download_netx_binary(tPlugin, strData, fnCallbackProgress)
	local aAttr = get_flasher_binary_attributes(strData)
	print(string.format("downloading to 0x%08x", aAttr.ulLoadAddress))
	write_image(tPlugin, aAttr.ulLoadAddress, strData, fnCallbackProgress)
	-- tPlugin:write_image(aAttr.ulLoadAddress, strData, fnCallbackProgress, string.len(strData))
	
	return aAttr
end

-- Download flasher.
-- - Load the flasher binary according to the chip type the
--    plugin is connected to
-- - Extract header information from the flasher
--   (static information about code/exec/buffer addresses)
-- - Download the flasher to the specified address

-- tPlugin plugin object with an active connection
-- strPrefix path to flasher binaries
-- fnCallbackProgress is a function to call while downloading the flasher.
--   This parameter is optional. The default is to print a simple progress
--   message to stdout.

--   The function must accept 2 parameters:
--    1) the number of processed bytes
--    2) the total number of bytes
--   The function must return one boolean. A value of 'true' continues the
--   download operation, while a value of 'false' cancels the download.
--
-- Returns flasher attributes (parameter address, buffer address etc.)



function download(tPlugin, strPrefix, fnCallbackProgress)
	local iChiptype = tPlugin:GetChiptyp()
	local fDebug = false
	local strPath = get_flasher_binary_path(iChiptype, strPrefix, fDebug)
	local tFile, strMsg = io.open(strPath, 'rb')
	if tFile==nil then
		error(string.format('Failed to open file "%s" for reading: %s', strPath, strMsg))
	end
	local strFlasherBin = tFile:read('*a')
	tFile:close()

	local aAttr = get_flasher_binary_attributes(strFlasherBin)
	aAttr.strBinaryName = strFlasherBin
	
	print(string.format("downloading to 0x%08x", aAttr.ulLoadAddress))
	write_image(tPlugin, aAttr.ulLoadAddress, strFlasherBin, fnCallbackProgress)
	
	return aAttr
end


-- set the buffer area (when using SDRAM as a buffer, for instance)
function set_buffer_area(aAttr, ulBufferAdr, ulBufferLen)
	aAttr.ulBufferAdr   = ulBufferAdr
	aAttr.ulBufferEnd   = ulBufferAdr + ulBufferLen
	aAttr.ulBufferLen   = ulBufferLen
end



-----------------------------------------------------------------------------
--                    Calling the flasher
-----------------------------------------------------------------------------



-- download parameters to netX
local function set_parameterblock(tPlugin, ulAddress, aulParameters, fnCallbackProgress)
	local strBin = ""
	for i,v in ipairs(aulParameters) do
		-- print parameters as openOCD TCL instructions
		-- local strSetMem = "set *((unsigned long *) 0x%08x) = 0x%08x"
		-- printf(strSetMem, ulAddress+4*(i-1), v)
		
		strBin = strBin .. string.char( bit.band(v,0xff), bit.band(bit.rshift(v,8),0xff), bit.band(bit.rshift(v,16),0xff), bit.band(bit.rshift(v,24),0xff) )
	end
	write_image(tPlugin, ulAddress, strBin, fnCallbackProgress) 
end

-- Stores parameters in netX memory, calls the flasher and returns the result value
-- 0 = success, 1 = failure
function callFlasher(tPlugin, aAttr, aulParams, fnCallbackMessage, fnCallbackProgress)
	fnCallbackMessage = fnCallbackMessage or default_callback_message
	fnCallbackProgress = fnCallbackProgress or default_callback_progress
	
	-- set the parameters
	local aulParameter = {}
	aulParameter[1] = 0xffffffff                 -- placeholder for return vallue, will be 0 if ok
	aulParameter[2] = aAttr.ulParameter+0x0c     -- pointer to actual parameters
	aulParameter[3] = 0x00000000                 -- unused
	                                             -- extended parameters
	aulParameter[4] = FLASHER_INTERFACE_VERSION  -- set the parameter version
	for i=1, #aulParams do
		aulParameter[4+i] = aulParams[i]     -- actual parameters for the particular function
	end

	set_parameterblock(tPlugin, aAttr.ulParameter, aulParameter, fnCallbackProgress)
	
	-- call
	call(tPlugin, aAttr.ulExecAddress, aAttr.ulParameter, fnCallbackMessage) 
	
	-- get the return value (ok/failed)
	-- any further return values must be read by the calling function
	ulValue = tPlugin:read_data32(aAttr.ulParameter+0x00)
	print(string.format("call finished with result 0x%08x", ulValue))
	return ulValue
end


-----------------------------------------------------------------------------
--                  Detecting flash and getting device info
-----------------------------------------------------------------------------


-- get "static" information about the buses, depending on the chip type:
-- SRAM bus parflash, extension bus parflash, SPI serial flash, SQI serial flash
local function getInfoBlock(tPlugin, aAttr, ulBusIdx, ulUnitIdx, fnCallbackMessage, fnCallbackProgress)
	local aResult = nil
	
	local aulParameter = 
	{
		OPERATION_MODE_GetBoardInfo,           -- operation mode: get board info
		ulBusIdx,
		ulUnitIdx,
		aAttr.ulBufferAdr,
		aAttr.ulBufferLen
	}
	
	local ulValue = callFlasher(tPlugin, aAttr, aulParameter, fnCallbackMessage, fnCallbackProgress)

	if ulValue==0 then
		-- Get the size of the board description.
		local sizInfoMax = tPlugin:read_data32(aAttr.ulParameter+0x08)
		if sizInfoMax>0 then
			-- Get the board information.
			strInfo = read_image(tPlugin, aAttr.ulBufferAdr, sizInfoMax, fnCallbackProgress)

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


function getBoardInfo(tPlugin, aAttr, fnCallbackMessage, fnCallbackProgress)
	-- Get the bus infos.
	local aBoardInfo = getInfoBlock(tPlugin, aAttr, 0xffffffff, 0xffffffff, fnCallbackMessage, fnCallbackProgress)
	for iCnt,aBusInfo in ipairs(aBoardInfo) do
		-- Get the unit info.
		local aUnitInfo = getInfoBlock(tPlugin, aAttr, aBusInfo.iIdx, 0xffffffff, fnCallbackMessage, fnCallbackProgress)
		aBusInfo.aUnitInfo = aUnitInfo
	end

	return aBoardInfo
end



-- check if a device is available on tBus/ulUnit/ulChipSelect
function detect(tPlugin, aAttr, tBus, ulUnit, ulChipSelect, fnCallbackMessage, fnCallbackProgress, atParameter)
	local aulParameter
	atParameter = atParameter or {}
	
	
	if tBus==BUS_Spi then
		-- Set the initial SPI speed. The default is 1000kHz (1MHz).
		local ulInitialSpeed = atParameter.ulInitialSpeed
		ulInitialSpeed = ulInitialSpeed or 1000
		
		-- Set the maximum SPI speed. The default is 25000kHz (25MHz).
		local ulMaximumSpeed = atParameter.ulMaximumSpeed
		ulMaximumSpeed = ulMaximumSpeed or 25000
		
		-- Set the idle configuration. The default is all lines driving 1.
		local ulIdleCfg = atParameter.ulIdleCfg
		ulIdleCfg = ulIdleCfg or (MSK_SQI_CFG_IDLE_IO1_OE + MSK_SQI_CFG_IDLE_IO1_OUT
		                        + MSK_SQI_CFG_IDLE_IO2_OE + MSK_SQI_CFG_IDLE_IO2_OUT
		                        + MSK_SQI_CFG_IDLE_IO3_OE + MSK_SQI_CFG_IDLE_IO3_OUT)
		
		-- Set the SPI mode. The default is 3.
		local ulSpiMode = atParameter.ulSpiMode
		ulSpiMode = ulSpiMode or 3
		
		-- Set the MMIO configuration. The default is 0xffffffff (no MMIO pins).
		local ulMmioConfiguration = atParameter.ulMmioConfiguration
		ulMmioConfiguration = ulMmioConfiguration or 0xffffffff
		
		aulParameter =
		{
			OPERATION_MODE_Detect,                -- operation mode: detect
			tBus,                                 -- the bus
			ulUnit,                               -- unit
			ulChipSelect,                         -- chip select
			ulInitialSpeed,                       -- initial speed in kHz
			ulMaximumSpeed,                       -- maximum allowed speed in kHz
			ulIdleCfg,                            -- idle configuration
			ulSpiMode,                            -- mode
			ulMmioConfiguration,                  -- MMIO configuration
			aAttr.ulDeviceDesc                    -- data block for the device description
		}
	elseif tBus==BUS_Parflash then
		-- Set the allowed bus widths. This parameter is not used yet.
		local ulAllowedBusWidths = atParameter.ulAllowedBusWidths
		ulAllowedBusWidths = ulAllowedBusWidths or 0
		
		aulParameter =
		{
			OPERATION_MODE_Detect,                -- operation mode: detect
			tBus,                                 -- the bus
			ulUnit,                               -- unit
			ulChipSelect,                         -- chip select
			ulAllowedBusWidths,                   -- the allowed bus widths
			0,                                    -- reserved
			0,                                    -- reserved
			0,                                    -- reserved
			0,                                    -- reserved
			aAttr.ulDeviceDesc                    -- data block for the device description
		}
  elseif tBus==BUS_IFlash then
    aulParameter =
    {
      OPERATION_MODE_Detect,                -- operation mode: detect
      tBus,                                 -- the bus
      ulUnit,                               -- unit
      ulChipSelect,                         -- chip select
      0,                                    -- reserved
      0,                                    -- reserved
      0,                                    -- reserved
      0,                                    -- reserved
      0,                                    -- reserved
      aAttr.ulDeviceDesc                    -- data block for the device description
    }
	elseif tBus==BUS_SDIO then
		aulParameter = {
			OPERATION_MODE_Detect,                -- operation mode: detect
			tBus,                                 -- the bus
			0,                                    -- unit
			0,                                    -- chip select
			0,                                    -- reserved
			0,                                    -- reserved
			0,                                    -- reserved
			0,                                    -- reserved
			0,                                    -- reserved
			aAttr.ulDeviceDesc                    -- data block for the device description
		}

	else
		error("Unknown bus: " .. tostring(tBus))
	end
	
	local ulValue = callFlasher(tPlugin, aAttr, aulParameter, fnCallbackMessage, fnCallbackProgress)
	return ulValue == 0
end



-- read device descriptor after detect (debugging)
function readDeviceDescriptor(tPlugin, aAttr, fnCallbackProgress)
	-- check the device description
	local strDevDesc
	local ulSize
	local ulVersion
	
	local ulValue = tPlugin:read_data32(aAttr.ulDeviceDesc)
	if ulValue==0 then
		print("the device desription is not valid, nothing detected.")
	else

		-- get the size of the returned data
		ulSize = tPlugin:read_data32(aAttr.ulDeviceDesc+0x04)
		if ulSize<16 then
			print("the device description claims to be valid, but has a strange size.")
		else
			-- read the interface version of the returned data
			ulVersion = tPlugin:read_data32(aAttr.ulDeviceDesc+0x08)
			if ulVersion~=FLASHER_INTERFACE_VERSION then
				-- the version does not match the expected value
				print(string.format("the device description has a strange interface version."))
			else
				-- get the device description
				strDevDesc = read_image(tPlugin, aAttr.ulDeviceDesc, ulSize, fnCallbackProgress)
			end
		end
	end

	return strDevDesc
end


function getDeviceId(tPlugin, aAttr, fnCallbackProgress)
	-- Read the flash device descriptor.
	local strDeviceDescriptor = readDeviceDescriptor(tPlugin, aAttr, fnCallbackProgress)
	if strDeviceDescriptor==nil then
		error("Failed to read the flash device descriptor!")
	end
	
	strDeviceId = nil
	if tBus==BUS_Spi then
		-- Extract the flash ID.
		local iIdxStart = ${OFFSETOF_DEVICE_DESCRIPTION_STRUCT_uInfo}+${OFFSETOF_FLASHER_SPI_FLASH_STRUCT_tAttributes}+${OFFSETOF_SPIFLASH_ATTRIBUTES_Ttag_acName} + 1
		local iIdxEnd = iIdxStart
		local iIdxMax = iIdxStart + ${SPIFLASH_NAME_SIZE} + 1
		while iIdxEnd<iIdxMax and string.byte(strDeviceDescriptor, iIdxEnd)~=0 do
			iIdxEnd = iIdxEnd + 1
		end
		if iIdxEnd>iIdxStart then
			strDeviceId = string.sub(strDeviceDescriptor, iIdxStart, iIdxEnd-1)
		end
	else
		error("The device ID can not yet be retrieved for parallel flashes.")
	end
	
	return strDeviceId
end



---------------------------------------------------------------------------------
-- The following functions assume that detect has been run and there is a
-- valid device description in the memory.

-- ulStartAddr, ulEndAddr are offsets in the flash device.
-- ulDataAddress is the absolute address of the  buffer.
---------------------------------------------------------------------------------

-- Writes data which has been loaded into the buffer at ulDataAddress to ulStartAddr in the flash.
function flash(tPlugin, aAttr, ulStartAdr, ulDataByteSize, ulDataAddress, fnCallbackMessage, fnCallbackProgress)
	local aulParameter =
	{
		OPERATION_MODE_Flash,
		aAttr.ulDeviceDesc,
		ulStartAdr,
		ulDataByteSize,
		ulDataAddress
	}
	local ulValue = callFlasher(tPlugin, aAttr, aulParameter, fnCallbackMessage, fnCallbackProgress)
	return ulValue == 0
end

-- Reads data from flash to RAM
function read(tPlugin, aAttr, ulFlashStartOffset, ulFlashEndOffset, ulBufferAddress, fnCallbackMessage, fnCallbackProgress)
	local aulParameter =
	{
		OPERATION_MODE_Read,
		aAttr.ulDeviceDesc,
		ulFlashStartOffset,
		ulFlashEndOffset,
		ulBufferAddress
	}
	local ulValue = callFlasher(tPlugin, aAttr, aulParameter, fnCallbackMessage, fnCallbackProgress)
	return ulValue == 0
end


-- Compares data in flash to RAM
function verify(tPlugin, aAttr, ulFlashStartOffset, ulFlashEndOffset, ulBufferAddress, fnCallbackMessage, fnCallbackProgress)
	local fEqual = false
	local aulParameter =
	{
		OPERATION_MODE_Verify,
		aAttr.ulDeviceDesc,
		ulFlashStartOffset,
		ulFlashEndOffset,
		ulBufferAddress
	}
	local ulValue = callFlasher(tPlugin, aAttr, aulParameter, fnCallbackMessage, fnCallbackProgress)
	
	if ulValue==0 then
		ulValue = tPlugin:read_data32(aAttr.ulParameter+0x08)
		fEqual = (ulValue==0)
	end
	
	return fEqual
end


-- Computes the SHA1 hash over data in the flash.
function hash(tPlugin, aAttr, ulFlashStartOffset, ulFlashEndOffset, fnCallbackMessage, fnCallbackProgress)
	local strHashBin = nil
	local aulParameter =
	{
		OPERATION_MODE_Checksum,
		aAttr.ulDeviceDesc,
		ulFlashStartOffset,
		ulFlashEndOffset,
	}
	local ulValue = callFlasher(tPlugin, aAttr, aulParameter, fnCallbackMessage, fnCallbackProgress)
	
	if ulValue==0 then
		strHashBin = read_image(tPlugin, aAttr.ulParameter+0x20, 20, fnCallbackProgress)
	end
	
	return ulValue == 0, strHashBin
end



-- Determines the smallest interval of sectors which has to be
-- erased in order to erase ulStartAdr to ulEndAdr-1.
-- returns nil if the call fails.
function getEraseArea(tPlugin, aAttr, ulStartAdr, ulEndAdr, fnCallbackMessage, fnCallbackProgress)
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
	
	ulValue = callFlasher(tPlugin, aAttr, aulParameter, fnCallbackMessage, fnCallbackProgress)
	if ulValue==0 then
		ulEraseStart = tPlugin:read_data32(aAttr.ulParameter+0x18)
		ulEraseEnd = tPlugin:read_data32(aAttr.ulParameter+0x1c)
	end

	return ulEraseStart, ulEraseEnd
end



-- get the flash size via getEraseArea
function getFlashSize(tPlugin, aAttr, fnCallbackMessage, fnCallbackProgress)
	local ulEraseStart, ulEraseEnd = getEraseArea(tPlugin, aAttr, 0, 0xffffffff, fnCallbackMessage, fnCallbackProgress)
	return ulEraseEnd
end




-- Checks if the area from ulEraseStart to ulEraseEnd is 0xff.
-- TODO: return nil if the call fails (e.g. because ulEraseEnd is too large)
function isErased(tPlugin, aAttr, ulEraseStart, ulEraseEnd, fnCallbackMessage, fnCallbackProgress)
	local fIsErased = false

	local aulParameter =
	{
		OPERATION_MODE_IsErased,               -- operation mode: isErased
		aAttr.ulDeviceDesc,                    -- data block for the device description
		ulEraseStart,
		ulEraseEnd
	}
	
	local ulValue = callFlasher(tPlugin, aAttr, aulParameter, fnCallbackMessage, fnCallbackProgress)
	if ulValue==0 then
		ulValue = tPlugin:read_data32(aAttr.ulParameter+0x08)
		fIsErased = (ulValue==0xff)
	end

	return fIsErased
end



-- Erase an area in the flash.
-- The start and end addresses must be aligned to sector boundaries as
-- set by getEraseArea.
function erase(tPlugin, aAttr, ulEraseStart, ulEraseEnd, fnCallbackMessage, fnCallbackProgress)
	local aulParameter =
	{
		OPERATION_MODE_Erase,                          -- operation mode: erase
		aAttr.ulDeviceDesc,                            -- data block for the device description
		ulEraseStart,
		ulEraseEnd
	}
	local ulValue = callFlasher(tPlugin, aAttr, aulParameter, fnCallbackMessage, fnCallbackProgress)
	return ulValue == 0
end



-- Easy erase.
-- A combination of GetEraseArea, IsErased and Erase.
-- NOTE: This is an equivalent of the eraseArea function (see below) for
--       environments without scripting capabilities. This function exists
--       just for the sake of a complete API.
function easy_erase(tPlugin, aAttr, ulEraseStart, ulEraseEnd, fnCallbackMessage, fnCallbackProgress)
	local aulParameter =
	{
		OPERATION_MODE_EasyErase,                      -- operation mode: easy erase
		aAttr.ulDeviceDesc,                            -- data block for the device description
		ulEraseStart,
		ulEraseEnd
	}
	local ulValue = callFlasher(tPlugin, aAttr, aulParameter, fnCallbackMessage, fnCallbackProgress)
	return ulValue == 0
end




-----------------------------------------------------------------------------
-- erase an area:
-- check if the area is already erased and erase only if it isn't empty.
-- ulSize = 0xffffffff to erase from ulDeviceOffset to end of chip
--
-- OK:
-- The area is empty, no erase necessary.
-- Area erased
--
-- Error messages:
-- getEraseArea failed!
-- Failed to check if the area is erased!
-- getEraseArea failed!
-- Failed to erase the area! (Failure during erase)
-- Failed to erase the area! (isErased check failed)


function eraseArea(tPlugin, aAttr, ulDeviceOffset, ulSize, fnCallbackMessage, fnCallbackProgress)
	local fIsErased
	local ulEndOffset
	local ulEraseStart,ulEraseEnd
	
	-- If length = 0xffffffff we get the erase area now in order to detect the flash size.
	if ulSize == 0xffffffff then
		ulEndOffset = ulSize
		ulEraseStart,ulEraseEnd = getEraseArea(tPlugin, aAttr, ulDeviceOffset, ulEndOffset, fnCallbackMessage, fnCallbackProgress)
		if not (ulEraseStart and ulEraseEnd) then
			return false, "getEraseArea failed!"
		end
		
		ulEndOffset = ulEraseEnd
	else
		ulEndOffset = ulDeviceOffset + ulSize
	end
	

	print(string.format("Area:  [0x%08x, 0x%08x[", ulDeviceOffset, ulEndOffset))
	print("Checking if the area is already empty")
	fIsErased = isErased(tPlugin, aAttr, ulDeviceOffset, ulEndOffset, fnCallbackMessage, fnCallbackProgress)

	if fIsErased==nil then
		return false, "Failed to check if the area is erased!"
	elseif fIsErased==true then
		return true, "The area is empty, no erase necessary."
	else
		-- Get the erase area unless we have already gotten it.
		if not (ulEraseStart and ulEraseEnd) then
			ulEraseStart,ulEraseEnd = getEraseArea(tPlugin, aAttr, ulDeviceOffset, ulEndOffset, fnCallbackMessage, fnCallbackProgress)
			if not (ulEraseStart and ulEraseEnd) then
				return false, "getEraseArea failed!"
			end
		end
		
		print("Erasing flash")
		print(string.format("Erase: [0x%08x, 0x%08x[", ulEraseStart, ulEraseEnd))

		fIsErased = erase(tPlugin, aAttr, ulEraseStart, ulEraseEnd, fnCallbackMessage, fnCallbackProgress)
		if fIsErased~=true then
			return false, "Failed to erase the area! (Failure during erase)"
		else
			print("Checking if the area has been erased")
			fIsErased = isErased(tPlugin, aAttr,  ulDeviceOffset, ulEndOffset, fnCallbackMessage, fnCallbackProgress)
			if fIsErased~=true then
				return false, "Failed to erase the area! (isErased check failed)"
			end
		end
	end
	return true, "Area erased"
end




-----------------------------------------------------------------------------
-- flash data in chunks

-- Error messages:
-- Failed to flash data!

-- Ok:
-- Image flashed.

function flashArea(tPlugin, aAttr, ulDeviceOffset, strData, fnCallbackMessage, fnCallbackProgress)
	local fOk
	local ulDataByteSize = strData:len()
	local ulDataOffset = 0
	local ulBufferAdr = aAttr.ulBufferAdr
	local ulBufferLen = aAttr.ulBufferLen
	local ulChunkSize
	local strChunk
	
	while ulDataOffset<ulDataByteSize do
		-- Extract the next chunk.
		strChunk = strData:sub(ulDataOffset+1, ulDataOffset+ulBufferLen)
		ulChunkSize = strChunk:len()

		-- Download the chunk to the buffer.
		write_image(tPlugin, ulBufferAdr, strChunk, fnCallbackProgress)

		-- Flash the chunk.
		print(string.format("flashing offset 0x%08x-0x%08x.", ulDeviceOffset, ulDeviceOffset+ulChunkSize))
		fOk = flasher.flash(tPlugin, aAttr, ulDeviceOffset, ulChunkSize, ulBufferAdr, fnCallbackMessage, fnCallbackProgress)
		if not fOk then
			return false, "Failed to flash data!"
		end

		-- Increase pointers.
		ulDataOffset = ulDataOffset + ulChunkSize
		ulDeviceOffset = ulDeviceOffset + ulChunkSize
	end

	return true, "Image flashed."
end



-----------------------------------------------------------------------------
-- verify data in chunks

-- Ok:
-- The data in the flash is equal to the input file.

-- Error messages:
-- Differences were found.

function verifyArea(tPlugin, aAttr, ulDeviceOffset, strData, fnCallbackMessage, fnCallbackProgress)
	local fOk
	local ulDataByteSize = strData:len()
	local ulDataOffset = 0
	local ulBufferAdr = aAttr.ulBufferAdr
	local ulBufferLen = aAttr.ulBufferLen
	local ulChunkSize
	local strChunk
	
	while ulDataOffset<ulDataByteSize do
		-- Extract the next chunk.
		strChunk = strData:sub(ulDataOffset+1, ulDataOffset+ulBufferLen)
		ulChunkSize = strChunk:len()

		-- Download the chunk to the buffer.
		write_image(tPlugin, ulBufferAdr, strChunk, fnCallbackProgress)

		-- Verify the chunk.
		print(string.format("verifying offset 0x%08x-0x%08x.", ulDeviceOffset, ulDeviceOffset+ulChunkSize))
		fOk = flasher.verify(tPlugin, aAttr, ulDeviceOffset, ulDeviceOffset + ulChunkSize, ulBufferAdr, fnCallbackMessage, fnCallbackProgress)
		if not fOk then
			return false, "Differences were found."
		end

		-- Increase pointers.
		ulDataOffset = ulDataOffset + ulChunkSize
		ulDeviceOffset = ulDeviceOffset + ulChunkSize
	end
	
	return true, "The data in the flash is equal to the input file."
end






-----------------------------------------------------------------------------
-- Read data in chunks
-- size = 0xffffffff to read from ulDeviceOffset to end of device

-- Ok:
-- Read successful.

-- Error messages:
-- Could not determine the flash size!
-- Error while reading from flash!
-- Error while reading from RAM buffer!

function readArea(tPlugin, aAttr, ulDeviceOffset, ulDataByteSize, fnCallbackMessage, fnCallbackProgress)
	local fOk
	local ulSize = ulDataByteSize
	local ulBufferAddr = aAttr.ulBufferAdr
	local ulBufferLen = aAttr.ulBufferLen
	local strChunk
	local ulChunkSize
	local astrChunks = {}
	
	if ulSize == 0xffffffff then 
		ulSize = getFlashSize(tPlugin, aAttr, fnCallbackMessage, fnCallbackProgress)
		if ulSize then
			print(string.format("Flash size: 0x%08x bytes", ulSize))
			ulSize = ulSize - ulDeviceOffset
		else
			return nil, "Could not determine the flash size!"
		end
	end
	
	while ulSize>0 do
		-- determine chunk size
		ulChunkSize = math.min(ulSize, ulBufferLen)
		
		-- Read chunk into buffer
		print(string.format("reading flash offset 0x%08x-0x%08x.", ulDeviceOffset, ulDeviceOffset+ulChunkSize))
		fOk = read(tPlugin, aAttr, ulDeviceOffset, ulDeviceOffset + ulChunkSize, ulBufferAddr, fnCallbackMessage, fnCallbackProgress)
		if not fOk then
			return nil, "Error while reading from flash!"
		end
		
		-- Read the buffer 
		strChunk = read_image(tPlugin, ulBufferAddr, ulChunkSize, fnCallbackProgress)
		if not strChunk then
			return nil, "Error while reading from RAM buffer!"
		end
	
		table.insert(astrChunks, strChunk)
		
		ulDeviceOffset = ulDeviceOffset + ulChunkSize
		ulSize = ulSize - ulChunkSize
	end

	local strBin = table.concat(astrChunks)
	local strMsg = string.format("%d bytes read.", ulDataByteSize)
	return strBin, strMsg
end




--------------------------------------------------------------------------
-- Calculate the SHA1 hash of an area of an area in the flash.
-- size = 0xffffffff to read from ulDeviceOffset to end of device
--
-- Returns the hash as a binary string or nil and an error message.
-- 
-- Ok:
-- "Checksum calculated."
--
-- Error messages:
-- Could not determine the flash size!
-- "Error while calculating SHA1 hash"
--
--------------------------------------------------------------------------

function hashArea(tPlugin, aAttr, ulDeviceOffset, ulDataByteSize, fnCallbackMessage, fnCallbackProgress)
	local fOk
	local strFlashHashBin
	local ulDeviceEndOffset
	
	if ulDataByteSize == 0xffffffff then 
		local ulDeviceSize = getFlashSize(tPlugin, aAttr, fnCallbackMessage, fnCallbackProgress)
		if ulDeviceSize then
			print(string.format("Flash size: 0x%08x bytes", ulDeviceSize))
			ulDeviceEndOffset = ulDeviceSize
		else
			return nil, "Could not determine the flash size!"
		end
	else
		ulDeviceEndOffset = ulDeviceOffset + ulDataByteSize
	end
	
	fOk, strFlashHashBin = hash(tPlugin, aAttr, ulDeviceOffset, ulDeviceEndOffset, fnCallbackMessage, fnCallbackProgress)

	if fOk~=true then
		return nil, "Error while calculating SHA1 hash."
	else
		return strFlashHashBin, "Checksum calculated."
	end
end


--------------------------------------------------------------------------
-- simple_flasher_string
-- This is a simple routine to flash the data in a string.
-- Load file from strDataFileName and write it to offset 0
-- Raise an error in case of any errors
--
--   tPlugin
--   strDataFileName
--
--   tBus
--   ulUnit
--   ulChipSelect
--
--   strFlasherPrefix
--   fnCallbackProgress
--   fnCallbackMessage
--------------------------------------------------------------------------

function simple_flasher_string(tPlugin, strData, tBus, ulUnit, ulChipSelect, strFlasherPrefix, fnCallbackProgress, fnCallbackMessage)
	strFlasherPrefix = strFlasherPrefix or ""
	
	local fOk
	local strMsg
	local ulDeviceOffset = 0
	
	-- Download the binary.
	local aAttr = download(tPlugin, strFlasherPrefix, fnCallbackProgress)
	
	-- Detect the device.
	fOk = detect(tPlugin, aAttr, tBus, ulUnit, ulChipSelect, fnCallbackMessage, fnCallbackProgress)
	if fOk~=true then
		error("Failed to detect the device!")
	end
	
	fOk, strMsg = eraseArea(tPlugin, aAttr, ulDeviceOffset, strData:len(), fnCallbackMessage, fnCallbackProgress)
	print(strMsg)
	assert(fOk, strMsg or "Error while erasing area")
	
	fOk, strMsg = flashArea(tPlugin, aAttr, ulDeviceOffset, strData, fnCallbackMessage, fnCallbackProgress)
	print(strMsg)
	assert(fOk, strMsg or "Error while programming area")
	
	print("*** Flashing ok ***")
end



--------------------------------------------------------------------------
-- simple_flasher
-- This is a simple routine to flash one file.
-- Load file from strDataFileName and write it to offset 0
-- Raise an error in case of any errors
--
--   tPlugin
--   strDataFileName
--
--   tBus
--   ulUnit
--   ulChipSelect
--
--   strFlasherPrefix
--   fnCallbackProgress
--   fnCallbackMessage
--------------------------------------------------------------------------

function simple_flasher(tPlugin, strDataFileName, tBus, ulUnit, ulChipSelect, strFlasherPrefix, fnCallbackProgress, fnCallbackMessage)
	-- Load the data.
	local tFile, strMsg = io.open(strDataFileName, 'rb')
	if tFile==nil then
		error(string.format('Failed to open file "%s" for reading: %s', strPath, strMsg))
	end
	local strData = tFile:read('*a')
	tFile:close()

	simple_flasher_string(tPlugin, strData, tBus, ulUnit, ulChipSelect, strFlasherPrefix, fnCallbackProgress, fnCallbackMessage)
end



--------------------------------------------------------------------------
-- SPI debug interface
--------------------------------------------------------------------------

function sdi_init(tPlugin, aAttr, ulUnit, ulChipSelect, ulSpeed_kHz, fnCallbackProgress, fnCallbackMessage)
	local ulValue
	local aulParameter
	local ulIdleCfg

	
	ulIdleCfg = MSK_SQI_CFG_IDLE_IO1_OE + MSK_SQI_CFG_IDLE_IO1_OUT
	          + MSK_SQI_CFG_IDLE_IO2_OE + MSK_SQI_CFG_IDLE_IO2_OUT
	          + MSK_SQI_CFG_IDLE_IO3_OE + MSK_SQI_CFG_IDLE_IO3_OUT
	
	aulParameter =
	{
		OPERATION_MODE_SpiMacroPlayer,        -- operation mode: SPI macro player
		SMC_INITIALIZE,                       -- Command: initialize
		aAttr.ulDeviceDesc,                   -- free space for the SPI configuration
		ulUnit,                               -- the SPI unit
		ulChipSelect,                         -- the SPI chip select
		ulSpeed_kHz,                          -- the speed in kHz (1000 -> 1MHz)
		ulSpeed_kHz,                          -- the maximum kHz
		ulIdleCfg,                            -- idle configuration
		3,                                    -- mode
		0xffffffff                            -- MMIO configuration
	}
	
	ulValue = callFlasher(tPlugin, aAttr, aulParameter, fnCallbackMessage, fnCallbackProgress)
	return ulValue == 0
end



function sdi_chip_select(tPlugin, aAttr, uiActive, fnCallbackProgress, fnCallbackMessage)
	local ulValue
	local aulParameter

	
	if tonumber(uiActive)==0 then
		ulValue = 0
	else
		ulValue = 1
	end
	
	aulParameter =
	{
		OPERATION_MODE_SpiMacroPlayer,        -- operation mode: SPI macro player
		SMC_CHIP_SELECT,                      -- Command: chip select
		aAttr.ulDeviceDesc,                   -- the SPI configuration
		ulValue,                              -- chip select
	}
	
	ulValue = callFlasher(tPlugin, aAttr, aulParameter, fnCallbackMessage, fnCallbackProgress)
	return ulValue == 0
end



function sdi_exchange_data(tPlugin, aAttr, strData, fnCallbackProgress, fnCallbackMessage)
	local ulValue
	local aulParameter
	local sizData
	local ulTxBuffer
	local ulRxBuffer
	local strRxData


	sizData = string.len(strData)

	ulTxBuffer = aAttr.ulBufferAdr
	ulRxBuffer = aAttr.ulBufferAdr + sizData

	-- Download the data.
	write_image(tPlugin, ulTxBuffer, strData, fnCallbackProgress)
	
	aulParameter =
	{
		OPERATION_MODE_SpiMacroPlayer,        -- operation mode: SPI macro player
		SMC_EXCHANGE_DATA,                    -- Command: exchange data
		aAttr.ulDeviceDesc,                   -- the SPI configuration
		ulTxBuffer,
		ulRxBuffer,
		sizData
	}
	
	ulValue = callFlasher(tPlugin, aAttr, aulParameter, fnCallbackMessage, fnCallbackProgress)
	if ulValue==0 then
		strRxData = read_image(tPlugin, ulRxBuffer, sizData, fnCallbackProgress)
	end
	
	return strRxData
end


function sdi_send_data(tPlugin, aAttr, strData, fnCallbackProgress, fnCallbackMessage)
	local ulValue
	local aulParameter
	local sizData
	local ulTxBuffer


	sizData = string.len(strData)

	ulTxBuffer = aAttr.ulBufferAdr

	-- Download the data.
	write_image(tPlugin, ulTxBuffer, strData, fnCallbackProgress)
	
	aulParameter =
	{
		OPERATION_MODE_SpiMacroPlayer,        -- operation mode: SPI macro player
		SMC_SEND_DATA,                        -- Command: send data
		aAttr.ulDeviceDesc,                   -- the SPI configuration
		ulTxBuffer,
		sizData
	}
	
	ulValue = callFlasher(tPlugin, aAttr, aulParameter, fnCallbackMessage, fnCallbackProgress)
	
	return ulValue == 0
end


function sdi_receive_data(tPlugin, aAttr, sizData, fnCallbackProgress, fnCallbackMessage)
	local ulValue
	local aulParameter
	local ulRxBuffer
	local strRxData


	ulRxBuffer = aAttr.ulBufferAdr

	aulParameter =
	{
		OPERATION_MODE_SpiMacroPlayer,        -- operation mode: SPI macro player
		SMC_RECEIVE_DATA,                     -- Command: receive data
		aAttr.ulDeviceDesc,                   -- the SPI configuration
		ulRxBuffer,
		sizData
	}
	
	ulValue = callFlasher(tPlugin, aAttr, aulParameter, fnCallbackMessage, fnCallbackProgress)
	if ulValue==0 then
		strRxData = read_image(tPlugin, ulRxBuffer, sizData, fnCallbackProgress)
	end
	
	return strRxData
end


function sdi_idle_bytes(tPlugin, aAttr, sizIdleBytes, fnCallbackProgress, fnCallbackMessage)
	local ulValue
	local aulParameter


	aulParameter =
	{
		OPERATION_MODE_SpiMacroPlayer,        -- operation mode: SPI macro player
		SMC_SEND_IDLE_BYTES,                  -- Command: send idle bytes
		aAttr.ulDeviceDesc,                   -- the SPI configuration
		sizIdleBytes
	}
	
	ulValue = callFlasher(tPlugin, aAttr, aulParameter, fnCallbackMessage, fnCallbackProgress)
	
	return ulValue == 0
end

