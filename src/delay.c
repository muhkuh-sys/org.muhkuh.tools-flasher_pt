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
  File          : delay.c                                                     
 ----------------------------------------------------------------------------   
  Description:                                                                  
                                                                                
      Creates a delay                                         
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
#include "netx_io_areas.h"
#include "delay.h"

//#if ASIC_TYP==ASIC_TYP_NETX90
//#       include "cortexm_systick.h"
//#endif

/*****************************************************************************/
/*! This function creates a delay                                 
* The function creates a delay with the entered parameter.
*   \param uiDelayUs  Delay value
*
*/
/*****************************************************************************/
void delay_us(unsigned int uiDelayUs)
{
#if ASIC_TYP==ASIC_TYP_NETX90
	HOSTDEF(ptGpioComArea);
	unsigned long ulTimerValue;
	unsigned long ulValue;


	/* Stop the counter. */
	ptGpioComArea->ulGpio_counter0_ctrl = 0;

	/* Convert the delay value to 10ns units. */
	ulTimerValue = uiDelayUs * 100;

	/* Set the maximum timer value. */
	ptGpioComArea->ulGpio_counter0_max = ulTimerValue;

	/*  Clear the current timer value. */
	ptGpioComArea->ulGpio_counter0_cnt = 0;

	/* Start the timer. */
	ulValue  = HOSTMSK(gpio_counter0_ctrl_run);
	ulValue |= HOSTMSK(gpio_counter0_ctrl_once);
	ptGpioComArea->ulGpio_counter0_ctrl = ulValue;

	/* Wait until the timer is not running anymore. */
	do
	{
		ulValue  = ptGpioComArea->ulGpio_counter0_ctrl;
		ulValue &= HOSTMSK(gpio_counter0_ctrl_run);
	} while( ulValue!=0 );

	/* Stop the timer. */
	ptGpioComArea->ulGpio_counter0_ctrl = 0;

	/* Reset the counter max value. */
	ptGpioComArea->ulGpio_counter0_max = 0;
#elif ASIC_TYP==ASIC_TYP_NETIOL
	/* TODO: Continue here... */

#else
	HOSTDEF(ptGpioArea);
	unsigned long ulTimerValue;
	unsigned long ulTimerCtrl;


	/*  Clear the timer register */
	ptGpioArea->aulGpio_counter_ctrl[0] = 0;

	/*  convert delay value to 10ns units */
	ulTimerValue = uiDelayUs * 100;

	/*  wait for 0.5 sec */
	ptGpioArea->aulGpio_counter_max[0] = ulTimerValue;

	/*  Clear the current timer value */
	ptGpioArea->aulGpio_counter_cnt[0] = 0;

	/*  Enable the timer */
	ptGpioArea->aulGpio_counter_ctrl[0] = HOSTMSK(gpio_counter0_ctrl_run)|HOSTMSK(gpio_counter0_ctrl_once);

	do
	{
		ulTimerCtrl  = ptGpioArea->aulGpio_counter_ctrl[0];
		ulTimerCtrl &= HOSTMSK(gpio_counter0_ctrl_run);
	} while( ulTimerCtrl!=0 );

	/*  Clear the timer register */
	ptGpioArea->aulGpio_counter_ctrl[0] = 0;

	/*  Reset the counter max value */
	ptGpioArea->aulGpio_counter_max[0] = 0;
#endif
}

