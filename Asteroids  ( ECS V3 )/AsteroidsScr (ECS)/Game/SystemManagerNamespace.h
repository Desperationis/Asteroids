#pragma once

#include "Systems/MovementSystem/MovementSystem.h"
#include "Systems/BulletSystem/BulletSystem.h"
#include "Systems/MeteorSystem/MeteorSystem.h"
#include "Systems/ScoreSystem/ScoreSystem.h"
#include "Systems/DeathSystem/DeathSystem.h"
#include "Systems/RenderingSystem/RenderingSystem.h"
#include "Systems/InputSystem/InputSystem.h"
#include "Systems/CollisionSystem/CollisionSystem.h"
#include "Systems/HealthDamageSystem/HealthDamageSystem.h"
#include "Systems/LevelSystem/LevelSystem.h"

namespace SystemsNamespace {
	InputSystem* inputSystem = nullptr;
	MovementSystem* movementSystem = nullptr;
	RenderingSystem* renderingSystem = nullptr;
	CollisionSystem* collisionSystem = nullptr;
	BulletSystem* bulletSystem = nullptr;
	ScoreSystem* scoreSystem = nullptr;
	DeathSystem* deathSystem = nullptr;
	MeteorSystem* meteorSystem = nullptr;
	HealthDamageSystem* healthDamageSystem = nullptr;
	LevelSystem* levelSystem = nullptr;

	void initSystems() {
		movementSystem = new MovementSystem();
		renderingSystem = new RenderingSystem();
		inputSystem = new InputSystem();
		healthDamageSystem = new HealthDamageSystem();
		meteorSystem = new MeteorSystem();
		collisionSystem = new CollisionSystem();
		bulletSystem = new BulletSystem();
		scoreSystem = new ScoreSystem();
		deathSystem = new DeathSystem();
		levelSystem = new LevelSystem();
	}
	
	void allocateSystemMemory() {
		MovementSystem::positions.reserve(ENTITY::RESERVE_ENTITIES);
		MovementSystem::velocities.reserve(ENTITY::RESERVE_ENTITIES);
		RenderingSystem::textures.reserve(ENTITY::RESERVE_ENTITIES);
		CollisionSystem::rects.reserve(ENTITY::RESERVE_ENTITIES);

		for (int i = 0; i < 100; i++) {
			CollisionSystem::nodes.push_back(ComponentMap<EntityID>());
			CollisionSystem::nodes[i].reserve(2);
		}
	}
};
