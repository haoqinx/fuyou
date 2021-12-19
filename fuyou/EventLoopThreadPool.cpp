#include "EventLoopThreadPool.h"

namespace fuyou
{
EventLoopThreadPool::EventLoopThreadPool(EventLoop*loop, int numThreads)
                                        :_mainLoop(loop),
                                        _started(false),
                                        _numThreads(numThreads){
    if(_numThreads <= 0){
        LOG << "invalid numThreads : " << numThreads << " < 0";
        abort();
    }
}

void EventLoopThreadPool::start(){

}
} // namespace fuyou
