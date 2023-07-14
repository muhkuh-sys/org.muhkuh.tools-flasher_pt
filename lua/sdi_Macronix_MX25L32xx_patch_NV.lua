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


local function sdi_init_bus(tFlasher, tPlugin, aAttr)
  -- Initialize the bus.
  local fOk = tFlasher:sdi_chip_select(tPlugin, aAttr, 0)
  assert(fOk, "Failed to set CS to 0.")

  fOk = tFlasher:sdi_idle_bytes(tPlugin, aAttr, 8)
  assert(fOk, "Failed to send 8 idle bytes.")
end



local function sdi_read_JEDEC_ID(tFlasher, tPlugin, aAttr)
  local strID


  local fOk = tFlasher:sdi_chip_select(tPlugin, aAttr, 1)
  assert(fOk, "Failed to set CS to 1.")

  local strData = string.char(0x9f)
  fOk = tFlasher:sdi_send_data(tPlugin, aAttr, strData)
  assert(fOk, "Failed to send data.")

  strID = tFlasher:sdi_receive_data(tPlugin, aAttr, 3)
  assert(strID, "Failed to receive data.")

  fOk = tFlasher:sdi_chip_select(tPlugin, aAttr, 0)
  assert(fOk, "Failed to set CS to 0.")

  fOk = tFlasher:sdi_idle_bytes(tPlugin, aAttr, 1)
  assert(fOk, "Failed to send 1 idle bytes.")

  return strID
end



local function sdi_send_write_enable(tFlasher, tPlugin, aAttr)
  local fOk = tFlasher:sdi_chip_select(tPlugin, aAttr, 1)
  assert(fOk, "Failed to set CS to 1.")

  local strData = string.char(0x06)
  fOk = tFlasher:sdi_send_data(tPlugin, aAttr, strData)
  assert(fOk, "Failed to send data.")

  fOk = tFlasher:sdi_chip_select(tPlugin, aAttr, 0)
  assert(fOk, "Failed to set CS to 0.")

  fOk = tFlasher:sdi_idle_bytes(tPlugin, aAttr, 1)
  assert(fOk, "Failed to send 1 idle bytes.")
end



local function sdi_read_status_register(tFlasher, tPlugin, aAttr)
  local strRX


  local fOk = tFlasher:sdi_chip_select(tPlugin, aAttr, 1)
  assert(fOk, "Failed to set CS to 1.")

  local strData = string.char(0x05)
  fOk = tFlasher:sdi_send_data(tPlugin, aAttr, strData)
  assert(fOk, "Failed to send data.")

  strRX = tFlasher:sdi_receive_data(tPlugin, aAttr, 1)
  assert(strRX, "Failed to receive data.")

  fOk = tFlasher:sdi_chip_select(tPlugin, aAttr, 0)
  assert(fOk, "Failed to set CS to 0.")

  fOk = tFlasher:sdi_idle_bytes(tPlugin, aAttr, 1)
  assert(fOk, "Failed to send 1 idle bytes.")

  return string.byte(strRX)
end



local function sdi_wait_for_not_busy(tFlasher, tPlugin, aAttr)
  repeat
    local ulStatus = sdi_read_status_register(tFlasher, tPlugin, aAttr)
    ulStatus = ulStatus & 1
  until ulStatus==0
end



local function sdi_write_status_register(tFlasher, tPlugin, aAttr, ucData)
  sdi_send_write_enable(tPlugin, aAttr)

  local fOk = tFlasher:sdi_chip_select(tPlugin, aAttr, 1)
  assert(fOk, "Failed to set CS to 1.")

  local strData = string.char(0x01, ucData)
  fOk = tFlasher:sdi_send_data(tPlugin, aAttr, strData)
  assert(fOk, "Failed to send data.")

  fOk = tFlasher:sdi_chip_select(tPlugin, aAttr, 0)
  assert(fOk, "Failed to set CS to 0.")

  fOk = tFlasher:sdi_idle_bytes(tPlugin, aAttr, 1)
  assert(fOk, "Failed to send 1 idle bytes.")

  sdi_wait_for_not_busy(tPlugin, aAttr)
end



tPlugin = _G.tester:getCommonPlugin()
if tPlugin==nil then
  error("No plugin selected, nothing to do!")
end

-- Download the binary.
local aAttr = tFlasher:download(tPlugin, "netx/", tester.progress)

local fOk

-- Use SPI Flash CS0.
ulUnit = 0
ulChipSelect = 0
ulSpeed_kHz = 1000
fOk = tFlasher:sdi_init(tPlugin, aAttr, ulUnit, ulChipSelect, ulSpeed_kHz)
assert(fOk, "Failed to init the SPI macro interface!")

sdi_init_bus(tFlasher, tPlugin, aAttr)
strID = sdi_read_JEDEC_ID(tFlasher, tPlugin, aAttr)
print(string.format('JEDEC ID: %02x %02x %02x', string.byte(strID, 1, 3)))

if strID~=string.char(0xc2, 0x20, 0x18) then
  error("The JEDEC ID does not match the Macronix M25L32xx.")
end

print("The JEDEC ID of the device is correct!")


ucStatus_Goal = 0x40

-- Read the status register.
ucStatus_Current = sdi_read_status_register(tFlasher, tPlugin, aAttr)
print(string.format("Status register: 0x%02x", ucStatus_Current))

if ucStatus_Current==ucStatus_Goal then
  print("The chip is already patched!")
else
  sdi_write_status_register(tFlasher, tPlugin, aAttr, ucStatus_Goal)

  ucData = sdi_read_status_register(tFlasher, tPlugin, aAttr)
  if ucData~=ucStatus_Goal then
    error("Status register not written!")
  end
end

print("")
print(" #######  ##    ## ")
print("##     ## ##   ##  ")
print("##     ## ##  ##   ")
print("##     ## #####    ")
print("##     ## ##  ##   ")
print("##     ## ##   ##  ")
print(" #######  ##    ## ")
print("")

-- disconnect the plugin
tPlugin:Disconnect()
