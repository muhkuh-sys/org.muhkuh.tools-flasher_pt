----------------------
-- The FlaSHer application. A helpful tool to write, verify, read and erase data in flash.
-- @author Christoph Thelen 
-- @copyright
-- @license
-- @release
-- @module flasher



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


local class = require "pl.class"
---  Flasher class. 
-- @type Flasher
local Flasher = class()

--- Initialize an instance of Flasher upon creation.
function Flasher:_init(tLog)

  self.tLog = tLog

  self.bit = require "bit"
  self.romloader = require "romloader"


--                           Definitions

  self.BUS_Parflash    = ${BUS_ParFlash}             -- parallel flash
  self.BUS_Spi         = ${BUS_SPI}             -- serial flash on spi bus
  self.BUS_IFlash      = ${BUS_IFlash}             -- internal flash
  self.BUS_SDIO        = ${BUS_SDIO}             -- SD/EMMC


  self.OPERATION_MODE_Flash             = ${OPERATION_MODE_Flash}
  self.OPERATION_MODE_Erase             = ${OPERATION_MODE_Erase}
  self.OPERATION_MODE_Read              = ${OPERATION_MODE_Read}
  self.OPERATION_MODE_Verify            = ${OPERATION_MODE_Verify}
  self.OPERATION_MODE_Checksum          = ${OPERATION_MODE_Checksum}     -- Build a checksum over the contents of a specified area of a device.
  self.OPERATION_MODE_Detect            = ${OPERATION_MODE_Detect}     -- Detect a device.
  self.OPERATION_MODE_IsErased          = ${OPERATION_MODE_IsErased}     -- Check if the specified area of a device is erased.
  self.OPERATION_MODE_GetEraseArea      = ${OPERATION_MODE_GetEraseArea}     -- Expand an area to the erase block borders.
  self.OPERATION_MODE_GetBoardInfo      = ${OPERATION_MODE_GetBoardInfo}     -- Get bus and unit information.
  self.OPERATION_MODE_EasyErase         = ${OPERATION_MODE_EasyErase}     -- A combination of GetEraseArea, IsErased and Erase.
  self.OPERATION_MODE_SpiMacroPlayer    = ${OPERATION_MODE_SpiMacroPlayer}    -- A debug mode to send commands to a SPI flash.


  self.MSK_SQI_CFG_IDLE_IO1_OE          = ${MSK_SQI_CFG_IDLE_IO1_OE}
  self.SRT_SQI_CFG_IDLE_IO1_OE          = ${SRT_SQI_CFG_IDLE_IO1_OE}
  self.MSK_SQI_CFG_IDLE_IO1_OUT         = ${MSK_SQI_CFG_IDLE_IO1_OUT}
  self.SRT_SQI_CFG_IDLE_IO1_OUT         = ${SRT_SQI_CFG_IDLE_IO1_OUT}
  self.MSK_SQI_CFG_IDLE_IO2_OE          = ${MSK_SQI_CFG_IDLE_IO2_OE}
  self.SRT_SQI_CFG_IDLE_IO2_OE          = ${SRT_SQI_CFG_IDLE_IO2_OE}
  self.MSK_SQI_CFG_IDLE_IO2_OUT         = ${MSK_SQI_CFG_IDLE_IO2_OUT}
  self.SRT_SQI_CFG_IDLE_IO2_OUT         = ${SRT_SQI_CFG_IDLE_IO2_OUT}
  self.MSK_SQI_CFG_IDLE_IO3_OE          = ${MSK_SQI_CFG_IDLE_IO3_OE}
  self.SRT_SQI_CFG_IDLE_IO3_OE          = ${SRT_SQI_CFG_IDLE_IO3_OE}
  self.MSK_SQI_CFG_IDLE_IO3_OUT         = ${MSK_SQI_CFG_IDLE_IO3_OUT}
  self.SRT_SQI_CFG_IDLE_IO3_OUT         = ${SRT_SQI_CFG_IDLE_IO3_OUT}


  self.SMC_INITIALIZE                   = ${SMC_INITIALIZE}
  self.SMC_CHIP_SELECT                  = ${SMC_CHIP_SELECT}
  self.SMC_EXCHANGE_DATA                = ${SMC_EXCHANGE_DATA}
  self.SMC_SEND_DATA                    = ${SMC_SEND_DATA}
  self.SMC_RECEIVE_DATA                 = ${SMC_RECEIVE_DATA}
  self.SMC_SEND_IDLE_BYTES              = ${SMC_SEND_IDLE_BYTES}


  self.FLASHER_INTERFACE_VERSION        = ${FLASHER_INTERFACE_VERSION}



  -- callback/progress functions,  
  -- read/write image, call
  local this = self
  self.fnProgressDefault = function(ulCnt, ulMax)
    return this:default_callback_progress(ulCnt, ulMax)
  end
  self.fnMessageDefault = function(a, b)
    return this:default_callback_message(a, b)
  end

  self.ulProgressLastTime    = 0
  self.fProgressLastPercent  = 0
  self.ulProgressLastMax     = nil
  self.PROGRESS_STEP_PERCENT = 10
end

--- Default callback progress function. The default is to print a simple progress message to stdout.
--   The function must accept 2 parameters:
--    1) the number of processed bytes
--    2) the total number of bytes
-- @param ulCnt number of processed bytes
-- @param ulMax total number of bytes
-- @return The function must return one boolean. A value of 'true' continues the download operation, while a value of 'false' cancels the download.
function Flasher:default_callback_progress(ulCnt, ulMax)
  local fPercent = math.floor(ulCnt * 100 / ulMax)
  local ulTime = os.time()
  if self.ulProgressLastMax~=ulMax or ulCnt==0 or ulCnt==ulMax or self.fProgressLastPercent-fPercent>self.PROGRESS_STEP_PERCENT or ulTime-self.ulProgressLastTime>1 then
    self.fProgressLastPercent = fPercent
    self.ulProgressLastMax = ulMax
    self.ulProgressLastTime = ulTime
    self.tLog.debug("%d%% (%d/%d)", fPercent, ulCnt, ulMax)
  end
  return true
end


--- Default callback message function.
-- @param a
-- @param b 
function Flasher:default_callback_message(a,b)
  if type(a)=="string" and string.len(a)>0 then
    local strCnt, strMax = string.match(a, '%% ([%x%X]+)/([%x%X]+)')
    if strCnt and strMax then
      local ulCnt = tonumber(strCnt, 16)
      local ulMax = tonumber(strMax, 16)
      if ulCnt and ulMax then
        return self:default_callback_progress(ulCnt, ulMax)
      end
    else
      if string.sub(a, -1)=='\n' then
        a = string.sub(a, 1, -2)
      end
      self.tLog.debug('[netx] %s', a)
    end
  end
  return true
end

--- Write an image.
-- @param tPlugin plugin object with an active connection
-- @param ulAddress 
-- @param strData 
-- @param fnCallbackProgress 
-- @return 
function Flasher:write_image(tPlugin, ulAddress, strData, fnCallbackProgress)
  --  local this = self
  fnCallbackProgress = fnCallbackProgress or self.fnProgressDefault
  tPlugin:write_image(ulAddress, strData, fnCallbackProgress, strData:len())
  --return tPlugin:write_image(ulAddress, strData, fnCallbackProgress, strData:len())
end

--- Read an image.
-- @param tPlugin plugin object with an active connection
-- @param ulAddress 
-- @param ulSize 
-- @param fnCallbackProgress 
-- @return 
function Flasher:read_image(tPlugin, ulAddress, ulSize, fnCallbackProgress)
  --  local this = self
  fnCallbackProgress = fnCallbackProgress or self.fnProgressDefault
  return tPlugin:read_image(ulAddress, ulSize, fnCallbackProgress, ulSize)
end

--- Call function.
-- @param tPlugin plugin object with an active connection
-- @param ulExecAddress 
-- @param ulParameterAddress
-- @param fnCallbackMessage 
-- @return 
function Flasher:call(tPlugin, ulExecAddress, ulParameterAddress, fnCallbackMessage)
  --  local this = self
  fnCallbackMessage = fnCallbackMessage or self.fnMessageDefault
  tPlugin:call(ulExecAddress, ulParameterAddress, fnCallbackMessage, 2)
  --  return tPlugin:call(ulExecAddress, ulParameterAddress, fnCallbackMessage, 2)
end


--                    Downloading the flasher

--- Description.
-- Prefix must include a trailing backslash if it's a directory.
-- @param iChiptype
-- @param strPathPrefix
-- @param fDebug
-- @return 
function Flasher:get_flasher_binary_path(iChiptype, strPathPrefix, fDebug)
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

--- Description.
-- @param strData
-- @param ulOffset
function Flasher:get_dword(strData, ulOffset)
  return strData:byte(ulOffset) + strData:byte(ulOffset+1)*0x00000100 + strData:byte(ulOffset+2)*0x00010000 + strData:byte(ulOffset+3)*0x01000000
end

--- Extract header information from the flasher binary.
-- Information about code/exec/buffer addresses.
-- @param strData
-- @return aAttr: Returns the binary's attribute list.
function Flasher:get_flasher_binary_attributes(strData)
  local aAttr = {}
  local tLog = self.tLog

  -- Get the load and exec address from the binary.
  aAttr.ulLoadAddress = self:get_dword(strData, ${OFFSETOF_FLASHER_VERSION_STRUCT_pulLoadAddress} + 1)
  aAttr.ulExecAddress = self:get_dword(strData, ${OFFSETOF_FLASHER_VERSION_STRUCT_pfnExecutionAddress} + 1)
  aAttr.ulParameter   = self:get_dword(strData, ${OFFSETOF_FLASHER_VERSION_STRUCT_pucBuffer_Parameter} + 1)
  aAttr.ulDeviceDesc  = self:get_dword(strData, ${OFFSETOF_FLASHER_VERSION_STRUCT_pucBuffer_DeviceDescription} + 1)
  aAttr.ulBufferAdr   = self:get_dword(strData, ${OFFSETOF_FLASHER_VERSION_STRUCT_pucBuffer_Data} + 1)
  aAttr.ulBufferEnd   = self:get_dword(strData, ${OFFSETOF_FLASHER_VERSION_STRUCT_pucBuffer_End} + 1)
  aAttr.ulBufferLen   = aAttr.ulBufferEnd - aAttr.ulBufferAdr

  -- Show the information:
  tLog.debug("parameter:          0x%08x", aAttr.ulParameter)
  tLog.debug("device description: 0x%08x", aAttr.ulDeviceDesc)
  tLog.debug("buffer start:       0x%08x", aAttr.ulBufferAdr)
  tLog.debug("buffer end:         0x%08x", aAttr.ulBufferEnd)
  tLog.debug("buffer size:        0x%08x", aAttr.ulBufferLen)

  return aAttr
end

--- Download binary to netX. Extracts and returns the header information.
-- Download a netx binary.
-- @param tPlugin plugin object with an active connection
-- @param strData
-- @param fnCallbackProgress
-- @return aAttr: Returns the binary's attribute list.
function Flasher:download_netx_binary(tPlugin, strData, fnCallbackProgress)
  local aAttr = self:get_flasher_binary_attributes(strData)
  local tLog = self.tLog
  tLog.debug("downloading to 0x%08x", aAttr.ulLoadAddress)
  self:write_image(tPlugin, aAttr.ulLoadAddress, strData, fnCallbackProgress)
  -- tPlugin:write_image(aAttr.ulLoadAddress, strData, fnCallbackProgress, string.len(strData))

  return aAttr
end

--- Download flasher.
--
-- - Load the flasher binary according to the chip type the plugin is connected to. 
--
-- - Extract header information from the flasher (static information about code/exec/buffer addresses)
--
-- - Download the flasher to the specified address.
--
-- @param tPlugin plugin object with an active connection
-- @param strPrefix path to flasher binaries
-- @param fnCallbackProgress is a function to call while downloading the flasher.
--   This parameter is optional. The default is to print a simple progress
--   message to stdout.
--   The function must accept 2 parameters:
--    1) the number of processed bytes
--    2) the total number of bytes
--   The function must return one boolean. A value of 'true' continues the
--   download operation, while a value of 'false' cancels the download.
-- @return aAttr: Returns flasher attributes (parameter address, buffer address etc.)
function Flasher:download(tPlugin, strPrefix, fnCallbackProgress)
  local iChiptype = tPlugin:GetChiptyp()
  local fDebug = false
  local strPath = self:get_flasher_binary_path(iChiptype, strPrefix, fDebug)
  local tFile, strMsg = io.open(strPath, 'rb')
  local tLog = self.tLog
  if tFile==nil then
    error(string.format('Failed to open file "%s" for reading: %s', strPath, strMsg))
  end
  local strFlasherBin = tFile:read('*a')
  tFile:close()

  local aAttr = self:get_flasher_binary_attributes(strFlasherBin)
  aAttr.strBinaryName = strFlasherBin

  tLog.debug("downloading to 0x%08x", aAttr.ulLoadAddress)
  self:write_image(tPlugin, aAttr.ulLoadAddress, strFlasherBin, fnCallbackProgress)

  return aAttr
end

--- Set the buffer area (when using SDRAM as a buffer, for instance).
-- @param aAttr
-- @param ulBufferAdr
-- @param ulBufferLen
function Flasher:set_buffer_area(aAttr, ulBufferAdr, ulBufferLen)
  aAttr.ulBufferAdr   = ulBufferAdr
  aAttr.ulBufferEnd   = ulBufferAdr + ulBufferLen
  aAttr.ulBufferLen   = ulBufferLen
end


--                    Calling the flasher

--- Download parameters to netX.
-- @param tPlugin plugin object with an active connection
-- @param ulAddress
-- @param aulParameters
-- @param fnCallbackProgress is a function to call while downloading the flasher.
--   This parameter is optional. The default is to print a simple progress
--   message to stdout.
function Flasher:set_parameterblock(tPlugin, ulAddress, aulParameters, fnCallbackProgress)
  local bit = self.bit
  local strBin = ""
    for i,v in ipairs(aulParameters) do
      strBin = strBin .. string.char( bit.band(v,0xff), bit.band(bit.rshift(v,8),0xff), bit.band(bit.rshift(v,16),0xff), bit.band(bit.rshift(v,24),0xff) )
    end
  self:write_image(tPlugin, ulAddress, strBin, fnCallbackProgress) 
end

--- Stores parameters in netX memory, calls the flasher and returns the result value.
-- @param tPlugin plugin object with an active connection
-- @param aAttr
-- @param aulParams
-- @param fnCallbackMessage
-- @param fnCallbackProgress is a function to call while downloading the flasher.
--   This parameter is optional. The default is to print a simple progress
--   message to stdout.
-- @return result value: 0 = success, 1 = failure
function Flasher:callFlasher(tPlugin, aAttr, aulParams, fnCallbackMessage, fnCallbackProgress)
  -- fnCallbackMessage = fnCallbackMessage or self.fnMessageDefault
  -- fnCallbackProgress = fnCallbackProgress or self.fnProgressDefault

  local tLog = self.tLog
  -- set the parameters
  local aulParameter = {}
  aulParameter[1] = 0xffffffff                 -- placeholder for return vallue, will be 0 if ok
  aulParameter[2] = aAttr.ulParameter+0x0c     -- pointer to actual parameters
  aulParameter[3] = 0x00000000                 -- unused
                                             -- extended parameters
  aulParameter[4] = self.FLASHER_INTERFACE_VERSION  -- set the parameter version
  for i=1, #aulParams do
    aulParameter[4+i] = aulParams[i]     -- actual parameters for the particular function
  end

  self:set_parameterblock(tPlugin, aAttr.ulParameter, aulParameter, fnCallbackProgress)

  -- call
  self:call(tPlugin, aAttr.ulExecAddress, aAttr.ulParameter, fnCallbackMessage) 

  -- get the return value (ok/failed)
  -- any further return values must be read by the calling function
  ulValue = tPlugin:read_data32(aAttr.ulParameter+0x00)
  tLog.debug("call finished with result 0x%08x", ulValue)
  return ulValue
end


--                  Detecting flash and getting device info

--- Description.
-- @param tPlugin plugin object with an active connection
-- @param aAttr
-- @param fnCallbackMessage
-- @param fnCallbackProgress is a function to call while downloading the flasher.
--   This parameter is optional. The default is to print a simple progress
--   message to stdout.
-- @return aResult: 
function Flasher:getBoardInfo(tPlugin, aAttr, fnCallbackMessage, fnCallbackProgress)
  local tLog = self.tLog
  local aResult = nil

  local aulParameter = 
  {
    self.OPERATION_MODE_GetBoardInfo,      -- operation mode: get board info
    0,                                     -- Placeholder for the buffer address.
    0                                      -- Placeholder for the buffer size.
  }

  local ulValue = self:callFlasher(tPlugin, aAttr, aulParameter, fnCallbackMessage, fnCallbackProgress)

  if ulValue==0 then
    -- Get the buffer address and size.
    local pucBuffer = tPlugin:read_data32(aAttr.ulParameter+0x14)
    local sizBuffer = tPlugin:read_data32(aAttr.ulParameter+0x18)
    tLog.debug("Buffer 0x%08x 0x%08x", pucBuffer, sizBuffer)

    -- The size of the data should be a multiple of 32 bytes.
    if sizBuffer==0 then
      tLog.warning('No device info available.')
    elseif (sizBuffer % 32)~=0 then
      tLog.error('The size of the device info data is %d bytes. This is not a multiple of 32.', sizBuffer)
    elseif sizBuffer>0x3fff then
      tLog.error('The size of the device info data is %d bytes. Cowardly refusing to read more than 16KBytes.', sizBuffer)
    else
      local strInfo = self:read_image(tPlugin, pucBuffer, sizBuffer, fnCallbackProgress)

      aResult = {}
      -- Split the data into chunks of 32 bytes.
      for uiPos=1,sizBuffer,32 do
        local tAttr = {
          bus=string.byte(strInfo, uiPos),
          unit=string.byte(strInfo, uiPos+1),
          cs=string.byte(strInfo, uiPos+2),
          flags=string.byte(strInfo, uiPos+3),
          id=string.match(string.sub(strInfo, uiPos+4, uiPos+32), '^[%w%p]+')
        }
        tLog.debug('Found B%d_U%d_C%d = %s with flags=0x%02x', tAttr.bus, tAttr.unit, tAttr.cs, tAttr.id, tAttr.flags)

        table.insert(aResult, tAttr)
      end
    end
  end

  return aResult
end

--- Check if a device is available on tBus/ulUnit/ulChipSelect.
-- @param tPlugin plugin object with an active connection
-- @param aAttr
-- @param tBus
-- @param ulUnit
-- @param ulChipSelect
-- @param fnCallbackMessage
-- @param fnCallbackProgress is a function to call while downloading the flasher.
--   This parameter is optional. The default is to print a simple progress
--   message to stdout.
-- @param atParameter
-- @return ulValue == 0
function Flasher:detect(tPlugin, aAttr, tBus, ulUnit, ulChipSelect, fnCallbackMessage, fnCallbackProgress, atParameter)
  local aulParameter
  atParameter = atParameter or {}

  if tBus==self.BUS_Spi then
    -- Set the initial SPI speed. The default is 1000kHz (1MHz).
    local ulInitialSpeed = atParameter.ulInitialSpeed
    ulInitialSpeed = ulInitialSpeed or 1000

    -- Set the maximum SPI speed. The default is 25000kHz (25MHz).
    local ulMaximumSpeed = atParameter.ulMaximumSpeed
    ulMaximumSpeed = ulMaximumSpeed or 25000

    -- Set the idle configuration. The default is all lines driving 1.
    local ulIdleCfg = atParameter.ulIdleCfg
    ulIdleCfg = ulIdleCfg or (self.MSK_SQI_CFG_IDLE_IO1_OE + self.MSK_SQI_CFG_IDLE_IO1_OUT
                            + self.MSK_SQI_CFG_IDLE_IO2_OE + self.MSK_SQI_CFG_IDLE_IO2_OUT
                            + self.MSK_SQI_CFG_IDLE_IO3_OE + self.MSK_SQI_CFG_IDLE_IO3_OUT)

    -- Set the SPI mode. The default is 3.
    local ulSpiMode = atParameter.ulSpiMode
    ulSpiMode = ulSpiMode or 3

    -- Set the MMIO configuration. The default is 0xffffffff (no MMIO pins).
    local ulMmioConfiguration = atParameter.ulMmioConfiguration
    ulMmioConfiguration = ulMmioConfiguration or 0xffffffff

    aulParameter =
    {
      self.OPERATION_MODE_Detect,           -- operation mode: detect
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
  elseif tBus==self.BUS_Parflash then
    -- Set the allowed bus widths. This parameter is not used yet.
    local ulAllowedBusWidths = atParameter.ulAllowedBusWidths
    ulAllowedBusWidths = ulAllowedBusWidths or 0

    aulParameter =
    {
      self.OPERATION_MODE_Detect,           -- operation mode: detect
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
  elseif tBus==self.BUS_IFlash then
    aulParameter =
    {
      self.OPERATION_MODE_Detect,           -- operation mode: detect
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
  elseif tBus==self.BUS_SDIO then
    aulParameter = {
      self.OPERATION_MODE_Detect,           -- operation mode: detect
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

  local ulValue = self:callFlasher(tPlugin, aAttr, aulParameter, fnCallbackMessage, fnCallbackProgress)
  return ulValue == 0
end

--- Read device descriptor after detect (debugging).
-- @param tPlugin plugin object with an active connection
-- @param aAttr
-- @param fnCallbackProgress
-- @return strDevDesc: device description
function Flasher:readDeviceDescriptor(tPlugin, aAttr, fnCallbackProgress)
  -- check the device description
  local strDevDesc
  local ulSize
  local ulVersion
  local tLog = self.tLog

  local ulValue = tPlugin:read_data32(aAttr.ulDeviceDesc)
  if ulValue==0 then
    tLog.error("the device desription is not valid, nothing detected.")
  else

    -- get the size of the returned data
    ulSize = tPlugin:read_data32(aAttr.ulDeviceDesc+0x04)
    if ulSize<16 then
      tLog.error("the device description claims to be valid, but has a strange size.")
    else
      -- read the interface version of the returned data
      ulVersion = tPlugin:read_data32(aAttr.ulDeviceDesc+0x08)
      if ulVersion~=self.FLASHER_INTERFACE_VERSION then
        -- the version does not match the expected value
        tLog.error("the device description has a strange interface version.")
      else
        -- get the device description
        strDevDesc = self:read_image(tPlugin, aAttr.ulDeviceDesc, ulSize, fnCallbackProgress)
      end
    end
  end

  return strDevDesc
end

--- Description.
-- @param tPlugin plugin object with an active connection
-- @param aAttr
-- @param fnCallbackProgress
-- @return strDeviceId: device ID
function Flasher:getDeviceId(tPlugin, aAttr, fnCallbackProgress)
  -- Read the flash device descriptor.
  local strDeviceDescriptor = self:readDeviceDescriptor(tPlugin, aAttr, fnCallbackProgress)
  if strDeviceDescriptor==nil then
    error("Failed to read the flash device descriptor!")
  end

  strDeviceId = nil
  if tBus==self.BUS_Spi then
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

-- The following functions assume that detect has been run and there is a
-- valid device description in the memory.

-- ulStartAddr, ulEndAddr are offsets in the flash device.
-- ulDataAddress is the absolute address of the buffer.

--- Writes data which has been loaded into the buffer at ulDataAddress to ulStartAddr in the flash.
-- @param tPlugin plugin object with an active connection
-- @param aAttr
-- @param ulStartAdr
-- @param ulDataByteSize
-- @param ulDataAddress
-- @param fnCallbackMessage
-- @param fnCallbackProgress
-- @return ulValue == 0
function Flasher:flash(tPlugin, aAttr, ulStartAdr, ulDataByteSize, ulDataAddress, fnCallbackMessage, fnCallbackProgress)
  local aulParameter =
  {
    self.OPERATION_MODE_Flash,
    aAttr.ulDeviceDesc,
    ulStartAdr,
    ulDataByteSize,
    ulDataAddress
  }
  local ulValue = self:callFlasher(tPlugin, aAttr, aulParameter, fnCallbackMessage, fnCallbackProgress)
  return ulValue == 0
end

--- Reads data from flash to RAM.
-- @param tPlugin plugin object with an active connection
-- @param aAttr
-- @param ulFlashStartOffset
-- @param ulFlashEndOffset
-- @param ulBufferAddress
-- @param fnCallbackMessage
-- @param fnCallbackProgress
-- @return ulValue == 0
function Flasher:read(tPlugin, aAttr, ulFlashStartOffset, ulFlashEndOffset, ulBufferAddress, fnCallbackMessage, fnCallbackProgress)
  local aulParameter =
  {
    self.OPERATION_MODE_Read,
    aAttr.ulDeviceDesc,
    ulFlashStartOffset,
    ulFlashEndOffset,
    ulBufferAddress
  }
  local ulValue = self:callFlasher(tPlugin, aAttr, aulParameter, fnCallbackMessage, fnCallbackProgress)
  return ulValue == 0
end

--- Compares data in flash to RAM.
-- @param tPlugin plugin object with an active connection
-- @param aAttr
-- @param ulFlashStartOffset
-- @param ulFlashEndOffset
-- @param ulBufferAddress
-- @param fnCallbackMessage
-- @param fnCallbackProgress
-- @return fEqual: if equal, returns true else false.
function Flasher:verify(tPlugin, aAttr, ulFlashStartOffset, ulFlashEndOffset, ulBufferAddress, fnCallbackMessage, fnCallbackProgress)
  local fEqual = false
  local aulParameter =
  {
    self.OPERATION_MODE_Verify,
    aAttr.ulDeviceDesc,
    ulFlashStartOffset,
    ulFlashEndOffset,
    ulBufferAddress
  }
  local ulValue = self:callFlasher(tPlugin, aAttr, aulParameter, fnCallbackMessage, fnCallbackProgress)

  if ulValue==0 then
    ulValue = tPlugin:read_data32(aAttr.ulParameter+0x08)
    fEqual = (ulValue==0)
  end

  return fEqual
end

--- Computes the SHA1 hash over data in the flash.
-- @param tPlugin plugin object with an active connection
-- @param aAttr
-- @param ulFlashStartOffset
-- @param ulFlashEndOffset
-- @param fnCallbackMessage
-- @param fnCallbackProgress
-- @return  ulValue == 0
-- @return strHashBin: 
function Flasher:hash(tPlugin, aAttr, ulFlashStartOffset, ulFlashEndOffset, fnCallbackMessage, fnCallbackProgress)
  local strHashBin = nil
  local aulParameter =
  {
    self.OPERATION_MODE_Checksum,
    aAttr.ulDeviceDesc,
    ulFlashStartOffset,
    ulFlashEndOffset,
  }
  local ulValue = self:callFlasher(tPlugin, aAttr, aulParameter, fnCallbackMessage, fnCallbackProgress)

  if ulValue==0 then
    strHashBin = self:read_image(tPlugin, aAttr.ulParameter+0x20, 20, fnCallbackProgress)
  end

  return ulValue == 0, strHashBin
end

--- Determines the smallest interval of sectors which has to be erased in order to erase ulStartAdr to ulEndAdr-1.
-- @param tPlugin plugin object with an active connection
-- @param aAttr
-- @param ulStartAdr
-- @param ulEndAdr
-- @param fnCallbackMessage
-- @param fnCallbackProgress
-- @return ulEraseStart:             ,otherwise returns nil if the call fails.
-- @return ulEraseEnd:             ,otherwise returns nil if the call fails.
function Flasher:getEraseArea(tPlugin, aAttr, ulStartAdr, ulEndAdr, fnCallbackMessage, fnCallbackProgress)
  local ulEraseStart
  local ulEraseEnd

  local aulParameter =
  {
    self.OPERATION_MODE_GetEraseArea,      -- operation mode: get erase area
    aAttr.ulDeviceDesc,                    -- data block for the device description
    ulStartAdr,
    ulEndAdr
  }

  local ulValue = self:callFlasher(tPlugin, aAttr, aulParameter, fnCallbackMessage, fnCallbackProgress)
  if ulValue==0 then
    ulEraseStart = tPlugin:read_data32(aAttr.ulParameter+0x18)
    ulEraseEnd = tPlugin:read_data32(aAttr.ulParameter+0x1c)
  end

  return ulEraseStart, ulEraseEnd
end

--- Get the flash size via getEraseArea.
-- @param tPlugin plugin object with an active connection
-- @param aAttr
-- @param fnCallbackMessage
-- @param fnCallbackProgress
-- @return ulEraseEnd: 
function Flasher:getFlashSize(tPlugin, aAttr, fnCallbackMessage, fnCallbackProgress)
  local ulEraseStart, ulEraseEnd = self:getEraseArea(tPlugin, aAttr, 0, 0xffffffff, fnCallbackMessage, fnCallbackProgress)
  return ulEraseEnd
end

--- Checks if the area from ulEraseStart to ulEraseEnd is 0xff.
-- @param tPlugin plugin object with an active connection
-- @param aAttr
-- @param ulEraseStart
-- @param ulEraseEnd
-- @param fnCallbackMessage
-- @param fnCallbackProgress
-- @return fIsErased: 
-- TODO: return nil if the call fails (e.g. because ulEraseEnd is too large)
function Flasher:isErased(tPlugin, aAttr, ulEraseStart, ulEraseEnd, fnCallbackMessage, fnCallbackProgress)
  local fIsErased = false

  local aulParameter =
  {
    self.OPERATION_MODE_IsErased,          -- operation mode: isErased
    aAttr.ulDeviceDesc,                    -- data block for the device description
    ulEraseStart,
    ulEraseEnd
  }

  local ulValue = self:callFlasher(tPlugin, aAttr, aulParameter, fnCallbackMessage, fnCallbackProgress)

  if ulValue == 0 then
    ulValue = tPlugin:read_data32(aAttr.ulParameter + 0x08)
    fIsErased = (ulValue == 0xff)
  else -- TODO: Solution
    tLog.debug("Failed to call the flasher")
    return nil
  end

  return fIsErased
end

--- Erase an area in the flash. The start and end addresses must be aligned to sector boundaries as set by getEraseArea.
-- @param tPlugin plugin object with an active connection
-- @param aAttr
-- @param ulEraseStart
-- @param ulEraseEnd
-- @param fnCallbackMessage
-- @param fnCallbackProgress
-- @return ulValue == 0
function Flasher:erase(tPlugin, aAttr, ulEraseStart, ulEraseEnd, fnCallbackMessage, fnCallbackProgress)
  local aulParameter =
  {
    self.OPERATION_MODE_Erase,                          -- operation mode: erase
    aAttr.ulDeviceDesc,                            -- data block for the device description
    ulEraseStart,
    ulEraseEnd
  }
  local ulValue = self:callFlasher(tPlugin, aAttr, aulParameter, fnCallbackMessage, fnCallbackProgress)
  return ulValue == 0
end

--- Easy erase. A combination of GetEraseArea, IsErased and Erase.
--
-- NOTE: This is an equivalent of the eraseArea function (see below) for environments without scripting capabilities. This function exists just for the sake of a complete API.
-- @param tPlugin plugin object with an active connection
-- @param aAttr
-- @param ulEraseStart
-- @param ulEraseEnd
-- @param fnCallbackMessage
-- @param fnCallbackProgress
-- @return ulValue == 0  
function Flasher:easy_erase(tPlugin, aAttr, ulEraseStart, ulEraseEnd, fnCallbackMessage, fnCallbackProgress)
  local aulParameter =
  {
    self.OPERATION_MODE_EasyErase,                      -- operation mode: easy erase
    aAttr.ulDeviceDesc,                            -- data block for the device description
    ulEraseStart,
    ulEraseEnd
  }
  local ulValue = self:callFlasher(tPlugin, aAttr, aulParameter, fnCallbackMessage, fnCallbackProgress)
  return ulValue == 0
end


--- erase an area.
--
-- Check if the area is already erased and erase only if it isn't empty.
-- ulSize = 0xffffffff to erase from ulDeviceOffset to end of chip.
--
-- @param tPlugin plugin object with an active connection
-- @param aAttr
-- @param ulDeviceOffset
-- @param ulSize
-- @param fnCallbackMessage
-- @param fnCallbackProgress
-- @return
-- OK:  
-- returns true, The area is empty, no erase necessary.  
-- returns true, Area erased  
--
-- Error messages:  
-- returns false, "getEraseArea failed!"  
-- returns false, "Failed to check if the area is erased!"  
-- returns false, "getEraseArea failed!"  
-- returns false, "Failed to erase the area! (Failure during erase)"  
-- returns false, "Failed to erase the area! (isErased check failed)"  
function Flasher:eraseArea(tPlugin, aAttr, ulDeviceOffset, ulSize, fnCallbackMessage, fnCallbackProgress)
  -- fnCallbackProgress = fnCallbackProgress or self.fnProgressDefault
  local fIsErased
  local ulEndOffset
  local ulEraseStart,ulEraseEnd
  local tLog = self.tLog

  -- If length = 0xffffffff we get the erase area now in order to detect the flash size.
  if ulSize == 0xffffffff then
    ulEndOffset = ulSize
    ulEraseStart,ulEraseEnd = self:getEraseArea(tPlugin, aAttr, ulDeviceOffset, ulEndOffset, fnCallbackMessage, self.fnProgressDefault)
    if not (ulEraseStart and ulEraseEnd) then
      return false, "getEraseArea failed!"
    end

    ulEndOffset = ulEraseEnd
  else
    ulEndOffset = ulDeviceOffset + ulSize
  end

  tLog.debug("Area:  [0x%08x, 0x%08x[", ulDeviceOffset, ulEndOffset)

  -- The total number of bytes to process is 3x the erase area.

  tLog.debug("Checking if the area is already empty")
  fIsErased = self:isErased(tPlugin, aAttr, ulDeviceOffset, ulEndOffset, fnCallbackMessage, fnCallbackProgress)

  if fIsErased==nil then
    return false, "Failed to check if the area is erased!"
  elseif fIsErased==true then
    return true, "The area is empty, no erase necessary."
  else
    -- Get the erase area unless we have already gotten it.
    if not (ulEraseStart and ulEraseEnd) then
      ulEraseStart, ulEraseEnd =
      self:getEraseArea(tPlugin, aAttr, ulDeviceOffset, ulEndOffset, fnCallbackMessage, fnCallbackProgress)
      if not (ulEraseStart and ulEraseEnd) then
        return false, "getEraseArea failed!"
      end
    end

    tLog.debug("Erasing flash")
    tLog.debug("Erase: [0x%08x, 0x%08x[", ulEraseStart, ulEraseEnd)

    fIsErased = self:erase(tPlugin, aAttr, ulEraseStart, ulEraseEnd, fnCallbackMessage, fnCallbackProgress)
    if fIsErased~=true then
      return false, "Failed to erase the area! (Failure during erase)"
    else
      tLog.debug("Checking if the area has been erased")
      
      fIsErased = self:isErased(tPlugin, aAttr, ulDeviceOffset, ulEndOffset, fnCallbackMessage, fnCallbackProgress)
      if fIsErased~=true then
        return false, "Failed to erase the area! (isErased check failed)"
      end
    end
  end
  return true, "Area erased"
end

--- Flash data in chunks.
-- @param tPlugin plugin object with an active connection
-- @param aAttr
-- @param ulDeviceOffset
-- @param strData
-- @param fnCallbackMessage
-- @param fnCallbackProgress
-- @return 
-- Error messages:  
-- returns false, "Failed to flash data!"
--
-- Ok:  
-- returns true, "Image flashed."
function Flasher:flashArea(tPlugin, aAttr, ulDeviceOffset, strData, fnCallbackMessage, fnCallbackProgress)
  -- fnCallbackProgress = fnCallbackProgress or self.fnProgressDefault
  local fOk
  local ulDataByteSize = strData:len()
  local ulDataOffset = 0
  local ulProgressOffset = 0
  local ulBufferAdr = aAttr.ulBufferAdr
  local ulBufferLen = aAttr.ulBufferLen
  local ulChunkSize
  local strChunk
  local tLog = self.tLog

  -- The total number of bytes to process is 2x the flash area.

  while ulDataOffset<ulDataByteSize do
    -- Extract the next chunk.
    -- Required for netx 90 Intflash, does not hurt in other cases:
    -- Align the end of the chunk to a 16 byte boundary, unless this is the last chunk.
    -- Note: Additionally, ulDeviceOffset must also be a multiple of 16 bytes.
    local ulEnd = ulDataOffset+ulBufferLen
    if ulEnd < ulDataByteSize then
      ulEnd = ulEnd - (ulEnd % 16) 
    end
    strChunk = strData:sub(ulDataOffset+1, ulEnd)
    ulChunkSize = strChunk:len()

    -- Download the chunk to the buffer.
    self:write_image(tPlugin, ulBufferAdr, strChunk, fnCallbackProgress)
  
    -- Flash the chunk.
    tLog.debug("flashing offset 0x%08x-0x%08x.", ulDeviceOffset, ulDeviceOffset + ulChunkSize)
    fOk = self:flash(tPlugin, aAttr, ulDeviceOffset, ulChunkSize, ulBufferAdr, fnCallbackMessage, fnCallbackProgress)
    if not fOk then
      return false, "Failed to flash data!"
    end

    -- Increase pointers.
    ulDataOffset = ulDataOffset + ulChunkSize
    ulDeviceOffset = ulDeviceOffset + ulChunkSize
  end

  return true, "Image flashed."
end

--- Verify data in chunks.
-- @param tPlugin plugin object with an active connection
-- @param aAttr
-- @param ulDeviceOffset
-- @param strData
-- @param fnCallbackMessage
-- @param fnCallbackProgress
-- @return 
-- Ok:  
-- returns true, "The data in the flash is equal to the input file."
--
-- Error messages:  
-- returns false, "Differences were found."
function Flasher:verifyArea(tPlugin, aAttr, ulDeviceOffset, strData, fnCallbackMessage, fnCallbackProgress)
  local fOk
  local ulDataByteSize = strData:len()
  local ulDataOffset = 0
  local ulBufferAdr = aAttr.ulBufferAdr
  local ulBufferLen = aAttr.ulBufferLen
  local ulChunkSize
  local strChunk
  local tLog = self.tLog

  while ulDataOffset<ulDataByteSize do
    -- Extract the next chunk.
    strChunk = strData:sub(ulDataOffset+1, ulDataOffset+ulBufferLen)
    ulChunkSize = strChunk:len()

    -- Download the chunk to the buffer.
    self:write_image(tPlugin, ulBufferAdr, strChunk, fnCallbackProgress)

    -- Verify the chunk.
    tLog.debug("verifying offset 0x%08x-0x%08x.", ulDeviceOffset, ulDeviceOffset + ulChunkSize)
    fOk = self:verify(tPlugin, aAttr, ulDeviceOffset, ulDeviceOffset + ulChunkSize, ulBufferAdr, fnCallbackMessage, fnCallbackProgress)
    if not fOk then
      return false, "Differences were found."
    end

    -- Increase pointers.
    ulDataOffset = ulDataOffset + ulChunkSize
    ulDeviceOffset = ulDeviceOffset + ulChunkSize
  end

  return true, "The data in the flash is equal to the input file."
end

--- Read data in chunks.  
--  size = 0xffffffff to read from ulDeviceOffset to end of device.
-- @param tPlugin plugin object with an active connection
-- @param aAttr
-- @param ulDeviceOffset
-- @param ulDataByteSize
-- @param fnCallbackMessage
-- @param fnCallbackProgress
-- @return 
-- Ok:  
-- "Read successful."  
-- returns strBin, strMsg  
--
-- Error messages:  
-- nil, "Could not determine the flash size!" 
-- nil, "Error while reading from flash!"
-- nil, "Error while reading from RAM buffer!"
function Flasher:readArea(tPlugin, aAttr, ulDeviceOffset, ulDataByteSize, fnCallbackMessage, fnCallbackProgress)
  local fOk
  local ulSize = ulDataByteSize
  local ulBufferAddr = aAttr.ulBufferAdr
  local ulBufferLen = aAttr.ulBufferLen
  local strChunk
  local ulChunkSize
  local astrChunks = {}
  local tLog = self.tLog

  if ulSize == 0xffffffff then 
    ulSize = self:getFlashSize(tPlugin, aAttr, fnCallbackMessage, fnCallbackProgress)
    if ulSize then
      tLog.debug("Flash size: 0x%08x bytes", ulSize)
      ulSize = ulSize - ulDeviceOffset
    else
      return nil, "Could not determine the flash size!"
    end
  end

  while ulSize>0 do
    -- determine chunk size
    ulChunkSize = math.min(ulSize, ulBufferLen)

    -- Read chunk into buffer
    tLog.debug("reading flash offset 0x%08x-0x%08x.", ulDeviceOffset, ulDeviceOffset + ulChunkSize)
    fOk = self:read(tPlugin, aAttr, ulDeviceOffset, ulDeviceOffset + ulChunkSize, ulBufferAddr, fnCallbackMessage, fnCallbackProgress)
    if not fOk then
      return nil, "Error while reading from flash!"
    end

    -- Read the buffer 
    strChunk = self:read_image(tPlugin, ulBufferAddr, ulChunkSize, fnCallbackProgress)
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



--- Calculate the SHA1 hash of an area of an area in the flash.  
-- size = 0xffffffff to read from ulDeviceOffset to end of device.
-- @param tPlugin plugin object with an active connection
-- @param aAttr
-- @param ulDeviceOffset
-- @param ulDataByteSize
-- @param fnCallbackMessage
-- @param fnCallbackProgress
-- @return Returns the hash as a binary string or nil and an error message.  
--
-- Ok:    
-- returns strFlashHashBin, "Checksum calculated."  
--
-- Error messages:  
-- returns nil, "Could not determine the flash size!"  
-- returns nil, "Error while calculating SHA1 hash"  
function Flasher:hashArea(tPlugin, aAttr, ulDeviceOffset, ulDataByteSize, fnCallbackMessage, fnCallbackProgress)
  local ulDeviceEndOffset
  local tLog = self.tLog
  if ulDataByteSize == 0xffffffff then 
    local ulDeviceSize = self:getFlashSize(tPlugin, aAttr, fnCallbackMessage, fnCallbackProgress)
    if ulDeviceSize then
      tLog.debug("Flash size: 0x%08x bytes", ulDeviceSize)
      ulDeviceEndOffset = ulDeviceSize
    else
      return nil, "Could not determine the flash size!"
    end
  else
    ulDeviceEndOffset = ulDeviceOffset + ulDataByteSize
  end

  local fOk, strFlashHashBin = self:hash(tPlugin, aAttr, ulDeviceOffset, ulDeviceEndOffset, fnCallbackMessage, fnCallbackProgress)
  if fOk~=true then
    return nil, "Error while calculating SHA1 hash."
  else
    return strFlashHashBin, "Checksum calculated."
  end
end


--- This is a simple routine to flash the data in a string.
-- Load file from strDataFileName and write it to offset 0.
-- Raise an error in case of any errors.
-- @param tPlugin plugin object with an active connection
-- @param strData
-- @param tBus
-- @param ulUnit
-- @param ulChipSelect
-- @param strFlasherPrefix
-- @param fnCallbackProgress
-- @param fnCallbackMessage

function Flasher:simple_flasher_string(tPlugin, strData, tBus, ulUnit, ulChipSelect, strFlasherPrefix, fnCallbackProgress, fnCallbackMessage)
  strFlasherPrefix = strFlasherPrefix or ""

  local fOk
  local strMsg
  local ulDeviceOffset = 0
  local tLog = self.tLog

  -- Download the binary.
  local aAttr = self:download(tPlugin, strFlasherPrefix, fnCallbackProgress)

  -- Detect the device.
  fOk = self:detect(tPlugin, aAttr, tBus, ulUnit, ulChipSelect, fnCallbackMessage, fnCallbackProgress)
  if fOk~=true then
    error("Failed to detect the device!")
  end

  fOk, strMsg = self:eraseArea(tPlugin, aAttr, ulDeviceOffset, strData:len(), fnCallbackMessage, fnCallbackProgress)
  tLog.debug(strMsg)
  assert(fOk, strMsg or "Error while erasing area")

  fOk, strMsg = self:flashArea(tPlugin, aAttr, ulDeviceOffset, strData, fnCallbackMessage, fnCallbackProgress)
  tLog.debug(strMsg)
  assert(fOk, strMsg or "Error while programming area")

  tLog.debug("*** Flashing ok ***")
end


--- This is a simple routine to flash one file.
-- Load file from strDataFileName and write it to offset 0.
-- Raise an error in case of any errors.
-- @param tPlugin plugin object with an active connection
-- @param strDataFileName
-- @param tBus
-- @param ulUnit
-- @param ulChipSelect
-- @param strFlasherPrefix
-- @param fnCallbackProgress
-- @param fnCallbackMessage
function Flasher:simple_flasher(tPlugin, strDataFileName, tBus, ulUnit, ulChipSelect, strFlasherPrefix, fnCallbackProgress, fnCallbackMessage)
  -- Load the data.
  local tFile, strMsg = io.open(strDataFileName, 'rb')
  if tFile==nil then
    error(string.format('Failed to open file "%s" for reading: %s', strPath, strMsg))
  end
  local strData = tFile:read('*a')
  tFile:close()

  self:simple_flasher_string(tPlugin, strData, tBus, ulUnit, ulChipSelect, strFlasherPrefix, fnCallbackProgress, fnCallbackMessage)
end


--- SPI debug interface.
-- @param tPlugin plugin object with an active connection
-- @param aAttr
-- @param ulUnit
-- @param ulChipSelect
-- @param ulSpeed_kHz
-- @param fnCallbackProgress
-- @param fnCallbackMessage
-- @return ulValue == 0
function Flasher:sdi_init(tPlugin, aAttr, ulUnit, ulChipSelect, ulSpeed_kHz, fnCallbackProgress, fnCallbackMessage)
  local ulIdleCfg = self.MSK_SQI_CFG_IDLE_IO1_OE + self.MSK_SQI_CFG_IDLE_IO1_OUT
                  + self.MSK_SQI_CFG_IDLE_IO2_OE + self.MSK_SQI_CFG_IDLE_IO2_OUT
                  + self.MSK_SQI_CFG_IDLE_IO3_OE + self.MSK_SQI_CFG_IDLE_IO3_OUT

  local aulParameter =
  {
    self.OPERATION_MODE_SpiMacroPlayer,   -- operation mode: SPI macro player
    self.SMC_INITIALIZE,                  -- Command: initialize
    aAttr.ulDeviceDesc,                   -- free space for the SPI configuration
    ulUnit,                               -- the SPI unit
    ulChipSelect,                         -- the SPI chip select
    ulSpeed_kHz,                          -- the speed in kHz (1000 -> 1MHz)
    ulSpeed_kHz,                          -- the maximum kHz
    ulIdleCfg,                            -- idle configuration
    3,                                    -- mode
    0xffffffff                            -- MMIO configuration
  }
  local ulValue = self:callFlasher(tPlugin, aAttr, aulParameter, fnCallbackMessage, fnCallbackProgress)
  return ulValue == 0
end

--- Description.
-- @param tPlugin plugin object with an active connection
-- @param aAttr
-- @param uiActive
-- @param fnCallbackProgress
-- @param fnCallbackMessage
-- @return ulValue == 0
function Flasher:sdi_chip_select(tPlugin, aAttr, uiActive, fnCallbackProgress, fnCallbackMessage)
  local ulValue
  if tonumber(uiActive)==0 then
    ulValue = 0
  else
    ulValue = 1
  end

  local aulParameter =
  {
    self.OPERATION_MODE_SpiMacroPlayer,   -- operation mode: SPI macro player
    self.SMC_CHIP_SELECT,                 -- Command: chip select
    aAttr.ulDeviceDesc,                   -- the SPI configuration
    ulValue,                              -- chip select
  }
  ulValue = self:callFlasher(tPlugin, aAttr, aulParameter, fnCallbackMessage, fnCallbackProgress)
  return ulValue == 0
end

--- Description.
-- @param tPlugin plugin object with an active connection
-- @param aAttr
-- @param strData
-- @param fnCallbackProgress
-- @param fnCallbackMessage
-- @return strRxData: 
function Flasher:sdi_exchange_data(tPlugin, aAttr, strData, fnCallbackProgress, fnCallbackMessage)
  local strRxData
  local sizData = string.len(strData)

  local ulTxBuffer = aAttr.ulBufferAdr
  local ulRxBuffer = aAttr.ulBufferAdr + sizData

  -- Download the data.
  self:write_image(tPlugin, ulTxBuffer, strData, fnCallbackProgress)

  local aulParameter =
  {
    self.OPERATION_MODE_SpiMacroPlayer,   -- operation mode: SPI macro player
    self.SMC_EXCHANGE_DATA,               -- Command: exchange data
    aAttr.ulDeviceDesc,                   -- the SPI configuration
    ulTxBuffer,
    ulRxBuffer,
    sizData
  }
  local ulValue = self:callFlasher(tPlugin, aAttr, aulParameter, fnCallbackMessage, fnCallbackProgress)
  if ulValue==0 then
    strRxData = self:read_image(tPlugin, ulRxBuffer, sizData, fnCallbackProgress)
  end

  return strRxData
end

--- Description.
-- @param tPlugin plugin object with an active connection
-- @param aAttr
-- @param strData
-- @param fnCallbackProgress
-- @param fnCallbackMessage
-- @return ulValue == 0
function Flasher:sdi_send_data(tPlugin, aAttr, strData, fnCallbackProgress, fnCallbackMessage)
  local sizData = string.len(strData)

  local ulTxBuffer = aAttr.ulBufferAdr

  -- Download the data.
  self:write_image(tPlugin, ulTxBuffer, strData, fnCallbackProgress)

  local aulParameter =
  {
    self.OPERATION_MODE_SpiMacroPlayer,   -- operation mode: SPI macro player
    self.SMC_SEND_DATA,                   -- Command: send data
    aAttr.ulDeviceDesc,                   -- the SPI configuration
    ulTxBuffer,
    sizData
  }

  local ulValue = self:callFlasher(tPlugin, aAttr, aulParameter, fnCallbackMessage, fnCallbackProgress)

  return ulValue == 0
end

--- Description.
-- @param tPlugin plugin object with an active connection
-- @param aAttr
-- @param sizData
-- @param fnCallbackProgress
-- @param fnCallbackMessage
-- @return strRxData:
function Flasher:sdi_receive_data(tPlugin, aAttr, sizData, fnCallbackProgress, fnCallbackMessage)
  local strRxData
  local ulRxBuffer = aAttr.ulBufferAdr

  local aulParameter =
  {
    self.OPERATION_MODE_SpiMacroPlayer,   -- operation mode: SPI macro player
    self.SMC_RECEIVE_DATA,                -- Command: receive data
    aAttr.ulDeviceDesc,                   -- the SPI configuration
    ulRxBuffer,
    sizData
  }

  local ulValue = self:callFlasher(tPlugin, aAttr, aulParameter, fnCallbackMessage, fnCallbackProgress)
  if ulValue==0 then
    strRxData = self:read_image(tPlugin, ulRxBuffer, sizData, fnCallbackProgress)
  end

  return strRxData
end

--- Description.
-- @param tPlugin plugin object with an active connection
-- @param aAttr
-- @param sizIdleBytes
-- @param fnCallbackProgress
-- @param fnCallbackMessage
-- @return ulValue == 0
function Flasher:sdi_idle_bytes(tPlugin, aAttr, sizIdleBytes, fnCallbackProgress, fnCallbackMessage)
  local aulParameter =
  {
    self.OPERATION_MODE_SpiMacroPlayer,   -- operation mode: SPI macro player
    self.SMC_SEND_IDLE_BYTES,             -- Command: send idle bytes
    aAttr.ulDeviceDesc,                   -- the SPI configuration
    sizIdleBytes
  }
  local ulValue = self:callFlasher(tPlugin, aAttr, aulParameter, fnCallbackMessage, fnCallbackProgress)

  return ulValue == 0
end

return Flasher
