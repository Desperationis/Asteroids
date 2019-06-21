#include "LevelSystem.h"
#include "../MeteorSystem/MeteorSystem.h"

json LevelSystem::levels;
int LevelSystem::currentLevel = 0;

LevelSystem::LevelSystem() {
	file.open("Game\\systems\\LevelSystem\\Levels.json");
	file >> levels;
	file.close();
}


void LevelSystem::loadLevel(int level) {
	if (currentLevel > 7) level = 7;
	std::stringstream tmp; tmp << "Level " << level;

	MeteorData data;
	data.x = 1800; data.y = 300;

	for (int i = 0; i < levels[tmp.str().c_str()]["small-meteor"]; i++) {
		data.angle = rand() % 361;
		data.dx = cos(data.angle * 0.0174533f) * METEOR_::SPEED * 3;
		data.dy = sin(data.angle * 0.0174533f) * METEOR_::SPEED * 3;
		data.size = MeteorSystem::METEOR::SMALL;
		EntityManager::queue.push_back(data);
	}
	for (int i = 0; i < levels[tmp.str().c_str()]["medium-meteor"]; i++) {
		data.angle = rand() % 361;
		data.dx = cos(data.angle * 0.0174533f) * METEOR_::SPEED * 1.5;
		data.dy = sin(data.angle * 0.0174533f) * METEOR_::SPEED * 1.5;
		data.size = MeteorSystem::METEOR::MEDIUM;
		EntityManager::queue.push_back(data);
	}
	for (int i = 0; i < levels[tmp.str().c_str()]["large-meteor"]; i++) {
		data.angle = rand() % 361;
		data.dx = cos(data.angle * 0.0174533f) * METEOR_::SPEED;
		data.dy = sin(data.angle * 0.0174533f) * METEOR_::SPEED;
		data.size = MeteorSystem::METEOR::LARGE;
		EntityManager::queue.push_back(data);
	}
}