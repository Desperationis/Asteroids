#pragma once
#include "../../Entities/EntityManager.h"
#include "../FontSystem/FontSystem.h"

class ScoreSystem {
public:
	ScoreSystem();

	void update();
	void render();
	void allocateID(const EntityID& id);
	void freeID(const EntityID& id);
	void makeScore(Uint64& score, Uint64& preScore);

	static Font font;

	static ComponentMap<Score> scores;
};
