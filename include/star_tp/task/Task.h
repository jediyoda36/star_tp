#ifndef LIGHT_TASK_H
#define LIGHT_TASK_H

#include <future>
#include <unordered_set>
#include <mutex>
#include <atomic>

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
    std::unordered_set<Task*> inDep, outDep;
    std::mutex mutInDep, mutOutDep;
    std::atomic_bool done;
public:
    explicit Task(std::packaged_task<T()> _task) : task(std::move(_task)), done(false) {}
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
        std::future<T> fut = task();
        fut.get();
        done = true;
        for (Task* t : outDep)
            t->removeDependency(this);
    }
};

#endif // LIGHT_TASK_H
