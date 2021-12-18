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
        LOG << "Another EventLoop " << t_loopInthisThread << " exists in this thread " << _threadId;
    }
    else{
        t_loopInthisThread = this;
    }

    _pwakeupChannel -> setEvents(EPOLLIN | EPOLLET);
    _pwakeupChannel -> setReadHandler(bind(&EventLoop::handleRead, this));
    _pwakeupChannel -> setConnHandler(bind(&EventLoop::handleConn, this));
    _poller -> epollAdd(_pwakeupChannel, 0);
}

void EventLoop::handleConn(){
    updatePoller(_pwakeupChannel, 0);
}

EventLoop::~EventLoop(){
    close(_wakeupfd);
    t_loopInthisThread = nullptr;
}

void EventLoop::wakeup(){
    uint64_t one = 1;
    ssize_t n = writen(_wakeupfd, (char*)one, sizeof(one));
    if(n != sizeof(one)){
        LOG << "EventLoop::wakeup() writes " << n << " bytes instead of 8";
    }
}

void EventLoop::handleRead(){
    uint64_t one = 1;
    ssize_t n = readn(_wakeupfd, &one, sizeof one);
    if (n != sizeof one) {
        LOG << "EventLoop::handleRead() reads " << n << " bytes instead of 8";
    }
    _pwakeupChannel -> setEvents(EPOLLIN | EPOLLET);
}

void EventLoop::runInLoop(Functor&& cb){
    if(isRunInLoop){
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
        wakeup();
    }
}
    
} // namespace fuyou


