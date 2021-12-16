#ifndef _ASYN_LOG_H
#define _ASYN_LOG_H
#include "MutexLock.h"
#include "nonecopyable.h"
#include "Thread.h"
#include "Condition.h"
#include "Logstream.h"
#include "CountDownLatch.h"
#include "Filelog.h"
#include <functional>
#include <vector>

namespace fuyou
{
class AsynLogging : nonecopyable{
public:
    AsynLogging(const std::string filename, int timeInterval = 2);
    ~AsynLogging(){
        if(isRunning){
            stop();
        }
    }
    void append(const char* line, int len);
    void start(){
        isRunning = true;
        thread.start();
        latch.wait();
    }
    void stop(){
        isRunning = false;
        cond.notify();
        thread.join();
    }

private: 
    typedef Logbuf<LARGE_BUF_SIZE> LargeBuffer;
    typedef std::vector<std::shared_ptr<LargeBuffer>> BufferVec;
    typedef std::shared_ptr<LargeBuffer> BufferPtr;

    const int timeInterval;
    void threadFunc();
    std::string filename;
    bool isRunning;
    Thread thread;
    MutexLock mutex;
    Condition cond;
    BufferPtr currentBuffer;
    BufferPtr nextBuffer;
    BufferVec buffers;
    CountDownLatch latch;
   

};
    
} // namespace fuyou

#endif