#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_key.h"

#define GPIOB_ODR_Addr		(GPIOB_BASE+0x0c)
#define PBout(n) 			*(unsigned int*)((GPIOB_ODR_Addr & 0xf0000000)+0x02000000+((GPIOB_ODR_Addr & 0x00ffffff)<<5)+(n<<2))

#define GPIOA_IDR_Addr		(GPIOA_BASE+0x08)
#define PAin(n) 			*(volatile unsigned int*)((GPIOA_IDR_Addr & 0xf0000000)+0x02000000+((GPIOA_IDR_Addr & 0x00ffffff)<<5)+(n<<2))
	
#define GPIOC_IDR_Addr		(GPIOC_BASE+0x08)
#define PCin(n) 			*(volatile unsigned int*)((GPIOC_IDR_Addr & 0xf0000000)+0x02000000+((GPIOC_IDR_Addr & 0x00ffffff)<<5)+(n<<2))
//这里volatile保护代码不被编译器优化，这里去掉volatile会出错，灯点不亮
void Delay(void)
{
	int i = 0,j = 0;
	for(i = 0;i < 1024;i++)
	{
		for(j = 0;j < 4096;j++)
		{
			;
		}
	}
}

int main(void)
{
	LED_GPIO_Config();
	KEY_GPIO_Config();
	LED_R(OFF);
	LED_G(OFF);
	LED_B(OFF);
	                                                                                                         
#if 0
	while(1)
	{
		PBout(0) = 0;
		Delay();
		PBout(0) = 1;
		Delay();
		PBout(1) = 0;
		Delay();
		PBout(1) = 1;
		Delay();
		PBout(5) = 2;
		Delay();
		PBout(5) = 1;
		Delay();
		
	}
#elif 1
	while(1)
	{
		if( PAin(0) == KEY_ON )
		{
			while(PAin(0) == KEY_ON)
			{
				;
			}
			LED_G_TOGGLE;
		}
		if( PCin(13) == KEY_ON )
		{
			while(PCin(13) == KEY_ON)
			{
				;
			}
			LED_B_TOGGLE;
		}
	}
	
#else 0
	while(1)
	{
		if( Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON )
			LED_G_TOGGLE;
		if( Key_Scan(KEY2_GPIO_PORT,KEY2_GPIO_PIN) == KEY_ON )
			LED_B_TOGGLE;
	}

	
#endif
	
	return 0;
}

