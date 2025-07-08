#include "HealthService.hpp"

#include "IO/Events/UnitDied.hpp"
#include "World.hpp"

HealthService::HealthService(hp_amount startHP, EntityID owner, std::weak_ptr<World> world) :
		_hp(startHP),
		_maxHP(startHP),
		_owner(owner),
		_world(world)
{}

HealthService::~HealthService() {}

HealthService::hp_amount HealthService::getCurrentHP() const
{
	return _hp;
}

bool HealthService::isAlive() const
{
	return _hp > 0;
}

bool HealthService::applyDamage(hp_amount amount)
{
	_hp = std::max(0, _hp - amount);
	if (_hp == 0)
	{
		if (auto world = _world.lock())
		{
			world->emit(sw::io::UnitDied{_owner});
		}
	}
	return true;
}

bool HealthService::applyHeal(hp_amount amount)
{
	_hp = std::min(_maxHP, _hp + amount);
	return true;
}

void HealthService::update() {}
