#include "spiSlave.h"
#include "usart.h"

 uint8_t testValue = 0;
void spiGpioInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/* 时钟配置 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);

	/* MISO配置为复用推挽输出 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* SCK和MOSI配置为浮空输入 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* NSS配置为浮空输入 */
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void spiModeInit(void)
{
	SPI_InitTypeDef SPI_InitStructure;

	/* 时钟配置 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);  
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Hard;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI2, &SPI_InitStructure);

	/* 打开接收中断 */
	SPI_I2S_ITConfig(SPI2, SPI_I2S_IT_RXNE, ENABLE);  //SPI_I2S_IT_TXE

	/* 打开SPI1 */
	SPI_Cmd(SPI2, ENABLE);

}

void nvicConfig(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	/* 选择中断分组2 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	/* 设置SPI1中断 */
	NVIC_InitStructure.NVIC_IRQChannel = SPI2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}


void SPI2_IRQHandler(void) 
{

	/* 接收中断 */
	if(SPI_I2S_GetITStatus(SPI2, SPI_I2S_IT_TXE) == SET)
	{  
		/* 接收到数据 */
		while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
		SPI_I2S_SendData(SPI2, 0x1f);
		SPI_I2S_ClearITPendingBit(SPI2, SPI_I2S_IT_TXE);
	}  
//	else 
	if(SPI_I2S_GetITStatus(SPI2, SPI_I2S_IT_RXNE) == SET)
	{  
		/* 接收到数据 */
		while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
		testValue = SPI_I2S_ReceiveData(SPI2);
		SPI_I2S_ClearITPendingBit(SPI2, SPI_I2S_IT_RXNE);
	}  
	
}


void spiSlaveInit(void)
{
	spiGpioInit();
	spiModeInit();
	nvicConfig();
}

