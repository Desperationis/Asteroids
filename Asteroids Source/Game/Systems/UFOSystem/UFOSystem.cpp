#include "UFOSystem.h"
#include "../MovementSystem/MovementSystem.h"
#include "../CollisionSystem/CollisionSystem.h"
#include "../AISystem/AISystem.h"

Uint64 UFOSystem::nameID = 0;
ComponentMap<EntityMask> UFOSystem::powerUps;

void UFOSystem::allocateUFO(int x, int y, POWERUP pwr) {
	nameID++;
	std::stringstream stringTmp; stringTmp << "UFO " << nameID;
	auto& currentID = EntityManager::allocateEntity(stringTmp.str().c_str(), x, y, 70, 70, 200, 0, 50, 50, COMPONENT_UFO).id;
	powerUps[currentID] = pwr;
	MovementSystem::positions[currentID].angle -= 90;
	CollisionSystem::rects[currentID].hitboxScaling = 2.0f;
}

Uint64 namePowerUp = 0;

void UFOSystem::allocatePowerUp(const EntityID& id, UFOSystem::POWERUP powerUp) {
	namePowerUp++;
	std::stringstream stringTmp; stringTmp << "PowerUp " << namePowerUp;
	int num = 0;

	switch (powerUp) {
	case RAPIDFIRE:
		num = 0;
		break;
	case GRAPESHOT:
		num = 50;
		break;
	case INFINITYBULLET:
		num = 100;
		break;
	case DMG:
		num = 150;
		break;
	}

	auto& currentID = EntityManager::allocateEntity(stringTmp.str().c_str(), CollisionSystem::rects[id].center[0], CollisionSystem::rects[id].center[1], 20, 20, num, 50, 50, 50, COMPONENT_POWERUP).id;
	
	EntityMask powerUpTmp = 0;
	switch (powerUp) {
	case RAPIDFIRE:
		powerUpTmp = POWERUP_RAPIDFIRE;
		break;
	case GRAPESHOT:
		powerUpTmp = POWERUP_GRAPESHOT;
		break;
	case INFINITYBULLET:
		powerUpTmp = POWERUP_INFINITYBULLET;
		break;
	case DMG:
		powerUpTmp = POWERUP_DMG;
	}
	
	powerUps[currentID] = powerUpTmp;
	MovementSystem::positions[currentID].angle -= 90;
	CollisionSystem::rects[currentID].hitboxScaling = 0.8f;
	MovementSystem::velocities[currentID] = MovementSystem::velocities[id];
}


