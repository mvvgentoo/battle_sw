#ifndef NAVIGATIONTASK_HPP
#define NAVIGATIONTASK_HPP

#include "INavigationTask.hpp"

class NavigationTask : public INavigationTask
{
public:
	explicit NavigationTask(Position target, uint32_t reachDistance);

	virtual ~NavigationTask() = default;

    const Position& getTarget() const override
	{
		return _target;
	}

    virtual bool isReached(const Position& current) const override;

private:
	Position _target;
	uint32_t _reachDistance;
};

#endif	// NAVIGATIONTASK_HPP
