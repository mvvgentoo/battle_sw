#ifndef ENTIYBUILDER_HPP
#define ENTIYBUILDER_HPP

#include "BaseTypes.hpp"

#include <functional>
#include <memory>

class World;
class Entity;

class UnitParams
{
public:
	void set(const std::string& key, int value)
	{
		_kvps[key] = value;
	}

	int get(const std::string& key, int defaultValue = 0) const
	{
		auto it = _kvps.find(key);
		return (it != _kvps.end()) ? it->second : defaultValue;
	}

private:
	std::unordered_map<std::string, int> _kvps;
};

class EntityFactory
{
public:
	EntityFactory();
	virtual ~EntityFactory();
	virtual std::unique_ptr<Entity> create(
		std::shared_ptr<World> world, EntityID id, Position pos, const UnitParams& params) const
		= 0;
};

class EntityBuilder
{
public:
	EntityBuilder();
	~EntityBuilder();

	void registerFactory(const std::string& name, std::unique_ptr<EntityFactory> factory)
	{
		_factories[name] = std::move(factory);
	}

	std::unique_ptr<Entity> create(
		const std::string& name,
		std::shared_ptr<World> world,
		EntityID id,
		Position pos,
		const UnitParams& params) const;

private:
	std::unordered_map<std::string, std::unique_ptr<EntityFactory>> _factories;
};

#endif	// ENTIYBUILDER_HPP
