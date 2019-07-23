#pragma once
#include "../../Entities/EntityManager.h"
#include <sstream>
#include <string>

class UFOSystem {
public:
	enum POWERUP {RAPIDFIRE, GRAPESHOT, INFINITYBULLET, DMG};

	static void allocateUFO(int x, int y, POWERUP pwr);
	static void allocatePowerUp(const EntityID& id, POWERUP powerUp);

	static EntityID nameID;
	static ComponentMap<EntityMask> powerUps;
};
