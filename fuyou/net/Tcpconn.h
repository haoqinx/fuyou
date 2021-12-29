#ifndef __TCPCONN_H
#define __TCPCONN_H

#include "../base/Logger.h"
#include "Channel.h"
#include "Epoll.h"
#include "Timer.h"
#include "Util.h"
#include "EventLoop.h"
#include "Httpdata.h"
#include <memory>
#include <atomic>

namespace fuyou
{

class Tcpconn : public std::enable_shared_from_this<Tcpconn>{
public:
    Tcpconn(EventLoop* loop, int connfd);
    ~Tcpconn();
    std::shared_ptr<Channel> getChannel(){
        return _channel;
    }
    EventLoop* getLoop(){
        return _loop;
    }
    void handleClose();
    void newEvent();
    
    void handleRead();
    void handleWrite();
    void handleConn();
    void handleError(int fd, int err_num, std::string msg);

    AnalysisState parseHeader();
    void setHeader();
private:
    EventLoop* _loop;
    int _connfd;
    std::shared_ptr<Epoll> _poller;
    std::shared_ptr<Channel> _channel;
    std::weak_ptr<TimerNode> _timer;
    std::string _inbuffer;
    std::string _outbuffer;
    atomic<bool> _error;
    
    std::shared_ptr<Httpdata> _httpdata;
    atomic<bool> _isparsingHeader;
     

};
} // namespace fuyou


#endif