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
#include <map>


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

    AnalysisState parseRequsets();
    URIState parseURI();
    HeaderState parseHeaders();
    void reset();
    void linkTimer(std::shared_ptr<TimerNode> timer){
        _timer = timer;
    }
    void seperateTimer(){
        if(_timer.lock()){
            std::shared_ptr<TimerNode> my_timer(_timer.lock());
            my_timer -> clearReq();
            _timer.reset();
        }
    }
private:
    EventLoop* _loop;
    int _connfd;
    std::shared_ptr<Epoll> _poller;
    std::shared_ptr<Channel> _channel;
    std::weak_ptr<TimerNode> _timer;
    std::string _inbuffer;
    std::string _outbuffer;
    atomic<bool> _error;
    
    // HTTP part
    //header
    HTTPopt _opt;
    std::string _filename;
    HTTPverion _version;
    //info
    std::string _userAgent;
    FileType _filetype;
    atomic<bool> _isKeepAlive;
    HTTPcharset _charset;
    HTTPencoding _encoding;
    //status
    ProcessState _pstate;
    ParseState _headerState;
    ConnectionState _connectionState;
    std::map<std::string, std::string> _headers;
    // read size
    int _nowReadPos;
    std::string _filepath;

};
} // namespace fuyou


#endif