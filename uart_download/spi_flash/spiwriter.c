/*
 * spiwriter.c
*/

/*
 * Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/
/* --------------------------------------------------------------------------
    FILE        : spiwriter.c
    PROJECT     : OMAP-L138 CCS SPI Flashing Utility
    AUTHOR      : Daniel Allred
    DESC        : Main function for flashing the SPI device on the OMAP-L138
 ----------------------------------------------------------------------------- */

// C standard I/O library
#include "stdio.h"

// General type include


// Device specific CSL
#include "device.h"

// Misc. utility function include
#include "util.h"

// Debug module
#include "debug.h"

// SPI memory driver include
#include "spi_mem.h"
#include "device_spi.h"
#include "string.h"
#include "spiwiter.h"
#include "uartStdio.h"


/************************************************************
* Global Function Definitions                               *
************************************************************/

static SPI_MEM_InfoHandle hSpiMemInfo;
#define BUFF_N 4096
Uint8 dest[BUFF_N];
Uint8 *pcode=(Uint8 *)0x11800000;

void spi_witer_init( void )
{
  // Init memory alloc pointer to start of external memory
  UTIL_setCurrMemPtr(0);
  // Prep device for SPI writing (pinmux/PSC)
  DEVICE_SPIInit(DEVICE_SPIBOOT_PERIPHNUM);
  // Initialize SPI Memory Device
  hSpiMemInfo = SPI_MEM_open(DEVICE_SPIBOOT_PERIPHNUM, DEVICE_SPIBOOT_CSNUM, hDEVICE_SPI_config);
  SPIDeceive_open(hSpiMemInfo->hSPIInfo);

}
int spiflash_eraseBytes(unsigned int startAddr,unsigned int byteCnt)
{
	unsigned char veriydata[1024];
	int i;
	SPI_MEM_eraseBytes(hSpiMemInfo, startAddr,byteCnt);
	for(i=0;i<byteCnt;i+=1024)
	{
		if(E_FAIL == SPI_MEM_verifyErase(hSpiMemInfo,startAddr,1024,veriydata))
			return -1;
		startAddr +=1024;
	}
	return 1;
}

static int spi_witer(Uint32 startAddr,Uint32 byteCnt)
{
	int i=0;
	Uint32 tempadd;
	Uint32 N;
	Uint32 N_left;

	N = byteCnt/BUFF_N;
	N_left = byteCnt%BUFF_N;

	//SPI_MEM_eraseBytes
	tempadd = startAddr;
	if(E_PASS!=SPI_MEM_eraseBytes(hSpiMemInfo,tempadd,byteCnt))
	{
		UARTprintf("1:SPI_MEM_eraseBytes fail\r\n");
		return -1;
	}

	//SPI_MEM_verifyErase
	tempadd = startAddr;
	for(i=0;i<N;i++)
	{
		if(E_PASS != SPI_MEM_verifyErase(hSpiMemInfo,tempadd,BUFF_N,dest))
		{
			UARTprintf("2_1:SPI_MEM_verifyErase fail\r\n");
			return -1;
		}
		tempadd +=BUFF_N;
	}
	if(E_PASS != SPI_MEM_verifyErase(hSpiMemInfo,tempadd,N_left,dest))
	{
		UARTprintf("2_2:SPI_MEM_verifyErase fail\r\n");
		return -1;
	}

	//SPI_MEM_writeBytes
	tempadd = startAddr;
	for(i=0;i<N;i++)
	{
		memcpy((void *)dest,(void*)(pcode+(tempadd-startAddr)),BUFF_N);
		if(E_PASS != SPI_MEM_writeBytes(hSpiMemInfo,tempadd,BUFF_N,dest))
		{
			UARTprintf("3_1:SPI_MEM_writeBytes fail\r\n");
			return -1;
		}
		tempadd +=BUFF_N;
	}
	memcpy((void *)dest,(void*)(pcode+(tempadd-startAddr)),N_left);
	if(E_PASS != SPI_MEM_writeBytes(hSpiMemInfo,tempadd,N_left,dest))
	{
		UARTprintf("3_2:SPI_MEM_writeBytes fail\r\n");
		return -1;
	}

	//SPI_MEM_verifyBytes
	tempadd = startAddr;
	for(i=0;i<N;i++)
	{
		if(E_PASS != SPI_MEM_verifyBytes(hSpiMemInfo,tempadd,BUFF_N,pcode+(tempadd-startAddr),dest))
		{
			UARTprintf("4_1:SPI_MEM_verifyBytes fail\r\n");
			return -1;
		}
		tempadd += BUFF_N;
	}
	if(E_PASS != SPI_MEM_verifyBytes(hSpiMemInfo,tempadd,N_left,pcode+(tempadd-startAddr),dest))
	{
		UARTprintf("4_2:SPI_MEM_verifyBytes fail\r\n");
		return -1;
	}
	return 0;
}
int spi_set_codelength(unsigned char *dest)
{

	CODE_length pcl;
	if(E_PASS!=SPI_MEM_eraseBytes(hSpiMemInfo,CODE_LENGTH_ADDR,12))
	{
		UARTprintf("spi_set_codelength:SPI_MEM_eraseBytes fail\r\n");
		return -1;
	}
	memcpy((void*)(&pcl),(void *)dest,12);
	if(E_PASS != SPI_MEM_writeBytes(hSpiMemInfo,CODE_LENGTH_ADDR,12,dest))
	{
		UARTprintf("spi_set_codelength:SPI_MEM_writeBytes fail\r\n");
		return -1;
	}
	if(E_PASS != SPI_MEM_verifyBytes(hSpiMemInfo,CODE_LENGTH_ADDR,12,(unsigned char *)&pcl,dest))
	{
		UARTprintf("spi_set_codelength:SPI_MEM_verifyBytes fail\r\n");
		return -1;
	}
	return 1;

}
int spi_get_codelength(unsigned char *dest)
{

	if(E_PASS != SPI_MEM_readBytes(hSpiMemInfo,CODE_LENGTH_ADDR,12,dest))
	{
		UARTprintf("spi_get_codelength:spi_get_codelength fail\r\n");
		return -1;
	}
	return 1;
}

void spi_witer_dspcode(Uint32 byteCnt)
{
	if(byteCnt<0x40000)
	{
		UARTprintf("spi_witer_dspcode:\r\n");
		spi_witer(DSPCODE_ADDR,byteCnt);
	}
	else
	{
		UARTprintf("fail:spi_witer_dspcode,byteCnt=%d>256K bytes\r\n",byteCnt);
	}


}
void spi_witer_arm(Uint32 byteCnt)
{
	if(byteCnt<0x20000)
	{
		UARTprintf("spi_witer_arm:\r\n");
		spi_witer(ARMCODE_ADDR,byteCnt);
	}
	else
	{
		UARTprintf("fail:spi_witer_arm,byteCnt=%d>128K bytes\r\n",byteCnt);
	}
}
void spi_witer_uboot(Uint32 byteCnt)
{
	if(byteCnt<0x8000)
	{
		UARTprintf("spi_witer_uboot:\r\n");
		if(0==spi_witer(UBOOT_ADDR,byteCnt))
		{
			UARTprintf("UP_UBOOT success,writer %d bytes\r\n",byteCnt);
		}
	}
	else
	{
		UARTprintf("fail:spi_witer_uboot,byteCnt=%d>32K bytes\r\n",byteCnt);
	}
}
void spi_witer_load(Uint32 byteCnt)
{
	if(byteCnt<0x10000)
	{
		UARTprintf("spi_witer_load:\r\n");
		spi_witer(DOWNLOAD_ADDR,byteCnt);
	}
	else
	{
		UARTprintf("fail:spi_witer_load,byteCnt=%d>64K bytes\r\n",byteCnt);
	}
}

void spi_get_data(Uint32 startAddr, Uint32 byteCnt)
{
	int i=0,j;
	Uint32 tempadd;
	Uint32 N;
	Uint32 N_left;

	N = byteCnt/BUFF_N;
	N_left = byteCnt%BUFF_N;

	//SPI_MEM_verifyBytes
	//SOF=uint8([hex2dec('48'),hex2dec('4D'),hex2dec('42'),hex2dec('A5')]);
	UARTPutc(0xab);
	UARTPutc(0xcd);
	UARTPutc(0xef);
	UARTPutc(0x48);
	UARTPutc(0x4d);
	UARTPutc(0x42);
	UARTPutc(0xA5);
	UARTPutc(0x12);
	UARTPutc(0x34);
	UARTPutc(0x56);
	tempadd = startAddr;
	for(i=0;i<N;i++)
	{
		if(E_PASS != SPI_MEM_readBytes(hSpiMemInfo,tempadd,BUFF_N,dest))
		{
			UARTprintf("spi_get_data:SPI_MEM_readBytes fail\r\n");
			return ;
		}
		for(j=0;j<BUFF_N;j++)
		{
			UARTPutc(dest[j]);
		}
		tempadd += BUFF_N;
	}
	if(E_PASS != SPI_MEM_readBytes(hSpiMemInfo,tempadd,N_left,dest))
	{
		UARTprintf("spi_get_data:SPI_MEM_readBytes fail\r\n");
		return ;
	}
	for(j=0;j<N_left;j++)
	{
		UARTPutc(dest[j]);
	}
	UARTPutc(0xab);
	UARTPutc(0xcd);
	UARTPutc(0xef);
	UARTPutc(0x48);
	UARTPutc(0x4d);
	UARTPutc(0x42);
	UARTPutc(0xA5);
	UARTPutc(0x12);
	UARTPutc(0x34);
	UARTPutc(0x56);

}


