#ifndef LIGHT_SCHEDULER_H
#define LIGHT_SCHEDULER_H

#include "star_tp/task/Task.h"
#include "star_tp/core/ThreadSafeQueue.h"
#include <atomic>
#include <mutex>
#include <memory>
#include <utility>

template <class T = void> class Scheduler {
  private:
    Scheduler() {}
    Scheduler(const Scheduler &) {}
    Scheduler &operator=(const Scheduler &) {}
    ~Scheduler() {}
    static ThreadSafeQueue<Task<T> *> notReadyTaskQueue;
    static ThreadSafeQueue<Task<T> *> readyTaskQueue;
    static Scheduler<T> *m_instance;
    static std::once_flag onceFlag;
    // static std::atomic_bool done;
    // static bool done;
    static void init();
    void updateNotReadyTasks();

  public:
    static Scheduler<T> *getInstance();
    void addTask(Task<T>*);
    std::shared_ptr<Task<T>*> getReadyTask();
    void schedule();
    // void wait_and_stop();
};

template <class T> ThreadSafeQueue<Task<T> *> Scheduler<T>::notReadyTaskQueue;

template <class T> ThreadSafeQueue<Task<T> *> Scheduler<T>::readyTaskQueue;

template <class T> Scheduler<T> *Scheduler<T>::m_instance = nullptr;

template <class T> std::once_flag Scheduler<T>::onceFlag;

// template <class T> std::atomic_bool Scheduler<T>::done{false};
// template <class T> bool Scheduler<T>::done{false};

template <class T> void Scheduler<T>::init() { m_instance = new Scheduler<T>(); }

template <class T> Scheduler<T> *Scheduler<T>::getInstance() {
    std::call_once(onceFlag, init);
    return m_instance;
}

template <class T> void Scheduler<T>::addTask(Task<T>* task) {
    // printf("Scheduler::addTask +\n");
    // task->taskInfo();
    if (task->isDone()) {
        // printf("isDone\n");
        return;
    }
    if (task->isReady()) {
        // printf("isReady\n");
        readyTaskQueue.push(std::move(task));
    } else {
        // printf("notReady\n");
        notReadyTaskQueue.push(std::move(task));
    }
    // printf("readyTaskQueue.size: %lu, notReadyTaskQueue.size: %lu\n", readyTaskQueue.size(), notReadyTaskQueue.size());
    // printf("Scheduler::addTask -\n");
}

template <class T> std::shared_ptr<Task<T>*> Scheduler<T>::getReadyTask() { return readyTaskQueue.try_pop(); }

template <class T> void Scheduler<T>::schedule() {
    // printf("Scheduler::schedule +\n");
    /*
    while (true) {
        if (done)
            break;
        printf("schedule 1\n");
        if (notReadyTaskQueue.empty())
            continue;
        updateNotReadyTasks();
    }
    */
    while (!notReadyTaskQueue.empty()) {
        // printf("schedule 2\n");
        updateNotReadyTasks();
    }
    // printf("Scheduler::schedule -\n");
}

/*
template <class T> void Scheduler<T>::wait_and_stop() {
    done = true;
    printf("Scheduler done, wait all task finish\n");
}
*/

template <class T> void Scheduler<T>::updateNotReadyTasks() {
    std::shared_ptr<Task<T>*> t = notReadyTaskQueue.try_pop();
    if (!t)
        return;
    Task<T>* tp = *t;
    if (tp->isDone())
        notReadyTaskQueue.try_pop();
    if (tp->isReady())
        readyTaskQueue.push(std::move(tp));
    else
        notReadyTaskQueue.push(std::move(tp));
}

#endif // LIGHT_SCHEDULER_H
