#ifndef HEALTHSERVICE_HPP
#define HEALTHSERVICE_HPP

#include "Core/BaseTypes.hpp"
#include "IGameService.hpp"

#include <string>
#include <vector>

class World;

class HealthService : public IGameService
{
public:
	using hp_amount = int;

	HealthService(hp_amount startHP, EntityID _owner, std::weak_ptr<World> _world);
	virtual ~HealthService();
	HealthService(const HealthService&) = delete;
	HealthService(HealthService&&) = delete;
	HealthService& operator=(const HealthService&) = delete;
	HealthService& operator=(HealthService&&) = delete;

	hp_amount getCurrentHP() const;
	bool isAlive() const;

	bool applyDamage(hp_amount amount);
	bool applyHeal(hp_amount amount);

	virtual void update() override;

private:
	hp_amount _hp;
	hp_amount _maxHP;
	EntityID _owner;
	std::weak_ptr<World> _world;
};

#endif	// HEALTHSERVICE_HPP
