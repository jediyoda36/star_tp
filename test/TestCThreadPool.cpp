#include "CThreadPool.h"
#include "CTask.h"
#include <boost/thread/thread.hpp>
#include <iostream>
#include <boost/timer.hpp>
#include <cstdio>

static void taskDemo(int taskId) {
    boost::this_thread::sleep(boost::posix_time::seconds(1));
    printf("task %d\n", taskId);
}


int main() {
  // Create a thread pool of 4 worker threads.
  CThreadPool pool(4);

  char * p = new char[sizeof(CTask) * 16];
  CTask* taskVector = (CTask*)p;
    for (int i = 0; i < 16; ++i) {
        new (taskVector+i)CTask(std::function<void()>(std::bind(taskDemo, i)));
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
