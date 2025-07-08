#include "OccupancyComponent.hpp"

OccupancyComponent::OccupancyComponent(CellFlag occupyType) :
		_cellFlag(occupyType)
{}

OccupancyComponent::~OccupancyComponent() {}

bool OccupancyComponent::canBeActivated()
{
	return true;
}

CellFlag OccupancyComponent::getFlag()
{
	return _cellFlag;
}
