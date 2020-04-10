/*
 * device.c
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
  FILE        : device.c                                                   
  PROJECT     : TI Boot and Flash Utils
  AUTHOR      : Daniel Allred
  DESC        : This file provides low-level init functions.
-------------------------------------------------------------------------- */ 


/************************************************************
* Include Files                                             *
************************************************************/

// General type include
#include "tistdtypes.h"

// PRU APIs
//#include "pru.h"

// This module's header file
#include "device.h"

// Execute LPSC state transition
static void DEVICE_LPSCTransition( Uint8 module, Uint8 domain, Uint8 state);
//static void DEVICE_pinmuxControl(Uint32 regOffset, Uint32 mask, Uint32 value);

/************************************************************
* Global Function Definitions                               *
************************************************************/

static void DEVICE_LPSCTransition(Uint8 module, Uint8 domain, Uint8 state)
{
  DEVICE_PSCRegs *PSC;
  PSC = PSC1;
  // Wait for any outstanding transition to complete
  while ( (PSC->PTSTAT) & (0x00000001 << domain) );
  
  // If we are already in that state, just return
  if (((PSC->MDSTAT[module]) & 0x1F) == state) return;
    
  // Perform transition
  PSC->MDCTL[module] = ((PSC->MDCTL[module]) & (0xFFFFFFE0)) | (state);
  PSC->PTCMD |= (0x00000001 << domain);

  // Wait for transition to complete
  while ( (PSC->PTSTAT) & (0x00000001 << domain) );
  
  // Wait and verify the state
  while (((PSC->MDSTAT[module]) & 0x1F) != state);
}
/*
static void DEVICE_pinmuxControl(Uint32 regOffset, Uint32 mask, Uint32 value)
{
  SYSTEM->PINMUX[regOffset] = (SYSTEM->PINMUX[regOffset] & ~mask) | (mask & value);
}
*/
// Device-level SPI initialization
Uint32 DEVICE_SPIInit(Uint8 periphNum)
{
  DEVICE_LPSCTransition(LPSC_SPI1, PD0, PSC_ENABLE);
 // DEVICE_pinmuxControl(5,0x00FF0FF0,0x00110110); // nSPI1_SCS[0], SPI1_CLK, SPI1_SIMO, SPI1_SOMI
  SYSTEM->PINMUX[5] = (SYSTEM->PINMUX[5] & ~0x00FF0FF0) | (0x00FF0FF0 & 0x00110110);
  return E_PASS;
}
/***********************************************************
* End file                                                 *
***********************************************************/

