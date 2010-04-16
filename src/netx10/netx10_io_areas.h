/***************************************************************************
 *   Copyright (C) 2005, 2006, 2007, 2008, 2009 by Hilscher GmbH           *
 *                                                                         *
 *   Author: Christoph Thelen (cthelen@hilscher.com)                       *
 *                                                                         *
 *   Redistribution or unauthorized use without expressed written          *
 *   agreement from the Hilscher GmbH is forbidden.                        *
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


extern NX10_ARM_BOOT_VECTOR_AREA_T * const ptArmBootVectorArea;

extern NX10_SR_AREA_T * const ptSrArea;

extern NX10_CORDIC_AREA_T * const ptCordicArea;

extern NX10_MPWM_AREA_T * const ptMpwmArea;

extern NX10_MENC_AREA_T * const ptMencArea;

extern NX10_XLINK_AREA_T * const ptXlink0Area;
extern NX10_XLINK_AREA_T * const ptXlink1Area;
extern NX10_XLINK_AREA_T * const ptXlink2Area;
extern NX10_XLINK_AREA_T * const ptXlink3Area;

extern NX10_IO_LINK_IRQ_AREA_T * const IoLinkIrqArea;

extern NX10_ADC_CTRL_AREA_T * const ptAdcCtrlArea;

extern NX10_XPIC_TIMER_AREA_T * const ptXpicTimerArea;

extern NX10_XPIC_VIC_AREA_T * const ptXpicVicArea;

extern NX10_XPIC_WDG_AREA_T * const ptXpicWdgArea;

extern NX10_XC_AREA_T * const ptXcArea;

extern NX10_XPEC_AREA_T * const ptXpec0Area;

extern NX10_XPIC_AREA_T * const ptXpicArea;

extern NX10_XPIC_DEBUG_AREA_T * const ptXpicDebugArea;

extern NX10_XMAC_AREA_T * const ptXmac0Area;

extern NX10_POINTER_FIFO_AREA_T * const ptPointerFifoArea;

extern NX10_XPEC_IRQ_REGISTERS_AREA_T * const ptXpecIrqRegistersArea;

extern NX10_XC_MEM_PROT_AREA_T * const ptXcMemProtArea;

extern NX10_BUF_MAN_AREA_T * const ptBufManArea;

extern NX10_ASIC_CTRL_AREA_T * const ptAsicCtrlArea;

extern NX10_EXT_ASYNCMEM_CTRL_AREA_T * const ptExtAsyncmemCtrlArea;
/*Addr_ext_sdram_ctrl*/
extern NX10_WATCHDOG_AREA_T * const ptWatchdogArea;

extern NX10_GPIO_AREA_T * const ptGpioArea;

extern NX10_ARM_TIMER_AREA_T * const ptArmTimerArea;

extern NX10_MMIO_CTRL_AREA_T * const ptMmioCtrlArea;

extern NX10_UART_AREA_T * const ptUart0Area;
extern NX10_UART_AREA_T * const ptUart1Area;

extern NX10_MIIMU_AREA_T * const ptMiimuArea;

extern NX10_HIF_IO_CTRL_AREA_T * const ptHifIoCtrlArea;

extern NX10_SPI_AREA_T * const ptSpiArea;

extern NX10_SQI_AREA_T * const ptSqiArea;

extern NX10_I2C_AREA_T * const ptI2cArea;

extern NX10_USB_DEV_CTRL_AREA_T * const ptUsbDevCtrlArea;

extern NX10_USB_DEV_FIFO_CTRL_AREA_T * const ptUsbDevFifoCtrlArea;

extern NX10_USB_DEV_FIFO_AREA_T * const ptUsvDevFifoArea;

extern NX10_SYSTIME_AREA_T * const ptSystimeArea;

extern NX10_HANDSHAKE_CTRL_AREA_T * const ptHandshakeCtrlArea;

extern NX10_DPM_AREA_T * const ptDpmArea;

extern NX10_DMAC_CH_AREA_T * const ptDmacCh0Area;
extern NX10_DMAC_CH_AREA_T * const ptDmacCh1Area;

extern NX10_DMAC_REG_AREA_T * const ptDmacRegArea;

extern NX10_VIC_AREA_T * const ptVicArea;

/*EXTMEM_PRIORITY_CTRL_AREA_T *ptExtmemPriorityCtrlArea;*/

extern NX10_SDRAM_AREA_T * const ptSdramArea;

extern NX10_USB_DEV_FIFO_AREA_T * const ptUsbDevFifoArea;

extern NX10_HANDSHAKE_BLOCK_AREA_T * const ptHandshakeArea;
extern NX10_HANDSHAKE_BLOCK_AREA_T * const ptHandshakeDtcmArmMirrorArea;


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

