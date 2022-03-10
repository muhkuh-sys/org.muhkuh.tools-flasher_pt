# Next FSH Release Notes

## BEFORE updating to New Version: Add Release Version to Files and update Release Notes: 

- /jonchki/org.muhkuh.tools.flasher_cli/flasher_cli.xml
- update release notes: docs/release_notes.md
- docs/_config.yml -> description
- LDOC/config.ld
- lua/fsh.lua -> function tlog.info run

## Changes Compared to Last Release (1.7.1)

-

## Changes Compared to Last Release (1.7.0)

-

## Changes Compared to Last Release (1.6.10)

-

## Changes Compared to Last Release (1.6.9)

-

## Changes Compared to Last Release (1.6.8)

- Wrong description of progress bar in function __getRange (fsh.lua)
- Change order of statement in function __run_write (fsh.lua) due to wrong display of progress bar information in case of an error in eraseArea
- Add error message in connect command if plugin was not found (fsh.lua)
- Change fill of progress bar due to unknown symbol in OS windows (progressbar.lua)
- Add return nil value in function isErased in the case of call fails (flasher.lua)
- Remove double default callback functions (flasher.lua)
- Remove of 'local this' in functions: write_image (and return), read_image, call (and return) (flasher.lua)
- Additional comments of LDOC
- Add shortcuts of plugins in the connect command (fsh.lua)
- Change color settings for different operating systems - linux and windows (fsh.lua)
- Additional option to use the input command directly by the argument "-i" or "--input" (fsh.lua)

## Possible Changes

- Write one image file to multiple intflash locations when the size of one flash location not fit
