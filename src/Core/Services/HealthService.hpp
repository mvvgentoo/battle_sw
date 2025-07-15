#ifndef HEALTHSERVICE_HPP
#define HEALTHSERVICE_HPP

#include "Core/Entity/EntityHandle.hpp"
#include "Core/Utils/BaseTypes.hpp"
#include "IGameService.hpp"

#include <string>
#include <vector>

class IWorldContext;

class HealthService : public IGameService
{
public:
	constexpr static int DefaultPriority = 0;
	using hp_amount = int;

	HealthService(std::weak_ptr<IWorldContext> worldContext, EntityID _owner, int priority = DefaultPriority);
	virtual ~HealthService();

	HealthService(const HealthService&) = delete;
	HealthService(HealthService&&) = delete;
	HealthService& operator=(const HealthService&) = delete;
	HealthService& operator=(HealthService&&) = delete;

	hp_amount getCurrentHP() const;
	bool isAlive() const;

	bool applyDamage(hp_amount amount);
	bool applyHeal(hp_amount amount);

	ITurnBehavior::TurnStatus update() override;

private:
	std::weak_ptr<IWorldContext> _worldContext;
	EntityID _owner;
	int _priority;
	EntityHandle _handle;

public:
	int getPriority() const override;
	void setPriority(int priority) override;
};

#endif	// HEALTHSERVICE_HPP
