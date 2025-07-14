#include "CombatSystem.hpp"
#include "Core/World/IWorldContext.hpp"
#include "Core/Entity/Entity.hpp"
#include "Core/Services/HealthService.hpp"
#include "IO/Events/UnitAttacked.hpp"

#include "Core/Systems/EntityManager.hpp"
#include "Core/Systems/EventManager.hpp"

CombatSystem::CombatSystem() : _worldContext()
{

}

CombatSystem::CombatSystem(std::shared_ptr<IWorldContext> worldCtx) : _worldContext(worldCtx)
{

}

CombatSystem::~CombatSystem()
{

}

void CombatSystem::setContext(std::shared_ptr<IWorldContext> worldCtx)
{
    _worldContext = worldCtx;
}

void CombatSystem::dealDamageNow(const DamageEvent &evt)
{
    if (auto worldCtx = _worldContext.lock())
    {
        const auto& entityManager = worldCtx->getEntityManager();
        if (auto targetEntity = entityManager.getEntityByID(evt.target).lock())
        {
            if (auto healthSrv = targetEntity->getServiceByType<HealthService>() )
            {
                int hpBefore = healthSrv->getCurrentHP();
                healthSrv->applyDamage(evt.damage);

                worldCtx->getEventManager().emit(sw::io::UnitAttacked{
                    evt.attacker,
                    evt.target,
                    static_cast<uint32_t>(evt.damage),
                    static_cast<uint32_t>(hpBefore)
                });
            }
        }
    }
}
