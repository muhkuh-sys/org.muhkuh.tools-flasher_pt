from __future__ import unicode_literals    # at top of module
# Subprocess of pirate_install.py
# written by C.Thelen
# modified by A.Ballmert

import platform
import subprocess
import string
import re
import os


programName="PlatformDetect"
version="0_0_1"
date="2018_08_07"

# defines for matrix
enWin=0
enLin=1
enx86=0
enx64=1
enERR='ERROR'

class PlatformDetect:
    def __init__(self):
        self.strHostCpuArchitecture = None
        self.strHostDistributionId = None
        self.strHostDistributionVersion = None
        self.strStandardArchiveFormat = None
        self.detect()

    def __windows_get_cpu_architecture_env(self):
        strCpuArchitecture = None
        strEnvProcessorArchitecture = None
        strEnvProcessorArchiteW6432 = None
        if 'PROCESSOR_ARCHITECTURE' in os.environ:
            strEnvProcessorArchitecture = string.lower(os.environ['PROCESSOR_ARCHITECTURE'])
        if 'PROCESSOR_ARCHITEW6432' in os.environ:
            strEnvProcessorArchiteW6432 = string.lower(os.environ['PROCESSOR_ARCHITEW6432'])
        # See here for details: https://blogs.msdn.microsoft.com/david.wang/
        # 2006/03/27/howto-detect-process-bitness/
        if((strEnvProcessorArchitecture == 'amd64') or
           (strEnvProcessorArchiteW6432 == 'amd64')):
            strCpuArchitecture = 'x86_64'
        elif((strEnvProcessorArchitecture == 'x86') and
             (strEnvProcessorArchiteW6432 is None)):
            strCpuArchitecture = 'x86'
        else:
            print('Failed to detect the CPU architecture on Windows with the '
                  'ENV variables.')
            print('PROCESSOR_ARCHITECTURE = %s' %
                  (str(strEnvProcessorArchitecture)))
            print('PROCESSOR_ARCHITEW6432 = %s' %
                  (str(strEnvProcessorArchiteW6432)))

        return strCpuArchitecture

    def __linux_get_os_architecture_getconf(self):
        strCpuArchitecture = None

        # Try to parse the output of the 'getconf LONG_BIT' command.
        strOutput = subprocess.check_output(['getconf', 'LONG_BIT'])
        strOutputStrip = strOutput.strip()
        if strOutputStrip == '32':
            strCpuArchitecture = 'x86'
        elif strOutputStrip == '64':
            strCpuArchitecture = 'x86_64'

        return strCpuArchitecture

    def __linux_get_cpu_architecture_lscpu(self):
        strCpuArchitecture = None
        astrReplacements = {
            'i386': 'x86',
            'i486': 'x86',
            'i586': 'x86',
            'i686': 'x86'
        }

        # Try to parse the output of the 'lscpu' command.
        strOutput = subprocess.check_output(['lscpu'])
        tMatch = re.search('Architecture: *(\S+)', strOutput)
        if tMatch is None:
            raise Exception('Failed to get the CPU architecture with "lscpu".')

        strCpuArchitecture = tMatch.group(1)
        # Replace the CPU architectures found in the list.
        if strCpuArchitecture in astrReplacements:
            strCpuArchitecture = astrReplacements[strCpuArchitecture]

        return strCpuArchitecture

    def __linux_detect_distribution_etc_lsb_release(self):
        strDistributionId = None
        strDistributionVersion = None

        # Try to open /etc/lsb-release.
        tFile = open('/etc/lsb-release', 'rt')
        if tFile is None:
            raise Exception('Failed to detect the Linux distribution with '
                            '/etc/lsb-release.')
        for strLine in tFile:
            tMatch = re.match('DISTRIB_ID=(.+)', strLine)
            if tMatch is not None:
                strDistributionId = string.lower(tMatch.group(1))
            tMatch = re.match('DISTRIB_RELEASE=(.+)', strLine)
            if tMatch is not None:
                strDistributionVersion = tMatch.group(1)
        tFile.close()

        # Return both components or none.
        if (strDistributionId is None) or (strDistributionVersion is None):
            strDistributionId = None
            strDistributionVersion = None

        return strDistributionId, strDistributionVersion

    def detect(self):
        strSystem = platform.system()
        if strSystem == 'Windows':
            # This is windows.

            # Detect the CPU architecture.
            self.strHostCpuArchitecture =\
                self.__windows_get_cpu_architecture_env()

            # Set the distribution version and ID.
            self.strHostDistributionId = 'windows'
            self.strHostDistributionVersion = ''

            # Windows uses ZIP as standard archive format.
            self.strStandardArchiveFormat = 'zip'
        elif strSystem == 'Linux':
            # This is a Linux.

            # Detect the CPU architecture.
            # Prefer the OS architecture over the CPU architecture to honour a
            # 32bit OS on a 64bit CPU. This happens with a 32bit Docker
            # container on a 64bit host.
            strCpuArch = self.__linux_get_os_architecture_getconf()
            if strCpuArch is None:
                strCpuArch = self.__linux_get_cpu_architecture_lscpu()
            self.strHostCpuArchitecture = strCpuArch

            # Detect the distribution.
            self.strHostDistributionId, self.strHostDistributionVersion =\
                self.__linux_detect_distribution_etc_lsb_release()

            # Linux uses TAR GZIP as standard archive format.
            self.strStandardArchiveFormat = 'tar.gz'
        else:
            raise Exception('Unknown platform: "%s"' % (strSystem))

#x=PlatformDetect()
#x.detect()
#print x.strHostCpuArchitecture

def GetPlatformMatrixEntry():
    
    x=PlatformDetect()

    ThePlatform=platform.system()
    theMachine=x.strHostCpuArchitecture

    # print "[pirate]: running %s on %s\n"%(ThePlatform,theMachine)
    
    cOS=''
    cPL=''
    
    if(theMachine=='x86'):
        cPL=enx86
    elif(theMachine=='x86_64'):
        cPL=enx64
    else:
        cPL=enERR
    if(ThePlatform=='Windows'):
        cOS=enWin
    elif(ThePlatform=='Linux'):
        cOS=enLin
    else:
        cOS=enERR
    return cOS,cPL,ThePlatform,theMachine



def UsePlatformMatrixExample():
    a=[['']*2 for x in range(2)]
    # print os.path.join("dpinst32.exe /q /s /f")
    # os.pat.join cartes for / vs. \ (arg1,arg2,arg3,...)
    # os.path.expanduser("~")    
    # Put in here the commands depending on the architecture
    #[ cOS ][ cPL ]='Command according to plattform'
    a[enWin][enx86]=os.path.join("dir")
    a[enWin][enx64]=os.path.join("whoami")
    a[enLin][enx86]='ls -lach'
    a[enLin][enx64]='uname'
    
    cOS,cPL,ThePlatform,theMachine = GetPlatformMatrixEntry()
    
    if cOS is enERR or cPL is enERR:
        print ('[pirate]: Error in Platform detection')
        exit(11)
    else:
        p=''
        if a[cOS][cPL] is not 'not_implemented':
            print ("[pirate] run: %s"%(a[cOS][cPL]))
            p = subprocess.Popen(a[cOS][cPL], shell=True, stdout = subprocess.PIPE)
            if(p!=''):
                stdout, stderr = p.communicate()
                if stdout:
                    print ('[pirate] stdout: ...')
                    print (stdout)
                if stderr:
                    print ('[pirate] stderr: ...')
                    print (stderr)
                print ("[pirate] Retrunvalue: %d"%(p.returncode)) # is 0 if success
                exit(p.returncode)
        else:
            print ("[pirate] No installation for %s on %s due to no command given"%(ThePlatform,theMachine))
            exit(12)

if __name__ == "__main__":
    UsePlatformMatrixExample()

