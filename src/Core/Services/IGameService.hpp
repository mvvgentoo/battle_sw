#ifndef IGAMESERVICE_HPP
#define IGAMESERVICE_HPP

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
    virtual int getPriority() = 0;
    virtual void setPriority(int priority) = 0;
};

#endif	// IGAMESERVICE_HPP
