#ifndef WORLD_HPP
#define WORLD_HPP

#include "BaseTypes.hpp"
#include "Core/Entity/Entity.hpp"
#include "Core/Entity/EntityHandle.hpp"
#include "EntiyBuilder.hpp"
#include "Core/Systems/EventBus.hpp"

#include <cstdlib>
#include <functional>
#include <list>
#include <map>
#include <vector>
#include <memory>

class Grid
{
public:
	Grid(int w, int h);

	int getHeight() const
	{
		return _h;
	}

	int getWidth() const
	{
		return _w;
	}

	void updatePosition(EntityID id, Position old_pos, Position new_pos, CellFlag flag);
	bool inBounds(const Position& pos) const;
	bool isOccupied(const Position& pos) const;

	static uint32_t chebyshevDistance(const Position& a, const Position& b)
	{
		return std::max((a.x > b.x ? a.x - b.x : b.x - a.x), (a.y > b.y ? a.y - b.y : b.y - a.y));
	}

private:
	int _w, _h;
	//std::vector<std::vector<std::pair<EntityID, CellFlag>>> _grid;
	std::vector<EntityID> _gridOccupied;
	std::vector<std::list<EntityID>> _gridShared;
};

class World : public std::enable_shared_from_this<World>
{
	friend class EntityHandle;

public:
	using Predicate = std::function<bool(const std::unique_ptr<Entity>& entity, Position start)>;

    static std::shared_ptr<World> create(int w, int h);

    World(const World&) = delete;
    World(World&&) = delete;
    World& operator=(const World&) = delete;
    World& operator=(World&&) = delete;

	EntityHandle createEntity(const std::string& name, EntityID id, Position pos, const UnitParams& params);

    std::vector<EntityID> getNeighboursInRadius(Position startPoint, Predicate condition) const;
	EntityHandle getEntityByID(EntityID id) const;

	void registerFactory(const std::string& name, std::unique_ptr<EntityFactory> factory);

	const Grid& getGrid() const
	{
		return _navGrid;
	}

	bool updateEntityPosition(EntityID id, const Position& pos);
	bool updateEntityPosition(EntityHandle entityHandle, const Position& pos);

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

	std::vector<EntityHandle> allEntities() const;
	std::vector<EntityHandle> allEntitiesIf(std::function<bool(const std::unique_ptr<Entity>& e)> condition) const;

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
	Grid _navGrid;
	std::map<EntityID, std::unique_ptr<Entity>> _units;
	//TODO: better to use more complex structure and preserve order in addToWorld
	//std::unordered_map<EntityID, std::unique_ptr<Entity>> _units;
	//std::vector<EntityID> _unitsOrder;

	EntityBuilder _entityBuilder;

	EntityHandle addToWorld(std::unique_ptr<Entity> entity, Position pos);
	Entity* getRawEntity(EntityID id) const;

	std::weak_ptr<EventBus> _eventBus;
	uint64_t _currentStep = 0;
};

#endif	// WORLD_HPP
