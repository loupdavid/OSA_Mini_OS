# -*- mode:gdb-script -*-

layout split
focus cmd
winheight cmd 25
target remote:1234

set history filename ~/.gdb_history
set history save

b *reset_asm_handler
b *after_kmain
b kernel_panic

b *kmain
b do_sys_reboot
b kernel_panic
b do_sys_yieldto
b sced.c:59
b kmain.c:13
b kmain.c:24

source utils.gdb

continue
