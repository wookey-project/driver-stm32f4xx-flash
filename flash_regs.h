#ifndef FLASH_REGS_H_
#define FLASH_REGS_H_

#include "autoconf.h"

#define r_CORTEX_M_FLASH		REG_ADDR(0x40023C00)

#define r_CORTEX_M_FLASH_ACR		(r_CORTEX_M_FLASH + (uint32_t)0x00)	/* FLASH access control register */
#define r_CORTEX_M_FLASH_KEYR		(r_CORTEX_M_FLASH + (uint32_t)0x01)	/* FLASH key register 1*/
#define r_CORTEX_M_FLASH_OPTKEYR	(r_CORTEX_M_FLASH + (uint32_t)0x02)	/* FLASH option key register */
#define r_CORTEX_M_FLASH_SR		(r_CORTEX_M_FLASH + (uint32_t)0x03)	/* FLASH status register */
#define r_CORTEX_M_FLASH_CR		(r_CORTEX_M_FLASH + (uint32_t)0x04)	/* FLASH control register */
#define r_CORTEX_M_FLASH_OPTCR		(r_CORTEX_M_FLASH + (uint32_t)0x05) 	/* FLASH option control register */
#if defined(CONFIG_STM32F439) || defined(CONFIG_STM32F429)			/* FLASH option control register 1 (only on f42xxx/43xxx) */
	#define r_CORTEX_M_FLASH_OPTCR1		(r_CORTEX_M_FLASH + (uint32_t)0x06)
#endif

/*******************  FLASH_ACR register  *****************/
#define FLASH_ACR_LATENCY_Pos		0
#define FLASH_ACR_LATENCY_Msk		((uint32_t)7 << FLASH_ACR_LATENCY_Pos)
#define FLASH_ACR_PRFTEN_Pos		8
#define FLASH_ACR_PRFTEN_Msk		((uint32_t)1 << FLASH_ACR_PRFTEN_Pos)	
#define FLASH_ACR_ICEN_Pos 		9
#define FLASH_ACR_ICEN_Msk		((uint32_t)1 << FLASH_ACR_ICEN_Pos)
#define FLASH_ACR_DCEN_Pos		10
#define FLASH_ACR_DCEN_Msk		((uint32_t)1 << FLASH_ACR_DCEN_Pos)
#define FLASH_ACR_ICRST_Pos		11
#define FLASH_ACR_ICRST_Msk		((uint32_t)1 << FLASH_ACR_ICRST_Pos)
#define FLASH_ACR_DCRST_Pos		12
#define FLASH_ACR_DCRST_Msk		((uint32_t)1 << FLASH_ACR_DCRST_Pos)

/*******************  Flash key register  ***************/
#define KEY1				((uint32_t)0x45670123)
#define KEY2				((uint32_t)0xCDEF89AB)

/*******************  Flash option key register  ***************/
#define OPTKEY1				((uint32_t)0x08192A3B)
#define OPTKEY2				((uint32_t)0x4C5D6E7F)

/*******************  FLASH_SR register  ******************/
#define FLASH_SR_EOP_Pos		0 
#define FLASH_SR_EOP_Msk 		((uint32_t)1 << FLASH_SR_EOP_Pos)
#define FLASH_SR_OPERR_Pos		1
#define FLASH_SR_OPERR_Msk		((uint32_t)1 << FLASH_SR_OPERR_Pos)
#define FLASH_SR_WRPERR_Pos		4
#define FLASH_SR_WRPERR_Msk		((uint32_t)1 << FLASH_SR_WRPERR_Pos)
#define FLASH_SR_PGAERR_Pos		5
#define FLASH_SR_PGAERR_Msk		((uint32_t)1 << FLASH_SR_PGAERR_Pos)
#define FLASH_SR_PGPERR_Pos		6
#define FLASH_SR_PGPERR_Msk		((uint32_t)1 << FLASH_SR_PGPERR_Pos)
#define FLASH_SR_PGSERR_Pos		7
#define FLASH_SR_PGSERR_Msk		((uint32_t)1 << FLASH_SR_PGSERR_Pos)
#if defined(CONFIG_STM32F439) || defined(CONFIG_STM32F429)			/* RDERR (only on f42xxx/43xxx) */
	#define FLASH_SR_RDERR_Pos		8
	#define FLASH_SR_RDERR_Msk		((uint32_t)1 << FLASH_SR_RDERR_Pos)
#endif
#define FLASH_SR_BSY_Pos   		16
#define FLASH_SR_BSY_Msk  		((uint32_t)1 << FLASH_SR_BSY_Pos)

/*******************  FLASH_CR register  ******************/
#define FLASH_CR_PG_Pos 		0 
#define FLASH_CR_PG_Msk  		((uint32_t)1 << FLASH_CR_PG_Pos)
#define FLASH_CR_SER_Pos 		1
#define FLASH_CR_SER_Msk		((uint32_t)1 << FLASH_CR_SER_Pos)
#define FLASH_CR_MER_Pos		2
#define FLASH_CR_MER_Msk		((uint32_t)1 << FLASH_CR_MER_Pos)
#define FLASH_CR_SNB_Pos		3
#define FLASH_CR_SNB_Msk		((uint32_t)0xF << FLASH_CR_SNB_Pos)
#define FLASH_CR_PSIZE_Pos		8
#define FLASH_CR_PSIZE_Msk		((uint32_t)3 << FLASH_CR_PSIZE_Pos)
#if defined(CONFIG_USR_DRV_FLASH_DUAL_BANK)			/* MER1 (only on f42xxx/43xxx) */
	#define FLASH_CR_MER1_Pos		15
	#define FLASH_CR_MER1_Msk		((uint32_t)1 << FLASH_CR_MER1_Pos)
#endif
#define FLASH_CR_STRT_Pos		16
#define FLASH_CR_STRT_Msk		((uint32_t)1 << FLASH_CR_STRT_Pos)
#define FLASH_CR_EOPIE_Pos		24
#define FLASH_CR_EOPIE_Msk		((uint32_t)1 << FLASH_CR_EOPIE_Pos)
#define FLASH_CR_ERRIE_Pos		25
#define FLASH_CR_ERRIE_Msk		((uint32_t)1 << FLASH_CR_ERRIE_Pos)
#define FLASH_CR_LOCK_Pos 		31
#define FLASH_CR_LOCK_Msk 		((uint32_t)1 << FLASH_CR_LOCK_Pos)

/*******************  FLASH_OPTCR register  ***************/
#define FLASH_OPTCR_OPTLOCK_Pos		0
#define FLASH_OPTCR_OPTLOCK_Msk		((uint32_t)1 << FLASH_OPTCR_OPTLOCK_Pos)
#define FLASH_OPTCR_OPTSTRT_Pos		1
#define FLASH_OPTCR_OPTSTRT_Msk		((uint32_t)1 << FLASH_OPTCR_OPTSTRT_Pos)
#define FLASH_OPTCR_BOR_LEV_Pos		2
#define FLASH_OPTCR_BOR_LEV_Msk		((uint32_t)3 << FLASH_OPTCR_BOR_LEV_Pos)
#if defined(CONFIG_STM32F439) || defined(CONFIG_STM32F429)			/* BFB2 (only on f42xxx/43xxx) */
	#define FLASH_OPTCR_BFB2_Pos		4
	#define FLASH_OPTCR_BFB2_Msk		((uint32_t)1 << FLASH_OPTCR_BFB2_Pos)
#endif
#define FLASH_OPTCR_WDG_SW_Pos		5
#define FLASH_OPTCR_WDG_SW_Msk		((uint32_t)1 << FLASH_OPTCR_WDG_SW_Pos)
#define FLASH_OPTCR_nRST_STOP_Pos	6	
#define FLASH_OPTCR_nRST_STOP_Msk	((uint32_t)1 << FLASH_OPTCR_nRST_STOP_Pos)
#define FLASH_OPTCR_nRST_STDBY_Pos	7
#define FLASH_OPTCR_nRST_STDBY_Msk	((uint32_t)1 << FLASH_OPTCR_nRST_STDBY_Pos)
#define FLASH_OPTCR_RDP_Pos		8
#define FLASH_OPTCR_RDP_Msk		((uint32_t)0xFF << FLASH_OPTCR_RDP_Pos)
#define FLASH_OPTCR_nWRP_Pos		16
#define FLASH_OPTCR_nWRP_Msk		((uint32_t)0x0FFF << FLASH_OPTCR_nWRP_Pos)
#if defined(CONFIG_STM32F439) || defined(CONFIG_STM32F429)			/*  Only on f42xxx/43xxx */
	#define FLASH_OPTCR_DB1M_Pos		30			
	#define FLASH_OPTCR_DB1M_Msk		((uint32_t)1 << FLASH_OPTCR_DB1M_Pos)
	#define FLASH_OPTCR_SPRMOD_Pos		31
	#define FLASH_OPTCR_SPRMOD_Msk		((uint32_t)1 << FLASH_OPTCR_SPRMOD_Pos)
#endif

/*******************  FLASH_OPTCR1 register  ***************/
#if defined(CONFIG_STM32F439) || defined(CONFIG_STM32F429)			/*  Only on f42xxx/43xxx */
	#define FLASH_OPTCR1_nWRP_Pos		16
	#define FLASH_OPTCR1_nWRP_Msk		((uint32_t)0x0FFF << FLASH_OPTCR1_nWRP_Pos)
#endif


/****** Adress definition for flash memory sectors ******/

/* Only STM32F429 and STM32F439 have dual 1MB banks */

# if CONFIG_USR_DRV_FLASH_1M
/* SoC with 1Mbyte flash. For these SoC, there can be two configurations:
 * single-bank of 1Mbytes memory length, or dual-bank of two 512Kbytes
 * memory length. Sectors structure are different
 * (See STM-RM0090, table 7.1)
 */

#define FLASH_SECTOR_0			((uint32_t) 0x08000000) /* 16 kB */
#define FLASH_SECTOR_0_END		((uint32_t) 0x08003FFF)
#define FLASH_SECTOR_1			((uint32_t) 0x08004000) /* 16 kB */
#define FLASH_SECTOR_1_END		((uint32_t) 0x08007FFF)
#define FLASH_SECTOR_2			((uint32_t) 0x08008000) /* 16 kB */
#define FLASH_SECTOR_2_END		((uint32_t) 0x0800BFFF)
#define FLASH_SECTOR_3			((uint32_t) 0x0800C000) /* 16 kB */
#define FLASH_SECTOR_3_END		((uint32_t) 0x0800FFFF)
#define FLASH_SECTOR_4			((uint32_t) 0x08010000) /* 64 kB */
#define FLASH_SECTOR_4_END		((uint32_t) 0x0801FFFF)
#define FLASH_SECTOR_5			((uint32_t) 0x08020000) /* 128 kB */
#define FLASH_SECTOR_5_END		((uint32_t) 0x0803FFFF)
#define FLASH_SECTOR_6			((uint32_t) 0x08040000) /* 128 kB */
#define FLASH_SECTOR_6_END		((uint32_t) 0x0805FFFF)
#define FLASH_SECTOR_7			((uint32_t) 0x08060000) /* 128 kB */
#define FLASH_SECTOR_7_END		((uint32_t) 0x0807FFFF)

#  if CONFIG_USR_DRV_FLASH_DUAL_BANK
/* in dual bank mode, the other bank is autonomous and has the same
 * sector structure as the first one
 */

#define FLASH_SECTOR_12			((uint32_t) 0x08080000) /* 16 kB */
#define FLASH_SECTOR_12_END		((uint32_t) 0x08083FFF)
#define FLASH_SECTOR_13			((uint32_t) 0x08084000) /* 16 kB */
#define FLASH_SECTOR_13_END		((uint32_t) 0x08087FFF)
#define FLASH_SECTOR_14			((uint32_t) 0x08088000) /* 16 kB */
#define FLASH_SECTOR_14_END		((uint32_t) 0x0808BFFF)
#define FLASH_SECTOR_15			((uint32_t) 0x0808C000) /* 16 kB */
#define FLASH_SECTOR_15_END		((uint32_t) 0x0808FFFF)
#define FLASH_SECTOR_16			((uint32_t) 0x08090000) /* 64 kB */
#define FLASH_SECTOR_16_END		((uint32_t) 0x0809FFFF)
#define FLASH_SECTOR_17			((uint32_t) 0x080A0000) /* 128 kB */
#define FLASH_SECTOR_17_END		((uint32_t) 0x080BFFFF)
#define FLASH_SECTOR_18			((uint32_t) 0x080C0000) /* 128 kB */
#define FLASH_SECTOR_18_END		((uint32_t) 0x080DFFFF)
#define FLASH_SECTOR_19			((uint32_t) 0x080E0000) /* 128 kB */
#define FLASH_SECTOR_19_END		((uint32_t) 0x080FFFFF)

#  else /* signe bank, continuing with 128kB sectors */

#define FLASH_SECTOR_8			((uint32_t) 0x08080000) /* 128 kB */
#define FLASH_SECTOR_8_END		((uint32_t) 0x0809FFFF)
#define FLASH_SECTOR_9			((uint32_t) 0x080A0000) /* 128 kB */
#define FLASH_SECTOR_9_END		((uint32_t) 0x080BFFFF)
#define FLASH_SECTOR_10			((uint32_t) 0x080C0000) /* 128 kB */
#define FLASH_SECTOR_10_END		((uint32_t) 0x080DFFFF)
#define FLASH_SECTOR_11			((uint32_t) 0x080E0000) /* 128 kB */
#define FLASH_SECTOR_11_END		((uint32_t) 0x080FFFFF)

#  endif /*!banking */

# else /* USR_DRV_FLASH_2M */
/* SoC with 2Mbyte flash. For these SoC, there in only one configuration:
 * a full 2Mbyte flash size in dual banking mode.
 * (See STM-RM0090, table 6)
 */

/* Bank 1 */
#define FLASH_SECTOR_0			((uint32_t) 0x08000000) /* 16 kB */
#define FLASH_SECTOR_0_END		((uint32_t) 0x08003FFF)
#define FLASH_SECTOR_1			((uint32_t) 0x08004000) /* 16 kB */
#define FLASH_SECTOR_1_END		((uint32_t) 0x08007FFF)
#define FLASH_SECTOR_2			((uint32_t) 0x08008000) /* 16 kB */
#define FLASH_SECTOR_2_END		((uint32_t) 0x0800BFFF)
#define FLASH_SECTOR_3			((uint32_t) 0x0800C000) /* 16 kB */
#define FLASH_SECTOR_3_END		((uint32_t) 0x0800FFFF)
#define FLASH_SECTOR_4			((uint32_t) 0x08010000) /* 64 kB */
#define FLASH_SECTOR_4_END		((uint32_t) 0x0801FFFF)
#define FLASH_SECTOR_5			((uint32_t) 0x08020000) /* 128 kB */
#define FLASH_SECTOR_5_END		((uint32_t) 0x0803FFFF)
#define FLASH_SECTOR_6			((uint32_t) 0x08040000) /* 128 kB */
#define FLASH_SECTOR_6_END		((uint32_t) 0x0805FFFF)
#define FLASH_SECTOR_7			((uint32_t) 0x08060000) /* 128 kB */
#define FLASH_SECTOR_7_END		((uint32_t) 0x0807FFFF)
#define FLASH_SECTOR_8			((uint32_t) 0x08080000) /* 128 kB */
#define FLASH_SECTOR_8_END		((uint32_t) 0x0809FFFF)
#define FLASH_SECTOR_9			((uint32_t) 0x080A0000) /* 128 kB */
#define FLASH_SECTOR_9_END		((uint32_t) 0x080BFFFF)
#define FLASH_SECTOR_10			((uint32_t) 0x080C0000) /* 128 kB */
#define FLASH_SECTOR_10_END		((uint32_t) 0x080DFFFF)
#define FLASH_SECTOR_11			((uint32_t) 0x080E0000) /* 128 kB */
#define FLASH_SECTOR_11_END		((uint32_t) 0x080FFFFF)


/* Bank 2 */
#define FLASH_SECTOR_12			((uint32_t) 0x08100000) /* 16 kB */
#define FLASH_SECTOR_12_END		((uint32_t) 0x08083FFF)
#define FLASH_SECTOR_13			((uint32_t) 0x08104000) /* 16 kB */
#define FLASH_SECTOR_13_END		((uint32_t) 0x08107FFF)
#define FLASH_SECTOR_14			((uint32_t) 0x08108000) /* 16 kB */
#define FLASH_SECTOR_14_END		((uint32_t) 0x0810BFFF)
#define FLASH_SECTOR_15			((uint32_t) 0x0810C000) /* 16 kB */
#define FLASH_SECTOR_15_END		((uint32_t) 0x0810FFFF)
#define FLASH_SECTOR_16			((uint32_t) 0x08110000) /* 64 kB */
#define FLASH_SECTOR_16_END		((uint32_t) 0x0811FFFF)
#define FLASH_SECTOR_17			((uint32_t) 0x08120000) /* 128 kB */
#define FLASH_SECTOR_17_END		((uint32_t) 0x0813FFFF)
#define FLASH_SECTOR_18			((uint32_t) 0x08140000) /* 128 kB */
#define FLASH_SECTOR_18_END		((uint32_t) 0x0815FFFF)
#define FLASH_SECTOR_19			((uint32_t) 0x08160000) /* 128 kB */
#define FLASH_SECTOR_19_END		((uint32_t) 0x0817FFFF)
#define FLASH_SECTOR_20			((uint32_t) 0x08180000) /* 128 kB */
#define FLASH_SECTOR_20_END		((uint32_t) 0x0819FFFF)
#define FLASH_SECTOR_21			((uint32_t) 0x081A0000) /* 128 kB */
#define FLASH_SECTOR_21_END		((uint32_t) 0x081BFFFF)
#define FLASH_SECTOR_22			((uint32_t) 0x081C0000) /* 128 kB */
#define FLASH_SECTOR_22_END		((uint32_t) 0x081DFFFF)
#define FLASH_SECTOR_23			((uint32_t) 0x081E0000) /* 128 kB */
#define FLASH_SECTOR_23_END		((uint32_t) 0x081FFFFF)

# endif

/*
 * System memory and One Time Programmable area are the same for all
 * SoCs
 */
#define FLASH_SECTOR_SYSTEM_MEM		((uint32_t) 0x1FFF0000) /* 30 kB */
#define FLASH_SECTOR_SYSTEM_MEM_END	((uint32_t) 0x1FFF77FF) 
#define FLASH_SECTOR_OTP_AREA		((uint32_t) 0x1FFF7800) /* 528 B */ 
#define FLASH_SECTOR_OTP_AREA_END	((uint32_t) 0x1FFF7A0F) 
#define FLASH_OPTION_BYTES		((uint32_t) 0x1FFFC000) /* 16 B */
#define FLASH_OPTION_BYTES_END		((uint32_t) 0x1FFFC00F)


#if defined(CONFIG_STM32F439) || defined(CONFIG_STM32F429)	/*  Only on f42xxx/43xxx */
	#define FLASH_OPTION_BYTES_SGL		((uint32_t) 0x1FFEC000)	/* 16 B */
	#define FLASH_OPTION_BYTES_SGL_END	((uint32_t) 0x1FFEC00F)
#endif

#define FLASH_OPTION_BYTES_BK1		((uint32_t) 0x1FFFC000) /* 16 B */
#define FLASH_OPTION_BYTES_BK1_END	((uint32_t) 0x1FFFC00F)
#define FLASH_OPTION_BYTES_BK2		((uint32_t) 0x1FFEC000)	/* 16 B */
#define FLASH_OPTION_BYTES_BK2_END	((uint32_t) 0x1FFEC00F)


/* return true if the the address is in the flash memory */
#if CONFIG_USR_DRV_FLASH_1M
# if CONFIG_USR_DRV_FLASH_DUAL_BANK
#  define IS_IN_FLASH(addr)		(addr >= FLASH_SECTOR_0) && \
					(addr <= FLASH_SECTOR_19_END)
# else
#  define IS_IN_FLASH(addr)		(addr >= FLASH_SECTOR_0) && \
					(addr <= FLASH_SECTOR_11_END)
# endif
#elif CONFIG_USR_DRV_FLASH_2M
#  define IS_IN_FLASH(addr)		(addr >= FLASH_SECTOR_0) && \
					(addr <= FLASH_SECTOR_23_END)
#else
# error "Unkown flash size!"
#endif

#define FLASH_SECTOR_SIZE(sector)  (FLASH_SECTOR_##sector##_END-FLASH_SECTOR_##sector)

/*******************  Bits definition for FLASH_ACR register  *****************/
#define FLASH_ACR_LATENCY                    ((uint32_t)0x00000007)
#define FLASH_ACR_LATENCY_0WS                ((uint32_t)0x00000000)
#define FLASH_ACR_LATENCY_1WS                ((uint32_t)0x00000001)
#define FLASH_ACR_LATENCY_2WS                ((uint32_t)0x00000002)
#define FLASH_ACR_LATENCY_3WS                ((uint32_t)0x00000003)
#define FLASH_ACR_LATENCY_4WS                ((uint32_t)0x00000004)
#define FLASH_ACR_LATENCY_5WS                ((uint32_t)0x00000005)
#define FLASH_ACR_LATENCY_6WS                ((uint32_t)0x00000006)
#define FLASH_ACR_LATENCY_7WS                ((uint32_t)0x00000007)

#define FLASH_ACR_PRFTEN                     ((uint32_t)0x00000100)
#define FLASH_ACR_ICEN                       ((uint32_t)0x00000200)
#define FLASH_ACR_DCEN                       ((uint32_t)0x00000400)
#define FLASH_ACR_ICRST                      ((uint32_t)0x00000800)
#define FLASH_ACR_DCRST                      ((uint32_t)0x00001000)
#define FLASH_ACR_BYTE0_ADDRESS              ((uint32_t)0x40023C00)
#define FLASH_ACR_BYTE2_ADDRESS              ((uint32_t)0x40023C03)

/*******************  Bits definition for FLASH_SR register  ******************/
#define FLASH_SR_EOP                         ((uint32_t)0x00000001)
#define FLASH_SR_SOP                         ((uint32_t)0x00000002)
#define FLASH_SR_WRPERR                      ((uint32_t)0x00000010)
#define FLASH_SR_PGAERR                      ((uint32_t)0x00000020)
#define FLASH_SR_PGPERR                      ((uint32_t)0x00000040)
#define FLASH_SR_PGSERR                      ((uint32_t)0x00000080)
#define FLASH_SR_BSY                         ((uint32_t)0x00010000)

/*******************  Bits definition for FLASH_CR register  ******************/
#define FLASH_CR_PG                          ((uint32_t)0x00000001)
#define FLASH_CR_SER                         ((uint32_t)0x00000002)
#define FLASH_CR_MER                         ((uint32_t)0x00000004)
#define FLASH_CR_SNB_0                       ((uint32_t)0x00000008)
#define FLASH_CR_SNB_1                       ((uint32_t)0x00000010)
#define FLASH_CR_SNB_2                       ((uint32_t)0x00000020)
#define FLASH_CR_SNB_3                       ((uint32_t)0x00000040)
#define FLASH_CR_PSIZE_0                     ((uint32_t)0x00000100)
#define FLASH_CR_PSIZE_1                     ((uint32_t)0x00000200)
#define FLASH_CR_STRT                        ((uint32_t)0x00010000)
#define FLASH_CR_EOPIE                       ((uint32_t)0x01000000)
#define FLASH_CR_LOCK                        ((uint32_t)0x80000000)

/*******************  Bits definition for FLASH_OPTCR register  ***************/
#define FLASH_OPTCR_OPTLOCK                  ((uint32_t)0x00000001)
#define FLASH_OPTCR_OPTSTRT                  ((uint32_t)0x00000002)
#define FLASH_OPTCR_BOR_LEV_0                ((uint32_t)0x00000004)
#define FLASH_OPTCR_BOR_LEV_1                ((uint32_t)0x00000008)
#define FLASH_OPTCR_BOR_LEV                  ((uint32_t)0x0000000C)
#define FLASH_OPTCR_WDG_SW                   ((uint32_t)0x00000020)
#define FLASH_OPTCR_nRST_STOP                ((uint32_t)0x00000040)
#define FLASH_OPTCR_nRST_STDBY               ((uint32_t)0x00000080)
#define FLASH_OPTCR_RDP_0                    ((uint32_t)0x00000100)
#define FLASH_OPTCR_RDP_1                    ((uint32_t)0x00000200)
#define FLASH_OPTCR_RDP_2                    ((uint32_t)0x00000400)
#define FLASH_OPTCR_RDP_3                    ((uint32_t)0x00000800)
#define FLASH_OPTCR_RDP_4                    ((uint32_t)0x00001000)
#define FLASH_OPTCR_RDP_5                    ((uint32_t)0x00002000)
#define FLASH_OPTCR_RDP_6                    ((uint32_t)0x00004000)
#define FLASH_OPTCR_RDP_7                    ((uint32_t)0x00008000)
#define FLASH_OPTCR_nWRP_0                   ((uint32_t)0x00010000)
#define FLASH_OPTCR_nWRP_1                   ((uint32_t)0x00020000)
#define FLASH_OPTCR_nWRP_2                   ((uint32_t)0x00040000)
#define FLASH_OPTCR_nWRP_3                   ((uint32_t)0x00080000)
#define FLASH_OPTCR_nWRP_4                   ((uint32_t)0x00100000)
#define FLASH_OPTCR_nWRP_5                   ((uint32_t)0x00200000)
#define FLASH_OPTCR_nWRP_6                   ((uint32_t)0x00400000)
#define FLASH_OPTCR_nWRP_7                   ((uint32_t)0x00800000)
#define FLASH_OPTCR_nWRP_8                   ((uint32_t)0x01000000)
#define FLASH_OPTCR_nWRP_9                   ((uint32_t)0x02000000)
#define FLASH_OPTCR_nWRP_10                  ((uint32_t)0x04000000)
#define FLASH_OPTCR_nWRP_11		             ((uint32_t)0x08000000)


#endif/*!FLASH_REGS_H_*/