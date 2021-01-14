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
if not tPlugin then
  error('No plugin selected, nothing to do!')
end

-- Download the binary.
local aAttr = tFlasher:download(tPlugin, 'netx/', _G.tester.progress)

-- Use SPI Flash CS0.
local fOk = tFlasher:detect(tPlugin, aAttr, tFlasher.BUS_Spi, 0, 0)
if not fOk then
  error('Failed to get a device description!')
end

-- Get the erase area for the range 0 .. 1.
local ulEraseStart, ulEraseEnd = tFlasher:getEraseArea(tPlugin, aAttr, 0, 1)
if not ulEraseStart then
  error('Failed to get erase areas!')
end
tLog.info('The first erase area is: 0x%08x-0x%08x', ulEraseStart, ulEraseEnd)

-- Check if the erase area is already clear.
local fIsErased
tLog.info('Is area 0x%08x-0x%08x already erased?', ulEraseStart, ulEraseEnd)
fIsErased = tFlasher:isErased(tPlugin, aAttr, ulEraseStart, ulEraseEnd)
if fIsErased==nil then
  error('failed to check the area!')
end


if fIsErased==true then
  tLog.info('The area is already erased.')
else
  tLog.info('The area is not erased. Erasing it now...')
  local fIsOk = tFlasher:erase(tPlugin, aAttr, ulEraseStart, ulEraseEnd)
  if not fIsOk then
    error('Failed to erase the area!')
  end
  tLog.info('Erase finished!')

  fIsErased = tFlasher:isErased(tPlugin, aAttr, ulEraseStart, ulEraseEnd)
  if not fIsErased then
    error('No error reported, but the area is not erased!')
  end
  tLog.info('The first erase area is clear now!')
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

-- Disconnect the plugin.
_G.tester:closeCommonPlugin()
