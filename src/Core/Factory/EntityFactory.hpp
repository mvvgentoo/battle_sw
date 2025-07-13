#ifndef ENTITYFACTORY_HPP
#define ENTITYFACTORY_HPP

#include "Core/BaseTypes.hpp"
#include "UnitParams.hpp"

#include <functional>
#include <memory>

class World;
class Entity;

class EntityFactory
{
public:
	EntityFactory();
	virtual ~EntityFactory();
	virtual std::unique_ptr<Entity> create(
		std::shared_ptr<World> world, EntityID id, Position pos, const UnitParams& params) const
		= 0;
};


#endif	// ENTITYFACTORY_HPP
