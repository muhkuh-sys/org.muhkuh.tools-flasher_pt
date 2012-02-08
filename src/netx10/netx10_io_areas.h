/***************************************************************************
 *   Copyright (C) 2012 by Hilscher GmbH                                   *
 *   cthelen@hilscher.com                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#ifndef __NETX10_IO_AREAS_H__
#define __NETX10_IO_AREAS_H__

#include "netx10_regdef.h"


typedef struct
{
	volatile unsigned long  ulSdram_general_ctrl;
	volatile unsigned long  ulSdram_timing_ctrl;
	volatile unsigned long  ulSdram_mr;
} NX10_SDRAM_AREA_T;

typedef struct
{
	volatile unsigned long aulHandshakeReg[16];
} NX10_HANDSHAKE_BLOCK_AREA_T;


#define NX10_DEF_ptArmBootVectorArea NX10_ARM_BOOT_VECTOR_AREA_T * const ptArmBootVectorArea = (NX10_ARM_BOOT_VECTOR_AREA_T * const)Addr_NX10_arm_boot_vector;

#define NX10_DEF_ptSrArea NX10_SR_AREA_T * const ptSrArea = (NX10_SR_AREA_T * const)Addr_NX10_sr_motion;

#define NX10_DEF_ptCordicArea NX10_CORDIC_AREA_T * const ptCordicArea = (NX10_CORDIC_AREA_T * const)Addr_NX10_cordic;

#define NX10_DEF_ptMpwmArea NX10_MPWM_AREA_T * const ptMpwmArea = (NX10_MPWM_AREA_T * const)Addr_NX10_mpwm;

#define NX10_DEF_ptMencArea NX10_MENC_AREA_T * const ptMencArea = (NX10_MENC_AREA_T * const)Addr_NX10_menc;

#define NX10_DEF_ptXlink0Area NX10_XLINK_AREA_T * const ptXlink0Area = (NX10_XLINK_AREA_T * const)Addr_NX10_xlink0;
#define NX10_DEF_ptXlink1Area NX10_XLINK_AREA_T * const ptXlink1Area = (NX10_XLINK_AREA_T * const)Addr_NX10_xlink1;
#define NX10_DEF_ptXlink2Area NX10_XLINK_AREA_T * const ptXlink2Area = (NX10_XLINK_AREA_T * const)Addr_NX10_xlink2;
#define NX10_DEF_ptXlink3Area NX10_XLINK_AREA_T * const ptXlink3Area = (NX10_XLINK_AREA_T * const)Addr_NX10_xlink3;

#define NX10_DEF_IoLinkIrqArea NX10_IO_LINK_IRQ_AREA_T * const IoLinkIrqArea = (NX10_IO_LINK_IRQ_AREA_T * const)Addr_NX10_io_link_irq;

#define NX10_DEF_ptAdcCtrlArea NX10_ADC_CTRL_AREA_T * const ptAdcCtrlArea = (NX10_ADC_CTRL_AREA_T * const)Addr_NX10_adc_ctrl;

#define NX10_DEF_ptXpicTimerArea NX10_XPIC_TIMER_AREA_T * const ptXpicTimerArea = (NX10_XPIC_TIMER_AREA_T * const)Addr_NX10_xpic_timer;

#define NX10_DEF_ptXpicVicArea NX10_XPIC_VIC_AREA_T * const ptXpicVicArea = (NX10_XPIC_VIC_AREA_T * const)Addr_NX10_xpic_vic;

#define NX10_DEF_ptXpicWdgArea NX10_XPIC_WDG_AREA_T * const ptXpicWdgArea = (NX10_XPIC_WDG_AREA_T * const)Addr_NX10_xpic_wdg;

#define NX10_DEF_ptXcArea NX10_XC_AREA_T * const ptXcArea = (NX10_XC_AREA_T * const)Addr_NX10_xc;

#define NX10_DEF_ptXpec0Area NX10_XPEC_AREA_T * const ptXpec0Area = (NX10_XPEC_AREA_T * const)Addr_NX10_xpec0;

#define NX10_DEF_ptXpicArea NX10_XPIC_AREA_T * const ptXpicArea = (NX10_XPIC_AREA_T * const)Addr_NX10_xpic;

#define NX10_DEF_ptXpicDebugArea NX10_XPIC_DEBUG_AREA_T * const ptXpicDebugArea = (NX10_XPIC_DEBUG_AREA_T * const)Addr_NX10_xpic_debug;

#define NX10_DEF_ptXmac0Area NX10_XMAC_AREA_T * const ptXmac0Area = (NX10_XMAC_AREA_T * const)Addr_NX10_xmac0;

#define NX10_DEF_ptPointerFifoArea NX10_POINTER_FIFO_AREA_T * const ptPointerFifoArea = (NX10_POINTER_FIFO_AREA_T * const)Addr_NX10_pointer_fifo;

#define NX10_DEF_ptXpecIrqRegistersArea NX10_XPEC_IRQ_REGISTERS_AREA_T * const ptXpecIrqRegistersArea = (NX10_XPEC_IRQ_REGISTERS_AREA_T * const)Addr_NX10_xpec_irq_registers;

#define NX10_DEF_ptXcMemProtArea NX10_XC_MEM_PROT_AREA_T * const ptXcMemProtArea = (NX10_XC_MEM_PROT_AREA_T * const)Addr_NX10_xc_mem_prot;

#define NX10_DEF_ptBufManArea NX10_BUF_MAN_AREA_T * const ptBufManArea = (NX10_BUF_MAN_AREA_T * const)Addr_NX10_buf_man;

#define NX10_DEF_ptAsicCtrlArea NX10_ASIC_CTRL_AREA_T * const ptAsicCtrlArea = (NX10_ASIC_CTRL_AREA_T * const)Addr_NX10_asic_ctrl;

#define NX10_DEF_ptExtAsyncmemCtrlArea NX10_EXT_ASYNCMEM_CTRL_AREA_T * const ptExtAsyncmemCtrlArea = (NX10_EXT_ASYNCMEM_CTRL_AREA_T * const)Addr_NX10_ext_asyncmem_ctrl;
/*Addr_ext_sdram_ctrl*/
#define NX10_DEF_ptWatchdogArea NX10_WATCHDOG_AREA_T * const ptWatchdogArea = (NX10_WATCHDOG_AREA_T * const)Addr_NX10_watchdog;

#define NX10_DEF_ptGpioArea NX10_GPIO_AREA_T * const ptGpioArea = (NX10_GPIO_AREA_T * const)Addr_NX10_gpio;

#define NX10_DEF_ptArmTimerArea NX10_ARM_TIMER_AREA_T * const ptArmTimerArea = (NX10_ARM_TIMER_AREA_T * const)Addr_NX10_arm_timer;

#define NX10_DEF_ptMmioCtrlArea NX10_MMIO_CTRL_AREA_T * const ptMmioCtrlArea = (NX10_MMIO_CTRL_AREA_T * const)Addr_NX10_mmio_ctrl;

#define NX10_DEF_ptUart0Area NX10_UART_AREA_T * const ptUart0Area = (NX10_UART_AREA_T * const)Addr_NX10_uart0;
#define NX10_DEF_ptUart1Area NX10_UART_AREA_T * const ptUart1Area = (NX10_UART_AREA_T * const)Addr_NX10_uart1;

#define NX10_DEF_ptMiimuArea NX10_MIIMU_AREA_T * const ptMiimuArea = (NX10_MIIMU_AREA_T * const)Addr_NX10_miimu;

#define NX10_DEF_ptHifIoCtrlArea NX10_HIF_IO_CTRL_AREA_T * const ptHifIoCtrlArea = (NX10_HIF_IO_CTRL_AREA_T * const)Addr_NX10_hif_io_ctrl;

#define NX10_DEF_ptSpiArea NX10_SPI_AREA_T * const ptSpiArea = (NX10_SPI_AREA_T * const)Addr_NX10_spi_motion;

#define NX10_DEF_ptSqiArea NX10_SQI_AREA_T * const ptSqiArea = (NX10_SQI_AREA_T * const)Addr_NX10_sqi;

#define NX10_DEF_ptI2cArea NX10_I2C_AREA_T * const ptI2cArea = (NX10_I2C_AREA_T * const)Addr_NX10_i2c;

#define NX10_DEF_ptUsbDevCtrlArea NX10_USB_DEV_CTRL_AREA_T * const ptUsbDevCtrlArea = (NX10_USB_DEV_CTRL_AREA_T * const)Addr_NX10_usb_dev_ctrl;

#define NX10_DEF_ptUsbDevFifoCtrlArea NX10_USB_DEV_FIFO_CTRL_AREA_T * const ptUsbDevFifoCtrlArea = (NX10_USB_DEV_FIFO_CTRL_AREA_T * const)Addr_NX10_usb_dev_fifo_ctrl;

#define NX10_DEF_ptUsvDevFifoArea NX10_USB_DEV_FIFO_AREA_T * const ptUsvDevFifoArea = (NX10_USB_DEV_FIFO_AREA_T * const)Addr_NX10_usb_dev_fifo;

#define NX10_DEF_ptSystimeArea NX10_SYSTIME_AREA_T * const ptSystimeArea = (NX10_SYSTIME_AREA_T * const)Addr_NX10_systime;

#define NX10_DEF_ptHandshakeCtrlArea NX10_HANDSHAKE_CTRL_AREA_T * const ptHandshakeCtrlArea = (NX10_HANDSHAKE_CTRL_AREA_T * const)Addr_NX10_handshake_ctrl;

#define NX10_DEF_ptDpmArea NX10_DPM_AREA_T * const ptDpmArea = (NX10_DPM_AREA_T * const)Addr_NX10_dpm;

#define NX10_DEF_ptDmacCh0Area NX10_DMAC_CH_AREA_T * const ptDmacCh0Area = (NX10_DMAC_CH_AREA_T * const)Addr_NX10_dmac_ch0;
#define NX10_DEF_ptDmacCh1Area NX10_DMAC_CH_AREA_T * const ptDmacCh1Area = (NX10_DMAC_CH_AREA_T * const)Addr_NX10_dmac_ch1;

#define NX10_DEF_ptDmacRegArea NX10_DMAC_REG_AREA_T * const ptDmacRegArea = (NX10_DMAC_REG_AREA_T * const)Addr_NX10_dmac_reg;

#define NX10_DEF_ptVicArea NX10_VIC_AREA_T * const ptVicArea = (NX10_VIC_AREA_T * const)Addr_NX10_vic;

/*EXTMEM_PRIORITY_CTRL_AREA_T *ptExtmemPriorityCtrlArea = (EXTMEM_PRIORITY_CTRL_AREA_T*);*/

#define NX10_DEF_ptSdramArea NX10_SDRAM_AREA_T * const ptSdramArea = (NX10_SDRAM_AREA_T * const)Addr_NX10_ext_sdram_ctrl;

#define NX10_DEF_ptUsbDevFifoArea NX10_USB_DEV_FIFO_AREA_T * const ptUsbDevFifoArea = (NX10_USB_DEV_FIFO_AREA_T * const)Addr_NX10_usb_dev_fifo;

#define NX10_DEF_ptHandshakeArea NX10_HANDSHAKE_BLOCK_AREA_T * const ptHandshakeArea = (NX10_HANDSHAKE_BLOCK_AREA_T * const)Addr_NX10_intram5_mirror_dtcm;
#define NX10_DEF_ptHandshakeDtcmArmMirrorArea NX10_HANDSHAKE_BLOCK_AREA_T * const ptHandshakeDtcmArmMirrorArea = (NX10_HANDSHAKE_BLOCK_AREA_T * const)Addr_NX10_intram5_mirror_dtcm_arm_mirror;


typedef enum
{
	MMIO_CFG_xm0_io0		= 0x00,
	MMIO_CFG_xm0_io1		= 0x01,
	MMIO_CFG_xm0_io2		= 0x02,
	MMIO_CFG_xm0_io3		= 0x03,
	MMIO_CFG_xm0_io4		= 0x04,
	MMIO_CFG_xm0_io5		= 0x05,
	MMIO_CFG_xm0_rx			= 0x06,
	MMIO_CFG_gpio0			= 0x07,
	MMIO_CFG_gpio1			= 0x08,
	MMIO_CFG_gpio2			= 0x09,
	MMIO_CFG_gpio3			= 0x0a,
	MMIO_CFG_gpio4			= 0x0b,
	MMIO_CFG_gpio5			= 0x0c,
	MMIO_CFG_gpio6			= 0x0d,
	MMIO_CFG_gpio7			= 0x0e,
	MMIO_CFG_phy0_led0		= 0x0f,
	MMIO_CFG_phy0_led1		= 0x10,
	MMIO_CFG_phy0_led2		= 0x11,
	MMIO_CFG_phy0_led3		= 0x12,
	MMIO_CFG_spi0_cs1n		= 0x13,
	MMIO_CFG_spi0_cs2n		= 0x14,
	MMIO_CFG_spi1_clk		= 0x15,
	MMIO_CFG_spi1_cs0n		= 0x16,
	MMIO_CFG_spi1_cs1n		= 0x17,
	MMIO_CFG_spi1_cs2n		= 0x18,
	MMIO_CFG_spi1_miso		= 0x19,
	MMIO_CFG_spi1_mosi		= 0x1a,
	MMIO_CFG_i2c_scl		= 0x1b,
	MMIO_CFG_i2c_sda		= 0x1c,
	MMIO_CFG_uart0_ctsn		= 0x1d,
	MMIO_CFG_uart0_rtsn		= 0x1e,
	MMIO_CFG_uart0_rxd		= 0x1f,
	MMIO_CFG_uart0_txd		= 0x20,
	MMIO_CFG_uart1_ctsn		= 0x21,
	MMIO_CFG_uart1_rtsn		= 0x22,
	MMIO_CFG_uart1_rxd		= 0x23,
	MMIO_CFG_uart1_txd		= 0x24,
	MMIO_CFG_pwm_failure_n		= 0x25,
	MMIO_CFG_pos_enc0_a		= 0x26,
	MMIO_CFG_pos_enc0_b		= 0x27,
	MMIO_CFG_pos_enc0_n		= 0x28,
	MMIO_CFG_pos_enc1_a		= 0x29,
	MMIO_CFG_pos_enc1_b		= 0x2a,
	MMIO_CFG_pos_enc1_n		= 0x2b,
	MMIO_CFG_pos_mp0		= 0x2c,
	MMIO_CFG_pos_mp1		= 0x2d,
	MMIO_CFG_io_link0_in		= 0x2e,
	MMIO_CFG_io_link0_out		= 0x2f,
	MMIO_CFG_io_link0_oe		= 0x30,
	MMIO_CFG_io_link1_in		= 0x31,
	MMIO_CFG_io_link1_out		= 0x32,
	MMIO_CFG_io_link1_oe		= 0x33,
	MMIO_CFG_io_link2_in		= 0x34,
	MMIO_CFG_io_link2_out		= 0x35,
	MMIO_CFG_io_link2_oe		= 0x36,
	MMIO_CFG_io_link3_in		= 0x37,
	MMIO_CFG_io_link3_out		= 0x38,
	MMIO_CFG_io_link3_oe		= 0x39,
	MMIO_CFG_PIO			= 0x3f
} MMIO_CFG_T;

#define MMIO_CFG_DISABLE MMIO_CFG_PIO


#endif	/* __NETX10_IO_AREAS_H__ */

