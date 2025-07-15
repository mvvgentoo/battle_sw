#ifndef COMPONENTHANDLER_HPP
#define COMPONENTHANDLER_HPP

#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>

template <class ComponentType>
class ComponentHandler
{
public:
	template <typename Base, typename T>
	bool addComponent(std::shared_ptr<T> component)
	{
		static_assert(std::is_base_of<Base, T>::value, "You are trying to register wrong component");

		if (!hasComponent<Base>())
		{
			_components[getHash<Base>()] = component;
			return true;
		}

		return false;
	}

	template <typename T>
	std::shared_ptr<T> getComponentByType() const
	{
		auto it = _components.find(getHash<T>());
		if (it != _components.end())
		{
			return std::dynamic_pointer_cast<T>(it->second);
		}

		return nullptr;
	}

	template <typename T>
	bool hasComponent() const
	{
		return _components.find(getHash<T>()) != _components.end();
	}

	template <typename T>
	std::vector<std::shared_ptr<T>> findAllComponents() const
	{
		std::vector<std::shared_ptr<T>> result;

		for (const auto& [type, ptr] : _components)
		{
			if (auto casted = std::dynamic_pointer_cast<T>(ptr))
			{
				result.push_back(casted);
			}
		}

		return result;
	}

	std::vector<std::shared_ptr<ComponentType>> getAllComponents() const
	{
		std::vector<std::shared_ptr<ComponentType>> result;
		result.reserve(_components.size());
		for (const auto& [_, comp] : _components)
		{
			result.push_back(comp);
		}
		return result;
	}

private:
	using hash_type = std::type_index;

	template <class T>
	hash_type getHash() const
	{
		return typeid(T);
	}

	std::unordered_map<std::type_index, std::shared_ptr<ComponentType>> _components;
};

#endif	// COMPONENTHANDLER_HPP
