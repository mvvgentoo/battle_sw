#include "World.hpp"

#include "Core/Systems/EntityManager.hpp"
#include "Core/Systems/NavGridSystem.hpp"
#include "Core/FightSystem/CombatSystem.hpp"
#include "Core/Systems/EventManager.hpp"

#include <memory>

World::World(std::shared_ptr<NavGridSystem> navGrid, std::shared_ptr<EntityManager> entityManager,
             std::shared_ptr<CombatSystem> combatSystem, std::shared_ptr<EventManager> eventManager) :
    _navGrid(navGrid), _entityManager(entityManager), _combatSystem(combatSystem), _eventManager(eventManager)
{

}

std::shared_ptr<World> World::create(std::shared_ptr<NavGridSystem> navGrid, std::shared_ptr<EntityManager> entityManager,
                                     std::shared_ptr<CombatSystem> combatSystem, std::shared_ptr<EventManager> eventManager)
{
    auto result = createInternal(navGrid,entityManager, combatSystem, eventManager);
    if(combatSystem)
    {
        combatSystem->setContext(result);
    }
    return result;
}

const NavGridSystem &World::getGrid() const
{
    return *_navGrid;
}

NavGridSystem &World::getGrid()
{
    return *_navGrid;
}

const EntityManager &World::getEntityManager() const
{
    return *_entityManager;
}

EntityManager &World::getEntityManager()
{
    return *_entityManager;
}

const CombatSystem &World::getCombatSystem() const
{
    return *_combatSystem;
}

CombatSystem &World::getCombatSystem()
{
    return *_combatSystem;
}

const EventManager &World::getEventManager() const
{
    return *_eventManager;
}

EventManager &World::getEventManager()
{
    return *_eventManager;
}

std::shared_ptr<IWorldContext> World::getSharedContext()
{
    return shared_from_this();
}

