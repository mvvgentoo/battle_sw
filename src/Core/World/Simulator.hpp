#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "Core/World/ITickProvider.hpp"
#include <cstdint>
#include <memory>

class IWorldContext;

class Simulator : public ITickProvider
{
public:
    Simulator(uint32_t maxSteps);

    uint32_t currentStep() const override;
    bool advance(std::shared_ptr<IWorldContext> worldCtx);
private:
    uint32_t _currentStep;
    uint32_t _maxSteps;
};

#endif // SIMULATOR_H
