#include "util.h"
#include "asm_tools.h"

// Cote user space -------------------------------------
// Fonction appel sys depuis le user space
void sys_reboot(){
  //r0 = 1 : reboot
  __asm("mov r0, #1");
  __asm("SWI #0");
}

void sys_nop(){
  //r0 = 2 : nop
  __asm("mov r0, #2");
  __asm("SWI #0");
  return;
}
// -----------------------------------------------------

// Cote kernel space -----------------------------------
void do_sys_reboot(){
  const int PM_RSTC = 0x2010001c;
  const int PM_WDOG = 0x20100024;
  const int PM_PASSWORD = 0x5a000000;
  const int PM_RSTC_WRCFG_FULL_RESET = 0x00000020;
  Set32(PM_WDOG, PM_PASSWORD | 1);
  Set32(PM_RSTC, PM_PASSWORD | PM_RSTC_WRCFG_FULL_RESET);
  while(1); 
}

void do_sys_nop(){
  return;
}

//Software Interrupt handler (kernel space)
void swi_handler(){
  //Save context
  __asm("stmfd sp!, {r0-r12,lr}");
  int num_swi;
  __asm("mov %0, r0" : "=r"(num_swi));
  switch(num_swi){
    case 1:
      do_sys_reboot();  
    case 2:
      do_sys_nop();  
    break;
    default:
      PANIC();
  }
  //Restore context
  __asm("ldmfd sp!, {r0-r12,pc}^");
}
// -----------------------------------------------------
