#ifndef IGAMESERVICE_HPP
#define IGAMESERVICE_HPP

#include "Core/ComponentHandler.hpp"
#include "Core/ITurnBehaviour.hpp"

#include <memory>
#include <typeindex>
#include <unordered_map>

class IBaseComponent;

class IGameService
{
public:
	using IGameServicePtr = std::unique_ptr<IGameService>;
	using IComponentPtr = std::unique_ptr<IBaseComponent>;

	IGameService();
	virtual ~IGameService();
    virtual ITurnBehavior::TurnStatus update() = 0;

	template <typename Base, typename T>
	bool addComponent(std::shared_ptr<T> component)
	{
		return _componentHandler.addComponent<Base, T>(component);
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

	template <typename T>
	std::vector<std::shared_ptr<T>> findAllComponents() const
	{
		return _componentHandler.findAllComponents<T>();
	}

protected:
	ComponentHandler<IBaseComponent> _componentHandler;
};

#endif	// IGAMESERVICE_HPP
