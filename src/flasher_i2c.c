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

#include <string.h>

#include "flasher_i2c.h"
#include "netx_io_areas.h"
#include "uprintf.h"

/* ------------------------------------- */

NETX_CONSOLEAPP_RESULT_T i2c_verify_with_progress (unsigned long ulFlashStartAdr, unsigned long ulDataByteLen, const unsigned char *pucDataStartAdr);
NETX_CONSOLEAPP_RESULT_T i2c_read_with_progress   (unsigned long ulFlashStartAdr, unsigned long ulDataByteLen, unsigned char *pucDataStartAdr);

/* ------------------------------------- */

#define ReadBuffer_Size 256
unsigned char pucReadBuffer[ReadBuffer_Size];

void i2c_sendAddress  (unsigned int         uiParams,   int          iStopFlag);
void i2c_readResponse (unsigned char        *pucBuffer, unsigned int uiLength);
void i2c_writeData    (const unsigned char  *pucBuffer, unsigned int uiLength);
void i2c_pollAck      (unsigned int uiAckCnt);

/* ------------------------------------- */

NETX_CONSOLEAPP_RESULT_T i2c_flash(const unsigned char *pbData, unsigned long ulDataByteLen)
{
  NETX_CONSOLEAPP_RESULT_T  tResult;
  const unsigned char       *pbDataCnt;
  const unsigned char       *pbDataEnd;
  unsigned long             ulFlashStartAdr;
  unsigned long             ulFlashAdrCnt;


  ulFlashStartAdr = 0;

  pbDataCnt     = pbData;
  pbDataEnd     = pbDataCnt + ulDataByteLen;
  ulFlashAdrCnt = ulFlashStartAdr;

  while( pbDataCnt<pbDataEnd ) 
  {
    /*  programm the byte */
    i2c_sendAddress(ulFlashAdrCnt, 0);
    i2c_writeData(pbDataCnt, 1);
    i2c_pollAck(512);

    /*  next byte */
    ++pbDataCnt;
    ++ulFlashAdrCnt;
  }


  /*  verify data */
  tResult = i2c_verify_with_progress(ulFlashStartAdr, ulDataByteLen, pbData);
  
  if( tResult!=NETX_CONSOLEAPP_RESULT_OK ) 
  {
     return tResult;
  }

  /*  all ok */
  return NETX_CONSOLEAPP_RESULT_OK;
}


NETX_CONSOLEAPP_RESULT_T i2c_erase(unsigned long ulDataByteLen)
{
        unsigned long       ulFlashStartAdr;
        unsigned long       ulFlashEndAdr;
        unsigned long       ulFlashAdrCnt;
        const unsigned char abEraseBuf[1] = { 0xff };


        /*  check for magic */
        if( ulDataByteLen==0xffffffff )
        {
                uprintf("! Error: complete device magic is not supported for i2c eeproms\n");
                return NETX_CONSOLEAPP_RESULT_ERROR;
        }

        ulFlashStartAdr = 0;
        ulFlashEndAdr = ulFlashStartAdr + ulDataByteLen;

        ulFlashAdrCnt = ulFlashStartAdr;

        while( ulFlashStartAdr<ulFlashEndAdr )
        {
                /*  programm the byte */
                i2c_sendAddress(ulFlashAdrCnt, 0);
                i2c_writeData(abEraseBuf, 1);
                i2c_pollAck(512);

                /*  next byte */
                ++ulFlashAdrCnt;
        }

        /*  all ok */
        return NETX_CONSOLEAPP_RESULT_OK;
}


NETX_CONSOLEAPP_RESULT_T i2c_read(unsigned char *pbData, unsigned long ulDataByteLen)
{
  NETX_CONSOLEAPP_RESULT_T tResult;
  unsigned long ulFlashStartAdr;


  ulFlashStartAdr = 0;

  /*  read data */
  tResult = i2c_read_with_progress(ulFlashStartAdr, ulDataByteLen, pbData);
  
  if( tResult!=NETX_CONSOLEAPP_RESULT_OK ) 
  {
     return tResult;
  }

  /*  all ok */
  return NETX_CONSOLEAPP_RESULT_OK;
}


NETX_CONSOLEAPP_RESULT_T i2c_verify(const unsigned char *pbData, unsigned long ulDataByteLen)
{
  NETX_CONSOLEAPP_RESULT_T tResult;
  unsigned long ulFlashStartAdr;


  ulFlashStartAdr = 0;

  /*  verify data */
  tResult = i2c_verify_with_progress(ulFlashStartAdr, ulDataByteLen, pbData);
  
  if( tResult!=NETX_CONSOLEAPP_RESULT_OK ) 
  {
     return tResult;
  }

  /*  all ok */
  return NETX_CONSOLEAPP_RESULT_OK;
}


/* ------------------------------------- */

NETX_CONSOLEAPP_RESULT_T i2c_verify_with_progress(unsigned long ulFlashStartAdr, unsigned long ulDataByteLen, const unsigned char *pucDataStartAdr)
{
  unsigned long       ulC, ulE;
  const unsigned char *pucDC;
  unsigned long       ulSegSize, ulMaxSegSize;


  ulMaxSegSize = ReadBuffer_Size;

  /*  loop over all data */
  ulC   = ulFlashStartAdr;
  ulE   = ulC + ulDataByteLen;
  pucDC = pucDataStartAdr;

  while( ulC<ulE ) 
  {
     /*  get the next segment, limit it to 'ulMaxSegSize' */
     ulSegSize = ulE - ulC;
     
     if( ulSegSize>ulMaxSegSize ) 
     {
       ulSegSize = ulMaxSegSize;
     }

      /*  read the segment */
      i2c_sendAddress(ulC, 0);
      i2c_readResponse(pucReadBuffer, ulSegSize);

      /*  compare... */
      if( memcmp(pucReadBuffer, pucDC, ulSegSize)!=0 ) 
      {
        return NETX_CONSOLEAPP_RESULT_ERROR;
      }

      /*  next segment */
      ulC += ulSegSize;
      pucDC += ulSegSize;
  }

    /*  compare ok! */
    return NETX_CONSOLEAPP_RESULT_OK;
}


NETX_CONSOLEAPP_RESULT_T i2c_read_with_progress(unsigned long ulFlashStartAdr, unsigned long ulDataByteLen, unsigned char *pucDataStartAdr)
{
  unsigned long ulC, ulE;
  unsigned char *pucDC;
  unsigned long ulSegSize, ulMaxSegSize;


  ulMaxSegSize = ReadBuffer_Size;

  /*  loop over all data */
  ulC = ulFlashStartAdr;
  ulE = ulC + ulDataByteLen;
  pucDC = pucDataStartAdr;

  while( ulC<ulE ) 
  {
          /*  get the next segment, limit it to 'ulMaxSegSize' */
          ulSegSize = ulE - ulC;
          if( ulSegSize>ulMaxSegSize ) 
          {
                  ulSegSize = ulMaxSegSize;
          }

          /*  read the segment */
          i2c_sendAddress(ulC, 0);
          i2c_readResponse(pucDC, ulSegSize);
          
          /*  next segment */
          ulC += ulSegSize;
          pucDC += ulSegSize;
   }

        /*  compare ok! */
        return NETX_CONSOLEAPP_RESULT_OK;

}


/* ------------------------------------- */

void i2c_sendAddress(unsigned int uiParams, int iStopFlag)
{
#ifdef __NETX500
  unsigned long ulVal;


  /*  first byte of the command is the ID */
  ulVal  = 0x50<<HOSTSRT(i2c_ctrl_ID);
  
  /*  set speed to max (HOSTMSK(i2c_ctrl_SPEED)) */
  ulVal |= 4<<HOSTSRT(i2c_ctrl_SPEED);
  
  /*  enable i2c core (HOSTMSK(i2c_ctrl_ENABLE)) */
  ulVal |= HOSTMSK(i2c_ctrl_ENABLE);
  ptNetXI2CArea->ulCtrl = ulVal;

  /*  send parameter data */


  /*  first parameter byte */
  ulVal  = (uiParams >> 8)&0xff;
  
  /*  prepend start data */
  ulVal |= HOSTMSK(i2c_data_CMD2);
  
  /*  execute command */
  ulVal |= HOSTMSK(i2c_data_CMD3);
  ptNetXI2CArea->ulData = ulVal;

  /*  wait for execution */
  while( (ptNetXI2CArea->ulData&HOSTMSK(i2c_data_CMD3))!=0 ) {}


  /*  second parameter byte */
  ulVal  = uiParams&0xff;
  
  /*  execute command */
  ulVal |= HOSTMSK(i2c_data_CMD3);
  
  /*  append stop condition? */
  if( iStopFlag!=0 ) 
  {
          ulVal |= HOSTMSK(i2c_data_CMD0);
  }
  
  ptNetXI2CArea->ulData = ulVal;

  /*  wait for execution */
  while( (ptNetXI2CArea->ulData&HOSTMSK(i2c_data_CMD3))!=0 ) {}
#endif
}


void i2c_readResponse(unsigned char *pucBuffer, unsigned int uiLength)
{
#ifdef __NETX500
        unsigned long ulVal;
        unsigned int  uiCnt;


        uiCnt = 0;
        while( uiCnt<uiLength ) 
        {
           /*  read byte */
           ulVal  = HOSTMSK(i2c_data_CMD1);
           
           /*  execute command */
           ulVal |= HOSTMSK(i2c_data_CMD3);

          /*  is this the first byte? */
          if( uiCnt==0 ) 
          {
             /*  yes -> prepend start data */
             ulVal |= HOSTMSK(i2c_data_CMD2);
          }
          
          /*  is this the last byte? */
          if( (uiCnt+1)==uiLength ) 
          {
             /*  yes -> append stop condition */
             ulVal |= HOSTMSK(i2c_data_CMD0);
          }
          
          ptNetXI2CArea->ulData = ulVal;

          /*  wait exec */
          while( (ptNetXI2CArea->ulData&HOSTMSK(i2c_data_CMD3))!=0 ) {}

          /*  get byte */
          pucBuffer[uiCnt] = (unsigned char)(ptNetXI2CArea->ulData&HOSTMSK(i2c_data_DATA));

          /*  next byte */
          ++uiCnt;
        }
#endif
}


void i2c_writeData(const unsigned char *pucBuffer, unsigned int uiLength)
{
#ifdef __NETX500
        unsigned long ulVal;
        unsigned int uiCnt;


        uiCnt = 0;
        while( uiCnt<uiLength ) 
        {
           /*  set data byte */
           ulVal  = pucBuffer[uiCnt];
           
           /*  execute command */
           ulVal |= HOSTMSK(i2c_data_CMD3);

           /*  is this the last byte? */
           if( (uiCnt+1)==uiLength ) 
           {
                   /*  yes -> append stop condition */
                   ulVal |= HOSTMSK(i2c_data_CMD0);
           }
           
           ptNetXI2CArea->ulData = ulVal;

           /*  wait exec */
           while( (ptNetXI2CArea->ulData&HOSTMSK(i2c_data_CMD3))!=0 ) {}

           /*  next byte */
           ++uiCnt;
        }
#endif
}


void i2c_pollAck(unsigned int uiAckCnt)
{
#ifdef __NETX500
        unsigned long ulVal;


        /*  ack polling can't be done with netX500 :( */
        i2c_sendAddress(0, 0);
        ulVal = HOSTMSK(i2c_data_CMD1)|HOSTMSK(i2c_data_CMD3);
        do {
                /*  send dummy byte */
                ptNetXI2CArea->ulData = ulVal;

                /*  wait exec */
                while( (ptNetXI2CArea->ulData&HOSTMSK(i2c_data_CMD3))!=0 ) {}
        } while( --uiAckCnt!=0 );

        /*  send stop condition */
        ulVal = HOSTMSK(i2c_data_CMD0)|HOSTMSK(i2c_data_CMD1)|HOSTMSK(i2c_data_CMD3);
        ptNetXI2CArea->ulData = ulVal;

        /*  wait exec */
        while( (ptNetXI2CArea->ulData&HOSTMSK(i2c_data_CMD3))!=0 ) {}
#endif
}

