#include "netx_consoleapp.h"
#include "flasher_interface.h"
#if CFG_INCLUDE_SHA1!=0
#       include "sha1.h"
#endif


#ifndef __INTERNAL_FLASH_MAZ_V0_H__
#define __INTERNAL_FLASH_MAZ_V0_H__


NETX_CONSOLEAPP_RESULT_T internal_flash_maz_v0_detect(CMD_PARAMETER_DETECT_T *ptParameter);

NETX_CONSOLEAPP_RESULT_T internal_flash_maz_v0_flash(CMD_PARAMETER_FLASH_T *ptParameter);
NETX_CONSOLEAPP_RESULT_T internal_flash_maz_v0_erase(CMD_PARAMETER_ERASE_T *ptParameter);
NETX_CONSOLEAPP_RESULT_T internal_flash_maz_v0_read(CMD_PARAMETER_READ_T *ptParameter);
#if CFG_INCLUDE_SHA1!=0
NETX_CONSOLEAPP_RESULT_T internal_flash_maz_v0_sha1(CMD_PARAMETER_CHECKSUM_T *ptParameter, SHA_CTX *ptSha1Context);
#endif
NETX_CONSOLEAPP_RESULT_T internal_flash_maz_v0_verify(CMD_PARAMETER_VERIFY_T *ptParameter, NETX_CONSOLEAPP_PARAMETER_T *ptConsoleParams);
NETX_CONSOLEAPP_RESULT_T internal_flash_maz_v0_is_erased(CMD_PARAMETER_ISERASED_T *ptParameter, NETX_CONSOLEAPP_PARAMETER_T *ptConsoleParams);
NETX_CONSOLEAPP_RESULT_T internal_flash_maz_v0_get_erase_area(CMD_PARAMETER_GETERASEAREA_T *ptParameter);


#endif  /* __INTERNAL_FLASH_MAZ_V0_H__ */
