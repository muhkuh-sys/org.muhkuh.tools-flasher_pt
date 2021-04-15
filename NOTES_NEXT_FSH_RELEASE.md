# Next FSH Release Notes

## Add Release Version to Files

- _docs/config.yml
- LDOC/config.ld
- lua/fsh.lua -> function tlog.info run

## Changes Compared to Last Release (1.6.8)

- bug fixes:
  - wrong description of progress bar in function __getRange (fsh.lua)
  - change order of statement in function __run_write (fsh.lua) due to wrong display of progress bar information in case of an error in eraseArea

- Add return nil value in function isErased in the case of call fails (flasher.lua)
- Remove double default callback functions (flasher.lua)
- Remove of 'local this' in functions: write_image (and return), read_image, call (and return) (flasher.lua)

- Additional comments of LDOC
