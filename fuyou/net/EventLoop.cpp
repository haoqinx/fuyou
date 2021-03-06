#include "EventLoop.h"
#include <sys/eventfd.h>
namespace fuyou
{

__thread EventLoop* t_loopInthisThread = 0;
int createEventfd(){
    int fd = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    if(fd < 0){
        LOG << "Failed create eventfd";
        abort();
    }
    return fd;
}

EventLoop::EventLoop():_looping(false),
                        _poller(new Epoll()),
                        _wakeupfd(createEventfd()),
                        _quit(false),
                        _eventHandling(false),
                        _callingPendingFunctors(false),
                        _threadId(CurrentThread::tid()),
                        _pwakeupChannel(new Channel(this, _wakeupfd)){
    if(t_loopInthisThread){
        LOG << "Another EventLoop " << t_loopInthisThread->_threadId << " exists in this thread " << _threadId;
    }
    else{
        t_loopInthisThread = this;
    }

    _pwakeupChannel -> setEvents(EPOLLIN | EPOLLPRI | EPOLLRDHUP);
    _pwakeupChannel -> setReadHandler(bind(&EventLoop::handleRead, this));
    _pwakeupChannel -> setConnHandler(bind(&EventLoop::handleConn, this));
    _poller -> epollAdd(_pwakeupChannel, 0);
}

void EventLoop::handleConn(){
    // ET mode
    // updatePoller(_pwakeupChannel);
    LOG << "Entering wakeup channel... ";
}

EventLoop::~EventLoop(){
    LOG << "Delete EventLoop";
    close(_wakeupfd);
    t_loopInthisThread = nullptr;
}

void EventLoop::wakeup(){
    uint64_t one = 1;
    ssize_t n = writen(_wakeupfd, (char*)&one, sizeof(one));
    LOG << "Wakeup " << _wakeupfd;
    if(n != sizeof(one)){
        LOG << "wakeupfd is " << _wakeupfd;
        LOG << "EventLoop::wakeup() writes " << n << " bytes instead of 8";
        abort();
    }
}

void EventLoop::handleRead(){
    uint64_t one = 1;
    ssize_t n = readn(_wakeupfd, &one, sizeof(one));
    if (n != sizeof(one)) {
        LOG << "EventLoop::handleRead() reads " << n << " bytes instead of 8";
    }
    else{
        LOG << "receive " << n << " bytes data";
    }
    // ET mod
    // _pwakeupChannel -> setEvents(EPOLLIN | EPOLLPRI | EPOLLRDHUP);
}

void EventLoop::runInLoop(Functor&& cb){
    if(isRunInLoop()){
        cb();
    }
    else{
        queueInLoop(std::move(cb));
    }
}

void EventLoop::queueInLoop(Functor&& cb){
    {
        MutexLockGuard lock(_mutex);
        _pendingFunctors.emplace_back(std::move(cb));
    }
    
    if(!isRunInLoop() || _callingPendingFunctors){
        LOG << "Not in right thread:" << "cur:" << CurrentThread::tid() << " vs " << "right: " << _threadId;
        wakeup();
    }
}

void EventLoop::loop(){
    assert(!_looping);
    assert(isRunInLoop());
    _looping = true;
    _quit = false;
    std::vector<SP_Channel> ret;
    while(!_quit){
        LOG << CurrentThread::tid() << " is running";
        ret.clear();
        ret = _poller -> poll();
        _eventHandling = true;
        for(auto& it : ret){
            it -> handleEvents();
        }
        _eventHandling = false;
        doPendingFunctors();
        _poller -> handleExpired();
    }
    _looping = true;
}

void EventLoop::doPendingFunctors(){
    std::vector<Functor> functors;
    _callingPendingFunctors = true;
    {
        MutexLockGuard lock(_mutex);
        functors.swap(_pendingFunctors);
    }
    for(size_t i = 0; i < functors.size(); ++ i){
        functors[i]();
    }
    _callingPendingFunctors = false;

}

void EventLoop::quit(){
    _quit = true;
    if(!isRunInLoop()){
        wakeup();
    }
}
    
} // namespace fuyou


