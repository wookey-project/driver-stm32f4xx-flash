#ifndef _STM32F4XX_FLASH_H
#define _STM32F4XX_FLASH_H

#include "autoconf.h"
#include "libc/regutils.h"
#include "libc/types.h"


/*
 * This is the stm32f4xx sector mapping, for various STM32F4 SoCs
 */

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
#define FLASH_SECTOR_12_END		((uint32_t) 0x08103FFF)
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



/*
 * This driver is a poll-mode STM42F4xxx flash driver, managing:
 * 1MB dual and mono-bankink
 * 2MB dual-banking
 * for various STM32F4 SoC.
 */

typedef enum {
#if CONFIG_WOOKEY
    FLIP_SHR = 0,
    FLIP,
    FLOP_SHR,
    FLOP,
#else
# if CONFIG_USR_DRV_FLASH_DUAL_BANK
    BANK1,
    BANK2,
# else
    MEM,
# endif
#endif
    CTRL,
#if CONFIG_USR_DRV_FLASH_DUAL_BANK
    CTRL2,
#endif
    SYSTEM,
    OTP,
    OPT_BANK1,
#if CONFIG_USR_DRV_FLASH_DUAL_BANK
    OPT_BANK2,
#endif
} t_flash_dev_id;


/*
 * This structure is passed to the flash driver early_init function to tell
 * it which device needs to be mapped. Due to the high number of devices, all
 * of them are mapped VOLUNTARY (this required the according permission). This
 * means that you need to call sys_cfg(CFG_DEV_MAP) and sys_cfg(CFG_DEV_UNMAP)
 * when you wish to access the device.
 */
typedef struct {
#if CONFIG_WOOKEY
    bool map_flip_shr;
    bool map_flip;
    bool map_flop_shr;
    bool map_flop;
#else
# if CONFIG_USR_DRV_FLASH_DUAL_BANK
    bool map_mem_bank1;
    bool map_mem_bank2;
# else
    bool map_mem;
# endif
#endif
    bool map_ctrl;
#if CONFIG_WOOKEY
    bool map_ctrl_2;
#endif
    bool map_system;
    bool map_otp;
    bool map_opt_bank1;
#if CONFIG_USR_DRV_FLASH_DUAL_BANK
    bool map_opt_bank2;
#endif
} t_device_mapping;

/*
 * flash bank identifiers. In signle bank mode (see menuconfig) only the
 * flash bank 0 is accessible. In dual bank mode, both banks are accessible
 * and configurable.
 */
typedef enum {
    FLASH_BANK_0 = 0,
    FLASH_BANK_1 = 1
} t_flash_bank_id;

int flash_get_descriptor(t_flash_dev_id id);

/******* Flash operations **********/
void flash_unlock(void);

void flash_unlock_opt(void);

void flash_lock(void);

void flash_lock_opt(void);

uint8_t flash_select_sector(physaddr_t addr);

uint8_t flash_sector_erase(physaddr_t addr);

void flash_mass_erase(void);

void flash_program_dword(uint64_t *addr, uint64_t value);

void flash_program_word(uint32_t *addr, uint32_t word);

void flash_program_byte(uint8_t *addr, uint8_t value);

void flash_read(uint8_t *buffer, physaddr_t addr, uint32_t size);

#if defined(USR_DRV_FLASH_DUAL_BANK)	/*  Only on f42xxx/43xxx */
uint8_t flash_get_bank_conf(void);

void flash_set_bank_conf(uint8_t conf);
#endif

void flash_copy_sector(physaddr_t dest, physaddr_t src);

int flash_device_early_init(t_device_mapping *devmap);

int flash_init(void);

/* return true if the device was previously registered during early init */
bool flash_is_device_registered(t_flash_dev_id device);

uint32_t flash_sector_size(uint8_t sector);

#endif /* _STM32F4XX_FLASH_H */

