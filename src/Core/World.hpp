#ifndef WORLD_HPP
#define WORLD_HPP

#include "BaseTypes.hpp"
#include "Core/Entity/Entity.hpp"
#include "Core/Entity/EntityHandle.hpp"
#include "Core/Systems/EntityManager.hpp"
#include "Core/Systems/EventBus.hpp"
#include "Core/Systems/NavGridSystem.hpp"


#include <cstdlib>
#include <functional>
#include <list>
#include <map>
#include <vector>
#include <memory>


class World : public std::enable_shared_from_this<World>
{
	friend class EntityHandle;

public:
    static std::shared_ptr<World> create(int w, int h);

    World(const World&) = delete;
    World(World&&) = delete;
    World& operator=(const World&) = delete;
    World& operator=(World&&) = delete;

	EntityHandle createEntity(const std::string& name, EntityID id, Position pos, const UnitParams& params);

    const NavGridSystem& getGrid() const
	{
        return *_navGrid;
	}

    NavGridSystem& getGrid()
    {
        return *_navGrid;
    }

	void setEventBus(std::shared_ptr<EventBus> bus);

    void setStep(uint64_t step);
	uint64_t getStep() const;

	template <typename Event>
	void emit(const Event& event) const
	{
		if (auto bus = _eventBus.lock())
		{
			bus->publish(getStep(), event);
		}
	}

    bool updateEntityPosition(EntityID id, const Position& pos);
    bool updateEntityPosition(EntityHandle entityHandle, const Position& pos);

private:
    World(int w, int h);

    template<typename ...Arg>
    std::shared_ptr<World> static createInternal(Arg&&...arg)
    {
        struct EnableMakeShared : public World {
            EnableMakeShared(Arg&&...arg) :World(std::forward<Arg>(arg)...) {}
        };
        return std::make_shared<EnableMakeShared>(std::forward<Arg>(arg)...);
    }

private:
    std::shared_ptr<NavGridSystem> _navGrid;
    std::weak_ptr<EventBus> _eventBus;
    std::shared_ptr<EntityManager> _entityManager;

	EntityHandle addToWorld(std::unique_ptr<Entity> entity, Position pos);

	uint64_t _currentStep = 0;
};

#endif	// WORLD_HPP
