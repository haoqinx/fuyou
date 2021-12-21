#include "Server.h"
#include "Util.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <functional>
#include "../base/Logger.h"


namespace fuyou
{
Server::Server(EventLoop* loop, int numthread, int port)
                :_loop(loop),
                _numThreads(numthread),
                _eventLoopThreadPool(new EventLoopThreadPool(_loop, numthread)),
                _started(false),
                _acceptChannel(new Channel(_loop)),
                _port(port),
                _listenfd(socket_bind_listen(_port)){
    _acceptChannel -> setfd(_listenfd);
    //为了避免两次write造成进程关闭
    handle_for_sigpipe();
    if(setSocketNonBlocking(_listenfd) < 0){
        perror("set socket non block error");
        abort();
    }
}

void Server::start(){
    _eventLoopThreadPool -> start();
    _acceptChannel -> setEvents(EPOLLIN | EPOLLET);
    _acceptChannel -> setReadHandler(bind(&Server::handleNewConn, this));
    _acceptChannel -> setConnHandler(bind(&Server::handleCurrentConn, this));
    _loop -> addPoller(_acceptChannel, 0);
    _started = true;
}



void Server::handleNewConn(){
    struct sockaddr_in client_addr;
    memset(&client_addr, 0, sizeof(client_addr));
    socklen_t client_addr_len = sizeof(client_addr);
    int acceptfd = 0;
    while((acceptfd = accept(_listenfd, (struct sockaddr*)&client_addr, &client_addr_len)) > 0){
        EventLoop* loop = _eventLoopThreadPool -> getNextLoop();
        LOG << "New Conn from " << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port);
        if(acceptfd >= MAXFDS){
            close(acceptfd);
            continue;
        }

        if(setSocketNonBlocking(acceptfd) < 0){
            LOG << "set non block failed";
            return;
        }
        setSocketNodelay(acceptfd);

        std::shared_ptr<Tcpconn> conn(new Tcpconn(loop, acceptfd));
        conn -> getChannel() -> setHolder(conn);
        loop -> queueInLoop(std::bind(&Tcpconn::newEvent, conn));
    
    }   
    _acceptChannel -> setEvents(EPOLLIN | EPOLLET);
}
} // namespace fuyou
