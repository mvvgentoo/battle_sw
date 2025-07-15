#ifndef ITICKPROVIDER_HPP
#define ITICKPROVIDER_HPP

#include <cstdint>

class ITickProvider
{
public:
	virtual ~ITickProvider() = default;
	virtual uint32_t currentStep() const = 0;
};

#endif	// ITICKPROVIDER_HPP
