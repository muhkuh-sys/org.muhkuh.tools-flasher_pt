
require("romloader_usb")
require("romloader_uart")

require("flasher")
require("select_plugin")


-- Muhkuh V1 emu function: read binary file into string.
--   returns the file or raises an error
if not muhkuh then
	muhkuh = {}
end
function muhkuh.load(strName)
	print("reading file " .. strName)
	local bin
	local f, msg = io.open(strName, "rb")
	if f then
		bin = f:read("*all")
		f:close()
		print(bin:len() .. " bytes read")
		return bin
	else
		error(msg)
	end
end


if #arg~=1 then
	error("Missing parameter: file to flash.")
end
strData = arg[1]


tPlugin = select_plugin.SelectPlugin()
if tPlugin==nil then
	print("No plugin selected, nothing to do!")
else
	-- Connect the plugin.
	tPlugin:Connect()

	-- Flash the file.
	flasher.simple_flasher(tPlugin, strData, flasher.BUS_Parflash, 0, 0, "../targets/")

	-- Disconnect the plugin.
	tPlugin:Disconnect()

	-- Free the plugin.
	tPlugin = nil
end
