#include "arm/sysregs.h"
 
#include "mm.h"
 
.section ".text.boot"
 
.globl _start
_start:
    mrs x0, mpidr_el1       
    and x0, x0,#0xFF    				// Check processor id
    cbz x0, master      				// Hang for all non-primary CPU
    b   proc_hang
 
proc_hang: 
    b   proc_hang
 
master:
    ldr x0, =SCTLR_VALUE_MMU_DISABLED 	//load no multiple memory units into x0
    msr sctlr_el1, x0  				  	// move value into system control register (el1)   
 
    ldr x0, =HCR_VALUE 				  	//load value for hypervisor configuration register into x0
    msr hcr_el2, x0 					//move value for hypervisor configuration register
 
    ldr x0, =SCR_VALUE 					//load value for el3 into x0
    msr scr_el3, x0 					//store value for el3
 
    ldr x0, =SPSR_EL2_VALUE				//load the saved program status register for el2 into x0
    msr spsr_el3, x0					//move this value into spsr_el3; now we jump to el2 from el3
 
    adr x0, el2_entry       			//load label for el2 entry into x0
    msr elr_el3, x0						//move this value into return register for el3
 
    eret                				//return to value in current exception level return register 
 
el2_entry:								//this starts after exiting el3
    adr x0, bss_begin					//load start into x0
    adr x1, bss_end						//load end into x1
    sub x1, x1, x0						//subratact x0 from x1 into x1
    bl  memzero							//reset memory to 0
 
    mov sp, #LOW_MEMORY					//move stack pointer 
 
    bl kernel_main_el2					//execute kernel_main_el2 in kernel.c, this is the el2 function
 
    ldr x0, =SPSR_EL1_VALUE             //load saved program status register for el1 into x0
    msr spsr_el2, x0					//move this value into spsr for el2
 
    ldr x0, =CPACR_EL1_FPEN				//load CPACR for el2 ( to give access to FP/SIMD registers)
    msr cpacr_el1, x0    				//move this value into the cpacr register for el1
 
    adr x0, el1_entry       			//load label for el1 entry into x0						
    msr elr_el2, x0						//move this value into return register for el2
 
    eret								//return to value in current exception level return register
 
el1_entry:
    mov sp, #LOW_MEMORY
 
    bl  kernel_main_el1	 				//execute kernel_main_el1 in kernel.c, this is the el1 function
    b   proc_hang       				// should never come here