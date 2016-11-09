#include "asm_tools.h"
#include "util.h"
#include "sced.h"

struct pcb_s kmain_process;
struct pcb_s* current_process;
//User space
void sys_yieldto(struct pcb_s* dest){
  //r0 = 5 : yieldto
  __asm("mov r0, #5");
  __asm("mov r1, %0" : : "r"(dest));
  __asm("SWI #0");
}

void sched_init(){
  current_process = &kmain_process;
}

//Kernel space
void do_sys_yieldto(uint32_t *register_pointer){
  //Le pointer vers la struc pcb est dans r1
  struct pcb_s *dest = (struct pcb_s*) register_pointer[1]; 

  //Switch context
  int i;
  for(i=0;i<12;i++){
    current_process->regs[i] = register_pointer[i];
    register_pointer[i] = dest->regs[i];
  }
  current_process->lr = register_pointer[13];
  register_pointer[13] = dest->lr;
  current_process = dest;
}
