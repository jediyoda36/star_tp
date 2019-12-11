#include "star.h"
#include <boost/thread/thread.hpp>
#include <iostream>
#include <boost/timer.hpp>
#include <cstdio>

static void taskDemo(int taskId) {
    boost::this_thread::sleep(boost::posix_time::seconds(1));
    printf("task %d\n", taskId);
}

int main() {
    CThreadPool pool(6);
    CScheduler* schdp = CScheduler::getInstance();
    char* p = new char[sizeof(CTask) * 16];
    CTask* taskVector = (CTask*)p;
    for (int i = 0; i < 16; ++i) {
        new (taskVector + i)CTask(std::function<void()>(std::bind(taskDemo, i)));
    }
    taskVector[1].addOutDep(&taskVector[3]);
    taskVector[2].addOutDep(&taskVector[3]);
    taskVector[3].addOutDep(&taskVector[4]).addOutDep(&taskVector[7]);
    taskVector[5].addOutDep(&taskVector[7]);
    taskVector[6].addOutDep(&taskVector[7]);
    taskVector[8].addOutDep(&taskVector[11]);
    taskVector[9].addOutDep(&taskVector[11]);
    taskVector[10].addOutDep(&taskVector[11]);
    taskVector[7].addOutDep(&taskVector[12]);
    taskVector[11].addOutDep(&taskVector[12]);
    taskVector[12].addOutDep(&taskVector[13]);
    taskVector[13].addOutDep(&taskVector[14]);
    taskVector[14].addOutDep(&taskVector[15]);
    for (int i = 0; i < 16; ++i) {
        schdp->addTask(&taskVector[i]);
    }
    schdp->schedule(pool);
    delete [] p;
    return 0;
}

int main1() {
    // Create a thread pool of 4 worker threads.
    CThreadPool pool(4);

    char* p = new char[sizeof(CTask) * 16];
    CTask* taskVector = (CTask*)p;
    for (int i = 0; i < 16; ++i) {
        new (taskVector + i)CTask(std::function<void()>(std::bind(taskDemo, i)));
    }

    for (int i = 0; i < 16; i++) {
        pool.submit(&taskVector[i]);
    }

    // Queue a bunch of work items.
    /*
    for (int i = 0; i < 16; ++i) {
      pool.submit([i] {
        boost::this_thread::sleep(boost::posix_time::seconds(1));
        taskDemo(i);
      });
      //pool.submit([i]{printf("task %d\n", i);});
    }
    */

    return 0;
}

