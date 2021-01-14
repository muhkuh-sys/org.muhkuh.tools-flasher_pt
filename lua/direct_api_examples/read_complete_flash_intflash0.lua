require 'muhkuh_cli_init'

local tLogWriter = require 'log.writer.console.color'.new()
local tLog = require 'log'.new(
  'debug',
  tLogWriter,
  require 'log.formatter.format'.new()
)

-- Register the CLI tester.
_G.tester = require 'tester_cli'(tLog)
-- Ask the user to select a plugin.
_G.tester.fInteractivePluginSelection = true

local tFlasher = require 'flasher'(tLog)

if #arg~=1 then
	error('Missing parameter: image file name.')
end
local strFileName = arg[1]

local tPlugin = _G.tester:getCommonPlugin()
if tPlugin==nil then
  error('No plugin selected, nothing to do!')
end

-- Download the binary.
local aAttr = tFlasher:download(tPlugin, 'netx/', _G.tester.progress)

-- Use INTFLASH0.
local tBus = tFlasher.BUS_IFlash
local ulUnit = 0
local ulChipSelect = 0
local fOk = tFlasher:detect(tPlugin, aAttr, tBus, ulUnit, ulChipSelect)
if not fOk then
  error('Failed to get a device description!')
end

-- Get the complete devicesize.
local ulFlashSize = tFlasher:getFlashSize(tPlugin, aAttr, tester.callback, _G.tester.callback_progress)
tLog.info('The device size is: 0x%08x', ulFlashSize)

-- Read the complete flash.
local strFlashContents, strMessage = tFlasher:readArea(tPlugin, aAttr, 0, ulFlashSize, tester.callback, tester.callback_progress)
if not strFlashContents then
  error('Failed to read the flash: ' .. strMessage)
end

-- Save the flash contents.
local tFile, strMsg = io.open(strFileName, 'wb')
if not tFile then
  error('Failed to open file ' .. strFileName .. ' for writing: ' .. strMsg)
end

tFile:write(strFlashContents)
tFile:close()

tLog.info('')
tLog.info(' #######  ##    ## ')
tLog.info('##     ## ##   ##  ')
tLog.info('##     ## ##  ##   ')
tLog.info('##     ## #####    ')
tLog.info('##     ## ##  ##   ')
tLog.info('##     ## ##   ##  ')
tLog.info(' #######  ##    ## ')
tLog.info('')

-- disconnect the plugin
tPlugin:Disconnect()
