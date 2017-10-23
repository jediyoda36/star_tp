#ifndef LIGHT_TASK_H
#define LIGHT_TASK_H

#include <functional>
#include <unordered_set>
#include <mutex>
#include <atomic>
#include <iostream>
#include <cstdio>
#include <memory>

/*
 * T is return type of task, using bind to add parameters
 *
 * e.g.: T->int
 * int add(int a, int b) { return a+b; }
 * std::packaged_task<int()> task(std::bind(add, 1, 2));
 */
template<class T = void>
class Task {
    std::function<T()> task;
    // std::unordered_set<std::shared_ptr<Task<T>>> inDep, outDep;
    std::unordered_set<Task<T>*> inDep, outDep;
    bool done;
    std::mutex mutInDep, mutOutDep, mutDone;
public:
    Task(std::function<T()> _task) : task(std::move(_task)), done(false) {}
    ~ Task() {}
    bool isReady() {
        std::lock_guard<std::mutex> lk(mutInDep);
        return inDep.empty();
    }
    bool isDone() {
        std::lock_guard<std::mutex> lk(mutDone);
        return done;
    }
    Task& addInDep(Task<T>* task) {
        std::lock_guard<std::mutex> lk(mutInDep);
        inDep.insert(task);
        return *this;
    }
    Task& addOutDep(Task<T>* task) {
        std::lock_guard<std::mutex> lk(mutOutDep);
        outDep.insert(task);
        task->addInDep(this);
        return *this;
    }
    void removeInDep(Task<T>* task) {
        std::lock_guard<std::mutex> lk(mutInDep);
        inDep.erase(task);
    }
    void operator()(){
        if (!task)
            std::cerr << "function is not callable\n";
        try {
            task();
        } catch (...) {
            throw;
        }
        done = true;
        for (Task<T>* t: outDep)
            t->removeInDep(this);
    }
    void taskInfo() {
        printf("address: %p, done: %d, inDep.size(): %d, outDep.size(): %d\n", this, done, inDep.size(), outDep.size());
    }
};

#endif // LIGHT_TASK_H
