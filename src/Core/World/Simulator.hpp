#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "Core/World/ITickProvider.hpp"
#include <cstdint>
#include <memory>

class IWorldContext;
class ITurnBehavior;

class Simulator : public ITickProvider
{
public:
    enum class SimulatorResult
    {
        NO_ACTED,
        ONE_OR_LESS_LEFT,
        REACH_MAX_STEPS,
        ERROR
    };

    Simulator(std::unique_ptr<ITurnBehavior> turnBhv);

    uint32_t currentStep() const override;
    SimulatorResult advance(std::shared_ptr<IWorldContext> worldCtx, uint32_t maxSteps);
private:
    uint32_t _currentStep;
    std::unique_ptr<ITurnBehavior> _turnBhv;
};

#endif // SIMULATOR_H
