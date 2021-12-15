#ifndef _NONECOPYABLE_H
#define _NONECOPYABLE_H

namespace fuyou
{
class nonecopyable{
public:
    typedef nonecopyable Self;
public:
    nonecopyable(){}
    ~nonecopyable(){}
    nonecopyable(const Self&) = delete;
    const Self& operator=(const Self&) = delete;

};
} // namespace fuyou

#endif