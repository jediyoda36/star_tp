#include "CTask.h"

CTask::CTask(std::function<void()> _func) : mFunc(std::move(_func)), mDone(false) {
}

CTask::~CTask() {}

bool CTask::isReady() {
    std::lock_guard<std::mutex> lk(mutInDep);
    return mInDep.empty();
}

bool CTask::isDone() {
    std::lock_guard<std::mutex> lk(mutDone);
    return mDone;
}

CTask& CTask::addInDep(CTask* task) {
    std::lock_guard<std::mutex> lk(mutInDep);
    mInDep.insert(task);
    return *this;
}

CTask& CTask::addOutDep(CTask* task) {
    task->addInDep(this);
    std::lock_guard<std::mutex> lk(mutOutDep);
    mOutDep.insert(task);
    return *this;
}

void CTask::removeInDep(CTask* task) {
    std::lock_guard<std::mutex> lk(mutInDep);
    mInDep.erase(task);
}

void CTask::operator()() {
    if (!mFunc)
        std::cerr << "function is not callable\n";
    try {
        mFunc();
    } catch (...) {
        throw;
    }
    mDone = true;
    for (CTask* t : mOutDep)
        t->removeInDep(this);
}

void CTask::taskInfo() {
    printf("address: %p, mDone: %d, mInDep.size(): %d, mOutDep.size(): %d\n", this, mDone, mInDep.size(), mOutDep.size());
}
