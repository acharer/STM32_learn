#include "stm32f10x.h"
#include "bsp_led.h"

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
	LED_R(OFF);
	LED_G(OFF);
	LED_B(OFF);
	while(1)
	{
		//GPIO_SetBits(LED_GPIO_PORT,LED_G_GPIO_PIN);
		LED_R(ON);
		Delay();
		//GPIO_ResetBits(LED_GPIO_PORT,LED_G_GPIO_PIN);
		LED_R(OFF);
		Delay();
		LED_G(ON);
		Delay();
		LED_G(OFF);
		Delay();
		LED_B(ON);
		Delay();
		LED_B(OFF);
		Delay();
	}

	return 0;
}

