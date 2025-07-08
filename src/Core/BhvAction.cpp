#include "BhvAction.hpp"

#include "FightService.hpp"
#include "INavigationService.hpp"

MeleeAttackIfInRange::MeleeAttackIfInRange() {}

bool MeleeAttackIfInRange::execute(EntityHandle entityHandle)
{
	if (auto entity = entityHandle.lock())
	{
		if (auto fightSrv = entity->getServiceByType<FightService>())
		{
			auto targets = fightSrv->findMeleeTargets();
			return fightSrv->MeleeAttack(targets);
		}
	}

	return false;
}

NavigationAction::NavigationAction() {}

bool NavigationAction::execute(EntityHandle entityHandle)
{
	if (auto entity = entityHandle.lock())
	{
		auto navSrv = entity->getServiceByType<NavigationService>();
		if (navSrv)
		{
			if (!navSrv->hasCurrentNavTask())
			{
				navSrv->setCurrentNavTask();
			}
			return navSrv->moveTo();
		}
	}

	return false;
}

RangeAttackIfInRange::RangeAttackIfInRange() {}

bool RangeAttackIfInRange::execute(EntityHandle entityHandle)
{
	if (auto entity = entityHandle.lock())
	{
		if (auto fightSrv = entity->getServiceByType<FightService>())
		{
			auto targets = fightSrv->findRangeTargets();
			return fightSrv->RangeAttack(targets);
		}
	}

	return false;
}
