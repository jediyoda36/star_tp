#include <iostream>
#include <thread>
#include <vector>
#include <cstdio>
#include <unistd.h>
#include "./ThreadSafeQueue.h"
#include "./SimpleThreadPool.h"

ThreadSafeQueue<int> tsq;

void do_work(int i) { tsq.push(i); }

void f() {
    printf("thread_id: %ld\n", std::this_thread::get_id());
}

int main() {
    std::vector<std::thread> tv;
    for (int i = 0; i < 10; ++i) {
        tv.push_back(std::thread(do_work, i));
    }
    for (int i = 0; i < 10; ++i)
        tv[i].join();
    while (!tsq.empty()) {
        std::cout << *tsq.try_pop() << std::endl;
    }

    SimpleThreadPool simpleThreadPool;
    std::cout << "master thread id:" << std::this_thread::get_id() << std::endl;
    sleep(1);
    for (int i = 0; i < 100; ++i) {
        simpleThreadPool.submit(f);
    }

    return 0;
}
