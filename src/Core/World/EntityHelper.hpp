#ifndef ENTITYHELPER_H
#define ENTITYHELPER_H

#include "Core/Entity/EntityHandle.hpp"
#include "Core/Factory/UnitParams.hpp"

class IWorldContext;
class Position;

class EntityHelper
{
public:
	EntityHelper();

	static bool updateEntityPosition(IWorldContext& ctx, EntityID id, const Position& pos);
	static bool updateEntityPosition(IWorldContext& ctx, EntityHandle handle, const Position& pos);
	static EntityHandle createEntity(
		IWorldContext& ctx, const std::string& name, EntityID id, Position pos, const UnitParams& params);
	static EntityHandle createHandle(IWorldContext& ctx, EntityID id);
};

#endif	// ENTITYHELPER_H
