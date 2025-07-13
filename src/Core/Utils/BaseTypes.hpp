#ifndef BASETYPES_HPP
#define BASETYPES_HPP

#include <algorithm>
#include <cstdint>


struct Position
{
	using _type = int;
	_type x, y;

	Position(_type x_, _type y_) :
			x(x_),
			y(y_)
	{}

	bool operator==(const Position& rhs)
	{
		return x == rhs.x && y == rhs.y;
	}
};

enum CellFlag
{
	OCCUPY,
	SHARE
};

uint32_t chebyshevDistance(const Position &a, const Position &b)
{
    return std::max((a.x > b.x ? a.x - b.x : b.x - a.x), (a.y > b.y ? a.y - b.y : b.y - a.y));
}


using EntityID = uint32_t;

#endif	// BASETYPES_HPP
