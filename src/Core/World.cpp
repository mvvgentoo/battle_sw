#include "World.hpp"

#include "Core/Entity/Entity.hpp"
#include "Core/Services/INavigationService.hpp"
#include <memory>

World::World(int w, int h) :
		_navGrid(w, h)
{}

std::shared_ptr<World> World::create(int w, int h)
{
    return createInternal(w,h);
}

EntityHandle World::createEntity(const std::string& name, EntityID id, Position pos, const UnitParams& params)
{
	auto entity = _entityBuilder.create(name, shared_from_this(), id, pos, params);
	return addToWorld(std::move(entity), pos);
}

EntityHandle World::addToWorld(std::unique_ptr<Entity> entity, Position pos)
{
	if (entity == nullptr)
	{
		return EntityHandle();
	}

	EntityID id = entity->getID();

	CellFlag cellOccupyType = CellFlag::OCCUPY;
	if (auto&& navSrv = entity->getServiceByType<NavigationService>())
	{
        //cellOccupyType = navSrv->getCellOccupyType();
	}

	_units.emplace(id, std::move(entity));
	_navGrid.updatePosition(id, {-1, -1}, pos, cellOccupyType);

	return EntityHandle();
}

Entity* World::getRawEntity(EntityID id) const
{
	auto it = _units.find(id);
	if (it != _units.end())
	{
		return it->second ? it->second.get() : nullptr;
	}

	return nullptr;
}

std::vector<EntityID> World::getNeighboursInRadius(Position startPoint, Predicate condition) const
{
	std::vector<EntityID> result;
	for (auto&& [_, entity] : _units)
	{
		if (condition(entity, startPoint))
		{
			result.push_back(entity->getID());
		}
	}

	return result;
}

EntityHandle World::getEntityByID(EntityID id) const
{
	return EntityHandle(shared_from_this(), id);
}

void World::registerFactory(const std::string& name, std::unique_ptr<EntityFactory> factory)
{
	_entityBuilder.registerFactory(name, std::move(factory));
}

bool World::updateEntityPosition(EntityID id, const Position& pos)
{
	auto it = _units.find(id);
	if (it == _units.end() || !it->second)
	{
		return false;
	}

	const auto& entity = it->second;
	const auto& oldPosition = entity->getPosition();
	CellFlag cellOccupyType = CellFlag::OCCUPY;
	if (auto&& navSrv = entity->getServiceByType<NavigationService>())
	{
		cellOccupyType = navSrv->getCellOccupyType();
	}

	_navGrid.updatePosition(id, oldPosition, pos, cellOccupyType);
	entity->setPosition(pos);
	return true;
}

bool World::updateEntityPosition(EntityHandle entityHandle, const Position& pos)
{
	return updateEntityPosition(entityHandle.getId(), pos);
}

void World::setEventBus(std::shared_ptr<EventBus> bus)
{
	_eventBus = std::move(bus);
}

void World::setStep(uint64_t step)
{
	_currentStep = step;
}

uint64_t World::getStep() const
{
	return _currentStep;
}

Grid::Grid(int w, int h) :
		_w(w),
		_h(h)
{
	_gridOccupied.resize(w * h, 0);
	_gridShared.resize(w * h);
}

void Grid::updatePosition(EntityID id, Position old_pos, Position new_pos, CellFlag flag)
{
	if (!inBounds(new_pos))
	{
		return;
	}

	size_t oldIndex = old_pos.y * getWidth() + old_pos.x;
	size_t newIndex = new_pos.y * getWidth() + new_pos.x;

	switch (flag)
	{
		case CellFlag::OCCUPY:
		{
			if (inBounds(old_pos) && _gridOccupied[oldIndex] == id)
			{
				_gridOccupied[oldIndex] = 0;
			}
			_gridOccupied[newIndex] = id;
		}
		break;
		case CellFlag::SHARE:
		{
			if (inBounds(old_pos))
			{
				auto& oldShared = _gridShared[oldIndex];
				std::erase(oldShared, id);
			}

			auto& shared = _gridShared[newIndex];
			shared.push_back(id);
		}
		break;
		default:
			//log_error
			return;
	}
}

bool Grid::inBounds(const Position& pos) const
{
	return pos.x > 0 && pos.x < getWidth() && pos.y > 0 && pos.y < getHeight();
}

bool Grid::isOccupied(const Position& pos) const
{
	if (!inBounds(pos))
	{
		return false;
	}

	return _gridOccupied[pos.y * getWidth() + pos.x] != 0;
}

std::vector<EntityHandle> World::allEntities() const
{
	return allEntitiesIf([](const std::unique_ptr<Entity>&) { return true; });
}

std::vector<EntityHandle> World::allEntitiesIf(std::function<bool(const std::unique_ptr<Entity>& e)> condition) const
{
	std::vector<EntityHandle> result;
	result.reserve(_units.size());

	auto self = shared_from_this();
	for (const auto& [id, entity] : _units)
	{
		if (entity && condition(entity))
		{
			result.emplace_back(self, id);
		}
	}

	return result;
}
