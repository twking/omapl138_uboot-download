/*
 * spiwiter.h
 *
 *  Created on: 2018-6-15
 *      Author: Administrator
 */

#ifndef SPIWITER_H_
#define SPIWITER_H_

#define UBOOT_ADDR 0
#define CODE_LENGTH_ADDR 0x8000//标识每个程序的大小
#define DOWNLOAD_ADDR 0x10000
#define ARMCODE_ADDR  0x20000
#define DSPCODE_ADDR  0x40000
#define DATACODE_ADDR 0x80000

#define ARM_RUN_ADDR 0x80000000
#define DSP_RUN_ADDR 0x11800000


typedef struct _CODE_LENGTH_
{
	unsigned int arm_length;
	unsigned int dsp_length;
	unsigned int downlown_length;
}CODE_length;

void spi_witer_init( void );
void gelengthCode(CODE_length *tbuff);
void geArmCode(int nl);
void geDspCode(int nl);
void geDownlodCode(int nl);
#endif /* SPIWITER_H_ */
