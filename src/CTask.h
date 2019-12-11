#ifndef STAR_CTASK_H
#define STAR_CTASK_H

#include <functional>
#include <unordered_set>
#include <mutex>
#include <atomic>
#include <iostream>
#include <cstdio>
#include <memory>

class CTask {
  private:
    std::function<void()> mFunc;
    std::unordered_set<CTask*> mInDep, mOutDep;
    bool mDone;
    std::mutex mutInDep, mutOutDep, mutDone;

    CTask& addInDep(CTask*);
    void removeInDep(CTask*);

  public:
    explicit CTask(std::function<void()>);
    ~CTask();
    bool isReady();
    bool isDone();
    CTask& addOutDep(CTask*);
    void operator()();
    void taskInfo();
};

#endif // STAR_CTASK_H
