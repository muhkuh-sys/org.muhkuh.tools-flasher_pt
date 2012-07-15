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
	('                                 .acName = "%s\0",',    '/* name                       */'),
	('                                 .ulSize = %d,',        '/* size                       */'),
	('                                .ulClock = %d,',        '/* minClock                   */'),
	('                             .ulPageSize = %d,',        '/* pageSize                   */'),
	('                          .ulSectorPages = %d,',        '/* sectorSize                 */'),
	('                               .tAdrMode = %s,',        '/* address mode               */'),
	('                           .ucReadOpcode = 0x%02x,',    '/* readOpcode                 */'),
	('                    .ucReadOpcodeDCBytes = %d,',        '/* readOpcodeDCBytes          */'),
	('                    .ucWriteEnableOpcode = 0x%02x,',    '/* writeEnableOpcode          */'),
	('                      .ucErasePageOpcode = 0x%02x,',    '/* erase page                 */'),
	('                    .ucEraseSectorOpcode = 0x%02x,',    '/* eraseSectorOpcode          */'),
	('                      .uiEraseChipCmdLen = %d,',        '/* erase chip command length  */'),
	('                        .aucEraseChipCmd = {0x60},',    '/* erase chip command         */'),
	('                       .ucPageProgOpcode = 0x%02x,',    '/* pageProgOpcode             */'),
	('                           .ucBufferFill = 0x%02x,',    '/* buffer fill opcode         */'),
	('                    .ucBufferWriteOpcode = 0x%02x,',    '/* buffer write opcode        */'),
	('               .ucEraseAndPageProgOpcode = 0x%02x,',    '/* eraseAndPageProgOpcode     */'),
	('                     .ucReadStatusOpcode = 0x%02x,',    '/* readStatusOpcode           */'),
	('                      .ucStatusReadyMask = 0x%02x,',    '/* statusReadyMask            */'),
	('                     .ucStatusReadyValue = 0x%02x,',    '/* statusReadyValue           */'),
	('                      .uiInitCmd0_length = %d,',        '/* initCmd0_length            */'),
	('                            .aucInitCmd0 = {%s},',      '/* initCmd0                   */'),
	('                      .uiInitCmd1_length = %d,',        '/* initCmd1_length            */'),
	('                            .aucInitCmd1 = {%s},',      '/* initCmd1                   */'),
	('                             .uiIdLength = %d,',        '/* id_length                  */'),
	('                              .aucIdSend = {%s},',      '/* id_send                    */'),
	('                              .aucIdMask = {%s},',      '/* id_mask                    */'),
	('                             .aucIdMagic = {%s}',       '/* id_magic                   */')
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
	aFlashes = dict({})
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
		if strDeviceName in aFlashes:
			raise Exception('Device %s defined multiple times. The device name must be unique!' % strDeviceName)
		
		
		# These commands are optional, replace an empty array with the empty command sequence.
		aOptionalCommands = [
			'Write@writeEnableCommand',
			'Write@pageProgramCommand',
			'Write@bufferFillCommand',
			'Write@bufferWriteCommand',
			'Write@eraseAndPageProgramCommand',
			'Erase@erasePageCommand',
			'Erase@eraseSectorCommand',
			'Erase@eraseChipCommand'
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
		
		# Update the maximum size of this entry.
		for strPath,sizMax in aMaxSize.iteritems():
			sizEntry = len(aEntry[strPath])
			if sizEntry>sizMax:
				aMaxSize[strPath] = sizEntry
		
		aFlashes[strDeviceName] = aEntry
	
	# Show the maximum elements:
	print aMaxSize
# 		print aEntry
#		#--------------------------------------------------------------------
#		# Replace all elements.
#		#--------------------------------------------------------------------
#		tGlobalFlashNode = tFlashNode 
#		strEntry = re.sub('\$\{([^}]+)\}', substitute_entry, strTemplate)
#		
#		print strHeader
#		print strEntry
		
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
