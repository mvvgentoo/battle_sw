#ifndef IRANGEMODIFIERVISITOR_HPP
#define IRANGEMODIFIERVISITOR_HPP

class IRangeModifierVisitor
{
public:
	virtual ~IRangeModifierVisitor() = default;

	virtual void visitMeleeRangeMaxModifier(int delta) = 0;
	virtual void visitRangedRangeMinModifier(int delta) = 0;
	virtual void visitRangedRangeMaxModifier(int delta) = 0;
};

class IRangeModifiable
{
public:
	virtual ~IRangeModifiable() = default;
	virtual void accept(IRangeModifierVisitor& visitor) const = 0;
};

class RangeModifierCollector : public IRangeModifierVisitor
{
public:
	RangeModifierCollector(int meleeMax, int rangedMin, int rangedMax);

	void visitMeleeRangeMaxModifier(int delta) override;
	void visitRangedRangeMinModifier(int delta) override;
	void visitRangedRangeMaxModifier(int delta) override;

	int meleeMax() const;
	int rangedMin() const;
	int rangedMax() const;

private:
	int _meleeMax = 0;
	int _rangedMin = 0;
	int _rangedMax = 0;
};

#endif	// IRANGEMODIFIERVISITOR_HPP
