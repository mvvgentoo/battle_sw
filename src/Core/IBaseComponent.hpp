#ifndef IBASECOMPONENT_H
#define IBASECOMPONENT_H

class IBaseComponent
{
public:
	IBaseComponent();
	virtual ~IBaseComponent();
	virtual bool canBeActivated() = 0;
};

#endif	// IBASECOMPONENT_H
