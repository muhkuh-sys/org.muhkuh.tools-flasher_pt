-----------------------------------------------------------------------------
-- Copyright (C) 2012 Hilscher Gesellschaft für Systemautomation mbH
--
-- Description:
-- Perform operation on the internal flash of the netx 90 MPW:
-- Enable/disable the redundancy pages
-- Copy page 0 to the redundancy pages
-- Erase the redundancy pages
-- Display page 0 and the redundancy pages
-----------------------------------------------------------------------------

_G.__MUHKUH_WORKING_FOLDER = ""
FLASHER_PATH = FLASHER_PATH or "netx/"



--------------------------------------------------------------------------
-- Usage
--------------------------------------------------------------------------

strUsage = [==[
Usage: lua netx90mpw_iflash.lua mode parameters

Mode                     Parameters
disable_redundancy_pages [p]        Disable redundancy pages
copy_page_0              [p]        Copy page 0 to redundancy pages
copy_iflash_0_page_0     [p]        Copy page 0 to redundancy pages in intflash 0 only
copy_iflash_1_page_0     [p]        Copy page 0 to redundancy pages in intflash 1 only
copy_iflash_2_page_0     [p]        Copy page 0 to redundancy pages in intflash 2 only
menu                     [p]        Interactive mode
-h                                  Show this help    
        
p:    -p plugin_name
      select plugin
      example: -p romloader_usb_00_01
	  
Options in interactive mode:
1: Show page 0 of main array and redundancy pages
2: Show pages 0-2 with current config
3: Disable redundancy pages
4: Map redundancy pages to pages 0 and 1
5: Map redundancy pages to pages 1 and 2
6: Map both redundancy pages to page 0
7: Erase redundancy pages

]==]

--------------------------------------------------------------------------
-- helpers
--------------------------------------------------------------------------

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


--------------------------------------------------------------------------
-- handle command line arguments
--------------------------------------------------------------------------
MODE_HELP = 0
MODE_DISABLE = 1
MODE_COPY = 2
MODE_MENU = 3
MODE_COPY_IFLASH0 = 4
MODE_COPY_IFLASH1 = 5
MODE_COPY_IFLASH2 = 6

arg2Mode = {
	disable_redundancy_pages  = MODE_DISABLE,
	copy_page_0               = MODE_COPY,
	copy_iflash_0_page_0      = MODE_COPY_IFLASH0,
	copy_iflash_1_page_0      = MODE_COPY_IFLASH1,
	copy_iflash_2_page_0      = MODE_COPY_IFLASH2,
	menu                      = MODE_MENU,
	["-h"]                    = MODE_HELP
}

function parseArgs()
	local fOk = true
	local strMsg
	local aArgs = {}
	if #arg == 0 then
		aArgs.iMode = MODE_HELP
		fOk = true
	else
		aArgs.iMode = arg2Mode[arg[1]]
		if aArgs.iMode == nil then
			strMsg = "Unknown mode"
			fOk = false
		else 
			if #arg == 1 then
				fOk = true
			elseif #arg == 3 and arg[2] == "-p" then
				aArgs.strPluginName = arg[3]
				fOk = true
			else
				fOk = false
				strMsg = "Invalid parameters"
			end
		end
	end
	
	return fOk, strMsg, aArgs
end


--------------------------------------------------------------------------
-- netx 90 MPW intflash
--------------------------------------------------------------------------

atIflashBlocks = {
	[0] = { name="iflash_cfg0_com",  ctrl= 0xff001c00,  mem = 0x00100000},
	[1] = { name="iflash_cfg1_com",  ctrl= 0xff001c80,  mem = 0x00180000},
	[2] = { name="iflash_cfg2",      ctrl= 0xff401400,  mem = 0x00200000},
}

OFF_iflash_reset     = 0x30
MSK_iflash_reset_reset = 1
OFF_iflash_red_cfg0  = 0x34
OFF_iflash_red_cfg1  = 0x38
OFF_iflash_ifren_cfg = 0x3c

function set_red_cfg(tPlugin, tIflashBlock, ulRedCfg0, ulRedCfg1)
	local ulCtrl = tIflashBlock.ctrl
	tPlugin:write_data32(ulCtrl + OFF_iflash_red_cfg0, ulRedCfg0)
	tPlugin:write_data32(ulCtrl + OFF_iflash_red_cfg1, ulRedCfg1)
	tPlugin:write_data32(ulCtrl + OFF_iflash_reset, MSK_iflash_reset_reset)
	tPlugin:write_data32(ulCtrl + OFF_iflash_reset, 0)
end

function set_red_cfg_all(tPlugin, ulRedCfg0, ulRedCfg1)
	set_red_cfg(tPlugin, atIflashBlocks[0], ulRedCfg0, ulRedCfg1)
	set_red_cfg(tPlugin, atIflashBlocks[1], ulRedCfg0, ulRedCfg1)
	set_red_cfg(tPlugin, atIflashBlocks[2], ulRedCfg0, ulRedCfg1)
end

function get_red_cfg(tPlugin, tIflashBlock)
	local ulCtrl = tIflashBlock.ctrl
	local ulRedCfg0 = tPlugin:read_data32(ulCtrl + OFF_iflash_red_cfg0)
	local ulRedCfg1 = tPlugin:read_data32(ulCtrl + OFF_iflash_red_cfg1)
	
	return ulRedCfg0, ulRedCfg1
end

function get_ifren_cfg(tPlugin, tIflashBlock)
	local ulCtrl = tIflashBlock.ctrl
	local ulIfrenCfg = tPlugin:read_data32(ulCtrl + OFF_iflash_ifren_cfg)
	return ulIfrenCfg
end

function callback_progress(a, b)
	--print(a, b)
	return true
end

function get_page(tPlugin, tIflashBlock, ulPage)
	local ulSize = 4096
	local ulAddr = tIflashBlock.mem + ulSize*ulPage
	local strPage0 = tPlugin:read_image(ulAddr, ulSize, callback_progress, ulSize)
	return strPage0
end

function hexdump(strPage)
	local str = strPage:sub(1, 64)
	tester.hexdump(str, 16)
end

strEmptyPage = string.rep(string.char(0xff), 4096)
function checkEmpty(strPage)
	if strEmptyPage == strPage then 
		print("Page is empty")
	else
		print("Page is not empty")
	end
end


--------------------------------------------------------------------------
-- 
--------------------------------------------------------------------------

function disable_redundancy_pages(tPlugin)
	print("disable_redundancy_pages")
	set_red_cfg_all(tPlugin, 1, 1)
	return true
end

function copy_page_0_all(tPlugin)
	local fOk, strMsg 
	
	disable_output(tPlugin)
	
	local aAttr = flasher.download(tPlugin, FLASHER_PATH)
	if aAttr == nil then
		fOk, strMsg = false, "failed to download the flasher"
	else
		for uiUnit = 0, 2 do
			fOk, strMsg = copy_page0_to_redundancy(tPlugin, aAttr, uiUnit)
			if fOk ~= true then 
				break
			end
		end
	end
	
	return fOk, strMsg
end


function copy_page_0_unit(tPlugin, uiUnit)
	local fOk, strMsg 
	
	disable_output(tPlugin)
	
	local aAttr = flasher.download(tPlugin, FLASHER_PATH)
	if aAttr == nil then
		fOk, strMsg = false, "failed to download the flasher"
	else
		fOk, strMsg = copy_page0_to_redundancy(tPlugin, aAttr, uiUnit)
	end
	
	return fOk, strMsg
end

function disable_output(tPlugin)
	tPlugin:write_data32(0x2009fff0, 0)
	tPlugin:write_data32(0x2009fff4, 0)
	tPlugin:write_data32(0x2009fff8, 0)
	tPlugin:write_data32(0x2009fffc, 0)
end

function copy_page0_to_redundancy(tPlugin, aAttr, uiUnit)
	local tIflashBlock = atIflashBlocks[uiUnit]
	local tBus = flasher.BUS_IFlash
	local ulChipSelect = 0
	
	print("********************************")
	print(tIflashBlock.name)
	print("********************************")

	-- Map redundancy pages to offset 0x1000 and 0x2000.
	set_red_cfg(tPlugin, tIflashBlock, 2, 4)
	
	-- Read page 0 of the main array.
	ulPage0Addr = tIflashBlock.mem
	strData = flasher.read_image(tPlugin, ulPage0Addr, 0x1000)

	-- Detect the iflash.
	fOk = flasher.detect(tPlugin, aAttr, tBus, uiUnit, ulChipSelect)
	if fOk ~= true then 
		fOk, strMsg = false, "Failed to detect the internal flash!"
	else
		-- Erase redundancy pages 0/1 at 0x1000/0x2000.
		fOk, strMsg = flasher.eraseArea(tPlugin, aAttr, 0x1000, 0x2000)
		if fOk ~= true then
			fOk, strMsg = false, strMsg or "Error while erasing redundancy pages"
		else
			-- Write two copies of page 0 into the redundancy pages.
			-- Todo: is it better to write the same data into both pages, or
			-- to write the data into one page and zero the other?
			fOk, strMsg = flasher.flashArea(tPlugin, aAttr, 0x1000, strData..strData)
			print(strMsg)
			if fOk ~= true then
				fOk, strMsg = false, strMsg or "Error while writing redundancy pages"
			else
				-- Map both redundancy pages to page 0. Read page 0 and compare with the page we read initially.
				set_red_cfg(tPlugin, tIflashBlock, 0, 0)
				strDataCheck = flasher.read_image(tPlugin, ulPage0Addr, 0x1000)
				if strData == strDataCheck then
					fOk, strMsg = true, "redundancy pages written and verified"
				else
					fOk, strMsg = false, "data from overlaid redundancy pages is not equal"
				end
			end
		end
	end
	
	-- Disable the redundancy pages.
	set_red_cfg(tPlugin, tIflashBlock, 1, 1)
	
	return fOk, strMsg 
end



function erase_redundancy_pages_all(tPlugin)
	local fOk, strMsg 
	
	local aAttr = flasher.download(tPlugin, FLASHER_PATH)
	if aAttr == nil then
		fOk, strMsg = false, "failed to download the flasher"
	else
		for uiUnit = 0, 2 do
			fOk, strMsg = erase_redundancy_pages(tPlugin, aAttr, uiUnit)
			if fOk ~= true then 
				break
			end
		end
	end
	
	return fOk, strMsg
end


function erase_redundancy_pages(tPlugin, aAttr, uiUnit)
	local tIflashBlock = atIflashBlocks[uiUnit]
	local tBus = flasher.BUS_IFlash
	local ulChipSelect = 0
	
	print("********************************")
	print(tIflashBlock.name)
	print("********************************")

	-- Map redundancy pages to offset 0x1000 and 0x2000.
	set_red_cfg(tPlugin, tIflashBlock, 2, 4)
	
	-- Detect the iflash.
	fOk = flasher.detect(tPlugin, aAttr, tBus, uiUnit, ulChipSelect)
	if not fOk then
		fOk, strMsg = false, "Failed to detect the internal flash!"
	else
		-- Erase redundancy pages 0/1 at 0x1000/0x2000.
		fOk, strMsg = flasher.eraseArea(tPlugin, aAttr, 0x1000, 0x2000)
		if not fOk then
			fOk, strMsg = false, strMsg or "Error while erasing pages 1 and 2"
		else
			print("Redundancy pages erased")
		end
	end
	
	-- Disable the redundancy pages.
	set_red_cfg(tPlugin, tIflashBlock, 1, 1)
	return fOk, strMsg
end


--------------------------------------------------------------------------
-- menu
--------------------------------------------------------------------------

function show_pages012(tPlugin)
	for i=0, 2 do
		local tIflashBlock = atIflashBlocks[i]
		print("********************************")
		print(tIflashBlock.name)
		print("********************************")
		for i=0, 2 do
			printf("Page %d:", i)
			local strPage = get_page(tPlugin, tIflashBlock, i)
			hexdump(strPage)
			print()
		end
	end
end


function show_pages(tPlugin)
	for i=0, 2 do
		local tIflashBlock = atIflashBlocks[i]
		print("********************************")
		print(tIflashBlock.name)
		print("********************************")
		
		-- save iflash_red_cfg0/1
		local ulRedCfg0, ulRedCfg1 = get_red_cfg(tPlugin, tIflashBlock)
		local ulIfrenCfg = get_ifren_cfg(tPlugin, tIflashBlock)
		tIflashBlock.ulRedCfg0 = ulRedCfg0
		tIflashBlock.ulRedCfg1 = ulRedCfg1
		printf("Current setting: ")
		printf("ulRedCfg0:  0x%08x", ulRedCfg0)
		printf("ulRedCfg1:  0x%08x", ulRedCfg1)
		printf("ulIfrenCfg: 0x%08x", ulIfrenCfg)
		print()
		
		-- enable normal memory: iflash_red_cfg0/1 = 1
		-- read page 0
		print("Page 0:")
		set_red_cfg(tPlugin, tIflashBlock, 1, 1)
		tIflashBlock.strPage0 = get_page(tPlugin, tIflashBlock, 0)
		hexdump(tIflashBlock.strPage0)
		checkEmpty(tIflashBlock.strPage0)
		print()
		
		-- enable redundancy page 0: iflash_red_cfg0 = 0, iflash_red_cfg1 = 1
		-- read page 0
		print("Redundancy page 0:")
		set_red_cfg(tPlugin, tIflashBlock, 0, 1)
		tIflashBlock.strRed0 = get_page(tPlugin, tIflashBlock, 0)
		hexdump(tIflashBlock.strRed0)
		checkEmpty(tIflashBlock.strRed0)
		print()
		
		-- enable redundancy page 1: iflash_red_cfg0 = 1, iflash_red_cfg1 = 0
		-- read page 0
		print("Redundancy page 1:")
		set_red_cfg(tPlugin, tIflashBlock, 1, 0)
		tIflashBlock.strRed1 = get_page(tPlugin, tIflashBlock, 0)
		hexdump(tIflashBlock.strRed1)
		checkEmpty(tIflashBlock.strRed1)
		print()
		
		-- restore iflash_red_cfg0/1
		set_red_cfg(tPlugin, tIflashBlock, ulRedCfg0, ulRedCfg1)
		
	end
end



function menu(tPlugin)

	while true do
		print("")
		print("Please select:")
		print("1: Show page 0 of main array and redundancy pages")
		print("2: Show pages 0-2 with current config")
		print("3: Disable redundancy pages")
		print("4: Map redundancy pages to pages 0 and 1")
		print("5: Map redundancy pages to pages 1 and 2")
		print("6: Map both redundancy pages to page 0")
		print("7: Erase redundancy pages")
		print("c: Cancel")
		print("")
		
		io.write(">")
		strSelection = io.read():lower()
		
		if strSelection == "1" then
			show_pages(tPlugin)
			
		elseif strSelection == "2" then
			show_pages012(tPlugin)
			
		elseif strSelection == "3" then
			set_red_cfg_all(tPlugin, 1, 1)
			
		elseif strSelection == "4" then
			set_red_cfg_all(tPlugin, 0, 2)
		
		elseif strSelection == "5" then
			set_red_cfg_all(tPlugin, 2, 4)
	
		elseif strSelection == "6" then
			set_red_cfg_all(tPlugin, 0, 0)
	
		elseif strSelection == "7" then
			fOk, strMsg = erase_redundancy_pages_all(tPlugin)
			print(fOk, strMsg)
			
		elseif strSelection == "c" then
			break
		end
	end

	return true
end

--------------------------------------------------------------------------
-- main
--------------------------------------------------------------------------
print(os.date())
io.output():setvbuf("no")

fOk, strMsg, aArgs = parseArgs()

if not fOk then
	print(strMsg or "Unknown error")
	os.exit(1)

elseif aArgs.iMode == MODE_HELP then
	print(strUsage)
	os.exit(0)

elseif aArgs.iMode then
	require("muhkuh_cli_init")
	require("flasher")
	require("flasher_test")

	tPlugin, strMsg = getPlugin(aArgs.strPluginName)
	if tPlugin then
		tPlugin:Connect()
		if aArgs.iMode == MODE_DISABLE then
			fOk, strMsg = disable_redundancy_pages(tPlugin)
		elseif aArgs.iMode == MODE_COPY then
			fOk, strMsg = copy_page_0_all(tPlugin)
		elseif aArgs.iMode == MODE_COPY_IFLASH0 then
			fOk, strMsg = copy_page_0_unit(tPlugin, 0)
		elseif aArgs.iMode == MODE_COPY_IFLASH1 then
			fOk, strMsg = copy_page_0_unit(tPlugin, 1)
		elseif aArgs.iMode == MODE_COPY_IFLASH2 then
			fOk, strMsg = copy_page_0_unit(tPlugin, 2)
		elseif aArgs.iMode == MODE_MENU then
			fOk, strMsg = menu(tPlugin)
		else
			fOk = false
			strMsg = "unknown mode***"
		end
		tPlugin:Disconnect()
	else
		fOk = false
	end
	
	print(os.date())
	if fOk then
		if strMsg then 
			print(strMsg)
		end
		os.exit(0)
	else
		print(strMsg or "an unknown error occurred")
		os.exit(1)
	end
	
else
	print(strUsage)
	os.exit(1)

end
