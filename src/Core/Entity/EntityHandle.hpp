#ifndef ENTITYHANDLE_H
#define ENTITYHANDLE_H

#include "Core/Utils/BaseTypes.hpp"
#include "Entity.hpp"

class EntityManager;

class EntityHandle {
public:
    EntityHandle();
    EntityHandle(std::weak_ptr<const EntityManager> _entityManager, EntityID id);
    ~EntityHandle();

    EntityID getId() const;
    Entity* lock();
    bool isValid() const;

private:
    std::weak_ptr<const EntityManager> _entityManager;
    EntityID _id;
};

#endif	// ENTITYHANDLE_H
