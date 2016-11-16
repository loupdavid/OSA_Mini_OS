struct pcb_s{
 uint32_t regs[13];
 uint32_t lr_user;
 uint32_t lr_svc;
 uint32_t sp_user;
 uint32_t cpsr_user;
 int last;
 struct pcb_s* next;
};

typedef int (func_t) (void);

void sys_yieldto(struct pcb_s* dest);
void do_sys_yieldto(uint32_t *register_pointer);
void sched_init();
struct pcb_s* create_process(func_t entry);
void sys_yield();
void do_sys_yield(uint32_t *register_pointer);
