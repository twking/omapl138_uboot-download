/*
 * cmd.h
 *
 *  Created on: 2018-8-17
 *      Author: Administrator
 */

#ifndef CMD_H_
#define CMD_H_

#define UP_ARM 0
#define UP_DSP 1
#define UP_UBOOT 2
#define UP_LOAD 3
#define GET_DATA 4
#define	ERASE_DATA_SECTION 5

#include "hw_types.h"

int gethelp(void);
int getCMDlines(void);
int getAddr_length(int *addr,int *nbytes);
int getdownloaddata(unsigned char *pData);
#endif /* CMD_H_ */
