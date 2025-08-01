#ifndef SWORDSMAN_FACTORY_HPP
#define SWORDSMAN_FACTORY_HPP

#include "Core/Entity/EntityHandle.hpp"
#include "Core/Factory/EntityFactory.hpp"

#include <memory>

class World;

class SwordsmanFactory : public EntityFactory
{
public:
	SwordsmanFactory(int hp, int meleeRange, int damage);
	~SwordsmanFactory() = default;
	std::unique_ptr<Entity> create(
		std::shared_ptr<IWorldContext> worldContext,
		EntityID id,
		Position pos,
		const UnitParams& params) const override;

private:
	int _hp;
	int _meleeRange;
	int _damage;
};

#endif
