/*
 * main.c
 */
/*
 * main.c
 *
 *  Created on: 2018-5-22
 *      Author: Administrator
 */

#include "dev_uart.h"
#include "spi_flash/spiwiter.h"

#pragma CODE_SECTION(app_main, ".app_main");
void app_main(void){};

int main(void)
{
	unsigned char i,n=0;

	int delay_nums,t=0;
	char putchar[4]={0xe5,0x5e,0x5e,0xe5};
	CODE_length code_l;
	InitUART2(115200);
	spi_witer_init();
	gelengthCode(&code_l);
	UARTCharPut(UART_CONSOLE_BASE,'U');
	UARTCharPut(UART_CONSOLE_BASE,'B');
	while(1)
	{
		for(i=0;i<128;i++)
		{
			delay_nums = 0;
			UARTCharPut(UART_CONSOLE_BASE,0xe5);
			t =-1;
			while(0xe5!=t)
			{
				t =UARTCharGetNonBlocking(UART_CONSOLE_BASE);
				delay_nums++;
				if(delay_nums>600)//>=80
				{
					n++;
					break;
				}
			}
		}
		if(n>=120)//加载正常运行程序
		{
			geArmCode(code_l.arm_length);
			geDspCode(code_l.dsp_length);
		}
		else//加载flash烧入程序
		{
			n=0;

			i = 255;
			while(i>1)
			{
				UARTCharPut(UART_CONSOLE_BASE,putchar[n%4]);
				t = -1;
				delay_nums=0;
				while(t==-1)
				{
					t = UARTCharGetNonBlocking(UART_CONSOLE_BASE);
					delay_nums++;
					if(delay_nums>100000)
					{
						i=2;
						break;
					}
					if(t==0xe5)
					{
						break;
					}
				}
				i--;
				n++;
			}
			geDownlodCode(code_l.downlown_length);
		}
		app_main();
	}

}
