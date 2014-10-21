flasher ${PROJECT_VERSION} ${PROJECT_VERSION_VCS}
=================================================

About
=====

This is the release of "flasher" ${PROJECT_VERSION} ${PROJECT_VERSION_VCS}.

The flasher is an application for systems based on the Hilscher "netX" CPU. It writes data to flash or EEPROM chips.

The flasher is a stand-alone application. This means it does not require an OS like Linux, WindowsCE or the netX specific rcX.
It's main use is writing bootable images to SPI or parallel flashes, but it can also be used to:

- write flashdisk images or application specific data
- erase a bootable image
- read the contents of a flash device


Supported devices
=================

SPI Flashes
-----------

SPI flashes from different vendors or even different families differ quite a lot. They have special commands or unusual sector layouts.
This means the flasher must know the SPI flash before it can be used.

The flasher has 2 ways to detect a SPI flash:

- a built-in list of known flashes

This list shows a way to detect a flash and how to use it.

Here is the complete list for this release: `spi_flash_types.html <spi_flash_types.html>`_  .


- SFDP

"Serial Flash Discoverable Parameter" (SFDP) is a JEDEC standard to detect parameters for a serial flash device.
The flasher uses SFDP after the built-in list of known flashes failed to to identify a device.
Details on SFDP: http://www.jedec.org/standards-documents/docs/jesd216


Parallel flashes
----------------

TBD.

