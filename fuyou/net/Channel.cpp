#include "Channel.h"
namespace fuyou
{
Channel::Channel(EventLoop* lp):_loop(lp),events(0),lastEvents(0),fd(0){
}

Channel::Channel(EventLoop* lp, int fd):_loop(lp), fd(fd), events(0),lastEvents(0){

}

Channel::~Channel(){
    LOG << "Delete Channel";
}

int Channel::getfd(){
    return fd;
}
void Channel::setfd(int fd_){
    fd = fd_;
}

void Channel::handleRead(){
    if(readHandler){
        readHandler();
    }
}

void Channel::handleWrite(){
    if(writeHandler){
        writeHandler();
    }
}
void Channel::handleConn(){
    if(connHandler){
        connHandler();
    }
}
} // namespace fuyou
