/*
 * spiwiter.h
 *
 *  Created on: 2018-6-15
 *      Author: Administrator
 */


#ifndef SPIWITER_H_
#define SPIWITER_H_

#include "tistdtypes.h"

typedef struct _CODE_LENGTH_
{
	unsigned int arm_length;
	unsigned int dsp_length;
	unsigned int downlown_length;
}CODE_length;
#define UBOOT_ADDR 0x0000//32kbytes
#define CODE_LENGTH_ADDR 0x8000//标识每个程序的大小,大小12bytes
#define DOWNLOAD_ADDR 0x10000
#define ARMCODE_ADDR  0x20000//128k bytes
#define DSPCODE_ADDR  0x40000//256 bytes
#define DATACODE_ADDR 0x80000//3840k bytes
#define MAX_AADR  (0x400000-1024)

void spi_witer_init( void );
void spi_witer_dspcode(Uint32 byteCnt);
void spi_witer_arm(Uint32 byteCnt);
void spi_witer_uboot(Uint32 byteCnt);
void spi_witer_load(Uint32 byteCnt);
void spi_get_data(Uint32 startAddr, Uint32 byteCnt);
int spi_set_codelength(unsigned char *dest);
int spi_get_codelength(unsigned char *dest);
int spiflash_eraseBytes(unsigned int startAddr,unsigned int byteCnt);

#endif /* SPIWITER_H_ */
