
require("romloader_usb")

require("flasher")
require("muhkuh")
require("select_plugin")


tPlugin = select_plugin.SelectPlugin()
if tPlugin==nil then
	print("No plugin selected, nothing to do!")
else
	-- connect the plugin
	tPlugin:Connect()

	-- Flash the file.
	flasher.simple_flasher(tPlugin, "nx10_sqixip.img", flasher.BUS_Spi, 0, 0, "../targets/")

	-- Disconnect the plugin.
	tPlugin:Disconnect()

	-- Free the plugin.
	tPlugin = nil
end
