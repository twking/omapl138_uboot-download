/*
 * cmd.c
 *
 *  Created on: 2018-8-17
 *      Author: Administrator
 */

#include"cmd.h"
#include "string.h"
#include "uartStdio.h"
#include "uart.h"
#include "soc_OMAPL138.h"

#define UART_CONSOLE_BASE               (SOC_UART_2_REGS)

#define CMD_NUMS 6

#define CMD_MAX_LENGTH 15
char *uart0_cmd[CMD_NUMS]={"up_arm","up_dsp","up_uboot","up_load","get_data","erase_data"};
char *cmd_discp[CMD_NUMS]={"up arm code","up dsp code","up uboot code","up download code","get flash data","erase data section"};
static char uart0_CMD[CMD_MAX_LENGTH+1] = "";

int gethelp(void)
{
	int i;
	UARTprintf("***********COMMAND INSTRUCYIONS**********\r\n");
	for(i=0;i<CMD_NUMS;i++)
	{
		UARTprintf("%d:%s===>%s\r\n",i+1,uart0_cmd[i],cmd_discp[i]);
	}
	UARTprintf("*******************END*******************\r\n");
	return 1;

}
int getCMDlines(void)
{
	int retVal;
	int i;
	UARTprintf("Please put cmd \r\n");
	retVal = UARTGets(uart0_CMD,CMD_MAX_LENGTH);
	UARTprintf("\r\n");
	if(retVal>0)
	{
		for(i=0;i<CMD_NUMS;i++)
		{
			if(!strcmp((const char *)uart0_cmd[i], (const char *)uart0_CMD))
			{
				return i;
			}
		}
	}
	return -1;
}
int getdownloaddata(unsigned char *pData)
{
	int i=0,delaynums=24000000;
	int tchar;
	while(delaynums>0)
	{
		tchar=UARTCharGetNonBlocking((UART_CONSOLE_BASE));
		if(tchar!=-1)
		{
			*(pData+i) = (unsigned char)tchar;
			i++;
			delaynums = 200000;
		}
		if(delaynums>=400000&&delaynums%400000==0)
		{
			UARTprintf("remainder t=%ds\r\n",(delaynums/400000));
		}
		delaynums--;
		if(i%1024==0&&i>1)
		{
			UARTprintf("Rx %dKbytes\r\n",i/1024);
		}
	}
	if(i>1)
	{
		UARTprintf("Rx total %dbytes\r\n",i);

	}
	return i;
}
int getAddr_length(int *addr,int *nbytes)
{
	unsigned t;
next:
	UARTprintf("Please put addr \r\n");
	*addr = UARTGetNum();
	UARTprintf("\r\nPlease put nbytes \r\n");
	*nbytes = UARTGetNum();
	UARTprintf("\r\naddr=%d,nbytes=%d is yo want read flash addr or nbytes? (Y or y),or Esc(q orQ)\r\n",*addr,*nbytes);
	t=UARTGetc();
	if((t=='y')||(t=='Y'))
	{
		return 1;
	}
	else if((t=='q')||(t=='Q'))
	{
		return -1;
	}
	else
	{
		goto next;
	}
}
