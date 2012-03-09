module("flasher_test", package.seeall)

---------------------------------------------------------------------------
-- Copyright (C) 2012 Hilscher Gesellschaft für Systemautomation mbH
--
-- Description:
--   flasher_test.lua: flasher test routines
--
--  Changes:
--    Date        Author        Description
--  29 feb 12     SL            created
---------------------------------------------------------------------------
---------------------------------------------------------------------------
-- SVN Keywords
SVN_DATE   ="$Date$"
SVN_VERSION="$Revision$"
SVN_AUTHOR ="$Author$"
---------------------------------------------------------------------------

require("flasher")

m_logMsgFile = nil
m_logMsgFile = "D:/log.txt"

function log_printf(...)
	local strMsg = string.format(...)
	print(strMsg)
	if m_logMsgFile then
		local fd = io.open(m_logMsgFile, "a+")
		assert(fd, "Could not open log file")
		fd:write(strMsg)
		fd:write("\n")
		fd:close()
	end
end


--========================================================================
--                      interface to flasher.lua
--========================================================================

-- Interface to the actual flash functions.
-- Generally, the routines return either true or false and an error message.
-- Read routines return the data or nil and an error message.
-- isErased returns true or false and an error message.
-- 
-- fOk, strMsg      init()            -- open plugin, download flasher, detect chip etc.
--
-- ulSize           getDeviceSize()   -- returns chip size in bytes
-- ulBusWidth       getBusWidth()     -- returns 1, 2 or 4
--
-- fOk, strMsg      flash(ulOffset, strData) 
-- fOk, strMsg      verify(ulOffset, strData)
-- strData, strMsg  read(ulOffset, ulSize)   -- returns data or nil and an error message
-- fOk, strMsg      erase(ulOffset, ulSize) 
-- fOk, strMsg      isErased(ulOffset, ulSize) 
-- 
-- strData, strMsg  readChip()
-- fOK, strMsg      eraseChip()
-- fOk, strMsg      isChipErased()


flasher_interface = {
	-- private:
	tPlugin = nil,
	a_attr = nil,
	iBus = nil,
	iUnit = nil,
	iChipSelect =nil,
}

function flasher_interface.configure(self, tPlugin, strFlasherPath, iBus, iUnit, iChipSelect)
	self.tPlugin = tPlugin
	self.strFlasherPath = strFlasherPath
	self.iBus = iBus
	self.iUnit = iUnit
	self.iChipSelect = iChipSelect
end

function flasher_interface.init(self)
	print("Downloading flasher binary")
	self.aAttr = flasher.download(self.tPlugin, self.strFlasherPath, self.fnCallbackProgress)
	if not self.aAttr then
		return false, "Error while downloading flasher binary"
	end

	-- check if the selected flash is present
	print("Detecting flash device")
	fOk = flasher.detect(
		self.tPlugin, self.aAttr, 
		self.iBus, self.iUnit, self.iChipSelect,
		self.fnCallbackMessage, self.fnCallbackProgress
		)
	if not fOk then
		return false, "Failed to get a device description!"
	end

	return true
end

function flasher_interface.finish(self)
end

function flasher_interface.getDeviceSize(self)
	local ulSize = flasher.getFlashSize(
		self.tPlugin, self.aAttr, 
		self.fnCallbackMessage, self.fnCallbackProgress)
		
	if ulSize then
		return ulSize
	else
		return nil, "Failed to get device size"
	end
end

-- bus 0: parallel, bus 1: serial
function flasher_interface.getBusWidth(self)
	if self.iBus==1 then
		return 1
	else
		return 2 -- may be 1, 2 or 4
	end
end

function flasher_interface.flash(self, ulOffset, strData)
	return flasher.flashArea(
		self.tPlugin, self.aAttr, 
		ulOffset, strData,
		self.fnCallbackMessage, self.fnCallbackProgress)
end

function flasher_interface.verify(self, ulOffset, strData)
	return flasher.verifyArea(
		self.tPlugin, self.aAttr, 
		ulOffset, strData,
		self.fnCallbackMessage, self.fnCallbackProgress)
end

function flasher_interface.read(self, ulOffset, ulSize)
	return flasher.readArea(
		self.tPlugin, self.aAttr, 
		ulOffset, ulSize,
		self.fnCallbackMessage, self.fnCallbackProgress)
end

function flasher_interface.erase(self, ulOffset, ulSize)
	return flasher.eraseArea(
		self.tPlugin, self.aAttr, 
		ulOffset, ulSize,
		self.fnCallbackMessage, self.fnCallbackProgress)
end

function flasher_interface.isErased(self, ulOffset, ulSize)
	local tPlugin = self.tPlugin
	local aAttr = self.aAttr
	local fIsErased = flasher.isErased(
		self.tPlugin, self.aAttr, ulOffset, ulOffset + ulSize,
		self.fnCallbackMessage, self.fnCallbackProgress)
		
	return fIsErased, fIsErased and "The area is empty" or "The area is not empty"
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

--========================================================================
--                           Helper routines
--========================================================================


-- random string
function getRandomData(iSize)
	local acBytes = {}
	for i=1, iSize do
		acBytes[i] = string.char(math.random(0, 255))
	end
	return table.concat(acBytes)
end


-- randomly re-order the elements of l
-- l is a list with integer keys 1..n
-- usage: l = reorder_randomly(l)
function reorder_randomly(l)
	local l2 = {}
	local iPos
	for iLen=#l, 1, -1 do
		iPos = math.random(1, iLen)
		table.insert(l2, l[iPos])
		table.remove(l, iPos)
	end
	return l2
end


-- insert a random segment in unused space.
-- segments must be ordered by offset and non-overlapping
-- fEven = true: generate even offset and size
-- returns true if a segment was inserted, false otherwise
function insert_random_segment(atSegments, ulDeviceSize, fEven)
	-- get a random position
	-- the new segment is inserted between atSegments[iPos] and atSegments[iPos+1]
	local iPos = math.random(0, #atSegments)
	
	-- get the inter-segment space at this position
	local offset   -- 0-based offset of the inter-segment space
	local size     -- size of the inter-segment space

	if #atSegments == 0 then
		offset = 0
		size = ulDeviceSize
	elseif iPos == 0 then
		offset = 0
		size = atSegments[1].offset
	elseif iPos == #atSegments then
		offset = atSegments[iPos].offset + atSegments[iPos].size
		size = ulDeviceSize - offset
	else
		offset = atSegments[iPos].offset + atSegments[iPos].size
		size = atSegments[iPos+1].offset - offset
	end
	
	if size > 0 then
		local offset1 = math.random(offset, offset+size-1)  -- start addr
		local offset2 = math.random(offset1, offset+size-1) -- end addr (incl)
		
		if fEven then
			-- start addr must be even
			-- end addr incl must be odd!
			offset1 = offset1 - (offset1 % 2)
			offset2 = offset2 - (offset2 % 2) + 1
		end
	
		local size1 = offset2 - offset1 + 1
		printf("0x%08x+0x%08x --> 0x%08x+0x%08x", offset, size, offset1, size1)
		local tSegment = {offset = offset1, size = size1}
	
		table.insert(atSegments, iPos+1, tSegment)
		return true
		
	else
		return false
	end
end

function printf(...) print(string.format(...)) end

--========================================================================
--                           Test
--========================================================================


function testFlasher(tFlasherInterface, fnLogPrintf)
	
	tFlasherInterface = tFlasherInterface or flasher_interface
	local log_printf = fnLogPrintf or log_printf
	
	-- init flasher
	fOk, strMsg = tFlasherInterface:init()
	assert(fOk, strMsg)
	
	local ulDeviceSize = tFlasherInterface:getDeviceSize()
	
	-- for serial flash
	local atSegments_1={
		{offset = 0, size = 12345},
		{offset = 0x10000, size = 0x10000},
		{offset = 0x30001, size = 0x10000},
		{offset = 0x50002, size = 0x10000},
		{offset = 0x70003, size = 0x10000},
		{offset = 0x90004, size = 0x10001},
		{offset = 0xb0004, size = 0x10002},
		{offset = 0xd0004, size = 0x10003},
		
		{offset = 0x20000, size = 1},
		{offset = 0x21004, size = 2},
		{offset = 0x22008, size = 3},
		
		{offset = 0x23000, size = 1},
		{offset = 0x23210, size = 1},
		
		{offset = ulDeviceSize - 12345, size = 12345},
	}
	
	-- for 16 bit parflash:
	-- offset/size must be multiples of bus width
	local atSegments_2={
		{offset = 0, size = 12346},
		{offset = 0x10000, size = 0x10000},
		{offset = 0x30002, size = 0x10000},
		{offset = 0x50002, size = 0x10000},
		{offset = 0x70004, size = 0x10000},
		{offset = 0x90004, size = 0x10000},
		{offset = 0xb0004, size = 0x10002},
		{offset = 0xd0004, size = 0x10004},
		
		{offset = 0x20000, size = 2},
		{offset = 0x21004, size = 2},
		{offset = 0x22008, size = 2},
		
		{offset = 0x23000, size = 2},
		{offset = 0x23210, size = 2},
		
		{offset = ulDeviceSize - 12346, size = 12346},
	}
	
	-- select the segments list according to the flash type
	if tFlasherInterface:getBusWidth()==1 then
		atSegments = atSegments_1
	else
		atSegments = atSegments_2
	end
	
	-- add random segments
	table.sort(atSegments, function(a, b) return a.offset<b.offset end)
	math.randomseed(os.time())
	local iSize = #atSegments
	
	local fRound = tFlasherInterface:getBusWidth() > 1
	while #atSegments < iSize + 10 do
		insert_random_segment(atSegments, ulDeviceSize, fRound)
	end
	
	for iSegment, tSegment in ipairs(atSegments) do
		local offset = tSegment.offset
		local size = tSegment.size
		log_printf("%d 0x%08x-0x%08x size 0x%x", iSegment, offset, offset+size-1, size)
	end
	
	-- reorder
	atSegments = reorder_randomly(atSegments)
	
	for iSegment, tSegment in ipairs(atSegments) do
		local offset = tSegment.offset
		local size = tSegment.size
		log_printf("%d 0x%08x-0x%08x size 0x%x", iSegment, offset, offset+size-1, size)
	end
	
	
	-- fill segments with data
	for iSegment, tSegment in ipairs(atSegments) do
		tSegment.data = tSegment.data or getRandomData(tSegment.size)
	end
	
	
	-- erase
	log_printf("Erasing flash")
	fOk, strMsg = tFlasherInterface:eraseChip()
	log_printf("Result: %s %s", tostring(fOk), tostring(strMsg))
	assert(fOk, strMsg)
	
	-- flash the segments
	for iSegment, tSegment in ipairs(atSegments) do
		log_printf("Flashing Segment %d  offset:0x%08x  size: %d", iSegment, tSegment.offset, tSegment.size)
		fOk, strMsg = tFlasherInterface:flash(tSegment.offset, tSegment.data)
		log_printf("Flashed Segment %d  offset:0x%08x  size: %d", iSegment, tSegment.offset, tSegment.size)
		log_printf("Result: %s %s", tostring(fOk), tostring(strMsg))
		assert(fOk)
	end
	
	-- verify the segments
	for iSegment, tSegment in ipairs(atSegments) do
		log_printf("Verifying Segment %d  offset:0x%08x  size: %d", iSegment, tSegment.offset, tSegment.size)
		fOk, strMsg = tFlasherInterface:verify(tSegment.offset, tSegment.data)
		log_printf("Verified Segment %d  offset:0x%08x  size: %d", iSegment, tSegment.offset, tSegment.size)
		log_printf("Result: %s %s", tostring(fOk), tostring(strMsg))
		assert(fOk)
	end
	
	-- read back
	fOk = true
	for iSegment, tSegment in ipairs(atSegments) do
		log_printf("Reading Segment %d  offset:0x%08x  size: %d", iSegment, tSegment.offset, tSegment.size)
		local strData, strMsg = tFlasherInterface:read(tSegment.offset, tSegment.size)
		log_printf("Read Segment %d  offset:0x%08x  size: %d", iSegment, tSegment.offset, tSegment.size)
		
		assert(strData, strMsg or "Error reading segment")
		
		if strData == tSegment.data then
			log_printf("Segment %d equal", iSegment)
		else
			log_printf("Segment %d differs!", iSegment)
			fOk = false
		end
		
	end
	assert(fOk, "Errors in read segments")
	
	
	
	
	-- Read an image of the whole chip. 
	-- Check that the data segments have been writen correctly 
	-- and that the space in-between is empty (ff)

	-- Read image
	log_printf("Reading image")
	strImage, strMsg = tFlasherInterface:readChip()
	log_printf("Image read")
	
	-- Compare the segments and check the space in-between
	table.sort(atSegments, function(a, b) return a.offset<b.offset end)
	
	for iSegment, tSegment in ipairs(atSegments) do
	log_printf("Comparing Segment %d with image. offset:0x%08x  size: %d", iSegment, tSegment.offset, tSegment.size)
		local iStart = tSegment.offset + 1
		local iEnd   = tSegment.offset + tSegment.size 
		local iNextStart
		
		local strData = strImage:sub(iStart, iEnd)
		assert(strData == tSegment.data, "Segment does not match")
		
		if iSegment < #atSegments then
			tSegment = atSegments[iSegment+1]
			iNextStart = tSegment.offset
		else
			iNextStart = ulDeviceSize
		end

		log_printf("Checking Range 0x%08x - 0x%08x", iEnd, iNextStart)
		for iPos = iEnd+1, iNextStart do
			assert(strImage:byte(iPos) == 0xff, string.format("0x%08x non-empty", iPos))
		end
	
	end
	
	
	-- Erase the segments
	for iSegment, tSegment in ipairs(atSegments) do
		log_printf("Erasing Segment %d  offset:0x%08x  size: %d", iSegment, tSegment.offset, tSegment.size)
		fOk, strMsg = tFlasherInterface:erase(tSegment.offset, tSegment.size)
		log_printf("Erased Segment %d  offset:0x%08x  size: %d", iSegment, tSegment.offset, tSegment.size)
		log_printf("Result: %s %s", tostring(fOk), tostring(strMsg))
		assert(fOk)
	end
	
	-- the flash should now be empty
	log_printf("Checking for emptyness")
	fOk, strMsg = tFlasherInterface:isChipErased()
	log_printf("Empty: %s %s", tostring(fOk), tostring(strMsg))
	assert(fOk)

	return true, "Test completed"
end



