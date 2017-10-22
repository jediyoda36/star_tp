#ifndef LIGHT_TASK_H
#define LIGHT_TASK_H

#include <future>
#include <unordered_set>
#include <mutex>
#include <atomic>
#include <iostream>

/*
 * T is return type of task, using bind to add parameters
 *
 * e.g.: T->int
 * int add(int a, int b) { return a+b; }
 * std::packaged_task<int()> task(std::bind(add, 1, 2));
 */
template<class T = void>
class Task {
    std::packaged_task<T()> task;
    // ThreadSafeQueue<shared_ptr<Task>> inDep, outDep;
    std::unordered_set<Task<T>*> inDep, outDep;
    std::mutex mutInDep, mutOutDep;
    std::atomic_bool done;
public:
    explicit Task(std::packaged_task<T()> _task, bool _done = false) : task(std::move(_task)), done(_done) {}
    ~ Task() {}
    bool isReady() {
        return inDep.empty();
    }
    bool isDone() {
        return done;
    }
    Task& addInDep(Task* task) {
        std::lock_guard<std::mutex> lk(mutInDep);
        inDep.insert(task);
        return *this;
    }
    Task& addOutDep(Task* task) {
        std::lock_guard<std::mutex> lk(mutOutDep);
        outDep.insert(task);
        return *this;
    }
    void removeDependency(Task* task) {
        std::lock_guard<std::mutex> lk(mutInDep);
        inDep.erase(task);
    }
    void operator()(){
        std::cout << "enter operator()\n";
        std::future<T> fut = task.get_future();
        std::cout << "future gotten\n";
        task();
        try {
            fut.get();
        } catch (...) {
            throw;
        }
        std::cout << "done\n";
        done = true;
        for (Task<T>* t : outDep)
            t->removeDependency(this);
    }
};

#endif // LIGHT_TASK_H
