-----------------------------------------------------------------------------
-- Copyright (C) 2012 Hilscher Gesellschaft für Systemautomation mbH
--
-- Description:
--   cli_flash.lua: command line flasher tool
--
--  Changes:
--    Date      Author   Description
--  01 mar 12   SL       adapted to use the extended routines in flasher.lua
-----------------------------------------------------------------------------
-----------------------------------------------------------------------------
-- SVN Keywords
SVN_DATE   ="$Date$"
SVN_VERSION="$Revision$"
SVN_AUTHOR ="$Author$"
-----------------------------------------------------------------------------

-- paths
package.cpath= "muhkuh/lua_plugins/?.dll;"..package.cpath

FLASHER_PATH = "../targets/"
--FLASHER_PATH = "./"
_G.__MUHKUH_WORKING_FOLDER = ""


-- flasher-related
--require("bit")
require("mhash")
--require("system_cli")
require("flasher")
require("flasher_test")


-- plugin-related
require("select_plugin_cli")
require("tester_cli")   -- kommt man evtl. nur mit select_plugin aus?
--require("romloader_eth")
require("romloader_usb")
require("romloader_uart")


--------------------------------------------------------------------------
-- Usage
--------------------------------------------------------------------------

strUsage = [==[
Usage: lua cli_flash.lua mode parameters

                   Mode        Parameters
flash a file:      flash       [plugin] device [offset] filename
read flash:        read        [plugin] device [offset] size filename
erase flash:       erase       [plugin] device [offset] size
verify flash:      verify      [plugin] device [offset] filename
verify using hash: verify_hash [plugin] device [offset] filename
compute SHA1:      hash        [plugin] device [offset] size
get board info:    info
detect flash:      detect      [plugin] device
test flasher:      test        [plugin] device
test cli flasher:  testcli     [plugin] device
show this help:    -h

plugin: -p plugin_name
        example: -p romloader_usb_00_00
        
device: -b bus -u unit -cs chip_select
        example: -b 0 -u 0 -cs 0
        unit and chip select default to 0, 0
       
offset: -s device_start_offset
        offset in the flash device, defaults to 0
       
size:   -l length
        read/erase: 0xffffffff = read/erase from offset to end of chip
]==]

--------------------------------------------------------------------------
-- helpers
--------------------------------------------------------------------------

-- fOk, strMsg writeBin(strName, strBin)
-- write binary file into string
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

MODE_TEST = 11 -- test
MODE_TEST_CLI = 12 -- test
MODE_IS_ERASED = 13 -- test
MODE_GET_DEVICE_SIZE = 14 -- test


argdefs = {
b  = {argkey = "iBus",              clkey ="-b",  name="bus number"},
u  = {argkey = "iUnit",             clkey ="-u",  name="unit number"},
cs = {argkey = "iChipSelect",       clkey ="-cs", name="chip select number"},
p  = {argkey = "strPluginName",     clkey ="-p",  name="plugin name"},
s  = {argkey = "ulStartOffset",     clkey ="-s",  name="start offset"},
l  = {argkey = "ulLen",             clkey ="-l",  name="number of bytes to read"},
f  = {argkey = "strDataFileName",   clkey = "",   name="file name"}
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
[MODE_HELP]         = {}
}

function checkArgs(aArgs)
	-- get the list of required/optional args for mode
	local required = requiredargs[aArgs.iMode]
	if not required then
		print("unknown mode!")
		return false
	end
	
	local fOk = true
	
	--show_args(aArgs)
	for i, strKey in pairs(required) do
		local argdef = argdefs[strKey]
		--print(strKey, argdef.argkey)
		if not aArgs[argdef.argkey] then
			printf("please specify %s (%s)", argdef.name, argdef.clkey)
			fOk = false
		end
	end
		
	return fOk
end

-- Evaluate command line arguments.
-- returns list of arguments or nil and error message.
-- Entries returned in aArgs:
-- iMode              MODE_FLASH/MODE_READ/MODE_INFO/MODE_HELP
-- strPluginName      plugin name
-- iBus               bus number
-- iUnit              unit number 
-- iChipSelect        chip selet number
-- ulStartOffset      start offset for read
-- ulLen              number of bytes to read
-- strDataFileName    input/output file name


function evalArg()
	local aArgs = {}
	local iMode
	local iArg = 2
	local nArgs = #arg
	
	if nArgs>=2 and arg[1] == "flash" then
		aArgs.iMode = MODE_FLASH
	elseif nArgs>=2 and arg[1] == "read" then
		aArgs.iMode = MODE_READ
	elseif nArgs>=2 and arg[1] == "erase" then
		aArgs.iMode = MODE_ERASE
	elseif nArgs>=2 and arg[1] == "verify" then
		aArgs.iMode = MODE_VERIFY
	elseif nArgs>=2 and arg[1] == "verify_hash" then
		aArgs.iMode = MODE_VERIFY_HASH
	elseif nArgs>=2 and arg[1] == "hash" then
		aArgs.iMode = MODE_HASH
	elseif nArgs>=2 and arg[1] == "detect" then
		aArgs.iMode = MODE_DETECT
	elseif nArgs>=2 and arg[1] == "test" then
		aArgs.iMode = MODE_TEST
	elseif nArgs>=2 and arg[1] == "testcli" then
		aArgs.iMode = MODE_TEST_CLI
	elseif nArgs>=1 and arg[1] == "info" then
		aArgs.iMode = MODE_INFO
	elseif nArgs>=1 and arg[1] == "-h" then
		aArgs.iMode = MODE_HELP
	else
		return nil
	end
	
	
	while (iArg <= nArgs) do
		local iRemArgs = nArgs - iArg + 1
		if arg[iArg] == "-p" and iRemArgs >=2 then
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
			
		elseif arg[iArg] == "-s" and iRemArgs >=2 then
			aArgs.ulStartOffset  = tonumber(arg[iArg+1])
			if not aArgs.ulStartOffset then
				return nil, "Error parsing start offset (-s)"
			end
			iArg = iArg + 2

		elseif arg[iArg] == "-l" and iRemArgs >=2 then
			aArgs.ulLen  = tonumber(arg[iArg+1])
			if not aArgs.ulLen then
				return nil, "Error parsing length (-l)"
			end
			iArg = iArg + 2
			
		elseif iRemArgs == 1 then
			aArgs.strDataFileName = arg[iArg]
			iArg = iArg + 1
		else
			return nil, string.format("unknown argument: %s", arg[iArg])
		end
	end
		
	-- set defaults
	aArgs.iUnit = aArgs.iUnit or 0
	aArgs.iChipSelect = aArgs.iChipSelect or 0
	aArgs.ulStartOffset = aArgs.ulStartOffset or 0
	
	
	-- check for missing args
	if checkArgs(aArgs) then
		return aArgs
	else
		return nil
	end
	
	return aArgs
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
		fOk = true
		
		-- load input file  strDataFileName --> strData
		if fOk and (iMode == MODE_FLASH or iMode == MODE_VERIFY or iMode == MODE_VERIFY_HASH) then
			print("Loading data file")
			strData, strMsg = muhkuh.load(strDataFileName)
			if not strData then
				fOk = false
				strMsg = "Failed to load binary '" .. strDataFileName .. "': " .. (strMsg or "Unknown error")
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
		
		if fOk and iMode == MODE_INFO then
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
		
		-- flash/erase: erase the area
		if fOk and (iMode == MODE_FLASH or iMode == MODE_ERASE) then
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
			fOk, strFlashHashBin = flasher.hash(tPlugin, aAttr, ulStartOffset, ulStartOffset + ulLen)
			if not fOk then
				fOk = false
				strMsg = "Could not compute the checksum over the flash!"
				
			else
				strFlashHash = getHexString(strFlashHashBin)
				print("Flash SHA1: " .. strFlashHash)
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
		strDataFileName = "D:/flashertest.bin"
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
	if self.aArgs.iBus==1 then
		return 1
	else
		return 2 -- may be 1, 2 or 4
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
		local strData = muhkuh.load(self.aArgs.strDataFileName)
		if not strData then
			return nil, "Could not read file " .. self.aArgs.strDataFileName
		else
			return strData
		end
	end
	
	--[[
	if fOk then
		local fd = io.open(self.aArgs.strDataFileName, "rb")
		if not fd then
			return nil, "Could not open file " .. self.aArgs.strDataFileName
		end
		strData = fd:read("*a")
		if not strData then 
			return nil, "Could not read file " .. self.aArgs.strDataFileName
		end
	end
	return strData
	--]]
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

aArgs, strMsg = evalArg()

if aArgs == nil then
	if strMsg then
		print(strMsg)
	end
	print(strUsage)
	os.exit(1)
	
elseif aArgs.iMode == MODE_HELP then
	print(strUsage)
	os.exit(0)
	
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

