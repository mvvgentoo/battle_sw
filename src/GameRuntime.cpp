#include "GameRuntime.hpp"
#include "Core/AI/DefaultTurnBehavior.hpp"

#include <Core/Entity/Entity.hpp>
#include <Core/Systems/EventBus.hpp>
#include <Core/Systems/EntityManager.hpp>
#include <Core/Systems/EventManager.hpp>
#include <Core/Systems/NavGridSystem.hpp>
#include <Core/FightSystem/CombatSystem.hpp>
#include <Core/Services/INavigationService.hpp>
#include <Core/Navigation/NavigationTask.hpp>
#include <Core/World/World.hpp>
#include <Core/World/EntityHelper.hpp>
#include <Core/World/Simulator.hpp>
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
        _eventBus(std::make_shared<EventBus>()), _world()
{
    auto turnBhv = std::make_unique<DefaultTurnBehavior>();
    _simulator = std::make_shared<Simulator>(std::move(turnBhv));
}

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
                auto cs = std::make_shared<CombatSystem>();
                auto em = EntityManager::create();
                auto eventManager =std::make_shared<EventManager>(_eventBus, _simulator);
                auto navGrid = std::make_shared<NavGridSystem>(cmd.width, cmd.height);
                _world = World::create(navGrid, em, cs, eventManager);
				const int swordmanMeleeRange = 1;
				const int swordsmanDefaultHP = 5;
				const int swordsmanDefaultStrength = 2;
				auto Swordsmanfactory = std::make_unique<SwordsmanFactory>(
					swordsmanDefaultHP, swordmanMeleeRange, swordsmanDefaultStrength);
                _world->getEntityManager().getEntityFactoryRegistry().registerFactory("Swordsman", std::move(Swordsmanfactory));

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
                _world->getEntityManager().getEntityFactoryRegistry().registerFactory("Hunter", std::move(hunterFactory));
                _world->getEventManager().emit(io::MapCreated{cmd.width, cmd.height});
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
                    EntityHelper::createEntity(*_world, unitType, cmd.unitId, {static_cast<int>(cmd.x), static_cast<int>(cmd.y)}, params);
                    _world->getEventManager().emit(io::UnitSpawned{cmd.unitId, unitType, cmd.x, cmd.y});
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
                    EntityHelper::createEntity(*_world,
						unitType, cmd.unitId, {static_cast<int>(cmd.x), static_cast<int>(cmd.y)}, params);
                    _world->getEventManager().emit(io::UnitSpawned{cmd.unitId, unitType, cmd.x, cmd.y});
				}
			})
		.add<io::March>(
			[&](const io::March& cmd)
			{
				if (_world)
				{
                    auto entityHandle = _world->getEntityManager().getEntityByID(cmd.unitId);
					if (auto entity = entityHandle.lock())
					{
						if (auto nav = entity->getServiceByType<NavigationService>())
						{
							auto navTask = std::make_unique<NavigationTask>(
								Position{static_cast<int>(cmd.targetX), static_cast<int>(cmd.targetY)}, 1);
							nav->addNavTask(std::move(navTask));
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

    auto result = _simulator->advance(_world, maxSteps);

    switch (result)
    {
    case Simulator::SimulatorResult::ONE_OR_LESS_LEFT:
        std::cout << "Simulation ended: 1 or 0 units remain." << std::endl;
        break;
    case Simulator::SimulatorResult::NO_ACTED:
        std::cout << "Simulation ended: no units acted at step " << _simulator->currentStep() << std::endl;
        break;
    case Simulator::SimulatorResult::REACH_MAX_STEPS:
        std::cout << "Simulation ended: reached max steps" << std::endl;
        break;
    default:
        break;
    }
}
