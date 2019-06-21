#pragma once
#include "../../Entities/EntityManager.h"

class DeathSystem
{
public:
	static void die();
	static void update();
	static void render();

	static bool dead;
	static Uint8 lives;

	static std::vector<EntityID> tmp;
};

