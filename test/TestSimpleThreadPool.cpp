#include <iostream>
#include <thread>
#include <vector>
#include <cstdio>
#include <unistd.h>
#include "star_tp/core/ThreadSafeQueue.h"
#include "star_tp/thread/SimpleThreadPool.h"

static ThreadSafeQueue<int> tsq_test_simple_thread_pool;

static void do_work_vq3453q(int i) { tsq_test_simple_thread_pool.push(i); }

static void f_lq234oi8() {
    printf("thread_id: %ld\n", std::this_thread::get_id());
}

static void taskDemo(int taskId) {
    printf("task %d\n", taskId);
}

int main() {
    // using std::thread
    std::vector<std::thread> tv;
    for (int i = 0; i < 10; ++i) {
        tv.push_back(std::thread(do_work_vq3453q, i));
    }
    for (int i = 0; i < 10; ++i)
        tv[i].join();
    while (!tsq_test_simple_thread_pool.empty()) {
        std::cout << *tsq_test_simple_thread_pool.try_pop() << std::endl;
    }

    // using SimpleThreadPool, no dependencies
    SimpleThreadPool<void> simpleThreadPool(6);
    std::cout << "master thread id:" << std::this_thread::get_id() << std::endl;
    sleep(1);
    for (int i = 0; i < 10; ++i) {
        Task<> t(std::function<void()>{f_lq234oi8});
        simpleThreadPool.submit(t);
    }
    simpleThreadPool.wait_and_stop();

    // using SimpleThreadPool, with dependencies
    sleep(1);
    // std::vector<Task<>> taskVector(16, Task<>());
    // using placement new at tp
    Task<>* taskVector = new Task<>[16];
    for (int i = 0; i < 16; ++i) {
        new (taskVector+i)Task<>(std::function<void()>(std::bind(taskDemo, i)));
        // taskVector.push_back(std::move(t));
        // taskVector[i].setFunction(std::function<void()>(std::bind(taskDemo, i)));
    }

    taskVector[1].addOutDep(&taskVector[3]);
    taskVector[2].addOutDep(&taskVector[3]);
    taskVector[3].addOutDep(&taskVector[4]).addOutDep(&taskVector[7]);
    taskVector[5].addOutDep(&taskVector[7]);
    taskVector[6].addOutDep(&taskVector[7]);
    taskVector[8].addOutDep(&taskVector[11]);
    taskVector[9].addOutDep(&taskVector[11]);
    taskVector[10].addOutDep(&taskVector[11]);
    taskVector[7].addOutDep(&taskVector[12]);
    taskVector[11].addOutDep(&taskVector[12]);
    taskVector[12].addOutDep(&taskVector[13]);
    taskVector[13].addOutDep(&taskVector[14]);
    taskVector[14].addOutDep(&taskVector[15]);

    for (int i = 0; i < 16; ++i) {
        simpleThreadPool.submit(taskVector[i]);
    }
    simpleThreadPool.wait_and_stop();



    return 0;
}
