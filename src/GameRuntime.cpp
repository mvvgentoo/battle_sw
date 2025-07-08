#include "GameRuntime.hpp"

#include <Core/Entity.hpp>
#include <Core/EventBus.hpp>
#include <Core/INavigationService.hpp>
#include <Core/NavigationTask.hpp>
#include <Core/World.hpp>
#include <Features/HunterFactory.hpp>
#include <Features/SwordsmanFactory.hpp>
#include <IO/Commands/CreateMap.hpp>
#include <IO/Commands/March.hpp>
#include <IO/Commands/SpawnHunter.hpp>
#include <IO/Commands/SpawnSwordsman.hpp>
#include <IO/Events/MapCreated.hpp>
#include <IO/Events/MarchEnded.hpp>
#include <IO/Events/MarchStarted.hpp>
#include <IO/Events/UnitAttacked.hpp>
#include <IO/Events/UnitDied.hpp>
#include <IO/Events/UnitMoved.hpp>
#include <IO/Events/UnitSpawned.hpp>
#include <IO/System/CommandParser.hpp>
#include <IO/System/EventLog.hpp>
#include <IO/System/PrintDebug.hpp>

GameRuntime::GameRuntime() :
		_eventBus(std::make_shared<EventBus>()),
		_world()
{}

GameRuntime::~GameRuntime() {}

std::shared_ptr<World> GameRuntime::getWorld() const
{
	return _world;
}

template <typename Event>
void subscribeToLog(std::shared_ptr<EventBus> eventBus, sw::EventLog& log)
{
	if (eventBus)
	{
		eventBus->subscribe<Event>([&log](uint64_t tick, const Event& event) { log.log(tick, event); });
	}
}

void GameRuntime::registerLogging()
{
	using namespace sw;
	subscribeToLog<io::MapCreated>(_eventBus, _eventLog);
	subscribeToLog<io::UnitSpawned>(_eventBus, _eventLog);
	subscribeToLog<io::MarchStarted>(_eventBus, _eventLog);
	subscribeToLog<io::MarchEnded>(_eventBus, _eventLog);
	subscribeToLog<io::UnitMoved>(_eventBus, _eventLog);
	subscribeToLog<io::UnitAttacked>(_eventBus, _eventLog);
	subscribeToLog<io::UnitDied>(_eventBus, _eventLog);
}

void GameRuntime::registerCommands()
{
	using namespace sw;
	_parser
		.add<io::CreateMap>(
			[&](const io::CreateMap& cmd)
			{
				_world = std::make_shared<World>(cmd.width, cmd.height);
				const int swordmanMeleeRange = 1;
				const int swordsmanDefaultHP = 5;
				const int swordsmanDefaultStrength = 2;
				auto Swordsmanfactory = std::make_unique<SwordsmanFactory>(
					swordsmanDefaultHP, swordmanMeleeRange, swordsmanDefaultStrength);
				_world->registerFactory("Swordsman", std::move(Swordsmanfactory));

				const int hunterMeleeRange = 1;
				const int hunterMinRange = 2;
				const int hunterMaxRange = 4;
				const int hunterDefaultHP = 10;
				const int hunterDefaultStrength = 1;
				const int hunterDefaultAgility = 5;
				auto hunterFactory = std::make_unique<HunterFactory>(
					hunterDefaultHP,
					hunterMinRange,
					hunterMaxRange,
					hunterMeleeRange,
					hunterDefaultAgility,
					hunterDefaultStrength);
				_world->registerFactory("Hunter", std::move(hunterFactory));

				_world->setEventBus(_eventBus);
				_world->emit(io::MapCreated{cmd.width, cmd.height});
			})
		.add<io::SpawnSwordsman>(
			[&](const io::SpawnSwordsman& cmd)
			{
				if (_world)
				{
					UnitParams params;
					params.set("hp", static_cast<int>(cmd.hp));
					params.set("strength", static_cast<int>(cmd.strength));
					auto unitType = "Swordsman";
					_world->createEntity(
						unitType, cmd.unitId, {static_cast<int>(cmd.x), static_cast<int>(cmd.y)}, params);
					_world->emit(io::UnitSpawned{cmd.unitId, unitType, cmd.x, cmd.y});
				}
			})
		.add<io::SpawnHunter>(
			[&](const io::SpawnHunter& cmd)
			{
				if (_world)
				{
					UnitParams params;
					params.set("hp", static_cast<int>(cmd.hp));
					params.set("strength", static_cast<int>(cmd.strength));
					params.set("maxRange", static_cast<int>(cmd.range));
					params.set("agility", static_cast<int>(cmd.agility));

					auto unitType = "Hunter";
					_world->createEntity(
						unitType, cmd.unitId, {static_cast<int>(cmd.x), static_cast<int>(cmd.y)}, params);
					_world->emit(io::UnitSpawned{cmd.unitId, unitType, cmd.x, cmd.y});
				}
			})
		.add<io::March>(
			[&](const io::March& cmd)
			{
				if (_world)
				{
					auto entityHandle = _world->getEntityByID(cmd.unitId);
					if (auto entity = entityHandle.lock())
					{
						if (auto nav = entity->getServiceByType<NavigationService>())
						{
							auto navTask = std::make_unique<NavigationTask>(
								Position{static_cast<int>(cmd.targetX), static_cast<int>(cmd.targetY)}, 1);
							nav->addNavTask(std::move(navTask));
							auto entityPos = entity->getPosition();
							_world->emit(io::MarchStarted{
								cmd.unitId,
								static_cast<uint32_t>(entityPos.x),
								static_cast<uint32_t>(entityPos.y),
								cmd.targetX,
								cmd.targetY});
						}
					}
				}
			});
}

void GameRuntime::loadCommands(std::istream& input)
{
	_parser.parse(input);
}

void GameRuntime::runScenario(uint64_t maxSteps)
{
	if (_world == nullptr)
	{
		std::cerr << "No world initialized" << std::endl;
		return;
	}

	for (uint64_t step = 1; step <= maxSteps; ++step)
	{
		_world->setStep(step);

		auto entityAliveFunctor = [](const std::unique_ptr<Entity>& e)
		{
			return e->isAlive();
		};

		auto alive = _world->allEntitiesIf(entityAliveFunctor);
		if (alive.size() <= 1)
		{
			std::cout << "Simulation ended: " << alive.size() << " units remain." << std::endl;
			break;
		}

		bool anyActed = false;
		for (auto handle : alive)
		{
			if (auto entity = handle.lock())
			{
				auto result = entity->take_turn(_world);
				if (result == ITurnBehavior::TurnStatus::SUCCESS)
				{
					anyActed = true;
				}
			}
		}

		if (!anyActed)
		{
			std::cout << "Simulation ended: no units acted at step " << step << std::endl;
			;
			break;
		}
	}
}
