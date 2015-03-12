
/* NOTE: This header is used in C and assembler sources.
 */

#ifndef __ASSEMBLER__
#       include <stddef.h>
#endif

#ifndef __PORTCONTROL_H__
#define __PORTCONTROL_H__


#define MSK_PORTCONTROL_INDEX_MINOR         0x000f
#define SRT_PORTCONTROL_INDEX_MINOR         0
#define MSK_PORTCONTROL_INDEX_MAJOR         0x0ff0
#define SRT_PORTCONTROL_INDEX_MAJOR         4

#define MSK_PORTCONTROL_CONFIGURATION_UDC   0x0003
#define SRT_PORTCONTROL_CONFIGURATION_UDC   0
#define MSK_PORTCONTROL_CONFIGURATION_DRV   0x0030
#define SRT_PORTCONTROL_CONFIGURATION_DRV   4
#define MSK_PORTCONTROL_CONFIGURATION_CTL   0x0f00
#define SRT_PORTCONTROL_CONFIGURATION_CTL   8
#define MSK_PORTCONTROL_CONFIGURATION_SEL   0x7000
#define SRT_PORTCONTROL_CONFIGURATION_SEL   12



#define REEMUX_0  0
#define REEMUX_1  1
#define REEMUX_2  2
#define REEMUX_3  3


#define REEMUX_DRV_04MA  0
#define REEMUX_DRV_06MA  1
#define REEMUX_DRV_08MA  2
#define REEMUX_DRV_12MA  3


#define REEMUX_UDC_NONE         0
#define REEMUX_UDC_PULLUP50K    1
#define REEMUX_UDC_NONE2        2
#define REEMUX_UDC_PULLDOWN50K  3



#define PORTCONTROL_INDEX(P_MAJ, P_MIN) (((P_MAJ << SRT_PORTCONTROL_INDEX_MAJOR) & MSK_PORTCONTROL_INDEX_MAJOR) |\
		                         ((P_MIN << SRT_PORTCONTROL_INDEX_MINOR) & MSK_PORTCONTROL_INDEX_MINOR))

#define PORTCONTROL_CONFIGURATION(P_SEL, P_CTL, P_DRV, P_UDC) (((P_SEL << SRT_PORTCONTROL_CONFIGURATION_SEL)   & MSK_PORTCONTROL_CONFIGURATION_SEL)   |\
		                                               ((P_CTL << SRT_PORTCONTROL_CONFIGURATION_CTL)   & MSK_PORTCONTROL_CONFIGURATION_CTL)   |\
		                                               ((P_DRV << SRT_PORTCONTROL_CONFIGURATION_DRV)   & MSK_PORTCONTROL_CONFIGURATION_DRV)   |\
		                                               ((P_UDC << SRT_PORTCONTROL_CONFIGURATION_UDC)   & MSK_PORTCONTROL_CONFIGURATION_UDC))

/* This value causes the portcontrol_apply routine to do nothing. */
#define PORTCONTROL_SKIP 0xffffU


#ifndef __ASSEMBLER__
void portcontrol_init(void);
void portcontrol_apply(const unsigned short *pusIndex, const unsigned short *pusConfiguration, size_t sizConfiguration);
void portcontrol_apply_mmio(const unsigned char *pucMmioIndex, const unsigned short *pusConfiguration, size_t sizConfiguration);
void portcontrol_restore(const unsigned short *pusIndex, size_t sizConfiguration);
void portcontrol_restore_mmio(const unsigned char *pucMmioIndex, size_t sizConfiguration);
#endif


#endif  /* __PORTCONTROL_H__ */

