/****************************************************************************/
/*  OMAPL138.cmd                                                            */
/*  Copyright (c) 2010 Texas Instruments Incorporated                       */
/*  Author: Rafael de Souza                                                 */
/*                                                                          */
/*    Description: This file is a sample linker command file that can be    */
/*                 used for linking programs built with the C compiler and  */
/*                 running the resulting .out file on an OMAPL138           */
/*                 device.  Use it as a guideline.  You will want to        */
/*                 change the memory layout to match your specific          */
/*                 target system.  You may want to change the allocation    */
/*                 scheme according to the size of your program.            */
/*                                                                          */
/*    Usage:       The map below contains the local memory for each core    */
/*                 Use the linker option --define=DSP_CORE=n                */
/*                 Where n defines the core used: DSP (n=1) or ARM (n=0)    */
/*                                                                          */
/****************************************************************************/
-stack          0x0000500 /* Stack Size */
-heap           0x0000500 /* Heap Size */
-e Entry

MEMORY
{
 	appmain_code	 org=0x80000000 len=0x00000100 /* running program */
    uboot_uart       o = 0x8001C000  l = 0x00003000  /* 8kB ARM local RAM */
}

SECTIONS
{
	.app_main    > appmain_code  /*   .text:_c_int00 > dsp_entry_point*/
    .init 	 : {
    			 system_config.lib<init.obj> (.text)
    		   } load > uboot_uart
    .text    > uboot_uart              /* CODE                              */
	.data    > uboot_uart
    .bss     > uboot_uart         /* GLOBAL & STATIC VARS              */
    			RUN_START(bss_start),
				RUN_END(bss_end)
    .const  > uboot_uart              /* SOFTWARE SYSTEM STACK             */
    .cinit  > uboot_uart              /* SOFTWARE SYSTEM STACK             */
    .stack  > uboot_uart              /* SOFTWARE SYSTEM STACK             */
    .sysmem     >   uboot_uart
    .switch     >   uboot_uart
    .far        >   uboot_uart

}
