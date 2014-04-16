require("flasher")

tPlugin = tester.getCommonPlugin()
if tPlugin==nil then
	error("No plugin selected, nothing to do!")
end

-- Download the binary.
local aAttr = flasher.download(tPlugin, "netx/", tester.progress)

local fOk

-- Use SPI Flash CS0.
ulUnit = 0
ulChipSelect = 0
ulSpeed_kHz = 1000
fOk = flasher.sdi_init(tPlugin, aAttr, ulUnit, ulChipSelect, ulSpeed_kHz)
assert(fOk, "Failed to init the SPI macro interface!")

-- Initialize the bus.
fOk = flasher.sdi_chip_select(tPlugin, aAttr, 0)
assert(fOk, "Failed to set CS to 0.")

fOk = flasher.sdi_idle_bytes(tPlugin, aAttr, 8)
assert(fOk, "Failed to send 8 idle bytes.")

fOk = flasher.sdi_chip_select(tPlugin, aAttr, 1)
assert(fOk, "Failed to set CS to 1.")

strData = string.char(0x9f)
fOk = flasher.sdi_send_data(tPlugin, aAttr, strData)
assert(fOk, "Failed to send data.")

strID = flasher.sdi_receive_data(tPlugin, aAttr, 3)
assert(strID, "Failed to receive data.")

fOk = flasher.sdi_chip_select(tPlugin, aAttr, 0)
assert(fOk, "Failed to set CS to 0.")

fOk = flasher.sdi_idle_bytes(tPlugin, aAttr, 1)
assert(fOk, "Failed to send 1 idle bytes.")


print("The JEDEC ID of the device is:")
tester.hexdump(strID, 16)


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
