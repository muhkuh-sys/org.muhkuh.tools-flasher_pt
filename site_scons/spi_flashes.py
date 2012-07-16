# -*- coding: utf-8 -*-
#-------------------------------------------------------------------------#
#   Copyright (C) 2012 by Christoph Thelen                                #
#   doc_bacardi@users.sourceforge.net                                     #
#                                                                         #
#   This program is free software; you can redistribute it and/or modify  #
#   it under the terms of the GNU General Public License as published by  #
#   the Free Software Foundation; either version 2 of the License, or     #
#   (at your option) any later version.                                   #
#                                                                         #
#   This program is distributed in the hope that it will be useful,       #
#   but WITHOUT ANY WARRANTY; without even the implied warranty of        #
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         #
#   GNU General Public License for more details.                          #
#                                                                         #
#   You should have received a copy of the GNU General Public License     #
#   along with this program; if not, write to the                         #
#   Free Software Foundation, Inc.,                                       #
#   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             #
#-------------------------------------------------------------------------#


import re
import string
import xml.etree.ElementTree

from SCons.Script import *


strHead = """/***************************************************************************
 *   Copyright (C) 2008 by Hilscher GmbH                                   *
 *   cthelen@hilscher.com                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#include "spi_flash_types.h"

/* uncomment the next line to disable some strange flashes with byte program only */
/* #define __NO_1BYTEPERPAGE_FLASHES__ */

const SPIFLASH_ATTRIBUTES_T atKnownSpiFlashTypes[] =
{
"""


aTemplateLines = [
	('.@name',                           '                                 .acName = "%s\\0",',    '/* name                       */'),
	('.@size',                           '                                 .ulSize = %d,',        '/* size                       */'),
	('.@clock',                          '                                .ulClock = %d,',        '/* minClock                   */'),
	('Layout@pageSize',                  '                             .ulPageSize = %d,',        '/* pageSize                   */'),
	('Layout@sectorPages',               '                          .ulSectorPages = %d,',        '/* sectorSize                 */'),
	('Layout@mode',                      '                               .tAdrMode = %s,',        '/* address mode               */'),
	('Read@readArrayCommand',            '                           .ucReadOpcode = 0x%02x,',    '/* readOpcode                 */'),
	('Read@ignoreBytes',                 '                    .ucReadOpcodeDCBytes = %d,',        '/* readOpcodeDCBytes          */'),
	('Write@writeEnableCommand',         '                    .ucWriteEnableOpcode = 0x%02x,',    '/* writeEnableOpcode          */'),
	('Erase@erasePageCommand',           '                      .ucErasePageOpcode = 0x%02x,',    '/* erase page                 */'),
	('Erase@eraseSectorCommand',         '                    .ucEraseSectorOpcode = 0x%02x,',    '/* eraseSectorOpcode          */'),
	('Erase@eraseChipCommandLen',        '                      .uiEraseChipCmdLen = %d,',        '/* erase chip command length  */'),
	('Erase@eraseChipCommandHex',        '                        .aucEraseChipCmd = {%s},',      '/* erase chip command         */'),
	('Write@pageProgramCommand',         '                       .ucPageProgOpcode = 0x%02x,',    '/* pageProgOpcode             */'),
	('Write@bufferFillCommand',          '                           .ucBufferFill = 0x%02x,',    '/* buffer fill opcode         */'),
	('Write@bufferWriteCommand',         '                    .ucBufferWriteOpcode = 0x%02x,',    '/* buffer write opcode        */'),
	('Write@eraseAndPageProgramCommand', '               .ucEraseAndPageProgOpcode = 0x%02x,',    '/* eraseAndPageProgOpcode     */'),
	('Status@readStatusCommand',         '                     .ucReadStatusOpcode = 0x%02x,',    '/* readStatusOpcode           */'),
	('Status@statusReadyMask',           '                      .ucStatusReadyMask = 0x%02x,',    '/* statusReadyMask            */'),
	('Status@statusReadyValue',          '                     .ucStatusReadyValue = 0x%02x,',    '/* statusReadyValue           */'),
	('Init0@commandLen',                 '                      .uiInitCmd0_length = %d,',        '/* initCmd0_length            */'),
	('Init0@commandHex',                 '                            .aucInitCmd0 = {%s},',      '/* initCmd0                   */'),
	('Init1@commandLen',                 '                      .uiInitCmd1_length = %d,',        '/* initCmd1_length            */'),
	('Init1@commandHex',                 '                            .aucInitCmd1 = {%s},',      '/* initCmd1                   */'),
	('Id@sendLen',                       '                             .uiIdLength = %d,',        '/* id_length                  */'),
	('Id@sendHex',                       '                              .aucIdSend = {%s},',      '/* id_send                    */'),
	('Id@maskHex',                       '                              .aucIdMask = {%s},',      '/* id_mask                    */'),
	('Id@magicHex',                      '                             .aucIdMagic = {%s}',       '/* id_magic                   */')
]

strFooter = """};


const size_t sizKnownSpiFlashTypes_len = sizeof(atKnownSpiFlashTypes)/sizeof(SPIFLASH_ATTRIBUTES_T);

"""


tGlobalFlashNode = None

def substitute_entry(tMatchObj):
	# Get the complete path.
	strAllPath = tMatchObj.group(1)
	
	# Split any attributes from the path.
	aPath = strAllPath.split("@")
	if len(aPath)>2:
		raise Exception("Malformed path: %s" % strAllPath)
	
	# Find the node.
	tNode = tGlobalFlashNode.find(aPath[0])
	if tNode is None:
		raise Exception("Could not find node at path: %s" % strAllPath)
	
	# Is this a text or attribute request?
	if len(aPath)==1:
		# This is a text request.
		strValue = tNode.text
	else:
		# This is an attribute request.
		if not aPath[1] in tNode.attrib:
			 raise Exception("Node at path %s has no attribute %s" % (aPath[0], aPath[1]))
		strValue = tNode.attrib[aPath[1]]
	
	return strValue



DATATYPE_STRING = 0
DATATYPE_NUMBER = 1
DATATYPE_NUMBER_ARRAY = 2

def get_value(tFlashNode, strPath, eType):
	# Split any attributes from the path.
	aPath = strPath.split("@")
	if len(aPath)>2:
		raise Exception("Invalid path: %s" % strPath)
	
	# Find the node.
	tNode = tFlashNode.find(aPath[0])
	if tNode is None:
		raise Exception("Could not find node at path: %s" % aPath[0])
	
	# Is this a text or attribute request?
	if len(aPath)==1:
		# This is a text request.
		strValue = tNode.text.strip()
	else:
		# This is an attribute request.
		if not aPath[1] in tNode.attrib:
			 raise Exception("Node at path %s has no attribute %s" % (aPath[0], aPath[1]))
		strValue = tNode.attrib[aPath[1]]
	
	# Convert the value to the requested type.
	if eType==DATATYPE_STRING:
		tResult = strValue
	elif eType==DATATYPE_NUMBER:
		tResult = int(strValue,0)
	elif eType==DATATYPE_NUMBER_ARRAY:
		# Split the string into numbers and convert them to integers.
		if strValue=='':
			tResult = []
		else:
			tResult = [ int(strByte.strip(),0) for strByte in strValue.split(',')]
	else:
		raise Exception("Unknown type:", eType)
	
	return tResult


aHexDumpEntries = [
	'Erase@eraseChipCommand',
	'Init0@command',
	'Init1@command',
	'Id@send',
	'Id@mask',
	'Id@magic'
]

def spiflashes_action(target, source, env):
	global tGlobalFlashNode
	
	# Read the XML flash descriptions.
	tXml = xml.etree.ElementTree.ElementTree()
	tXml.parse(source[0].get_path())

	# Get the maximum sizes for the following arrays.
	aMaxSize = dict({
		'Erase@eraseChipCommand': 0,
		'Init0@command': 0,
		'Init1@command': 0,
		'Id@send': 0
	})
	
	# Loop over all "SerialFlash" nodes.
	aFlashes = []
	aFlashNames = []
	for tFlashNode in tXml.findall('SerialFlash'):
		aEntry = dict({})
		
		# Get the "Description" node.
		tDescriptionNode = tFlashNode.find('Description')
		if tDescriptionNode is None:
			raise Exception("No Description node.")
		aEntry['Description'] = tDescriptionNode.text
		
		# Add any notes.
		aNotes = []
		for tNoteNode in tFlashNode.findall('Note'):
			strNote = tNoteNode.text
			if not strNote is None: 
				aNotes.append(strNote)
		aEntry['Note'] = aNotes
		
		# Get all values.
		aEntryNames = dict({
			'.@name':                              DATATYPE_STRING,
			'.@size':                              DATATYPE_NUMBER,
			'.@clock':                             DATATYPE_NUMBER,
			
			'Layout@pageSize':                     DATATYPE_NUMBER,
			'Layout@sectorPages':                  DATATYPE_NUMBER,
			'Layout@mode':                         DATATYPE_STRING,
			
			'Read@readArrayCommand':               DATATYPE_NUMBER_ARRAY,
			'Read@ignoreBytes':                    DATATYPE_NUMBER,
			
			'Write@writeEnableCommand':            DATATYPE_NUMBER_ARRAY,
			'Write@pageProgramCommand':            DATATYPE_NUMBER_ARRAY,
			'Write@bufferFillCommand':             DATATYPE_NUMBER_ARRAY,
			'Write@bufferWriteCommand':            DATATYPE_NUMBER_ARRAY,
			'Write@eraseAndPageProgramCommand':    DATATYPE_NUMBER_ARRAY,
			
			'Erase@erasePageCommand':              DATATYPE_NUMBER_ARRAY,
			'Erase@eraseSectorCommand':            DATATYPE_NUMBER_ARRAY,
			'Erase@eraseChipCommand':              DATATYPE_NUMBER_ARRAY,
			
			'Status@readStatusCommand':            DATATYPE_NUMBER_ARRAY,
			'Status@statusReadyMask':              DATATYPE_NUMBER,
			'Status@statusReadyValue':             DATATYPE_NUMBER,
			
			'Init0@command':                       DATATYPE_NUMBER_ARRAY,
			'Init1@command':                       DATATYPE_NUMBER_ARRAY,
			
			'Id@send':                             DATATYPE_NUMBER_ARRAY,
			'Id@mask':                             DATATYPE_NUMBER_ARRAY,
			'Id@magic':                            DATATYPE_NUMBER_ARRAY	
		})
		for strPath,eType in aEntryNames.iteritems():
			aEntry[strPath] = get_value(tFlashNode, strPath, eType)
		
		
		# Is this entry unique?
		strDeviceName = aEntry['.@name'] 
		if strDeviceName in aFlashNames:
			raise Exception('Device %s defined multiple times. The device name must be unique!' % strDeviceName)
		aFlashNames.append(strDeviceName)
		

		# Set the length for the hexdump entries.
		# NOTE: this must be done before the assignment of the default values.
		for strPath in aHexDumpEntries:
			# Set the length of the field.
			aEntry[strPath+'Len'] = len(aEntry[strPath])
		
		
		# These commands are optional, replace an empty array with the empty command sequence.
		aOptionalCommands = [
			'Write@writeEnableCommand',
			'Write@pageProgramCommand',
			'Write@bufferFillCommand',
			'Write@bufferWriteCommand',
			'Write@eraseAndPageProgramCommand',
			'Erase@erasePageCommand',
			'Erase@eraseSectorCommand',
			'Erase@eraseChipCommand',
			'Init0@command',
			'Init1@command'
		]
		# Loop over all optional commands.
		for strPath in aOptionalCommands:
			# Is the array empty?
			if len(aEntry[strPath])==0:
				# Yes, it is empty.
				# Replace it with the default empty command.
				aEntry[strPath] = [0]
		
 		
 		# Check that all entries in this list have only one array element.
 		# This is hard-coded in the SPI routines. They need to be modified if this is
 		# no longer true.  
		aSingleByteCommands = [
			'Read@readArrayCommand',
			'Write@writeEnableCommand',
			'Write@pageProgramCommand',
			'Write@bufferFillCommand',
			'Write@bufferWriteCommand',
			'Write@eraseAndPageProgramCommand',
			'Erase@erasePageCommand',
			'Erase@eraseSectorCommand',
			'Status@readStatusCommand'
		]
		# Loop over all optional commands.
		for strPath in aSingleByteCommands:
			# Does the array have exactly one entry?
			if len(aEntry[strPath])!=1:
				# No, it has a different size.
				raise Exception('Device %s: The command %s must be a single-byte command. Change the SPI code to change this.' % (strDeviceName, strPath))
			else:
				# Convert the array to a single value.
				ucByte = aEntry[strPath][0]
				aEntry[strPath] = ucByte
		
		
		# All ID attributes must have the same size.
		aIdEntries = [
			'Id@send',
			'Id@mask',
			'Id@magic'
		]
		sizId = len(aEntry[aIdEntries[0]])
		for strPath in aIdEntries:
			if len(aEntry[strPath])!=sizId:
				raise Exception('Device %s: The ID entries must have the same size!' % strDeviceName)


		# Create a hexdump for the selected commands.
		for strPath in aHexDumpEntries:
			# Create the hex dump for this entry.
			aEntry[strPath+'Hex'] = string.join(['0x%02x'%ucByte for ucByte in aEntry[strPath]], ', ')
		
		
		# Convert the layout mode to the enum.
		aLayoutMode = dict({
			'linear': 'SPIFLASH_ADR_LINEAR',
			'pagesize bitshift': 'SPIFLASH_ADR_PAGESIZE_BITSHIFT'
		})
		strMode = aEntry['Layout@mode']
		if not strMode in aLayoutMode:
			raise Exception('Device %s: Unknown layout mode: %s' % strDeviceName, strMode)
		# Translate the mode name to the enum element.
		aEntry['Layout@mode'] = aLayoutMode[strMode]
		
		
		# Update the maximum size of this entry.
		for strPath,sizMax in aMaxSize.iteritems():
			sizEntry = len(aEntry[strPath])
			if sizEntry>sizMax:
				aMaxSize[strPath] = sizEntry
		
		aFlashes.append(aEntry)
	
	# Show the maximum elements:
	print aMaxSize
	
	
	astrFlashes = []
	astrFlashes.append(strHead)
	uiIndent = 88
	for aEntry in aFlashes:
		# Append the description.
		astrFlashes.append('        /* %s */' % aEntry['Description'])
		# Append all notes.
		for strNote in aEntry['Note']:
			astrFlashes.append('        /* %s */' % strNote)
		astrFlashes.append('        {')
		for (strPath,strPattern,strComment) in aTemplateLines:
			strLine = strPattern % aEntry[strPath]
			sizLine = len(strLine)
			if sizLine<uiIndent:
				strLine += ' '*(uiIndent-sizLine)
			strLine += strComment
			astrFlashes.append(strLine)
		astrFlashes.append('        },')
		astrFlashes.append('        ')
	astrFlashes.append(strFooter)
	
	# Write the result.
	tFile = open(target[0].get_path(), 'wt')
	tFile.write(string.join(astrFlashes, '\n'))
	tFile.close()
	
	return None



def spiflashes_emitter(target, source, env):
	# Nothing yet.
	return target, source



def spiflashes_string(target, source, env):
	return 'SPIFlashes %s' % target[0].get_path()



def ApplyToEnv(env):
	#----------------------------------------------------------------------------
	#
	# Add SPI Flashes builder.
	#
	
	spiflashes_act = SCons.Action.Action(spiflashes_action, spiflashes_string)
	spiflashes_bld = Builder(action=spiflashes_act, emitter=spiflashes_emitter, suffix='.c', src_suffix='.xml', single_source=1)
	env['BUILDERS']['SPIFlashes'] = spiflashes_bld
