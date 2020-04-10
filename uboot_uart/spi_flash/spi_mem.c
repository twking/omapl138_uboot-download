/*
 * spi_mem.c
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
  FILE      : spi_mem.c
  PROJECT   : Catalog Boot-Loader and Flasher Utilities
  AUTHOR    : Daniel Allred
  DESC      : Generic SPI memory driver file
-------------------------------------------------------------------------- */

// General type include

// Device specific CSL
#include "device.h"
// SPI module's header file 
#include "spi.h"
// Platform/device specific SPI info
#include "device_spi.h"
// This module's header file
#include "spi_mem.h"


/************************************************************
* Explicit External Declarations                            *
************************************************************/


/************************************************************
* Local Macro Declarations                                  *
************************************************************/


/************************************************************
* Local Function Declarations                               *
************************************************************/

static Uint32 LOCAL_xferCmdAddrBytes(SPI_MEM_InfoHandle hSPIMemInfo, Uint8 command, Uint32 addr);

/************************************************************
* Local Variable Definitions                                *
************************************************************/


/************************************************************
* Global Variable Definitions                               *
************************************************************/

SPI_MEM_InfoObj     gSPIMemInfo;
SPI_MEM_ParamsObj   gSPIMemParams;

/************************************************************
* Global Function Definitions                               *
************************************************************/

// Initialze SPI memory interface
SPI_MEM_InfoHandle SPI_MEM_open(Uint32 spiPeripheralNum, Uint32 chipSelectNum, SPI_ConfigHandle hSPICfg)
{
  SPI_MEM_InfoHandle hSPIMemInfo = NULL;
  hSPIMemInfo = &gSPIMemInfo;//(SPI_MEM_InfoHandle) UTIL_allocMem(sizeof(SPI_MEM_InfoObj));
  // Open SPI peripheral
  hSPIMemInfo->hSPIInfo = SPI_open
  (
    spiPeripheralNum,
    chipSelectNum,
    SPI_ROLE_MASTER,
    SPI_MODE_3PIN,//SPI_MODE_4PIN_CS,//SPI_MODE_3PIN,
    hSPICfg
  );
	hSPIMemInfo->hMemParams = hDEVICE_SPI_MEM_params;
	SPI_disableCS(hSPIMemInfo->hSPIInfo);
	return hSPIMemInfo;
}

// Routine to read data from SPI
Uint32 SPI_MEM_readBytes(SPI_MEM_InfoHandle hSPIMemInfo, Uint32 addr, Uint32 byteCnt, Uint8 *dest)
{
  Uint32 status;

  SPI_enableCS(hSPIMemInfo->hSPIInfo);
  
  // Send command and address
  LOCAL_xferCmdAddrBytes(hSPIMemInfo, SPI_MEM_CMD_READ, addr);
  
  // Receive data bytes
  status = SPI_xferBytes(hSPIMemInfo->hSPIInfo, byteCnt, dest);
  
  SPI_disableCS(hSPIMemInfo->hSPIInfo);

  return status;
}

/************************************************************
* Local Function Definitions                                *
************************************************************/

static Uint32 LOCAL_xferCmdAddrBytes(SPI_MEM_InfoHandle hSPIMemInfo, Uint8 command, Uint32 addr)
{
  Uint8  cmdAddrBuff[4];
  Uint32 i;
  
  // Send memory write command
  cmdAddrBuff[0] = command;

  for (i=0; i<(hSPIMemInfo->hMemParams->addrWidth>>3); i++)
  {
    cmdAddrBuff[i+1] = ((addr >> (hSPIMemInfo->hMemParams->addrWidth - ((i + 1)*8))) & 0xFF);
  }
  
  return SPI_xferBytes(hSPIMemInfo->hSPIInfo, 1 + (hSPIMemInfo->hMemParams->addrWidth>>3), cmdAddrBuff);  
}

/***********************************************************
* End file                                                 *
***********************************************************/

