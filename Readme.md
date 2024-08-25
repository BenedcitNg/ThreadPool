# Disclaimer

This demo project is for learning purpose only. The originial code is from [ThreadPool](https://subingwen.cn/linux/threadpool/#1-%E7%BA%BF%E7%A8%8B%E6%B1%A0%E5%8E%9F%E7%90%86") and I am not the author of this project, I just simply rewrote it by myself and made some tweaks.

# Thread Pool

## The Necessity of Thread Pool

If every time we want to use a thread, we just create a new thread, it is convenient; however, if in the occasion that the concurrency is high but each thread only is executed for a very short time period and it will be destroyed, the frequent creation/destruction of threads will be costly. Hence, we need a technology to reuse the created threads and allow them to execute other tasks instead of being destroyed. So this is why the thread pool is introduced. Thread pool manages threads in batch, threads in the thread pool only are destroyed when the thread pool terminates.

## Components of Thread Pool

A thread pool mainly consists of 3 parts: [task queue](#task-queue), [working threads](#working-threads-number-of-threads-n), and [manager thread](#manager-thread-number-of-threads-1).

### Task Queue

It stores the tasks needed to be handled. It is a producer-consumer model, when APIs are called, tasks are added/removed from the task queue. Once a task is handled, it will be removed from the task queue.The user of task queue, that is the thread adds jobs to task queue, is the producer.

### Working Threads (Number of Threads: N)

Thread pool maintains a certain amount of working threads, their tasks are reading from the task queue and handling the threads from task queue. Working threads are like consumers of task queue. If a task queue is empty, working threads will be blocked by conditional variables/semaphores. After the block, if new tasks are generated, the producer will unblock them and they will start working.

### Manager Thread (Number of Threads: 1)

The manager thread manages each thread. Its job is periodically check the number of tasks in the task queue and the number of working threads. It accordingly creates/destroys tasks.


# Compile the program

This demo program needs to be compiled at Linux OS. Simply type `make` and the program will be compiled. The elf file is located at `./staging/bin`. The `staging` directory is a temporary directory used to store intermediate files. Type `make clean` to clean the entire directory.