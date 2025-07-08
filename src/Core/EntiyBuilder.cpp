#include "EntiyBuilder.hpp"

#include "Entity.hpp"
#include "World.hpp"

EntityBuilder::EntityBuilder() {}

EntityBuilder::~EntityBuilder() {}

std::unique_ptr<Entity> EntityBuilder::create(
	const std::string& name, std::shared_ptr<World> world, EntityID id, Position pos, const UnitParams& params) const
{
	auto it = _factories.find(name);
	if (it != _factories.end())
	{
		if (auto&& factory = it->second)
		{
			return factory->create(world, id, pos, params);
		}
	}
	return nullptr;
}

EntityFactory::~EntityFactory() {}

EntityFactory::EntityFactory() {}
