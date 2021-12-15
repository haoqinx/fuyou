#ifndef _COUNTDOWNLATCH_H
#define _COUNTDOWNLATCH_H
#include "MutexLock.h"
#include "nonecopyable.h"
#include "Condition.h"

namespace fuyou
{
class CountDownLatch:nonecopyable{
public:
    explicit CountDownLatch(int count):count(count),mutex(),cond(mutex){
    
    }
    ~CountDownLatch()=default;
    void wait(){
        MutexLockGuard lock(mutex);
        while(count > 0) cond.wait();
    }
    void countDown(){
        MutexLockGuard lock(mutex);
        if(-- count == 0){
            cond.notifyAll();
        }
    }
private:
    int count;
    mutable MutexLock mutex;
    Condition cond;
    
};
} // namespace fuyou



#endif