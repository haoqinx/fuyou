#ifndef _EVENTLOOP_THREAD_H
#define _EVENTLOOP_THREAD_H
#include "base/nocopyable.hpp"
#include "EventLoop.h"
#include "base/Thread.h"
#include "base/MutexLock.h"
#include "base/Condition.h"
namespace fuyou
{
class EventLoopThread : noncopyable{
public:
    EventLoopThread();
    ~EventLoopThread();
    EventLoop* startloop();

private:
    void threadFunc();
    EventLoop* _loop;
    bool _exiting;
    Thread _thread;
    MutexLock _mutex;
    Condition _cond;
};
} // namespace fuyou


#endif