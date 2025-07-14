#ifndef MOVEMENTDATA_HPP
#define MOVEMENTDATA_HPP

#include <memory>
#include "Core/Utils/BaseTypes.hpp"
#include "IDataComponent.hpp"

struct MovementData : public IDataComponent
{
    int maxCellsPerTurn = 1;
    CellFlag cellOccupyType = CellFlag::OCCUPY;
};


#endif // MOVEMENTDATA_HPP
