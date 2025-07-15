#include "Entity.hpp"

#include "Core/AI/ITurnBehaviour.hpp"
#include "Core/DataComponents/IDataComponent.hpp"
#include "Core/Services/HealthService.hpp"
#include "Core/World/World.hpp"

Entity::Entity(EntityID id, Position pos) :
		_id(id),
		_pos(pos)
{}

Entity::~Entity() {}

EntityID Entity::getID() const
{
	return _id;
}

const Position& Entity::getPosition() const
{
	return _pos;
}

void Entity::setPosition(const Position& pos)
{
	_pos = pos;
}

bool Entity::canBeAttacked() const
{
	if (auto&& healthSrv = getServiceByType<HealthService>())
	{
		return true;
	}

	return false;
}

bool Entity::isAlive() const
{
	if (auto&& healthSrv = getServiceByType<HealthService>())
	{
		return healthSrv->isAlive();
	}

	return true;
}

std::vector<std::shared_ptr<IGameService>> Entity::getAllServices() const
{
	return _serviceHandler.getAllComponents();
}
