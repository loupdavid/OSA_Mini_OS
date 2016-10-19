#include "util.h"
// Fonction appel sys depuis le user space
void sys_reboot(){
  //r0 = 1 : reboot
  __asm("mov r0, #1");
  __asm("SWI #0");
}

void do_sys_reboot(){
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
