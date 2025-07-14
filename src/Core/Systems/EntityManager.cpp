#include "EntityManager.hpp"
#include "Core/Factory/EntityFactory.hpp"
#include "Core/World/IWorldContext.hpp"

EntityManager::EntityManager()
{

}

EntityManager::~EntityManager()
{

}

EntityHandle EntityManager::createEntity(const std::string& name, EntityID id, const Position &pos, const UnitParams &params, std::shared_ptr<IWorldContext> sharedWorldCtx)
{
    const EntityFactory* factory = getEntityFactoryRegistry().getFactory(name);
    if (!factory)
    {
        return EntityHandle();
    }

    std::unique_ptr<Entity> entity = factory->create(sharedWorldCtx, id, pos, params);
    if (!entity)
    {
        return EntityHandle();
    }

    _units.emplace(id, std::move(entity));
    return EntityHandle(shared_from_this(), id);
}

std::shared_ptr<EntityManager> EntityManager::create()
{
    return createInternal();
}

EntityHandle EntityManager::getEntityByID(EntityID id) const
{
    if (_units.find(id) != _units.end())
    {
        return EntityHandle(shared_from_this(), id);
    }
    return EntityHandle();
}

Entity* EntityManager::resolveHandle(EntityHandle entityHandle) const
{
    if (entityHandle.getId() == 0)
    {
        return nullptr;
    }
    auto it = _units.find(entityHandle.getId());
    return (it != _units.end()) ? it->second.get() : nullptr;
}

bool EntityManager::updateEntityPosition(EntityID id, const Position& pos)
{
    auto it = _units.find(id);
    if (it != _units.end())
    {
        auto& entity = it->second;
        if(entity)
        {
            entity->setPosition(pos);
            return true;
        }
    }
    return false;
}

bool EntityManager::updateEntityPosition(EntityHandle handle, const Position& pos)
{
    return updateEntityPosition(handle.getId(), pos);
}

bool EntityManager::isValid(EntityHandle handle) const
{
    if (const auto* e = resolveHandle(handle))
    {
        return e->isAlive();
    }

    return false;
}

EntityFactoryRegistry &EntityManager::getEntityFactoryRegistry()
{
    return _factoryRegistry;
}

const EntityFactoryRegistry &EntityManager::getEntityFactoryRegistry() const
{
    return _factoryRegistry;
}

std::vector<EntityID> EntityManager::getNeighboursInRadius(Position start, Predicate condition) const
{
    std::vector<EntityID> result;
    for (const auto& [id, entity] : _units)
    {
        if (condition(entity, start))
        {
            result.push_back(id);
        }
    }

    return result;
}
