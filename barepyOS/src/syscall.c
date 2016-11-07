#include "util.h"
#include "asm_tools.h"
#include "hw.h"
#include <stdint.h>

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

void sys_settime(uint64_t date_ms){
  //r0 = 3 : settime
  int inutile = 5;
  int inutile2 = 6;
  inutile = inutile + inutile2;
  inutile = inutile2 + date_ms; 

  //Numero d'appel dans r0, argument dans r1
  __asm("mov r1, %0" : : "r"(date_ms & 0xffffffff00000000 >> 32));
  __asm("mov r2, %0" : : "r"(date_ms & 0x00000000ffffffff));
  __asm("mov r0, #3");
  __asm("SWI #0");
  return;
}
// -----------------------------------------------------

// Cote kernel space -----------------------------------
void do_sys_reboot(){
  //Deja defini dans hw.c
  /*const int PM_RSTC = 0x2010001c;
  const int PM_WDOG = 0x20100024;
  const int PM_PASSWORD = 0x5a000000;
  const int PM_RSTC_WRCFG_FULL_RESET = 0x00000020;*/
  Set32(PM_WDOG, PM_PASSWORD | 1);
  Set32(PM_RSTC, PM_PASSWORD | PM_RSTC_WRCFG_FULL_RESET);
  while(1); 
}

void do_sys_nop(){
  return;
}

void do_sys_settime(void *param_pointer){
  //Recupere parametre
  uint64_t date_ms=3;
  //r2 = lsb = pointer, pointer + 4 ( + 32 bits) = msb = r1
  uint32_t lsb = *(uint32_t*)param_pointer;
  uint32_t msb = *(uint32_t*)(param_pointer+4);
  date_ms = (uint64_t) msb << 32 | (uint64_t) lsb;
  set_date_ms(date_ms);
}

//Software Interrupt handler (kernel space)
void __attribute__((naked)) swi_handler(){
  //Save context
  __asm("stmfd sp!, {r0-r12,lr}");

  //Save parameters
  void *param_pointer;
  __asm("push {r1}");
  __asm("push {r2}");
  __asm("mov %0, sp" : "=r"(param_pointer));

  int num_swi;
  __asm("mov %0, r0" : "=r"(num_swi));
  switch(num_swi){
    case 1:
      do_sys_reboot();  
    case 2:
      do_sys_nop();
    break;
    case 3:
      do_sys_settime(param_pointer);  
    break;
    default:
      PANIC();
  }
  //On pop r1, sinon la restauration du contexte foire
  __asm("pop {r1,r2}");
  //Restore context
  __asm("ldmfd sp!, {r0-r12,pc}^");
}
// -----------------------------------------------------
