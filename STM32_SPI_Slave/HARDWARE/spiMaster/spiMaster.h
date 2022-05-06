#ifndef  __SPIMASTER_H
#define  __SPIMASTER_H
#include "stm32f10x.h"
void spi_master_init(void);
static void spi_master_gpio_init(void);
static void spi_master_mode_init(void);
static void spi_master_cs_init(void);
void spi_master_cs_high(void);
void spi_master_cs_low(void);
uint8_t spi_master_rw_byte(uint8_t TxData); 

#endif /*__SPIMASTER_H*/

