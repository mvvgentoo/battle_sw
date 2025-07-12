#include "MeleeAttackBehavior.hpp"

MeleeAttackBehavior::MeleeAttackBehavior(std::shared_ptr<MeleeAttackData> data)
    : _data(std::move(data)) {}

int MeleeAttackBehavior::getPriority() const
{
    return _data->priority;
}
