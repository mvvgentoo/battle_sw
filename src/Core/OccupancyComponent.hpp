#ifndef OCCUPANCYCOMPONENT_HЗЗ
#define OCCUPANCYCOMPONENT_HЗЗ

#include "BaseTypes.hpp"
#include "IBaseComponent.hpp"

class OccupancyComponent : public IBaseComponent
{
public:
	OccupancyComponent(CellFlag occupyType);
	virtual ~OccupancyComponent();
	bool canBeActivated();
	virtual CellFlag getFlag();

private:
	CellFlag _cellFlag;
};

#endif	// OCCUPANCYCOMPONENT_HЗЗ
