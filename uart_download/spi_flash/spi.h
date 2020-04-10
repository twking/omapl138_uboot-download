/*
 * spi.h
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
  FILE        : spi.h
  PROJECT     : DaVinci User Boot-Loader and Flasher
  AUTHOR      : Texas Instruments Incorporated
  DESC        : Generic SPI driver header file
 ----------------------------------------------------------------------------- */
 
#ifndef _SPI_H_
#define _SPI_H_

#include "tistdtypes.h"

// Prevent C++ name mangling
#ifdef __cplusplus
extern far "c" {
#endif

/************************************************************
* Global Macro Declarations                                 *
************************************************************/

#define SPI_SPIFLG_TXINTFLAG     (0x00000200u)
#define SPI_SPIFLG_RXINTFLAG     (0x00000100u)
#define SPI_SPIFLG_OVRNINTFLG    (0x00000040u)
#define SPI_SPIFLG_BITERRFLG     (0x00000010u)
#define SPI_SPIFLG_DESELECTFLG   (0x00000004u)            // SPI_PARERRFLG


/***********************************************************
* Global Typedef declarations                              *
***********************************************************/

// SPI Module Roles
typedef enum _SPI_ROLE_
{
  SPI_ROLE_MASTER = 0x01,
  SPI_ROLE_SLAVE = 0x02
}
SPI_Role;

// SPI Module Modes of Operation
typedef enum _SPI_MODE_
{
  SPI_MODE_3PIN       = 0x01,
  SPI_MODE_4PIN_CS    = 0x02,
  SPI_MODE_4PIN_ENA   = 0x04,
  SPI_MODE_5PIN       = 0x08
}
SPI_Mode;

typedef struct _SPI_CONFIG_
{
  Uint8 polarity;
  Uint8 phase;
  Uint8 prescalar;
  Uint8 charLen;
}
SPI_ConfigObj, *SPI_ConfigHandle;

// SPI driver structure
typedef struct _SPI_INFO_
{
  Uint32            peripheralNum;
  Uint32            chipSelectNum;
  void              *regs;
  SPI_Role          role;
  SPI_Mode          mode;
  SPI_ConfigHandle  hSPICfg;
}
SPI_InfoObj, *SPI_InfoHandle;

/***********************************************************
* Global Variable declarations                             *
***********************************************************/

extern __FAR__ SPI_ConfigHandle const hDEFAULT_SPI_CONFIG;


/************************************************************
* Global Function Declarations                              *
************************************************************/

extern __FAR__ SPI_InfoHandle SPI_open(Uint32 spiPeripheralNum, Uint32 spiChipSelectNum, SPI_Role role, SPI_Mode mode, SPI_ConfigHandle config);
extern __FAR__ Uint32 SPI_reset(SPI_InfoHandle hSPIInfo);
extern __FAR__ Uint32 SPI_readBytes(SPI_InfoHandle hSPIInfo, Uint32 byteCnt, Uint8 *dest);
extern __FAR__ Uint32 SPI_writeBytes(SPI_InfoHandle hSPIInfo, Uint32 byteCnt, Uint8 *src);
extern __FAR__ Uint32 SPI_xferBytes(SPI_InfoHandle hSPIInfo, Uint32 byteCnt, Uint8 *src);
extern __FAR__ Uint8  SPI_xferOneChar(SPI_InfoHandle hSPIInfo, Uint8 dataOut);
extern __FAR__ void   SPI_enableCS(SPI_InfoHandle hSPIInfo);
extern __FAR__ void   SPI_disableCS(SPI_InfoHandle hSPIInfo);
extern __FAR__ void  SPIDeceive_open(SPI_InfoHandle hSPIInfo);

/***********************************************************
* End file                                                 *
***********************************************************/

#ifdef __cplusplus
}
#endif

#endif //_SPI_H_

