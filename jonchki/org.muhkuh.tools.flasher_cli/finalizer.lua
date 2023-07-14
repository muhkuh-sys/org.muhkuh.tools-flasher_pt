local t = ...

t:install {
  -- Copy the muhkuh cli init script. The active plugins are defined here.
  ['muhkuh_cli_init.lua'] = '${install_lua_path}/',

  -- Copy all tools to the installation base.
  ['${depack_path_org.muhkuh.tools.flasher_pt.flasher}/tools'] = '${install_base}/',

  -- Copy all API demos.
  ['${depack_path_org.muhkuh.tools.flasher_pt.flasher}/direct_api_examples'] = '${install_base}/direct_api_examples/',

  -- Copy the report.
  ['${report_path}'] = '${install_base}/.jonchki/'
}

return true
