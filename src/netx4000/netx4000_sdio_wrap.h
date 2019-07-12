#ifndef __NETX4000_SDIO_WRAP__
#define __NETX4000_SDIO_WRAP__

#include "flasher_interface.h"


NETX_CONSOLEAPP_RESULT_T sdio_detect_wrap(SDIO_HANDLE_T *ptSdioHandle);
//NETX_CONSOLEAPP_RESULT_T sdio_detect_wrap(SDIO_HANDLE_T *ptSdioHandle, const SDIO_OPTIONS_T *ptSdioOptions);

NETX_CONSOLEAPP_RESULT_T sdio_read(SDIO_HANDLE_T *ptSdioHandle, CMD_PARAMETER_READ_T *ptParams);

#endif /* __NETX4000_SDIO_WRAP__ */

