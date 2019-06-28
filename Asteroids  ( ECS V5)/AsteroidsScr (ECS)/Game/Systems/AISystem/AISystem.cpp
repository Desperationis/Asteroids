#include "AISystem.h"
#include "../MovementSystem/MovementSystem.h"
#include "../BulletSystem/BulletSystem.h"
#include "../CollisionSystem/CollisionSystem.h"

ComponentMap<AIData> AISystem::AI;
int frame = 0;
Uint64 bulletID = 0;
void AISystem::update() {
	frame++;
	for (auto it = AI.begin(); it != AI.end(); it++) {
		switch (it.value().type) {
		case UFO:
			auto& playerData = MovementSystem::positions[EntityManager::currentVessel];
			auto& ufoData = MovementSystem::positions[it.key()];
			auto& ufoVel = MovementSystem::velocities[it.key()];
			float angle = atan2(playerData.y - ufoData.y, playerData.x - ufoData.x) * (180.0f / M_PI) + ((rand() % 16 - 8));
			float xOffset = (cos(frame / 30.0f) * 15.0f);
			float yOffset = (sin(frame / 30.0f) * 15.0f);

			switch (it.value().state) {
			case CHASE:
				it.value().chaseTimer++;
				ufoVel.dx = cos(angle * 0.0174533f) + (cos(angle * 0.0174533f) * xOffset);
				ufoVel.dy = sin(angle * 0.0174533f) + (sin(angle * 0.0174533f) * yOffset);
				//I have no clue how this works but it creates a nice loopyloop path
				break;
			case SHOOT:
				ufoVel.dx = ufoVel.dy = 0;
				it.value().shootTimer++;
				if (frame % 20 == 0) {
					EntityID id = BulletSystem::allocateBullet(0.0);
					EntityManager::entities[id].mask |= COMPONENT_ENEMYBULLET;
					MovementSystem::formatIDPosition(id, CollisionSystem::rects[it.key()].center[0], CollisionSystem::rects[it.key()].center[1] + 10, ufoData.angle);
					MovementSystem::formatIDVelocity(id, cos(angle * 0.0174533) * BULLET::MOVEMENT_SPEED, sin(angle * 0.0174533f) * BULLET::MOVEMENT_SPEED, false);
					bulletID++; std::stringstream tmp; tmp << "EnemyBullet " << bulletID;
					EntityManager::names[id].name = tmp.str();
				}
				break;
			}

			if (it.value().state == CHASE && it.value().chaseTimer % 181 == 0) it.value().state = SHOOT;
			else if (it.value().state == SHOOT && it.value().shootTimer % 60 == 0) it.value().state = CHASE;
			break;
		}
	}
}

void AISystem::allocateID(const EntityID& id) {
	if (EntityManager::names[id].name.find("UFO") != std::string::npos) {
		AI[id].type = UFO;
		AI[id].state = CHASE;
	}
}

void AISystem::freeID(const EntityID& id) {
	AI.erase(id);
}