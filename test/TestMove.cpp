#ifndef LIGHT_TEST_MOVE_H
#define LIGHT_TEST_MOVE_H

#include <utility>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <cstdio>
#include <unistd.h>
#include <CThreadSafeQueue.h>

CThreadSafeQueue<int> que;
CThreadSafeQueue<int*> quep;

void thread_get_int() {
    std::shared_ptr<int> sp = que.wait_and_pop();
    printf("%d: %p\n", *sp, sp.get());
}

void thread_get_intp() {
    std::shared_ptr<int*> sp = quep.wait_and_pop();
    printf("%d: %p\n", *(*sp), *sp);
}

int main() {
    int a = 3;
    std::cout << &a << std::endl;
    int b = std::move(a);
    std::cout << a << std::endl;
    std::cout << &a << std::endl;
    std::cout << &b << std::endl;

    std::shared_ptr<int> p1(std::make_shared<int>(a));

    for (int i = 0; i < 10; ++i)
        que.push(i);
    for (int i = 0; i < 10; ++i) {
        std::shared_ptr<int> sp = que.try_pop();
        std::cout << *sp << ": " << sp.get() << std::endl;
        que.push(*sp);
    }

    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i)
        threads.push_back(std::thread(thread_get_int));
    for (int i = 0; i < 10; ++i)
        threads[i].join();

    sleep(2);

    std::vector<int*> intps;
    for (int i = 0; i < 10; ++i)
        intps.push_back(new int(i));
    for (int i = 0; i < 10; ++i)
        quep.push(intps[i]);
    for (int i = 0; i < 10; ++i) {
        std::shared_ptr<int*> sp = quep.try_pop();
        std::cout << *(*sp) << ": " << *sp << std::endl;
        quep.push(*sp);
    }

    std::vector<std::thread> threadsp;
    for (int i = 0; i < 10; ++i)
        threadsp.push_back(std::thread(thread_get_intp));
    for (int i = 0; i < 10; ++i)
        threadsp[i].join();
    return 0;
}

#endif // LIGHT_TEST_MOVE_H
