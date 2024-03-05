#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

#define LED_G_GPIO_PORT		GPIOB
#define LED_G_GPIO_CLK_ENABLE	RCC->APB2ENR|= ( 1 << 3 )
#define LED_G_GPIO_PIN		GPIO_Pin_0
#define LED_B_GPIO_PIN		GPIO_Pin_1
#define LED_R_GPIO_PIN		GPIO_Pin_5

//声明延时函数
void delay(void);

int main(void)
{
#if 0 //直接用地址操作寄存器
	//使能GPIOB端口的时钟
	*((unsigned int*)(0x40021018)) |= (1<<3);
	
	//配置PB0 1 5口为输出
	*((unsigned int*)(0x40010c00)) &=~((0x0f)<<(4*0));
	*((unsigned int*)(0x40010c00)) |= ((1)<<(4*0));
	*((unsigned int*)(0x40010c00)) &=~((0x0f)<<(4*1));
	*((unsigned int*)(0x40010c00)) |= ((1)<<(4*1));
	*((unsigned int*)(0x40010c00)) &=~((0x0f)<<(4*5));
	*((unsigned int*)(0x40010c00)) |= ((1)<<(4*5));
	
	//配置ODR寄存器,首先熄灭RGB,再在循环中让RGB三色依次闪烁
	*((unsigned int*)(0x40010c0c)) |= (1<<0);
	*((unsigned int*)(0x40010c0c)) |= (1<<1);
	*((unsigned int*)(0x40010c0c)) |= (1<<5);
	while(1)
	{
			*((unsigned int*)(0x40010c0c)) &=~(1<<0);
			delay();
			*((unsigned int*)(0x40010c0c)) |= (1<<0);
			delay();
			*((unsigned int*)(0x40010c0c)) &=~(1<<1);
			delay();
			*((unsigned int*)(0x40010c0c)) |= (1<<1);
			delay();
			*((unsigned int*)(0x40010c0c)) &=~(1<<5);
			delay();
			*((unsigned int*)(0x40010c0c)) |= (1<<5);
			delay();
		
	}
#elif 0 //用寄存器映射的方法操作寄存器
	//使能GPIOB端口的时钟
	RCC_APB2ENR	 |= (1<<3);
	
	//配置PB0 1 5口为输出
	GPIOB_CRL &=~((0x0f)<<(4*0));
	GPIOB_CRL |= ((1)<<(4*0));
	GPIOB_CRL &=~((0x0f)<<(4*1));
	GPIOB_CRL |= ((1)<<(4*1));
	GPIOB_CRL &=~((0x0f)<<(4*5));
	GPIOB_CRL |= ((1)<<(4*5));
	
	//配置ODR寄存器,首先熄灭RGB,再在循环中让RGB三色依次闪烁
	GPIOB_ODR |= (1<<0);
	GPIOB_ODR |= (1<<1);
	GPIOB_ODR |= (1<<5);
	while(1)
	{
			GPIOB_ODR &=~(1<<0);
			delay();
			GPIOB_ODR |= (1<<0);
			delay();
			GPIOB_ODR &=~(1<<1);
			delay();
			GPIOB_ODR |= (1<<1);
			delay();
			GPIOB_ODR &=~(1<<5);
			delay();
			GPIOB_ODR |= (1<<5);
			delay();
		
	}
#elif 0
	//使能GPIOB端口的时钟
	RCC->APB2ENR|= (1<<3);
	
	//配置PB0 1 5口为输出
	GPIOB->CRL &=~((0x0f)<<(4*0));
	GPIOB->CRL |= ((1)<<(4*0));
	GPIOB->CRL &=~((0x0f)<<(4*1));
	GPIOB->CRL |= ((1)<<(4*1));
	GPIOB->CRL &=~((0x0f)<<(4*5));
	GPIOB->CRL |= ((1)<<(4*5));
	
	//配置ODR寄存器,首先熄灭RGB,再在循环中让RGB三色依次闪烁
	GPIOB->ODR |= (1<<0);
	GPIOB->ODR |= (1<<1);
	GPIOB->ODR |= (1<<5);
	while(1)
	{
			GPIOB->ODR &=~(1<<0);
			delay();
			GPIOB->ODR |= (1<<0);
			delay();
			GPIOB->ODR &=~(1<<1);
			delay();
			GPIOB->ODR |= (1<<1);
			delay();
			GPIOB->ODR &=~(1<<5);
			delay();
			GPIOB->ODR |= (1<<5);
			delay();
		
	}
#elif 0
	//使能GPIOB端口的时钟
	RCC->APB2ENR|= (1<<3);
	
	//配置PB0 1 5口为输出
	GPIOB->CRL &=~((0x0f)<<(4*0));
	GPIOB->CRL |= ((1)<<(4*0));
	GPIOB->CRL &=~((0x0f)<<(4*1));
	GPIOB->CRL |= ((1)<<(4*1));
	GPIOB->CRL &=~((0x0f)<<(4*5));
	GPIOB->CRL |= ((1)<<(4*5));
	
	//配置ODR寄存器,首先熄灭RGB,再在循环中让RGB三色依次闪烁
	

	GPIO_SetBits(GPIOB,GPIO_Pin_0);
	GPIO_SetBits(GPIOB,GPIO_Pin_1);
	GPIO_SetBits(GPIOB,GPIO_Pin_5);
	while(1)
	{
			GPIO_ResetBits(GPIOB,GPIO_Pin_0);
			delay();
			GPIO_SetBits(GPIOB,GPIO_Pin_0);
			delay();
			GPIO_ResetBits(GPIOB,GPIO_Pin_1);
			delay();
			GPIO_SetBits(GPIOB,GPIO_Pin_1);
			delay();
			GPIO_ResetBits(GPIOB,GPIO_Pin_5);
			delay();
			GPIO_SetBits(GPIOB,GPIO_Pin_5);
			delay();
	}
#elif 1
	//使能GPIOB端口的时钟
	LED_G_GPIO_CLK_ENABLE;
	
	//配置PB0 1 5口为输出
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = LED_G_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHZ;
	GPIO_Init(LED_G_GPIO_PORT,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = LED_B_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHZ;
	GPIO_Init(LED_G_GPIO_PORT,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = LED_R_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHZ;
	GPIO_Init(LED_G_GPIO_PORT,&GPIO_InitStructure);
	
	//配置ODR寄存器,首先熄灭RGB,再在循环中让RGB三色依次闪烁
	GPIO_SetBits(LED_G_GPIO_PORT,LED_R_GPIO_PIN);
	GPIO_SetBits(LED_G_GPIO_PORT,LED_G_GPIO_PIN);
	GPIO_SetBits(LED_G_GPIO_PORT,LED_B_GPIO_PIN);
	while(1)
	{
			GPIO_ResetBits(LED_G_GPIO_PORT,LED_R_GPIO_PIN);
			delay();
			GPIO_SetBits(LED_G_GPIO_PORT,LED_R_GPIO_PIN);
			delay();
			GPIO_ResetBits(LED_G_GPIO_PORT,LED_G_GPIO_PIN);
			delay();
			GPIO_SetBits(LED_G_GPIO_PORT,LED_G_GPIO_PIN);
			delay();
			GPIO_ResetBits(LED_G_GPIO_PORT,LED_B_GPIO_PIN);
			delay();
			GPIO_SetBits(LED_G_GPIO_PORT,LED_B_GPIO_PIN);
			delay();
	}
	
#endif


	//置位 |=
	//清零 &=~
	
	return 0;
}

void SystemInit(void)
{
	//为了骗过编译器
}

//延时函数，延时1s
void delay(void)
{
	unsigned int i = 0;
	unsigned int j = 0;
	for(i = 0;i < 512;i++)
	{
		for(j = 0;j < 512;j++)
		{
			;
		}
	}
	
}