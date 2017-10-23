# star_tp
thread pool version of star.

## ThreadSafeQueue
ThreadSafeQueue is implemented using std::mutex and std::condition_variable.

## SimpleThreadPool
Simple thread pool implementation.

## JoinThreads
Thread joiner, using destructor safely release std::thread objects.(RAII)

## Task
Tasks that star_tp supports, wrapping std::packaged_task<T>. currently only support Task<void>.

## Scheduler
Scheduler schedules the tasks in readyTaskQueue and notReadyTaskQueue. When a task is ready Scheduler moves it from notReadyTaskQueue to readyTaskQueue, from where threads in thread_pool get tasks.
