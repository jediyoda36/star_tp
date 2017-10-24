#ifndef LIGHT_TEST_FUNCTION_AND_BIND_H
#define LIGHT_TEST_FUNCTION_AND_BIND_H

#include <iostream>
#include <functional>

int half(int x) {
    return x/2;
}

int main() {
    std::function<int(int)> f1{half};
    std::function<int()> f2{std::bind(half, 2)};

    std::function<int()> f3 {f2};  // test copy constructor
    std::function<int()>& f4 = f3; // test reference

    std::cout << "f1(4): " << f1(4) << std::endl;
    std::cout << "f2() : " << f2() << std::endl;
    std::cout << "f3() : " << f3() << std::endl;
    std::cout << "f4() : " << f4() << std::endl;

    std::function<int()> f5;
    std::cout << (f5 ? "callable" : "not callable") << "\n";

    return 0;
}

#endif // LIGHT_TEST_FUNCTION_AND_BIND_H
