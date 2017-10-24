#ifndef LIGHT_SIMPLE_THREAD_POOL_H
#define LIGHT_SIMPLE_THREAD_POOL_H

#include <thread>
#include <atomic>
#include <functional>
#include <vector>
#include "star_tp/thread/JoinThreads.h"
#include "star_tp/scheduler/Scheduler.h"

template< class T = void>
class SimpleThreadPool {
  private:
    std::atomic_bool done;
    std::vector<std::thread> threads;
    JoinThreads joiner;
    int numThreads;

    void workerThread() {
        while (!done) {
            // std::function<void()> task;
            std::shared_ptr<Task<T>*> task = Scheduler<T>::getInstance()->getReadyTask();
            if (task) {
                Task<T>* tp = *task;
                (*tp)();
            } else {
                std::this_thread::yield();
            }
        }
    }

  public:
    SimpleThreadPool(int _numThreads) : done(false), joiner(threads), numThreads(_numThreads) {
        try {
            for (unsigned i = 0; i < numThreads; ++i) {
                threads.push_back(
                    std::thread(&SimpleThreadPool<T>::workerThread, this));
            }
        }
        catch (...) {
            done = true;
            throw;
        }
    }

    ~SimpleThreadPool() { done = true; }

    //template <class func> void submit(func f) {
        //workQueue.push(std::function<void()>(f));
    //}

    void submit(Task<T>& t) {
        // printf("SimpleThreadPool::submit +\n");
        Scheduler<T>::getInstance()->addTask(&t);
        // printf("SimpleThreadPool::submit -\n");
    }

    void wait_and_stop() {
        Scheduler<T>::getInstance()->schedule();
    }
};

#endif // LIGHT_SIMPLE_THREAD_POOL_H
