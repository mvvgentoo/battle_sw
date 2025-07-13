#include <limits>

#include "SimpleMovementBehavior.hpp"
#include "Core/DataComponents/MovementData.hpp"
#include "Core/World.hpp"

struct Direction
{
    int x, y;

    Direction(int x_, int y_) :
        x(x_),
        y(y_)
    {}
};

static Direction computeStep(const Position& from, const Position& to)
{
    int dx = (int)to.x - (int)from.x;
    int dy = (int)to.y - (int)from.y;

    int stepX = dx == 0 ? 0 : dx / abs(dx);
    int stepY = dy == 0 ? 0 : dy / abs(dy);

    return {stepX, stepY};
}

SimpleMovementBehavior::SimpleMovementBehavior(std::shared_ptr<MovementData> data) : _data(data)
{

}

SimpleMovementBehavior::~SimpleMovementBehavior()
{

}

IMovementBehavior::MovementResult SimpleMovementBehavior::moveTo(Position current, const Position &target, EntityID id, World &world)
{
    if (current == target)
    {
        return MovementResult{false, true, current, target};
    }

    auto from = current;
    int steps = _data->maxCellsPerTurn;
    const auto& navGrid = world.getGrid();

    for (int s = 0; s < steps; ++s)
    {
        Direction dir = computeStep(current, target);
        if (dir.x == 0 && dir.y == 0)
        {
            break;
        }

        Position next = {current.x + dir.x, current.y + dir.y};

        const static std::vector<Direction> directions
            = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}};

        auto bestDistance = std::numeric_limits<uint32_t>::max();
        bool found = false;
        if (navGrid.isOccupied(next) || !navGrid.inBounds(next))
        {
            for (const Direction& d : directions)
            {
                Position candidate{current.x + d.x, current.y + d.y};

                if (navGrid.isOccupied(candidate) || !navGrid.inBounds(candidate))
                {
                    continue;
                }

                auto dist = chebyshevDistance(candidate, target);
                if (dist < bestDistance)
                {
                    next = candidate;
                    bestDistance = dist;
                    found = true;
                }
            }
        }

        if (!found)
        {
            return MovementResult{false, false, current, {0,0}};
        }

        Position newPos{next.x, next.y};
        world.updateEntityPosition(id, newPos);
        current = newPos;

        //world.emit(sw::io::UnitMoved{id, static_cast<uint32_t>(current.x), static_cast<uint32_t>(current.y)});

        if (current == target)
        {
            return MovementResult{true, true, from, target};
        }
        break;
    }

    return MovementResult{true, false, from, current};
}
