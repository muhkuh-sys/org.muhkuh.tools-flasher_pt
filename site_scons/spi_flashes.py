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


import os.path
import re
import string
import xml.etree.ElementTree

from string import Template

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
	('.@name',                           '                                 .acName = "%s\\0",',   '/* name                       */'),
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
	('Erase@eraseChipCommandLen',        '                      .ucEraseChipCmdLen = %d,',        '/* erase chip command length  */'),
	('Erase@eraseChipCommandHex',        '                        .aucEraseChipCmd = {%s},',      '/* erase chip command         */'),
	('Write@pageProgramCommand',         '                       .ucPageProgOpcode = 0x%02x,',    '/* pageProgOpcode             */'),
	('Write@bufferFillCommand',          '                           .ucBufferFill = 0x%02x,',    '/* buffer fill opcode         */'),
	('Write@bufferWriteCommand',         '                    .ucBufferWriteOpcode = 0x%02x,',    '/* buffer write opcode        */'),
	('Write@eraseAndPageProgramCommand', '               .ucEraseAndPageProgOpcode = 0x%02x,',    '/* eraseAndPageProgOpcode     */'),
	('Status@readStatusCommand',         '                     .ucReadStatusOpcode = 0x%02x,',    '/* readStatusOpcode           */'),
	('Status@statusReadyMask',           '                      .ucStatusReadyMask = 0x%02x,',    '/* statusReadyMask            */'),
	('Status@statusReadyValue',          '                     .ucStatusReadyValue = 0x%02x,',    '/* statusReadyValue           */'),
	('Init0@commandLen',                 '                      .ucInitCmd0_length = %d,',        '/* initCmd0_length            */'),
	('Init0@commandHex',                 '                            .aucInitCmd0 = {%s},',      '/* initCmd0                   */'),
	('Init1@commandLen',                 '                      .ucInitCmd1_length = %d,',        '/* initCmd1_length            */'),
	('Init1@commandHex',                 '                            .aucInitCmd1 = {%s},',      '/* initCmd1                   */'),
	('Id@sendLen',                       '                             .ucIdLength = %d,',        '/* id_length                  */'),
	('Id@sendHex',                       '                              .aucIdSend = {%s},',      '/* id_send                    */'),
	('Id@maskHex',                       '                              .aucIdMask = {%s},',      '/* id_mask                    */'),
	('Id@magicHex',                      '                             .aucIdMagic = {%s}',       '/* id_magic                   */')
]

strFooter = """};

"""


strHeaderTemplate = """
#ifndef ${DEFINE}
#define ${DEFINE}


#include <stddef.h>


/*
   The T_SPIFLASH_ADR enumeration defines the addressing mode for a spi flash.

   * SPIFLASH_ADR_LINEAR is linear addressing, it's like a normal memory. It is
     used for devices with a power-of-2 pagesize.
   * SPIFLASH_ADR_PAGESIZE_BITSHIFT is used for devices with other pagesizes
     than power-of-2. The address is a combination of the page offset and the
     shifted page number. The page number is shifted by the maximum number of
     bits the page offset can occupy.
     This addressing mode is used for Atmel flashes.
*/
typedef enum SPIFLASH_ADR_Ttag
{
	SPIFLASH_ADR_LINEAR,					    /* linear addressing */
	SPIFLASH_ADR_PAGESIZE_BITSHIFT		/* bitshift derived from the pagesize */
} SPIFLASH_ADR_T;


/*
   The structure SPIFLASH_ATTRIBUTES_T defines the attributes and commands for
   an spi flash. It provides the identify sequence for the device and the
   commands to erase, read and write data.
*/

/* size of the spiFlashAttributes name field */
#define SPIFLASH_NAME_SIZE ${SIZEOF_NAME}

/* size of the erase chip command field */
#define SPIFLASH_ERASECHIP_SIZE ${SIZEOF_ERASE_CHIP}

/* size of the spiFlashAttributes init fields */
#define SPIFLASH_INIT0_SIZE ${SIZEOF_INIT0}
#define SPIFLASH_INIT1_SIZE ${SIZEOF_INIT1}

/* size of the spiFlashAttributes id fields */
#define SPIFLASH_ID_SIZE ${SIZEOF_ID}


typedef struct SPIFLASH_ATTRIBUTES_Ttag
{
	char            acName[SPIFLASH_NAME_SIZE+1];                   /* name of the flash, 0 terminated                              */
	unsigned long   ulSize;                                         /* size of the flash memory in bytes                            */
	unsigned long   ulClock;                                        /* maximum speed in kHz                                         */
	unsigned long   ulPageSize;                                     /* size of one page in bytes                                    */
	unsigned long   ulSectorPages;                                  /* size of one sector in pages                                  */
	SPIFLASH_ADR_T  tAdrMode;                                       /* addressing mode                                              */
	unsigned char   ucReadOpcode;                                   /* opcode for 'continuous array read' command                   */
	unsigned char   ucReadOpcodeDCBytes;                            /* don't care bytes after readOpcode and address                */
	unsigned char   ucWriteEnableOpcode;                            /* opcode for 'write enable' command, 0x00 means no write protect mechanism */
	unsigned char   ucErasePageOpcode;                              /* opcode for 'erase page'                                      */
	unsigned char   ucEraseSectorOpcode;                            /* opcode for 'erase sector'                                    */
	unsigned char   ucEraseChipCmdLen;                              /* length of the 'erase chip' command, 0 means not available    */
	unsigned char   aucEraseChipCmd[SPIFLASH_ERASECHIP_SIZE];       /* command to erase the complete chip                           */
	unsigned char   ucPageProgOpcode;                               /* opcode for 'page program (without buildin erase)'            */
	unsigned char   ucBufferFill;                                   /* opcode for 'fill buffer with data'                           */
	unsigned char   ucBufferWriteOpcode;                            /* opcode for 'write buffer to flash'                           */
	unsigned char   ucEraseAndPageProgOpcode;                       /* opcode for 'page program with buildin erase'                 */
	unsigned char   ucReadStatusOpcode;                             /* opcode for 'read status register'                            */
	unsigned char   ucStatusReadyMask;                              /* the bitmask indicating device busy                           */
	unsigned char   ucStatusReadyValue;                             /* eor bitmask for device busy                                  */
	unsigned char   ucInitCmd0_length;                              /* length of the first init command in bytes                    */
	unsigned char   aucInitCmd0[SPIFLASH_INIT0_SIZE];               /* first command string to init the device                      */
	unsigned char   ucInitCmd1_length;                              /* length of the second init command in bytes                   */
	unsigned char   aucInitCmd1[SPIFLASH_INIT1_SIZE];               /* second command string to init the device                     */
	unsigned char   ucIdLength;                                     /* length in bytes of the id_send, id_mask and id_magic fields  */
	unsigned char   aucIdSend[SPIFLASH_ID_SIZE];                    /* command string to request the id                             */
	unsigned char   aucIdMask[SPIFLASH_ID_SIZE];                    /* mask for the device id. the data received from the id_send command will be anded with this field */
	unsigned char   aucIdMagic[SPIFLASH_ID_SIZE];                   /* magic sequence of this device                                */
} SPIFLASH_ATTRIBUTES_T;

#define NUMBER_OF_SPIFLASH_ATTRIBUTES ${ELEMENTS}

#endif  /* ${DEFINE} */
"""


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
	# Read the XML flash descriptions.
	tXml = xml.etree.ElementTree.ElementTree()
	tXml.parse(source[0].get_path())

	# Get the maximum sizes for the following arrays.
	aMaxSize = dict({
		'.@name': 0,
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


	# Create the header for the array.
	strDefine = '__' + os.path.basename(target[1].get_path()).upper().replace('.', '_') + '__'
	aReplaceDict = dict({
		'DEFINE':             strDefine,
		'ELEMENTS':           len(aFlashes),

		'SIZEOF_NAME':        aMaxSize['.@name'],
		'SIZEOF_ERASE_CHIP':  aMaxSize['Erase@eraseChipCommand'],
		'SIZEOF_INIT0':       aMaxSize['Init0@command'],
		'SIZEOF_INIT1':       aMaxSize['Init1@command'],
		'SIZEOF_ID':          aMaxSize['Id@send']
	})
	strHeader = string.Template(strHeaderTemplate).safe_substitute(aReplaceDict)

	tFile = open(target[1].get_path(), 'wt')
	tFile.write(strHeader)
	tFile.close()
	
	return None



def spiflashes_emitter(target, source, env):
	# This rule also builds a header.
	strPath = os.path.splitext(target[0].get_path())[0] + '.h'
	target.append(File(strPath))
	
	# Depend on this builder.
	Depends(target, __file__)

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
