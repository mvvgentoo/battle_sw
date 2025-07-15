#include "World.hpp"

#include "Core/FightSystem/CombatSystem.hpp"
#include "Core/Systems/EntityManager.hpp"
#include "Core/Systems/EventManager.hpp"
#include "Core/Systems/NavGridSystem.hpp"
#include "Core/Utils/EnableMakeShared.hpp"

#include <memory>

World::World(
	std::shared_ptr<NavGridSystem> navGrid,
	std::shared_ptr<EntityManager> entityManager,
	std::shared_ptr<CombatSystem> combatSystem,
	std::shared_ptr<EventManager> eventManager) :
		_navGrid(navGrid),
		_entityManager(entityManager),
		_combatSystem(combatSystem),
		_eventManager(eventManager)
{}

std::shared_ptr<World> World::create(
	std::shared_ptr<NavGridSystem> navGrid,
	std::shared_ptr<EntityManager> entityManager,
	std::shared_ptr<CombatSystem> combatSystem,
	std::shared_ptr<EventManager> eventManager)
{
	return EnableMakeShared<World>::createSharedPtrInternal(navGrid, entityManager, combatSystem, eventManager);
}

const NavGridSystem& World::getGrid() const
{
	assert(_navGrid && "NavGridSystem is null");
	return *_navGrid;
}

NavGridSystem& World::getGrid()
{
	assert(_navGrid && "NavGridSystem is null");
	return *_navGrid;
}

const EntityManager& World::getEntityManager() const
{
	assert(_entityManager && "EntityManager is null");
	return *_entityManager;
}

EntityManager& World::getEntityManager()
{
	assert(_entityManager && "EntityManager is null");
	return *_entityManager;
}

const CombatSystem& World::getCombatSystem() const
{
	assert(_combatSystem && "CombatSystem is null");
	return *_combatSystem;
}

CombatSystem& World::getCombatSystem()
{
	assert(_combatSystem && "CombatSystem is null");
	return *_combatSystem;
}

const EventManager& World::getEventManager() const
{
	assert(_eventManager && "EventManager is null");
	return *_eventManager;
}

EventManager& World::getEventManager()
{
	assert(_eventManager && "EventManager is null");
	return *_eventManager;
}

std::shared_ptr<IWorldContext> World::getSharedContext()
{
	return shared_from_this();
}
