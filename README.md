# star_tp
thread pool version of star.

## Usage
Currently all modules are implemented as header files under include directory, if you want to use the modules, just add the following line in your **CMakeLists.txt** file:

```cmake
include_directories(/{path-to-star_tp}/include)
```
or the following line in your **Makefile**:
```make
CFLAGS += -I/{path-to-star_tp}/include
```

## Modules

### ThreadSafeQueue
ThreadSafeQueue is implemented using std::mutex and std::condition_variable.

### SimpleThreadPool
Simple thread pool implementation.

### JoinThreads
Thread joiner, using destructor safely release std::thread objects.(RAII)

### Task
Tasks that star_tp supports, wrapping std::packaged_task<T>. currently only support Task<void>.

### Scheduler
Scheduler schedules the tasks in readyTaskQueue and notReadyTaskQueue. When a task is ready Scheduler moves it from notReadyTaskQueue to readyTaskQueue, from where threads in thread_pool get tasks.

## TODO

### refactor

<2017.12.01>
* [x] using boost for thread pool.
* [x] redesign the scheduler to manage dependencies between CTask objects.

### performance

<2017.11.29>
* [x] thread safe queue, using condition variable instead of while loop when waiting for tasks.

### facilities

### doc
