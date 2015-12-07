#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "threading.h"
#include "worklist.h"
#include "dirtravers.h"
#include <sys/types.h>

volatile bool notDone = true;
volatile int threads_waiting = 0;
pthread_mutex_t waitingLock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t boolLock = PTHREAD_MUTEX_INITIALIZER;
/**
 * goes through the work pool, if there is not work
 * to be done it marks itself as waiting.
 */
void *worker(void *arg){
    int * countSearches = (int*)calloc(1,sizeof(int));
    while(getIsNotDone()){
        if(!work_queue_empty()){
            setWaiting(false); 
            char * directory = get_work();
            /** if someone beat us to the work queue */
            if(directory != NULL){
                searchForName(directory,(struct Flags *)arg);
                *countSearches = *countSearches + 1;
                free(directory);
            }
            setWaiting(true);
        }
    }
    return (void*) countSearches;
}

/** a thread is waiting for work */
void setWaiting(bool waiting){
    pthread_mutex_lock(&waitingLock);
    if(waiting)
        threads_waiting++;
    else if(threads_waiting > 0)
        threads_waiting--;
    pthread_mutex_unlock(&waitingLock);
}

/** get the added waiting value of all threads */
int getWaiting(){
    pthread_mutex_lock(&waitingLock);
    int temp = threads_waiting;
    pthread_mutex_unlock(&waitingLock);
    return temp; 
}

/** all threads are done */
void isDone(){
    pthread_mutex_lock(&boolLock);
    notDone = false;
    pthread_mutex_unlock(&boolLock);
}

/** get the added waiti */
bool getIsNotDone(){
    pthread_mutex_lock(&boolLock);
    bool temp = notDone;
    pthread_mutex_unlock(&boolLock);
    return temp;
}

