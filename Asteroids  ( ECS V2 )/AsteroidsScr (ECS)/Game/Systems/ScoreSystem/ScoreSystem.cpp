#include "ScoreSystem.h"

ComponentMap<Score> ScoreSystem::scores;

ScoreSystem::ScoreSystem() {
	font = TTF_OpenFont("Fonts\\8bitoperator_jve.ttf", 24);
	TM::SetAlphaBlending(texture);
	TM::SetAlpha(texture, 50);
	Uint64 tmp = 0;
	makeScore(tmp, tmp);
}


void ScoreSystem::render() {
	TM::DrawTexture(texture, dest);
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
	SDL_DestroyTexture(texture);
	texture = nullptr;
	std::stringstream charScore; charScore << "Eliminated: " << score;

	SDL_Surface* surfaceTmp = TTF_RenderText_Solid(font, charScore.str().c_str(), fontColor);
	texture = SDL_CreateTextureFromSurface(Game::renderer, surfaceTmp);
	SDL_FreeSurface(surfaceTmp);
	surfaceTmp = nullptr;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	dest.x = 0, dest.y = 0;
	preScore = score;
	TM::SetAlpha(texture, 255);

	
}