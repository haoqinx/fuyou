#include "EventLoopThreadPool.h"

namespace fuyou
{
EventLoopThreadPool::EventLoopThreadPool(EventLoop*loop, int numThreads)
                                        :_mainLoop(loop),
                                        _started(false),
                                        _numThreads(numThreads){
    if(_numThreads <= 0){
        LOG << "invalid numThreads : " << numThreads << " < 0";
        abort();
    }
}

void EventLoopThreadPool::start(){
    _mainLoop -> assertInLoopThread();
    _started = true;
    for(int i = 0; i < _numThreads; ++ i){
        SP_LoopThread tmp(new EventLoopThread());
        _threads.push_back(tmp);
        _loops.push_back(tmp -> startloop());
    }
}

EventLoop* EventLoopThreadPool::getNextLoop(){
    _mainLoop -> assertInLoopThread();
    assert(_started);
    EventLoop* loop = _mainLoop;
    if(! _loops.empty()){
        loop = _loops[_next];
        _next = (_next + 1) % _numThreads;
    }
    return loop;
}
} // namespace fuyou
