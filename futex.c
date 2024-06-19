#ifndef SYS_futex
#define SYS_futex __NR_futex
#endif

#include "futex.h"
#include <sys/syscall.h>
#include <unistd.h>
#include <linux/futex.h>

extern long syscall(long number, ...);

long chan_futex_wait(_Atomic uint32_t *uaddr, uint32_t val)
{
    return syscall(SYS_futex, uaddr, FUTEX_WAIT, val, NULL, NULL, 0);
}

long chan_futex_wake(_Atomic uint32_t *uaddr, uint32_t val)
{
    return syscall(SYS_futex, uaddr, FUTEX_WAKE, val, NULL, NULL, 0);
}