#ifndef GAMERUNTIME_H
#define GAMERUNTIME_H

#include "IO/System/CommandParser.hpp"
#include "IO/System/EventLog.hpp"

#include <memory>

class EventBus;
class World;
class Simulator;

class GameRuntime
{
public:
	GameRuntime();
	~GameRuntime();

	void registerLogging();
	void registerCommands();

	void loadCommands(std::istream& input);

	std::shared_ptr<World> getWorld() const;
	void runScenario(uint64_t maxSteps);

private:
	std::shared_ptr<EventBus> _eventBus;
	std::shared_ptr<World> _world;
	std::shared_ptr<Simulator> _simulator;
	sw::io::CommandParser _parser;
	sw::EventLog _eventLog;
};

#endif	// GAMERUNTIME_H
