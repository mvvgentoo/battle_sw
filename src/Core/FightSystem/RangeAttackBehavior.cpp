#include "RangeAttackBehavior.hpp"

RangeAttackBehavior::RangeAttackBehavior(std::shared_ptr<RangeAttackData> data)
    : _data(std::move(data)) {}

int RangeAttackBehavior::getPriority() const
{
    return _data->priority;
}
