#include "EntityHandle.hpp"

#include "World.hpp"

EntityHandle::EntityHandle() :
		_world(),
		_id(0)
{}

EntityHandle::EntityHandle(std::weak_ptr<const World> world, EntityID id) :
		_world(world),
		_id(id)
{}

EntityHandle::~EntityHandle() {}

EntityID EntityHandle::getId()
{
	return _id;
}

Entity* EntityHandle::lock()
{
	if (auto w = _world.lock())
	{
		return w->getRawEntity(_id);
	}
	return nullptr;
}

bool EntityHandle::isValid() const
{
	if (auto w = _world.lock())
	{
		auto entity = w->getRawEntity(_id);
		return entity != nullptr && entity->isAlive();
	}
	return false;
}
