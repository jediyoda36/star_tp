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
    Task<> t1{std::function<void()>{testTask01}};
    t1();
    Task<> t2{std::function<void()>{std::bind(testTask02, 1, 2)}};
    t2();
    // the following statements are failed, because field mut* in Task has inaccessible copy constructor
    // Task<> t3(t2);
    // t3();
    // Task<> t4 = t2;
    // t4();
    return 0;
}

#endif // LIGHT_TEST_TASK_H
