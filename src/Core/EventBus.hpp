#ifndef EVENTBUS_HPP
#define EVENTBUS_HPP

#include <functional>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>

class EventBus
{
public:
	template <typename Event>
	void subscribe(std::function<void(uint64_t tick, const Event&)> handler)
	{
		auto wrapper = [handler = std::move(handler)](uint64_t tick, const void* ptr)
		{
			handler(tick, *static_cast<const Event*>(ptr));
		};
		_handlers[typeid(Event)].push_back(std::move(wrapper));
	}

	template <typename Event>
	void publish(uint64_t tick, const Event& event) const
	{
		auto it = _handlers.find(typeid(Event));
		if (it != _handlers.end())
		{
			for (const auto& handler : it->second)
			{
				handler(tick, &event);
			}
		}
	}

private:
	using RawHandler = std::function<void(uint64_t, const void*)>;
	std::unordered_map<std::type_index, std::vector<RawHandler>> _handlers;
};

#endif	// EVENTBUS_HPP
