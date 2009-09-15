-----------------------------------------------------------------------------
--   Copyright (C) 2009 by Christoph Thelen                                --
--   doc_bacardi@users.sourceforge.net                                     --
--                                                                         --
--   This program is free software; you can redistribute it and/or modify  --
--   it under the terms of the GNU General Public License as published by  --
--   the Free Software Foundation; either version 2 of the License, or     --
--   (at your option) any later version.                                   --
--                                                                         --
--   This program is distributed in the hope that it will be useful,       --
--   but WITHOUT ANY WARRANTY; without even the implied warranty of        --
--   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         --
--   GNU General Public License for more details.                          --
--                                                                         --
--   You should have received a copy of the GNU General Public License     --
--   along with this program; if not, write to the                         --
--   Free Software Foundation, Inc.,                                       --
--   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             --
-----------------------------------------------------------------------------

module("flasher", package.seeall)

require("bit")


local function progress(cnt,max)
	print(string.format("%d%% (%d/%d)", cnt*100/max, cnt, max))
	return true
end

local function callback(a,b)
	print(string.format("'%s'", a))
	return true
end


local function set_parameterblock(tPlugin, ulAddress, aulParameters)
	local strBin = ""


	for i,v in ipairs(aulParameters) do
		strBin = strBin .. string.char( bit.band(v,0xff), bit.band(bit.rshift(v,8),0xff), bit.band(bit.rshift(v,16),0xff), bit.band(bit.rshift(v,24),0xff) )
	end
	tPlugin:write_image(ulAddress, strBin, progress, string.len(strBin))
end



function flash(tPlugin, ulDevDescAdr, ulStartAdr, ulDataByteSize, ulDataAddress)
	local parameter_block = 0x00018000
	local dev_desc_adr = 0x00018080
	local ulValue
	local aulParameter
	local ulEraseStart
	local ulEraseEnd
	local fIsErased


	aulParameter = {}
	-- set the parameter
	aulParameter[1] = 0xffffffff
	aulParameter[2] = parameter_block+0x0c
	aulParameter[3] = 0x00000000
	-- set the extended parameter
	aulParameter[4] = 0x00020000					-- parameter version: 2.0
	aulParameter[5] = 0						-- operation mode: Flash
	aulParameter[6] = ulDevDescAdr					-- data block for the device description
	aulParameter[7] = ulStartAdr
	aulParameter[8] = ulDataByteSize
	aulParameter[9] = ulDataAddress

	set_parameterblock(tPlugin, parameter_block, aulParameter)


	tPlugin:call(0x00008000, parameter_block, callback, 2)

	-- get the result
	ulValue = tPlugin:read_data32(parameter_block+0x00)
	print(string.format("call finished with result 0x%08x", ulValue))
	if ulValue==0 then
		-- check the device description
		ulValue = tPlugin:read_data32(parameter_block+0x08)
		fIsErased = (ulValue==0xff)
	end

	return fIsErased
end



function erase(tPlugin, ulDevDescAdr, ulEraseStart, ulEraseEnd)
	local parameter_block = 0x00018000
	local dev_desc_adr = 0x00018080
	local ulValue
	local aulParameter
	local fIsOk


	aulParameter = {}
	-- set the parameter
	aulParameter[1] = 0xffffffff
	aulParameter[2] = parameter_block+0x0c
	aulParameter[3] = 0x00000000
	-- set the extended parameter
	aulParameter[4] = 0x00020000					-- parameter version: 2.0
	aulParameter[5] = 1						-- operation mode: erase
	aulParameter[6] = ulDevDescAdr					-- data block for the device description
	aulParameter[7] = ulEraseStart
	aulParameter[8] = ulEraseEnd

	set_parameterblock(tPlugin, parameter_block, aulParameter)


	tPlugin:call(0x00008000, parameter_block, callback, 2)

	-- get the result
	ulValue = tPlugin:read_data32(parameter_block+0x00)
	print(string.format("call finished with result 0x%08x", ulValue))
	fIsOk = (ulValue==0)

	return fIsOk
end



function detect(tPlugin, tBus, ulChipSelect, ulDevDescAdr)
	local parameter_block = 0x00018000
	local dev_desc_adr = 0x00018080
	local ulValue
	local aulParameter
	local strDevDesc = nil


	aulParameter = {}
	-- set the parameter
	aulParameter[1] = 0xffffffff
	aulParameter[2] = parameter_block+0x0c
	aulParameter[3] = 0x00000000
	-- set the extended parameter
	aulParameter[4] = 0x00020000					-- parameter version: 2.0
	aulParameter[5] = 5						-- operation mode: detect
	aulParameter[6] = tBus						-- device: spi flash
	aulParameter[7] = ulChipSelect					-- chip select: 1
	aulParameter[8] = ulDevDescAdr					-- data block for the device description

	set_parameterblock(tPlugin, parameter_block, aulParameter)


	tPlugin:call(0x00008000, parameter_block, callback, 2)

	-- get the result
	ulValue = tPlugin:read_data32(parameter_block+0x00)
	print(string.format("call finished with result 0x%08x", ulValue))
	if ulValue==0 then
		-- check the device description
		ulValue = tPlugin:read_data32(ulDevDescAdr)
		if ulValue==0 then
			print("the device desription is not valid, nothing detected.")
		else
			local ulSize
			local ulVersion

			-- get the size of the returned data
			ulSize = tPlugin:read_data32(ulDevDescAdr+0x04)
			if ulSize<16 then
				print("the device description claims to be valid, but has a strange size.")
			else
				-- read the interface version of the returned data
				ulVersion = tPlugin:read_data32(ulDevDescAdr+0x08)
				if ulVersion~=0x00020000 then
					-- the version does not match the expected value
					print(string.format("the device description has a strange interface version."))
				else
					-- get the device description
					strDevDesc = tPlugin:read_image(ulDevDescAdr, ulSize, progress, ulSize)
				end
			end
		end
	end

	return strDevDesc
end



function getEraseArea(tPlugin, ulDevDescAdr, ulStartAdr, ulLastAdr)
	local parameter_block = 0x00018000
	local dev_desc_adr = 0x00018080
	local ulValue
	local aulParameter
	local ulEraseStart
	local ulEraseEnd


	aulParameter = {}
	-- set the parameter
	aulParameter[1] = 0xffffffff
	aulParameter[2] = parameter_block+0x0c
	aulParameter[3] = 0x00000000
	-- set the extended parameter
	aulParameter[4] = 0x00020000					-- parameter version: 2.0
	aulParameter[5] = 7						-- operation mode: 
	aulParameter[6] = ulDevDescAdr					-- data block for the device description
	aulParameter[7] = ulStartAdr
	aulParameter[8] = ulLastAdr

	set_parameterblock(tPlugin, parameter_block, aulParameter)


	tPlugin:call(0x00008000, parameter_block, callback, 2)

	-- get the result
	ulValue = tPlugin:read_data32(parameter_block+0x00)
	print(string.format("call finished with result 0x%08x", ulValue))
	if ulValue==0 then
		-- check the device description
		ulEraseStart = tPlugin:read_data32(parameter_block+0x18)
		ulEraseEnd = tPlugin:read_data32(parameter_block+0x1c)
	end

	return ulEraseStart, ulEraseEnd
end



function isErased(tPlugin, ulDevDescAdr, ulEraseStart, ulEraseEnd)
	local parameter_block = 0x00018000
	local dev_desc_adr = 0x00018080
	local ulValue
	local aulParameter
	local ulEraseStart
	local ulEraseEnd
	local fIsErased


	aulParameter = {}
	-- set the parameter
	aulParameter[1] = 0xffffffff
	aulParameter[2] = parameter_block+0x0c
	aulParameter[3] = 0x00000000
	-- set the extended parameter
	aulParameter[4] = 0x00020000					-- parameter version: 2.0
	aulParameter[5] = 6						-- operation mode: isErased
	aulParameter[6] = ulDevDescAdr					-- data block for the device description
	aulParameter[7] = ulEraseStart
	aulParameter[8] = ulEraseEnd

	set_parameterblock(tPlugin, parameter_block, aulParameter)


	tPlugin:call(0x00008000, parameter_block, callback, 2)

	-- get the result
	ulValue = tPlugin:read_data32(parameter_block+0x00)
	print(string.format("call finished with result 0x%08x", ulValue))
	if ulValue==0 then
		-- check the device description
		ulValue = tPlugin:read_data32(parameter_block+0x08)
		fIsErased = (ulValue==0xff)
	end

	return fIsErased
end

