#ifndef _TIMER_H
#define _TIMER_H
#include <memory>

namespace fuyou
{
class  HttpData; 

class TimerManager{
public:
    TimerManager();
    ~TimerManager();
    void handleExpiredEvent();
    void addTimer(std::shared_ptr<HttpData> SPHttpData, int timeout);
};
} // namespace fuyou


#endif