#ifndef ENTITYFACTORYREGISTRY_HPP
#define ENTITYFACTORYREGISTRY_HPP

#include <string>
#include <memory>
#include <unordered_map>

class EntityFactory;

class EntityFactoryRegistry
{
public:
    void registerFactory(const std::string& name, std::unique_ptr<EntityFactory> factory);
    const EntityFactory* getFactory(const std::string& name) const;
    bool hasFactory(const std::string& name) const;

private:
    std::unordered_map<std::string, std::unique_ptr<EntityFactory>> _factories;
};
#endif // ENTITYFACTORYREGISTRY_HPP
