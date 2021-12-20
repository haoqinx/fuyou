#ifndef _SERVER_H
#define _SERVER_H
#include "EventLoop.h"
#include "EventLoopThreadPool.h"
#include "Channel.h"
#include <memory>
namespace fuyou
{
class Server{
public:
    Server(EventLoop* loop, int threadNum, int port);
    ~Server(){}
    EventLoop* getLoop()const{
        return _loop;
    }
    void start();
    void handleNewConn();
    void handleCurrentConn(){
        _loop -> updatePoller(_acceptChannel);
    }

private:
    EventLoop* _loop;
    int _numThreads;
    std::unique_ptr<EventLoopThreadPool> _eventLoopThreadPool;
    bool _started;
    std::shared_ptr<Channel> _acceptChannel;
    int _port;
    int _listenfd;
    static const int MAXFDS = 100000;

};
} // namespace fuyou

#endif