#pragma once
#include "json.hpp"
#include "../FontSystem/FontSystem.h"
#include "../../Entities/EntityManager.h"
#include "../MeteorSystem/MeteorSystem.h"
#include <fstream>
#include <string>
#include <sstream>
using namespace nlohmann;

class LevelSystem {
public:
	LevelSystem();
	static void loadLevel(int level);
	static void loadMeteorData(int level, const char* loading, MeteorSystem::METEOR size, float speed);
	static void render();

	static json levels;
	std::fstream file;
	static Font font;
	static int currentLevel;
};

