#include "NavGridSystem.hpp"

NavGridSystem::NavGridSystem(int w, int h) :
		_w(w),
		_h(h)
{
	_gridOccupied.resize(w * h, 0);
	_gridShared.resize(w * h);
}

NavGridSystem::~NavGridSystem() {}

bool NavGridSystem::updatePosition(EntityID id, Position old_pos, Position new_pos, CellFlag flag)
{
	if (!inBounds(new_pos))
	{
		return false;
	}

	size_t oldIndex = old_pos.y * getWidth() + old_pos.x;
	size_t newIndex = new_pos.y * getWidth() + new_pos.x;

	switch (flag)
	{
		case CellFlag::OCCUPY:
		{
			if (inBounds(old_pos) && _gridOccupied[oldIndex] == id)
			{
				_gridOccupied[oldIndex] = 0;
			}
			_gridOccupied[newIndex] = id;
		}
		break;
		case CellFlag::SHARE:
		{
			if (inBounds(old_pos))
			{
				auto& oldShared = _gridShared[oldIndex];
				std::erase(oldShared, id);
			}

			auto& shared = _gridShared[newIndex];
			shared.push_back(id);
		}
		break;
		default:
			//log_error
			return false;
	}

	return true;
}

bool NavGridSystem::inBounds(const Position& pos) const
{
	return pos.x > 0 && pos.x < getWidth() && pos.y > 0 && pos.y < getHeight();
}

bool NavGridSystem::isOccupied(const Position& pos) const
{
	if (!inBounds(pos))
	{
		return false;
	}

	return _gridOccupied[pos.y * getWidth() + pos.x] != 0;
}

int NavGridSystem::getHeight() const
{
	return _h;
}

int NavGridSystem::getWidth() const
{
	return _w;
}
