import argparse
import json
import os
import os.path
import requests
import string
import xml.etree.ElementTree


class BinTray:
	__strApi = 'https://api.bintray.com'
	__strUser = None
	__strPasswd = None
	__strSubject = None
	__strRepository = None
	
	
	
	def __init__(self, strUser, strPasswd, strSubject, strRepository):
		self.__strUser       = strUser
		self.__strPasswd     = strPasswd
		self.__strSubject    = strSubject
		self.__strRepository = strRepository
	
	
	
	def version_exist(self, strPackage, strVersion):
		strRequest = os.path.join(self.__strApi, 'packages', self.__strSubject, self.__strRepository, strPackage, 'versions', strVersion)
		tRequest = requests.get(strRequest, auth=(self.__strUser, self.__strPasswd))
		
		if tRequest.status_code!=200 and tRequest.status_code!=404:
			raise Exception('Unknown respose code: %d', tRequest.status_code)
		
		fResult = (tRequest.status_code==200)
		return fResult
	
	
	
	def version_delete(self, strPackage, strVersion):
		strRequest = os.path.join(self.__strApi, 'packages', self.__strSubject, self.__strRepository, strPackage, 'versions', strVersion)
		tRequest = requests.delete(strRequest, auth=(self.__strUser, self.__strPasswd))
		
		if tRequest.status_code!=200:
			raise Exception('Failed to delete the version: %d', tRequest.status_code)
	
	
	
	def version_create(self, strPackage, strVersion, strDesc, strVcsId):
		strRequest = os.path.join(self.__strApi, 'packages', self.__strSubject, self.__strRepository, strPackage, 'versions')
		strData = json.dumps({'name':strVersion, 'desc':strDesc, 'vcs_tag':strVcsId})
		tRequest = requests.post(strRequest, strData, auth=(self.__strUser, self.__strPasswd))
		
		if tRequest.status_code!=201:
			raise Exception('Failed to create the version: %d', tRequest.status_code)
	
	
	
	def content_upload(self, strPackage, strVersion, strGroup, strFilename, strDestinationFilename):
		aGroup = string.split(strGroup, '.')
		aGroup.reverse()
		strGroupPath = '/'.join(aGroup)
		
		tFile = open(strFilename, 'rb')
		strRequest = os.path.join(self.__strApi, 'content', self.__strSubject, self.__strRepository, strGroupPath, strPackage, strVersion, strDestinationFilename) + ';bt_package=%s;bt_version=%s;publish=1'%(strPackage,strVersion)
		tRequest = requests.put(strRequest, tFile, auth=(self.__strUser, self.__strPasswd))
		tFile.close()
		
		if tRequest.status_code!=201:
			raise Exception('Failed to create the content: %d', tRequest.status_code)


tParser = argparse.ArgumentParser(description='Deploy some artifacts.')
tParser.add_argument('strArtifactsFilename', metavar='FILE', help='Read the artifact list from FILE.')
aOptions = tParser.parse_args()

strAuth = os.environ['BINTRAY_APITOKEN']
strUser,strApiToken = string.split(strAuth, ':')

# Open the XML file.
tXmlArtifacts = xml.etree.ElementTree.parse(aOptions.strArtifactsFilename)
tNodeRoot = tXmlArtifacts.getroot()


tBinTray = BinTray(strUser, strApiToken, 'muhkuh', 'Muhkuh')

# Loop over all targets and find all package/version combinations without duplicates.
aPackageVersions = set()
for tNodeTarget in tNodeRoot.findall('Project/Server/Target'):
	strPackage = tNodeTarget.find('ArtifactID').text
	strVersion = tNodeTarget.find('Version').text
	
	aPackageVersions.add((strPackage, strVersion))


# Loop over all package/version combinations. Delete existing version on the server. Create all versions on the server.
for strPackageVersion in aPackageVersions:
	strPackage = strPackageVersion[0]
	strVersion = strPackageVersion[1]
	
	print 'Checking if package %s, version %s exists.' % (strPackage,strVersion)
	fResult = tBinTray.version_exist(strPackage, strVersion)
	if fResult==True:
		print 'Package %s: version %s exisis already. Delete it.' % (strPackage,strVersion)
		tBinTray.version_delete(strPackage, strVersion)
	
	print 'Package %s: create version %s.' % (strPackage,strVersion)
	tBinTray.version_create(strPackage, strVersion, 'Build results from travis-ci.', '1234')


# Loop over all targets and upload the files.
for tNodeTarget in tNodeRoot.findall('Project/Server/Target'):
	strPackage   = tNodeTarget.find('ArtifactID').text
	strVersion   = tNodeTarget.find('Version').text
	strFile      = tNodeTarget.get('file')
	strGroup     = tNodeTarget.find('GroupID').text
	strPackaging = tNodeTarget.find('Packaging').text
	
	print 'Uploading %s.' % strFile
	tBinTray.content_upload(strPackage, strVersion, strGroup, strFile, '%s-%s.%s' % (strPackage,strVersion,strPackaging))

