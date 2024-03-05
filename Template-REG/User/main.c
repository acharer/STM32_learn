#include "stm32f10x.h"


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
#else //用寄存器映射的方法操作寄存器
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