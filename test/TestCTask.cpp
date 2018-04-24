#ifndef LIGHT_TEST_CTASk_H
#define LIGHT_TEST_CTASk_H

#include "star.h"
#include <iostream>

void testCTask01() {
    std::cout << "testCTask01\n";
}

void testCTask02(int a, int b) {
    std::cout << a+b << std::endl;
}

int main() {
    CTask t1{std::function<void()>{testCTask01}};
    t1();
    CTask t2{std::function<void()>{std::bind(testCTask02, 1, 2)}};
    t2();
    // the following statements are failed, because field mut* in CTask has inaccessible copy constructor
    // CTask<> t3(t2);
    // t3();
    // CTask<> t4 = t2;
    // t4();
    return 0;
}

#endif // LIGHT_TEST_CTASk_H
