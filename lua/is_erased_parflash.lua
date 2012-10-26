require("flasher")

tPlugin = tester.getCommonPlugin()
if not tPlugin then
	error("No plugin selected, nothing to do!")
end

-- Download the binary.
local aAttr = flasher.download(tPlugin, "netx/", progress)

-- Use parallel flash on unit 0, chipselect 0.
strDevDesc = flasher.detect(tPlugin, aAttr, flasher.BUS_Parflash, 0, 0, ulDevDescAdr)
if strDevDesc==nil then
	error("Failed to get a device description!")
end

-- Get erase area.
local ulDataFirst, ulDataEnd, ulEraseFirst, ulEraseEnd
ulDataFirst = 0x00020080
ulDataEnd = 0x00021000
ulEraseFirst,ulEraseEnd = flasher.getEraseArea(tPlugin, aAttr, ulDataFirst, ulDataEnd)
if ulEraseFirst==nil or ulEraseEnd==nil then
	error("Failed to get the erase area!")
end
print(string.format("Area:  [0x%08x, 0x%08x[", ulDataFirst, ulDataEnd))
print(string.format("Erase: [0x%08x, 0x%08x[", ulEraseFirst, ulEraseEnd))

-- Check if the area is erased.
local fIsErased
fIsErased = flasher.isErased(tPlugin, aAttr, ulEraseStart, ulEraseEnd)
if fIsErased==nil then
	error("Failed to check if the area is erased!")
elseif fIsErased==true then
	print("!ALL CLEAN! The area is erased.")
else
	print("!!!DIRTY!!! The area must be erased before flashing!")
end

-- disconnect the plugin
tPlugin:Disconnect()
