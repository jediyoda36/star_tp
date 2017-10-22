#ifndef LIGHT_TEST_TASK_H
#define LIGHT_TEST_TASK_H

#include "star_tp/task/Task.h"
#include <iostream>

void testTask01() {
    std::cout << "testTask01\n";
}

void testTask02(int a, int b) {
    std::cout << a+b << std::endl;
}

int main() {
    Task<> t1{std::packaged_task<void()>{testTask01}};
    t1();
    Task<> t2{std::packaged_task<void()>{std::bind(testTask02, 1, 2)}};
    t2();
    return 0;
}

#endif // LIGHT_TEST_TASK_H
