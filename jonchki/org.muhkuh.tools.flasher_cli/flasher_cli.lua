local t = ...
local strDistId, strDistVersion, strCpuArch = t:get_platform()

-- Copy all demo scripts to the installation base.
t:install('${depack_path_org.muhkuh.tools.flasher.lua5.1-flasher}/demo',  '${install_base}/')

-- Create a ZIP archive for Windows and a TAR.GZ for Linux.
local strExtension
if strDistId=='windows' then
  strExtension = 'zip'
elseif strDistId=='ubuntu' then
  strExtension = 'tar.gz'
end

local strArtifact = string.format('flasher_cli_%s%s_%s', strDistId, strDistVersion, strCpuArch)
local strInstallFolder = t:replace_template('${install_base}')
local strArchive = t:replace_template(string.format('${install_base}/../%s.%s', strArtifact, strExtension))

print('************', strArtifact, strArchiveFolder, strArchive)
-- Remove the old archive if it exists.
if t.pl.path.exists(strArchive)==strArchive then
  t.pl.file.delete(strArchive)
end

-- Loop over all files in the install folder.
local archive = require 'archive'

local strArchiveRoot = t.pl.path.abspath(strInstallFolder)

-- Create a read disk object.
local tReader = archive.ArchiveReadDisk()
local tResult = tReader:open(strArchiveRoot)
if tResult~=0 then
  error(string.format('Failed to open the local folder "%s" for reading.', strArchiveRoot))
end

-- Create a new archive.
local tArchive = archive.ArchiveWrite()
if strDistId=='windows' then
  tResult = tArchive:set_format_zip()
  if tResult~=0 then
    error('Failed to set the archive format to ZIP.')
  end
elseif strDistId=='ubuntu' then
  tResult = tArchive:set_format_gnutar()
  if tResult~=0 then
    error('Failed to set the archive format to GNU TAR.')
  end
  tResult = tArchive:add_filter_xz()
  if tResult~=0 then
    error('Failed to add XZ filter.')
  end
end
tResult = tArchive:open_filename(strArchive)
if tResult~=0 then
  error(string.format('Failed to open archive "%s" for writing.', strArchive))
end

for tEntry in tReader:iter_header() do
  -- Cut off the archive root.
  local strAbsEntry = tEntry:pathname()
  local strRelEntry = t.pl.path.relpath(strAbsEntry, strArchiveRoot)
  if strRelEntry~='' then
    tEntry:set_pathname(strRelEntry)
    tResult = tArchive:write_header(tEntry)
    if tResult~=0 then
      error(string.format('Failed to write the header for entry "%s".', strAbsEntry))
    end
    -- Copy the data.
    for strData in tReader:iter_data(16384) do
      tResult = tArchive:write_data(strData)
      if tResult~=0 then
        error(string.format('Failed to write data for entry "%s".', strAbsEntry))
      end
    end
    -- Finish the entry.
    tResult = tArchive:finish_entry()
    if tResult~=0 then
      error(string.format('Failed to finish the entry "%s".', strAbsEntry))
    end
  end
  if tReader:can_descend()~=0 then
    tResult = tReader:descend()
    if tResult~=0 then
      error(string.format('Failed to descend into entry "%s".', strAbsEntry))
    end
  end
end

tResult = tArchive:close()
if tResult~=0 then
  error(string.format('Failed to close the archive "%s".', strArchive))
end
tReader:close()

return true
