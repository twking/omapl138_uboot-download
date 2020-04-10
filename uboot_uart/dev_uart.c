/*
 * dev_uart.c
 *
 *  Created on: 2018-8-16
 *      Author: Administrator
 */




/**
 * \file  uartConsole.c
 *
 * \brief This file contains functions which interface interactively
 *        with the user through the serial console to perform some
 *        utility operations.
 */

/*
* Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
*
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
*/

/* HW Macros */
#include "dev_uart.h"


/******************************************************************************
**              INTERNAL MACRO DEFINITIONS
******************************************************************************/


//void InitUART0(unsigned int baseAdd)//BAUD_115200
//{
    //unsigned int intFlags = 0;
 //   unsigned int config = 0;
   // rxlength = 0;
   // length = 0;
   // count = 0;

    /* Enabling the PSC for UART2.*/
  //  PSCModuleControl(SOC_PSC_0_REGS, HW_PSC_UART0, PSC_POWERDOMAIN_ALWAYS_ON,
//		     PSC_MDCTL_NEXT_ENABLE);

    /* Setup PINMUX */
//    UARTPinMuxSetup(0, FALSE);

    /* Enabling the transmitter and receiver*/
//    UARTEnable(SOC_UART_0_REGS);

    /* 1 stopbit, 8-bit character, no parity */
//    config = UART_WORDL_8BITS;

    /* Configuring the UART parameters*/
//    UARTConfigSetExpClk(SOC_UART_0_REGS, SOC_UART_0_MODULE_FREQ,
//    		baseAdd, config,
//                        UART_OVER_SAMP_RATE_16);
    /* Enabling the FIFO and flushing the Tx and Rx FIFOs.*/
//    UARTFIFOEnable(SOC_UART_0_REGS);

    /* Setting the UART Receiver Trigger Level*/
//    UARTFIFOLevelSet(SOC_UART_0_REGS, UART_RX_TRIG_LEVEL_1);

//}

void InitUART2(unsigned int baseAdd)//BAUD_115200
{
    //unsigned int intFlags = 0;
    unsigned int config = 0;
   // rxlength = 0;
   // length = 0;
   // count = 0;

    /* Enabling the PSC for UART2.*/
    PSCModuleControl(SOC_PSC_1_REGS, HW_PSC_UART2, PSC_POWERDOMAIN_ALWAYS_ON,
		     PSC_MDCTL_NEXT_ENABLE);

    /* Setup PINMUX */
    UARTPinMuxSetup(2, FALSE);

    /* Enabling the transmitter and receiver*/
    UARTEnable(SOC_UART_2_REGS);

    /* 1 stopbit, 8-bit character, no parity */
    config = UART_WORDL_8BITS;

    /* Configuring the UART parameters*/
    UARTConfigSetExpClk(SOC_UART_2_REGS, SOC_UART_2_MODULE_FREQ,
    		baseAdd, config,
                        UART_OVER_SAMP_RATE_16);

    /* Enabling the FIFO and flushing the Tx and Rx FIFOs.*/
    UARTFIFOEnable(SOC_UART_2_REGS);

    /* Setting the UART Receiver Trigger Level*/
    UARTFIFOLevelSet(SOC_UART_2_REGS, UART_RX_TRIG_LEVEL_1);

}

/********************************* End Of File ******************************/
