/*
 * dev_uart.h
 *
 *  Created on: 2018-8-16
 *      Author: Administrator
 */

#ifndef DEV_UART_H_
#define DEV_UART_H_
#include "hw_types.h"

/* System Defines */
#include "evmOMAPL138.h"
#include "soc_OMAPL138.h"
#include "hw_syscfg0_OMAPL138.h"

/* Driver APIs */
#include "psc.h"
#include "uart.h"
#define UART_CONSOLE_BASE               (SOC_UART_2_REGS)
//void InitUART0(unsigned int baseAdd);
void InitUART2(unsigned int baseAdd);

#endif /* DEV_UART_H_ */
