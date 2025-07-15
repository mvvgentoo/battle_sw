#ifndef WORLD_HPP
#define WORLD_HPP

#include "Core/Entity/EntityHandle.hpp"
#include "Core/World/IWorldContext.hpp"

#include <cstdlib>
#include <functional>
#include <list>
#include <map>
#include <vector>
#include <memory>

class EventManager;
class EntityManager;
class CombatSystem;
class NavGridSystem;

class World : public std::enable_shared_from_this<World>, public IWorldContext
{
	friend class EntityHandle;

public:
    static std::shared_ptr<World> create(std::shared_ptr<NavGridSystem> navGrid, std::shared_ptr<EntityManager> entityManager,
                                         std::shared_ptr<CombatSystem> combatSystem, std::shared_ptr<EventManager> eventManager);

    World(const World&) = delete;
    World(World&&) = delete;
    World& operator=(const World&) = delete;
    World& operator=(World&&) = delete;

    const NavGridSystem& getGrid() const override;
    NavGridSystem& getGrid() override;

    const EntityManager& getEntityManager() const override;
    EntityManager& getEntityManager() override;

    const CombatSystem& getCombatSystem() const override;
    CombatSystem& getCombatSystem() override;

    const EventManager& getEventManager() const override;
    EventManager& getEventManager() override;

    std::shared_ptr<IWorldContext> getSharedContext() override;

protected:
    World(std::shared_ptr<NavGridSystem> navGrid, std::shared_ptr<EntityManager> entityManager,
                 std::shared_ptr<CombatSystem> combatSystem, std::shared_ptr<EventManager> eventManager);    

private:
    std::shared_ptr<NavGridSystem> _navGrid;
    std::shared_ptr<EventManager> _eventManager;
    std::shared_ptr<EntityManager> _entityManager;
    std::shared_ptr<CombatSystem> _combatSystem;	
};

#endif	// WORLD_HPP
