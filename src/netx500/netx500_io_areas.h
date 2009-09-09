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

      IO Area for the netX100/500
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

#include "netx500_regdef.h"

#ifndef __NETX500_IO_AREAS_H__
#define __NETX500_IO_AREAS_H__


/*
************************************************************
*   Defines for the I2C Interface
************************************************************
*/
typedef struct
{
        volatile unsigned long ulCtrl;                                  /* I2C Control Register */
        volatile unsigned long ulData;                                  /* I2C Data Register    */
} I2C_AREA_T, *PI2C_AREA_T;

extern const PI2C_AREA_T ptNetXI2CArea;


/*
************************************************************
*   Defines for the SPI Interface
************************************************************
*/
typedef struct
{
        volatile unsigned long ulData;                                  /* SPI Data Register        */
        volatile unsigned long ulStatus;                                /* SPI Status Register      */
        volatile unsigned long ulControl;                               /* SPI Control Register     */
        volatile unsigned long ulInterruptControl;                      /* SPI IRQ Control Register */
} SPI_AREA_T, *PSPI_AREA_T;

extern const PSPI_AREA_T ptNetXSpi0Area;


/*
************************************************************
*   Defines for the UART Interface
************************************************************
*/
typedef struct
{
        volatile unsigned long ulUartdr;                                /* UART Data Register                   */
        volatile unsigned long ulUartrsr;                               /* UART Status Register                 */
        volatile unsigned long ulUartlcr_h;                             /* UART Line Control Register           */
        volatile unsigned long ulUartlcr_m;                             /* UART Baud Rate Divisor MSB           */
        volatile unsigned long ulUartlcr_l;                             /* UART Baud Rate Divisor LSB           */
        volatile unsigned long ulUartcr;                                /* UART Control Register                */
        volatile unsigned long ulUartfr;                                /* UART Flag Register                   */
        volatile unsigned long ulUartiir;                               /* UART IRQ Identification Register     */
        volatile unsigned long ulUartilpr;                              /* UART IrDA Low Power Counter Register */
        volatile unsigned long ulUartrts;                               /* UART UART RTS Control Register       */
        volatile unsigned long ulUartforerun;                           /* UART RTS Leading Cycles              */
        volatile unsigned long ulUarttrail;                             /* UART RTS Trailing Cycles             */
        volatile unsigned long ulUartdrvout;                            /* UART Output Driver Enable Register   */
        volatile unsigned long ulUartcr_2;                              /* UART Baud Rate Mode Control Register */
        volatile unsigned long ulUartrxiflsel;                          /* UART Receive FIFO IRQ Trigger Level  */
        volatile unsigned long ulUarttxiflsel;                          /* UART Transmit FIFO IRQ Trigger Level */
} UART_AREA_T, *PUART_AREA_T;

extern const PUART_AREA_T ptNetXUartArea;


/*
************************************************************
*   Defines for the GPIO Interface
************************************************************
*/
typedef struct
{
        volatile unsigned long aul_gpio_cfg[16];                        /* GPIO Configuration Register        */
        volatile unsigned long aul_gpio_tc[16];                         /* GPIO Threshold or Capture Register */
        volatile unsigned long aul_gpio_counter_ctrl[5];                /* GPIO Counter Control Register      */
        volatile unsigned long aul_gpio_counter_max[5];                 /* GPIO Counter Max Value             */
        volatile unsigned long aul_gpio_counter_cnt[5];                 /* GPIO Current Counter Value         */
        volatile unsigned long ul_gpio_irq_mask_set;                    /* GPIO IRQ Request Enable Mask       */
        volatile unsigned long ul_gpio_irq_mask_rst;                    /* GPIO IRQ Request Disable Mask      */
        volatile unsigned long ul_gpio_systime_cmp;                     /* GPIO System Time NS Compare Value  */
        volatile unsigned long ul_gpio_line;                            /* GPIO Output Register               */
        volatile unsigned long ul_gpio_in;                              /* GPIO Input Register                */
        volatile unsigned long ul_gpio_irq;                             /* GPIO IRQ Register                  */
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


#endif  /*  __NETX500_IO_AREAS_H__ */
