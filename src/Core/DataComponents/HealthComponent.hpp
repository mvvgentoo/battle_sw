#ifndef HEALTHCOMPONENT_HPP
#define HEALTHCOMPONENT_HPP

#include "Core/BaseTypes.hpp"

struct HealthComponent : public IDataComponent
{
    int hpMax = 10;
    int currentHP = 1;
    bool isDead = false;
};

#endif // HEALTHCOMPONENT_HPP
