/*
 * device.h
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
  FILE        : device.h                                                   
  PROJECT     : DA8xx/OMAP-L138 ROM Boot Loader
  AUTHOR      : Daniel Allred
  DESC        : Provides device differentiation for the project files. This
                file MUST be modified to match the device specifics.
----------------------------------------------------------------------------- */

#ifndef _DEVICE_H_
#define _DEVICE_H_

#include "tistdtypes.h"

// Prevent C++ name mangling
#ifdef __cplusplus
extern far "c" {
#endif

/***********************************************************
* Global Macro Declarations                                *
***********************************************************/


/************************************************************
* Global Variable Declarations                              *
************************************************************/

#define LPSC_SPI0           (4)
#define LPSC_SPI1           (10)

/******************************************************
* Global Typedef declarations                         *
******************************************************/


typedef enum _DEVICE_BOOTPERIPHERAL_
{
  DEVICE_BOOTPERIPHERAL_SPI=0,

}
DEVICE_BootPeripheral;

typedef enum _DEVICE_BOOTMODE_
{
  DEVICE_BOOTMODE_SPI0_FLASH=0,               // 24 bit address
  DEVICE_BOOTMODE_SPI1_FLASH,                 // 24 bit address
}
DEVICE_BootMode;

// Power/Sleep Ctrl Register structure
typedef struct _DEVICE_PSC_REGS_
{
  VUint32 PID;        // 0x000
  VUint8 RSVD0[16];   // 0x004
  VUint8 RSVD1[4];    // 0x014
  VUint32 INTEVAL;    // 0x018
  VUint8 RSVD2[36];   // 0x01C
  VUint32 MERRPR0;    // 0x040
  VUint32 MERRPR1;    // 0x044
  VUint8 RSVD3[8];    // 0x048
  VUint32 MERRCR0;    // 0x050
  VUint32 MERRCR1;    // 0x054
  VUint8 RSVD4[8];    // 0x058
  VUint32 PERRPR;     // 0x060
  VUint8 RSVD5[4];    // 0x064
  VUint32 PERRCR;     // 0x068
  VUint8 RSVD6[4];    // 0x06C
  VUint32 EPCPR;      // 0x070
  VUint8 RSVD7[4];    // 0x074
  VUint32 EPCCR;      // 0x078
  VUint8 RSVD8[144];  // 0x07C
  VUint8 RSVD9[20];   // 0x10C
  VUint32 PTCMD;      // 0x120
  VUint8 RSVD10[4];   // 0x124
  VUint32 PTSTAT;     // 0x128
  VUint8 RSVD11[212]; // 0x12C
  VUint32 PDSTAT0;    // 0x200
  VUint32 PDSTAT1;    // 0x204
  VUint8 RSVD12[248]; // 0x208
  VUint32 PDCTL0;     // 0x300
  VUint32 PDCTL1;     // 0x304
  VUint8 RSVD13[536]; // 0x308
  VUint32 MCKOUT0;    // 0x520
  VUint32 MCKOUT1;    // 0x524
  VUint8 RSVD14[728]; // 0x528
  VUint32 MDSTAT[41]; // 0x800
  VUint8 RSVD15[348]; // 0x8A4
  VUint32 MDCTL[41];  // 0xA00
}
DEVICE_PSCRegs;

#define PSC0 ((DEVICE_PSCRegs*) 0x01C10000)
#define PSC1 ((DEVICE_PSCRegs*) 0x01E27000)

#define EMURSTIE_MASK       (0x00000200)

#define PSC_ENABLE          (0x3)
#define PSC_DISABLE         (0x2)
#define PSC_SYNCRESET       (0x1)
#define PSC_SWRSTDISABLE    (0x0)

#define PSC_MDCTL_LRSTZ_MASK     (0x00000100u)
#define PSC_MDCTL_LRSTZ_SHIFT    (0x00000008u)

#define PSCNUM0             (0x0)
#define PSCNUM1             (0x1)

#define PD0                 (0x0)
#define PD1                 (0x1)
// System Control Module register structure
typedef struct _DEVICE_SYS_MODULE_REGS_
{
  VUint32 REVID;              //0x00
  VUint8  RSVD0[4];           //0x04
  VUint32 DIEIDR[4];          //0x08
  VUint32 DEVIDD[2];          //0x18
  VUint32 BOOTCFG;            //0x20
  VUint32 CHIPREVID;          //0x24
  VUint32 FEATURE_ENA;        //0x28
  VUint32 L2ROMDIV;           //0x2C
  VUint8  RSVD1[8];           //0x30
  VUint32 KICKR[2];           //0x38
  VUint32 HOSTCFG[2];         //0x40
  VUint8  RSVD2[152];         //0x48
  VUint32 IRAWSTRAT;          //0xE0
  VUint32 IENSTAT;            //0xE4
  VUint32 IENSET;             //0xE8
  VUint32 IENCLR;             //0xEC
  VUint32 EOI;                //0xF0
  VUint32 FLTADDRR;           //0xF4
  VUint32 FLTSTAT;            //0xF8
  VUint32 FLTCLR;             //0xFC
  VUint8  RSVD3[16];          //0x100
  VUint32 MSTPRI[3];          //0x110
  VUint8  RSVD4[4];           //0x11C
  VUint32 PINMUX[20];         //0x120
  VUint32 SUSPSRC;            //0x170
  VUint32 CHIPSIG;            //0x174
  VUint32 CHIPSIG_CLR;        //0x178
  VUint32 CFGCHIP[5];         //0x17C
  VUint8  RSVD5[5];           //0x190
  VUint32 ROMCHECKSUM[2];     //0x1A0
}
DEVICE_SysModuleRegs;

#define SYSTEM ((DEVICE_SysModuleRegs*) 0x01C14000)

#define DEVICE_BOOTCFG_BOOTMODE_MASK    (0x000000FFu)
#define DEVICE_BOOTCFG_BOOTMODE_SHIFT   (0)

#define DEVICE_CHIPREVID_TYPE_MASK      (0x00000030u)
#define DEVICE_CHIPREVID_TYPE_SHIFT     (4)

#define DEVICE_CFGCHIP0_PLL0MASTERLOCK_MASK    (0x00000010u)
#define DEVICE_CFGCHIP0_PLL0MASTERLOCK_SHIFT   (4)

#define DEVICE_CFGCHIP1_HPIBYTEAD_MASK  (0x00010000u)
#define DEVICE_CFGCHIP1_HPIBYTEAD_SHIFT (16)
#define DEVICE_CFGCHIP1_HPIENA_MASK     (0x00008000u)
#define DEVICE_CFGCHIP1_HPIENA_SHIFT    (15)

#define DEVICE_CFGCHIP3_RMII_MODE_MASK        (0x00000100u)
#define DEVICE_CFGCHIP3_RMII_MODE_SHIFT       (8)
#define DEVICE_CFGCHIP3_EMB_2XCLKSRC_MASK     (0x00000080u)
#define DEVICE_CFGCHIP3_EMB_2XCLKSRC_SHIFT    (7)
#define DEVICE_CFGCHIP3_RPI_TXCLKSRC_MASK     (0x00000040u)
#define DEVICE_CFGCHIP3_RPI_TXCLKSRC_SHIFT    (6)
#define DEVICE_CFGCHIP3_PLL1MASTERLOCK_MASK   (0x00000020u)
#define DEVICE_CFGCHIP3_PLL1MASTERLOCK_SHIFT  (5)
#define DEVICE_CFGCHIP3_ASYNC3_CLKSRC_MASK    (0x00000010u)
#define DEVICE_CFGCHIP3_ASYNC3_CLKSRC_SHIFT   (4)
#define DEVICE_CFGCHIP3_PRUEVTSEL_MASK        (0x00000008u)
#define DEVICE_CFGCHIP3_PRUEVTSEL_SHIFT       (3)
#define DEVICE_CFGCHIP3_DIV4p5ENA_MASK        (0x00000004u)
#define DEVICE_CFGCHIP3_DIV4p5ENA_SHIFT       (2)
#define DEVICE_CFGCHIP3_EMA_CLKSRC_MASK       (0x00000002u)
#define DEVICE_CFGCHIP3_EMA_CLKSRC_SHIFT      (1)

#define DEVICE_L2ROMDIV_ADDRLINE_MASK   (0x000003FFu)
#define DEVICE_L2ROMDIV_ADDRLINE_SHIFT  (0)

// SPI Register structure
typedef struct _DEVICE_SPI_REGS_
{
  VUint32 SPIGCR0;          // 0x00
  VUint32 SPIGCR1;          // 0x04
  VUint32 SPIINT;           // 0x08
  VUint32 SPILVL;           // 0x0C
  VUint32 SPIFLG;           // 0x10
  VUint32 SPIPC0;           // 0x14
  VUint32 SPIPC1;           // 0x18
  VUint32 SPIPC2;           // 0x1C
  VUint32 SPIPC3;           // 0x20
  VUint32 SPIPC4;           // 0x24
  VUint32 SPIPC5;           // 0x28
  VUint32 SPIPC6;           // 0x2C
  VUint32 SPIPC7;           // 0x30
  VUint32 SPIPC8;           // 0x34
  VUint32 SPIDAT[2];        // 0x38
  VUint32 SPIBUF;           // 0x40
  VUint32 SPIEMU;           // 0x44
  VUint32 SPIDELAY;         // 0x48
  VUint32 SPIDEF;           // 0x4C
  VUint32 SPIFMT[4];        // 0x50
  VUint32 TGINTVEC[2];      // 0x60
  VUint32 SPIDUMMY[51];
  VUint32 SPIIOLPBK;
}
DEVICE_SPIRegs;

#define SPI1 ((DEVICE_SPIRegs *) 0x01F0E000u)

#define DEVICE_SPI_SPIGCR1_SPIEN_MASK     (0x01000000u)
#define DEVICE_SPI_SPIGCR1_SPIEN_SHIFT    (24)


/***********************************************************
* Global Function Declarations                             *
***********************************************************/
extern __FAR__ Uint32  DEVICE_SPIInit(Uint8 periphNum);


/***********************************************************
* End file                                                 *
***********************************************************/

#ifdef __cplusplus
}
#endif

#endif // End _DEVICE_H_


