#include "Tcpconn.h"
#include "Epoll.h"
#include <memory>
namespace fuyou
{
const __uint32_t DEFAULT_EVENT = EPOLLIN | EPOLLPRI | EPOLLRDHUP;
const int DEFAULT_EXPIRED_TIME = 2000;  
const int KEEP_CONN_TIME = 5 * 60 * 1000;
Tcpconn::Tcpconn(EventLoop* loop, int connfd):
                _loop(loop),
                _connfd(connfd),
                _channel(new Channel(loop, connfd)){
    _channel -> setReadHandler(bind(&Tcpconn::handleRead, this));
    _channel -> setWriteHandler(bind(&Tcpconn::handleWrite, this));
    _channel -> setConnHandler(bind(&Tcpconn::handleConn, this));
}

Tcpconn::~Tcpconn(){
    LOG << "TCP closed";
}

void Tcpconn::handleRead(){
    __uint32_t &events = _channel -> getEvents();
    bool isClose = false;
    bool isEnd = false;
    do{
        bool zero = false;
        int readBytes = readn(_connfd, _inbuffer, zero);
       
        if(readBytes > 0){
            LOG << "New Msg :" << _inbuffer; 

            handleWrite();
        }
        else if(readBytes < 0){
            perror("read error");
            handleError(_connfd, 400, "Bad req");
        }
        else if(zero){
            handleClose();
        }   

    }while(false);
}

void Tcpconn::handleWrite(){
    if(!_error){
        __uint32_t &_events = _channel -> getEvents();
        LOG << "handle Write: " << _events;
        int writeBytes = 0;
        if((writeBytes = writen(_connfd, _outbuffer)) < 0){
            perror("writen error");
            _events = 0;
            _error = true;
        }
        else if(_outbuffer.size() > 0){
            _events |= EPOLLOUT;
            LOG << "write " << writeBytes << " data";
            _channel -> setEvents(_events);
            _poller -> epollMod(_channel, 0);
        }
    }
}

void Tcpconn::newEvent(){
    _channel -> setEvents(DEFAULT_EVENT);
    _loop -> addPoller(_channel, DEFAULT_EXPIRED_TIME);
}

void Tcpconn::handleConn(){
    LOG << "handling connection";
    __uint32_t& _events = _channel -> getEvents();
    if(_events & EPOLLOUT){
        LOG << "Handleconn event detects: EPOLLOUT";
    }
    else if(_events & EPOLLIN){
        LOG << "Handleconn event detects: EPOLLIN";
    }
    // _events |= (EPOLLIN | EPOLLET);
    // int timeout = KEEP_CONN_TIME;
    // _loop -> updatePoller(_channel, timeout);
}
void Tcpconn::handleError(int fd, int err_num, std::string msg){
    LOG << "Doing Handle Error";
}

void Tcpconn::handleClose(){
    LOG << "begin to close";
    std::shared_ptr<Tcpconn> guard(shared_from_this());
    _loop -> removeFromPoller(_channel);
    close(_channel -> getfd());
}

AnalysisState Tcpconn::parseHeader(){
    string &str = _inbuffer;
    atomic<bool> isEnd(false);
    size_t i = 0;
    for( ; i < str.size(); ++ i){
        
    }

}
} // namespace fuyou
