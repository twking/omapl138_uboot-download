-stack          0x00001000 /* Stack Size */
-heap           0x00001000 /* Heap Size */
-e Entry
MEMORY
{
  entrypoin	  org=0x80000000 len=0x00000100 /* running program */
  SHARED_RAM  org=0x80000100 len=0x0001C000-0x100 /* running program */
  uboot_uart  org=0x8001C000 len =0x00003000 /* 8kB ARM local RAM */
  L2_RAM      org=0x8001F000 len=0x00001000 /* L2_RAM for flash witer code */
  L2_DOWNLODD org=0x11800000 len=0x00040000 /* L2_RAM for download code */
}

SECTIONS
{
	//.main    > main_code  /*   .text:_c_int00 > dsp_entry_point*/
    .init 	 : {
    			 system_config.lib<init.obj> (.text)
    		   } load > entrypoin
    .text    > SHARED_RAM              /* CODE                              */
	.data    > SHARED_RAM
    .bss     > SHARED_RAM         /* GLOBAL & STATIC VARS              */
    			RUN_START(bss_start),
				RUN_END(bss_end)
    .const  > SHARED_RAM              /* SOFTWARE SYSTEM STACK             */
    .cinit  > SHARED_RAM              /* SOFTWARE SYSTEM STACK             */
    .stack  > SHARED_RAM             /* SOFTWARE SYSTEM STACK             */
    .sysmem     >   SHARED_RAM
    .switch     >   SHARED_RAM
    .far        >   SHARED_RAM

  .ddr_mem :
  {
    . += 0x00001000;
  } run = L2_RAM,type=DSECT, RUN_START(EXTERNAL_RAM_START), RUN_END(EXTERNAL_RAM_END)
}
