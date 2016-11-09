//User space
void sys_reboot();
void sys_nop();
void sys_settime(uint64_t date_ms);
uint64_t sys_gettime();

//Kernel
void do_sys_settime(uint32_t *param_pointer);
void do_sys_gettime(uint32_t *param_pointer);
void do_sys_reboot();
void swi_handler();
