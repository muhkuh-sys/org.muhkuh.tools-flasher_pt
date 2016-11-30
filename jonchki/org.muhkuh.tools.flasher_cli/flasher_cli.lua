local t = ...
local strPlatform = t:get_platform()

-- Copy all demo scripts to the installation base.
t:install('${depack_path_org.muhkuh.tools.flasher.lua5.1-flasher}/demo',  '${install_base}/')

return true
