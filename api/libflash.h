#ifndef _STM32F4XX_FLASH_H
#define _STM32F4XX_FLASH_H

#include "autoconf.h"
#include "api/regutils.h"

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
    SYSTEM,
    OTP,
    OPT_BANK1,
#if CONFIG_USR_DRV_LASH_DUAL_BANK
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
#ifdef CONFIG_WOOKEY
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
    bool map_system;
    bool map_otp;
    bool map_opt_bank1;
#if CONFIG_USR_DRV_LASH_DUAL_BANK
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

uint8_t flash_select_sector(uint32_t *addr);

uint8_t flash_sector_erase(uint32_t *addr);

void flash_mass_erase(void);

void flash_program_word(uint32_t *addr, uint32_t word);

void flash_program_byte(uint8_t *addr, uint8_t value);

void flash_read(uint8_t *buffer, uint32_t *addr, uint32_t size);

#if defined(USR_DRV_FLASH_DUAL_BANK)	/*  Only on f42xxx/43xxx */
uint8_t flash_get_bank_conf(void);

void flash_set_bank_conf(uint8_t conf);
#endif

void flash_copy_sector(uint32_t *dest, uint32_t *src);

int flash_device_early_init(t_device_mapping *devmap);

#endif /* _STM32F4XX_FLASH_H */

