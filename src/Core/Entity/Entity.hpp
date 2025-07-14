#ifndef ENTITY_H
#define ENTITY_H

#include "Core/Utils/BaseTypes.hpp"
#include "Core/Utils/ComponentHandler.hpp"

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class IGameService;
class IDataComponent;
class World;

class Entity
{
public:
	using IGameServicePtr = std::unique_ptr<IGameService>;

    Entity(EntityID id, Position pos);
    ~Entity();

    EntityID getID() const;
	const Position& getPosition() const;
	void setPosition(const Position& pos);

	bool canBeAttacked() const;
	bool isAlive() const;

	template <typename Base, typename T>
	bool addService(std::shared_ptr<T> service)
	{
        return _serviceHandler.addComponent<Base, T>(service);
	}

	template <typename T>
	std::shared_ptr<T> getServiceByType() const
	{
        return _serviceHandler.getComponentByType<T>();
	}

	template <typename T>
	bool hasService() const
	{
        return _serviceHandler.hasComponent<T>();
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

    std::vector<std::shared_ptr<IGameService>> getAllServices() const;

private:
	EntityID _id;
	Position _pos;

    ComponentHandler<IGameService> _serviceHandler;
    ComponentHandler<IDataComponent> _componentHandler;
};

#endif	// ENTITY_H
