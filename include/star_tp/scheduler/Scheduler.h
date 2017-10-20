#ifndef LIGHT_SCHEDULER_H
#define LIGHT_SCHEDULER_H

#include "star_tp/task/Task.h"
#include "star_tp/core/ThreadSafeQueue.h"
#include <atomic>
#include <mutex>

template <class T> class Scheduler {
  private:
    Scheduler() {}
    Scheduler(const Scheduler &) {}
    Scheduler &operator=(const Scheduler &) {}
    ~Scheduler() {}
    static ThreadSafeQueue<Task<T>> notReadyTaskQueue;
    static ThreadSafeQueue<Task<T>> readyTaskQueue;
    static Scheduler<T> *m_instance;
    static std::once_flag onceFlag;
    static std::atomic_bool done;
    static void init();

  public:
    static Scheduler<T> *getInstance();
    void addTask(Task<T> &task);
    bool getReadyTask(Task<T> &t);
    void schedule();
    void wait_and_stop();
};

template <class T> ThreadSafeQueue<Task<T>> Scheduler<T>::notReadyTaskQueue;

template <class T> ThreadSafeQueue<Task<T>> Scheduler<T>::readyTaskQueue;

template <class T> Scheduler<T> *Scheduler<T>::m_instance = nullptr;

template <class T> std::once_flag Scheduler<T>::onceFlag;

template <class T> std::atomic_bool Scheduler<T>::done{false};

template <class T> void Scheduler<T>::init() { m_instance = new Scheduler<T>(); }

template <class T> Scheduler<T> *Scheduler<T>::getInstance() {
    std::call_once(onceFlag, init);
    return m_instance;
}

template <class T> void Scheduler<T>::addTask(Task<T> &task) {
    if (task.isDone())
        return;
    if (task.isReady()) {
        readyTaskQueue.push(task);
    } else {
        notReadyTaskQueue.push(task);
    }
}

template <class T> bool Scheduler<T>::getReadyTask(Task<T> &t) { return readyTaskQueue.try_pop(t); }

template <class T> void Scheduler<T>::schedule() {
    while (!done) {
        Task<T> t;
    }
}

template <class T> void Scheduler<T>::wait_and_stop() { done = true; }

#endif // LIGHT_SCHEDULER_H
