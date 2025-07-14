#include "Simulator.hpp"
#include "IWorldContext.hpp"
#include "Core/Systems/EntityManager.hpp"
#include "Core/AI/ITurnBehaviour.hpp"

Simulator::Simulator(std::unique_ptr<ITurnBehavior> turnBhv) : _currentStep(0), _turnBhv(std::move(turnBhv))
{

}

uint32_t Simulator::currentStep() const
{
    return _currentStep;
}

Simulator::SimulatorResult Simulator::advance(std::shared_ptr<IWorldContext> worldCtx, uint32_t maxSteps)
{
    if (worldCtx == nullptr)
    {
        return SimulatorResult::ERROR;
    }

    const auto& entityManager = worldCtx->getEntityManager();

    while (_currentStep < maxSteps)
    {
        auto entityAliveFunctor = [](const std::unique_ptr<Entity>& e) {
            return e->isAlive();
        };

        auto entitiesAlive = entityManager.getAllEntities(entityAliveFunctor);

        if (entitiesAlive.size() <= 1)
        {
            return SimulatorResult::ONE_OR_LESS_LEFT;
        }

        bool anyActed = false;
        for (auto handle : entitiesAlive)
        {
            if (auto entity = handle.lock())
            {
                if(_turnBhv)
                {
                    auto result = _turnBhv->makeTurn(worldCtx, entity->getID());
                    if (result == ITurnBehavior::TurnStatus::SUCCESS)
                    {
                        anyActed = true;
                    }
                }
            }
        }

        if (!anyActed)
        {
            return SimulatorResult::NO_ACTED;
        }

        ++_currentStep;
    }

    return SimulatorResult::REACH_MAX_STEPS;
}

