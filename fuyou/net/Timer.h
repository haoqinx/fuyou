#ifndef _TIMER_H
#define _TIMER_H
#include <memory>
#include <queue>

namespace fuyou
{
class  Tcpconn; 

class TimerNode{
public:
    TimerNode(std::shared_ptr<Tcpconn>reqdata, int timeout);
    ~TimerNode();

    TimerNode(TimerNode& tn);
    void update(int timeout);
    bool isVaild();
    void clearReq();
    void setDeleted(){
        _deleted = true;
    }
    bool isDeleted() const {
        return _deleted;
    }
    size_t getExpTime()const{
        return _expiredTime;
    }
private:
    bool _deleted;
    size_t _expiredTime;
    std::shared_ptr<Tcpconn> SP_HttpData;
};
struct TimerCmp{
    bool operator()(std::shared_ptr<TimerNode>& t1, std::shared_ptr<TimerNode>& t2){
        return t1 -> getExpTime() > t2 -> getExpTime();
    }
};
class TimerManager{
public:
    TimerManager();
    ~TimerManager();
    void handleExpiredEvent();
    void addTimer(std::shared_ptr<Tcpconn> SPHttpData, int timeout);

private:
    typedef std::shared_ptr<TimerNode> SP_TimeNode;
    std::priority_queue<SP_TimeNode,std::deque<SP_TimeNode>, TimerCmp> timeNodeQueue;


};
} // namespace fuyou


#endif