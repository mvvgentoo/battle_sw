#include "HealthService.hpp"

#include "IO/Events/UnitDied.hpp"
#include "Core/World.hpp"
#include "Core/DataComponents/HealthComponent.hpp"

HealthService::HealthService(EntityID owner, std::weak_ptr<World> world, std::shared_ptr<HealthComponent> healthData) :
		_owner(owner),
        _world(world),
        _healthData(healthData)
{}

HealthService::~HealthService() {}

HealthService::hp_amount HealthService::getCurrentHP() const
{
    return  _healthData ? _healthData->currentHP : 0;
}

bool HealthService::isAlive() const
{
    return _healthData && !_healthData->isDead && _healthData->currentHP > 0;
}

bool HealthService::applyDamage(hp_amount amount)
{
    if (!isAlive())
    {
        return false;
    }

    _healthData->currentHP = std::max(0, _healthData->currentHP - amount);
    if (_healthData->currentHP == 0)
    {
        markDead();
	}
	return true;
}

bool HealthService::applyHeal(hp_amount amount)
{	
    if (!isAlive())
    {
        return false;
    }

    _healthData->currentHP = std::min(_healthData->hpMax, _healthData->currentHP + amount);
	return true;
}

ITurnBehavior::TurnStatus HealthService::update()
{
    return ITurnBehavior::TurnStatus::IDLE;
}

void HealthService::markDead()
{
    if (_healthData && !_healthData->isDead) {
        _healthData->isDead = true;

        if (auto world = _world.lock()) {
            world->emit(sw::io::UnitDied{_owner});
        }
    }
}

int HealthService::getPriority()
{
    return _priority;
}

void HealthService::setPriority(int priority)
{
    _priority = priority;
}
