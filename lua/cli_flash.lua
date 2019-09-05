-----------------------------------------------------------------------------
-- Copyright (C) 2017 Hilscher Gesellschaft für Systemautomation mbH
--
-- Description:
--   cli_flash.lua: command line flasher tool
--
-----------------------------------------------------------------------------
-----------------------------------------------------------------------------
-- SVN Keywords
SVN_DATE   ="$Date$"
SVN_VERSION="$Revision$"
SVN_AUTHOR ="$Author$"
-----------------------------------------------------------------------------

FLASHER_PATH = "netx/"

require("muhkuh_cli_init")

-- flasher-related
require("mhash")
require("flasher")
require("flasher_test")


--------------------------------------------------------------------------
-- Usage
--------------------------------------------------------------------------

strUsage = [==[
Usage: lua cli_flash.lua mode parameters
        
Mode        Parameters                                                  
flash       [p] dev [offset]      file   Write file to flash    
read        [p] dev [offset] size file   Read flash and write to file      
erase       [p] dev [offset] size        Erase area or whole flash       
verify      [p] dev [offset]      file   Byte-by-byte compare
verify_hash [p] dev [offset]      file   Quick compare using checksums
hash        [p] dev [offset] size        Compute SHA1
info        [p]                          Show busses/units/chip selects
detect      [p] dev                      Check if flash is recognized
test        [p] dev                      Test flasher      
testcli     [p] dev                      Test cli flasher  
list_interfaces                          List all usable interfaces
detect_netx [p]                          Detect the netx chip type
-h                                       Show this help    
        
p:    -p plugin_name
      select plugin
      example: -p romloader_usb_00_01
        
dev:  -b bus [-u unit -cs chip_select]
      select flash device
      default: -u 0 -cs 0
       
off:  -s device_start_offset
      offset in the flash device, defaults to 0
       
size: -l length
      number of bytes to read/erase/hash
      read/erase: 0xffffffff = from offset to end of chip

                        
Examples:

Write file to serial flash:
lua cli_flash.lua flash -b 1 NETX100-BSL.bin

Erase boot cookie from serial flash:
lua cli_flash.lua erase -b 1 -l 4 

Erase boot cookie from parallel flash:
lua cli_flash.lua erase -b 0 -l 4

]==]

--------------------------------------------------------------------------
-- helpers
--------------------------------------------------------------------------

-- strData, strMsg loadBin(strFilePath)
-- Load a binary file.
-- returns 
--   data if successful 
--   nil, message if an error occurred
function loadBin(strFilePath)
	local strData
	local tFile
	local strMsg
	
	tFile, strMsg = io.open(strFilePath, "rb")
	if tFile then
		strData = tFile:read("*a")
		tFile:close()
		if strData == nil then
			strMsg = string.format("Could not read from file %s", strFilePath)
		end
	else
		strMsg = string.format("Could not open file %s: %s", strFilePath, strMsg or "Unknown error")
	end
	return strData, strMsg
end


-- fOk, strMsg writeBin(strName, strBin)
-- Write string to binary file.
-- returns true or false, message
function writeBin(strName, bin)
	local f, msg = io.open(strName, "wb")
	if f then 
		f:write(bin)
		f:close()
		return true, string.format("%d bytes written to file %s", bin:len(), strName)
	else
		print("Failed to open file for writing")
		return false, msg
	end
end

-- get hex representation (no spaces) of a byte string
function getHexString(strBin)
	local strHex = ""
	for i=1, strBin:len() do
		strHex = strHex .. string.format("%02x", strBin:byte(i))
	end
	return strHex
end


function printf(...) print(string.format(...)) end

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
		tPlugin = select_plugin.SelectPlugin()
		if tPlugin == nil then
			strError = "No plugin selected!"
		end
	end
	
	return tPlugin, strError
end


function printf(...) print(string.format(...)) end
function list_interfaces()
	-- detect all interfaces
	local aDetectedInterfaces = {}
	for iPluginClass, tPluginClass in ipairs(__MUHKUH_PLUGINS) do
		tPluginClass:DetectInterfaces(aDetectedInterfaces)
	end
	-- filter used and non valid interfaces
	local aUnusedInterfaces = {}
	for i,v in ipairs(aDetectedInterfaces) do
		if not v:IsUsed() and v:IsValid() then
				table.insert(aUnusedInterfaces, v)
		end
	end
	-- output of not used and valid interfaces
	print()
	printf("START LIST NOT USED INTERFACES (%d Interfaces found)", #aUnusedInterfaces)
	print()
	for i, v in ipairs(aUnusedInterfaces) do
		printf("%d : Name:%-30s Typ: %-25s", i, v:GetName(), v:GetTyp())
	end
	print()
	print("END LIST INTERFACES")
end



function detect_chiptype(aArgs)
	local strPluginName  = aArgs.strPluginName
	local fOk = false
	local tPlugin, strMsg = getPlugin(strPluginName)
	if tPlugin then
		tPlugin:Connect()
		
		local iChiptype = tPlugin:GetChiptyp()
		if iChiptype then
			local strChipName = tPlugin:GetChiptypName(iChiptype)
			print("")
			printf("Chip type: (%d) %s", iChiptype, strChipName)
			print("")
			fOk = true
		else
			strMsg = "Failed to get chip type"
		end -- if iChiptype
	else
		strMsg = strMsg or "Could not connect to device"
	end -- if tPlugin
	
	return fOk, strMsg
end


--------------------------------------------------------------------------
-- handle command line arguments
--------------------------------------------------------------------------

MODE_FLASH = 0
MODE_READ = 2
MODE_VERIFY = 3
MODE_ERASE = 4
MODE_HASH = 5
MODE_DETECT = 6
MODE_VERIFY_HASH = 7
MODE_INFO = 8
MODE_HELP = 10
MODE_LIST_INTERFACES = 15
MODE_DETECT_CHIPTYPE = 16

-- test modes
MODE_TEST = 11
MODE_TEST_CLI = 12

-- used by test modes
MODE_IS_ERASED = 13
MODE_GET_DEVICE_SIZE = 14


arg2Mode = {
	flash       	= MODE_FLASH,
	read        	= MODE_READ,
	erase      		= MODE_ERASE,
	verify      	= MODE_VERIFY,
	verify_hash 	= MODE_VERIFY_HASH,
	hash        	= MODE_HASH,
	detect      	= MODE_DETECT,
	test        	= MODE_TEST,
	testcli     	= MODE_TEST_CLI,
	info        	= MODE_INFO,
	list_interfaces = MODE_LIST_INTERFACES,
	detect_netx     = MODE_DETECT_CHIPTYPE,
	["-h"]      	= MODE_HELP
}


argdefs = {
b  = {type = "number", clkey ="-b",  argkey = "iBus",              name="bus number"},
u  = {type = "number", clkey ="-u",  argkey = "iUnit",             name="unit number"},
cs = {type = "number", clkey ="-cs", argkey = "iChipSelect",       name="chip select number"},
p  = {type = "string", clkey ="-p",  argkey = "strPluginName",     name="plugin name"},
s  = {type = "number", clkey ="-s",  argkey = "ulStartOffset",     name="start offset"},
l  = {type = "number", clkey ="-l",  argkey = "ulLen",             name="number of bytes to read/erase/hash"},
f  = {type = "string", clkey = "",   argkey = "strDataFileName",   name="file name"}
}

requiredargs = {
[MODE_FLASH]        = {"b", "u", "cs", "f"},
[MODE_READ]         = {"b", "u", "cs", "f", "l"},
[MODE_VERIFY]       = {"b", "u", "cs", "f"},
[MODE_ERASE]        = {"b", "u", "cs", "l"},
[MODE_VERIFY_HASH]  = {"b", "u", "cs", "f"},
[MODE_HASH]         = {"b", "u", "cs"},
[MODE_DETECT]       = {"b", "u", "cs"},
[MODE_INFO]         = {},
[MODE_TEST]         = {"b", "u", "cs"},
[MODE_TEST_CLI]     = {"b", "u", "cs"},
[MODE_HELP]         = {},
[MODE_LIST_INTERFACES] = {},
[MODE_DETECT_CHIPTYPE] = {}
}

function checkArgs(aArgs)
	-- get the list of required/optional args for mode
	local required = requiredargs[aArgs.iMode]
	if not required then
		print("unknown mode!")
		return false
	end
	
	local fOk = true
	
	for i, strKey in pairs(required) do
		local argdef = argdefs[strKey]
		if not aArgs[argdef.argkey] then
			printf("please specify %s (%s)", argdef.name, argdef.clkey)
			fOk = false
		end
	end
		
	return fOk
end


function parseArg(aArgs, strKey, strVal)
	local iVal
	local tArgdef
	
	for k,argdef in pairs(argdefs) do
		if strKey == argdef.clkey then
			tArgdef = argdef
			break
		end
	end
	
	if not tArgdef then
		return false, string.format("Unknown argument: %s", strKey)
		
	elseif strVal == nil then
		return false, string.format("argument to %s is missing", strKey)
		
	elseif tArgdef.type == "string" then
		aArgs[tArgdef.argkey] = strVal
		return true
		
	elseif tArgdef.type == "number" then
		iVal = tonumber(strVal)
		if iVal then
			aArgs[tArgdef.argkey] = iVal
			return true
		else
			return false, string.format("Error parsing %s (%s)", tArgdef.name, tArgdef.clkey)
		end
	end
end


-- Evaluate command line arguments.
-- returns list of arguments or nil and error message.
-- Entries returned in aArgs:
-- iMode              MODE_FLASH etc.
-- strPluginName      plugin name
-- iBus               bus number
-- iUnit              unit number 
-- iChipSelect        chip selet number
-- ulStartOffset      start offset for read
-- ulLen              number of bytes to read
-- strDataFileName    input/output file name


function evalArg()
	local aArgs = {}
	local nArgs = #arg
	local iArg = 2
	
	-- First arg is the mode.
	-- If no args are given, set help mode
	if nArgs == 0 then
		aArgs.iMode = MODE_HELP
		return aArgs
	elseif arg[1] and arg2Mode[arg[1]] then 
		aArgs.iMode = arg2Mode[arg[1]]
	else
		return nil
	end

	-- Parse the arguments.
	-- The last argument may be the file name and has no key.
	while (iArg <= nArgs) do
		local strKey = arg[iArg]
		local strVal = arg[iArg+1]
		local fOk, strMsg = parseArg(aArgs, strKey, strVal)
		
		if fOk then
			iArg = iArg + 2
		elseif iArg == nArgs then
			aArgs.strDataFileName = arg[iArg]
			iArg = iArg + 1
		else
			return nil, strMsg
		end
	end
		
	-- Add defaults
	aArgs.iUnit = aArgs.iUnit or 0
	aArgs.iChipSelect = aArgs.iChipSelect or 0
	aArgs.ulStartOffset = aArgs.ulStartOffset or 0
	
	-- Check if all necessary args for the mode are present.
	if checkArgs(aArgs) then
		return aArgs
	else
		return nil
	end
end


function show_args(aArgs)
	for k,v in pairs(aArgs) do 
		print(k,v)
	end
end

--------------------------------------------------------------------------
--  board info
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


function printBoardInfo(tBoardInfo)
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
end


---------------------------------------------------------------------------------------
--                   Execute flash operation
---------------------------------------------------------------------------------------


--                  info   detect   flash   verify   erase   read   hash   verify_hash
---------------------------------------------------------------------------------------
-- open plugin        x       x       x       x        x      x       x         x     
-- load flasher       x       x       x       x        x      x       x         x     
-- download flasher   x       x       x       x        x      x       x         x     
-- info               x
-- detect                     x       x       x        x      x       x         x
-- load data file                     x       x                                 x
-- eraseArea                          x                x
-- flashArea                          x
-- verifyArea                                 x
-- readArea                                                   x
-- SHA over data file                                                           x
-- SHA over flash                                                     x         x
-- save file                                                  x

function exec(aArgs)
	local iMode          = aArgs.iMode
	local strPluginName  = aArgs.strPluginName
	local iBus           = aArgs.iBus
	local iUnit          = aArgs.iUnit
	local iChipSelect    = aArgs.iChipSelect
	local ulStartOffset  = aArgs.ulStartOffset
	local ulLen          = aArgs.ulLen
	local strDataFileName= aArgs.strDataFileName
	
	local tPlugin
	local aAttr
	local strData
	local fOk
	local strMsg
	
	local strFileHashBin, strFlashHashBin
	local strFileHash , strFlashHash
	
	-- open the plugin
	tPlugin, strMsg = getPlugin(strPluginName)
	if tPlugin then
		tPlugin:Connect()
		fOk = true
		
		-- load input file  strDataFileName --> strData
		if fOk and (iMode == MODE_FLASH or iMode == MODE_VERIFY or iMode == MODE_VERIFY_HASH) then
			print("Loading data file")
			strData, strMsg = loadBin(strDataFileName)
			if not strData then
				fOk = false
			else
				ulLen = strData:len()
			end
		end
		
		-- Download the flasher.
		if fOk then
			print("Downloading flasher binary")
			aAttr = flasher.download(tPlugin, FLASHER_PATH)
			if not aAttr then
				fOk = false
				strMsg = "Error while downloading flasher binary"
			end
		end
		
		if fOk then 
			if iMode == MODE_INFO then
				-- Get the board info table.
				aBoardInfo = flasher.getBoardInfo(tPlugin, aAttr)
				if aBoardInfo then
					printBoardInfo(aBoardInfo)
					fOk = true
				else
					fOk = false
					strMsg = "Failed to read board info"
				end
	
			else
				-- check if the selected flash is present
				print("Detecting flash device")
				fOk = flasher.detect(tPlugin, aAttr, iBus, iUnit, iChipSelect)
				if not fOk then
					fOk = false
					strMsg = "Failed to get a device description!"
				end
			end
		end
		
		-- flash/erase: erase the area
		--if fOk and (iMode == MODE_FLASH or iMode == MODE_ERASE) then
		-- Explicit erase is not necessary when flashing SDIO
		if fOk and (iMode == MODE_ERASE or (iMode == MODE_FLASH and iBus ~= flasher.BUS_SDIO))then
			fOk, strMsg = flasher.eraseArea(tPlugin, aAttr, ulStartOffset, ulLen)
		end
		
		-- flash: flash the data
		if fOk and iMode == MODE_FLASH then
			fOk, strMsg = flasher.flashArea(tPlugin, aAttr, ulStartOffset, strData)
		end
		
		-- verify
		if fOk and iMode == MODE_VERIFY then
			fOk, strMsg = flasher.verifyArea(tPlugin, aAttr, ulStartOffset, strData)
		end
		
		-- read
		if fOk and iMode == MODE_READ then
			strData, strMsg = flasher.readArea(tPlugin, aAttr, ulStartOffset, ulLen)
			if strData == nil then
				fOk = false
				strMsg = strMsg or "Error while reading"
			end
		end
		
		-- for test mode
		if fOk and iMode == MODE_TEST then
			flasher_test.flasher_interface:configure(tPlugin, FLASHER_PATH, iBus, iUnit, iChipSelect)
			fOk, strMsg = flasher_test.testFlasher()
		end
		
		-- for test mode
		if fOk and iMode == MODE_IS_ERASED then
			local fOk = flasher.isErased(tPlugin, aAttr, ulStartOffset, ulStartOffset + ulLen)
			strMsg = fOk and "Area is empty" or "Area is not empty"
		end
		
		-- for test mode
		if fOk and iMode == MODE_GET_DEVICE_SIZE then
			ulLen = flasher.getFlashSize(tPlugin, aAttr)
			if ulLen == nil then
				fOk = false
				strMsg = "Failed to get device size"
			end
		end
		
		
		-- hash, verify_hash: compute the SHA1 of the data in the flash
		if fOk and (iMode == MODE_HASH or iMode == MODE_VERIFY_HASH) then
			strFlashHashBin, strMsg = flasher. hashArea(tPlugin, aAttr, ulStartOffset, ulLen)
			if strFlashHashBin then
				fOk = true
				strFlashHash = getHexString(strFlashHashBin)
				print("Flash SHA1: " .. strFlashHash)
			else
				fOk = false
				strMsg = strMsg or "Could not compute the hash sum of the flash contents"
			end
		end
		
		
		-- verify_hash: compute the hash of the input file and compare
		if fOk and iMode == MODE_VERIFY_HASH then
			local mh = mhash.mhash_state()
			mh:init(mhash.MHASH_SHA1)
			mh:hash(strData)
			strFileHashBin = mh:hash_end()
			strFileHash = getHexString(strFileHashBin)
			print("File SHA1: " .. strFileHash)

			if strFileHashBin == strFlashHashBin then
				print("Checksums are equal!")
				fOk = true
				strMsg = "The data in the flash and the file have the same checksum"
			else
				print("Checksums are not equal!")
				fOk = true
				strMsg = "The data in the flash and the file do not have the same checksum"
			end
		end
	
		-- save output file   strData --> strDataFileName
		if fOk and iMode == MODE_READ then
			fOk, strMsg = writeBin(strDataFileName, strData)
		end
		
		tPlugin:Disconnect()
		tPlugin = nil
	end
	
	if iMode == MODE_GET_DEVICE_SIZE then
		return ulLen, strMsg
	else
		return fOk, strMsg
	end
end



--========================================================================
--                    test interface
--========================================================================

flasher_interface = {}

function flasher_interface.configure(self, strPluginName, iBus, iUnit, iChipSelect)
	self.aArgs = {
		strPluginName = strPluginName,
		iBus = iBus,
		iUnit = iUnit,
		iChipSelect = iChipSelect,
		strDataFileName = "flashertest.bin"
		}
end


function flasher_interface.init(self)
	return true
end


function flasher_interface.finish(self)
end


function flasher_interface.getDeviceSize(self)
	self.aArgs.iMode = MODE_GET_DEVICE_SIZE
	return exec(self.aArgs)
end


-- bus 0: parallel, bus 1: serial
function flasher_interface.getBusWidth(self)
	if self.aArgs.iBus==flasher.BUS_Parflash then
		return 2 -- may be 1, 2 or 4
	elseif self.aArgs.iBus==flasher.BUS_Spi then
		return 1
	elseif self.aArgs.iBus==flasher.BUS_IFlash then
		return 4
	elseif self.aArgs.iBus == flasher.BUS_SDIO then
		return 1
	end
end

function flasher_interface.getEmptyByte(self)
	if self.aArgs.iBus == flasher.BUS_Parflash then
		return 0xff
	elseif self.aArgs.iBus == flasher.BUS_Spi then
		return 0xff
	elseif self.aArgs.iBus == flasher.BUS_IFlash then
		return 0xff
	elseif self.aArgs.iBus == flasher.BUS_SDIO then
		return 0x00
	end
end

function flasher_interface.flash(self, ulOffset, strData)
	local fOk, strMsg = writeBin(self.aArgs.strDataFileName, strData)
	if fOk == false then
		return false, strMsg
	end
	
	self.aArgs.iMode = MODE_FLASH
	self.aArgs.ulStartOffset = ulOffset
	self.aArgs.ulLen = strData:len()
	return exec(self.aArgs)
end


function flasher_interface.verify(self, ulOffset, strData)
	local fOk, strMsg = writeBin(self.aArgs.strDataFileName, strData)
	if fOk == false then
		return false, strMsg
	end
	
	self.aArgs.iMode = MODE_VERIFY
	self.aArgs.ulStartOffset = ulOffset
	self.aArgs.ulLen = strData:len()
	return exec(self.aArgs)
end

function flasher_interface.read(self, ulOffset, ulSize)
	self.aArgs.iMode = MODE_READ
	self.aArgs.ulStartOffset = ulOffset
	self.aArgs.ulLen = ulSize
	
	local fOk, strMsg = exec(self.aArgs)

	if not fOk then
		return nil, strMsg
	else
		strData, strMsg = loadBin(self.aArgs.strDataFileName)
	end
	
	return strData, strMsg
end


function flasher_interface.erase(self, ulOffset, ulSize)
	self.aArgs.iMode = MODE_ERASE
	self.aArgs.ulStartOffset = ulOffset
	self.aArgs.ulLen = ulSize
	return exec(self.aArgs)
end


function flasher_interface.isErased(self, ulOffset, ulSize)
	self.aArgs.iMode = MODE_IS_ERASED
	self.aArgs.ulStartOffset = ulOffset
	self.aArgs.ulLen = ulSize
	return exec(self.aArgs)
end


function flasher_interface.eraseChip(self)
	return self:erase(0, self:getDeviceSize())
end


function flasher_interface.readChip(self)
	return self:read(0, self:getDeviceSize())
end


function flasher_interface.isChipErased(self)
	return self:isErased(0, self:getDeviceSize())
end

--------------------------------------------------------------------------
-- main
--------------------------------------------------------------------------

local aArgs
local fOk
local strMsg

io.output():setvbuf("no")

aArgs, strMsg = evalArg()

if aArgs == nil then
	if strMsg then
		print(strMsg)
	end
	os.exit(1)
	
elseif aArgs.iMode == MODE_HELP then
	print(strUsage)
	os.exit(0)
	
elseif aArgs.iMode == MODE_LIST_INTERFACES then
	list_interfaces()
	os.exit(0)

elseif aArgs.iMode == MODE_DETECT_CHIPTYPE then
	fOk, strMsg = detect_chiptype(aArgs)
	if fOk then
		if strMsg then 
			print(strMsg)
		end
		os.exit(0)
	else
		printf("Error: %s", strMsg or "unknown error")
		os.exit(1)
	end
	
elseif aArgs.iMode == MODE_TEST_CLI then
	flasher_interface:configure(aArgs.strPluginName, aArgs.iBus, aArgs.iUnit, aArgs.iChipSelect)
	fOk, strMsg = flasher_test.testFlasher(flasher_interface)
	print(fOk, strMsg)
	os.exit(0)
	
else
	show_args(aArgs)
	
	fOk, strMsg = exec(aArgs)
	
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