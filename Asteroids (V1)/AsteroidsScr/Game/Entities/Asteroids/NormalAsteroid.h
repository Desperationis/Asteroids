#pragma once
#include "../EntityManager.h"
#include "../Spaceship/Bullet.h"

class NormalAsteroid : public Rect
{
public:
	NormalAsteroid(int x, int y);
	
	void update(std::vector<Bullet> bullets);
	void render();
private:
	float x = 0.0f, y = 0.0f, dx = 0.0f, dy = 0.0f;
	float DEGTORAD = 0.017453f;
};

