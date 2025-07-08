#pragma once

#include "details/PrintFieldVisitor.hpp"

#include <iostream>
#include <typeindex>
#include <unordered_map>

namespace sw
{
	class EventLog
	{
	public:
		template <class TEvent>
		void log(uint64_t tick, TEvent&& event)
		{
			std::cout << "[" << tick << "] " << TEvent::Name << " ";
			PrintFieldVisitor visitor(std::cout);
			event.visit(visitor);
			std::cout << std::endl;
		}

		template <class TEvent>
		void log(uint64_t tick, const TEvent& event)
		{
			std::cout << "[" << tick << "] " << TEvent::Name << " ";
			PrintFieldVisitor visitor(std::cout);
			auto ev = const_cast<TEvent&>(event);
			ev.visit(visitor);
			std::cout << std::endl;
		}
	};
}
