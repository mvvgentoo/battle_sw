#ifndef IWORLDCONTEXT_HPP
#define IWORLDCONTEXT_HPP

#include <memory>
class EntityManager;
class NavGridSystem;
class CombatSystem;
class EventManager;

class IWorldContext
{
public:
	virtual ~IWorldContext() = default;

	virtual const NavGridSystem& getGrid() const = 0;
	virtual NavGridSystem& getGrid() = 0;

	virtual const EntityManager& getEntityManager() const = 0;
	virtual EntityManager& getEntityManager() = 0;

	virtual const CombatSystem& getCombatSystem() const = 0;
	virtual CombatSystem& getCombatSystem() = 0;

	virtual const EventManager& getEventManager() const = 0;
	virtual EventManager& getEventManager() = 0;

	virtual std::shared_ptr<IWorldContext> getSharedContext() = 0;
};

#endif	// IWORLDCONTEXT_HPP
