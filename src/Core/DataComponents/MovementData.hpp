#ifndef MOVEMENTDATA_HPP
#define MOVEMENTDATA_HPP

#include <memory>
#include "Core/BaseTypes.hpp"

struct MovementData : public IDataComponent
{
    int maxCellsPerTurn = 1;
};


#endif // MOVEMENTDATA_HPP
