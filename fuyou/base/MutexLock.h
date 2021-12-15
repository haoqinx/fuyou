#include "nonecopyable.h"
#include <pthread.h>
#include <cstdio>
#ifndef _MUTEXLOCK_H
#define _MUTEXLOCK_H

namespace fuyou
{
class MutexLock:nonecopyable{
public:
    MutexLock(){
        pthread_mutex_init(&mutex, nullptr);
    }
    ~MutexLock(){
        pthread_mutex_lock(&mutex); 
        pthread_mutex_destroy(&mutex);
    }

    void lock(){
        pthread_mutex_lock(&mutex);
    }
    void unlock(){
        pthread_mutex_unlock(&mutex);
    }

    pthread_mutex_t* get(){
        return &mutex;
    }
private:
    pthread_mutex_t mutex;
    friend class Condition;

};

class MutexLockGuard:nonecopyable{
public:
explicit MutexLockGuard(MutexLock& m):mutex(m){
    mutex.lock();
}

~MutexLockGuard(){
    mutex.unlock();
}
private:
    MutexLock &mutex;
};
} // namespace fuyou



#endif