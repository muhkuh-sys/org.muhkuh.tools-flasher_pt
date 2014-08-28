import json
import os
import os.path
import requests
import string



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

strAuth = os.environ['BINTRAY_APITOKEN']
strUser,strApiToken = string.split(strAuth, ':')

strPackage = 'flasher'
strVersion = 'SNAPSHOT'

tBinTray = BinTray(strUser, strApiToken, 'muhkuh', 'Muhkuh')
fResult = tBinTray.version_exist(strPackage, strVersion)
if fResult==True:
	print 'The version %s exisis already. Delete it.' % strVersion
	tBinTray.version_delete(strPackage, strVersion)
tBinTray.version_create(strPackage, strVersion, 'Build results from travis-ci.', '1234')

tBinTray.content_upload(strPackage, strVersion, 'tools.muhkuh.org', 'targets/ivy/repository/org/muhkuh/tools/flasher/SNAPSHOT/flasher-SNAPSHOT.zip', 'flasher.zip')
tBinTray.content_upload(strPackage, strVersion, 'tools.muhkuh.org', 'targets/ivy/repository/org/muhkuh/tools/flasher/SNAPSHOT/ivy-SNAPSHOT.xml',     'ivy.xml')
tBinTray.content_upload(strPackage, strVersion, 'tools.muhkuh.org', 'targets/ivy/flasher_cli/targets/flasher_cli_windows_amd64-SNAPSHOT.zip',        'flasher_cli_windows_amd64.zip')
tBinTray.content_upload(strPackage, strVersion, 'tools.muhkuh.org', 'targets/ivy/flasher_cli/targets/flasher_cli_windows_x86-SNAPSHOT.zip',          'flasher_cli_windows_x86.zip')


