#pragma once
#include "../EntityManager.h"

class Bullet : public Rect
{
private:
	float dx = 0.0f, dy = 0.0f, x = 0.0f, y = 0.0f;
	double angle;
	bool dead = false;
public:
	Bullet(int x, int y, float dx, float dy, double angle);
	void update();
	void render();
	inline bool hasDied() const { return dead; }

	SDL_Rect scr;
};

