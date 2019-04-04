#pragma once
#include "../../Entities/EntityManager.h"

class DeathSystem
{
public:
	static void die();
	static void update();

	static bool dead;

	static std::vector<EntityID> tmp;
};

