#ifndef HUNTER_FACTORY_HPP
#define HUNTER_FACTORY_HPP

#include <Core/Factory/EntityFactory.hpp>
#include <memory>

class World;

class HunterFactory : public EntityFactory
{
public:
	HunterFactory(int hp, int minRange, int maxRange, int meleeRange, int agility, int strength);
	~HunterFactory() = default;
	std::unique_ptr<Entity> create(
		std::shared_ptr<IWorldContext> worldContext,
		EntityID id,
		Position pos,
		const UnitParams& params) const override;

private:
	int _hp;
	int _minAttackRange;
	int _maxAttackRange;
	int _meleeRange;
	int _agility;
	int _strength;
};

#endif
