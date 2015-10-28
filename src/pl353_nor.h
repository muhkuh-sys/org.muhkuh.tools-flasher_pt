
typedef struct PL353_NOR_TIMINGS_STUCT
{
	unsigned short usT_RC;
	unsigned short usT_WC;
	unsigned char  ucT_CEOE;
	unsigned char  ucT_WP;
	unsigned char  ucT_PC;
	unsigned char  ucT_TR;
	unsigned char  ucWeTime;
} PL353_NOR_TIMINGS_T;


typedef enum MEMORY_WIDTH_ENUM
{
	MEMORY_WIDTH_Off    = 0,
	MEMORY_WIDTH_08Bit  = 1,
	MEMORY_WIDTH_16Bit  = 2,
	MEMORY_WIDTH_32Bit  = 3,
	MEMORY_WIDTH_Auto   = 4
} MEMORY_WIDTH_T;

typedef struct PL353_NOR_SETTINGS_STUCT
{
	MEMORY_WIDTH_T tBusWidth;

	/* opMode, for NAND */
	unsigned char ucBurstAlign;
	unsigned char ucBlsTime;
	unsigned char ucAdV;
	unsigned char ucBAA;
	unsigned char ucWrBl;
	unsigned char ucWrSync;
	unsigned char ucRdBl;
	unsigned char ucRdSync;

	PL353_NOR_TIMINGS_T tTimingsNs;
/*	unsigned short ausPortControl08[49]; */
/*	unsigned short ausPortControl16[49]; */
} PL353_NOR_SETTINGS_T;


/* This is the MCLK period in nanoseconds. */
#define PL353_MCLK_NS 20


typedef struct PL353_NOR_HANDLE_STRUCT
{
	unsigned int uiChipSelect;

	unsigned long ulPL353_timings;  /* The prepared value for the PL353 timing register. */
	unsigned long ulPL353_opmode;

	PL353_NOR_TIMINGS_T tTimingsMclks;
} PL353_NOR_HANDLE_T;

extern PL353_NOR_SETTINGS_T g_tPl353_NorDefaultSettings;

unsigned char convert_ns_to_mclks(unsigned long ulValueNs, unsigned long ulInitialNs, unsigned char ucInitialMClk, unsigned char ucMaxMClk);
void nor_update_settings(PL353_NOR_HANDLE_T *ptHandle, PL353_NOR_SETTINGS_T *ptPl353_NorSettings);
void pl353_nor_update_registers(PL353_NOR_HANDLE_T *ptHandle);
void pl353_nor_setup(PL353_NOR_HANDLE_T *ptHandle, MEMORY_WIDTH_T tBusWidth);

//void setup_pl353(unsigned int uiChipSelect, MEMORY_WIDTH_T tBusWidth);
//void setup_flash_nor_pl353(unsigned int uiChipSelect, MEMORY_WIDTH_T tBits);
void setup_flash_nor_pl353(unsigned int uiChipSelect, MEMORY_WIDTH_T tBusWidth);
