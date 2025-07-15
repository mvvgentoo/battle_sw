#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include "Core/Entity/Entity.hpp"
#include "Core/Entity/EntityHandle.hpp"
#include "Core/Factory/EntityFactoryRegistry.hpp"
#include "Core/Factory/UnitParams.hpp"
#include "Core/Utils/BaseTypes.hpp"

#include <map>
#include <memory>

class EntityFactory;
class IWorldContext;

class EntityManager : public std::enable_shared_from_this<EntityManager>
{
public:
	using Predicate = std::function<bool(const std::unique_ptr<Entity>& entity, Position start)>;

	static std::shared_ptr<EntityManager> create();

	EntityManager(const EntityManager&) = delete;
	EntityManager(EntityManager&&) = delete;
	EntityManager& operator=(const EntityManager&) = delete;
	EntityManager& operator=(EntityManager&&) = delete;

	~EntityManager();

	EntityHandle createEntity(
		const std::string& name,
		EntityID id,
		const Position& pos,
		const UnitParams& params,
		std::shared_ptr<IWorldContext> sharedWorldCtx);
	EntityHandle getEntityByID(EntityID id) const;
	Entity* resolveHandle(EntityHandle entityHandle) const;

	std::vector<EntityID> getNeighboursInRadius(Position startPoint, Predicate condition) const;
	std::vector<EntityHandle> getAllEntities(
		const std::function<bool(const std::unique_ptr<Entity>&)>& predicate) const;

	bool updateEntityPosition(EntityID id, const Position& pos);
	bool updateEntityPosition(EntityHandle entityHandle, const Position& pos);
	bool isValid(EntityHandle entityHandle) const;

	EntityFactoryRegistry& getEntityFactoryRegistry();
	const EntityFactoryRegistry& getEntityFactoryRegistry() const;

	std::shared_ptr<EntityManager> getSharedData();

private:
	std::map<EntityID, std::unique_ptr<Entity>> _units;
	//TODO: better to use more complex structure and preserve order in addToWorld
	//std::unordered_map<EntityID, std::unique_ptr<Entity>> _units;
	//std::vector<EntityID> _unitsOrder;
	EntityFactoryRegistry _factoryRegistry;

protected:
	EntityManager();
};

#endif	// ENTITYMANAGER_HPP
