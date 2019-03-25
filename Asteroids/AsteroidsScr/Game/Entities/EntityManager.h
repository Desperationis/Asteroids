#pragma once
#include "../Game/Game.h"
#include "../../Tools/Rect.h"
//note: don't define structs of classes; forward-declare

class Spaceship; class NormalAsteroid;
class EntityManager
{
public:
	EntityManager();

	void update();
	void render();

	static SDL_Texture* spritesheet;

private:
	Spaceship* spaceship = nullptr;
	NormalAsteroid* asteroid = nullptr;
};

//typename EntityManager EM;

