#include "World.hpp"

#include "Core/Entity/Entity.hpp"
#include <memory>

World::World(int w, int h)
{
    _navGrid = std::make_shared<NavGridSystem>(w,h);
    _entityManager = EntityManager::create();
    _eventBus = std::make_shared<EventBus>();
}

std::shared_ptr<World> World::create(int w, int h)
{
    return createInternal(w,h);
}

EntityHandle World::createEntity(const std::string& name, EntityID id, Position pos, const UnitParams& params)
{
    auto entity = _entityManager->createEntity(name, id, pos, params, shared_from_this());
    updateEntityPosition(entity.getId(), pos);
    return entity;
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

bool World::updateEntityPosition(EntityID id, const Position& pos)
{
    auto entityHandle = _entityManager->getEntityByID(id);
    if (auto entity = entityHandle.lock())
    {
        CellFlag cellOccupyType = CellFlag::OCCUPY;
        auto currentPos = entity->getPosition();
        bool result = _entityManager->updateEntityPosition(id, pos);
        result = result && getGrid().updatePosition(id, currentPos, pos, cellOccupyType);
        return result;
    }

    return false;
}

bool World::updateEntityPosition(EntityHandle entityHandle, const Position& pos)
{
	return updateEntityPosition(entityHandle.getId(), pos);
}

void World::setEventBus(std::shared_ptr<EventBus> bus)
{
	_eventBus = std::move(bus);
}



