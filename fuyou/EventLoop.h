#ifndef _EVENTLOOP_H
#define _EVENTLOOP_H
#include <functional>
#include <assert.h>
#include "base/Thread.h"
#include "Channel.h"
#include "Util.h"
#include "Epoll.h"

namespace fuyou
{
class EventLoop{
public:
    typedef std::function<void()> Functor;
    EventLoop();
    ~EventLoop();

    void loop();
    void quit();
    void runInLoop(Functor&& cb);
    void queueInLoop(Functor&& cb);
    bool isRunInLoop()const {
        return _threadId == CurrentThread::tid();
    }
    void assertInLoopThread() {
        assert(isRunInLoop());
    }
    void shutdown(SP_Channel channel){
        shutdownWrite(channel -> getfd());
    }
    void removeFromPoller(SP_Channel channel){
        _poller -> epollDel(channel);
    }
    void updatePoller(SP_Channel channel, int timeout = 0){
        _poller -> epollMod(channel, timeout);
    }
    void addPoller(SP_Channel channel, int timeout = 0){
        _poller -> epollAdd(channel, timeout);
    }

private:
    const pid_t _threadId;
    bool _looping;
    bool _quit;
    bool _eventHandling;
    bool _callingPendingFunctors;
    int _wakeupfd;
    mutable MutexLock _mutex;
    std::vector<Functor> _pendingFunctors;
    SP_Channel _pwakeupChannel;
    std::shared_ptr<Epoll> _poller;

    void wakeup();
    void handleRead();
    void doPendingFunctors();
    void handleConn();

};
} // namespace fuyou



#endif