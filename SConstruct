import netx


rcx_defines         = ['_NETX_HITOP_', '__RCX__', '_RCX_LIBRARY_VERSION_BUILD_', '_RX_MICRO_KERNEL_']
flasher_defines_netx500 = ['__NETX500']
flasher_defines_netx50  = ['__NETX50']
#flasher_defines_silent  = ['SILENT']
flasher_defines_debug   = ['DEBUG']

flasher_includes_netx500 = Split("""
                                 ./
                                 ./netx500
                                 """)

flasher_includes_netx50 = Split("""
                                ./
                                ./netx50
                                """)


# ----------------------------------------------------------------
# ------------------- Common Sources -----------------------------
# ----------------------------------------------------------------

flasher_common_c = Split("""
                         ./cfi_flash.c
                         ./delay.c
                         ./spi_flash.c
                         ./flasher_ext.c
                         ./flasher_i2c.c
                         ./flasher_spi.c
                         ./flasher_srb.c
                         ./main.c
                         ./netx_consoleapp.c
                         ./parflash_common.c
                         ./progress_bar.c
                         ./rdyrun.c
                         ./spansion.c
                         ./spi_flash_types.c
                         ./strata.c
                         ./uprintf.c
                         """)

flasher_common_s = Split("""
                         ./init_netx_test.s
                         ./startvector.s
                         """)

# ----------------------------------------------------------------
# ---------------- Sources for netx500 ---------------------------
# ----------------------------------------------------------------

flasher_netx500_c = Split("""
                          ./netx500/flasher_header.c
                          ./netx500/hal_spi.c
                          ./netx500/netx_io_areas.c
                          """)

# ----------------------------------------------------------------
# ---------------- Sources for netx50 ----------------------------
# ----------------------------------------------------------------

flasher_netx50_c  = Split("""
                          ./netx50/flasher_header.c
                          ./netx50/hal_spi.c
                          ./netx50/netx_io_areas.c
                          """)

# ----------------------------------------------------------------
# ---------------- Build all flasher versions --------------------
# ----------------------------------------------------------------

flasher_nx500_r_files = netx.netx500_compile_arm(flasher_common_c + flasher_common_s + flasher_netx500_c,
                                                 flasher_includes_netx500,
                                                 flasher_defines_netx500,
                                                 'output/flasher_nx500_r')
#flasher_nx500_s_files = netx.netx500_compile_arm(flasher_common_c + flasher_common_s + flasher_netx500_c,
#                                                 flasher_includes_netx500,
#                                                 flasher_defines_netx500 + flasher_defines_silent,
#                                                 'output/flasher_nx500_s')
flasher_nx500_d_files = netx.netx500_compile_arm(flasher_common_c + flasher_common_s + flasher_netx500_c,
                                                 flasher_includes_netx500,
                                                 flasher_defines_netx500 + flasher_defines_debug,
                                                 'output/flasher_nx500_d')


flasher_nx50_r_files  = netx.netx50_compile_arm( flasher_common_c + flasher_common_s + flasher_netx50_c,
                                                 flasher_includes_netx50,
                                                 flasher_defines_netx50,
                                                 'output/flasher_nx50_r')
#flasher_nx50_s_files  = netx.netx50_compile_arm( flasher_common_c + flasher_common_s + flasher_netx50_c,
#                                                 flasher_includes_netx50,
#                                                 flasher_defines_netx50 + flasher_defines_silent,
#                                                 'output/flasher_nx50_s')
flasher_nx50_d_files  = netx.netx50_compile_arm( flasher_common_c + flasher_common_s + flasher_netx50_c,
                                                 flasher_includes_netx50,
                                                 flasher_defines_netx50 + flasher_defines_debug,
                                                 'output/flasher_nx50_d')



flasher_nx500_r_elf = netx.netx500_makeelf(flasher_nx500_r_files, 'output/flasher_nx500_r', 'flasher_nx500_r.elf', '', '', 'flasher_netx500.ld')
flasher_nx500_d_elf = netx.netx500_makeelf(flasher_nx500_d_files, 'output/flasher_nx500_d', 'flasher_nx500_d.elf', '', '', 'flasher_netx500.ld')


flasher_nx50_r_elf  = netx.netx50_makeelf( flasher_nx50_r_files,  'output/flasher_nx50_r',  'flasher_nx50_r.elf', '', '', 'flasher_netx50.ld')
flasher_nx50_d_elf  = netx.netx50_makeelf( flasher_nx50_d_files,  'output/flasher_nx50_d',  'flasher_nx50_d.elf', '', '', 'flasher_netx50.ld')



netx.arm_env.Oc('flasher_netx500.bin',       flasher_nx500_r_elf)
netx.arm_env.Oc('flasher_netx500_debug.bin', flasher_nx500_d_elf)


netx.arm_env.Oc('flasher_netx50.bin',        flasher_nx50_r_elf)
netx.arm_env.Oc('flasher_netx50_debug.bin',  flasher_nx50_d_elf)

