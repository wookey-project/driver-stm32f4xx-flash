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


/*
 * flash bank identifiers. In signle bank mode (see menuconfig) only the
 * flash bank 0 is accessible. In dual bank mode, both banks are accessible
 * and configurable.
 */
typedef enum {
    FLASH_BANK_0 = 0,
    FLASH_BANK_1 = 1
} t_flash_bank_id;

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

// WTF ??? uint8_t get_active_bank(void);

/// WTF ??? void switch_active_bank(void);

void flash_copy_sector(uint32_t *dest, uint32_t *src);

int flash_device_early_init(void);

#endif /* _STM32F4XX_FLASH_H */

