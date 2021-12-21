#include "Tcpconn.h"
#include "Epoll.h"
namespace fuyou
{
const __uint32_t DEFAULT_EVENT = EPOLLIN | EPOLLET | EPOLLONESHOT;
const int DEFAULT_EXPIRED_TIME = 2000;  

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
    do{
        bool zero = false;
        int readBytes = readn(_connfd, _inbuffer, zero);
        LOG << "New Msg :" << _inbuffer; 
        _inbuffer.clear();
        if(readBytes < 0){
            perror("read error");
            handleError(_connfd, 400, "Bad req");
        }
        else if(zero){

        }

    }while(false);
    if(!_error){
        if(_outbuffer.size() > 0){
            handleWrite();
        }
    }

}

void Tcpconn::handleWrite(){
    if(!_error){
        __uint32_t &_events = _channel -> getEvents();
        if(writen(_connfd, _outbuffer) < 0){
            perror("writen");
            _events = 0;
            _error = true;
        }
        if(_outbuffer.size() > 0){
            _events |= EPOLLOUT;
        }
    }
}

void Tcpconn::newEvent(){
    _channel -> setEvents(DEFAULT_EVENT);
    _loop -> addPoller(_channel, DEFAULT_EXPIRED_TIME);
}

void Tcpconn::handleConn(){
    LOG << "enter hanleconn";
}
void Tcpconn::handleError(int fd, int err_num, std::string msg){

}
} // namespace fuyou
