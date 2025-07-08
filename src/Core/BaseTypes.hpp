#ifndef BASETYPES_HPP
#define BASETYPES_HPP

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

using EntityID = uint32_t;

#endif	// BASETYPES_HPP
