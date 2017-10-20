#include <iostream>
#include <future>
#include <mutex>
#include <thread>

using namespace std;

static std::mutex mut_test_future_promise_async;

static int factorial(int n) {
    int res = 1;
    for (int i = n; i > 1; --i)
        res *= i;
    {
        std::lock_guard<std::mutex> lk(mut_test_future_promise_async);
        cout << "result is: " << res << endl;
    }
    return res;
}

int testFuture() {
    int x;
    std::future<int> fu =  std::async(factorial, 4);
    x = fu.get();

    cout << x << endl;
    return 0;
}


static int factorial1(std::future<int>& f) {
    int res = 1;
    int n = f.get();
    for (int i = n; i > 1; --i)
        res *= i;
    {
        std::lock_guard<std::mutex> lk(mut_test_future_promise_async);
        cout << "result is: " << res << endl;
    }
    return res;
}

int testPromiseAndFuture() {
    int x;
    std::promise<int> p;
    std::future<int> f = p.get_future();

    std::future<int> fu = std::async(factorial1, std::ref(f));

    // do something

    p.set_value(4);
    x = fu.get();

    cout << x << endl;

    return 0;
}

static int factorial2(std::shared_future<int> sf) {
    int res = 1;
    int n = sf.get();
    for (int i = n; i > 1; --i)
        res *= i;
    {
        std::lock_guard<std::mutex> lk(mut_test_future_promise_async);
        cout << "result is: " << res << endl;
    }
    return res;
}

int testSharedFuture() {
    int x;

    std::promise<int> p;
    std::future<int> f = p.get_future();
    std::shared_future<int> sf = f.share();

    std::future<int> fu1 = std::async(factorial2, sf);
    std::future<int> fu2 = std::async(factorial2, sf);
    std::future<int> fu3 = std::async(factorial2, sf);

    // do something

    p.set_value(4);
    x = fu1.get();
    x = fu2.get();
    x = fu3.get();

    cout << x << endl;

    return 0;
}

int main() {
    printf("testFuture\n");
    testFuture();
    printf("testPromiseAndFuture\n");
    testPromiseAndFuture();
    printf("testSharedFuture\n");
    testSharedFuture();
    return 0;
}
