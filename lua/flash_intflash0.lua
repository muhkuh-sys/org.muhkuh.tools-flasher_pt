require 'muhkuh_cli_init'

local tLogWriter = require 'log.writer.console.color'.new()
local tLog = require "log".new(
  'debug',
  tLogWriter,
  require "log.formatter.format".new()
)

_G.tester = require 'tester_cli'(tLog)
-- Ask the user to select a plugin.
_G.tester.fInteractivePluginSelection = true

if #arg~=1 then
	error("Missing parameter: file to flash.")
end
strFileName = arg[1]


local tFlasher = require 'flasher'(tLog)

tPlugin = tester:getCommonPlugin()
if tPlugin==nil then
  error("No plugin selected, nothing to do!")
end


-- Flash the file.
local tBus = tFlasher.BUS_IFlash
local ulUnit = 0
local ulChipSelect = 0
tFlasher:simple_flasher(tPlugin, strFileName, tBus, ulUnit, ulChipSelect, "netx/")

tLog.info("")
tLog.info(" #######  ##    ## ")
tLog.info("##     ## ##   ##  ")
tLog.info("##     ## ##  ##   ")
tLog.info("##     ## #####    ")
tLog.info("##     ## ##  ##   ")
tLog.info("##     ## ##   ##  ")
tLog.info(" #######  ##    ## ")
tLog.info("")

-- disconnect the plugin
tPlugin:Disconnect()
