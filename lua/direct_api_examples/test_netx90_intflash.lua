require("muhkuh_cli_init")
require("flasher")

function printf(...) print(string.format(...)) end

function rndData(iLen)
	local ac = {}
	for i=1, iLen do
		local b = math.random(0, 255)
		local c = string.char(b)
		table.insert(ac, c)
	end
	return table.concat(ac)
end

atTestBlocks = {
	{u=0, cs=0, data=rndData(0x80000)},
	{u=2, cs=1, data=rndData(0x1000)},
	{u=1, cs=0, data=rndData(0x80000)},
	{u=0, cs=1, data=rndData(0x1000)},
	{u=2, cs=0, data=rndData(0x80000)},
	{u=1, cs=1, data=rndData(0x1000)},
}

tPlugin = tester.getCommonPlugin()
if not tPlugin then
	error("No plugin selected, nothing to do!")
end

-- Download the binary.
local aAttr = flasher.download(tPlugin, "netx/", tester.progress)

for _i, tBlock in ipairs(atTestBlocks) do
	local iUnit = tBlock.u
	local iCS = tBlock.cs
	local strData = tBlock.data
	local iLen = strData:len()
	local ulDeviceOffset = 0

	printf("Detecting unit %d cs %d", iUnit, iCS)
	local fOk = flasher.detect(tPlugin, aAttr, flasher.BUS_IFlash, iUnit, iCS)
	if not fOk then
		error("Failed to get a device description!")
	end

	printf("Get erase area %d cs %d", iUnit, iCS)
	local ulEraseStart, ulEraseEnd = flasher.getEraseArea(tPlugin, aAttr, ulDeviceOffset, iLen)
	if not ulEraseStart then
		error("Failed to get erase areas!")
	end
	print(string.format("The first erase area is: 0x%08x-0x%08x", ulEraseStart, ulEraseEnd))

	print("Erase")
	local fIsOk = flasher.erase(tPlugin, aAttr, ulEraseStart, ulEraseEnd)
	if not fIsOk then
		error("Failed to erase the area!")
	end
	print("Erase finished!")

	fIsErased = flasher.isErased(tPlugin, aAttr, ulEraseStart, ulEraseEnd)
	if not fIsErased then
		error("No error reported, but the area is not erased!")
	end
	print("The first erase area is clear now!")

	fOk, strMsg = flasher.flashArea(tPlugin, aAttr, ulDeviceOffset, strData)
	print(strMsg)
	assert(fOk, strMsg or "Error while erasing area")

end


for _i, tBlock in ipairs(atTestBlocks) do
	local iUnit = tBlock.u
	local iCS = tBlock.cs
	local strData = tBlock.data
	local iLen = strData:len()
	local ulDeviceOffset = 0
	
	printf("Reading back: unit %d cs %d", iUnit, iCS)
	print("Detecting")
	local fOk = flasher.detect(tPlugin, aAttr, flasher.BUS_IFlash, iUnit, iCS)
	if not fOk then
		error("Failed to get a device description!")
	end
	
	local strRead, strMessage = flasher.readArea(tPlugin, aAttr, ulDeviceOffset, iLen)
	if not strRead then
		error("Failed to read: " .. strMessage)
	end 
	
	if strRead == strData then
		print("verify OK")
	else
		error("verify failed")
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

-- Disconnect the plugin.
tester.closeCommonPlugin()

