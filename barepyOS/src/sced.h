struct pcb_s{
 uint32_t regs[13];
 uint32_t lr_user;
 uint32_t lr_svc;
 uint32_t sp_user;
};

typedef int (func_t) (void);

void sys_yieldto(struct pcb_s* dest);
void do_sys_yieldto(uint32_t *dest);
void sched_init();
struct pcb_s* create_process(func_t entry);
