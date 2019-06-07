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

-- Add the "pack" command and all its options.
local tParserCommandPack = tParser:command('pack p', 'Pack a WFP based on an XML.')
  :target('fCommandPackSelected')
tParserCommandPack:argument('xml', 'The XML control file.')
  :target('strWfpControlFile')
tParserCommandPack:argument('archive', 'The WFP file to create.')
  :target('strWfpArchiveFile')
tParserCommandPack:flag('-o --overwrite')
  :description('Overwrite an existing WFP archive. The default is to do nothing if the target archive already exists.')
  :default(false)
  :target('fOverwrite')
tParserCommandPack:option('-v --verbose')
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
local pl = tWfpControl.pl

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
elseif tArgs.fCommandPackSelected==true then
  local archive = require 'archive'

  -- Does the archive already exist?
  local strWfpArchiveFile = tArgs.strWfpArchiveFile
  if pl.path.exists(strWfpArchiveFile)==strWfpArchiveFile then
    if tArgs.fOverwrite~=true then
      tLog.error('The output archive "%s" already exists. Use "--overwrite" to force overwriting it.', strWfpArchiveFile)
      fOk = false
    else
      local tFsResult, strError = pl.file.delete(strWfpArchiveFile)
      if tFsResult==nil then
        self.tLog.error('Failed to delete the old archive "%s": %s', strArchivePath, strError)
        fOk = false
      end
    end
  end

  if fOk==true then
    local tResult = tWfpControl:openXml(tArgs.strWfpControlFile)
    if tResult==nil then
      tLog.error('Failed to read the control file "%s"!', tArgs.strWfpControlFile)
      fOk = false
    else
      -- Get the absolute directory of the control file.
      local strWorkingPath = pl.path.dirname(pl.path.abspath(tArgs.strWfpControlFile))

      -- Collect all file references from the control file.
      local atFiles = {}
      local atSortedFiles = {}
      for strTarget, tTarget in pairs(tWfpControl.atConfigurationTargets) do
        for _, tTargetFlash in ipairs(tTarget.atFlashes) do
          for _, tData in ipairs(tTargetFlash.atData) do
            local strFile = tData.strFile
            local strFileAbs = strFile
            if pl.path.isabs(strFileAbs)~=true then
              strFileAbs = pl.path.join(strWorkingPath, strFileAbs)
              tLog.debug('Extending the relative path "%s" to "%s".', strFile, strFileAbs)
            end
            local strFileBase = pl.path.basename(strFile)
            if atFiles[strFileBase]==nil then
              if pl.path.exists(strFileAbs)~=strFileAbs then
                tLog.error('The path "%s" does not exist.', strFileAbs)
                fOk = false
              elseif pl.path.isfile(strFileAbs)~=true then
                tLog.error('The path "%s" does not point to a file.', strFileAbs)
                fOk = false
              else
                tLog.debug('Adding file "%s" to the list.', strFileAbs)
                atFiles[strFileBase] = strFileAbs
                table.insert(atSortedFiles, strFileAbs)
              end
            elseif atFiles[strFileBase]~=strFileAbs then
              tLog.error('Multiple files with the base name "%s" found.', strFileBase)
              fOk = false
            end
          end
        end
      end
      if fOk~=true then
        tLog.error('Not all files are OK. Stopping here.')
      else
        -- Create a new archive.
        local tArchive = archive.ArchiveWrite()
        local tFormat = archive.ARCHIVE_FORMAT_TAR_GNUTAR
        tArcResult = tArchive:set_format(tFormat)
        if tArcResult~=0 then
          tLog.error('Failed to set the archive format to ID %d: %s', tFormat, tArchive:error_string())
          fOk = false
        else
          local atFilter = { archive.ARCHIVE_FILTER_XZ }
          for _, tFilter in ipairs(atFilter) do
            tArcResult = tArchive:add_filter(tFilter)
            if tArcResult~=0 then
              tLog.error('Failed to add filter with ID %d: %s', tFilter, tArchive:error_string())
              fOk = false
              break
            end
          end

          local tTimeNow = os.time()
          local strWfpArchiveFile = tArgs.strWfpArchiveFile
          tArcResult = tArchive:open_filename(strWfpArchiveFile)
          if tArcResult~=0 then
            tLog.error('Failed to open the archive "%s": %s', strWfpArchiveFile, tArchive:error_string())
            fOk = false
          else
            for _, strFileAbs in ipairs(atSortedFiles) do
              local tEntry = archive.ArchiveEntry()
              tEntry:set_pathname(pl.path.basename(strFileAbs))
              local strData = pl.utils.readfile(strFileAbs, true)
              tEntry:set_size(string.len(strData))
              tEntry:set_filetype(archive.AE_IFREG)
              tEntry:set_perm(420)
              tEntry:set_gname('wfp')
--              tEntry:set_uname('wfp')
              tArchive:write_header(tEntry)
              tArchive:write_data(strData)
              tArchive:finish_entry()
            end
          end

          tArchive:close()
        end
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
