struct pcb_s{
 uint32_t regs[13];
 uint32_t lr_user;
 uint32_t lr_svc;
};

void sys_yieldto(struct pcb_s* dest);
void do_sys_yieldto(uint32_t *dest);
void sched_init();
