/** @file stm32f4xx_flash.c
 * \brief File includes functions to manipulate flash memory.
 *
 * See part. 3 (p73) in DocID018909 Rev 13
 */

#include "autoconf.h"
#include "api/libflash.h"
#include "api/syscall.h"
#include "api/print.h"
#include "api/regutils.h"
#include "flash_regs.h"

#define FLASH_DEBUG 1

/* Primitive for debug output */
#if FLASH_DEBUG
#define log_printf(...) printf(__VA_ARGS__)
#else
#define log_printf(...)
#endif

#ifndef assert
#define assert(val) if (!(val)) { log_printf("bkpt"); while(1){}; }; 
#endif

/* the flash device is mapped in a discretional memory layout:
 * - the flash memory
 *     -> from 0x08000000 to 0x08010000 or 0x08020000 for 2M flash
 * - the flash control register interface
 *     -> from 0x40023C00 to 0x40023FFF
 * - the flash system memory (holding the RO ST bootloader)
 *     -> from 0x1FFF000 to 0x1FFF77FF
 * - the flash One Time Programmable (OTP) region
 *     -> from 0x1FFF7800 to 0x1FFF7A0F
 * - The Bank 1 option bytes
 *     -> from 0x1FFFC000 to 1FFFC00F
 * - the Bank 2 option bytes
 *     -> from 0x1FFEC000 to 1FFEC00F
 *
 *  All these areasare not mapped continuously and request independent
 *  device mapping.
 *  As a consequence, and because it is not possible to map such a number of
 *  device, all devices are mapped VOLUNTARY, and are dynamically mapped/unmapped
 *  as needed by this driver.
 *
 *  At init time, the upper layer specify which device in the above list
 *  is requested to be declared. This permit to declare only the required one, avoiding
 *  the mapping of devices like the OTP area, which is not always needed, depending
 *  on the upper layer needs.
 *
 */
/* Register the flash device with the kernel */
int flash_device_early_init(void) {
	const char *name = "flash";
	e_syscall_ret ret = 0;	

	device_t dev = { 0 };
	int      dev_desc = 0;
	strncpy(dev.name, name, sizeof (dev.name));


	dev.map_mode = DEV_MAP_AUTO;
	dev.irq_num = 0;
	dev.gpio_num = 0;

	log_printf("registering flash driver\n");
	ret = sys_init(INIT_DEVACCESS, &dev, &dev_desc);

	printf("sys_init returns %s !\n", strerror(ret));
	if(ret != 0){
		goto err;
	}
	return 0;
err:
	return -1;
}

static inline int flash_is_busy(void){
	return !!(read_reg_value(r_CORTEX_M_FLASH_CR + FLASH_SR_BSY));
}

static inline void flash_busy_wait(void){
	while (flash_is_busy()) {};
}

/**
 * \brief Unlock the flash control register
 *
 * FIXME Check if CR bit is == RESET ?
 */
void flash_unlock(void)
{
	log_printf("Unlocking flash\n");
	write_reg_value(r_CORTEX_M_FLASH_KEYR, KEY1);
	write_reg_value(r_CORTEX_M_FLASH_KEYR, KEY2);
}

/**
 * \brief Unlock the flash option bytes register
 */
void flash_unlock_opt(void)
{
	log_printf("Unlocking flash option bytes register\n");
	write_reg_value(r_CORTEX_M_FLASH_OPTKEYR, OPTKEY1);
	write_reg_value(r_CORTEX_M_FLASH_OPTKEYR, OPTKEY2);
}

/**
 * \brief Lock the flash control register
 */
void flash_lock(void)
{
	log_printf("Locking flash\n");
	set_reg(r_CORTEX_M_FLASH_CR, 1, FLASH_CR_LOCK);	/* Write only to 1, unlock is
							 * done by the previous
							 * sequence (RM0090
							 * DocID018909
							 * Rev 13 3.9.7 p104)
							 */
}

/**
 * \brief Lock the flash option bytes register
 */
void flash_lock_opt(void)
{
	log_printf("Locking flash option bytes register\n");
	set_reg(r_CORTEX_M_FLASH_OPTCR, 1, FLASH_OPTCR_OPTLOCK); /* Same as previously */
}

/**
 * \brief Select the sector to erase
 *
 * Sector address and size size depends on the configured flash device.
 * See flash_regs.h for more information about how these macros are defined.
 *
 * \param   addr Address pointing to sector
 *
 * \return sector number to erase
 */
uint8_t flash_select_sector(uint32_t *addr)
{
	uint8_t sector = 255;
	/* First 8 sectors are the same in single/dual mem config */
	if ((uint32_t)addr <= FLASH_SECTOR_0_END) {
		sector = 0;
	}
	else if ((uint32_t)addr <= FLASH_SECTOR_1_END) {
		sector = 1;
	}
	else if ((uint32_t)addr <= FLASH_SECTOR_2_END) {
		sector = 2;
	}
	else if ((uint32_t)addr <= FLASH_SECTOR_3_END) {
		sector = 3;
	}
	else if ((uint32_t)addr <= FLASH_SECTOR_4_END) {
		sector = 4;
	}
	else if ((uint32_t)addr <= FLASH_SECTOR_5_END) {
		sector = 5;
	}
	else if ((uint32_t)addr <= FLASH_SECTOR_6_END) {
		sector = 6;
	}
	else if ((uint32_t)addr <= FLASH_SECTOR_7_END) {
		sector = 7;
	}
# if (USR_DRV_FLASH_1M && !USR_DRV_FLASH_DUAL_BANK) || USR_DRV_FLASH_2M
    /* 1MB flash in dual banking doesn't have these 4 sectors */
	else if ((uint32_t)addr <= FLASH_SECTOR_8_END) {
		sector = 8;
	}
	else if ((uint32_t)addr <= FLASH_SECTOR_9_END) {
		sector = 9;
	}
	else if ((uint32_t)addr <= FLASH_SECTOR_10_END) {
		sector = 10;
	}
	else if ((uint32_t)addr <= FLASH_SECTOR_11_END) {
		sector = 11;
	}
    /* 1MB flash in single banking finishes here */
#endif
# if (USR_DRV_FLASH_1M && USR_DRV_FLASH_DUAL_BANK) || USR_DRV_FLASH_2M
	else if ((uint32_t)addr <= FLASH_SECTOR_12_END) {
		sector = 12;
	}
	else if ((uint32_t)addr <= FLASH_SECTOR_13_END) {
		sector = 13;
	}
	else if ((uint32_t)addr <= FLASH_SECTOR_14_END) {
		sector = 14;
	}
	else if ((uint32_t)addr <= FLASH_SECTOR_15_END) {
		sector = 15;
	}
	else if ((uint32_t)addr <= FLASH_SECTOR_16_END) {
		sector = 16;
	}
	else if ((uint32_t)addr <= FLASH_SECTOR_17_END) {
		sector = 17;
	}
	else if ((uint32_t)addr <= FLASH_SECTOR_18_END) {
		sector = 18;
	}
	else if ((uint32_t)addr <= FLASH_SECTOR_19_END) {
		sector = 19;
	}
    /* 1MB flash in dual banking finishes here */
#endif
# if USR_DRV_FLASH_2M
	else if ((uint32_t)addr <= FLASH_SECTOR_20_END) {
		sector = 20;
	}
	else if ((uint32_t)addr <= FLASH_SECTOR_21_END) {
		sector = 21;
	}
	else if ((uint32_t)addr <= FLASH_SECTOR_22_END) {
		sector = 22;
	}
	else if ((uint32_t)addr <= FLASH_SECTOR_23_END) {
		sector = 23;
	}
    /* 2MB flash in dual banking finishes here */
#endif
	else {
		log_printf("Error: Wrong address case, can't happen.\n");
		while(1){};
	}
	return sector;
}




/**
 * \brief Erase a sector on the flash memory.
 *
 * @param sector Sector to erase (from 16 to 128 kB)
 * @return Erased sector number
 */
uint8_t flash_sector_erase(uint32_t *addr)
{
	uint8_t sector = 255;
	/* Check that we're looking into the flash */
	assert(IS_IN_FLASH((uint32_t)addr));

	/* Check that the BSY bit in the FLASH_SR reg is not set */
	if(flash_is_busy()){
		log_printf("Flash busy. Should not happen\n");
		while(1){};
	}

	/* Select sector to erase */
	sector = flash_select_sector(addr);
	log_printf("Erasing flash sector #%d\n", sector);

	/* Set SER bit */
	set_reg(r_CORTEX_M_FLASH_CR, 1, FLASH_CR_SER);

	/* Erase sector */
	set_reg(r_CORTEX_M_FLASH_CR, sector, FLASH_CR_SNB);

	/* Set STRT bit in FLASH_CR reg */
	set_reg(r_CORTEX_M_FLASH_CR, 1, FLASH_CR_STRT);

	/* Wait for BSY bit to be cleared */
	flash_busy_wait();

	return sector;
}

/**
 * \brief Erase a whole bank
 *
 * @param bank Bank to erase (0 bank 1, 1 bank 2)
 */
void flash_bank_erase(uint8_t bank)
{
	/* Check that the BSY bit in the FLASH_SR reg is not set */
	if(flash_is_busy()){
		log_printf("Flash busy. Should not happen\n");
		while(1){};
	}

	/* Set MER or MER1 bit accordingly */
	if (bank) {
#if !(defined(CONFIG_USR_DRV_FLASH_DUAL_BANK)) /*  Dual blank only on f42xxx/43xxx */
		log_printf("Can't acess bank 2 on a single bank memory!\n");
		while(1){};
#else
		set_reg(r_CORTEX_M_FLASH_CR, 1, FLASH_CR_MER1);
#endif
	}
	else
		set_reg(r_CORTEX_M_FLASH_CR, 1, FLASH_CR_MER);

	/* Set STRT bit in FLASH_CR reg */
	set_reg(r_CORTEX_M_FLASH_CR, 1, FLASH_CR_STRT);

	/* Wait for BSY bit to be cleared */
	flash_busy_wait();
}

/**
 * \brief Mass erase (erase the whole flash)
 */
void flash_mass_erase(void)
{
	/* Check that the BSY bit in the FLASH_SR reg is not set */
	if(flash_is_busy()){
		log_printf("Flash busy. Should not happen\n");
		while(1){};
	}

	/* Set MER and MER1 bit */
	set_reg(r_CORTEX_M_FLASH_CR, 1, FLASH_CR_MER);
#if defined(CONFIG_USR_DRV_FLASH_DUAL_BANK) /*  Dual blank only on f42xxx/43xxx */
	set_reg(r_CORTEX_M_FLASH_CR, 1, FLASH_CR_MER1);
#endif
	/* Set STRT bit in FLASH_CR reg */
	set_reg(r_CORTEX_M_FLASH_CR, 1, FLASH_CR_STRT);

	/* Wait for BSY bit to be cleared */
	flash_busy_wait();
}


/* Macro for programming factorization */
#define flash_program(addr, elem, elem_cfg) do {\
	/* Check that the BSY bit in the FLASH_SR reg is not set */\
	if (flash_is_busy()) {\
		log_printf("Flash busy. Should not happen\n");\
		while(1){};\
	}\
	/* Set PSIZE for 64 bits writing */\
	set_reg(r_CORTEX_M_FLASH_CR, (elem_cfg), FLASH_CR_PSIZE);\
	/* Set PG bit */\
	set_reg(r_CORTEX_M_FLASH_CR, 1, FLASH_CR_PG);\
	/* Perform data write op */\
	*(addr) = (elem);\
	/* Wait for BSY bit to be cleared */\
	flash_busy_wait();\
} while(0);

/**
 * \brief Write 64-bit-long data
 *
 * Program erased flash (because successive write op
 * are possible when writing '0' (from a '1')
 * As today, need an extern lock and erase. May be
 * integrated in this function in the future ?
 */
void flash_program_dword(uint64_t *addr, uint64_t value)
{
	flash_program(addr, value, 3);
}

/**
 * \brief Write 32-bit-long data
 *
 * Program erased flash (because successive write op
 * are possible when writing '0' (from a '1')
 * As today, need an extern lock and erase. May be
 * integrated in this function in the future ?
 */
void flash_program_word(uint32_t *addr, uint32_t value)
{
	flash_program(addr, value, 2);
}

/**
 * \brief Write 16-bit-long data
 *
 * Program erased flash (because successive write op
 * are possible when writing '0' (from a '1')
 * As today, need an extern lock and erase. May be
 * integrated in this function in the future ?
 */
void flash_program_hword(uint16_t *addr, uint16_t value)
{
	flash_program(addr, value, 1);
}

/**
 * \brief Write 8-bit-long data
 *
 * Program erased flash (because successive write op
 * are possible when writing '0' (from a '1')
 * As today, need an extern lock and erase. May be
 * integrated in this function in the future ?
 */
void flash_program_byte(uint8_t *addr, uint8_t value)
{
	flash_program(addr, value, 0);
}


/**
 * \brief Read from flash memory
 *
 * @param addr		Adress to read from
 * @param size		Size to read
 * @param buffer	Buffer to write in
 */
void flash_read(uint8_t *buffer, uint32_t *addr, uint32_t size)
{
	if (!IS_IN_FLASH((uint32_t)addr)) {
		log_printf("Read not authorized (not in flash memory)\n");
		while(1){};
	}
	/* Copy data into buffer */
	memcpy(buffer, addr, size);
}


#if defined(CONFIG_STM32F439) || defined(CONFIG_STM32F429)      /*  Dual blank only on f42xxx/43xxx */
/**
 * \brief Get the current used bank configuration
 *
 * Only for boards with dual bank flah memory
 *
 * @return Bank configuration which is currently used
 */
uint8_t flash_get_bank_conf(void)
{
#if CONFIG_USR_DRV_FLASH_1M
	return get_reg(r_CORTEX_M_FLASH_OPTCR, FLASH_OPTCR_DB1M) == 0 ? 0 : 1;
#else
    /* always in dual bank in 2M mode */
    return 1;
#endif
}

/**
 * \brief Set bank memory configuration between single/dual bank organization
 *
 * Only for boards with dual bank flah memory
 *
 * @param conf 0 (default) :single (12 sectors) / 1 : dual (24 sectors)
 */
void flash_set_bank_conf(uint8_t conf)
{
#if CONFIG_USR_DRV_FLASH_1M
	if (conf){
		conf = 1;
	}
	set_reg(r_CORTEX_M_FLASH_OPTCR, conf, FLASH_OPTCR_DB1M);
#endif
    /* with 2Mbytes flash mode, only dual bank mode is supported */
}
#endif

/**
 * \brief Get bank currently used
 *
 * @return 0 for bank 1, 1 for bank 2
 */
uint8_t get_active_bank(void)
{
	/* FIXME Verify cast */
	return (uint8_t)get_reg_value((volatile uint32_t *)0x08060000, 1, 0);
}

/**
 * \brief Switch bank to use
 */
void switch_active_bank(void)
{
	/* Get current bank */
	uint8_t config = get_active_bank();
	/* Switch value */
	config = config == 0 ? 1 : 0;
	/* Set new value */
	set_reg_value((volatile uint32_t *)0x08060000, config, 1, 0);
}

/**
 * \brief Return sector size in bytes
 *
 * FIXME
 *
 * @return Sector size
 */
uint32_t flash_sector_size(uint8_t sector)
{
	switch(sector){
		case 0:
			return FLASH_SECTOR_SIZE(0);
		case 1:
			return FLASH_SECTOR_SIZE(1);
		case 2:
			return FLASH_SECTOR_SIZE(2);
		case 3:
			return FLASH_SECTOR_SIZE(3);
		case 4:
			return FLASH_SECTOR_SIZE(4);
		case 5:
			return FLASH_SECTOR_SIZE(5);
		case 6:
			return FLASH_SECTOR_SIZE(6);
		case 7:
			return FLASH_SECTOR_SIZE(7);
# if (USR_DRV_FLASH_1M && !USR_DRV_FLASH_DUAL_BANK) || USR_DRV_FLASH_2M
    /* 1MB flash in dual banking doesn't have these 4 sectors */
		case 8:
			return FLASH_SECTOR_SIZE(8);
		case 9:
			return FLASH_SECTOR_SIZE(9);
		case 10:
			return FLASH_SECTOR_SIZE(10);
		case 11:
			return FLASH_SECTOR_SIZE(11);
#endif
#if (USR_DRV_FLASH_1M && USR_DRV_FLASH_DUAL_BANK) || USR_DRV_FLASH_2M
		case 12:
			return FLASH_SECTOR_SIZE(12);
		case 13:
			return FLASH_SECTOR_SIZE(13);
		case 14:
			return FLASH_SECTOR_SIZE(14);
		case 15:
			return FLASH_SECTOR_SIZE(15);
		case 16:
			return FLASH_SECTOR_SIZE(16);
		case 17:
			return FLASH_SECTOR_SIZE(17);
		case 18:
			return FLASH_SECTOR_SIZE(18);
		case 19:
			return FLASH_SECTOR_SIZE(19);
    /* 1MB flash in dual banking finishes here */
#endif
# if USR_DRV_FLASH_2M
		case 20:
			return FLASH_SECTOR_SIZE(20);
		case 21:
			return FLASH_SECTOR_SIZE(21);
		case 22:
			return FLASH_SECTOR_SIZE(22);
		case 23:
			return FLASH_SECTOR_SIZE(23);
    /*2MB flash in dual banking finishes here */
#endif
		default:
			log_printf("[Flash] Error: bad sector %d\n", sector);
			return 0;
	}
}


/* [RB] FIXME: do we really need such a complex function here?? */
/**
 * \brief Copy one flash sector into another
 *
 * FIXME Verify size of both sectors accessed !
 *
 * @param dest Destination address
 * @param src Sourcr address
 */
void flash_copy_sector(uint32_t *dest, uint32_t *src)
{
	/* Set up variables */
	uint8_t sector = 20;
	uint8_t buffer[64];
	uint32_t i = 0, j = 0, k = 0, sector_size = 0;
	if ((!IS_IN_FLASH((uint32_t)dest)) || (!IS_IN_FLASH((uint32_t)src))) {
		log_printf("Read not authorized (not in flash memory)\n");
		while(1){};
	}
	memset(buffer, 0, 64);
	/* Erase sector */
	sector = flash_sector_erase(dest);
	/* Get sector size */
	sector_size = flash_sector_size(sector);
	/* Perform copy */
	for (i = 0; i < sector_size; i++) { /* Go through each kB of the sector */
		log_printf("#%d ", i);
		for (j = 0; j < 16; j++) { /* Go through each 64B packet of each kB */
			/* Read packet to copy */
			flash_read(buffer, (uint32_t *)(src+(i<<8)+(j<<4)), 64); /* !!  sigh 32 bit addr, >>2  */
			log_printf("Buffer #%d:\n", j+i*2);
			for (k = 0; k < 64; k++)
				log_printf("%x ", buffer[k]);
			log_printf("\n");
			/* Write packet by 1B */
			for (k = 0; k < 64; k++)
				flash_program_byte((uint8_t *)(dest)+(i<<10)+(j<<6)+k, buffer[k]);
			flash_read(buffer,( uint32_t *)(dest+(i<<8)+(j<<4)), 64);
			log_printf("Dest:\n");
			for (k = 0; k < 64; k++)
				log_printf("%x ", buffer[k]);
			log_printf("\n");
		} /* j loop */
	} /* i loop */
	log_printf("End of copy\n");
}

