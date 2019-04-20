#include "LevelSystem.h"
#include "../ScoreSystem/ScoreSystem.h"
#include "../UFOSystem/UFOSystem.h"

json LevelSystem::levels;
int LevelSystem::currentLevel = 0;
Font LevelSystem::font;

LevelSystem::LevelSystem() {
	file.open("Game\\systems\\LevelSystem\\Levels.json");
	file >> levels;
	file.close();

	font.fontColor.r = font.fontColor.g = font.fontColor.b = 0;
	font.fontDest.x = 0, font.fontDest.y = ScoreSystem::font.fontDest.h;
	FontSystem::setUp(font, "Fonts\\emulogic.ttf", 20);
}

void LevelSystem::loadMeteorData(int level, const char* loading, MeteorSystem::METEOR size, float speed) {
	int location;
	MeteorData data;
	//if (currentLevel > 7) level = 7;
	std::stringstream tmp; tmp << "Level " << level;

	for (int i = 0; i < levels[tmp.str().c_str()][loading]; i++) {
		location = rand() % 4;
		switch (location) {
		case 0: //left
			data.x = 0; data.y = rand() % 1080;
			break;
		case 1: // top
			data.x = rand() % 1920, data.y = 5000; // 5000 so it teleports to top
			break;
		case 2: // right
			data.x = 1919, data.y = rand() % 1080;
			break;
		case 3: //bottom
			data.x = rand() % rand() % 1920, data.y = 1079;
			break;
		}
		data.angle = rand() % 361;
		data.dx = cos(data.angle * 0.0174533f) * speed;
		data.dy = sin(data.angle * 0.0174533f) * speed;
		data.size = size;
		EntityManager::queue.push_back(data);
	}
}

void LevelSystem::loadLevel(int level) {
	currentLevel = level;
	std::stringstream tmp; tmp << "Level " << level;
	loadMeteorData(level, "small-meteor", MeteorSystem::METEOR::SMALL, METEOR_::SPEED * 3.0f);
	loadMeteorData(level, "medium-meteor", MeteorSystem::METEOR::MEDIUM, METEOR_::SPEED * 1.5f);
	loadMeteorData(level, "large-meteor", MeteorSystem::METEOR::LARGE, METEOR_::SPEED);
	loadMeteorData(level, "xlarge-meteor", MeteorSystem::METEOR::XLARGE, METEOR_::SPEED / 1.5f);
	loadMeteorData(level, "gigalarge-meteor", MeteorSystem::METEOR::GIGALARGE, METEOR_::SPEED / 3.0f);
	loadMeteorData(level, "god-meteor", MeteorSystem::METEOR::DEUS, METEOR_::SPEED / 6.0f);

	for (int i = 0; i < levels[tmp.str().c_str()]["ufo"]; i++) {
		float angle = (rand() % 3600) / 10.0f;
		UFOSystem::allocateUFO(cos(angle * 0.0174533f) * 450, sin(angle * 0.0174533f) * 450, UFOSystem::POWERUP::RAPIDFIRE);
	}
}

int tmp = -1;
void LevelSystem::render() {
	if (tmp != currentLevel) {
		tmp = currentLevel;
		std::stringstream stringTmp; stringTmp << "Level:" << currentLevel;
		FontSystem::setText(font, stringTmp.str().c_str());
	}

	SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(Game::renderer, &font.fontDest);
	TM::DrawTexture(font.fontTexture, font.fontDest);
}