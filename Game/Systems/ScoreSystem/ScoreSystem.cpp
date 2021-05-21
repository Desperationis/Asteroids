#include "ScoreSystem.h"

ComponentMap<Score> ScoreSystem::scores;
Font ScoreSystem::font;

ScoreSystem::ScoreSystem() {
	font.fontColor.r = font.fontColor.g = font.fontColor.b = 0;
	font.fontDest.x = 0, font.fontDest.y = 0;
	FontSystem::setUp(font, "../Fonts/emulogic.ttf", 20);
	FontSystem::setText(font, "0");

	Uint64 tmp = 0;
	makeScore(tmp, tmp);
}


void ScoreSystem::render() {
	SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(Game::renderer, &font.fontDest);
	TM::DrawTexture(font.fontTexture, font.fontDest);
}

void ScoreSystem::update() {
	for (auto it = scores.begin(); it != scores.end(); it++) {
		if (it->second.preScore != it->second.score) {
			makeScore(it.value().score, it.value().preScore);
		}
	}
}

void ScoreSystem::allocateID(const EntityID& id) {
	scores[id] = Score{ };
}

void ScoreSystem::freeID(const EntityID& id) {
	scores.erase(id);
}

void ScoreSystem::makeScore(Uint64& score, Uint64& preScore) {
	SDL_DestroyTexture(font.fontTexture);
	font.fontTexture = nullptr;
	std::stringstream charScore; charScore << "Score:" << score;

	FontSystem::setText(font, charScore.str().c_str());

	preScore = score;
}
