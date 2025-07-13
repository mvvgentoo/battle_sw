#include "EntityFactoryRegistry.hpp"

void EntityFactoryRegistry::registerFactory(const std::string &name, std::unique_ptr<EntityFactory> factory)
{
    _factories[name] = std::move(factory);
}

const EntityFactory *EntityFactoryRegistry::getFactory(const std::string &name) const
{
    auto it = _factories.find(name);
    return (it != _factories.end()) ? it->second.get() : nullptr;
}

bool EntityFactoryRegistry::hasFactory(const std::string &name) const
{
    return _factories.contains(name);
}
