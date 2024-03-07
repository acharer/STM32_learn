#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_key.h"

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
	while(1)
	{
		if( Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON )
			LED_G_TOGGLE;
		if( Key_Scan(KEY2_GPIO_PORT,KEY2_GPIO_PIN) == KEY_ON )
			LED_B_TOGGLE;
	}

	return 0;
}

