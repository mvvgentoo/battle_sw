#include "CombatSystem.hpp"

#include "Core/Entity/Entity.hpp"
#include "Core/Services/HealthService.hpp"
#include "Core/Systems/EntityManager.hpp"
#include "Core/Systems/EventManager.hpp"
#include "Core/World/IWorldContext.hpp"
#include "IO/Events/UnitAttacked.hpp"

CombatSystem::CombatSystem() :
		_worldContext()
{}

CombatSystem::~CombatSystem() {}

void CombatSystem::dealDamageNow(const DamageEvent& evt, const IWorldContext& worldCtx) const
{
	const auto& entityManager = worldCtx.getEntityManager();
	if (auto targetEntity = entityManager.getEntityByID(evt.target).lock())
	{
		if (auto healthSrv = targetEntity->getServiceByType<HealthService>())
		{
			int hpBefore = healthSrv->getCurrentHP();

			worldCtx.getEventManager().emit(sw::io::UnitAttacked{
				evt.attacker, evt.target, static_cast<uint32_t>(evt.damage), static_cast<uint32_t>(hpBefore)});

			healthSrv->applyDamage(evt.damage);
		}
	}
}
