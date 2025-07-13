#ifndef COMBATSYSTEM_HPP
#define COMBATSYSTEM_HPP

#include <memory>
#include "Core/Utils/BaseTypes.hpp"

class World;

struct DamageEvent
{
    EntityID attacker;
    EntityID target;
    int damage;
};

class CombatSystem
{
public:
    CombatSystem(std::shared_ptr<World> world);
    ~CombatSystem();

    void dealDamageNow(const DamageEvent& evt);
private:
    std::weak_ptr<World> _world;
};


#endif // COMBATSYSTEM_HPP
