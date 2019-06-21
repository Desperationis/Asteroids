#pragma once
#include "../../Entities/EntityManager.h"

class ScoreSystem {
public:
	ScoreSystem();

	void update();
	void render();
	void allocateID(const EntityID& id);
	void freeID(const EntityID& id);
	void makeScore(Uint64& score, Uint64& preScore);

	TTF_Font* font;
	SDL_Color fontColor{ 255,255,255,255 };
	SDL_Texture* texture;
	SDL_Rect dest;

	static ComponentMap<Score> scores;
};
