#ifndef __EVENTLOOPTHREADPOOL_H
#define __EVENTLOOPTHREADPOOL_H
#include "../base/nonecopyable.h"
#include "EventLoop.h"
#include "EventLoopThread.h"
#include "../base/Logger.h"
#include <vector>
#include <memory>
namespace fuyou
{
class EventLoopThreadPool : nonecopyable{
public:
    EventLoopThreadPool(EventLoop* loop, int numThreads);
    ~EventLoopThreadPool(){
        LOG << "delete EventLoopThreadPool";
    };
    void start();
    EventLoop* getNextLoop();

private:
    typedef std::shared_ptr<EventLoopThread> SP_LoopThread;
    EventLoop* _mainLoop;
    bool _started;
    int _numThreads;
    int _next;

    std::vector<SP_LoopThread> _threads;
    std::vector<EventLoop*> _loops;

};
    
} // namespace fuyou
#endif