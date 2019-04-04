#include "ScoreSystem.h"

ComponentMap<Score> ScoreSystem::scores;

ScoreSystem::ScoreSystem() {
	font.color.r = font.color.g = font.color.b = 255;
	font.dest.x = 0, font.dest.y = 0;
	FontSystem::setUp(font, "Fonts\\8bitoperator_jve.ttf", 64);
	FontSystem::setText(font, "0", font.color);

	Uint64 tmp = 0;
	makeScore(tmp, tmp);
}


void ScoreSystem::render() {
	TM::DrawTexture(font.texture, font.dest);
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
	SDL_DestroyTexture(font.texture);
	font.texture = nullptr;
	std::stringstream charScore; charScore << "Score: " << score;

	FontSystem::setText(font, charScore.str().c_str(), font.color);

	preScore = score;
}