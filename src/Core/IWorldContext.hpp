#ifndef IWORLDCONTEXT_HPP
#define IWORLDCONTEXT_HPP

class EntityManager;
class NavGridSystem;
class CombatSystem;
class EventBus;

class IWorldContext {
public:
    virtual ~IWorldContext() = default;

    virtual EntityManager& entities() = 0;
    virtual const EntityManager& entities() const = 0;

    virtual NavGridSystem& grid() = 0;
    virtual const NavGridSystem& grid() const = 0;

    virtual CombatSystem& combat() = 0;
    virtual const CombatSystem& combat() const = 0;

    virtual EventBus& events() = 0;
};

#endif // IWORLDCONTEXT_HPP
