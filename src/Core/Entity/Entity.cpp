#include "Entity.hpp"

#include "FightService.hpp"
#include "HealthService.hpp"
#include "ITurnBehaviour.hpp"
#include "World.hpp"

Entity::Entity(EntityID id, Position pos, std::unique_ptr<ITurnBehavior> strategy) :
		_id(id),
		_pos(pos),
		_turnStrategy(std::move(strategy))
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

ITurnBehavior::TurnStatus Entity::take_turn(std::weak_ptr<World> world)
{
	return _turnStrategy->makeTurn(world, _id);
}
