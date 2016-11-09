#include "asm_tools.h"
#include "util.h"
#include "sced.h"

//User space
void sys_yieldto(struct pcb_s* dest){
  //r0 = 5 : yieldto
  __asm("mov r0, #5");
  __asm("mov r1, %0" : : "r"(dest));
  __asm("SWI #0");
}

//Kernel space
void do_sys_yieldto(uint32_t *register_pointer){
  //Le pointer vers la struc pcb est dans r1
  struct pcb_s *pointer = (struct pcb_s*) register_pointer[1]; 
  struct pcb_s dest = *pointer;

  dest.i = 0xbabababa;
  dest.i = dest.i + 1;
}
