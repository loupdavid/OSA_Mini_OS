#include "asm_tools.h"
#include "util.h"
#include "sced.h"
#include "kheap.h"

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
  kheap_init();
  current_process = &kmain_process;
}

struct pcb_s* create_process(func_t entry){
  unsigned int size = 1000;
  struct pcb_s* pcb = (struct pcb_s*) kAlloc(sizeof(struct pcb_s));
  char* mem = (char *) kAlloc(size);
  pcb->lr_svc = (uint32_t) entry;
  pcb->sp_user = (uint32_t) (mem+size);
  return pcb;
}

//Kernel space
void do_sys_yieldto(uint32_t *register_pointer){
  //Le pointer vers la struc pcb est dans r1
  struct pcb_s *dest = (struct pcb_s*) register_pointer[1];

  // Sauvegarde -----
  // On passe en mode sys pour avoir acces au reg user
  __asm("cps 0x1f");
  __asm("mov %0, lr" : "=r"(current_process->lr_user));
  __asm("mov %0, sp" : "=r"(current_process->sp_user));
  // On repasse le CPU en mode SVC
  __asm("cps 0x13");
  int i;
  for(i=0;i<12;i++){
    current_process->regs[i] = register_pointer[i];
  }
  current_process->lr_svc = register_pointer[13];

  //------Switch -------------
  current_process = dest;
  
  // Restore ------
  for(i=0;i<12;i++){
    register_pointer[i] = current_process->regs[i];
  }
  register_pointer[13] = dest->lr_svc;
  __asm("cps 0x1f"); // User : Restore sp
  __asm("mov sp, %0" : : "r"(current_process->sp_user));
  __asm("mov lr, %0" : : "r"(current_process->lr_user));
  __asm("cps 0x13"); // SVC
  //---------------
}