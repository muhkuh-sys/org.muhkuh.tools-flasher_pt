module("muhkuh_cli_init", package.seeall)

-- Set the search path for LUA plugins.
package.cpath = package.cpath .. ";lua_plugins/?.so"

-- Set the search path for LUA modules.
package.path = package.path .. ";lua/?.lua;lua/?/init.lua"

-- Load the common romloader plugins.
require("romloader_eth")
require("romloader_usb")
require("romloader_uart")
require("romloader_jtag")

-- Load the common modules for a CLI environment.
require("muhkuh")
require("select_plugin_cli")
require("tester_cli")

-- This string is appended to all paths in the function "load_from_working_folder".
_G.__MUHKUH_WORKING_FOLDER = ""
