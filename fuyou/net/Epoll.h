#ifndef _EPOLL_H
#define _EPOLL_H
#include "Channel.h"
#include "Timer.h"
#include <vector>
#include <memory>
#include <iostream>
namespace fuyou
{

class Epoll{
public:
    Epoll();
    ~Epoll();
    void epollAdd(SP_Channel req, int timeout);
    void epollMod(SP_Channel req, int timeout);
    void epollDel(SP_Channel req);
    void handleExpired();
    std::vector<std::shared_ptr<Channel>> poll();
    std::vector<std::shared_ptr<Channel>> getEventRequests(int eventsNum);
    void addTimer(std::shared_ptr<Channel> reqData, int timeout);
    int getEpollfd(){
        return _epollfd;
    }
private:
    static const int MAXFDS = 100000;
    int _epollfd;
    std::vector<epoll_event> events;
    std::shared_ptr<Channel> fdToChannel[MAXFDS];
    std::shared_ptr<Tcpconn> fdToHttp[MAXFDS];
    TimerManager _timerManager;
};
} // namespace fuyou


#endif