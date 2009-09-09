
#ifndef __NETX_IO_AREAS_H__
#define __NETX_IO_AREAS_H__

#define DO_CONCAT(a,b,c) a##_##b##_##c
#define CONCAT(a,b,c) DO_CONCAT(a,b,c)

#if defined(__NETX500)
	#define HOST NX500
	#include "netx500/netx500_io_areas.h"
#else
#if defined(__NETX50)
	#define HOST NX50
	#include "netx50/netx50_io_areas.h"
#else
	#error "no host define set!"
#endif
#endif


#define HOSTADR(a)  CONCAT(Adr,HOST,a)
#define HOSTADDR(a) CONCAT(Addr,HOST,a)
#define HOSTMSK(a)  CONCAT(MSK,HOST,a)
#define HOSTSRT(a)  CONCAT(SRT,HOST,a)


#endif	/* __NETX_IO_AREAS_H__ */
