#ifndef MOVEMENTDATA_HPP
#define MOVEMENTDATA_HPP

#include "Core/Utils/BaseTypes.hpp"
#include "IDataComponent.hpp"

#include <memory>

struct MovementData : public IDataComponent
{
	int maxCellsPerTurn;
	CellFlag cellOccupyType;

	MovementData(int cellsPerTurn, CellFlag cellFlag = CellFlag::OCCUPY) :
			maxCellsPerTurn(cellsPerTurn),
			cellOccupyType(cellFlag)
	{}
};

#endif	// MOVEMENTDATA_HPP
