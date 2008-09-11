/***************************************************************************
 *   Copyright (C) 2008 by Christoph Thelen                                *
 *   doc_bacardi@users.sourceforge.net                                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#include <string.h>

#include "uprintf.h"
#include "serial_vectors.h"

/*
 No Bells Printf

 This version of printf is very limited compared to the ANSI version.
 It can only handle the following conversions:

  ${length}   :  Interpret the argument as 'unsigned integer' and print it in hexadecimal.
                 The 'length' parameter is optional. It must be one single decimal digit
                 starting with '1' (i.e. '0' is no valid length)


  Notes:

  * Passing a NULL pointer as the format string results in the output "NULL\n"

  * The routine does not know escaping the format identifier. This means it is not possible
    to print '$' characters.

  * The default length for hexadecimal output is 8 digits.

*/

void uprintf(const char* pchFmt, ...)
{
  int           iLen;
  int           iLenParam;
  unsigned int  uDigit;
  char          cChar;
  unsigned long ulArgument;
  va_list       ptArgument;
  typedef void  (*pfnSerialInit_t)(void);
  unsigned long ulResVec;
  unsigned long ulChipId;


  /*  check the output handlers */
  if( serial_vectors.fn.fnPut==NULL )
  {
    /* NOTE:
       On netX500 and netX100 the romcode disables the UART before the call and reenables it when the call
       returns. This means we have to init the uart here.
    */

    /*  is this a netx100/500? */
    ulResVec = *((volatile unsigned long*)0x00000000);
    ulChipId = *((volatile unsigned long*)0x00200008);
    if(  (ulResVec==0xea080001 && ulChipId==0x00001000 )  ||  (ulResVec==0xea080002 && ulChipId==0x00003002 ) )
    {
      /*  yes, it's a netx100/500 */

      /*  reinit the romcode uart routines, they are deactivated right before the 'CALL' command enters the user's code */
      /*  NOTE: the routine is thumb-code, bit #0 of the address must be set to switch the mode */
      ((pfnSerialInit_t)(0x002015f4|1))();

      /*  set the vectors to the romcode */
      /*  NOTE: all routines are thumb-code, bit #0 of the address must be set to switch the mode */
      serial_vectors.fn.fnGet   = (pfnSerialGet_t)(0x00201664|1);
      serial_vectors.fn.fnPut   = (pfnSerialPut_t)(0x00201646|1);
      serial_vectors.fn.fnPeek  = (pfnSerialPeek_t)(0x002016b0|1);
      serial_vectors.fn.fnFlush = (pfnSerialFlush_t)(0x002016ba|1);
    }
  }

  if( serial_vectors.fn.fnPut!=NULL )
  {
    /*  Get initial pointer to first argument */
    va_start(ptArgument, pchFmt);

    /*  Is it a NULL Pointer ? */
    if( pchFmt==NULL )
    {
      pchFmt = "NULL\n";
    }

    while( (cChar=*(pchFmt++))!=0 )
    {
      /*  is there a format command? */
      if( cChar!='$')
      {
        /*  expand LF to CR/LF */
        if( cChar=='\n' )
        {
          serial_vectors.fn.fnPut('\r');
          serial_vectors.fn.fnPut('\n');
          if( serial_vectors.fn.fnFlush!=NULL )
          {
            serial_vectors.fn.fnFlush();
          }
        }
        else
        {
          serial_vectors.fn.fnPut(cChar);
        }
      }
      else
      {
        /*  get the argument */
        ulArgument = va_arg((ptArgument), unsigned long);

        /*  default length is 8 digits */
        iLen = 28;

        /*  get the optional length */
        cChar = *pchFmt;
        iLenParam = cChar - '1';
        if( (iLenParam>=0) && (iLenParam<9) )
        {
          iLen = iLenParam << 2;
          ++pchFmt;
        }

        do
        {
          uDigit = ulArgument >> iLen;
          uDigit &= 0x0f;
          if( uDigit>9 )
          {
            uDigit += 'A'-('9'+1);
          }
          uDigit += '0';
          serial_vectors.fn.fnPut(uDigit);
          iLen -= 4;
        } while( iLen>=0 );
      }
    }
  }
}
