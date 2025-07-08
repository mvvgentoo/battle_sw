#ifndef ENTITY_H
#define ENTITY_H

#include "BaseTypes.hpp"
#include "ComponentHandler.hpp"
#include "Core/ITurnBehaviour.hpp"

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class IGameService;
class World;

class Entity
{
public:
	using IGameServicePtr = std::unique_ptr<IGameService>;

	Entity(EntityID id, Position pos, std::unique_ptr<ITurnBehavior> strategy);
	~Entity();
	EntityID getID() const;
	const Position& getPosition() const;
	void setPosition(const Position& pos);

	bool canBeAttacked() const;
	bool isAlive() const;

	template <typename Base, typename T>
	bool addService(std::shared_ptr<T> service)
	{
		return serviceHandler.addComponent<Base, T>(service);
	}

	template <typename T>
	std::shared_ptr<T> getServiceByType() const
	{
		return serviceHandler.getComponentByType<T>();
	}

	template <typename T>
	bool hasService() const
	{
		return serviceHandler.hasComponent<T>();
	}

	ITurnBehavior::TurnStatus take_turn(std::weak_ptr<World> world);

private:
	EntityID _id;
	Position _pos;

	ComponentHandler<IGameService> serviceHandler;
	std::unordered_set<std::string> _srvNames;
	std::unique_ptr<ITurnBehavior> _turnStrategy;
};

#endif	// ENTITY_H
