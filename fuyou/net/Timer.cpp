#include "Timer.h"
#include <sys/time.h>

namespace fuyou
{
TimerNode::TimerNode(std::shared_ptr<Tcpconn> reqdata, int timeout)
                    :_deleted(false),
                    SP_HttpData(reqdata){
    struct timeval now;
    gettimeofday(&now, nullptr);
    _expiredTime = (((now.tv_sec % 10000) * 1000) + (now.tv_usec / 1000)) + timeout;

}

TimerNode::TimerNode(TimerNode& tn)
                    :SP_HttpData(tn.SP_HttpData),
                    _expiredTime(0){

}

TimerNode::~TimerNode(){
    if(SP_HttpData){
        // SP_HttpData -> handleClose();
    }
}

void TimerNode::update(int timeout){
    struct timeval now;
    gettimeofday(&now, nullptr);
    _expiredTime = (((now.tv_sec % 10000) * 1000) + (now.tv_usec / 1000)) + timeout;
}

bool TimerNode::isVaild(){
    struct timeval now;
    gettimeofday(&now, nullptr);
    size_t tmp = (((now.tv_sec % 10000) * 1000) + (now.tv_usec / 1000));
    if(tmp > _expiredTime){
        setDeleted();
        return false;
    }
    else{
        return true;
    }
}

void TimerNode::clearReq(){
    SP_HttpData.reset();
    setDeleted();
}



TimerManager::TimerManager(){

}

TimerManager::~TimerManager(){
    
}

void TimerManager::handleExpiredEvent(){
    while(!timeNodeQueue.empty()){
        SP_TimeNode node = timeNodeQueue.top();
        if(node -> isDeleted()){
            timeNodeQueue.pop();
        }
        else if(! node -> isVaild()){
            timeNodeQueue.pop();
        }
        else break;
    }
}

void TimerManager::addTimer(std::shared_ptr<Tcpconn> SPHttpData, int timeout){
    SP_TimeNode newNode(new TimerNode(SPHttpData, timeout));
    timeNodeQueue.push(newNode);
    // SPHttpData -> linkTimer(newNode);   
}

    
} // namespace fuyou
