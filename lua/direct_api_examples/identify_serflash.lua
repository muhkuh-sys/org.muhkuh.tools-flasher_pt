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

local tPlugin = _G.tester:getCommonPlugin()
if tPlugin==nil then
  error('No plugin selected, nothing to do!')
end

-- Download the binary.
local aAttr = tFlasher:download(tPlugin, 'netx/', _G.tester.progress)

-- Use SPI Flash CS0.
local tBus = tFlasher.BUS_Spi
local ulUnit = 0
local ulChipSelect = 0
local fOk = tFlasher:detect(tPlugin, aAttr, tBus, ulUnit, ulChipSelect)
if not fOk then
  error('Failed to get a device description!')
end

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
