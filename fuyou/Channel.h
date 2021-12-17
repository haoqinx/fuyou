#ifndef _CHANNEL_H
#define _CHANNEL_H

namespace fuyou
{
class EventLoop;
class HttpData;
class Channel{
public:
    Channel();
    ~Channel();
    int getfd();
private:
    int fd
};
} // namespace fuyou



#endif