
#ifndef __NETX_IO_AREAS_H__
#define __NETX_IO_AREAS_H__

#define DO_CONCAT(a,b) a##b
#define CONCAT(a,b) DO_CONCAT(a,b)

#if defined(__NETX500)
	#define HOST NX500
	#define HOSTADR(a)  CONCAT(Adr_NX500_,a)
	#define HOSTADDR(a) CONCAT(Addr_NX500_,a)
	#define HOSTMSK(a)  CONCAT(MSK_NX500_,a)
	#define HOSTSRT(a)  CONCAT(SRT_NX500_,a)
	#include "netx500/netx500_io_areas.h"
#else
#if defined(__NETX50)
	#define HOST NX50
	#define HOSTADR(a)  CONCAT(Adr_NX50_,a)
	#define HOSTADDR(a) CONCAT(Addr_NX50_,a)
	#define HOSTMSK(a)  CONCAT(MSK_NX50_,a)
	#define HOSTSRT(a)  CONCAT(SRT_NX50_,a)
	#include "netx50/netx50_io_areas.h"
#else
	#error "no host define set!"
#endif
#endif

#endif	/* __NETX_IO_AREAS_H__ */
