#ifndef CHAN_H
#define CHAN_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "mutex.h"

struct chan_item {
    _Atomic uint32_t lap;
    void *data;
};

struct chan {
    _Atomic bool closed;
    _Atomic(void **) datap;
    struct mutex send_mtx, recv_mtx;
    _Atomic uint32_t send_ftx, recv_ftx;
    _Atomic size_t send_waiters, recv_waiters;
    size_t cap;
    _Atomic uint64_t head, tail;
    struct chan_item ring[0];
};

typedef void *(*chan_alloc_func_t)(size_t);

struct chan *chan_make(size_t cap, chan_alloc_func_t alloc);
void chan_close(struct chan *ch);
int chan_send(struct chan *ch, void *data);
int chan_recv(struct chan *ch, void **data);

#endif // CHAN_H