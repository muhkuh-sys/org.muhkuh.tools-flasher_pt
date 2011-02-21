
-- NOTE: This script uses the "bit" and "romloader_usb" lua libraries. Both
-- are part of the "Muhkuh" experimental distribution.

require("romloader_usb")
require("flasher")
require("muhkuh")
require("tester")
require("select_plugin")

FLASHER_PATH = "../targets/"
--FLASHER_PATH = "./"

--------------------------------------------------------------------------
--  callbacks
--------------------------------------------------------------------------

local progress_last_cnt
local progress_last_max
local progress_percent_step = 10
local function progress(cnt,max)
	if progress_last_max == nil or progress_last_cnt == nil -- first call to progress
		or progress_last_max ~= max or cnt < progress_last_cnt -- first call to progress in a new up/download
		or ((cnt - progress_last_cnt)*100/max) >= progress_percent_step then -- current up/download
			progress_last_cnt = cnt
			progress_last_max = max
			print(string.format("%d%% (%d/%d)", cnt*100/max, cnt, max))
	end
	return true
end

-- unused
local function callback(a,b)
	print(string.format(">'%s'", a))
	return true
end


--------------------------------------------------------------------------
-- handle command line arguments
--------------------------------------------------------------------------

MODE_FLASH = 1
MODE_DETECT = 32
MODE_HELP = 255

strUsage = [==[
Usage: 
flash a file:         lua flash.lua [plugin] [device] filename
detect flash devices: lua flash.lua [plugin] -d
show this help:       lua flash.lua -h

plugin: -p plugin_name
        example: -p romloader_usb_00_00
        
device: -b bus -u unit -cs chip_select
        example: -b 0 -u 0 -cs 0
        unit/chip select default to 0, 0

]==]


-- Evaluate command line arguments.
-- returns list of arguments or nil and error message.
-- Entries returned in aArgs:
-- iMode              MODE_FLASH/MODE_DETECT/MODE_HELP
-- strPluginName      plugin name
-- iBus               bus number
-- iUnit              unit number 
-- iChipSelect        chip selet number
-- strInputFile       input file name

function evalArg()
	local aArgs = {}
	local iMode
	local iArg = 1
	local nArgs = #arg
	
	if nArgs == 0 then
		aArgs.iMode = MODE_HELP
		return aArgs
	else
		aArgs.iMode = MODE_FLASH
		while (iArg <= nArgs) do
			local iRemArgs = nArgs - iArg + 1
			
			if arg[iArg] == "-h" and iRemArgs >= 1 then
				aArgs.iMode = MODE_HELP
				iArg = iArg + 1
				
			elseif arg[iArg] == "-d" and iRemArgs >= 1 then
				aArgs.iMode = MODE_DETECT
				iArg = iArg + 1
				
			elseif arg[iArg] == "-p" and iRemArgs >=2 then
				aArgs.strPluginName = arg[iArg+1]
				iArg = iArg + 2
				
			elseif arg[iArg] == "-b" and iRemArgs >=2 then
				aArgs.iBus  = tonumber(arg[iArg+1])
				if not aArgs.iBus then
					return nil, "Error parsing bus number (-b)"
				end
				iArg = iArg + 2
				
			elseif arg[iArg] == "-u" and iRemArgs >=2 then
				aArgs.iUnit  = tonumber(arg[iArg+1])
				if not aArgs.iUnit then
					return nil, "Error parsing unit number (-u)"
				end
				iArg = iArg + 2
				
			elseif arg[iArg] == "-cs" and iRemArgs >=2 then
				aArgs.iChipSelect  = tonumber(arg[iArg+1])
				if not aArgs.iChipSelect then
					return nil, "Error parsing chip select number (-cs)"
				end
				iArg = iArg + 2
				
			elseif iRemArgs == 1 then
				aArgs.strDataFileName = arg[iArg]
				iArg = iArg + 1
			else
				return nil, "Too many/unknown arguments"
			end
			
			
		end
		
		-- if bus number is specified, unit and chip select default to 0
		if aArgs.iBus then
			aArgs.iUnit = aArgs.iUnit or 0
			aArgs.iChipSelect = aArgs.iChipSelect or 0
		end
		
		if aArgs.iMode == MODE_FLASH and not aArgs.iBus then
			return nil, "Please specify the bus/unit/chip select number."
		end
		
		if aArgs.iMode == MODE_FLASH and not aArgs.strDataFileName then
			return nil, "Please specify the input file to flash."
		end
		return aArgs
	end
end

function show_args(aArgs)
	for k,v in pairs(aArgs) do 
		print(k,v)
	end
end

--------------------------------------------------------------------------
-- get plugin
--------------------------------------------------------------------------

function getPluginByName(strName)
	for iPluginClass, tPluginClass in ipairs(__MUHKUH_PLUGINS) do
		local iDetected
		local aDetectedInterfaces = {}
		print(string.format("Detecting interfaces with plugin %s", tPluginClass:GetID()))
		iDetected = tPluginClass:DetectInterfaces(aDetectedInterfaces)
		print(string.format("Found %d interfaces with plugin %s", iDetected, tPluginClass:GetID()))
		
		for i,v in ipairs(aDetectedInterfaces) do
			print(string.format("%d: %s (%s) Used: %s, Valid: %s", i, v:GetName(), v:GetTyp(), tostring(v:IsUsed()), tostring(v:IsValid())))
			if strName == v:GetName() then
				if not v:IsValid() then
					return nil, "Plugin is not valid"
				elseif v:IsUsed() then
					return nil, "Plugin is in use"
				else
					print("found plugin")
					local tPlugin = v:Create()
					if tPlugin then 
						tPlugin:Connect()
						return tPlugin
					else
						return nil, "Error creating plugin instance"
					end
				end
			end
		end
	end
	return nil, "plugin not found"
end

function getPlugin(strPluginName)
	local tPlugin, strError
	if strPluginName then
		-- get the plugin by name
		tPlugin, strError = getPluginByName(strPluginName)
	else
		-- Ask the user to pick a plugin.
		tPlugin = tester.getCommonPlugin()
		if tPlugin == nil then
			strError = "No plugin selected!"
		end
	end
	
	return tPlugin, strError
end


--------------------------------------------------------------------------
-- flash
--------------------------------------------------------------------------

function doFlash(tPlugin, args)
	local strDataFileName = args.strDataFileName
	
	local strDevDesc
	-- Download the flasher.
	print("Downloading flasher binary")
	aAttr = flasher.download(tPlugin, FLASHER_PATH, progress)

	-- check if the selected flash is present
	print("Detecting flash device")
	strDevDesc = flasher.detect(tPlugin, aAttr, args.iBus, args.iUnit, args.iChipSelect)
	
	if not strDevDesc then
		return false, "Failed to get a device description!"
	end

	-- Load the data.
	print("Loading data file")
	strData, msg = muhkuh.load(strDataFileName)
	if not strData then
		return false, "Failed to load binary '" .. strDataFileName .. "': " .. msg
	end

	-- Get the erase area.
	print("Erasing the area")
	local ulDataFirst, ulDataEnd, ulEraseFirst, ulEraseEnd
	ulDataFirst = 0x00000000
	ulDataEnd = ulDataFirst + string.len(strData)
	ulEraseFirst,ulEraseEnd = flasher.getEraseArea(tPlugin, aAttr, ulDataFirst, ulDataEnd)
	print(string.format("Area:  [0x%08x, 0x%08x[", ulDataFirst, ulDataEnd))
	print(string.format("Erase: [0x%08x, 0x%08x[", ulEraseFirst, ulEraseEnd))

	-- Make sure the area is erased.
	-- TODO: for serial flashes:
	-- if the flash has erase-and-program capability, we might skip this
	-- if the flash has neither PageErase nor EraseAndProgram,
	local fIsErased = flasher.isErased(tPlugin, aAttr, ulEraseStart, ulEraseEnd)
	if fIsErased==nil then
		return false, "Failed to check if the area is erased!"
	elseif fIsErased==true then
		print("!ALL CLEAN! The area is erased.")
	else
		print("!!!DIRTY!!! The area must be erased before flashing!")

		io.write("Press enter to start erasing >") io.read()
		
		fIsErased = flasher.erase(tPlugin, aAttr, ulEraseStart, ulEraseEnd)
		if fIsErased~=true then
			return false, "Failed to erase the area!"
		else
		
			io.write("Press enter to start erase check >") io.read()
			fIsErased = flasher.isErased(tPlugin, aAttr, ulEraseStart, ulEraseEnd)
			if fIsErased~=true then
				return false, "The flasher pretended to erase the area, but it is still dirty!"
			end
		end
	end


	io.write("Press enter to start flashing >") io.read()
	-- Loop over the complete data array and flash it in chunks.
	
	-- Was ist, wenn Puffergröße kein Vielfaches der Sektorgröße ist,
	-- das Binary größer als der Puffer ist
	-- und das Flash kein PageErase/EraseAndProgram kann?
	
	ulDataByteSize = strData:len()
	ulDataOffset = 0
	ulDeviceOffset = 0
	while ulDataOffset<ulDataByteSize do
		-- Extract the next chunk.
		strChunk = strData:sub(ulDataOffset+1, ulDataOffset+aAttr.ulBufferLen)
		ulChunkSize = strChunk:len()

		-- Download the chunk to the buffer.
		tPlugin:write_image(aAttr.ulBufferAdr, strChunk, progress, ulChunkSize)

		-- Flash the chunk.
		print(string.format("flashing offset 0x%08x-0x%08x.", ulDeviceOffset, ulDeviceOffset+ulChunkSize))
		fResult = flasher.flash(tPlugin, aAttr, ulDeviceOffset, ulChunkSize, aAttr.ulBufferAdr)
		if fResult==false or fResult==nil then
			return false, "Failed to flash data!"
		end

		-- Increase pointers.
		ulDataOffset = ulDataOffset + ulChunkSize
		ulDeviceOffset = ulDeviceOffset + ulChunkSize
	end

	return true, "image flashed"
end




--------------------------------------------------------------------------
--  device list/menu
--------------------------------------------------------------------------


function printobj(val, key, indent)
	key = key or ""
	indent = indent or ""
	
	if type(val)=="number" then
		print(string.format("%s%s = %d (number)", indent, key, val))
	elseif type(val)=="string" then
		print(string.format("%s%s = %s (string)", indent, key, val))
	elseif type(val)=="table" then
		local indent = indent .. "  "
		print(string.format("%s%s = {", indent, key))
		for k,v in pairs(val) do
			printobj(v, tostring(k), indent)
		end
		print(string.format("%s} -- %s", indent, key))
	end
end



function doDetect(tPlugin, aArgs)
	-- Download the flasher binary.
	aAttr = flasher.download(tPlugin, FLASHER_PATH, progress)
	
	-- Get the board info table.
	aBoardInfo = flasher.getBoardInfo(tPlugin, aAttr)
	print("Board info:")
	for iBusCnt,tBusInfo in ipairs(aBoardInfo) do
		print(string.format("Bus %d:\t%s", tBusInfo.iIdx, tBusInfo.strName))
		if not tBusInfo.aUnitInfo then
			print("\tNo units.")
		else
			for iUnitCnt,tUnitInfo in ipairs(tBusInfo.aUnitInfo) do
				print(string.format("\tUnit %d:\t%s", tUnitInfo.iIdx, tUnitInfo.strName))
			end
		end
		print("")
	end
	
	-- printobj(aBoardInfo)
	return true
end



--------------------------------------------------------------------------
--
--------------------------------------------------------------------------


local fOk = false
local args
local strMsg
local tPlugin

args, strMsg = evalArg()

if args == nil then
	if strMsg then
		print(strMsg)
	end
	print(strUsage)
	os.exit(1)
	
elseif args.iMode == MODE_HELP then
	print(strUsage)
	os.exit(0)
	
elseif args.iMode == MODE_FLASH then
	show_args(args)
	tPlugin, strMsg = getPlugin(args.strPluginName)
	if tPlugin then
		fOk, strMsg = doFlash(tPlugin, args)
		tPlugin:Disconnect()
		tPlugin = nil
	end
	
	if fOk then
		if strMsg then 
			print(strMsg)
		end
		os.exit(0)
	else
		print(strMsg or "an unknown error occurred")
		os.exit(1)
	end
	
elseif args.iMode == MODE_DETECT then
	tPlugin, strMsg = getPlugin(args.strPluginName)
	if tPlugin then
		fOk, strMsg = doDetect(tPlugin, args)
		tPlugin:Disconnect()
		tPlugin = nil
	end
	
	if fOk then
		if strMsg then 
			print(strMsg)
		end
		os.exit(0)
	else
		print(strMsg or "an unknown error occurred")
		os.exit(1)
	end
end

