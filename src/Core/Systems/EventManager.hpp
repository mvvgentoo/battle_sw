#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include "Core/Systems/EventBus.hpp"
#include "Core/World/ITickProvider.hpp"

class EventManager
{
public:
    EventManager(std::shared_ptr<EventBus> eventBus, std::shared_ptr<ITickProvider> tickProvider);
    ~EventManager();

    template <typename Event>
    void emit(const Event& event) const
    {
        assert(_eventBus && "EventBus is not set");
        assert(_tickProvider && "TickProvider is not set");

        _eventBus->publish(_tickProvider->currentStep(), event);
    }


private:
    std::shared_ptr<EventBus> _eventBus;
    std::shared_ptr<ITickProvider> _tickProvider;
};

#endif // EVENTMANAGER_HPP
