#ifndef LIGHT_SIMPLE_THREAD_POOL_H
#define LIGHT_SIMPLE_THREAD_POOL_H

#include <thread>
#include <atomic>
#include <functional>
#include <vector>
#include "ThreadSafeQueue.h"
#include "JoinThreads.h"

class SimpleThreadPool {
  private:
    std::atomic_bool done;
    ThreadSafeQueue<std::function<void()> > workQueue;
    std::vector<std::thread> threads;
    JoinThreads joiner;

    void workerThread() {
        while (!done) {
            std::function<void()> task;
            if (workQueue.try_pop(task)) {
                task();
            } else {
                std::this_thread::yield();
            }
        }
    }

  public:
    SimpleThreadPool() : done(false), joiner(threads) {
        unsigned const threadCount = std::thread::hardware_concurrency();
        try {
            for (unsigned i = 0; i < threadCount; ++i) {
                threads.push_back(
                    std::thread(&SimpleThreadPool::workerThread, this));
            }
        }
        catch (...) {
            done = true;
            throw;
        }
    }

    ~SimpleThreadPool() { done = true; }

    template <class func> void submit(func f) {
        workQueue.push(std::function<void()>(f));
    }
};

#endif // LIGHT_SIMPLE_THREAD_POOL_H
