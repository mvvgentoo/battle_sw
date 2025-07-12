#ifndef EVENTBUS_HPP
#define EVENTBUS_HPP

#include <functional>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>
#include <cassert>

class EventBus
{
public:
    template <typename Event>
	void subscribe(std::function<void(uint64_t tick, const Event&)> handler)
	{
        insertHandlersForType<Event>(handler);
	}

	template <typename Event>
	void publish(uint64_t tick, const Event& event) const
    {
        if (auto handlers = getHandlersForType<Event>())
        {
            for (const auto& handler : *handlers)
            {
                handler(tick, event);
            }
        }
	}

private:
    class HandlerBase
    {
    public:
        virtual ~HandlerBase() = default;
    };

    using Handler = std::unique_ptr<HandlerBase>;

    template <typename Type>
    class TypeHandler : public HandlerBase
    {
    public:
        using Functor = std::function<void(uint64_t, const Type&)>;
        ~TypeHandler() = default;

        const std::vector<Functor>& get() const {return handlers; }
        void add(Functor f) {handlers.push_back(std::move(f)); }
    private:
        std::vector<std::function<void(uint64_t, const Type&)>> handlers;
    };

    template <typename T>
    const typename std::vector<typename TypeHandler<T>::Functor>* getHandlersForType() const
    {
        auto type_ = std::type_index(typeid(T));
        if (auto it = _handlers.find(type_); it != _handlers.end() )
        {
            auto& handlerBase = it->second;
            TypeHandler<T>* concrete_type = dynamic_cast<TypeHandler<T>*>(handlerBase.get());
            if (concrete_type)
            {
                return &concrete_type->get();
            }
        }

        return nullptr;
    }

    template <typename T>
    void insertHandlersForType(typename TypeHandler<T>::Functor handler)
    {
        auto type_ = std::type_index(typeid(T));
        auto it = _handlers.find(type_);
        if(it == _handlers.end() )
        {
            it = _handlers.insert({type_, std::make_unique<TypeHandler<T>>()}).first;
        }

        auto& handlerBase = it->second;
        auto concrete_type = dynamic_cast<TypeHandler<T>*>(handlerBase.get());
        assert(concrete_type && "EventBus::insertHandlersForType::type_error");
        concrete_type->add(std::move(handler));
    }

    std::unordered_map<std::type_index, Handler> _handlers;
};

#endif	// EVENTBUS_HPP
