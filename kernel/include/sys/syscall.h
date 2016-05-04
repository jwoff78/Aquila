#ifndef _SYSCALL_H
#define _SYSCALL_H

#include <core/system.h>

#if ARCH==X86
#include <arch/x86/include/syscall.h>
#endif

extern void (*syscall_table[])();

#endif /* ! _SYSCALL_H */