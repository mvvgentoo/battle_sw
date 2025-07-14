#include "Simulator.hpp"

Simulator::Simulator(uint32_t maxSteps) : _currentStep(0), _maxSteps(maxSteps)
{

}

uint32_t Simulator::currentStep() const
{
    return _currentStep;
}

bool Simulator::advance(std::shared_ptr<IWorldContext> worldCtx)
{
    while (_currentStep < _maxSteps)
    {
        //TODO logic
        ++_currentStep;
    }
    return true;
}

