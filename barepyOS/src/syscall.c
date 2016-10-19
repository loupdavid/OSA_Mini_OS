#include "util.h"
#include "asm_tools.h"
// Fonction appel sys depuis le user space
void sys_reboot(){
  //r0 = 1 : reboot
  __asm("mov r0, #1");
  __asm("SWI #0");
}

void do_sys_reboot(){
  const int PM_RSTC = 0x2010001c;
  const int PM_WDOG = 0x20100024;
  const int PM_PASSWORD = 0x5a000000;
  const int PM_RSTC_WRCFG_FULL_RESET = 0x00000020;
  Set32(PM_WDOG, PM_PASSWORD | 1);
  Set32(PM_RSTC, PM_PASSWORD | PM_RSTC_WRCFG_FULL_RESET);
  while(1); 
}

//Software Interrupt handler (kernel space)
void swi_handler(){
  int num_swi;
  __asm("mov %0, r0" : "=r"(num_swi));
  switch(num_swi){
    case 1:
      do_sys_reboot();  
    break;
    default:
      PANIC();
  }
}
