#include "Tcpconn.h"

namespace fuyou
{
Tcpconn::Tcpconn(EventLoop* loop, int connfd):
                _loop(loop),
                _connfd(connfd),
                _channel(new Channel(loop, connfd)){
    _channel -> setReadHandler(bind(&Tcpconn::handleRead, this));
    _channel -> setWriteHandler(bind(&Tcpconn::handleWrite, this));
    _channel -> setConnHandler(bind(Tcpconn::handleConn, this));
    
}

void Tcpconn::handleRead(){
    __uint32_t &events = _channel -> getEvents();
    do{
        bool zero = false;
        int readBytes = readn(_connfd, _inbuffer, zero);
        LOG << "New Msg :" << _inbuffer; 
    }while(false);
}
} // namespace fuyou
