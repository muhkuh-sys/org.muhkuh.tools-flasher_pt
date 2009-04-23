import os
import sys
import os.path
import re
import copy
import shutil

from SCons             import *
from SCons.Script      import *
from SCons.Environment import *

arm_env = Environment()
env_netx500 = Environment()
env_netx500_interwork = Environment()
env_netx500_interwork16 = Environment()

_buildroot = ''
_build_options_c   = ''
_build_options_asm = ''

if ARGUMENTS.get('target', '0').lower() == 'debug':
  print "**********************"
  print "*** Debug build... ***"
  print "**********************"
  _buildroot = 'debug'

  _build_options_c   = '-gdwarf-2 -O0 '
  _build_options_asm = '-gdwarf2 '
   
elif ARGUMENTS.get('target', '0').lower() == 'debugrel':
  print "***********************************************"
  print "*** Release with debugging symbols build... ***"
  print "***********************************************"
  _buildroot = 'debugrel'

  _build_options_c   = '-gdwarf-2 -Os '
  _build_options_asm = '-gdwarf2 '
else:
  print "************************"
  print "*** Release build... ***"
  print "************************"
  _buildroot = 'release'

  _build_options_c = '-Os '

_library_includes_netx500 = '';
_library_includes_netx50  = '';

# Check O/S
if sys.platform.startswith("win"):

# Windows detection of tools, is wrong, so we need to override the environment tools

  arm_env = Environment(
    ENV     = os.environ,
    tools   = ['gcc','gas','g++','gnulink','ar','Subversion','m4']
  )

# Check if user provided a compiler prefix
  if ARGUMENTS.get('prefix'):
    prefix = ARGUMENTS.get('prefix')

    if(ARGUMENTS.get('libdir_netx500')):
      _library_includes_netx500 = ARGUMENTS.get('libdir_netx500')

    if(ARGUMENTS.get('libdir_netx50')):
      _library_includes_netx50 = ARGUMENTS.get('libdir_netx50')
      
    print "Using Compiler \"" + prefix + "\""
          
  else:
    prefix = 'arm-hitex-elf-'
  
    if arm_env['ENV']['PATH_GNU_ARM'] == None:
      raise EnvironmentError, 'PATH_GNU_ARM is not defined in your environment. Make sure the Hitex Toolchain is correctly installed!'
    else:
      _hitexpath = arm_env['ENV']['PATH_GNU_ARM']
      print "Found Hitex Arm Compiler in \"" +  _hitexpath + "\""
      arm_env['ENV']['PATH'] = _hitexpath  + "/bin" + ";" + arm_env['ENV']['PATH_GNU_ARM']
      
      _library_includes_netx500 = [_hitexpath + '/arm-hitex-elf/lib/interwork/arm926ej-s',
                                 _hitexpath + '/lib/gcc/arm-hitex-elf/4.0.3/interwork/arm926ej-s']
      _library_includes_netx50  = [_hitexpath + '/arm-hitex-elf/lib/interwork/arm926ej-s',
                                   _hitexpath + '/lib/gcc/arm-hitex-elf/4.0.3/interwork/arm926ej-s']
  
elif sys.platform.startswith("linux"):
  arm_env = Environment(
    ENV     = os.environ
  )
  if ARGUMENTS.get('prefix'):
    prefix = ARGUMENTS.get('prefix')
  else:
    prefix = '/home/christoph/crossgcc_4.3.2/bin/arm-elf-'

  if(ARGUMENTS.get('libdir_netx500')):
    _library_includes_netx500 = ARGUMENTS.get('libdir_netx500')
  else:
    _library_includes_netx500 = ['/home/christoph/crossgcc_4.3.2/arm-elf/lib/arm926ej-s/interwork',
                               '/home/christoph/crossgcc_4.3.2/lib/gcc/arm-elf/4.3.2/arm926ej-s/interwork']

  if(ARGUMENTS.get('libdir_netx50')):
    _library_includes_netx50 = ARGUMENTS.get('libdir_netx50')
  else:
    _library_includes_netx50  = ['/home/christoph/crossgcc_4.3.2/arm-elf/lib/arm966e-s/interwork',
                               '/home/christoph/crossgcc_4.3.2/lib/gcc/arm-elf/4.3.2/arm966e-s/interwork']

  print "Using Compiler \"" + prefix + "\""

print "Using Libraries from directory:"
print " * netX100/500 : ", _library_includes_netx500
print " * netX50      : ", _library_includes_netx50

# Override compiler/linker/assembler flags and prefixes
arm_env['AR']         = prefix + 'ar'
arm_env['ARFLAGS']    = 'ru'
arm_env['AS']         = prefix + 'as'
arm_env['ASFLAGS']    = _build_options_asm
arm_env['CC']         = prefix + 'gcc'
arm_env['CCFLAGS']    += _build_options_c + ' -fno-builtin -Wall -Wextra -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Wcast-align -Wpointer-arith -Wmissing-prototypes -Wstrict-prototypes'
arm_env['LD']         = prefix + 'ld' 
arm_env['LINK']       = prefix + 'ld' 
arm_env['LIBS']       = ['c', 'm', 'gcc']
arm_env['LINKFLAGS']  = '-nostdlib -static'
arm_env['LINKCOM']    += ' -T$LDFILE'
arm_env['_LIBFLAGS']  = '-\( ${_stripixes(LIBLINKPREFIX, LIBS, LIBLINKSUFFIX, LIBPREFIX, LIBSUFFIX, __env__)} -\)' 
arm_env['PROGSUFFIX'] = '.elf' 

# --- Override Build outputs ---
arm_env['CCCOMSTR']     = "[CC]  $SOURCE"
arm_env['CXXCOMSTR']    = "[C++] $SOURCE"
arm_env['ASCOMSTR']     = "[AS]  $SOURCE"
arm_env['LINKCOMSTR']   = "[ELF] $SOURCE"
arm_env['ARCOMSTR']     = "[LIB] $TARGET"
arm_env['INSTALLSTR']   = "[INSTALL] $SOURCE --> $TARGET"

arm_env['OC'] = prefix + 'objcopy'
arm_env['OCFLAGS'] = '-O binary'
arm_env['OCCOMSTR'] = '[OC] $TARGET'

arm_env.SourceSignatures('timestamp')
arm_env.BuildDir('build', 'src', duplicate=0)


# --- the objectcopy builder ---
def generate_oc_actions(source, target, env, for_signature):
  return '%s %s %s %s' % (env['OC'], env['OCFLAGS'], source[0], target[0])

arm_oc_bld = Builder(generator = generate_oc_actions, suffix = '.bin', src_suffix = '.elf')

arm_env.Append(BUILDERS = {'Oc' : arm_oc_bld})


# ----------------------------------------------------------
# -------------------- NETX 500 ----------------------------
# ----------------------------------------------------------
env_netx500 = arm_env.Copy()
env_netx500['CCFLAGS'] += ' -mcpu=arm926ej-s '
env_netx500['ASFLAGS'] += ' -mcpu=arm926ej-s '

env_netx500_interwork = env_netx500.Copy(
  LIBPATH = _library_includes_netx500
)
env_netx500_interwork['CCFLAGS'] += ' -mthumb-interwork'
env_netx500_interwork['ASFLAGS'] += ' -mthumb-interwork'

env_netx500_interwork16 = env_netx500_interwork.Copy()
env_netx500_interwork16['CCFLAGS'] += ' -mthumb'
env_netx500_interwork16['ASFLAGS'] += ' -mthumb'

# ----------------------------------------------------------


# ----------------------------------------------------------
# -------------------- NETX 50 -----------------------------
# ----------------------------------------------------------
env_netx50 = arm_env.Copy()
env_netx50['CCFLAGS'] += ' -mcpu=arm9e '
env_netx50['ASFLAGS'] += ' -mcpu=arm9e '

env_netx50_interwork = env_netx50.Copy(
  LIBPATH = _library_includes_netx50
)
env_netx50_interwork['CCFLAGS'] += ' -mthumb-interwork'
env_netx50_interwork['ASFLAGS'] += ' -mthumb-interwork'

env_netx50_interwork16 = env_netx50_interwork.Copy()
env_netx50_interwork16['CCFLAGS'] += ' -mthumb'
env_netx50_interwork16['ASFLAGS'] += ' -mthumb'

def _generate_build_dir(build_dir_prefix, src_list, env):
  """Generate build directory prefixes for each file. This functions searches for the first invalid character (/\:..) 
     and uses the path info das builddir prefix """

# Iterate over source list
  for i in range(len(src_list)): 
    src_dir, tmp_srcfile = os.path.split(src_list[i])
    
    tmp_dir          = src_dir
    src_file         = tmp_srcfile
    src_dir_stripped = ""
  
# Split path until we read an invalid char
    while tmp_srcfile:
      tmp_dir, tmp_srcfile = os.path.split(tmp_dir)
      if not re.match(r"\.\.|\\\\|//|:", tmp_srcfile):
        if src_dir_stripped!="":
          src_dir_stripped = "/" + tmp_srcfile + src_dir_stripped
        else:
          src_dir_stripped = "/" + tmp_srcfile
      else:
# Illegal entry found
        break

# Source dir is is now transformed from e.g. "./RCX/Sources/oldSyslock.s" --> "build/release/RCX/Sources/oldSyslock.s"
    _build_dir = build_dir_prefix + src_dir_stripped 
 
    src_list[i] = _build_dir + "/" + src_file

#Add build directory to environment
    env.BuildDir(_build_dir, src_dir ,duplicate = 0)
  
def _netx_compile(MyEnv, src_list, inc_list, cdefine_list, build_dir_prefix):
  """Compile a netX object list using the given environment"""

  tempenv = MyEnv.Copy()

  build_src_list = copy.copy(src_list)
  
  _generate_build_dir(build_dir_prefix, build_src_list, tempenv)

  tempenv.Append(CPPPATH      = inc_list)
  tempenv.Append(CPPDEFINES   = cdefine_list)
  tempenv.Append(ASCOM        = tempenv['_CPPINCFLAGS'])

  return tempenv.Object(build_src_list)

def _netx_makeelf(MyEnv, src_list, build_dir_prefix, elfname, libpath, libs, ld_file):
  tempenv = MyEnv.Copy()

  build_src_list = copy.copy(src_list)
#  _generate_build_dir(build_dir_prefix + "/" + _buildroot, build_src_list, tempenv)

  tempenv.Append(LIBPATH      = libpath)
  tempenv.Append(LIBS         = libs)

#Add Mapfile command to linker. TODO: How to delete the map file on a clean build
  tempenv['LINKCOM']    += ' -Map '+ build_dir_prefix + "/" + _buildroot + "/" + elfname+'.map'

  return tempenv.Program(build_dir_prefix + "/" + _buildroot + "/" + elfname, build_src_list, LDFILE=ld_file)
  
# ----------------------------------------------------------
# -------------------- NETX 500 ----------------------------
# ----------------------------------------------------------
def netx500_compile_thumb(src_list, inc_list, cdefine_list, build_dir_prefix):
  return _netx_compile(env_netx500_interwork16, src_list, inc_list, cdefine_list, build_dir_prefix + "/" + _buildroot)

def netx500_compile_arm(src_list, inc_list, cdefine_list, build_dir_prefix):
  return _netx_compile(env_netx500_interwork, src_list, inc_list, cdefine_list, build_dir_prefix + "/" + _buildroot)

def netx500_makelib(obj_list, build_dir_prefix, libname, installdir):
  _install = env_netx500_interwork.StaticLibrary(build_dir_prefix + "/" + _buildroot + "/" + libname, obj_list)

  env_netx500_interwork.Install(installdir, _install)
  
  return _install
  
def netx500_makeelf(obj_list, build_dir_prefix, elfname, libpath, libs, ld_file):
  return _netx_makeelf(env_netx500_interwork, obj_list, build_dir_prefix, elfname, libpath, libs, ld_file)
# ----------------------------------------------------------

# ----------------------------------------------------------
# -------------------- NETX 50 -----------------------------
# ----------------------------------------------------------
def netx50_compile_thumb(src_list, inc_list, cdefine_list, build_dir_prefix):
  return _netx_compile(env_netx50_interwork16, src_list, inc_list, cdefine_list, build_dir_prefix + "/" + _buildroot)

def netx50_compile_arm(src_list, inc_list, cdefine_list, build_dir_prefix):
  return _netx_compile(env_netx50_interwork, src_list, inc_list, cdefine_list, build_dir_prefix + "/" + _buildroot)


def netx50_makelib(obj_list, build_dir_prefix, libname, installdir):
  _install = env_netx50_interwork.StaticLibrary(build_dir_prefix + "/" + _buildroot + "/" + libname, obj_list)
 
  env_netx50_interwork.Install(installdir, _install)
  
  return _install

def netx50_makeelf(obj_list, build_dir_prefix, elfname, libpath, libs, ld_file):
  return _netx_makeelf(env_netx50_interwork, obj_list, build_dir_prefix, elfname, libpath, libs, ld_file)


# ----------------------------------------------------------
