#ifndef NAVGRID_HPP
#define NAVGRID_HPP

#include "Core/Utils/BaseTypes.hpp"

#include <list>
#include <vector>

class NavGridSystem
{
public:
	NavGridSystem(int w, int h);
	~NavGridSystem();

	int getHeight() const;
	int getWidth() const;

	bool updatePosition(EntityID id, Position old_pos, Position new_pos, CellFlag flag);
	bool inBounds(const Position& pos) const;
	bool isOccupied(const Position& pos) const;

private:
	int _w, _h;
	std::vector<EntityID> _gridOccupied;
	std::vector<std::list<EntityID>> _gridShared;
};

#endif	// NAVGRID_HPP
