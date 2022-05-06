#include "delay.h"
#include "sys.h"
#include "spiSlave.h"
#include "usart.h"	
#include "spiMaster.h"

int main(void)
{	 
	uint8_t readValue = 0;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();
	uart_init(115200);
	spi_master_init();
	spiSlaveInit();

	while(1)
	{
		spi_master_cs_low();
		readValue = spi_master_rw_byte(0x55);
		readValue = spi_master_rw_byte(0x55);
		spi_master_cs_high();
		printf("readValue = %#x\r\n",readValue);
		printf("testValue = %#x\r\n",testValue);
		delay_ms(1000);
	}
}

