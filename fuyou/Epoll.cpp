#include "Epoll.h"
#include <assert.h>
#include "base/Logger.h"
namespace fuyou
{
const int EVENTSNUM = 4096;
const int EPOLLWAIT_TIME = 10000;

Epoll::Epoll():_epollfd(epoll_create1(EPOLL_CLOEXEC)),
                events(EVENTSNUM){
    assert(_epollfd > 0);
}
Epoll::~Epoll(){}

void Epoll::epollAdd(SP_Channel req, int timeout){
    int fd = req -> getfd();
    if(timeout > 0){
        addTimer(req, timeout);
        fdToHttp[fd] = req -> getHolder();
    }
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = req -> getEvents();
    req -> equalAndUpdatelastEvents();
    fdToChannel[fd] = req;

    if(epoll_ctl(_epollfd, EPOLL_CTL_ADD, fd, &ev) < 0){
        perror("epoll add error");
        fdToChannel[fd].reset();
    }
}

void Epoll::epollMod(SP_Channel req, int timeout){
    if(timeout > 0) addTimer(req, timeout);
    int fd = req -> getfd();
    if(!req -> equalAndUpdatelastEvents()){
        struct epoll_event ev;
        ev.data.fd = fd;
        ev.events = req -> getEvents();
        if(epoll_ctl(_epollfd, EPOLL_CTL_MOD, fd, & ev) < 0){
            perror("epoll mod error");
            fdToChannel[fd].reset();
        }
    }
}
    
void Epoll::epollDel(SP_Channel req){
    int fd = req -> getfd();
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = req -> getLastEvents();

    if(epoll_ctl(_epollfd, EPOLL_CTL_DEL, fd, &ev) < 0){
        perror("epoll del error");
    }
    fdToChannel[fd].reset();
    fdToHttp[fd].reset();
}

std::vector<SP_Channel> Epoll::poll(){
    while(true){
        int ev_cnt = epoll_wait(_epollfd, &*events.begin(), events.size(), EPOLLWAIT_TIME);
        if(ev_cnt < 0) perror("epoll wait error");
        std::vector<SP_Channel> reqdata = getEventRequests(ev_cnt);
        if(reqdata.size() > 0) return reqdata;
    }
}

void Epoll::handleExpired(){
    _timerManager.handleExpiredEvent();
}

std::vector<SP_Channel> Epoll::getEventRequests(int eventNum){
    std::vector<SP_Channel> reqdata;
    for(int i = 0; i < eventNum; ++ i){
        int fd = events[i].data.fd;
        SP_Channel curReq = fdToChannel[fd];
        if(curReq){
            curReq -> setRevents(events[i].events);
            curReq -> setEvents(0);
            reqdata.push_back(curReq);
        }
        else{
            LOG << "SP cur_req is invalid";
        }
    }
    return reqdata;
}

void Epoll::addTimer(SP_Channel reqdata, int timeout){
    std::shared_ptr<HttpData> t = reqdata->getHolder();
    if (t){
        _timerManager.addTimer(t, timeout);
    }
    else{
        LOG << "timer add fail";
    }
}

} // namespace fuyou
