#ifndef FUTEX_H
#define FUTEX_H

#include <stdatomic.h>
#include <stdint.h>

long chan_futex_wait(_Atomic uint32_t *uaddr, uint32_t val);
long chan_futex_wake(_Atomic uint32_t *uaddr, uint32_t val);

#endif // FUTEX_H