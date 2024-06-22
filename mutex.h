#ifndef MUTEX_H
#define MUTEX_H

#include <stdatomic.h>
#include <stdint.h>



struct mutex {
    _Atomic uint32_t val;
};

#define MUTEX_INITIALIZER \
    (struct mutex) { .val = 0 }

void mutex_init(struct mutex *mu);
void mutex_unlock(struct mutex *mu);
void mutex_lock(struct mutex *mu);

#endif // MUTEX_H