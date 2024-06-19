#include "mutex.h"
#include "futex.h"

enum {
    UNLOCKED = 0,
    LOCKED_NO_WAITER = 1,
    LOCKED = 2,
};

void mutex_init(struct mutex *mu)
{
    mu->val = UNLOCKED;
}

void mutex_unlock(struct mutex *mu)
{
    uint32_t orig =
        atomic_fetch_sub_explicit(&mu->val, 1, memory_order_relaxed);
    if (orig != LOCKED_NO_WAITER) {
        mu->val = UNLOCKED;
        chan_futex_wake(&mu->val, 1);
    }
}

static uint32_t cas(_Atomic uint32_t *ptr, uint32_t expect, uint32_t new)
{
    atomic_compare_exchange_strong_explicit(
        ptr, &expect, new, memory_order_acq_rel, memory_order_acquire);
    return expect;
}

void mutex_lock(struct mutex *mu)
{
    uint32_t val = cas(&mu->val, UNLOCKED, LOCKED_NO_WAITER);
    if (val != UNLOCKED) {
        do {
            if (val == LOCKED ||
                cas(&mu->val, LOCKED_NO_WAITER, LOCKED) != UNLOCKED)
                chan_futex_wait(&mu->val, LOCKED);
        } while ((val = cas(&mu->val, UNLOCKED, LOCKED)) != UNLOCKED);
    }
}