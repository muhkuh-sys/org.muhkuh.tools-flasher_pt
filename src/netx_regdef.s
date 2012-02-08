
#define DO_CONCAT(a,b,c) a##_##b##_##c
#define CONCAT(a,b,c) DO_CONCAT(a,b,c)

#if ASIC_TYP==500
#       define HOST NX500
#       include "netx500_regdef.s"
#elif ASIC_TYP==56
#       define HOST NX56
#       include "netx56_regdef.s"
#elif ASIC_TYP==50
#       define HOST NX50
#       include "netx50_regdef.s"
#elif ASIC_TYP==10
#       define HOST NX10
#       include "netx10_regdef.s"
#else
#       error "no host define set!"
#endif


#define HOSTADR(a)  CONCAT(Adr,HOST,a)
#define HOSTADDR(a) CONCAT(Addr,HOST,a)
#define HOSTMSK(a)  CONCAT(MSK,HOST,a)
#define HOSTSRT(a)  CONCAT(SRT,HOST,a)
#define HOSTADEF(a) CONCAT(HOST,a,AREA_T)
#define HOSTREL(a)  CONCAT(REL_Adr,HOST,a)
