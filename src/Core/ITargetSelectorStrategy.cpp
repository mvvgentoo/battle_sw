#include "ITargetSelectorStrategy.hpp"

#include <random>

ITargetSelectorStrategy::ITargetSelectorStrategy() {}

RandomTargetSelector::RandomTargetSelector() {}

std::vector<EntityID> RandomTargetSelector::selectTargets(const std::vector<EntityID>& initialTargets)
{
	if (initialTargets.empty())
	{
		return {};
	}

	std::uniform_int_distribution<std::size_t> dist(0, initialTargets.size() - 1);
	static std::mt19937 rng(std::random_device{}());
	EntityID chosen = initialTargets[dist(rng)];
	return {chosen};
}
