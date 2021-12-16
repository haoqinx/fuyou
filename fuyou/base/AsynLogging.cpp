#include "AsynLogging.h"
#include "CountDownLatch.h"
#include <assert.h>
#include <iostream>
namespace fuyou
{

AsynLogging::AsynLogging(const std::string filename, int timeInterval)
                :timeInterval(timeInterval),
                isRunning(false),
                filename(filename),
                thread(std::bind(&AsynLogging::threadFunc, this), "logging"),
                mutex(),
                cond(mutex),
                currentBuffer(new LargeBuffer),
                nextBuffer(new LargeBuffer),
                buffers(),
                latch(1)
                {
    assert(filename.size() > 1);
    currentBuffer -> clear();
    nextBuffer -> clear();
    buffers.reserve(16);

}

void AsynLogging::threadFunc(){
    assert(isRunning == true);
    latch.countDown();
    Filelog output(filename);
    BufferPtr tmpBuffer1(new LargeBuffer());
    BufferPtr tmpBuffer2(new LargeBuffer());
    tmpBuffer1 -> clear();
    tmpBuffer2 -> clear();

    BufferVec bufferTowrite;
    bufferTowrite.reserve(16);

    while(isRunning){
        assert(tmpBuffer1 != nullptr);
        assert(tmpBuffer1 -> getLen() == 0);
        assert(tmpBuffer2 != nullptr);
        assert(tmpBuffer2 -> getLen() == 0);
        assert(bufferTowrite.empty());
        {
            MutexLockGuard lock(mutex);
            if(buffers.empty()){
                cond.waitForSeconds(timeInterval);
            }
            buffers.push_back(currentBuffer);
            currentBuffer.reset();

            currentBuffer = std::move(tmpBuffer1);
            bufferTowrite.swap(buffers);

            if(!nextBuffer){
                nextBuffer = std::move(tmpBuffer2);
            }

            assert(! bufferTowrite.empty());

            if(bufferTowrite.size() > 25){
                bufferTowrite.erase(bufferTowrite.begin() + 2, bufferTowrite.end());
            }
            for(size_t i = 0; i < bufferTowrite.size(); ++ i){
                output.append(bufferTowrite[i] -> getData(), bufferTowrite[i] -> getLen());
            }

            if(bufferTowrite.size() > 2){
                bufferTowrite.resize(2);
            }
            if(!tmpBuffer1){
                assert(!bufferTowrite.empty());
                tmpBuffer1 = bufferTowrite.back();
                bufferTowrite.pop_back();
                tmpBuffer1 -> reset();
            }

            if(!tmpBuffer2){
                assert(!bufferTowrite.empty());
                tmpBuffer2 = bufferTowrite.back();
                bufferTowrite.pop_back();
                tmpBuffer2 -> reset();
            }

            bufferTowrite.clear();
            output.flush();

        } 

        output.flush();
    }

}

void AsynLogging::append(const char* line, int len){
    MutexLockGuard lock(mutex);
    if(currentBuffer->getLeft() > len){
        currentBuffer -> append(line, len);
    }
    else{
        buffers.push_back(currentBuffer);
        currentBuffer.reset();
        if(nextBuffer){
            currentBuffer = std::move(nextBuffer);
        }
        else{
            currentBuffer.reset(new LargeBuffer);
        }
        currentBuffer -> append(line, len);
        cond.notify();
    }
}

} // namespace fuyou
