#ifndef _EVENTLOOP_H
#define _EVENTLOOP_H
#include <functional>
#include "base/Thread.h"
#include "Channel.h"
#include "Util.h"

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
    void shutdown(shared_ptr<Channel>channel){
        shutdownWrite()
    }

private:
    const pid_t _threadId;
};
} // namespace fuyou



#endif