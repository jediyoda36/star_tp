#ifndef STAR_ITHREAD_POOL_H
#define STAR_ITHREAD_POOL_H

#include "Task.h"

class IThreadPool {
public:
    IThreadPool();
    virtual ~IThreadPool();

    virtual void  init(int numThreads) = 0;

    virtual void submit(Task &t) = 0;

};

#endif // STAR_ITHREAD_POOL_H
