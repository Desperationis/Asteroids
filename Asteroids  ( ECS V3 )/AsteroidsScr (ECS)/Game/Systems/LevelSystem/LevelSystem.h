#pragma once
#include "../../json-develop/single_include/nlohmann/json.hpp"
#include "../../Entities/EntityManager.h"
#include <fstream>
#include <string>
#include <sstream>
using namespace nlohmann;

class LevelSystem {
public:
	LevelSystem();
	static void loadLevel(int level);

	static json levels;
	std::fstream file;
	static int currentLevel;
};

