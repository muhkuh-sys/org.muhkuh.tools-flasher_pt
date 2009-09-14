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


#include "netx5_io_areas.h"
#include "netx500/netx500_regdef.h"


/*-----------------------------------*/

/* netX 5 address windows */
/* Window 0 */
#define NX5_DPM_OFFSET_FIX_DPM_CFG_WINDOW	0x00000
/* Window 1 */
#define NX5_DPM_OFFSET_ASIC_CTRL		0x00100
#define NX5_DPM_OFFSET_ABORT			0x00200
#define NX5_DPM_OFFSET_ZPU			0x00240
#define NX5_DPM_OFFSET_PIO			0x00400
#define NX5_DPM_OFFSET_MIIMU			0x00500
#define NX5_DPM_OFFSET_SPI			0x00600
#define NX5_DPM_OFFSET_SYSTIME			0x00700
#define NX5_DPM_OFFSET_DPM			0x00800
#define NX5_DPM_OFFSET_XPEC0_REG		0x00900
/* Window 2 */
#define NX5_DPM_OFFSET_XPEC0_PRAM		0x01000
#define NX5_DPM_OFFSET_XPEC0_DRAM		0x03000
#define NX5_DPM_OFFSET_XPEC1_REG		0x05000
/* Window 3 */
#define NX5_DPM_OFFSET_XPEC1_PRAM		0x06000
#define NX5_DPM_OFFSET_XPEC1_DRAM		0x08000
/* Window 4 */
#define NX5_DPM_OFFSET_XMAC0			0x0A000
#define NX5_DPM_OFFSET_XMAC1			0x0B000
#define NX5_DPM_OFFSET_POINTER_FIFO		0x0E000
#define NX5_DPM_OFFSET_XPEC_IRQ_REGISTERS	0x0E400
#define NX5_DPM_OFFSET_XC_MEM_PROT		0x0E800
#define NX5_DPM_OFFSET_XC_DEBUG			0x0EC00
#define NX5_DPM_OFFSET_TRIGGER_SAMPLE_UNIT	0x0F000
#define NX5_DPM_OFFSET_FMMUSM			0x0F400
#define NX5_DPM_OFFSET_BUF_MAN			0x0F600
/* Window 5 */
#define NX5_DPM_OFFSET_INTRAM0			0x10000
#define NX5_DPM_OFFSET_INTRAM1			0x18000



const NX5_SPI_AREA_T *ptNetXSpi0Area = (NX5_SPI_AREA_T*)(Addr_NX500_hif_ahbls6+NX5_DPM_OFFSET_SPI);
