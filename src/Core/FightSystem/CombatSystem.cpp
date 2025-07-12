#include "CombatSystem.hpp"
#include "Core/World.hpp"
#include "Core/Entity/Entity.hpp"
#include "Core/Services/HealthService.hpp"
#include "IO/Events/UnitAttacked.hpp"

CombatSystem::CombatSystem(std::shared_ptr<World> world) : _world(world)
{

}

CombatSystem::~CombatSystem()
{

}

void CombatSystem::dealDamageNow(const DamageEvent &evt)
{
    if (auto world = _world.lock())
    {
        if (auto targetEntity = world->getEntityByID(evt.target).lock())
        {
            if (auto healthSrv = targetEntity->getServiceByType<HealthService>() )
            {
                int hpBefore = healthSrv->getCurrentHP();
                healthSrv->applyDamage(evt.damage);

                world->emit(sw::io::UnitAttacked{
                    evt.attacker,
                    evt.target,
                    static_cast<uint32_t>(evt.damage),
                    static_cast<uint32_t>(hpBefore)
                });
            }
        }
    }
}
