local t = ...
local strPlatform = t:get_platform()

-- Copy all demo scripts to the installation base.
t:install('${depack_path_org.muhkuh.tools.flasher.lua5.1-flasher}/demo',  '${install_base}/')
--[[
local strArtifact = string.format('flasher_cli_%s', strPlatform)
local strArchiveFolder = t:replace_template(string.format('${work}/install/%s', strArtifact))
local strZipArchive = t:replace_template(string.format('${work}/install/%s.zip', strArtifact))

-- Remove an old archive.
if t.pl.path.exists(strZipArchive)==strZipArchive then
  t.pl.file.delete(strZipArchive)
end
-- Create a ZIP archive.
local tZip, strError = t:zip.open(strZipArchive, t.zip.OR(t.zip.CREATE, t.zip.EXCL))
if tZip==nil then
  error(string.format('Failed to create the arcive "%s": %s', strZipArchive, strError))
end
-- Add an archive comment.
tZip:set_archive_comment(string.format('G:"org.muhkuh.tools", M:"flasher", A:"%s", V:""', strArtifact))

-- Add the complete install folder.
for strRoot, astrDirs, astrFiles in t.pl.dir.walk(strArchiveFolder) do
  -- Create all directories.
  for strDir in astrDirs do
    local strPath = t.pl.path.join(strRoot, strDir)
    print(string.format('Creating folder %s', strPath))
  end
  for strFile in astrFiles do
    local strPath = t.pl.path.join(strRoot, strFile)
    print(string.format('Creating file %s', strPath))
  end
end

-- Close the ZIP archive.
tZip:close()
--]]

return true
