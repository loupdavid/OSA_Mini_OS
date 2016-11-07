//User space
void sys_reboot();
void sys_nop();
void sys_settime(uint64_t date_ms);

//Kernel
void do_sys_settime(void *param_pointer);
void do_sys_reboot();
void swi_handler();
