/***************************************************************************
 *   Copyright (C) 2008 by Hilscher GmbH                                   *
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

/***************************************************************************
  File          : netx_io_areas.c
 ----------------------------------------------------------------------------
  Description:

      IO Area for the netX50
 ----------------------------------------------------------------------------
  Todo:

 ----------------------------------------------------------------------------
  Known Problems:

    -

 ----------------------------------------------------------------------------
 ***************************************************************************/


/*
************************************************************
*   Inclusion Area
************************************************************
*/

#include "netx_regdef.h"

#ifndef __NETX_IO_AREAS_H__
#define __NETX_IO_AREAS_H__


/*
************************************************************
*   Defines for the I2C Interface
************************************************************
*/
typedef struct
{
        volatile unsigned long ulMcr;                                   /* Master Control Register      */
        volatile unsigned long ulScr;                                   /* Slave Control Register       */
        volatile unsigned long ulCmd;                                   /* Master Command Register      */
        volatile unsigned long ulMdr;                                   /* Master Data Register         */
        volatile unsigned long ulSdr;                                   /* Slave Data Register          */
        volatile unsigned long ulMfifoCr;                               /* Master FIFO Control Register */
        volatile unsigned long ulSfifoCr;                               /* Slave FIFO Control Register  */
        volatile unsigned long ulSr;                                    /* Status Register              */
        volatile unsigned long ulIrqmsk;                                /* IRQ Mask set/clear Register  */
        volatile unsigned long ulIrqsr;                                 /* RAW IRQ Status Register      */
        volatile unsigned long ulIrqmsked;                              /* Mask IRQ Status Register     */
        volatile unsigned long ulDmacr;                                 /* DMA Control Register         */
} I2C_AREA_T, *PI2C_AREA_T;

extern const PI2C_AREA_T ptNetXI2CArea;


/*
************************************************************
*   Defines for the SPI Interface
************************************************************
*/
typedef struct
{
        volatile unsigned long ul_spi_cr0;                              /* Control Register 0             */
        volatile unsigned long ul_spi_cr1;                              /* Control Register 1             */
        volatile unsigned long ul_spi_dr;                               /* Data Register                  */
        volatile unsigned long ul_spi_sr;                               /* Status Register                */
        volatile unsigned long ul_spi_cpsr;                             /* Clock Prescale Register        */
        volatile unsigned long ul_spi_imsc;                             /* IRQ MAsk set/clear Register    */
        volatile unsigned long ul_spi_ris;                              /* RAW IRQ Status Register        */
        volatile unsigned long ul_spi_mis;                              /* Mask IRQ Status Register       */
        volatile unsigned long ul_spi_icr;                              /* IRQ Clear Register             */
        volatile unsigned long ul_spi_dmacr;                            /* DMA Control Register           */
        volatile unsigned long aul_reserved28[2];
        volatile unsigned long ul_spi_data_register;                    /* Data Register                  */
        volatile unsigned long ul_spi_status_register;                  /* Status Register                */
        volatile unsigned long ul_spi_control_register;                 /* Control Register               */
        volatile unsigned long ul_spi_interrupt_control_register;       /* IRQ Control Register           */
} SPI_AREA_T, *PSPI_AREA_T;

extern const PSPI_AREA_T ptNetXSpi0Area;


/*
************************************************************
*   Defines for the UART Interface
************************************************************
*/
typedef struct
{
        volatile unsigned long ulUartdr;                                /* Data Register                            */
        volatile unsigned long ulUartrsr;                               /* Status Register                          */
        volatile unsigned long ulUartlcr_h;                             /* Line Control Register                    */
        volatile unsigned long ulUartlcr_m;                             /* Baud Rate Divisor MSB                    */
        volatile unsigned long ulUartlcr_l;                             /* Baud Rate Divisor LSB                    */
        volatile unsigned long ulUartcr;                                /* Control Register                         */
        volatile unsigned long ulUartfr;                                /* Flag Register                            */
        volatile unsigned long ulUartiir;                               /* IRQ Identify Register                    */
        volatile unsigned long ulUartilpr;                              /* IRDA Low Power Count Register            */
        volatile unsigned long ulUartrts;                               /* RTS Control Register                     */
        volatile unsigned long ulUartforerun;                           /* RTS Leading Cycles                       */
        volatile unsigned long ulUarttrail;                             /* RTS Trailing Cycles                      */
        volatile unsigned long ulUartdrvout;                            /* Output Driver Enable Register            */
        volatile unsigned long ulUartcr_2;                              /* Baud Rate Mode Control Register          */
        volatile unsigned long ulUartrxiflsel;                          /* RX FIFO Trigger Level and RX-DMA Enable  */
        volatile unsigned long ulUarttxiflsel;                          /* TX FIFO Trigger Level and TX-DMA Enable  */
} UART_AREA_T, *PUART_AREA_T;

extern const PUART_AREA_T ptNetXUartArea;


/*
************************************************************
*   Defines for the GPIO Interface
************************************************************
*/
typedef struct
{
        volatile unsigned long aul_gpio_cfg[32];                        /* Configuration Registers        */
        volatile unsigned long aul_gpio_tc[32];                         /* Threshold or Capture Registers */
        volatile unsigned long aul_gpio_counter_ctrl[5];                /* Counter Control Registers      */
        volatile unsigned long aul_gpio_counter_max[5];                 /* Counter max Values             */
        volatile unsigned long aul_gpio_counter_cnt[5];                 /* Current Counter Values         */
        volatile unsigned long ul_gpio_systime_cmp;                     /* System Time NS Compare Value   */
        volatile unsigned long ul_gpio_line;                            /* Output Register                */ 
        volatile unsigned long ul_gpio_in;                              /* Input Register                 */
        volatile unsigned long ul_gpio_irq_raw;                         /* RAW IRQ Register               */
        volatile unsigned long ul_gpio_irq_masked;                      /* Masked IRQ Register            */
        volatile unsigned long ul_gpio_irq_mask_set;                    /* IRQ Request Mask Enable        */
        volatile unsigned long ul_gpio_irq_mask_rst;                    /* IRQ Request Mask Disable       */
        volatile unsigned long ul_gpio_cnt_irq_raw;                     /* RAW IRQ Register               */
        volatile unsigned long ul_gpio_cnt_irq_masked;                  /* Mask IRQ Register              */
        volatile unsigned long ul_gpio_cnt_irq_mask_set;                /* IRQ Request Mask Enable        */
        volatile unsigned long ul_gpio_cnt_irq_mask_rst;                /* IRQ Request Mask Disable       */
} GPIO_AREA_T, *PGPIO_AREA_T;

extern const PGPIO_AREA_T ptNetXGpioArea;


/*
************************************************************
*   Defines for the netx_global_reg_block1_area
************************************************************
*/
typedef struct
{
        volatile unsigned long ul_sta_netx;
} NETX_GLOBAL_REG_BLOCK_1_AREA_T, *PNETX_GLOBAL_REG_BLOCK_1_AREA_T;

extern const PNETX_GLOBAL_REG_BLOCK_1_AREA_T ptNetXGlobalRegBlock1Area;


/*
************************************************************
*   Defines for the netx_global_reg_block_2
************************************************************
*/
typedef struct
{
        volatile unsigned long ul_reserved_00;
        volatile unsigned long ul_clk_reg;
        volatile unsigned long ul_if_conf1;
        volatile unsigned long ul_if_conf2;
        volatile unsigned long aul_ext_bus_config[4];
        volatile unsigned long ul_io_reg_mode0;
        volatile unsigned long ul_io_reg_drv_en0;
        volatile unsigned long ul_io_reg_data0;
        volatile unsigned long ul_io_reg_reserved_2c;
        volatile unsigned long ul_io_reg_mode1;
        volatile unsigned long ul_io_reg_drv_en1;
        volatile unsigned long ul_io_reg_data1;
        volatile unsigned long ul_io_reg_reserved_3c;
        union
        {
                struct
                {
                        volatile unsigned long ul_mb_base0;
                        volatile unsigned long ul_mb_mapping0;
                        volatile unsigned long ul_mb_base1;
                        volatile unsigned long ul_mb_mapping1;
                        volatile unsigned long ul_mb_base2;
                        volatile unsigned long ul_mb_mapping2;
                        volatile unsigned long ul_mb_base3;
                        volatile unsigned long ul_mb_mapping3;
                        volatile unsigned long ul_mb_base4;
                        volatile unsigned long ul_mb_mapping4;
                        volatile unsigned long ul_mb_base5;
                        volatile unsigned long ul_mb_mapping5;
                        volatile unsigned long ul_mb_base6;
                        volatile unsigned long ul_mb_mapping6;
                        volatile unsigned long ul_mb_base7;
                        volatile unsigned long ul_mb_mapping7;
                } s;
                volatile unsigned long aul_mb_config[16];
        } u_mb;
        volatile unsigned long aul_hs_ctrl[16];
} NETX_GLOBAL_REG_BLOCK_2_AREA_T, *PNETX_GLOBAL_REG_BLOCK_2_AREA_T;

extern const PNETX_GLOBAL_REG_BLOCK_2_AREA_T ptNetXGlobalRegBlock2Area;


#endif  /*  __NETX_IO_AREAS_H__ */
