#include "IRangeModifierVisitor.hpp"

RangeModifierCollector::RangeModifierCollector(int meleeMax, int rangedMin, int rangedMax) :
		_meleeMax(meleeMax),
		_rangedMin(rangedMin),
		_rangedMax(rangedMax)
{}

void RangeModifierCollector::visitMeleeRangeMaxModifier(int delta)
{
	_meleeMax += delta;
}

void RangeModifierCollector::visitRangedRangeMinModifier(int delta)
{
	_rangedMin += delta;
}

void RangeModifierCollector::visitRangedRangeMaxModifier(int delta)
{
	_rangedMax += delta;
}

int RangeModifierCollector::meleeMax() const
{
	return _meleeMax;
}

int RangeModifierCollector::rangedMin() const
{
	return _rangedMin;
}

int RangeModifierCollector::rangedMax() const
{
	return _rangedMax;
}
