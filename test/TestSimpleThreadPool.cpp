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

int testSimpleThreadPool() {
    std::vector<std::thread> tv;
    for (int i = 0; i < 10; ++i) {
        tv.push_back(std::thread(do_work_vq3453q, i));
    }
    for (int i = 0; i < 10; ++i)
        tv[i].join();
    while (!tsq_test_simple_thread_pool.empty()) {
        std::cout << *tsq_test_simple_thread_pool.try_pop() << std::endl;
    }

    SimpleThreadPool<void> simpleThreadPool;
    std::cout << "master thread id:" << std::this_thread::get_id() << std::endl;
    sleep(1);
    for (int i = 0; i < 100; ++i) {
        simpleThreadPool.submit(f_lq234oi8);
    }

    return 0;
}
