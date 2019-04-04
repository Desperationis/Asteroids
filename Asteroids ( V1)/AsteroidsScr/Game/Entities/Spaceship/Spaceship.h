#pragma once
#include "../EntityManager.h"
#include "Bullet.h"

class Spaceship : public Rect
{
public:
	Spaceship(int x, int y);
	
	void render();
	void update();

public:
	std::vector<Bullet> bullets;
private:
	void getInput();
	void hinderSpeed();
	void loopAround();
	bool checkTimeInterval(int timer);
private:
	double angle = 0.0;
	Uint64 now = SDL_GetTicks(), then = SDL_GetTicks();
	SDL_Rect scr;
	float x = 0.0f, y = 0.0f, dx = 0.0f, dy = 0.0f;
	bool thrust = false, spacePressed = false;;
	float DEGTORAD = 0.017453f; //Used to convert angles into radians



	
};

