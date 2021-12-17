#ifndef _CHANNEL_H
#define _CHANNEL_H
#include <sys/epoll.h>
#include <memory>
#include <string>
#include <functional>
namespace fuyou
{
class EventLoop;
class HttpData;
class Channel{
public:
    typedef std::function<void()> CallBack;
    Channel(EventLoop*, int fd);
    Channel(EventLoop*);
    ~Channel();
    int getfd();
    void setfd(int fd);

    void setHolder(std::shared_ptr<HttpData> holder){
        holder_ = holder;
    }

    std::shared_ptr<HttpData> getHolder(){
        std::shared_ptr<HttpData> ret(holder_.lock());
        return ret;
    }

    void setReadHandler(CallBack&& rh){
        readHandler = rh;
    }
    
    void setWriteHandler(CallBack&& wh){
        writeHandler = wh;
    }

    void setErrorHandler(CallBack&& eh){
        errorHandler = eh;
    }

    void setConnHandler(CallBack&& ch){
        connHandler = ch;
    }
    void handleEvents (){
        events = 0;
        if((revents & EPOLLHUP) && !(revents & EPOLLIN)){
            events = 0;
            return;
        }
        if(revents & EPOLLERR){
            if(errorHandler) errorHandler();
            events = 0;
            return;
        }

        if(revents & (EPOLLIN | EPOLLPRI | EPOLLRDHUP)){
            handleRead();
        }

        if(revents & (EPOLLOUT)){
            handleWrite();
        }

        handleConn();
    }
    void handleRead();
    void handleWrite();
    void handleConn();

    void setRevents(__uint32_t ev){
        revents = ev;
    }

    void setEvents(__uint32_t ev){
        events = ev;
    }

    __uint32_t& getEvents(){
        return events;
    }

    bool equalAndUpdatelastEvents(){
         bool ret = (lastEvents == events);
        lastEvents = events;
        return ret;
    }

    __uint32_t getLastEvents(){
        return lastEvents;
    }
private:
    
    int fd;
    EventLoop* _loop;
    __uint32_t events;
    __uint32_t revents;
    __uint32_t lastEvents;

    std::weak_ptr<HttpData> holder_;
    CallBack readHandler;
    CallBack writeHandler;
    CallBack errorHandler;
    CallBack connHandler;
};

typedef std::shared_ptr<Channel> SP_Channel;
} // namespace fuyou



#endif