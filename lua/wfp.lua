require 'muhkuh_cli_init'
require 'flasher'
local archive = require 'archive'
local argparse = require 'argparse'
local wfp_control = require 'wfp_control'


local strFlasherPrefix = 'netx/'

local atLogLevels = {
  'debug',
  'info',
  'warning',
  'error',
  'fatal'
}

local tParser = argparse('wfp', 'Flash, list and create "wonderful feelings" packages.')
  :command_target("strSubcommand")

-- Add the "flash" command and all its options.
local tParserCommandFlash = tParser:command('flash f', 'Flash the contents of the WFP.')
  :target('fCommandFlashSelected')
tParserCommandFlash:argument('archive', 'The WFP file to process.')
  :target('strWfpArchiveFile')
tParserCommandFlash:flag('-d --dry-run')
  :description('Dry run. Connect to a netX and read all data from the WFP, but to not alter the flash.')
  :default(false)
  :target('fDryRun')
tParserCommandFlash:option('-v --verbose')
  :description(string.format('Set the verbosity level to LEVEL. Possible values for LEVEL are %s.', table.concat(atLogLevels, ', ')))
  :argname('<LEVEL>')
  :default('debug')
  :target('strLogLevel')

-- Add the "list" command and all its options.
local tParserCommandList = tParser:command('list l', 'List the contents of the WFP.')
  :target('fCommandListSelected')
tParserCommandList:argument('archive', 'The WFP file to process.')
  :target('strWfpArchiveFile')
tParserCommandList:option('-v --verbose')
  :description(string.format('Set the verbosity level to LEVEL. Possible values for LEVEL are %s.', table.concat(atLogLevels, ', ')))
  :argname('<LEVEL>')
  :default('debug')
  :target('strLogLevel')

local tArgs = tParser:parse()

local tLogWriterConsole = require 'log.writer.console'.new()
local tLogWriterFilter = require 'log.writer.filter'.new(tArgs.strLogLevel, tLogWriterConsole)
local tLogWriter = require 'log.writer.prefix'.new('[Main] ', tLogWriterFilter)
local tLog = require 'log'.new(
  'trace',
  tLogWriter,
  require 'log.formatter.format'.new()
)


local atName2Bus = {
  ['Parflash'] = flasher.BUS_Parflash,
  ['Spi']      = flasher.BUS_Spi,
  ['IFlash']   = flasher.BUS_IFlash
}


-- Create the WFP controller.
local tWfpControl = wfp_control(tLogWriterFilter)

local fOk = true

if tArgs.fCommandFlashSelected==true then
  -- Read the control file from the WFP archive.
  tLog.debug('Using WFP archive "%s".', tArgs.strWfpArchiveFile)
  local tResult = tWfpControl:open(tArgs.strWfpArchiveFile)
  if tResult==nil then
    tLog.error('Failed to open the archive "%s"!', tArgs.strWfpArchiveFile)
    fOk = false
  else
    -- Select a plugin and connect to the netX.
    local tPlugin = tester.getCommonPlugin()
    if not tPlugin then
      tLog.error('No plugin selected, nothing to do!')
      fOk = false
    else
      local iChiptype = tPlugin:GetChiptyp()
      -- Does the WFP have an entry for the chip?
      local tTarget = tWfpControl:getTarget(iChiptype)
      if tTarget==nil then
        tLog.error('The chip type %s is not supported.', tostring(iChiptype))
        fOk = false
      else
        -- Download the binary.
        local aAttr = flasher.download(tPlugin, strFlasherPrefix)

        -- Loop over all flashes.
        for _, tTargetFlash in ipairs(tTarget.atFlashes) do
          local strBusName = tTargetFlash.strBus
          local tBus = atName2Bus[strBusName]
          if tBus==nil then
            tLog.error('Unknown bus "%s" found in WFP control file.', strBusName)
            fOk = false
            break
          else
            local ulUnit = tTargetFlash.ulUnit
            local ulChipSelect = tTargetFlash.ulChipSelect
            tLog.debug('Processing bus: %s, unit: %d, chip select: %d', strBusName, ulUnit, ulChipSelect)

            -- Detect the device.
            fOk = flasher.detect(tPlugin, aAttr, tBus, ulUnit, ulChipSelect)
            if fOk~=true then
              tLog.error("Failed to detect the device!")
              fOk = false
              break
            end

            for _, tData in ipairs(tTargetFlash.atData) do
              local strFile = tData.strFile
              local ulOffset = tData.ulOffset
              tLog.debug('Found file "%s" with offset 0x%08x.', strFile, ulOffset)

              -- Loading the file data from the archive.
              local strData = tWfpControl:getData(strFile)
              local sizData = string.len(strData)
              if strData~=nil then
                if tArgs.fDryRun==true then
                  tLog.warning('Not touching the flash as dry run is selected.')
                else
                  tLog.debug('Flashing %d bytes...', sizData)

                  fOk, strMsg = flasher.eraseArea(tPlugin, aAttr, ulOffset, sizData)
                  if fOk~=true then
                    tLog.error('Failed to erase the area: %s', strMsg)
                    fOk = false
                    break
                  else
                    fOk, strMsg = flasher.flashArea(tPlugin, aAttr, ulOffset, strData)
                    if fOk~=true then
                      tLog.error('Failed to flash the area: %s', strMsg)
                      fOk = false
                      break
                    end
                  end
                end
              end
            end
          end

          if fOk~=true then
            break
          end
        end
      end
    end
  end
elseif tArgs.fCommandListSelected==true then
  -- Read the control file from the WFP archive.
  tLog.debug('Using WFP archive "%s".', tArgs.strWfpArchiveFile)
  local tResult = tWfpControl:open(tArgs.strWfpArchiveFile)
  if tResult==nil then
    tLog.error('Failed to open the archive "%s"!', tArgs.strWfpArchiveFile)
    fOk = false
  else
    tLog.info('WFP contents:')
    for strTarget, tTarget in pairs(tWfpControl.atConfigurationTargets) do
      tLog.info('  "%s":', strTarget)

      -- Loop over all flashes.
      for _, tTargetFlash in ipairs(tTarget.atFlashes) do
        local strBusName = tTargetFlash.strBus
        local tBus = atName2Bus[strBusName]
        if tBus==nil then
          tLog.error('Unknown bus "%s" found in WFP control file.', strBusName)
          fOk = false
          break
        else
          local ulUnit = tTargetFlash.ulUnit
          local ulChipSelect = tTargetFlash.ulChipSelect
          tLog.info('    Bus: %s, unit: %d, chip select: %d', strBusName, ulUnit, ulChipSelect)
          for _, tData in ipairs(tTargetFlash.atData) do
            local strFile = tData.strFile
            local ulOffset = tData.ulOffset
            tLog.info('      0x%08x: "%s"', ulOffset, strFile)
          end
        end
      end

      if fOk~=true then
        break
      end
    end
  end
end


if fOk==true then
  tLog.info('')
  tLog.info(' #######  ##    ## ')
  tLog.info('##     ## ##   ##  ')
  tLog.info('##     ## ##  ##   ')
  tLog.info('##     ## #####    ')
  tLog.info('##     ## ##  ##   ')
  tLog.info('##     ## ##   ##  ')
  tLog.info(' #######  ##    ## ')
  tLog.info('')
end
