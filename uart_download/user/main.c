/*
 * main.c
 *
 *  Created on: 2018-5-22
 *      Author: Administrator
 */
#include "..//spi_flash/spiwiter.h"
#include "uartStdio.h"
#include "cmd.h"
#include <string.h>
#include "..//xmodem/xmodem.h"

void main(void)
{

	int c_n;
	int adder,nbytes;
	unsigned char *pCode = (unsigned char *)0x11800000;
	CODE_length pcdl;
	UARTStdioInit();
	spi_witer_init();
	int bytecnts;
	memset((void*)pCode,0,0x00040000);
	gethelp();

	while(1)
	{
		c_n=getCMDlines();
		switch(c_n)
		{
			case UP_ARM:
				//bytecnts =getdownloaddata(pCode);

				bytecnts = xmodemReceive(pCode, 0x00040000);
				if (bytecnts < 0)
				{
					UARTprintf ("Xmodem receive error: status: %d\r\n", bytecnts);
				}
				else
				{
					UARTprintf ("\r\nXmodem successfully received %d bytes\r\n", bytecnts);
				}

				if(bytecnts>1024)
				{
					spi_witer_arm(bytecnts);
					if(1==spi_get_codelength((unsigned char *)&pcdl))
					{
						pcdl.arm_length = bytecnts;
						if(1==spi_set_codelength((unsigned char *)&pcdl))
						{
							UARTprintf("up_arm success,writer %d bytes\r\n",bytecnts);
						}
					}
				}
				break;
			case UP_DSP:
				//bytecnts =getdownloaddata(pCode);
				bytecnts = xmodemReceive(pCode, 0x00040000);
				if (bytecnts < 0)
				{
					UARTprintf ("Xmodem receive error: status: %d\r\n", bytecnts);
				}
				else
				{
					UARTprintf ("\r\nXmodem successfully received %d bytes\r\n", bytecnts);
				}
				if(bytecnts>1024)
				{
					spi_witer_dspcode(bytecnts);
					if(1==spi_get_codelength((unsigned char *)&pcdl))
					{
						pcdl.dsp_length = bytecnts;
						if(1==spi_set_codelength((unsigned char *)&pcdl))
						{
							UARTprintf("up_dsp success,writer %d bytes\r\n",bytecnts);
						}
					}
				}
				break;
			case UP_UBOOT:
				//bytecnts =getdownloaddata(pCode);
				bytecnts = xmodemReceive(pCode, 0x00040000);
				if (bytecnts < 0)
				{
					UARTprintf ("Xmodem receive error: status: %d\r\n", bytecnts);
				}
				else
				{
					UARTprintf ("\r\nXmodem successfully received %d bytes\r\n", bytecnts);
				}
				if(bytecnts>1024)
				{
					spi_witer_uboot(bytecnts);

				}
				break;
			case UP_LOAD:
				//bytecnts =getdownloaddata(pCode);
				bytecnts = xmodemReceive(pCode, 0x00040000);
				if (bytecnts < 0)
				{
					UARTprintf ("Xmodem receive error: status: %d\r\n", bytecnts);
				}
				else
				{
					UARTprintf ("\r\nXmodem successfully received %d bytes\r\n", bytecnts);
				}

				if(bytecnts>1024)
				{
					spi_witer_load(bytecnts);
					if(1==spi_get_codelength((unsigned char *)&pcdl))
					{
						pcdl.downlown_length = bytecnts;
						if(1==spi_set_codelength((unsigned char *)&pcdl))
						{
							UARTprintf("UP_LOAD success,writer %d bytes\r\n",bytecnts);
						}
					}
				}
				break;
			case GET_DATA:
				if(getAddr_length(&adder,&nbytes)!=-1)
				{
					spi_get_data(adder,nbytes);
				}
				break;
			case ERASE_DATA_SECTION:
				if(spiflash_eraseBytes(DATACODE_ADDR,MAX_AADR-DATACODE_ADDR))
				{

					UARTprintf("Erase flash success\r\n");
				}
				else
				{
					UARTprintf("Erase flash fail\r\n");
				}
				break;
			default:
				UARTprintf("This is bad cmd\r\n");
				gethelp();
				break;
		}

	}
}


