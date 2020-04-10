/*
 * spi.c
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
  FILE      : spi.c
  PROJECT   : TI Booting and Flashing Utilities
  AUTHOR    : Daniel Allred
  DESC      : Generic SPI driver file for common SPI peripheral
-------------------------------------------------------------------------- */

// General type include
#include "tistdtypes.h"

// Device specific CSL
#include "device.h"

// Util functions
#include "util.h"

// This module's header file 
#include "spi.h"
#include "device_spi.h"


/************************************************************
* Explicit External Declarations                            *
************************************************************/

extern Uint32 DEVICE_SPI_baseAddr[];


/************************************************************
* Local Macro Declarations                                  *
************************************************************/

#define DELAY_AFTER_CS_DN     (0)//(4700)
#define DELAY_BEFORE_CS_UP    (0)//(3800)
#define DELAY_AFTER_CS_UP     (0)//(9400)

/************************************************************
* Local Function Declarations                               *
************************************************************/

static Uint32 LOCAL_setupMode(SPI_InfoHandle hSPIInfo);

/************************************************************
* Local Variable Definitions                                *
************************************************************/


/************************************************************
* Global Variable Definitions                               *
************************************************************/

#ifdef USE_IN_ROM
SPI_InfoObj gSPIInfo;
#endif

// Default SPI Config strcuture
const SPI_ConfigObj DEFAULT_SPI_CONFIG = 
{
  1,        // polarity
  0,        // phase
  10,        // prescalar
  8         // charLen
};

SPI_ConfigHandle const hDEFAULT_SPI_CONFIG = (SPI_ConfigHandle) &DEFAULT_SPI_CONFIG;


/************************************************************
* Global Function Definitions                               *
************************************************************/

// Initialze SPI interface
SPI_InfoHandle SPI_open(Uint32 spiPeripheralNum, Uint32 spiChipSelectNum, SPI_Role role, SPI_Mode mode, SPI_ConfigHandle hSPICfg)
{
  //DEVICE_SPIRegs *SPI;
  SPI_InfoHandle hSPIInfo;
  
  // Do device level init (pinmux, power domain, etc.)
  if (DEVICE_SPIInit(spiPeripheralNum) != E_PASS)
  {
    return NULL;
  }

#ifdef USE_IN_ROM
  hSPIInfo = (SPI_InfoHandle) &gSPIInfo;
#else
  hSPIInfo = (SPI_InfoHandle) UTIL_allocMem(sizeof(SPI_InfoObj));
#endif

  // Assign the correct register base
  hSPIInfo->peripheralNum = spiPeripheralNum;
  hSPIInfo->chipSelectNum = spiChipSelectNum;
  hSPIInfo->regs = (void *) DEVICE_SPI_baseAddr[spiPeripheralNum];
  //SPI = (DEVICE_SPIRegs *) hSPIInfo->regs;
  
  // Assign mode and role
  hSPIInfo->role = role;
  hSPIInfo->mode = mode;
  
  if (hSPICfg == NULL)
  {
    hSPIInfo->hSPICfg = hDEFAULT_SPI_CONFIG;
  }
  else
  {
    hSPIInfo->hSPICfg = hSPICfg;
  }
 /*
  // Reset the SPI
  SPI_reset(hSPIInfo);

  LOCAL_setupMode(hSPIInfo);

  // Disable CS if in 3-pin mode
  SPI_disableCS(hSPIInfo);
  
  // Enable SPI
  SPI->SPIGCR1 |= ( 1 << 24 );
  */
  return hSPIInfo;
}
void SPIDeceive_open(SPI_InfoHandle hSPIInfo)
{

	 DEVICE_SPIRegs *SPI;
	 SPI = (DEVICE_SPIRegs *) hSPIInfo->regs;
	 DEVICE_SPIInit(DEVICE_SPIBOOT_PERIPHNUM);
	  SPI_reset(hSPIInfo);

	  LOCAL_setupMode(hSPIInfo);

	  // Disable CS if in 3-pin mode
	  SPI_disableCS(hSPIInfo);
	  // Enable SPI
	  SPI->SPIGCR1 |= ( 1 << 24 );
}

// Routine to reset the SPI device
Uint32 SPI_reset(SPI_InfoHandle hSPIInfo)
{
  DEVICE_SPIRegs *SPI = (DEVICE_SPIRegs *) hSPIInfo->regs;

  // Put the SPI in reset
  SPI->SPIGCR0 = 0x00;
  //UTIL_waitLoop( 1 );//1000

  // Release SPI from reset
  SPI->SPIGCR0 = 0x01;

  return E_PASS;
}

Uint32 SPI_readBytes(SPI_InfoHandle hSPIInfo, Uint32 byteCnt, Uint8 *dest)
{
  Uint32 i;

  if (hSPIInfo->hSPICfg->charLen == 16)
  {
    Uint16 *tempDest = (Uint16 *) dest;
    for (i=0; i< (byteCnt>>1); i++)
    {
      tempDest[i] = SPI_xferOneChar(hSPIInfo,0x0000);
    }
  }
  else if (hSPIInfo->hSPICfg->charLen == 8)
  {
    for (i=0; i< byteCnt; i++)
    {
      dest[i] = SPI_xferOneChar(hSPIInfo,0x00);
    }
  }

  return E_PASS;
}

Uint32 SPI_writeBytes(SPI_InfoHandle hSPIInfo, Uint32 byteCnt, Uint8 *src)
{
  Uint32 i;

  if (hSPIInfo->hSPICfg->charLen == 16)
  {
    Uint16 *tempSrc = (Uint16 *) src;
    for (i=0; i< (byteCnt>>1); i++)
    {
      SPI_xferOneChar(hSPIInfo,tempSrc[i]);
    }
  }
  else if (hSPIInfo->hSPICfg->charLen == 8)
  {
    for (i=0; i< byteCnt; i++)
    {
      SPI_xferOneChar(hSPIInfo,src[i]);
    }
  }

  return E_PASS;
}

Uint32 SPI_xferBytes(SPI_InfoHandle hSPIInfo, Uint32 numBytes, Uint8 *spiBuf )
{
  VUint32 *spiTxReg;
  Uint32  i;
  
  DEVICE_SPIRegs *SPI = (DEVICE_SPIRegs *) hSPIInfo->regs;

  spiTxReg = &(SPI->SPIDAT[DEVICE_SPI_DATOFFSET]);

  // Clear any overrun conditions
  if (SPI->SPIFLG & SPI_SPIFLG_OVRNINTFLG)
  {
    spiBuf[0] = (SPI->SPIBUF);
    SPI->SPIFLG &= SPI_SPIFLG_OVRNINTFLG;  
  }
  
  // Write output data
  for (i=0; i< numBytes; i++)
  {
    // Wait for transmit ready
    while (!(SPI->SPIFLG & SPI_SPIFLG_TXINTFLAG));  
  
    // Transmit data
    *spiTxReg = spiBuf[i];
    
    while (!(SPI->SPIFLG & SPI_SPIFLG_RXINTFLAG));
    
    spiBuf[i] = (SPI->SPIBUF);
  }

  return E_PASS;
}


Uint8 SPI_xferOneChar(SPI_InfoHandle hSPIInfo, Uint8 dataOut)
{
  DEVICE_SPIRegs *SPI = (DEVICE_SPIRegs *) hSPIInfo->regs;
  
  Uint8 *spiDat = (Uint8 *) &(SPI->SPIDAT[DEVICE_SPI_DATOFFSET]);

  // Write output data
  while (!(SPI->SPIFLG & SPI_SPIFLG_TXINTFLAG));
  
  *spiDat = dataOut;
  
  while (!(SPI->SPIFLG & SPI_SPIFLG_RXINTFLAG));
  
  return (Uint8)(SPI->SPIBUF);
  
#if (0)  

  do 
  { 
    spiflg = SPI->SPIFLG;
    if (spiflg & SPI_RXINTFLAG)
    {
      spibuf = (SPI->SPIBUF);
      break;
    }
    if (spiflg & SPI_OVRNINTFLG)
    {
      spibuf = (SPI->SPIBUF);
      SPI->SPIFLG &= SPI_OVRNINTFLG;
      continue;
    }
    if (spiflg & SPI_BITERRFLG)
    {                      
      spibuf = 0x0;
      break;
    }
  } 
  while (TRUE);

  return (spibuf & mask);
#endif  
}

void SPI_enableCS(SPI_InfoHandle hSPIInfo)
{
  DEVICE_SPIRegs *SPI = (DEVICE_SPIRegs *) hSPIInfo->regs;

  if (hSPIInfo->mode != SPI_MODE_3PIN)
    return;

  // Clear GPIO
  SPI->SPIPC5 = 0x1 << hSPIInfo->chipSelectNum;
  //UTIL_waitLoopAccurate ((Uint32)DELAY_AFTER_CS_DN);
}

void SPI_disableCS(SPI_InfoHandle hSPIInfo)
{
  DEVICE_SPIRegs *SPI = (DEVICE_SPIRegs *) hSPIInfo->regs;

  if (hSPIInfo->mode != SPI_MODE_3PIN)
    return;

  UTIL_waitLoopAccurate ((Uint32) DELAY_BEFORE_CS_UP);

  // Set GPIO
  SPI->SPIPC4 = 0x1 << hSPIInfo->chipSelectNum;

  UTIL_waitLoopAccurate ((Uint32) DELAY_AFTER_CS_UP);
}


/************************************************************
* Local Function Definitions                                *
************************************************************/

static Uint32 LOCAL_setupMode(SPI_InfoHandle hSPIInfo)
{
  DEVICE_SPIRegs *SPI = (DEVICE_SPIRegs *) hSPIInfo->regs;
  
  if (hSPIInfo->role == SPI_ROLE_MASTER)
  {
    SPI->SPIGCR1 = 0
        | ( 0 << 24 )
        | ( 0 << 16 )
        | ( 1 << 1 )
        | ( 1 << 0 );
  }
  else if (hSPIInfo->role == SPI_ROLE_SLAVE)
  {
    SPI->SPIGCR1 = 0
        | ( 0 << 24 )
        | ( 0 << 16 )
        | ( 0 << 1 )
        | ( 0 << 0 ); 
  }
  else
  {
    return E_FAIL;
  }
   
  switch (hSPIInfo->mode)
  {
    case SPI_MODE_3PIN:
      SPI->SPIPC0 =  0
        | ( 1 << 11 )   // SOMI
        | ( 1 << 10 )   // SIMO
        | ( 1 << 9 );   // SPI_CLK
      SPI->SPIPC4 |= 0x01;
      SPI->SPIPC1 |= 0x01;  // Make CS a GPIO output 
      break;
    case SPI_MODE_4PIN_CS:
      SPI->SPIPC0 =  0
        | ( 1 << 11 )   // DI
        | ( 1 << 10 )   // DO
        | ( 1 << 9 )    // CLK
        | ( 1 << 0 );   // CS0
      break;
    case SPI_MODE_4PIN_ENA:
    SPI->SPIPC0 =  0
        | ( 1 << 11 )   // DI
        | ( 1 << 10 )   // DO
        | ( 1 << 9 )    // CLK
        | ( 1 << 8 );   // ENA
      break;
    case SPI_MODE_5PIN:
      SPI->SPIPC0 =  0
        | ( 1 << 11 )   // DI
        | ( 1 << 10 )   // DO
        | ( 1 << 9 )    // CLK
        | ( 1 << 8 )    // ENA
        | ( 1 << 0 );   // CS0
      break;
    default: 
      return E_FAIL;
  }
  
  SPI->SPIFMT[0] = 0x0;
  if (hSPIInfo->hSPICfg->polarity)
    SPI->SPIFMT[0] |= ( 1 << 17 );   // Polarity
  if (hSPIInfo->hSPICfg->phase)
    SPI->SPIFMT[0] |= ( 1 << 16 );   // Phase
  SPI->SPIFMT[0] |= (hSPIInfo->hSPICfg->charLen & 0xFF);
  SPI->SPIFMT[0] |= ((hSPIInfo->hSPICfg->prescalar & 0xFF) << 8);

  // CSHOLD off, FMT[0] used  
  SPI->SPIDAT[1] = 0x00;

  // All chip selects go high when no transfer
  SPI->SPIDEF = 0xFF;

  // Disable interrupts
  SPI->SPIINT = 0x00;
  SPI->SPILVL = 0x00;
  
  return E_PASS;
}


/***********************************************************
* End file                                                 *
***********************************************************/

