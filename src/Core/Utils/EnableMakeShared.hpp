#ifndef ENABLEMAKESHARED_HPP
#define ENABLEMAKESHARED_HPP

#include <memory>
#include <utility>

template <typename T>
class EnableMakeShared : public T
{
public:
    template<typename... Args>
    EnableMakeShared(Args&&... args)
        : T(std::forward<Args>(args)...) {}

    template<typename ...Arg>
    std::shared_ptr<T> static createSharedPtrInternal(Arg&&...arg)
    {
        return std::make_shared<EnableMakeShared<T>>(std::forward<Arg>(arg)...);
    }
};

#endif // ENABLEMAKESHARED_HPP
