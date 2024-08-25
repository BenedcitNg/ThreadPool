#ifndef _THREADPOOL_H
#define _THREADPOOL_H

#ifdef _cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NUMBER 2
typedef struct Task
{
    void (*function)(void* arg);
    void* arg;
}Task;

typedef struct ThreadPool
{
    // Task Queue
    Task* taskQ;
    int queueCapacity;  
    int queueSize;          // The current size of tasks
    int queueFront;         // head of task: insert data
    int queueRear;          // tail of task: take out data

    pthread_t managerID;    
    pthread_t *threadIDs;   // IDs of working threads
    int minNum;             // minimun existing threads
    int maxNum;             // maximum existing threads
    int busyNum;            // No. of working threas
    int liveNum;            // No. of existing threads
    int exitNum;            // No. of threads to be destroyed
    pthread_mutex_t mutexPool;  // Mutex for entire thread pool
    pthread_mutex_t mutexBusy;  // mutex for busyNum
    pthread_cond_t notFull;     // Check if task queue is full
    pthread_cond_t notEmpty;    // check if task queue is empty

    int shutdown;         
}ThreadPool;

ThreadPool *threadPoolCreate(int min, int max, int queueSize);
int threadPoolDestroy(ThreadPool* pool);
void threadPoolAdd(ThreadPool* pool, void(*func)(void*), void* arg);
int threadPoolBusyNum(ThreadPool* pool);
int threadPoolAliveNum(ThreadPool* pool);

void* worker(void* arg);

void* manager(void* arg);

void threadExit(ThreadPool* pool);

#ifdef _cplusplus
    }
#endif
#endif 
