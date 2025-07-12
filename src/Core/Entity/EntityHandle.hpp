#ifndef ENTITYHANDLE_H
#define ENTITYHANDLE_H

#include "Core/BaseTypes.hpp"
#include "Entity.hpp"

class World;

class EntityHandle
{
public:
	EntityHandle();
	EntityHandle(std::weak_ptr<const World> world, EntityID id);

	~EntityHandle();

	EntityID getId();
	Entity* lock();
	bool isValid() const;

public:
	std::weak_ptr<const World> _world;
	EntityID _id;
};

#endif	// ENTITYHANDLE_H
