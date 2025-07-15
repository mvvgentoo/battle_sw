#include "EntityHandle.hpp"

#include "Core/Systems/EntityManager.hpp"

EntityHandle::EntityHandle() :
		_entityManager(),
		_id(0)
{}

EntityHandle::EntityHandle(std::weak_ptr<const EntityManager> entityManager, EntityID id) :
		_entityManager(entityManager),
		_id(id)
{}

EntityHandle::~EntityHandle() {}

EntityID EntityHandle::getId() const
{
	return _id;
}

Entity* EntityHandle::lock() const
{
	if (auto em = _entityManager.lock())
	{
		return em->resolveHandle(*this);
	}
	return nullptr;
}

bool EntityHandle::isValid() const
{
	if (auto em = _entityManager.lock())
	{
		return em->isValid(*this);
	}
	return false;
}
