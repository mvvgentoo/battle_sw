#ifndef MOVEMENTDATA_HPP
#define MOVEMENTDATA_HPP

#include <memory>
#include "IDataComponent.hpp"

struct MovementData : public IDataComponent
{
    int maxCellsPerTurn = 1;
};


#endif // MOVEMENTDATA_HPP
