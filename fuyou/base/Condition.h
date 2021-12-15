#ifndef _CONDITION_H
#define _CONDITION_H
#include "nonecopyable.h"
#include <pthread.h>
#include <mutex>
#include "MutexLock.h"
#include <time.h>
namespace fuyou
{
class Condition:nonecopyable{
public:
    explicit Condition(MutexLock& m):mutex(m){
        pthread_cond_init(&cond, nullptr);
    }
    ~Condition(){
        pthread_cond_destroy(&cond);
    }

    void wait(){
        pthread_cond_wait(&cond, mutex.get());
    }
    void notify(){
        pthread_cond_signal(&cond);
    }
    void notifyAll(){
        pthread_cond_broadcast(&cond);
    }

    bool waitForSeconds(int sec){
        struct timespec abstime;
        clock_gettime(CLOCK_REALTIME, &abstime);
        abstime.tv_sec += static_cast<time_t>(sec);
        return ETIMEDOUT == pthread_cond_timedwait(&cond, mutex.get(), &abstime);
    }
private:
    MutexLock &mutex;
    pthread_cond_t cond;
};
    
} // namespace fuyou


#endif