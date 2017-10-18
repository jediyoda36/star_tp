#ifndef LIGHT_JOIN_THREADS_H
#define LIGHT_JOIN_THREADS_H

#include <vector>
#include <thread>

class JoinThreads {
private:
    std::vector<std::thread>& threads;

public:
    explicit JoinThreads(std::vector<std::thread>& _threads) : threads(_threads) {}
    ~JoinThreads() {
        for (unsigned int i = 0; i < threads.size(); ++i) {
            if (threads[i].joinable())
                threads[i].join();
        }
    }
};


#endif // LIGHT_JOIN_THREADS_H
