#include "delay.h"
#include "sys.h"
#include "spiSlave.h"
#include "usart.h"	


int main(void)
{	 
	uart_init(115200);
	spiSlaveInit();
	while(1)
	{
	}
}

