#include "Game/GameRuntime.hpp"

#include <fstream>
#include <iostream>

int main(int argc, char** argv)
{
	using namespace sw;

	if (argc != 2)
	{
		throw std::runtime_error("Error: No file specified in command line argument");
	}

	std::ifstream file(argv[1]);
	if (!file)
	{
		throw std::runtime_error("Error: File not found - " + std::string(argv[1]));
	}

	std::cout << "\n\nEvents:\n";

	GameRuntime runtime;
	runtime.registerLogging();
	runtime.registerCommands();
	runtime.loadCommands(file);
	runtime.runScenario(1000);

	return 0;
}
