#ifndef ENTITY_H
#define ENTITY_H

#include "Core/BaseTypes.hpp"
#include "Core/ComponentHandler.hpp"
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

    template <typename Base, typename T>
    bool addComponent(std::shared_ptr<T> service)
    {
        return _componentHandler.addComponent<Base, T>(service);
    }

    template <typename T>
    std::shared_ptr<T> getComponentByType() const
    {
        return _componentHandler.getComponentByType<T>();
    }

    template <typename T>
    bool hasComponent() const
    {
        return _componentHandler.hasComponent<T>();
    }

	ITurnBehavior::TurnStatus take_turn(std::weak_ptr<World> world);

private:
	EntityID _id;
	Position _pos;

	ComponentHandler<IGameService> serviceHandler;
    ComponentHandler<IDataComponent> _componentHandler;
	std::unordered_set<std::string> _srvNames;
	std::unique_ptr<ITurnBehavior> _turnStrategy;
};

#endif	// ENTITY_H
