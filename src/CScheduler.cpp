#include "CScheduler.h"

CThreadSafeQueue<CTask*> CScheduler::notReadyTaskQueue;

CThreadSafeQueue<CTask*> CScheduler::readyTaskQueue;

CScheduler* CScheduler::m_instance = nullptr;

std::once_flag CScheduler::onceFlag;

void CScheduler::init() {
    m_instance = new CScheduler();
}

CScheduler* CScheduler::getInstance() {
    std::call_once(onceFlag, init);
    return m_instance;
}

void CScheduler::addTask(CTask* task) {
    if (task->isDone()) {
        return;
    }
    if (task->isReady()) {
        readyTaskQueue.push(std::move(task));
    } else {
        notReadyTaskQueue.push(std::move(task));
    }
}

std::shared_ptr<CTask*> CScheduler::getReadyTask() {
    return readyTaskQueue.try_pop();
}

void CScheduler::schedule(CThreadPool& tpool) {
    while (!notReadyTaskQueue.empty()) {
        while (!readyTaskQueue.empty()) {
            tpool.submit(*getReadyTask());
        }
        updateNotReadyTasks();
    }
    while (!readyTaskQueue.empty()) {
        tpool.submit(*getReadyTask());
    }
}

void CScheduler::updateNotReadyTasks() {
    std::shared_ptr<CTask*> t = notReadyTaskQueue.try_pop();
    if (!t)
        return;
    CTask* tp = *t;
    if (tp->isDone())
        notReadyTaskQueue.try_pop();
    if (tp->isReady())
        readyTaskQueue.push(std::move(tp));
    else
        notReadyTaskQueue.push(std::move(tp));
}
