#ifndef MELEEATTACKBEHAVIOR_HPP
#define MELEEATTACKBEHAVIOR_HPP

#include <memory>
#include "Core/FightSystem/IAttackBehavior.hpp"
#include "Core/DataComponents/RangeAttackData.hpp"

#include "Core/World.hpp"
#include "Core/FightSystem/CombatSystem.hpp"

class RangeAttackBehavior : public IAttackBehavior
{
public:
    explicit RangeAttackBehavior(std::shared_ptr<RangeAttackData> data);
    virtual ~RangeAttackBehavior() = default;

    int getPriority() const override;

    bool canBeActivated(const World&, EntityID) const override {
        return true; // всегда можно
    }

    std::vector<EntityID> findTargets(const World& world, EntityID self) const override {
        const Position& pos = world.getEntityByID(self).lock()->getPosition();
        return _data->targetSelector->selectTargets
        (
                world.getNeighboursInRadius(pos, [rMin = _data->rangeMin, rMax = _data->rangeMax](const auto& entity, Position pos)
                                            {
                                                auto dist = Grid::chebyshevDistance(pos, entity->getPosition());
                                                return entity && entity->isAlive() && dist <= rMax && dist >= rMin;
            })
        );
    }

    void execute(EntityID attacker, const std::vector<EntityID>& targets, CombatSystem& combat) const override {
        for (auto id : targets) {
            combat.dealDamageNow({ attacker, id, _data->agility });
        }
    }

private:
    std::shared_ptr<RangeAttackData> _data;
};
#endif // MELEEATTACKBEHAVIOR_HPP
