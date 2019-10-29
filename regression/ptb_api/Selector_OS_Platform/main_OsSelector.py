'''
Created on Jul 18, 2018

@author: armin
'''

# OLD !!!


import platform


ThePlatform=platform.system()
theMachine=platform.machine()
if(ThePlatform=='Linux'):
    print "is Linux"
    if(theMachine=='i386'):
        print "is i386"
        
    elif(theMachine=='x86_64'):
        print "is x86_64"
        
    else:
        print "unknown machine"
    
    
elif(ThePlatform=='windows'):
    print "is Windows"
    if(theMachine=='i386'):
        print "is i386"
        
    elif(theMachine=='x86_64'):
        print "is x86_64"
        
    else:
        print "unknown machine"
        
else:
    print "unknown"
    

    
    

