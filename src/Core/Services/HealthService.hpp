#ifndef HEALTHSERVICE_HPP
#define HEALTHSERVICE_HPP

#include "Core/Utils/BaseTypes.hpp"
#include "IGameService.hpp"

#include <string>
#include <vector>

class IWorldContext;
class HealthComponent;

class HealthService : public IGameService
{
public:
	using hp_amount = int;

	HealthService(EntityID _owner, std::weak_ptr<IWorldContext> worldContext, std::shared_ptr<HealthComponent> hpdata);
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
	EntityID _owner;
	std::weak_ptr<IWorldContext> _worldContext;
	std::shared_ptr<HealthComponent> _healthData;
	int _priority = 0;

	void markDead();

	// IGameService interface

public:
	int getPriority() const override;
	void setPriority(int priority) override;
};

#endif	// HEALTHSERVICE_HPP
