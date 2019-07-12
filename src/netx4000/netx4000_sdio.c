#include "netx4000_sdio.h"

#include "cr7_global_timer.h"
#include "netx_io_areas.h"
#include "portcontrol.h"
#include "uprintf.h"


/* Timeouts
 *
 * The longest command is the sector read command. It needs about 1400 clocks.
 * To be absolutely sure that the command has finished even on slow cards, we
 * set the hardware timeout to 1048576 clocks. That's a TOP of 2^20.
 *
 *
 * CR7 timeout
 *
 * In addition to the SDIO modules timeout, the code provides a timer-based
 * timeout. It should be longer than the timeout of the SDIO hardware module.
 */



typedef enum SDIO_RESULT_ENUM
{
	SDIO_RESULT_Ok                       = 0,
	SDIO_RESULT_CardIsStillBusy          = 1,
	SDIO_RESULT_ErrorsInSdInfo2          = 2,
	SDIO_RESULT_ErrorsInResponse         = 3,
	SDIO_RESULT_CommandTimeout           = 4,
	SDIO_RESULT_SW_CommandTimeout        = 5,
	SDIO_RESULT_DataTimeout              = 6,
	SDIO_RESULT_NoData                   = 7,
	SDIO_RESULT_AccessEndTimeout         = 8,
	SDIO_RESULT_ACMD41Timeout            = 9,
	SDIO_RESULT_UnsupportedVoltageRange  = 10,
	SDIO_RESULT_UnitInitiallyBusy        = 11,
	SDIO_RESULT_NoReactionToReset        = 12,
	SDIO_RESULT_CheckPatternMismatch     = 13,
	SDIO_RESULT_CMD08VoltageRejected     = 14,
	SDIO_RESULT_Invalid_CSD_Version      = 15,
	SDIO_RESULT_InvalidCapacity          = 16
} SDIO_RESULT_T;


/* This is the OCR register. */
#define MSK_SD_OCD_VDD_VOLTAGE         0x00ffffff
#define MSK_SD_OCR_VDD_VOLTAGE_27_28   0x00008000
#define MSK_SD_OCR_VDD_VOLTAGE_28_29   0x00010000
#define MSK_SD_OCR_VDD_VOLTAGE_29_30   0x00020000
#define MSK_SD_OCR_VDD_VOLTAGE_30_31   0x00040000
#define MSK_SD_OCR_VDD_VOLTAGE_31_32   0x00080000
#define MSK_SD_OCR_VDD_VOLTAGE_32_33   0x00100000
#define MSK_SD_OCR_VDD_VOLTAGE_33_34   0x00200000
#define MSK_SD_OCR_VDD_VOLTAGE_34_35   0x00400000
#define MSK_SD_OCR_VDD_VOLTAGE_35_36   0x00800000
#define MSK_SD_OCR_CardCapacityStatus  0x40000000
#define MSK_SD_OCR_CardPowerUpStatus   0x80000000

#define MSK_SD_SCR_SD_BUS_WIDTHS_1Bit  0x00000001
#define MSK_SD_SCR_SD_BUS_WIDTHS_4Bit  0x00000004


/* This is the card status. */
#define MSK_SDIO_CARD_STATUS_AKE_SEQ_ERROR       0x00000008U
#define SRT_SDIO_CARD_STATUS_AKE_SEQ_ERROR       3
#define MSK_SDIO_CARD_STATUS_APP_CMD             0x00000020U
#define SRT_SDIO_CARD_STATUS_APP_CMD             5
#define MSK_SDIO_CARD_STATUS_READY_FOR_DATA      0x00000100U
#define SRT_SDIO_CARD_STATUS_READY_FOR_DATA      8
#define MSK_SDIO_CARD_STATUS_CURRENT_STATE       0x00001e00U
#define SRT_SDIO_CARD_STATUS_CURRENT_STATE       9
#define MSK_SDIO_CARD_STATUS_ERASE_RESET         0x00002000U
#define SRT_SDIO_CARD_STATUS_ERASE_RESET         13
#define MSK_SDIO_CARD_STATUS_CARD_ECC_DISABLED   0x00004000U
#define SRT_SDIO_CARD_STATUS_CARD_ECC_DISABLED   14
#define MSK_SDIO_CARD_STATUS_WP_ERASE_SKIP       0x00008000U
#define SRT_SDIO_CARD_STATUS_WP_ERASE_SKIP       15
#define MSK_SDIO_CARD_STATUS_CSD_OVERWRITE       0x00010000U
#define SRT_SDIO_CARD_STATUS_CSD_OVERWRITE       16
#define MSK_SDIO_CARD_STATUS_ERROR               0x00080000U
#define SRT_SDIO_CARD_STATUS_ERROR               19
#define MSK_SDIO_CARD_STATUS_CC_ERROR            0x00100000U
#define SRT_SDIO_CARD_STATUS_CC_ERROR            20
#define MSK_SDIO_CARD_STATUS_CARD_ECC_FAILED     0x00200000U
#define SRT_SDIO_CARD_STATUS_CARD_ECC_FAILED     21
#define MSK_SDIO_CARD_STATUS_ILLEGAL_COMMAND     0x00400000U
#define SRT_SDIO_CARD_STATUS_ILLEGAL_COMMAND     22
#define MSK_SDIO_CARD_STATUS_COM_CRC_ERROR       0x00800000U
#define SRT_SDIO_CARD_STATUS_COM_CRC_ERROR       23
#define MSK_SDIO_CARD_STATUS_LOCK_UNLOCK_FAILED  0x01000000U
#define SRT_SDIO_CARD_STATUS_LOCK_UNLOCK_FAILED  24
#define MSK_SDIO_CARD_STATUS_CARD_IS_LOCKED      0x02000000U
#define SRT_SDIO_CARD_STATUS_CARD_IS_LOCKED      25
#define MSK_SDIO_CARD_STATUS_WP_VIOLATION        0x04000000U
#define SRT_SDIO_CARD_STATUS_WP_VIOLATION        26
#define MSK_SDIO_CARD_STATUS_ERASE_PARAM         0x08000000U
#define SRT_SDIO_CARD_STATUS_ERASE_PARAM         27
#define MSK_SDIO_CARD_STATUS_ERASE_SEQ_ERROR     0x10000000U
#define SRT_SDIO_CARD_STATUS_ERASE_SEQ_ERROR     28
#define MSK_SDIO_CARD_STATUS_BLOCK_LEN_ERROR     0x20000000U
#define SRT_SDIO_CARD_STATUS_BLOCK_LEN_ERROR     29
#define MSK_SDIO_CARD_STATUS_ADDRESS_ERROR       0x40000000U
#define SRT_SDIO_CARD_STATUS_ADDRESS_ERROR       30
#define MSK_SDIO_CARD_STATUS_OUT_OF_RANGE        0x80000000U
#define SRT_SDIO_CARD_STATUS_OUT_OF_RANGE        31


/* This is a mask for all error bits. */
#define MSK_SDIO_CARD_STATI_ALL_ERRORS   MSK_SDIO_CARD_STATUS_AKE_SEQ_ERROR |\
                                         MSK_SDIO_CARD_STATUS_CSD_OVERWRITE |\
                                         MSK_SDIO_CARD_STATUS_ERROR |\
                                         MSK_SDIO_CARD_STATUS_CC_ERROR |\
                                         MSK_SDIO_CARD_STATUS_CARD_ECC_FAILED |\
                                         MSK_SDIO_CARD_STATUS_ILLEGAL_COMMAND |\
                                         MSK_SDIO_CARD_STATUS_COM_CRC_ERROR |\
                                         MSK_SDIO_CARD_STATUS_LOCK_UNLOCK_FAILED |\
                                         MSK_SDIO_CARD_STATUS_WP_VIOLATION |\
                                         MSK_SDIO_CARD_STATUS_ERASE_PARAM |\
                                         MSK_SDIO_CARD_STATUS_ERASE_SEQ_ERROR |\
                                         MSK_SDIO_CARD_STATUS_BLOCK_LEN_ERROR |\
                                         MSK_SDIO_CARD_STATUS_ADDRESS_ERROR |\
                                         MSK_SDIO_CARD_STATUS_OUT_OF_RANGE


#define MSK_SDIO_R6_AKE_SEQ_ERROR       0x00000008U
#define SRT_SDIO_R6_AKE_SEQ_ERROR       3
#define MSK_SDIO_R6_APP_CMD             0x00000020U
#define SRT_SDIO_R6_APP_CMD             5
#define MSK_SDIO_R6_READY_FOR_DATA      0x00000100U
#define SRT_SDIO_R6_READY_FOR_DATA      8
#define MSK_SDIO_R6_CURRENT_STATE       0x00001e00U
#define SRT_SDIO_R6_CURRENT_STATE       9
#define MSK_SDIO_R6_ERROR               0x00002000U
#define SRT_SDIO_R6_ERROR               13
#define MSK_SDIO_R6_ILLEGAL_COMMAND     0x00004000U
#define SRT_SDIO_R6_ILLEGAL_COMMAND     14
#define MSK_SDIO_R6_COM_CRC_ERROR       0x00008000U
#define SRT_SDIO_R6_COM_CRC_ERROR       15
#define MSK_SDIO_R6_RCA                 0xffff0000U
#define SRT_SDIO_R6_RCA                 16



/* This tables shows the port control indices for the SDIO pins. */
static const unsigned short ausPortcontrol_Index_SDIO[8] =
{
	PORTCONTROL_INDEX(11,  0),      /* SDIO_CLK */
	PORTCONTROL_INDEX(11,  1),      /* SDIO_CMD */
	PORTCONTROL_INDEX(11,  2),      /* SDIO_DAT0 */
	PORTCONTROL_INDEX(11,  3),      /* SDIO_DAT1 */
	PORTCONTROL_INDEX(11,  4),      /* SDIO_DAT2 */
	PORTCONTROL_INDEX(11,  5),      /* SDIO_DAT3 */
	PORTCONTROL_INDEX(11,  6),      /* SDIO_CD */
	PORTCONTROL_INDEX(11,  7)       /* SDIO_WP */
};


/* The module clock is 100MHz. */
#define SDIO_IMCLK_Hz 100000000

#define SDIO_SD_OPTION_TOP_SDCLKx2_13 0x00
#define SDIO_SD_OPTION_TOP_SDCLKx2_14 0x01
#define SDIO_SD_OPTION_TOP_SDCLKx2_15 0x02
#define SDIO_SD_OPTION_TOP_SDCLKx2_16 0x03
#define SDIO_SD_OPTION_TOP_SDCLKx2_17 0x04
#define SDIO_SD_OPTION_TOP_SDCLKx2_18 0x05
#define SDIO_SD_OPTION_TOP_SDCLKx2_19 0x06
#define SDIO_SD_OPTION_TOP_SDCLKx2_20 0x07
#define SDIO_SD_OPTION_TOP_SDCLKx2_21 0x08
#define SDIO_SD_OPTION_TOP_SDCLKx2_22 0x09
#define SDIO_SD_OPTION_TOP_SDCLKx2_23 0x0a
#define SDIO_SD_OPTION_TOP_SDCLKx2_24 0x0b
#define SDIO_SD_OPTION_TOP_SDCLKx2_25 0x0c
#define SDIO_SD_OPTION_TOP_SDCLKx2_26 0x0d
#define SDIO_SD_OPTION_TOP_SDCLKx2_27 0x0e

#define SDIO_SD_OPTION_CTOP_IMCLKx2_10 0x00
#define SDIO_SD_OPTION_CTOP_IMCLKx2_11 0x01
#define SDIO_SD_OPTION_CTOP_IMCLKx2_12 0x02
#define SDIO_SD_OPTION_CTOP_IMCLKx2_13 0x03
#define SDIO_SD_OPTION_CTOP_IMCLKx2_14 0x04
#define SDIO_SD_OPTION_CTOP_IMCLKx2_15 0x05
#define SDIO_SD_OPTION_CTOP_IMCLKx2_16 0x06
#define SDIO_SD_OPTION_CTOP_IMCLKx2_17 0x07
#define SDIO_SD_OPTION_CTOP_IMCLKx2_18 0x08
#define SDIO_SD_OPTION_CTOP_IMCLKx2_19 0x09
#define SDIO_SD_OPTION_CTOP_IMCLKx2_20 0x0a
#define SDIO_SD_OPTION_CTOP_IMCLKx2_21 0x0b
#define SDIO_SD_OPTION_CTOP_IMCLKx2_22 0x0c
#define SDIO_SD_OPTION_CTOP_IMCLKx2_23 0x0d
#define SDIO_SD_OPTION_CTOP_IMCLKx2_24 0x0e

#define SDIO_SD_OPTION_WIDTH_1bit 1
#define SDIO_SD_OPTION_WIDTH_4bit 0


#define RAPSDIO_CMD00    0 | (0 << HOSTSRT(SDIO_SD_CMD_C))
#define RAPSDIO_CMD02    2 | (0 << HOSTSRT(SDIO_SD_CMD_C))
#define RAPSDIO_CMD03    3 | (0 << HOSTSRT(SDIO_SD_CMD_C))
#define RAPSDIO_CMD07    7 | (0 << HOSTSRT(SDIO_SD_CMD_C))
#define RAPSDIO_CMD08    8 | (0 << HOSTSRT(SDIO_SD_CMD_C))
#define RAPSDIO_CMD09    9 | (0 << HOSTSRT(SDIO_SD_CMD_C))
#define RAPSDIO_CMD17   17 | (0 << HOSTSRT(SDIO_SD_CMD_C))
#define RAPSDIO_CMD55   55 | (0 << HOSTSRT(SDIO_SD_CMD_C))
#define RAPSDIO_ACMD06   6 | (1 << HOSTSRT(SDIO_SD_CMD_C))
#define RAPSDIO_ACMD41  41 | (1 << HOSTSRT(SDIO_SD_CMD_C))
#define RAPSDIO_ACMD51  51 | (1 << HOSTSRT(SDIO_SD_CMD_C))

#define RAPSDIO_MMC_CMD01   1 | (0 << HOSTSRT(SDIO_SD_CMD_C))





static void sdio_set_hw_command_timeout_exponent(SDIO_HANDLE_T *ptSdioHandle, unsigned char ucExponent)
{
	HOSTDEF(ptRAPSDIOArea);
	unsigned long ulValue;


	/* Check the range of the exponent. It must be [13,27]. */
	if( ucExponent<13 )
	{
		ucExponent = 13;
	}
	else if( ucExponent>27 )
	{
		ucExponent = 27;
	}
	ptSdioHandle->ulHwCommandTimeoutExponent = ucExponent;

	/* Update the timeout. */
	ulValue  = ptRAPSDIOArea->ulSDIO_SD_OPTION;
	ulValue &= ~HOSTMSK(SDIO_SD_OPTION_TOP);
	ulValue |= ((unsigned long)ucExponent-13) << HOSTSRT(SDIO_SD_OPTION_TOP);
	ptRAPSDIOArea->ulSDIO_SD_OPTION = ulValue;
}


/* NOTE: This routine will at least set a speed of 195312,5Hz even if a lower speed was requested. */
static void sdio_set_clock(SDIO_HANDLE_T *ptSdioHandle, unsigned long ulSdClkKHz, unsigned int uiAutoClk)
{
	HOSTDEF(ptRAPSDIOArea);
	unsigned long ulValue;
	unsigned long ulSdClkBorderKHz;
	unsigned long ulDiv;
	unsigned long ulImclkDivider;
	unsigned long ulSdclkUs;
	unsigned int uiCnt;


	/* Remember the current request without limits. Maybe they change later. */
	ptSdioHandle->ulCurrentSpeedKHz = ulSdClkKHz;

	/* Limit the requested clock to the maximum allowed value. */
	if( ulSdClkKHz>ptSdioHandle->ptSdioOptions->ulMaximumSpeedKHz )
	{
		ulSdClkKHz = ptSdioHandle->ptSdioOptions->ulMaximumSpeedKHz;
	}

	/* Disable the clock. */
	ulValue  = 0;
	ptRAPSDIOArea->ulSDIO_SD_CLK_CTRL = ulValue;

	/* NOTE: IMCLK is 100MHz.
	 *  DIV = 128  ->  SDCLK = IMCLK / 512  ->    195312,5 Hz
	 *  DIV =  64  ->  SDCLK = IMCLK / 256  ->    390625   Hz
	 *  DIV =  32  ->  SDCLK = IMCLK / 128  ->    781250   Hz
	 *  DIV =  16  ->  SDCLK = IMCLK /  64  ->   1562500   Hz
	 *  DIV =   8  ->  SDCLK = IMCLK /  32  ->   3125000   Hz
	 *  DIV =   4  ->  SDCLK = IMCLK /  16  ->   6250000   Hz
	 *  DIV =   2  ->  SDCLK = IMCLK /   8  ->  12500000   Hz
	 *  DIV =   1  ->  SDCLK = IMCLK /   4  ->  25000000   Hz
	 *  DIV =   0  ->  SDCLK = IMCLK /   2  ->  50000000   Hz
	 *  DIV = 255  ->  SDCLK = IMCLK        -> 100000000   Hz
	 *
	 * *** NOTE: disable the clock before changing the DIV value. ***
	 *
	 * According to the manuals are these values the only valid settings
	 * for the DIV field. Other values are not allowed.
	 *
	 * The IMCLK divider IMCLK_DIV for a known SDCLK is:
	 *      SDCLK     = IMCLK / IMCLK_DIV
	 *  <=> IMCLK_DIV = IMCLK / SDCLK
	 *
	 * For the initialization the SDCLK should be no more than 400kHz.
	 * This results in
	 *
	 *      IMCLK_DIV = IMCLK     / SDCLK
	 *                = 100MHz    / 400kHz
	 *                = 100000000 / 400000
	 *                = 250
	 *
	 * The next matching DIV value is 256, which results in an SDCLK of
	 * 3960,6 kHz.
	 */

	/*
	 * Get the clock divider. Do not allow the 255 setting.
	 */

	/* Get the highest SDCLK. We are starting with 50MHz which is a divider of 0.
	 * Note the conversion of SDIO_IMCLK from Hz to kHz.
	 *
	 * The divider is kept in ulValue. Bits 1..8 represent the DIV value.
	 * This makes it easy to start with ulValue=1 and just rotate it left
	 * for further dividers.
	 */
	ulSdClkBorderKHz = (
	                     ( SDIO_IMCLK_Hz / 1000 )   /* Convert from Hz to kHz. */
	                     / 2                        /* Apply the first divider. */
	                   );
	ulImclkDivider = 1;
	do
	{
		/* Is the requested frequency greater or equal than the
		 * current border?
		 */
		if( ulSdClkKHz>=ulSdClkBorderKHz )
		{
			/* That's the best fitting value for DIV. */
			break;
		}

		/* Move to the next divider.
		 *  - Divide the SDCLK by 2 (which results in a right shift).
		 *  - Shift the DIV value one position to the left.
		 */
		ulSdClkBorderKHz >>= 1;
		ulImclkDivider <<= 1;
	/* Stop at the lowest possible frequency. This is the DIV value of 128.
	 * NOTE: The check below uses "2*" because the DIV value is stored in
	 *       bits 1-8 of ulValue.
	 */
	} while( ulImclkDivider<2*128 );

	/* Get the DIV value. */
	ulDiv = (ulImclkDivider >> 1) & 0xff;
//	trace_message_uc(TRACEMSG_SDIO_NewClockDivider, (unsigned char)ulDiv);

	ulValue  = (ulDiv << HOSTSRT(SDIO_SD_CLK_CTRL_DIV)) & HOSTMSK(SDIO_SD_CLK_CTRL_DIV);
	if( uiAutoClk!=0 )
	{
		ulValue |= HOSTMSK(SDIO_SD_CLK_CTRL_SD_CLK_OFFEN);
	}
	ulValue |= HOSTMSK(SDIO_SD_CLK_CTRL_SD_CLK_EN);
	ptRAPSDIOArea->ulSDIO_SD_CLK_CTRL = ulValue;

	/*
	 * Get the command timeout for the new frequency.
	 *
	 * For SDCLK=400kHz and TOP=2^20 this is 2,687076s.
	 * For SDCLK=25MHz and TOP=2^20 this is 42,084ms.
	 */

	/* One 50MHz clock is 20ns. This is the fastest possible SDCLK.
	 *
	 * The lowest timeout exponent is 13, resulting in 8192 SDCLKs.
	 * Multiplied with the SDCLK this is 163,84us.
	 * Round this up to 164us and multiply it with the IMCLK divider and
	 * rest of the timeout exponent:
	 *
	 *   2^(SDIO_HW_TIMEOUT_EXP2-13)
	 */
	/* This has a maximum of 41984 for a IMCLK divider of 256. */
	ulSdclkUs  = 164 * ulImclkDivider;
	/* Multiply with the number of TOP clocks left from 2^13.
	 * This has a maximum of 687865856 (0x29000000) for a IMCLK divider
	 * of 256 and a total TOP of 2^27.
	 * It still fits into 32bits, but results in a delay of 687s, which
	 * is over 11 minutes.
	 */
	uiCnt  = ptSdioHandle->ulHwCommandTimeoutExponent;
	uiCnt -= 13;
	while( uiCnt!=0 )
	{
		ulSdclkUs *= 2;
		--uiCnt;
	}
	/* Add 100us to be definitely later than the hardware timer. */
	ulSdclkUs += 100;
	ptSdioHandle->ulSwCommandTimeoutUs = ulSdclkUs;
}



static SDIO_RESULT_T wait_until_idle(void)
{
	HOSTDEF(ptRAPSDIOArea);
	unsigned long ulValue;
	TIMER_HANDLE_T tTimer;
	int iTimerHasElapsed;
	SDIO_RESULT_T tResult;


	/* Wait until the card is not busy anymore.
	 * NOTE: This should go away within 8 clock cycles.
	 *       The lowest speed of 195312,5 results in a clock cycle
	 *       duration of 5,12us. 8 clock cycles have a duration of
	 *       40,96us.
	 */
	cr7_global_timer_start_us(&tTimer, 41);
	iTimerHasElapsed = 0;
	do
	{
		ulValue  = ptRAPSDIOArea->ulSDIO_SD_INFO2;
		ulValue &= HOSTMSK(SDIO_SD_INFO2_CBSY);
		if( ulValue==0 )
		{
			/* The card is not busy. Start the next command. */
			break;
		}

		iTimerHasElapsed = cr7_global_timer_elapsed(&tTimer);
	} while( iTimerHasElapsed==0 );

	if( iTimerHasElapsed!=0 )
	{
//		trace_message(TRACEMSG_SDIO_StillBusy);
		tResult = SDIO_RESULT_CardIsStillBusy;
	}
	else
	{
		tResult = SDIO_RESULT_Ok;
	}

	return tResult;
}


static SDIO_RESULT_T send_cmd(SDIO_HANDLE_T *ptHandle, unsigned long ulCmd, unsigned long ulArg)
{
	HOSTDEF(ptRAPSDIOArea);
	unsigned long ulValue;
	TIMER_HANDLE_T tTimer;
	int iTimerHasElapsed;
	SDIO_RESULT_T tResult;
	unsigned long ulTimeoutUs;


	/* Wait until the card is not busy anymore. */
	tResult = wait_until_idle();
	if( tResult==SDIO_RESULT_Ok )
	{
		/* Acknowledge any pending "response end" bit. */
		ptRAPSDIOArea->ulSDIO_SD_INFO1 = ~HOSTMSK(SDIO_SD_INFO1_INFO0);

		/* Acknowledge any pending status bits. */
		ulValue  = ~(  HOSTMSK(SDIO_SD_INFO2_ERR0)
			     | HOSTMSK(SDIO_SD_INFO2_ERR1)
			     | HOSTMSK(SDIO_SD_INFO2_ERR2)
			     | HOSTMSK(SDIO_SD_INFO2_ERR3)
			     | HOSTMSK(SDIO_SD_INFO2_ERR4)
			     | HOSTMSK(SDIO_SD_INFO2_ERR5)
			     | HOSTMSK(SDIO_SD_INFO2_ERR6)
			     | HOSTMSK(SDIO_SD_INFO2_ILA) );
		ptRAPSDIOArea->ulSDIO_SD_INFO2 = ulValue;

		/* Set the argument. */
		ptRAPSDIOArea->aulSDIO_SD_ARG[0] = ulArg;
		/* Set the command. */
		ptRAPSDIOArea->ulSDIO_SD_CMD = ulCmd;

		/* Get the software timeout for the current speed. */
		ulTimeoutUs  = ptHandle->ulSwCommandTimeoutUs;

		/* Wait for response end. */
		cr7_global_timer_start_us(&tTimer, ulTimeoutUs);
		iTimerHasElapsed = 0;
		do
		{
			ulValue  = ptRAPSDIOArea->ulSDIO_SD_INFO1;
			ulValue &= HOSTMSK(SDIO_SD_INFO1_INFO0);
			if( ulValue!=0 )
			{
				/* Acknowledge the "response end" bit. */
				ptRAPSDIOArea->ulSDIO_SD_INFO1 = ~HOSTMSK(SDIO_SD_INFO1_INFO0);

				break;
			}

			iTimerHasElapsed = cr7_global_timer_elapsed(&tTimer);
		} while( iTimerHasElapsed==0 );

		if( iTimerHasElapsed==0 )
		{
			/* Check for errors. */
			ulValue  = ptRAPSDIOArea->ulSDIO_SD_INFO2;
			ulValue &=   HOSTMSK(SDIO_SD_INFO2_ERR0)
			           | HOSTMSK(SDIO_SD_INFO2_ERR1)
			           | HOSTMSK(SDIO_SD_INFO2_ERR2)
			           | HOSTMSK(SDIO_SD_INFO2_ERR3)
			           | HOSTMSK(SDIO_SD_INFO2_ERR4)
			           | HOSTMSK(SDIO_SD_INFO2_ERR5)
			           | HOSTMSK(SDIO_SD_INFO2_ERR6)
			           | HOSTMSK(SDIO_SD_INFO2_ILA);
			if( ulValue!=0 )
			{
				/* Command error! */
				uprintf("! SDIO send_cmd error :0x%08x", ulValue);

				/* Acknowledge the error flags. */
				ptRAPSDIOArea->ulSDIO_SD_INFO2 = ~ulValue;

				tResult = SDIO_RESULT_ErrorsInSdInfo2;
			}
			else
			{
				tResult = SDIO_RESULT_Ok;
			}
		}
		else
		{
			tResult = SDIO_RESULT_SW_CommandTimeout;
		}
	}

	return tResult;
}



static SDIO_RESULT_T send_acmd(SDIO_HANDLE_T *ptSdioHandle, unsigned long ulCommand, unsigned long ulArgument)
{
	HOSTDEF(ptRAPSDIOArea);
	SDIO_RESULT_T tResult;
	unsigned long ulValue;


	/* Send CMD55. */
	tResult = send_cmd(ptSdioHandle, RAPSDIO_CMD55, ptSdioHandle->ulRCA);
	if( tResult==SDIO_RESULT_Ok )
	{
		/* This is an R1 response. */
		ulValue  = ptRAPSDIOArea->ulSDIO_SD_RSP10;
		ulValue &= MSK_SDIO_CARD_STATI_ALL_ERRORS;
		/* Mask out the 'illegal command' error to work with the SmartDV model. */
		ulValue &= ~MSK_SDIO_CARD_STATUS_ILLEGAL_COMMAND;
		if( ulValue!=0 )
		{
			/* Received an error from the card. */
//			trace_message_ul(TRACEMSG_SDIO_CardError, ulValue);
			tResult = SDIO_RESULT_ErrorsInResponse;
		}
		else
		{
			/* Send the command. */
			tResult = send_cmd(ptSdioHandle, ulCommand, ulArgument);
		}
	}

	return tResult;
}



static SDIO_RESULT_T read_data(unsigned long *pulData, size_t sizDataDw, unsigned long ulTimeout)
{
	HOSTDEF(ptRAPSDIOArea);
	SDIO_RESULT_T tResult;
	unsigned long ulValue;
	TIMER_HANDLE_T tTimer;
	int iTimerHasElapsed;
	unsigned long *pulCnt;
	unsigned long *pulEnd;


	/* Wait for BRE or error. */
	cr7_global_timer_start_us(&tTimer, ulTimeout);
	tResult = SDIO_RESULT_Ok;
	do
	{
		/* Check for buffer read enable. */
		ulValue  = ptRAPSDIOArea->ulSDIO_SD_INFO2;
		ulValue &= HOSTMSK(SDIO_SD_INFO2_BRE);
		if( ulValue!=0 )
		{
			/* Acknowledge the flag. */
			ptRAPSDIOArea->ulSDIO_SD_INFO2 = ~ulValue;

			break;
		}

		/* Check for error. */
		ulValue  = ptRAPSDIOArea->ulSDIO_SD_INFO2;
		ulValue &=   HOSTMSK(SDIO_SD_INFO2_ERR0)
			   | HOSTMSK(SDIO_SD_INFO2_ERR1)
			   | HOSTMSK(SDIO_SD_INFO2_ERR2)
			   | HOSTMSK(SDIO_SD_INFO2_ERR3)
			   | HOSTMSK(SDIO_SD_INFO2_ERR4)
			   | HOSTMSK(SDIO_SD_INFO2_ERR5)
			   | HOSTMSK(SDIO_SD_INFO2_ERR6)
			   | HOSTMSK(SDIO_SD_INFO2_ILA);
		if( ulValue!=0 )
		{
			/* Acknowledge the error bits. */
			ptRAPSDIOArea->ulSDIO_SD_INFO2 = ~ulValue;

//			trace_message_ul(TRACEMSG_SDIO_Error, ulValue);
			tResult = SDIO_RESULT_ErrorsInSdInfo2;
			break;
		}

		/* Check for access end. */
		ulValue  = ptRAPSDIOArea->ulSDIO_SD_INFO1;
		ulValue &= HOSTMSK(SDIO_SD_INFO1_INFO2);
		if( ulValue!=0 )
		{
			/* Acknowledge the error bits. */
			ptRAPSDIOArea->ulSDIO_SD_INFO1 = ~ulValue;

//			trace_message(TRACEMSG_SDIO_ReadNoData);
			tResult = SDIO_RESULT_NoData;
			break;
		}

		iTimerHasElapsed = cr7_global_timer_elapsed(&tTimer);
		if( iTimerHasElapsed!=0 )
		{
//			trace_message(TRACEMSG_SDIO_CommandTimeOut);
			tResult = SDIO_RESULT_DataTimeout;
		}
	} while( iTimerHasElapsed==0 );


	if( tResult==SDIO_RESULT_Ok )
	{
		/* Read the block data. */
		pulCnt = pulData;
		pulEnd = pulData + sizDataDw;
		ulValue = 0;
		while( pulCnt<pulEnd )
		{
			*(pulCnt++) = ptRAPSDIOArea->ulSDIO_SD_BUF0;
		}

		/* Wait for BRE or error. */
		cr7_global_timer_start_us(&tTimer, ulTimeout);
		do
		{
			/* Check for access end. */
			ulValue  = ptRAPSDIOArea->ulSDIO_SD_INFO1;
			ulValue &= HOSTMSK(SDIO_SD_INFO1_INFO2);
			if( ulValue!=0 )
			{
				/* Acknowledge the flag. */
				ptRAPSDIOArea->ulSDIO_SD_INFO1 = ~ulValue;
				break;
			}

			iTimerHasElapsed = cr7_global_timer_elapsed(&tTimer);
			if( iTimerHasElapsed!=0 )
			{
//				trace_message(TRACEMSG_SDIO_CommandTimeOut);
				tResult = SDIO_RESULT_AccessEndTimeout;
			}
		} while( iTimerHasElapsed==0 );
	}

	return tResult;
}



static SDIO_RESULT_T sdio_poll_acmd41(SDIO_HANDLE_T *ptSdioHandle, unsigned long ulArgument, unsigned long *pulOCR)
{
	HOSTDEF(ptRAPSDIOArea);
	SDIO_RESULT_T tResult;
	unsigned long ulOcrRegister;
	unsigned int uiRetriesLeft;


	uiRetriesLeft = 1000;
	do
	{
		tResult = send_acmd(ptSdioHandle, RAPSDIO_ACMD41, ulArgument);
		if( tResult==SDIO_RESULT_Ok )
		{
			/* This is an R3 response. */
			ulOcrRegister = ptRAPSDIOArea->ulSDIO_SD_RSP10;

			/* Is the card still busy? */
			if( (ulOcrRegister&MSK_SD_OCR_CardPowerUpStatus)!=0 )
			{
				/* No, the card is no longer busy. */
				*pulOCR = ulOcrRegister;
				break;
			}
			else
			{
				/* The card is still busy. Retry? */
				if( uiRetriesLeft==0 )
				{
					/* No more retries left. */
					tResult = SDIO_RESULT_ACMD41Timeout;
				}
				else
				{
					--uiRetriesLeft;
				}
			}
		}
	} while( tResult==SDIO_RESULT_Ok );

	return tResult;
}



static SDIO_RESULT_T sdio_read_scr_register(SDIO_HANDLE_T *ptSdioHandle, unsigned long *pulData)
{
	HOSTDEF(ptRAPSDIOArea);
	SDIO_RESULT_T tResult;
	unsigned long ulValue;


	/* Read 8 bytes. */
	ptRAPSDIOArea->ulSDIO_SD_SIZE = 8;

	tResult = send_acmd(ptSdioHandle, RAPSDIO_ACMD51, 0);
	if( tResult==SDIO_RESULT_Ok )
	{
		/* This is an R1 response. */
		ulValue  = ptRAPSDIOArea->ulSDIO_SD_RSP10;
		ulValue &= MSK_SDIO_CARD_STATI_ALL_ERRORS;
		if( ulValue!=0 )
		{
			/* Received an error from the card. */
//			trace_message_ul(TRACEMSG_SDIO_CardError, ulValue);
			tResult = SDIO_RESULT_ErrorsInResponse;
		}
		else
		{
			/* Read the SCR register with a size of 8 bytes. */
			tResult = read_data(pulData, 8/sizeof(unsigned long), ptSdioHandle->ulSwCommandTimeoutUs);
		}
	}

	return tResult;
}



static SDIO_RESULT_T sdio_read_csd_register(SDIO_HANDLE_T *ptSdioHandle, unsigned long *pulData)
{
	HOSTDEF(ptRAPSDIOArea);
	SDIO_RESULT_T tResult;


	/* Read 16 bytes. */
	ptRAPSDIOArea->ulSDIO_SD_SIZE = 16;

	tResult = send_cmd(ptSdioHandle, RAPSDIO_CMD09, ptSdioHandle->ulRCA);
	if( tResult==SDIO_RESULT_Ok )
	{
		/* This is an R2 response.
		 * The CSD register is now in RSP10 .. RSP76.
		 */
		pulData[0] = ptRAPSDIOArea->ulSDIO_SD_RSP10;
		pulData[1] = ptRAPSDIOArea->ulSDIO_SD_RSP32;
		pulData[2] = ptRAPSDIOArea->ulSDIO_SD_RSP54;
		pulData[3] = ptRAPSDIOArea->ulSDIO_SD_RSP76;
	}

	return tResult;
}



static SDIO_RESULT_T read_data_block(SDIO_HANDLE_T *ptSdioHandle, unsigned long ulAddress, unsigned long *pulData)
{
	HOSTDEF(ptRAPSDIOArea);
	unsigned long ulValue;
	SDIO_RESULT_T tResult;


	/* Read 512 bytes. */
	ptRAPSDIOArea->ulSDIO_SD_SIZE = 512;

	tResult = send_cmd(ptSdioHandle, RAPSDIO_CMD17, ulAddress);
	if( tResult==SDIO_RESULT_Ok )
	{
		/* This is an R1 response. */
		ulValue  = ptRAPSDIOArea->ulSDIO_SD_RSP10;
		ulValue &= MSK_SDIO_CARD_STATI_ALL_ERRORS;
		if( ulValue!=0 )
		{
			/* Received an error from the card. */
//			trace_message_ul(TRACEMSG_SDIO_CardError, ulValue);
			tResult = SDIO_RESULT_ErrorsInResponse;
		}
		else
		{
			/* Read the data. */
			tResult = read_data(pulData, 512/sizeof(unsigned long), ptSdioHandle->ulSwCommandTimeoutUs);
		}
	}

	return tResult;
}



/*-------------------------------------------------------------------------*/


static SDIO_RESULT_T sdio_card_select_voltage(SDIO_HANDLE_T *ptHandle, int iCardHasCmd08)
{
	HOSTDEF(ptRAPSDIOArea);
	unsigned long ulValue;
	SDIO_RESULT_T tResult;
	unsigned long ulOcrRegister;


	/* Get the supported voltage range of the card. */
	ulValue = 0;
	if( iCardHasCmd08!=0 )
	{
		/* Indicate that we support high capacity. */
		ulValue |= MSK_SD_OCR_CardCapacityStatus;
	}
	tResult = send_acmd(ptHandle, RAPSDIO_ACMD41, ulValue);
	if( tResult==SDIO_RESULT_Ok )
	{
		/* This is an R3 response. */
		ulOcrRegister = ptRAPSDIOArea->ulSDIO_SD_RSP10;

		/* Check the voltage range. */
		if( (ulOcrRegister&(MSK_SD_OCR_VDD_VOLTAGE_32_33|MSK_SD_OCR_VDD_VOLTAGE_33_34))==0 )
		{
			/* The card does not support our voltage range. */
//			trace_message_ul(TRACEMSG_SDIO_UnsupportedVoltageRange, ulOcrRegister);
			tResult = SDIO_RESULT_UnsupportedVoltageRange;
		}
		else
		{
			/* Select a voltage range and poll for ready.
			 * NOTE: Just echo the voltage range of the
			 *       card. This seems to be the only valid
			 *       response for the SmartDV models. :(((
			 */
			ulValue = ulOcrRegister & MSK_SD_OCD_VDD_VOLTAGE;
			if( iCardHasCmd08!=0 )
			{
				/* Indicate that we support high capacity. */
				ulValue |= MSK_SD_OCR_CardCapacityStatus;
			}
			tResult = sdio_poll_acmd41(ptHandle, ulValue, &ulOcrRegister);
			if( tResult==SDIO_RESULT_Ok )
			{
				if( iCardHasCmd08==0 )
				{
					/* A card without CMD08 can only support standard capacity. */
					ptHandle->uiCardIsHC = 0;
				}
				else
				{
					if( (ulOcrRegister&MSK_SD_OCR_CardCapacityStatus)!=0 )
					{
						/* The card supports high capacity. */
						ptHandle->uiCardIsHC = 1;
					}
				}
			}
		}
	}

	return tResult;
}



static SDIO_RESULT_T sdio_set_card_to_identification_state(SDIO_HANDLE_T *ptHandle)
{
	HOSTDEF(ptRAPSDIOArea);
	SDIO_RESULT_T tResult;
	union
	{
		unsigned long aul[4];
		unsigned char auc[4*sizeof(unsigned long)];
	} uR2Response;


	uprintf("Set the card to identification state.\n");
	/* Send CMD02. */
	tResult = send_cmd(ptHandle, RAPSDIO_CMD02, 0);
	if( tResult!=SDIO_RESULT_Ok )
	{
		uprintf("Failed to execute CMD02: %d\n", tResult);
	}
	else
	{
		/* This is an R2 response. */
		uR2Response.aul[0] = ptRAPSDIOArea->ulSDIO_SD_RSP10;
		uR2Response.aul[1] = ptRAPSDIOArea->ulSDIO_SD_RSP32;
		uR2Response.aul[2] = ptRAPSDIOArea->ulSDIO_SD_RSP54;
		uR2Response.aul[3] = ptRAPSDIOArea->ulSDIO_SD_RSP76;
		uprintf("R2 response:\n");
		hexdump(uR2Response.auc, sizeof(uR2Response));
	}
	uprintf("\n");

	return tResult;
}



static SDIO_RESULT_T sdio_get_relative_card_address(SDIO_HANDLE_T *ptHandle)
{
	HOSTDEF(ptRAPSDIOArea);
	unsigned long ulResponse;
	unsigned long ulValue;
	SDIO_RESULT_T tResult;
	unsigned long ulRCA;


	uprintf("Get the relative card address...\n");

	/* Send CMD03. */
	tResult = send_cmd(ptHandle, RAPSDIO_CMD03, 0);
	if( tResult!=SDIO_RESULT_Ok )
	{
		uprintf("Failed to execute CMD03: %d\n", tResult);
	}
	else
	{
		/* This is an R6 response. */
		ulResponse = ptRAPSDIOArea->ulSDIO_SD_RSP10;
		uprintf("R6 response: 0x%08x\n", ulResponse);

		/* Did an error occur? */
		ulValue  = ulResponse;
		ulValue &= MSK_SDIO_R6_AKE_SEQ_ERROR | MSK_SDIO_R6_ERROR | MSK_SDIO_R6_ILLEGAL_COMMAND | MSK_SDIO_R6_COM_CRC_ERROR;
		if( ulValue!=0 )
		{
			/* Received an error from the card. */
			uprintf("The card returned an error: 0x%08x\n", ulValue);
			tResult = SDIO_RESULT_ErrorsInResponse;
		}
		else
		{
			/* Extract the RCA from the response.
			 * NOTE: keep the RCA in bits 31:16. They seem to be used there in the further commands. */
			ulRCA = ulResponse & MSK_SDIO_R6_RCA;
			ptHandle->ulRCA = ulRCA;
			uprintf("RCA: 0x%08x\n", ulRCA);
		}
	}

	uprintf("\n");

	return tResult;
}



static SDIO_RESULT_T set_card_to_transfer_mode(SDIO_HANDLE_T *ptHandle)
{
	HOSTDEF(ptRAPSDIOArea);
	unsigned long ulValue;
	SDIO_RESULT_T tResult;


	tResult = send_cmd(ptHandle, RAPSDIO_CMD07, ptHandle->ulRCA);
	if( tResult!=SDIO_RESULT_Ok )
	{
		uprintf("Failed to set the card into transfer mode.\n");
	}
	else
	{
		/* This is an R1b response. */
		ulValue  = ptRAPSDIOArea->ulSDIO_SD_RSP10;
		ulValue &= MSK_SDIO_CARD_STATI_ALL_ERRORS;
		if( ulValue!=0 )
		{
			/* Received an error from the card. */
			uprintf("The card rejected to switch into transfer mode: 0x%08x\n", ulValue);
			tResult = SDIO_RESULT_ErrorsInResponse;
		}
	}

	return tResult;
}



/* This table maps the "time value" field of the CSD TRAN_SPEED value to the multiplier.
 * NOTE: The value is multiplicated with 10 to keep the values integers. This is compensated
 *       with the "transfer rate unit" being 10 times smaller.
 */
static const unsigned long aulTransferSpeedTime[16] =
{
	 0,  /*  0: reserved */
	10,  /*  1: 1.0 */
	12,  /*  2: 1.2 */
	13,  /*  3: 1.3 */
	15,  /*  4: 1.5 */
	20,  /*  5: 2.0 */
	25,  /*  6: 2.5 */
	30,  /*  7: 3.0 */
	35,  /*  8: 3.5 */
	40,  /*  9: 4.0 */
	45,  /* 10: 4.5 */
	50,  /* 11: 5.0 */
	55,  /* 12: 5.5 */
	60,  /* 13: 6.0 */
	70,  /* 14: 7.0 */
	80   /* 15: 8.0 */
};

static const unsigned long aulTransferRateUnit[8] =
{
	   10,  /* 0: 100kbit/s */
	  100,  /* 1: 1Mbit/s */
	 1000,  /* 2: 10Mbit/s */
	10000,  /* 3: 100Mbit/s */
	    0, /* 4: reserved */
	    0, /* 5: reserved */
	    0, /* 6: reserved */
	    0  /* 7: reserved */
};



static SDIO_RESULT_T switch_to_higher_speed(SDIO_HANDLE_T *ptSdioHandle)
{
	SDIO_RESULT_T tResult;
	union CSD_REGISTER_UNION
	{
		unsigned char auc[16];
		unsigned long aul[16/sizeof(unsigned long)];
	} tCsdRegister;
	unsigned long ulTranSpeed;
	unsigned long ulTime;
	unsigned long ulUnit;
	unsigned long ulSpeedKHz;


	/* Get the CSD register. */
	tResult = sdio_read_csd_register(ptSdioHandle, tCsdRegister.aul);
	if( tResult!=SDIO_RESULT_Ok )
	{
		uprintf("Failed to read the CSD register.\n");
	}
	else
	{
		uprintf("CSD register:\n");
		hexdump(tCsdRegister.auc, sizeof(tCsdRegister));

		ulTranSpeed = tCsdRegister.auc[11];
		ulTime = (ulTranSpeed & 0x78U) >> 3U;
		ulTime = aulTransferSpeedTime[ulTime];
		ulUnit =  ulTranSpeed & 7U;
		ulUnit = aulTransferRateUnit[ulUnit];

		ulSpeedKHz = ulTime * ulUnit;
		if( ulSpeedKHz!=0 )
		{
			uprintf("Switching to %dkHz\n", ulSpeedKHz);
			sdio_set_clock(ptSdioHandle, ulSpeedKHz, 1);
		}
	}

	return tResult;
}



static SDIO_RESULT_T switch_bus_to_4bit_if_possible(SDIO_HANDLE_T *ptSdioHandle)
{
	HOSTDEF(ptRAPSDIOArea);
	unsigned long ulValue;
	SDIO_RESULT_T tResult;
	union SCR_REGISTER_UNION
	{
		unsigned char auc[8];
		unsigned long aul[8/sizeof(unsigned long)];
	} tScrRegister;


	/* Get the SCR register. */
	tResult = sdio_read_scr_register(ptSdioHandle, tScrRegister.aul);
	if( tResult!=SDIO_RESULT_Ok )
	{
		uprintf("Failed to read the SCR register.\n");
	}
	else
	{
		uprintf("SCR register:\n");
		hexdump(tScrRegister.auc, sizeof(tScrRegister));

		/* Does the card support 4 bit mode? */
		if( (tScrRegister.auc[1]&4U)==0 )
		{
			uprintf("The card does not support 4 bit mode.\n");
		}
		else
		{
			/* Yes, the card supports 4 bit. */

			/* Send ACMD6 to switch the card to 4 bit mode. */
			tResult = send_acmd(ptSdioHandle, RAPSDIO_ACMD06, 2);
			if( tResult!=SDIO_RESULT_Ok )
			{
				uprintf("Failed to set the card to 4 bit mode.\n");
			}
			else
			{
				/* This is an R1 response. */
				ulValue  = ptRAPSDIOArea->ulSDIO_SD_RSP10;
				ulValue &= MSK_SDIO_CARD_STATI_ALL_ERRORS;
				if( ulValue!=0 )
				{
					/* Received an error from the card. */
					uprintf("The card rejected to switch to 4 bit mode: %08x\n", ulValue);
					tResult = SDIO_RESULT_ErrorsInResponse;
				}
				else
				{
					/* Switch the interface to 4 bit bus. */
					ulValue  = ptRAPSDIOArea->ulSDIO_SD_OPTION;
					ulValue &= ~HOSTMSK(SDIO_SD_OPTION_WIDTH);
					ulValue |= (SDIO_SD_OPTION_WIDTH_4bit << HOSTSRT(SDIO_SD_OPTION_WIDTH)) & HOSTMSK(SDIO_SD_OPTION_WIDTH);
					ptRAPSDIOArea->ulSDIO_SD_OPTION = ulValue;
				}
			}
		}
	}

	return tResult;
}


/*-------------------------------------------------------------------------*/

static SDIO_RESULT_T mmc_select_voltage_and_poll_for_ready(SDIO_HANDLE_T *ptSdioHandle)
{
	HOSTDEF(ptRAPSDIOArea);
	SDIO_RESULT_T tResult;
	unsigned long ulArgument;
	unsigned int uiRetries;
	unsigned long ulOcrRegister;



	/* This host supports a high voltage multimedia card. */
	ulArgument  = MSK_SD_OCR_VDD_VOLTAGE_27_28;
	ulArgument |= MSK_SD_OCR_VDD_VOLTAGE_28_29;
	ulArgument |= MSK_SD_OCR_VDD_VOLTAGE_29_30;
	ulArgument |= MSK_SD_OCR_VDD_VOLTAGE_30_31;
	ulArgument |= MSK_SD_OCR_VDD_VOLTAGE_31_32;
	ulArgument |= MSK_SD_OCR_VDD_VOLTAGE_32_33;
	ulArgument |= MSK_SD_OCR_VDD_VOLTAGE_33_34;
	ulArgument |= MSK_SD_OCR_VDD_VOLTAGE_34_35;
	ulArgument |= MSK_SD_OCR_VDD_VOLTAGE_35_36;
	/* The host supports high capacity cards. */
	ulArgument |= MSK_SD_OCR_CardCapacityStatus;

	uiRetries = 1000;
	do
	{
		/* Poll for ready and select the voltage range. */
		tResult = send_cmd(ptSdioHandle, RAPSDIO_MMC_CMD01, ulArgument);
		if( tResult==SDIO_RESULT_Ok )
		{
			/* This is an R3 response. */
			ulOcrRegister = ptRAPSDIOArea->ulSDIO_SD_RSP10;

			/* Is the card still busy? */
			if( (ulOcrRegister&MSK_SD_OCR_CardPowerUpStatus)!=0 )
			{
				/* No, the card is no longer busy. */
				break;
			}
			else
			{
				/* One more retry used. */
				--uiRetries;
				if( uiRetries==0 )
				{
					tResult = SDIO_RESULT_CardIsStillBusy;
				}
			}
		}
	} while( tResult==SDIO_RESULT_Ok );

	if( tResult==SDIO_RESULT_Ok )
	{
		if( (ulOcrRegister&MSK_SD_OCR_CardCapacityStatus)!=0 )
		{
			/* The card supports high capacity.
			 * NOTE: this field is set to 0 by default.
			 */
			ptSdioHandle->uiCardIsHC = 1;
		}
	}

	return tResult;
}


/*-------------------------------------------------------------------------*/

static SDIO_RESULT_T sdio_get_capacity(SDIO_HANDLE_T *ptSdioHandle)
{
	SDIO_RESULT_T tResult;
	union CSD_REGISTER_UNION
	{
		unsigned char auc[16];
		unsigned long aul[16/sizeof(unsigned long)];
	} tCsdRegister;
	
	unsigned int uiCsdVersion;
	unsigned int uiReadBlBlen;
	unsigned long ulCSize;
	unsigned int uiCSizeMult;
	unsigned int uiBlockLen;
	unsigned int uiMult;
	unsigned int uiMKB;
	unsigned long ulSizeKB;


	ptSdioHandle->ulSizeKB = 0;
	/* Get the CSD register. */
	tResult = sdio_read_csd_register(ptSdioHandle, tCsdRegister.aul);
	if( tResult!=SDIO_RESULT_Ok )
	{
		uprintf("Failed to read the CSD register.\n");
	}
	else
	{
		uprintf("CSD register:\n");
		hexdump(tCsdRegister.auc, sizeof(tCsdRegister));

		/* Get the CSD version.
		 * One of our eMMCs has a version of 3.
		 */
		uiCsdVersion = (tCsdRegister.auc[14] & 0xc0U) >> 6U;
		if( uiCsdVersion==0 || uiCsdVersion==3 )
		{
			/* Get the block length. */
			uiReadBlBlen = tCsdRegister.auc[9] & 0x0fU;
			uiBlockLen = 1U << uiReadBlBlen;

			/* Get the size multiplier. */
			uiCSizeMult = (tCsdRegister.aul[1] & 0x00000380U) >> 7U;
			uiMult = 1U << (uiCSizeMult + 2U);

			/* Get the C_SIZE. */
			ulCSize   =  (unsigned long)(tCsdRegister.auc[6]);
			ulCSize  |= ((unsigned long)(tCsdRegister.auc[7])) <<  8U;
			ulCSize  |= ((unsigned long)(tCsdRegister.auc[8])) << 16U;
			ulCSize  &= 0x0003ffc0U;
			ulCSize >>= 6U;

			/* Reduce the multipliers to kilo byte. */
			uiMKB = uiMult * uiBlockLen / 1024U;

			/* Get the capacity in kilo bytes. */
			ulSizeKB = ulCSize * uiMKB;

//			ullCapacity = ((unsigned long long)uiCSize) * ((unsigned long long)(uiBlockLen*uiMult));
		}
		else if( uiCsdVersion==1 )
		{
			ulCSize  =  (unsigned long)(tCsdRegister.auc[5]);
			ulCSize |= ((unsigned long)(tCsdRegister.auc[6])) <<  8U;
			ulCSize |= ((unsigned long)(tCsdRegister.auc[7])) << 16U;
			ulCSize &= 0x003fffffU;

			ulSizeKB = ulCSize * 512;
		}
		else
		{
			tResult = SDIO_RESULT_Invalid_CSD_Version;
		}

		if( tResult==SDIO_RESULT_Ok )
		{
			ptSdioHandle->ulSizeKB = ulSizeKB;
		}
	}

	return tResult;
}



/*-------------------------------------------------------------------------*/


static SDIO_RESULT_T sdio_initialize(SDIO_HANDLE_T *ptSdioHandle, const SDIO_OPTIONS_T *ptSdioOptions)
{
	HOSTDEF(ptRAPSDIOArea);
	unsigned long ulValue;
	TIMER_HANDLE_T tHandle;
	int iElapsed;
	SDIO_RESULT_T tResult;
	int iCardHasCmd08;
	int iRetries;


	/* Add a pointer to the options. */
	ptSdioHandle->ptSdioOptions = ptSdioOptions;
	/* No speed set yet. */
	ptSdioHandle->ulCurrentSpeedKHz = 0;
	/* Default to no HC. */
	ptSdioHandle->uiCardIsHC = 0;
	/* Default to MMC. */
	ptSdioHandle->uiCardIsMMC = 1;
	/* Set the default software command timeout. */
	ptSdioHandle->ulSwCommandTimeoutUs = 0xffffffff;
	/* Set the initial RCA. */
	ptSdioHandle->ulRCA = 0;

	/* Reset the SDIO unit. */
	ptRAPSDIOArea->ulSDIO_SOFT_RST = 0;
	ptRAPSDIOArea->ulSDIO_SOFT_RST = HOSTMSK(SDIO_SOFT_RST_SDRST);

	/*
	 * Disable all interrupts.
	 * NOTE: Yes, a '1' really disables the IRQ.
	 */
	ulValue  = HOSTMSK(SDIO_SD_INFO1_MASK_MASK0);
	ulValue |= HOSTMSK(SDIO_SD_INFO1_MASK_MASK2);
	ulValue |= HOSTMSK(SDIO_SD_INFO1_MASK_MASK3);
	ulValue |= HOSTMSK(SDIO_SD_INFO1_MASK_MASK4);
	ulValue |= HOSTMSK(SDIO_SD_INFO1_MASK_MASK8);
	ulValue |= HOSTMSK(SDIO_SD_INFO1_MASK_MASK9);
	ptRAPSDIOArea->ulSDIO_SD_INFO1_MASK = ulValue;

	ulValue  = HOSTMSK(SDIO_SD_INFO2_MASK_EMASK0);
	ulValue |= HOSTMSK(SDIO_SD_INFO2_MASK_EMASK1);
	ulValue |= HOSTMSK(SDIO_SD_INFO2_MASK_EMASK2);
	ulValue |= HOSTMSK(SDIO_SD_INFO2_MASK_EMASK3);
	ulValue |= HOSTMSK(SDIO_SD_INFO2_MASK_EMASK4);
	ulValue |= HOSTMSK(SDIO_SD_INFO2_MASK_EMASK5);
	ulValue |= HOSTMSK(SDIO_SD_INFO2_MASK_EMASK6);
	ulValue |= HOSTMSK(SDIO_SD_INFO2_MASK_BMASK0);
	ulValue |= HOSTMSK(SDIO_SD_INFO2_MASK_BMASK1);
	ulValue |= HOSTMSK(SDIO_SD_INFO2_MASK_Reserved3);
	ulValue |= HOSTMSK(SDIO_SD_INFO2_MASK_IMASK);
	ptRAPSDIOArea->ulSDIO_SD_INFO2_MASK = ulValue;

	ulValue  = HOSTMSK(SDIO_SDIO_INFO1_MASK_IOMASK);
	ulValue |= HOSTMSK(SDIO_SDIO_INFO1_MASK_Reserved1);
	ulValue |= HOSTMSK(SDIO_SDIO_INFO1_MASK_MEXPUB52);
	ulValue |= HOSTMSK(SDIO_SDIO_INFO1_MASK_SDIO_INFO1_MASK1);
	ptRAPSDIOArea->ulSDIO_SDIO_INFO1_MASK = ulValue;

	/* Disable DMA mode. */
	ptRAPSDIOArea->ulSDIO_CC_EXT_MODE = 0;

	/* Select normal mode instead of DDR. */
	ptRAPSDIOArea->ulSDIO_SDIF_MODE = 0;

	/* Use 32bit access. */
	ptRAPSDIOArea->ulSDIO_HOST_MODE = 0;

	/* Do not receive SDIO IRQs. */
	ptRAPSDIOArea->ulSDIO_SDIO_MODE = 0;

	/* No data swapping. */
	ptRAPSDIOArea->ulSDIO_EXT_SWAP = 0;

	/* Clear all flags except the card detection states.
	 * NOTE: a flag is cleared by writing a 0 to a bit and keeping all
	 *       others 1. */
	ulValue  = ptRAPSDIOArea->ulSDIO_SD_INFO1;
	ulValue &= ~(HOSTMSK(SDIO_SD_INFO1_INFO0)|HOSTMSK(SDIO_SD_INFO1_INFO2));
	ptRAPSDIOArea->ulSDIO_SD_INFO1 = ulValue;

	/* Clear all flags in the INFO2 register. */
	ulValue  = 0;
	ptRAPSDIOArea->ulSDIO_SD_INFO2 = ulValue;

	/* Clear all flags in the SDIO INFO1 register. */
	ulValue  = 0;
	ptRAPSDIOArea->ulSDIO_SDIO_INFO1 = ulValue;

	/* Set the timeout for the initialization. */
	ulValue  = (SDIO_SD_OPTION_CTOP_IMCLKx2_24 << HOSTSRT(SDIO_SD_OPTION_CTOP)) & HOSTMSK(SDIO_SD_OPTION_CTOP);
	ulValue |= (SDIO_SD_OPTION_TOP_SDCLKx2_27  << HOSTSRT(SDIO_SD_OPTION_TOP)) & HOSTMSK(SDIO_SD_OPTION_TOP);
	ulValue |= (SDIO_SD_OPTION_WIDTH_1bit      << HOSTSRT(SDIO_SD_OPTION_WIDTH)) & HOSTMSK(SDIO_SD_OPTION_WIDTH);
	ptRAPSDIOArea->ulSDIO_SD_OPTION = ulValue;
	sdio_set_hw_command_timeout_exponent(ptSdioHandle, ptSdioHandle->ptSdioOptions->ucHwTimeoutExponentInitialization);

	/* Select port 0. */
	ulValue  = 0;
	ptRAPSDIOArea->ulSDIO_SD_PORTSEL = ulValue;

	/* Set the clock to the initial value. Disable automatic clock control. */
	sdio_set_clock(ptSdioHandle, ptSdioHandle->ptSdioOptions->ulInitialSpeedKHz, 0);

	/* The SD specification requires 74 clock cycles. There seems to be
	 * no way to count the produced clock cycles, so we have to delay for
	 * an appropriate amount of time.
	 *
	 * One clock cycle has a duration of 2,56us. 74 clock cycles have
	 * 3031,04us.
	 */
//	trace_message(TRACEMSG_SDIO_InitialClocksStart);
	cr7_global_timer_delay_us(ptSdioHandle->ptSdioOptions->ulInitialClockGenerationUs);
//	trace_message(TRACEMSG_SDIO_InitialClocksEnd);

	/* Set the clock to the initial value. Enable automatic clock control. */
	sdio_set_clock(ptSdioHandle, ptSdioHandle->ptSdioOptions->ulInitialSpeedKHz, 1);

	/* Check if command is busy. This could happen if the unit is still
	 * serving data after a jump to 0.
	 */
	cr7_global_timer_start_ms(&tHandle, 1);
	do
	{
		/* Reached the timeout? */
		iElapsed = cr7_global_timer_elapsed(&tHandle);
		if( iElapsed!=0 )
		{
			break;
		}

		ulValue  = ptRAPSDIOArea->ulSDIO_SD_INFO2;
		ulValue &= HOSTMSK(SDIO_SD_INFO2_CBSY);
	} while( ulValue!=0 );

	if( iElapsed!=0 )
	{
		uprintf("SDIO is still busy.\n");
		tResult = SDIO_RESULT_UnitInitiallyBusy;
	}
	else
	{
		/* Acknowledge INFO4. */
		ptRAPSDIOArea->ulSDIO_SD_INFO1 = ~HOSTMSK(SDIO_SD_INFO1_INFO4);

		/* Try to reset the card with 8 retries. */
		iRetries = 8;
		do
		{
			/* Send CMD00. */
			tResult = send_cmd(ptSdioHandle, RAPSDIO_CMD00, 0);
			if( tResult!=SDIO_RESULT_Ok )
			{
				/* Are some retries left? */
				if( iRetries!=0 )
				{
					--iRetries;
					/* Delay for 500us. */
					cr7_global_timer_delay_us(500);
				}
				else
				{
					/* No more retries left. */
					tResult = SDIO_RESULT_NoReactionToReset;
					break;
				}
			}
		} while( tResult!=SDIO_RESULT_Ok );

		if( tResult!=SDIO_RESULT_Ok )
		{
			uprintf("Failed to reset the card.\n");
		}
		else
		{
			/* Assume that the card does not support CMD08. */
			iCardHasCmd08 = 0;

			/* Send CMD08. */
			ulValue  = 0xaa;   /* Check pattern. */
			ulValue |= 1 << 8U;  /* 2,7 - 3,6V */
			tResult = send_cmd(ptSdioHandle, RAPSDIO_CMD08, ulValue);
			if( tResult==SDIO_RESULT_Ok )
			{
				/* This is an R7 response. */
				ulValue = ptRAPSDIOArea->ulSDIO_SD_RSP10;
				if( (ulValue&0xff)!=0xaa )
				{
					/* The check pattern does not match. */
					uprintf("CMD08 Check pattern mismatch\n");
					tResult = SDIO_RESULT_CheckPatternMismatch;
				}
				else if( (ulValue&0x100)==0 )
				{
					/* The voltage was not accepted. */
					uprintf("CMD08 Voltage Rejected\n");
					tResult = SDIO_RESULT_CMD08VoltageRejected;
				}
				else
				{
					iCardHasCmd08 = 1;
				}
			}
			else
			{
				/* The card does not support CMD08. */
				tResult = SDIO_RESULT_Ok;
			}

			if( tResult==SDIO_RESULT_Ok )
			{
				tResult = sdio_card_select_voltage(ptSdioHandle, iCardHasCmd08);
				if( tResult==SDIO_RESULT_Ok )
				{
					/* This is an SD card. */
					ptSdioHandle->uiCardIsMMC = 0;
				}
				else if( tResult==SDIO_RESULT_ErrorsInSdInfo2 )
				{
					uprintf("The card does not support ACMD41. This looks like a MMC.\n");
					tResult = SDIO_RESULT_Ok;
				}
				else
				{
					/* Otherwise this is a normal error. */
				}

				if( tResult==SDIO_RESULT_Ok )
				{
					/* Handle SD cards. */
					if( ptSdioHandle->uiCardIsMMC==0 )
					{
						tResult = sdio_set_card_to_identification_state(ptSdioHandle);
						if( tResult==SDIO_RESULT_Ok )
						{
							tResult = sdio_get_relative_card_address(ptSdioHandle);
							if( tResult==SDIO_RESULT_Ok )
							{
								tResult = switch_to_higher_speed(ptSdioHandle);
								if( tResult==SDIO_RESULT_Ok )
								{
									tResult = sdio_get_capacity(ptSdioHandle);
									if( tResult==SDIO_RESULT_Ok )
									{
										tResult = set_card_to_transfer_mode(ptSdioHandle);
										if( tResult==SDIO_RESULT_Ok )
										{
											tResult = switch_bus_to_4bit_if_possible(ptSdioHandle);
										}
									}
								}
							}
						}
					}
					else
					{
						/* Handle MMC cards. */
						tResult = mmc_select_voltage_and_poll_for_ready(ptSdioHandle);
						if( tResult==SDIO_RESULT_Ok )
						{
							tResult = sdio_set_card_to_identification_state(ptSdioHandle);
							if( tResult==SDIO_RESULT_Ok )
							{
								tResult = sdio_get_relative_card_address(ptSdioHandle);
								if( tResult==SDIO_RESULT_Ok )
								{
									tResult = switch_to_higher_speed(ptSdioHandle);
									if( tResult==SDIO_RESULT_Ok )
									{
										tResult = sdio_get_capacity(ptSdioHandle);
										if( tResult==SDIO_RESULT_Ok )
										{
											tResult = set_card_to_transfer_mode(ptSdioHandle);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	if( tResult==SDIO_RESULT_Ok )
	{
		/* Set the timeout for the transfer phase. */
		sdio_set_hw_command_timeout_exponent(ptSdioHandle, ptSdioHandle->ptSdioOptions->ucHwTimeoutExponentTransfer);
		/* Generate the new software timeout from this value. */
		sdio_set_clock(ptSdioHandle, ptSdioHandle->ulCurrentSpeedKHz, 1);
	}

	return tResult;
}



/*-------------------------------------------------------------------------*/

#if 0
static int sdio_restart(void *pvUser)
{
	SDIO_HANDLE_T *ptSdioHandle;


	ptSdioHandle = (SDIO_HANDLE_T*)pvUser;

	/* Set up the port control unit. */
	portcontrol_apply(ausPortcontrol_Index_SDIO, ptSdioHandle->ptSdioOptions->ausPortControl, sizeof(ausPortcontrol_Index_SDIO)/sizeof(ausPortcontrol_Index_SDIO[0]));

	/* Set the speed again. It was updated at speed-ups. */
	sdio_set_clock(ptSdioHandle, ptSdioHandle->ulCurrentSpeedKHz, 0);

	/* Always OK. */
	return 0;
}
#endif


int sdio_read_sector(SDIO_HANDLE_T *ptSdioHandle, unsigned long ulSectorId, unsigned long *pulRead)
{
	SDIO_RESULT_T tResult;
	int iResult;
	unsigned long ulSectorAddress;


	//uprintf("Read sector %d\n", ulSectorId);

	/* Non-HC cards use byte addressing while HC cards use the number of
	 * the sector.
	 */
	if( ptSdioHandle->uiCardIsHC==0 )
	{
		ulSectorAddress = ulSectorId * 512;
	}
	else
	{
		ulSectorAddress = ulSectorId;
	}

	tResult = read_data_block(ptSdioHandle, ulSectorAddress, pulRead);
	if( tResult==SDIO_RESULT_Ok )
	{
		iResult = 0;
	}
	else
	{
		uprintf("Read error\n");
		iResult = -1;
	}

	return iResult;
}


/*-------------------------------------------------------------------------*/


static int sdio_enable_power(const SDIO_OPTIONS_T *ptSdioOptions)
{
	HOSTDEF(ptRAPSysctrlArea);
	TIMER_HANDLE_T tHandle;
	int iResult;
	unsigned long ulValue;
	int iElapsed;


	/* Is the SDIO power already enabled? */
	ulValue  = ptRAPSysctrlArea->ulRAP_SYSCTRL_NOCPWRSTAT;
	ulValue &= HOSTMSK(RAP_SYSCTRL_NOCPWRSTAT_SDIO);
	if( ulValue!=0 )
	{
		/* The power is already enabled. */
		uprintf("The SDIO power is already enabled.\n");
		iResult = 0;
	}
	else
	{
		/* No, the SDIO power is not yet enabled.
		 * Can it be enabled?
		 */
		ulValue  = ptRAPSysctrlArea->ulRAP_SYSCTRL_NOCPWRMASK;
		ulValue &= HOSTMSK(RAP_SYSCTRL_NOCPWRMASK_SDIO);
		if( ulValue==0 )
		{
			/* No, it can not be enabled. */
			uprintf("The SDIO power is masked out.\n");
			iResult = -1;
		}
		else
		{
			/* Yes, the power can be enabled. */
			ulValue  = ptRAPSysctrlArea->ulRAP_SYSCTRL_CLKCFG;
			ulValue |= HOSTMSK(RAP_SYSCTRL_CLKCFG_SDIO);
			ptRAPSysctrlArea->ulRAP_SYSCTRL_CLKCFG = ulValue;

			/* Enable the power. */
			ulValue  = ptRAPSysctrlArea->ulRAP_SYSCTRL_NOCPWRCTRL;
			ulValue |= HOSTMSK(RAP_SYSCTRL_NOCPWRCTRL_SDIO);
			ptRAPSysctrlArea->ulRAP_SYSCTRL_NOCPWRCTRL = ulValue;

			/* Wait until the power is enabled. */
			cr7_global_timer_start_ticks(&tHandle, ptSdioOptions->ulPowerUpTimeoutTicks);
			iResult = 0;
			do
			{
				/* Reached the timeout? */
				iElapsed = cr7_global_timer_elapsed(&tHandle);
				if( iElapsed!=0 )
				{
					uprintf("The SDIO power did not become active after %d ticks.\n", ptSdioOptions->ulPowerUpTimeoutTicks);
					iResult = -1;
					break;
				}
				else
				{
					ulValue  = ptRAPSysctrlArea->ulRAP_SYSCTRL_NOCPWRSTAT;
					ulValue &= HOSTMSK(RAP_SYSCTRL_NOCPWRSTAT_SDIO);
				}
			} while( ulValue==0 );

			/* Delay after the power was enabled. */
			if( iResult==0 )
			{
				ulValue = ptSdioOptions->ulResetDelayTicks;
				if( ulValue!=0 )
				{
					cr7_global_timer_delay_ticks(ulValue);
				}
				uprintf("The SDIO power is now enabled.\n");
			}
		}
	}

	return iResult;
}


/*-------------------------------------------------------------------------*/



int sdio_detect(SDIO_HANDLE_T *ptSdioHandle, const SDIO_OPTIONS_T *ptSdioOptions)
{
	HOSTDEF(ptRAPSDIOArea);
	int iResult;
	unsigned long ulValue;
	SDIO_RESULT_T tResult;
	unsigned long aulSector[512/4];

	/* Be optimistic. */
	iResult = 0;

	/* Set up the port control unit. */
	portcontrol_apply(ausPortcontrol_Index_SDIO, ptSdioOptions->ausPortControl, sizeof(ausPortcontrol_Index_SDIO)/sizeof(ausPortcontrol_Index_SDIO[0]));

	/* Enable the power for the module. */
	iResult = sdio_enable_power(ptSdioOptions);
	if( iResult==0 )
	{
		/* Now the power is up. */

		/* NOTE: the INFO5 bit is only updated if the CD pin was
		 *       constant for a number of IMCLKs. The initial state
		 *       is "UNKNOWN".
		 *       Set the number of detection clocks to 1024, ACK a
		 *       pending INFO5 bit and delay for 1024 IMCLKs. With
		 *       IMCLK=100MHz this results in 10,24us.
		 */

		/* Clear the card detect bit. The initial value is unknown. */
		ptRAPSDIOArea->ulSDIO_SD_INFO1 = ~HOSTMSK(SDIO_SD_INFO1_INFO5);
		
		/* Set the number of clocks the CD signal has to be stable to 2^10 IMCLKs. */
		ulValue  = (SDIO_SD_OPTION_CTOP_IMCLKx2_10 << HOSTSRT(SDIO_SD_OPTION_CTOP)) & HOSTMSK(SDIO_SD_OPTION_CTOP);
		ulValue |= (SDIO_SD_OPTION_TOP_SDCLKx2_27  << HOSTSRT(SDIO_SD_OPTION_TOP)) & HOSTMSK(SDIO_SD_OPTION_TOP);
		ulValue |= (SDIO_SD_OPTION_WIDTH_1bit      << HOSTSRT(SDIO_SD_OPTION_WIDTH)) & HOSTMSK(SDIO_SD_OPTION_WIDTH);
		ptRAPSDIOArea->ulSDIO_SD_OPTION = ulValue;

		/* Delay for 1024 * IMCLK.
		 *
		 * With IMCLK=100MHz this is 1024*10ns = 10240ns.
		 * These are 10240ns/5ns = 2048 ticks.
		 *
		 * With IMCLK=50MHz this is 1024*20ns = 20480ns.
		 * These are 20480ns/5ns = 4096 ticks.
		 */
//		ulValue = (1024 * (1000000000/SDIO_IMCLK_Hz)) / NX4000_GLOBAL_TIMER_TICK_NS;
		/* With values up to 8192, detection is unstable, with 10240, it seems stable. */
		ulValue = (10240 * (1000000000/SDIO_IMCLK_Hz)) / NX4000_GLOBAL_TIMER_TICK_NS;
		cr7_global_timer_delay_ticks(ulValue);

		/* Check if a SD card is present with "ISD0CD state". */
		ulValue  = ptRAPSDIOArea->ulSDIO_SD_INFO1;
		ulValue &= HOSTMSK(SDIO_SD_INFO1_INFO5);
		if( ulValue==0 )
		{
			/* No card detected. */
			uprintf("No card detected with the card detect pin.\n");
			iResult = -1;
		}
		else
		{
			/* A card was detected. */
			uprintf("Detected a card with the card detect pin.\n");

			tResult = sdio_initialize(ptSdioHandle, ptSdioOptions);
			if( tResult!=SDIO_RESULT_Ok )
			{
				uprintf("Failed to initialize the card: %d\n", tResult);
				iResult = -1;
			}
			else
			{
				uprintf("Capacity: %d KB\n", ptSdioHandle->ulSizeKB);
				
				uprintf("Reading first sector\n");
				iResult = sdio_read_sector(ptSdioHandle, 0, aulSector);
				if( tResult!=SDIO_RESULT_Ok )
				{
					uprintf("Failed to read the first sector: %d\n", tResult);
					iResult = -1;
				}
				else
				{
					uprintf("Read OK\n");
				}
			}
		}
	}

	return iResult;
}
