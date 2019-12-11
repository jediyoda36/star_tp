#ifndef STAR_CSCHEDULER_H
#define STAR_CSCHEDULER_H

#include "CTask.h"
#include "CThreadSafeQueue.h"
#include "CThreadPool.h"
#include <atomic>
#include <mutex>
#include <memory>
#include <utility>

class CScheduler {
  private:
    CScheduler() {}
    CScheduler(const CScheduler&) {}
    CScheduler& operator=(const CScheduler&) {}
    ~CScheduler() {}
    static CThreadSafeQueue<CTask*> notReadyTaskQueue;
    static CThreadSafeQueue<CTask*> readyTaskQueue;
    static CScheduler* m_instance;
    static std::once_flag onceFlag;
    static void init();
    void updateNotReadyTasks();
    std::shared_ptr<CTask*> getReadyTask();

  public:
    static CScheduler* getInstance();
    void addTask(CTask*);
    void schedule(CThreadPool&);
};

#endif // STAR_CSCHEDULER_H
