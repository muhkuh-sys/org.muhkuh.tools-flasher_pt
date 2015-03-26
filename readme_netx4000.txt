
The netX 4000 version of the flasher is currently only suitable for the SCIT board, as
MMIOs and port control settings are not configured.

Currently, the build system cannot handle two compilers in parallel.
By default, the flasher is built for netX 500/100/50/10/51/52.

In order to build for netX 4000:
Rename Sconstruct to something else and rename Sconstruct_netx4000 to Sconstruct.
In setup.xml, comment out the entry for the gcc-arm-elf compiler and uncomment the entry for the gcc-arm-none-eabi compiler.
In templates/flasher.lua, uncomment the line
--	[romloader.ROMLOADER_CHIPTYP_NETX4000] = "netx4000"
In the detect function, change the line 
		0xffffffff,                           -- mmio config
to
		0x35363437,                           -- mmio config

