#ifndef SIMPLEMOVEMENTBEHAVIOR_HPP
#define SIMPLEMOVEMENTBEHAVIOR_HPP

#include <memory>
#include "IMovementBehavior.hpp"


class IWorldContext;
struct MovementData;

class SimpleMovementBehavior : public IMovementBehavior
{
public:
    explicit SimpleMovementBehavior(std::shared_ptr<MovementData> _data);
    ~SimpleMovementBehavior();

    MovementResult moveTo(Position current, const Position &target, EntityID id, IWorldContext &world);

private:
    std::shared_ptr<MovementData> _data;
};

#endif // SIMPLEMOVEMENTBEHAVIOR_HPP
