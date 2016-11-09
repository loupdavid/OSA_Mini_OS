struct pcb_s{
 int i;
};

void sys_yieldto(struct pcb_s* dest);
void do_sys_yieldto(uint32_t *dest);
