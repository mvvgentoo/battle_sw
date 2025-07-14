#ifndef MOVEMENTDATA_HPP
#define MOVEMENTDATA_HPP

#include <memory>
#include "Core/Utils/BaseTypes.hpp"
#include "IDataComponent.hpp"

struct MovementData : public IDataComponent
{
    int maxCellsPerTurn;
    CellFlag cellOccupyType;

    MovementData(int cellsPerTurn, CellFlag cellFlag = CellFlag::OCCUPY) : maxCellsPerTurn(cellsPerTurn), cellOccupyType(cellFlag)
    {

    }
};


#endif // MOVEMENTDATA_HPP
