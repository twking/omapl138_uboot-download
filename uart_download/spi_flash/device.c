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

// Utility functions
#include "util.h"

// PRU APIs
//#include "pru.h"

// This module's header file
#include "device.h"


/************************************************************
* Explicit External Declarations                            *
************************************************************/

extern __FAR__ Uint32 EXTERNAL_RAM_START;

#if (defined(DA850) || defined(C6746))
extern __FAR__ Uint32 PRU0_DATA_START, PRU0_DATA_SIZE;
extern __FAR__ Uint32 PRU0_INST_START, PRU0_INST_SIZE;
extern __FAR__ Uint32 PRU0_CODE_START, PRU0_CODE_SIZE;

extern __FAR__ Uint32 PRU1_DATA_START, PRU1_DATA_SIZE;
extern __FAR__ Uint32 PRU1_INST_START, PRU1_INST_SIZE;

extern __FAR__ Uint32 ARM_VECT_START,   ARM_VECT_SIZE;
#endif


/************************************************************
* Local Macro Declarations                                  *
************************************************************/


/************************************************************
* Local Typedef Declarations                                *
************************************************************/


/************************************************************
* Local Function Declarations                               *
************************************************************/


/************************************************************
* Local Variable Definitions                                *
************************************************************/


static const Uint8 LOCAL_bootModeLUT[] = 
{                                   // BOOT[7..0]
  DEVICE_BOOTMODE_I2C0_MASTER,      // 0x0000 0000
  DEVICE_BOOTMODE_I2C0_SLAVE,       // 0x0000 0001
  DEVICE_BOOTMODE_NOR_EMIFA,        // 0x0000 0010
  DEVICE_BOOTMODE_NOR_EMIFA,        // 0x0000 0011
  DEVICE_BOOTMODE_UHPI,             // 0x0000 0100
  DEVICE_BOOTMODE_UHPI,             // 0x0000 0101
  DEVICE_BOOTMODE_I2C1_MASTER,      // 0x0000 0110
  DEVICE_BOOTMODE_I2C1_SLAVE,       // 0x0000 0111
  DEVICE_BOOTMODE_SPI0_EEPROM,      // 0x0000 1000
  DEVICE_BOOTMODE_SPI1_EEPROM,      // 0x0000 1001
  DEVICE_BOOTMODE_SPI0_FLASH,       // 0x0000 1010
  DEVICE_BOOTMODE_SPI0_FLASH,       // 0x0000 1011
  DEVICE_BOOTMODE_SPI1_FLASH,       // 0x0000 1100
  DEVICE_BOOTMODE_SPI1_FLASH,       // 0x0000 1101
  DEVICE_BOOTMODE_NAND_EMIFA_8BIT,  // 0x0000 1110 
  DEVICE_BOOTMODE_NAND_EMIFA_8BIT,  // 0x0000 1111
  DEVICE_BOOTMODE_NAND_EMIFA_16BIT, // 0x0001 0000
  DEVICE_BOOTMODE_NONE,             // 0x0001 0001
  DEVICE_BOOTMODE_SPI0_SLAVE,       // 0x0001 0010
  DEVICE_BOOTMODE_SPI1_SLAVE,       // 0x0001 0011
  DEVICE_BOOTMODE_UART2,            // 0x0001 0100
  DEVICE_BOOTMODE_THB,              // 0x0001 0101
  DEVICE_BOOTMODE_UART0,            // 0x0001 0110
  DEVICE_BOOTMODE_UART1,            // 0x0001 0111
  DEVICE_BOOTMODE_ESF,              // 0x0001 1000
  DEVICE_BOOTMODE_ESF,              // 0x0001 1001
  DEVICE_BOOTMODE_USB11,            // 0x0001 1010
  DEVICE_BOOTMODE_USB20,            // 0x0001 1011
  DEVICE_BOOTMODE_SDMMC0,           // 0x0001 1100
  DEVICE_BOOTMODE_SDMMC1,           // 0x0001 1101
  DEVICE_BOOTMODE_EMU_DEBUG,        // 0x0001 1110
  DEVICE_BOOTMODE_NONE,             // 0x0001 1111
};


/************************************************************
* Global Variable Definitions                               *
************************************************************/

#if defined(OMAPL138)
  const char devString[] = "OMAP-L138";
#elif defined(OMAPL138_LCDK)
  const char devString[] = "OMAP-L138 LCDK";
#elif defined(AM1808)
  const char devString[] = "AM1808";
#elif defined(AM1810)
  const char devString[] = "AM1810";  
#elif defined(C6748)
  const char devString[] = "C6748";
#elif defined(C6748_LCDK)
  const char devString[] = "C6748 LCDK";
#elif defined(C6746)  
  const char devString[] = "C6746";
#else
  const char devString[] = "OMAP-L138";
#endif  

//DEVICE_OperatingPoint gDeviceOpPoint;


/************************************************************
* Global Function Definitions                               *
************************************************************/

Uint32 DEVICE_init()
{
  Uint32 status = E_PASS;
  
  // Ensure the kick registers are unlocked 
  // Note these lines have no effect on 2.0 and later silicon
  DEVICE_kickLock();
  DEVICE_kickUnlock();
  
  SYSTEM->SUSPSRC &= ( (1 << 27) | (1 << 22) | (1 << 20) | (1 << 5) | (1 << 16));

#ifndef SKIP_LOW_LEVEL_INIT
  // System PSC Setup
  DEVICE_PSCInit();

  // System PLL Setup
  if (status == E_PASS)
  {
  #if defined(AM1808)
    // CPU(s) at 456 MHz
    status |= DEVICE_PLL0Init(0, 18, 0, 0, 0, 18, 8);
  #else
    // CPU(s) at 300 MHz
    status |= DEVICE_PLL0Init(0, 24, 0, 1, 0, 11, 5);
  #endif  
  }
  
  if (status == E_PASS)
  {
    // mDDR @ 150MHz
    status |= DEVICE_PLL1Init(24, 1, 0, 1, 2);
  }
  
  // External Memory Timing Setup
  if (status == E_PASS)
  {
	#if defined(AM1810)
      // Timings for DDR2 at 150 MHz
      status |= DEVICE_ExternalMemInit(0x00000047, 0x08934832, 0x204929C9, 0x0C12C722, 0x00000406, 0x00000000);
    #elif defined(OMAPL138_LCDK)
      // Timings for DDR2 at 150 MHz
      status |= DEVICE_ExternalMemInit(0x000000C5, 0x00134832, 0x264A3209, 0x3C14C722, 0x00000492, 0x00000000);
	#elif defined(C6748_LCDK)
      // Timings for DDR2 at 150 MHz
      status |= DEVICE_ExternalMemInit(0x000000C5, 0x00134832, 0x264A3209, 0x3C14C722, 0x00000492, 0x00000000);
    #else
      // Timings for mDDR at 150 MHz
      status |= DEVICE_ExternalMemInit(0x000000C4, 0x0A034622, 0x1C912A08, 0x3811C700, 0x00000494, 0x00000000);
	#endif
  }
#endif

#if (defined(DA850) || defined(C6746))
  LOCAL_initARMVectors((Uint32 *) &(LOCAL_arm_idle_vectors[0]));

  LOCAL_wakeUpARM();
  
  while(1);
#endif

  return status;
}

DEVICE_ChipRevIDType DEVICE_chipRevIDType( )
{
  // The code used by the actual ROM boot loader
  Uint32 chipType = (SYSTEM->CHIPREVID & DEVICE_CHIPREVID_TYPE_MASK) >> DEVICE_CHIPREVID_TYPE_SHIFT;
  return ((DEVICE_ChipRevIDType)chipType);
}

void DEVICE_LPSCTransition(Uint8 pscnum, Uint8 module, Uint8 domain, Uint8 state)
{
  DEVICE_PSCRegs *PSC;
  
  if (pscnum == PSCNUM0)
    PSC = PSC0;
  else if(pscnum == PSCNUM1)
    PSC = PSC1;
  else
    return; 

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

void DEVICE_pinmuxControl(Uint32 regOffset, Uint32 mask, Uint32 value)
{
  SYSTEM->PINMUX[regOffset] = (SYSTEM->PINMUX[regOffset] & ~mask) | (mask & value);
}

void DEVICE_PSCInit()
{                                                                    
  Uint32 i;
  
  // PSC0, domain 0 init
  while ((PSC0->PTSTAT) & 0x00000001);

  // LPSC_EDMA_CC0 through LPSC_ARM_RAMROM
  for( i = 0 ; i <= 7 ; i++ )
    PSC0->MDCTL[i] = (PSC0->MDCTL[i] & 0xFFFFFFE0) | PSC_ENABLE;

  // LPSC_UART0 through LPSC_SCR2
  for( i = 9 ; i <= 12 ; i++ )
    PSC0->MDCTL[i] = (PSC0->MDCTL[i] & 0xFFFFFFE0) | PSC_ENABLE;
    
  // Do Always-On Power Domain Transitions
  PSC0->PTCMD |= 0x00000001;
  while ((PSC0->PTSTAT) & 0x00000001);
  
  // PSC1, domain 1 init
  while ((PSC1->PTSTAT) & 0x00000001);

  // LPSC_EDMA_CC1 through LPSC_EDMA_CC1
  for( i = 0 ; i <= 0 ; i++ )
    PSC1->MDCTL[i] = (PSC1->MDCTL[i] & 0xFFFFFFE0) | PSC_ENABLE;
  
  // LPSC_GPIO through LPSC_EMAC
  for( i = 3 ; i <= 7 ; i++ )
    PSC1->MDCTL[i] = (PSC1->MDCTL[i] & 0xFFFFFFE0) | PSC_ENABLE;

  // LPSC_VPIF through LPSC_TPTC2
  for( i = 9 ; i <= 21 ; i++ )
    PSC1->MDCTL[i] = (PSC1->MDCTL[i] & 0xFFFFFFE0) | PSC_ENABLE;
  
  // LPSC_L3CBA through LPSC_L3CBA
  for( i = 31 ; i <= 31 ; i++ )
    PSC1->MDCTL[i] = (PSC1->MDCTL[i] & 0xFFFFFFE0) | PSC_ENABLE;
    
  // Do Always-On Power Domain Transitions
  PSC1->PTCMD |= 0x00000001;
  while ((PSC1->PTSTAT) & 0x00000001);
}

void DEVICE_kickUnlock(void)
{
  SYSTEM->KICKR[0] = 0x83e70b13;  // Kick0 register + data (unlock)
  SYSTEM->KICKR[1] = 0x95a4f1e0;  // Kick1 register + data (unlock)
}

void DEVICE_kickLock( void )
{
  SYSTEM->KICKR[0] = 0x00000000;  // Kick0 register + data (lock)
  SYSTEM->KICKR[1] = 0x00000000;  // Kick0 register + data (lock)
}

DEVICE_BootPeripheral DEVICE_bootPeripheral( void )
{
  DEVICE_BootPeripheral bp;
  DEVICE_BootMode bm = DEVICE_bootMode();
  switch (bm)
  {
    case DEVICE_BOOTMODE_SPI0_EEPROM:
    case DEVICE_BOOTMODE_SPI1_EEPROM:
    case DEVICE_BOOTMODE_SPI0_FLASH:
    case DEVICE_BOOTMODE_SPI1_FLASH:
      bp = DEVICE_BOOTPERIPHERAL_SPI;
      break;
    case DEVICE_BOOTMODE_I2C0_MASTER:
    case DEVICE_BOOTMODE_I2C0_SLAVE:
    case DEVICE_BOOTMODE_I2C1_MASTER:
    case DEVICE_BOOTMODE_I2C1_SLAVE: 
      bp = DEVICE_BOOTPERIPHERAL_I2C;
      break;
    case DEVICE_BOOTMODE_NAND_EMIFA_8BIT:
    case DEVICE_BOOTMODE_NAND_EMIFA_16BIT:
      bp = DEVICE_BOOTPERIPHERAL_NAND;
      break;
    case DEVICE_BOOTMODE_UART0:
    case DEVICE_BOOTMODE_UART1:
    case DEVICE_BOOTMODE_UART2:
      bp = DEVICE_BOOTPERIPHERAL_UART;
      break;
    case DEVICE_BOOTMODE_NOR_EMIFA:
      bp = DEVICE_BOOTPERIPHERAL_NOR;
      break;
    case DEVICE_BOOTMODE_SDMMC0:
    case DEVICE_BOOTMODE_SDMMC1:
      bp = DEVICE_BOOTPERIPHERAL_SDMMC;
      break;
    default:
      bp = DEVICE_BOOTPERIPHERAL_NONE;
      break;
  }
  
  return bp;
}

DEVICE_BootMode DEVICE_bootMode( void )
{
  Uint8 i;

  // Read BOOT pins and set bootMode using a look-up table
  i = (SYSTEM->BOOTCFG & DEVICE_BOOTCFG_BOOTMODE_MASK) >> DEVICE_BOOTCFG_BOOTMODE_SHIFT;

  // Bit sequence used for LUT is 4,3,2,1,0
  i &= 0x1F;

  return ((DEVICE_BootMode)LOCAL_bootModeLUT[i]);
}

DEVICE_BusWidth DEVICE_emifBusWidth( void )
{
  if (DEVICE_bootMode() == DEVICE_BOOTMODE_NAND_EMIFA_8BIT)
  {
    return DEVICE_BUSWIDTH_8BIT;
  }
  else
  {
    return DEVICE_BUSWIDTH_16BIT;
  }
}


Uint32 DEVICE_PLL0Init(Uint8 clk_src, Uint8 pllm, Uint8 prediv, Uint8 postdiv, Uint8 div1 ,Uint8 div3, Uint8 div7)
{
  // Note:  PLL0_SYSCLK1 - Not used on Freon subchip, fixed divider (/1) - allow to change div1 
  //        PLL0_SYSCLK2 - Used on Freon subchip, but it has a fixed divider ratio to SYSCLK1(/2) - should be used for sc ASYNC3 domain 
  //                       to simplify clock management for peripherals during the ROM boot loader CFGCHIP3[ASYNC3_CLKSRC] - configure with div1
  //        PLL0_SYSCLK3 - Variable Divider, not used on Freon subchip, but ASYNC1 (EMIFA) on matrix - treat same as in Primus (configure)
  //        PLL0_SYSCLK4 - Used on Freon subchip, but it has a fixed ratio to div1 (/4) - configure with div1
  //        PLL0_SYSCLK5 - Variable divider, not used on Freon subchip - do nothing
  //        PLL0_SYSCLK6 - Not used on Freon subchip, fixed ratio to div1 (/1) - configure with div1
  //        PLL0_SYSCLK7 - Variable divider, is used on Freon subchip (Test, RMII, possibly USB 1.1) - treat the same as on Primus (configure)
  //        PLL0_SYSCLK8 - Variable divider, not used on Freon subchip - treat same as in Primus (do nothing)
  //        PLL0_SYSCLK9 - Variable divider, used on Freon subchip (test) - treat same as in Primus (do nothing)
  //        DIV4p5CLOCK  - Not used on Freon, can be used in in EMIFA on matrix - treat same as in Primus - configure in EMIF setups, not here
  
  // Clear PLL lock bit
  SYSTEM->CFGCHIP[0] &= ~(DEVICE_CFGCHIP0_PLL0MASTERLOCK_MASK);
  
  // Set PLLENSRC '0',bit 5, PLL Enable(PLLEN) selection is controlled through MMR
  PLL0->PLLCTL &= ~DEVICE_PLLCTL_PLLENSRC_MASK;

  // PLLCTL.EXTCLKSRC bit 9 should be left at 0 for Freon
  PLL0->PLLCTL &= ~DEVICE_PLLCTL_EXTCLKSRC_MASK;

  // Set PLLEN=0 to put in bypass mode
  PLL0->PLLCTL &= ~DEVICE_PLLCTL_PLLEN_MASK;

  // Wait for 4 cycles to allow PLLEN mux switches properly to bypass clock
  UTIL_waitLoopAccurate (4);

  // Select the Clock Mode bit 8 as External Clock or On Chip Oscilator
  PLL0->PLLCTL &= 0xFFFFFEFF;
  PLL0->PLLCTL |= (clk_src << 8);

  // Clear PLLRST bit to reset the PLL
  PLL0->PLLCTL &= ~DEVICE_PLLCTL_PLLRST_MASK;

  // Disable the PLL output
  PLL0->PLLCTL |= DEVICE_PLLCTL_PLLDIS_MASK;

  // PLL initialization sequence
  // Power up the PLL by setting PWRDN bit set to 0
  PLL0->PLLCTL &= ~DEVICE_PLLCTL_PLLPWRDN_MASK;

  // Enable the PLL output
  PLL0->PLLCTL &= ~DEVICE_PLLCTL_PLLDIS_MASK;

  // FIXME - how long?: Wait for the PLLs to stabilize - see PLL spec/datasheet
  UTIL_waitLoopAccurate (2000);

  // Program the required multiplier value in PLLM
  PLL0->PLLM = pllm;

  // Prediv setup
  PLL0->PREDIV = DEVICE_PLLDIV_EN_MASK | prediv;

  // If desired to scale all the SYSCLK frequencies of a given PLLC, program the POSTDIV ratio
  PLL0->POSTDIV = DEVICE_PLLDIV_EN_MASK | postdiv;

  // Check for the GOSTAT bit in PLLSTAT to clear to 0 to indicate that no GO operation is currently in progress
  while (PLL0->PLLSTAT & DEVICE_PLLSTAT_GOSTAT_MASK);

  // Program the RATIO field in PLLDIVx with the desired divide factors. In addition, make sure in this step you leave the PLLDIVx.DxEN bits set so clocks are still enabled (default).
  PLL0->PLLDIV1 = DEVICE_PLLDIV_EN_MASK | div1;
  PLL0->PLLDIV2 = DEVICE_PLLDIV_EN_MASK | (((div1+1)*2)-1);
  PLL0->PLLDIV4 = DEVICE_PLLDIV_EN_MASK | (((div1+1)*4)-1);
  PLL0->PLLDIV6 = DEVICE_PLLDIV_EN_MASK | div1;
  PLL0->PLLDIV3 = DEVICE_PLLDIV_EN_MASK | div3;
  PLL0->PLLDIV7 = DEVICE_PLLDIV_EN_MASK | div7;

  // Set the GOSET bit in PLLCMD to 1 to initiate a new divider transition
  PLL0->PLLCMD |= DEVICE_PLLCMD_GOSET_MASK;

  // Wait for the GOSTAT bit in PLLSTAT to clear to 0 (completion of phase alignment)
  while (PLL0->PLLSTAT & DEVICE_PLLSTAT_GOSTAT_MASK);

  // FIXME: how long? Wait for PLL to reset - see PLL spec/datasheet
  UTIL_waitLoopAccurate (200);

  // Set the PLLRST bit in PLLCTL to 1 to bring the PLL out of reset
  PLL0->PLLCTL |= DEVICE_PLLCTL_PLLRST_MASK;

  // Wait for PLL to lock. See PLL spec for PLL lock time
  UTIL_waitLoopAccurate (2000);

  // Set the PLLEN bit in PLLCTL to 1 to remove the PLL from bypass mode
  PLL0->PLLCTL |= DEVICE_PLLCTL_PLLEN_MASK;

  // SET PLL lock bit
  SYSTEM->CFGCHIP[0] |= (0x1 << DEVICE_CFGCHIP0_PLL0MASTERLOCK_SHIFT) & DEVICE_CFGCHIP0_PLL0MASTERLOCK_MASK;

  return E_PASS;
}

Uint32 DEVICE_PLL1Init( Uint8 pllm, Uint8 postdiv, Uint8 div1, Uint8 div2, Uint8 div3 )
{ 
  // Clear PLL lock bit
  SYSTEM->CFGCHIP[3] &= ~(DEVICE_CFGCHIP3_PLL1MASTERLOCK_MASK);

  // Set PLLENSRC '0',bit 5, PLL Enable(PLLEN) selection is controlled through MMR
  PLL1->PLLCTL &= ~DEVICE_PLLCTL_PLLENSRC_MASK;

  // PLLCTL.EXTCLKSRC bit 9 should be left at 0 for Freon
  PLL1->PLLCTL &= ~DEVICE_PLLCTL_EXTCLKSRC_MASK;

  // Set PLLEN=0 to put in bypass mode
  PLL1->PLLCTL &= ~DEVICE_PLLCTL_PLLEN_MASK;

  // wait for 4 cycles to allow PLLEN mux switches properly to bypass clock
  UTIL_waitLoopAccurate (4);

  // Clear PLLRST bit to reset the PLL
  PLL1->PLLCTL &= ~DEVICE_PLLCTL_PLLRST_MASK;

  // Disable the PLL output
  PLL1->PLLCTL |= DEVICE_PLLCTL_PLLDIS_MASK;

  // PLL initialization sequence
  // Power up the PLL by setting PWRDN bit set to 0
  PLL1->PLLCTL &= ~DEVICE_PLLCTL_PLLPWRDN_MASK;

  // Enable the PLL output
  PLL1->PLLCTL &= ~DEVICE_PLLCTL_PLLDIS_MASK;

  // FIXME - how long?: Wait for the PLLs to stabilize - see PLL spec/datasheet
  UTIL_waitLoopAccurate (2000);

  // Program the required multiplier value in PLLM
  PLL1->PLLM = pllm;

  // If desired to scale all the SYSCLK frequencies of a given PLLC, program the POSTDIV ratio
  PLL1->POSTDIV = DEVICE_PLLDIV_EN_MASK | postdiv;

  // Check for the GOSTAT bit in PLLSTAT to clear to 0 to indicate that no GO operation is currently in progress
  while (PLL1->PLLSTAT & DEVICE_PLLSTAT_GOSTAT_MASK);

  // Program the RATIO field in PLLDIVx with the desired divide factors
  PLL1->PLLDIV1 = DEVICE_PLLDIV_EN_MASK | div1;
  PLL1->PLLDIV2 = DEVICE_PLLDIV_EN_MASK | div2;
  PLL1->PLLDIV3 = DEVICE_PLLDIV_EN_MASK | div3;

  // Set the GOSET bit in PLLCMD to 1 to initiate a new divider transition
  PLL1->PLLCMD |= DEVICE_PLLCMD_GOSET_MASK;

  // Wait for the GOSTAT bit in PLLSTAT to clear to 0 (completion of phase alignment)
  while (PLL1->PLLSTAT & DEVICE_PLLSTAT_GOSTAT_MASK);

  // FIXME: how long? Wait for PLL to reset - see PLL spec/datasheet
  UTIL_waitLoopAccurate (200);

  // Set the PLLRST bit in PLLCTL to 1 to bring the PLL out of reset
  PLL1->PLLCTL |= DEVICE_PLLCTL_PLLRST_MASK;

  // Wait for PLL to lock. See PLL spec for PLL lock time
  UTIL_waitLoopAccurate (2000);

  // Set the PLLEN bit in PLLCTL to 1 to remove the PLL from bypass mode
  PLL1->PLLCTL |= DEVICE_PLLCTL_PLLEN_MASK;

  // SET PLL lock bit
  SYSTEM->CFGCHIP[3] |= (0x1 << DEVICE_CFGCHIP3_PLL1MASTERLOCK_SHIFT) & DEVICE_CFGCHIP3_PLL1MASTERLOCK_MASK;

  return E_PASS;
}

Uint32 DEVICE_ExternalMemInit(Uint32 ddrphycr, Uint32 sdcr, Uint32 sdtimr, Uint32 sdtimr2, Uint32 sdrcr, Uint32 sdcr2)
{
  VUint32 data_tmp;
  VUint32 *DDRStart = (VUint32 *) &EXTERNAL_RAM_START;

  // Set the DDR2 to enable                                          
  DEVICE_LPSCTransition(PSCNUM1, LPSC_EMIFB, PD0, PSC_ENABLE);

  if (SUBCHIPCFG->VTPIO_CTL & 0x00000040)
  {
    // Begin VTP Calibration
    SUBCHIPCFG->VTPIO_CTL |= DEVICE_VTPIO_CTL_IOPWRDN_MASK;     // Set IOPWRDN bit to enable input buffer powerdown enable mode
    SUBCHIPCFG->VTPIO_CTL &= ~(DEVICE_VTPIO_CTL_POWERDN_MASK);  // Clear POWERDN bit (enable VTP)

    // Pulse (low) CLRZ to initiate VTP IO Calibration
    SUBCHIPCFG->VTPIO_CTL |= DEVICE_VTPIO_CTL_CLKRZ_MASK;       // Set CLRZ bit 
    SUBCHIPCFG->VTPIO_CTL &= ~(DEVICE_VTPIO_CTL_CLKRZ_MASK);    // Clear CLRZ bit (CLRZ should be low for at least 2ns)
    SUBCHIPCFG->VTPIO_CTL |= DEVICE_VTPIO_CTL_CLKRZ_MASK;       // Set CLRZ bit 

    // Polling READY bit to see when VTP calibration is done
    while(!((SUBCHIPCFG->VTPIO_CTL & DEVICE_VTPIO_CTL_READY_MASK)>>DEVICE_VTPIO_CTL_READY_SHIFT)); 

    SUBCHIPCFG->VTPIO_CTL |= DEVICE_VTPIO_CTL_LOCK_MASK;        // Set LOCK bit for static mode
    SUBCHIPCFG->VTPIO_CTL |= DEVICE_VTPIO_CTL_PWRSAVE_MASK;     // Set PWRSAVE bit to save power              
    // End VTP Calibration
  }

  // Config DDR timings
  EMIF3A->DDRPHYC1R   = ddrphycr;

  // Clear the unlock bits (in case user accidentally set them)
  sdcr = sdcr & (~DEVICE_SDCR_BOOTUNLOCK_MASK) & (~DEVICE_SDCR_TIMUNLOCK_MASK);
  
  // Set SDCR with BOOTUNLOCK Set and TIMUNLOCK cleared
  EMIF3A->SDCR        = sdcr | ((0x1 << DEVICE_SDCR_BOOTUNLOCK_SHIFT) & DEVICE_SDCR_BOOTUNLOCK_MASK);
  // Set SDCR with BOOTUNLOCK cleared and TIMUNLOCK set
  EMIF3A->SDCR        = sdcr | ((0x1 << DEVICE_SDCR_TIMUNLOCK_SHIFT) & DEVICE_SDCR_TIMUNLOCK_MASK);
  
  // Check if this init is for mDDR
  if (sdcr & DEVICE_SDCR_MSDRAMEN_MASK)
  {
    // If it is, set SDCR2 with PASR and ROWSIZE PARAMS
    EMIF3A->SDCR2     = sdcr2;
  }
                        
  EMIF3A->SDTIMR      = sdtimr;
  EMIF3A->SDTIMR2     = sdtimr2;

  // Clear TIMUNLOCK bit
  EMIF3A->SDCR        &= (~DEVICE_SDCR_TIMUNLOCK_MASK); 
  EMIF3A->SDRCR       = sdrcr;

  // Set the DDR2 to syncreset
  EMIF3A->SDRCR |= 0xC0000000;  // Set to self-refresh, enable mclkstop
  DEVICE_LPSCTransition(PSCNUM1, LPSC_EMIFB, PD0, PSC_SYNCRESET);

  // Set the DDR2 to enable
  DEVICE_LPSCTransition(PSCNUM1, LPSC_EMIFB, PD0, PSC_ENABLE);
  EMIF3A->SDRCR &= ~(0xC0000000);  // disable self-refresh

  // Dummy write/read to apply timing settings
  *DDRStart = 0xA55AA55A;               // write
  data_tmp = *DDRStart;                 // read
  *DDRStart = data_tmp;

  return E_PASS;                                                              
}

Uint32 DEVICE_AsyncMemInit (Uint8 interfaceNum)
{
  if (interfaceNum == 0)
  {
    // Turn on the EMIF LPSC
    DEVICE_LPSCTransition(PSCNUM0, LPSC_EMIFA, PD0, PSC_ENABLE);

    // Set PINMUX for EMIF use
    DEVICE_pinmuxControl(5 ,0xFF000000,0x11000000); // EMA_BA[1],EMA_BA[0]
    DEVICE_pinmuxControl(7 ,0xF0FFFFFF,0x00111111); // EMA_WAIT[0], nEMA_WE, nEMA_OE, nEMA_CS[2], nEMA_CS[3], nEMA_CS[4], nEMA_CS[5]
    DEVICE_pinmuxControl(8 ,0xFFFFFFFF,0x11111111); // EMA_D[15:8]
    DEVICE_pinmuxControl(9 ,0xFFFFFFFF,0x11111111); // EMA_D[7:0]
    DEVICE_pinmuxControl(10,0xFFFFFFFF,0x11111111); // EMA_A[23..16]
    DEVICE_pinmuxControl(11,0xFFFFFFFF,0x11111111); // EMA_A[15..8]
    DEVICE_pinmuxControl(12,0xFFFFFFFF,0x11111111); // EMA_A[7..0]

  }
  else
  {
    return E_FAIL;
  }

  return E_PASS;
}

// Device-level SPI initialization
Uint32 DEVICE_SPIInit(Uint8 periphNum)
{
  if (periphNum >= SPI_PERIPHERAL_CNT)
  {
    return E_FAIL;
  }

  switch (periphNum)
  {
    case 0:
      DEVICE_LPSCTransition(PSCNUM0, LPSC_SPI0, PD0, PSC_ENABLE);
      DEVICE_pinmuxControl(3,0x0000FF0F,0x00001101); // SPI0_CLK, SPI0_SIMO, SPI0_SOMI
      DEVICE_pinmuxControl(4,0x000000F0,0x00000010); // nSPI0_SCS[0]
      break;
    case 1:
      DEVICE_LPSCTransition(PSCNUM1, LPSC_SPI1, PD0, PSC_ENABLE);
      DEVICE_pinmuxControl(5,0x00FF0FF0,0x00110110); // nSPI1_SCS[0], SPI1_CLK, SPI1_SIMO, SPI1_SOMI
      break;
    default:
      return E_FAIL;
  }
  
  return E_PASS;
}

// Device-level UART initialization
Uint32 DEVICE_UARTInit(Uint8 periphNum)
{
  switch (periphNum)
  {
    case 0:
      DEVICE_LPSCTransition(PSCNUM0, LPSC_UART0, PD0, PSC_ENABLE);
      DEVICE_pinmuxControl(3,0x00FF0000,0x00220000); // UART0_TXD, UART0_RXD
      break;
    case 1:
      DEVICE_LPSCTransition(PSCNUM1, LPSC_UART1, PD0, PSC_ENABLE);
      DEVICE_pinmuxControl(4,0xFF000000,0x22000000); // UART1_TXD, UART1_RXD
      break;
    case 2:
      DEVICE_LPSCTransition(PSCNUM1, LPSC_UART2, PD0, PSC_ENABLE);
      DEVICE_pinmuxControl(4,0x00FF0000,0x00220000); // UART2_TXD, UART2_RXD
      break;
    default:
      return E_FAIL;
  }

  return E_PASS;
}

// Device-level I2C init
Uint32 DEVICE_I2CInit(Uint8 periphNum)
{
  // Assign the correct register base
  if (periphNum >= I2C_PERIPHERAL_CNT)
  {
    return E_FAIL;
  }
    
  switch (periphNum)
  {
    case 0:
      // No LPSC for I2C0
      DEVICE_pinmuxControl(4,0x0000FF00,0x00002200); // I2C0_SCL, I2C0_SDA
      break;
    case 1:
      DEVICE_LPSCTransition(PSCNUM1, LPSC_I2C1, PD0, PSC_ENABLE);
      DEVICE_pinmuxControl(4,0x00FF0000,0x00440000); // I2C1_SDA, I2C1_SCL
      break;
    default:
      return E_FAIL;
  }
    
  return E_PASS;
}

Uint32 DEVICE_SDMMCInit(Uint8 periphNum)
{
  // Assign the correct register base
  if (periphNum >= SDMMC_PERIPHERAL_CNT)
  {
    return E_FAIL;
  }
  
  switch (periphNum)
  {
    case 0:
      DEVICE_LPSCTransition(PSCNUM0, LPSC_SDMMC0, PD0, PSC_ENABLE);
      DEVICE_pinmuxControl(10,0xFFFFFFFF,0x22222222); // CLK, CMD, DAT[5:0]
      DEVICE_pinmuxControl(11,0x000000FF,0x00000022); // DAT[7:6]
      break;
    case 1:
      DEVICE_LPSCTransition(PSCNUM1, LPSC_SDMMC1, PD0, PSC_ENABLE);
      DEVICE_pinmuxControl(10,0xFF0FFF00,0x11022200); // CLK, CMD, DAT[7:6,0]
      DEVICE_pinmuxControl(11,0x000FFFFF,0x00022211); // DAT[5:1]
      break;
    default:
      return E_FAIL;
  }

  return E_PASS;
}

Uint32 DEVICE_TIMER0Init()
{
  // Power-up the Timer
  //DEVICE_LPSCTransition(PSCNUM0, LPSC_TIMER0, PD0 ,PSC_ENABLE);

  // Put timer into reset
  //TIMER0->EMUMGT_CLKSPD = 0x00000003;
  //TIMER0->TCR   = 0x00000000;
  
  // Setup as 2 unchained 32-bit timers
  //TIMER0->TGCR  = 0x00000005;

  // Reset timers to zero 
  //TIMER0->TIM12 = 0x00000000;

  // Set period to 5 sec
  //TIMER0->PRD12 = 0x019BFCC0;

  return E_PASS;
}

void DEVICE_TIMER0Start(void)
{
  // Clear interrupt
  //AINTC->IRQ1   |=  0x00000001;

  // Put timer out in reset
  //TIMER0->TGCR  &= ~(0x00000001);
    
  // Reset the timer counter to zero
  //TIMER0->TIM12 = 0x00000000;

  // Set for one-time run
  //TIMER0->TCR   = 0x00000040;
    
  // Take timer out of reset
  //TIMER0->TGCR  = 0x00000005;
  
}

void DEVICE_TIMER0Stop(void)
{
  // Clear interrupt
  //AINTC->IRQ1   |=  0x00000001;

  // Put timer in reset
  //TIMER0->TCR   = 0x00000000;
  //TIMER0->TGCR  = 0x00000000;

  // Reset timer count to zero 
  //TIMER0->TIM12 = 0x00000000;
}

Uint32 DEVICE_TIMER0Status(void)
{
  //return ((AINTC->IRQ1)&0x1);
	return 1;
}


/************************************************************
* Local Function Definitions                                *
************************************************************/

#if (defined(DA850) || defined(C6746))

static void LOCAL_initARMVectors (const Uint32 *armVectors)
{
  Uint32 *PRUDRam = (Uint32 *) &PRU0_DATA_START;

  PRU_enable();
  
  // Wake up the ARM memories
  DEVICE_LPSCTransition(PSCNUM0, LPSC_ARMRAM, PD0, PSC_ENABLE);

  // Make the address the global GEM address (prepend 0x11 to top two nibbles)
  // since the PRU cannot access stuff using local GEM address
  PRUDRam[0] = ((Uint32) armVectors)& 0x00FFFFFF | 0x11000000 ;
  PRUDRam[1] = (Uint32) (&ARM_VECT_START);
  PRUDRam[2] = (Uint32) (&ARM_VECT_SIZE);

  // Load PRU code
  PRU_load( (Uint32*)LOCAL_pru_mem1d_transfer, (sizeof(LOCAL_pru_mem1d_transfer)>>2));
  
  PRU_run();
  
  PRU_waitForHalt(-1);
  
  PRU_disable();
}

static void LOCAL_wakeUpARM ( void )
{
  // Wake-up ARM
  SYSTEM->HOSTCFG[0] = 0x00000001;
  DEVICE_LPSCTransition(PSCNUM0, LPSC_ARMINTC, PD0, PSC_ENABLE);
  DEVICE_LPSCTransition(PSCNUM0, LPSC_ARM, PD0, PSC_ENABLE);

  // De-assert ARM local reset
  PSC0->MDCTL[LPSC_ARM] = (PSC0->MDCTL[LPSC_ARM] & (~PSC_MDCTL_LRSTZ_MASK)) | (0x01 << PSC_MDCTL_LRSTZ_SHIFT);
}

#endif  


/***********************************************************
* End file                                                 *
***********************************************************/

