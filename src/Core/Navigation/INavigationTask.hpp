#ifndef INAVIGATIONTASK_HPP
#define INAVIGATIONTASK_HPP

#include "Core/Utils/BaseTypes.hpp"

class INavigationTask
{
public:
    virtual ~INavigationTask() = default;

    virtual const Position& getTarget() const = 0;
    virtual bool isReached(const Position& current) const = 0;
};


#endif // INAVIGATIONTASK_HPP
