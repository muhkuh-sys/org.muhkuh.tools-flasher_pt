local t = ...
local strDistId, strDistVersion, strCpuArch = t:get_platform()
local tLog = t.tLog
local cLog = t.cLog
local tResult
local archives = require 'installer.archives'
local pl = require'pl.import_into'()

local atInstall = {
  -- Copy the muhkuh cli init script. The active plugins are defined here.
  ['muhkuh_cli_init.lua'] = '${install_lua_path}/',

  -- Copy all tools to the installation base.
  ['${depack_path_org.muhkuh.tools.flasher_pt.flasher}/tools'] = '${install_base}/',

  -- Copy all API demos.
  ['${depack_path_org.muhkuh.tools.flasher_pt.flasher}/direct_api_examples'] = '${install_base}/direct_api_examples/',

  -- Copy the report.
  ['${report_path}'] = '${install_base}/.jonchki/'
}
for strSrc, strDst in pairs(atInstall) do
  t:install(strSrc, strDst)
end


-- Create the package file.
local strPackageText = t:replace_template([[PACKAGE_NAME=${root_artifact_artifact}
PACKAGE_VERSION=${root_artifact_version}
PACKAGE_VCS_ID=${root_artifact_vcs_id}
HOST_DISTRIBUTION_ID=${platform_distribution_id}
HOST_DISTRIBUTION_VERSION=${platform_distribution_version}
HOST_CPU_ARCHITECTURE=${platform_cpu_architecture}
]])
local strPackagePath = t:replace_template('${install_base}/.jonchki/package.txt')
local tFileError, strError = pl.utils.writefile(strPackagePath, strPackageText, false)
if tFileError==nil then
  tLog.error('Failed to write the package file "%s": %s', strPackagePath, strError)
else
  local Archive = archives(cLog)

  -- Create a ZIP archive for Windows platforms. Build a "tar.gz" for Linux.
  local strArchiveExtension
  local tFormat
  local atFilter
  if strDistId=='windows' then
    strArchiveExtension = 'zip'
    tFormat = Archive.archive.ARCHIVE_FORMAT_ZIP
    atFilter = {}
  else
    strArchiveExtension = 'tar.gz'
    tFormat = Archive.archive.ARCHIVE_FORMAT_TAR_GNUTAR
    atFilter = { Archive.archive.ARCHIVE_FILTER_GZIP }
  end

  local strArtifactVersion = t:replace_template('${root_artifact_artifact}-${root_artifact_version}')
  local strArchive = t:replace_template(string.format('${install_base}/../../../%s-%s%s_%s.%s', strArtifactVersion, strDistId, strDistVersion, strCpuArch, strArchiveExtension))
  local strDiskPath = t:replace_template('${install_base}')
  local strArchiveMemberPrefix = strArtifactVersion

  tResult = Archive:pack_archive(strArchive, tFormat, atFilter, strDiskPath, strArchiveMemberPrefix)
end

return tResult
