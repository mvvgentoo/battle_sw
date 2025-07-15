#include "EventManager.hpp"

EventManager::EventManager(std::shared_ptr<EventBus> eventBus, std::shared_ptr<ITickProvider> tickProvider) :
		_eventBus(eventBus),
		_tickProvider(tickProvider)
{}

EventManager::~EventManager() {}
