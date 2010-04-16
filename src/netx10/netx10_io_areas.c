/***************************************************************************
 *   Copyright (C) 2005, 2006, 2007, 2008, 2009 by Hilscher GmbH           *
 *                                                                         *
 *   Author: Christoph Thelen (cthelen@hilscher.com)                       *
 *                                                                         *
 *   Redistribution or unauthorized use without expressed written          *
 *   agreement from the Hilscher GmbH is forbidden.                        *
 ***************************************************************************/


#if ASIC_TYP==10


#include "netx10_io_areas.h"


NX10_ARM_BOOT_VECTOR_AREA_T * const ptArmBootVectorArea = (NX10_ARM_BOOT_VECTOR_AREA_T * const)Addr_NX10_arm_boot_vector;

NX10_SR_AREA_T * const ptSrArea = (NX10_SR_AREA_T * const)Addr_NX10_sr_motion;

NX10_CORDIC_AREA_T * const ptCordicArea = (NX10_CORDIC_AREA_T * const)Addr_NX10_cordic;

NX10_MPWM_AREA_T * const ptMpwmArea = (NX10_MPWM_AREA_T * const)Addr_NX10_mpwm;

NX10_MENC_AREA_T * const ptMencArea = (NX10_MENC_AREA_T * const)Addr_NX10_menc;

NX10_XLINK_AREA_T * const ptXlink0Area = (NX10_XLINK_AREA_T * const)Addr_NX10_xlink0;
NX10_XLINK_AREA_T * const ptXlink1Area = (NX10_XLINK_AREA_T * const)Addr_NX10_xlink1;
NX10_XLINK_AREA_T * const ptXlink2Area = (NX10_XLINK_AREA_T * const)Addr_NX10_xlink2;
NX10_XLINK_AREA_T * const ptXlink3Area = (NX10_XLINK_AREA_T * const)Addr_NX10_xlink3;

NX10_IO_LINK_IRQ_AREA_T * const IoLinkIrqArea = (NX10_IO_LINK_IRQ_AREA_T * const)Addr_NX10_io_link_irq;

NX10_ADC_CTRL_AREA_T * const ptAdcCtrlArea = (NX10_ADC_CTRL_AREA_T * const)Addr_NX10_adc_ctrl;

NX10_XPIC_TIMER_AREA_T * const ptXpicTimerArea = (NX10_XPIC_TIMER_AREA_T * const)Addr_NX10_xpic_timer;

NX10_XPIC_VIC_AREA_T * const ptXpicVicArea = (NX10_XPIC_VIC_AREA_T * const)Addr_NX10_xpic_vic;

NX10_XPIC_WDG_AREA_T * const ptXpicWdgArea = (NX10_XPIC_WDG_AREA_T * const)Addr_NX10_xpic_wdg;

NX10_XC_AREA_T * const ptXcArea = (NX10_XC_AREA_T * const)Addr_NX10_xc;

NX10_XPEC_AREA_T * const ptXpec0Area = (NX10_XPEC_AREA_T * const)Addr_NX10_xpec0;

NX10_XPIC_AREA_T * const ptXpicArea = (NX10_XPIC_AREA_T * const)Addr_NX10_xpic;

NX10_XPIC_DEBUG_AREA_T * const ptXpicDebugArea = (NX10_XPIC_DEBUG_AREA_T * const)Addr_NX10_xpic_debug;

NX10_XMAC_AREA_T * const ptXmac0Area = (NX10_XMAC_AREA_T * const)Addr_NX10_xmac0;

NX10_POINTER_FIFO_AREA_T * const ptPointerFifoArea = (NX10_POINTER_FIFO_AREA_T * const)Addr_NX10_pointer_fifo;

NX10_XPEC_IRQ_REGISTERS_AREA_T * const ptXpecIrqRegistersArea = (NX10_XPEC_IRQ_REGISTERS_AREA_T * const)Addr_NX10_xpec_irq_registers;

NX10_XC_MEM_PROT_AREA_T * const ptXcMemProtArea = (NX10_XC_MEM_PROT_AREA_T * const)Addr_NX10_xc_mem_prot;

NX10_BUF_MAN_AREA_T * const ptBufManArea = (NX10_BUF_MAN_AREA_T * const)Addr_NX10_buf_man;

NX10_ASIC_CTRL_AREA_T * const ptAsicCtrlArea = (NX10_ASIC_CTRL_AREA_T * const)Addr_NX10_asic_ctrl;

NX10_EXT_ASYNCMEM_CTRL_AREA_T * const ptExtAsyncmemCtrlArea = (NX10_EXT_ASYNCMEM_CTRL_AREA_T * const)Addr_NX10_ext_asyncmem_ctrl;
/*Addr_ext_sdram_ctrl*/
NX10_WATCHDOG_AREA_T * const ptWatchdogArea = (NX10_WATCHDOG_AREA_T * const)Addr_NX10_watchdog;

NX10_GPIO_AREA_T * const ptGpioArea = (NX10_GPIO_AREA_T * const)Addr_NX10_gpio;

NX10_ARM_TIMER_AREA_T * const ptArmTimerArea = (NX10_ARM_TIMER_AREA_T * const)Addr_NX10_arm_timer;

NX10_MMIO_CTRL_AREA_T * const ptMmioCtrlArea = (NX10_MMIO_CTRL_AREA_T * const)Addr_NX10_mmio_ctrl;

NX10_UART_AREA_T * const ptUart0Area = (NX10_UART_AREA_T * const)Addr_NX10_uart0;
NX10_UART_AREA_T * const ptUart1Area = (NX10_UART_AREA_T * const)Addr_NX10_uart1;

NX10_MIIMU_AREA_T * const ptMiimuArea = (NX10_MIIMU_AREA_T * const)Addr_NX10_miimu;

NX10_HIF_IO_CTRL_AREA_T * const ptHifIoCtrlArea = (NX10_HIF_IO_CTRL_AREA_T * const)Addr_NX10_hif_io_ctrl;

NX10_SPI_AREA_T * const ptSpiArea = (NX10_SPI_AREA_T * const)Addr_NX10_spi_motion;

NX10_SQI_AREA_T * const ptSqiArea = (NX10_SQI_AREA_T * const)Addr_NX10_sqi;

NX10_I2C_AREA_T * const ptI2cArea = (NX10_I2C_AREA_T * const)Addr_NX10_i2c;

NX10_USB_DEV_CTRL_AREA_T * const ptUsbDevCtrlArea = (NX10_USB_DEV_CTRL_AREA_T * const)Addr_NX10_usb_dev_ctrl;

NX10_USB_DEV_FIFO_CTRL_AREA_T * const ptUsbDevFifoCtrlArea = (NX10_USB_DEV_FIFO_CTRL_AREA_T * const)Addr_NX10_usb_dev_fifo_ctrl;

NX10_USB_DEV_FIFO_AREA_T * const ptUsvDevFifoArea = (NX10_USB_DEV_FIFO_AREA_T * const)Addr_NX10_usb_dev_fifo;

NX10_SYSTIME_AREA_T * const ptSystimeArea = (NX10_SYSTIME_AREA_T * const)Addr_NX10_systime;

NX10_HANDSHAKE_CTRL_AREA_T * const ptHandshakeCtrlArea = (NX10_HANDSHAKE_CTRL_AREA_T * const)Addr_NX10_handshake_ctrl;

NX10_DPM_AREA_T * const ptDpmArea = (NX10_DPM_AREA_T * const)Addr_NX10_dpm;

NX10_DMAC_CH_AREA_T * const ptDmacCh0Area = (NX10_DMAC_CH_AREA_T * const)Addr_NX10_dmac_ch0;
NX10_DMAC_CH_AREA_T * const ptDmacCh1Area = (NX10_DMAC_CH_AREA_T * const)Addr_NX10_dmac_ch1;

NX10_DMAC_REG_AREA_T * const ptDmacRegArea = (NX10_DMAC_REG_AREA_T * const)Addr_NX10_dmac_reg;

NX10_VIC_AREA_T * const ptVicArea = (NX10_VIC_AREA_T * const)Addr_NX10_vic;

/*EXTMEM_PRIORITY_CTRL_AREA_T *ptExtmemPriorityCtrlArea = (EXTMEM_PRIORITY_CTRL_AREA_T*);*/

NX10_SDRAM_AREA_T * const ptSdramArea = (NX10_SDRAM_AREA_T * const)Addr_NX10_ext_sdram_ctrl;

NX10_USB_DEV_FIFO_AREA_T * const ptUsbDevFifoArea = (NX10_USB_DEV_FIFO_AREA_T * const)Addr_NX10_usb_dev_fifo;

NX10_HANDSHAKE_BLOCK_AREA_T * const ptHandshakeArea = (NX10_HANDSHAKE_BLOCK_AREA_T * const)Addr_NX10_intram5_mirror_dtcm;
NX10_HANDSHAKE_BLOCK_AREA_T * const ptHandshakeDtcmArmMirrorArea = (NX10_HANDSHAKE_BLOCK_AREA_T * const)Addr_NX10_intram5_mirror_dtcm_arm_mirror;


#endif	/* ASIC_TYP==10 */
