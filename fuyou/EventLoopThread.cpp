#include "EventLoopThread.h"

namespace fuyou
{
EventLoopThread::EventLoopThread():_loop(nullptr),
                                    _exiting(false),
                                    _thread(bind(&EventLoopThread::threadFunc,this), "EventLoopThread"),
                                    _mutex(),
                                    _cond(_mutex){

}

EventLoopThread::~EventLoopThread(){
    _exiting = true;
    if(_loop != nullptr){
        _loop -> quit();
        _thread.join();
    }
}

EventLoop* EventLoopThread::startloop(){
    assert(!_thread.started());
    _thread.start();
    {
        MutexLockGuard lock(_mutex);
        while(_loop == nullptr){
            _cond.wait();
        }
    }
    return _loop;
}

void EventLoopThread::threadFunc(){
    EventLoop loop;
    {
        MutexLockGuard lock(_mutex);
        _loop = &loop;
        _cond.notify();
    }
    _loop -> loop();
    _loop = nullptr;
}
} // namespace fuyou
