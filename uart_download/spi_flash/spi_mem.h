/*
 * spi_mem.h
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
  FILE        : spi_mem.h
  PROJECT     : DaVinci User Boot-Loader and Flasher
  AUTHOR      : Texas Instruments Incorporated
  DESC        : Generic SPI Memory driver header file
 ----------------------------------------------------------------------------- */
 
#ifndef _SPI_MEM_H_
#define _SPI_MEM_H_

#include "tistdtypes.h"
#include "spi.h"

// Prevent C++ name mangling
#ifdef __cplusplus
extern far "c" {
#endif

/************************************************************
* Global Macro Declarations                                 *
************************************************************/

#define SPI_MAX_PAGE_SIZE   (64)


/***********************************************************
* Global Typedef declarations                              *
***********************************************************/

typedef enum _SPI_MEM_TYPE_
{
  SPI_MEM_TYPE_EEPROM       = 0x01,
  SPI_MEM_TYPE_FLASH        = 0x02,
  SPI_MEM_TYPE_ATMELFLASH   = 0x04
}
SPI_MEM_Type;

// SPI Memory device commands (Master mode)
typedef enum _SPI_MEM_COMMANDS_
{
  SPI_MEM_CMD_WREN = 0x06,
  SPI_MEM_CMD_WRDI = 0x04,
  SPI_MEM_CMD_RDSR = 0x05,
  SPI_MEM_CMD_WRSR = 0x01,
  SPI_MEM_CMD_READ = 0x03,
  SPI_MEM_CMD_WRITE = 0x02,
  SPI_MEM_CMD_FASTREAD = 0x0B,                // SPI Flash only 
  SPI_MEM_CMD_FASTREAD_DUAL_OUTPUT = 0x3B,    // SPI Flash only 
  SPI_MEM_CMD_BLOCKERASE = 0xD8,              // SPI Flash only 
  SPI_MEM_CMD_SECTORERASE = 0x20,             // SPI Flash only 
  SPI_MEM_CMD_CHIPERASE = 0xC7,               // SPI Flash only 
  SPI_MEM_CMD_POWERDOWN = 0xB9,               // SPI Flash only 
  SPI_MEM_CMD_RELEASE_POWERDOWN = 0xAB,       // SPI Flash only 
  SPI_MEM_CMD_SIMPLE_ID = 0x90,               // SPI Flash only 
  SPI_MEM_CMD_JEDEC_ID = 0x9F                 // SPI Flash only 
}
SPI_MEM_Commands;

typedef struct _SPI_MEM_CMDS_
{
  Uint8 readCmd;
  Uint8 writeCmd;
}
SPI_MEM_Cmds;

typedef struct _SPI_MEM_PARAMS_
{
  SPI_MEM_Type memType;
  Uint16 addrWidth;
  Uint16 pageSize;
  Uint32 sectorSize;
  Uint32 blockSize;
  Uint32 memorySize;
}
SPI_MEM_ParamsObj, *SPI_MEM_ParamsHandle;

// SPI driver structure
typedef struct _SPI_MEM_INFO_
{
  SPI_InfoHandle hSPIInfo;
  SPI_MEM_ParamsHandle hMemParams; 
}
SPI_MEM_InfoObj, *SPI_MEM_InfoHandle;


/************************************************************
* Global Function Declarations                              *
************************************************************/

extern __FAR__ SPI_MEM_InfoHandle SPI_MEM_open(Uint32 spiPeripheralNum, Uint32 chipSelectNum, SPI_ConfigHandle hSPICfg);
extern __FAR__ Uint32 SPI_MEM_readBytes(SPI_MEM_InfoHandle hSPIMemInfo, Uint32 addr, Uint32 byteCnt, Uint8 *dest);
extern __FAR__ Uint32 SPI_MEM_writeBytes(SPI_MEM_InfoHandle hSPIMemInfo, Uint32 addr, Uint32 byteCnt, Uint8 *src);
extern __FAR__ Uint32 SPI_MEM_verifyBytes(SPI_MEM_InfoHandle hSPIMemInfo, Uint32 addr, Uint32 byteCnt, Uint8 *src, Uint8* dest);
extern __FAR__ Uint32 SPI_MEM_globalErase(SPI_MEM_InfoHandle hSPIMemInfo);
extern __FAR__ Uint32 SPI_MEM_eraseBytes(SPI_MEM_InfoHandle hSPIMemInfo, Uint32 addr, Uint32 byteCnt);
extern __FAR__ Uint32 SPI_MEM_verifyErase(SPI_MEM_InfoHandle hSPIMemInfo, Uint32 addr, Uint32 byteCnt, Uint8* dest);


/***********************************************************
* End file                                                 *
***********************************************************/

#ifdef __cplusplus
}
#endif

#endif //_SPI_H_

