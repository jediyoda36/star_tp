#include <future>
#include <deque>
#include <mutex>
#include <condition_variable>
#include <iostream>

static std::deque<std::packaged_task<int()>> task_q_packaged_task;
static std::mutex mut_test_packaged_task;
static std::condition_variable cond_packaged_task;

static int factorial3(int n) {
    int res = 1;
    for (int i = n; i > 1; --i)
        res *= i;
    std::cout << "result: " << res << std::endl;
    return res;
}

static void thread_func() {
    std::packaged_task<int()> t;
    {
        std::unique_lock<std::mutex> lk(mut_test_packaged_task);
        cond_packaged_task.wait(lk, []{return !task_q_packaged_task.empty();});
        t = std::move(task_q_packaged_task.front());
        task_q_packaged_task.pop_front();
    }
    t();
}

int testPackagedTask() {
    std::thread t1(thread_func);
    std::packaged_task<int()> t(std::bind(factorial3, 6));
    std::future<int> fu = t.get_future();

    {
        std::unique_lock<std::mutex> lk(mut_test_packaged_task);
        task_q_packaged_task.push_back(std::move(t));
        cond_packaged_task.notify_one();
    }

    std::cout << fu.get() << std::endl;

    t1.join();

    return 0;
}
