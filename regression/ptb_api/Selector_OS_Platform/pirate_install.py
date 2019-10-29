import platform
import subprocess
import os

import platform_detect

x=platform_detect.PlatformDetect()


programName="Inst hbootm"
version="0_0_1"
date="2018_07_18"


ThePlatform=platform.system()
theMachine=x.strHostCpuArchitecture


# need idea, some time it takes...
# a=[['']*2] * 2
a=[['']*2 for x in range(2)]

Win=0
Lin=1
x86=0
x64=1
ERR='ERROR'

#print os.path.join("dpinst32.exe /q /s /f")

# Put in here the commands depending on the architecture
a[Win][x86]=os.path.join("dpinst32.exe /q /s /f")
a[Win][x64]=os.path.join("dpinst64.exe /q /s /f")
a[Lin][x86]='x'
a[Lin][x64]='y'

#print a[Win][x86]

cOS=''
cPL=''

if(theMachine=='x86'):
    cPL=x86
elif(theMachine=='x86_64'):
    cPL=x64
else:
    cPL=ERR
if(ThePlatform=='Windows'):
    cOS=Win
elif(ThePlatform=='Linux'):
    cOS=Lin
else:
    cOS=ERR
if(cOS == ERR or cPL == ERR):
    print "[pirate] unknown machine / os"
    print "[pirate] Detected Os: %S Platorm: %s"%(theMachine,ThePlatform)
    exit(1)
else:
    p=''
    print "Command: %s"%(a[cOS][cPL])
    if a[cOS][cPL] is not '':
        print "[pirate] run: %s"%(a[cOS][cPL])
        p = subprocess.Popen(a[cOS][cPL], shell=True, stdout = subprocess.PIPE)
        if(p!=''):
            stdout, stderr = p.communicate()
            print stdout
            print stderr
            print "[pirate] Retrunvalue: %d"%(p.returncode) # is 0 if success
            exit(p.returncode)
    else:
        print "[pirate] No installation for %s on %s due to no command given"%(ThePlatform,theMachine)



if __file__ == '__main__':
  print "[pirate] Programm: %s\nVersion: %s\ndate: %s" % (programName, version, date)
  print "[pirate] \nrunning %s on %s\n" % (ThePlatform, theMachine)