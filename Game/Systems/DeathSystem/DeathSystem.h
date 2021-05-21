#pragma once
#include "../../Entities/EntityManager.h"

class DeathSystem
{
public:
	static void die();
	static void update();
	static void render();
	static bool timer(int delay);

	static bool dead;
	static int lives;
	static Uint64 now;

	static std::vector<EntityID> tmp;

};

