#include "../BulletSystem/BulletSystem.h"
#include "../InputSystem/InputSystem.h"
#include "../MovementSystem/MovementSystem.h"
#include "../CollisionSystem/CollisionSystem.h"
#include "../RenderingSystem/RenderingSystem.h"
#include "../HealthDamageSystem/HealthDamageSystem.h"

EntityID nameID = 0;
bool spacePressed = false;
void BulletSystem::update() {
	auto& currentID = EntityManager::currentVessel;
	auto& currentMask = EntityManager::entities[currentID].mask;

	now++;
	if ((currentMask & POWERUP_RAPIDFIRE) == POWERUP_RAPIDFIRE && timer(BULLET::RAPIDFIRE_TICKS)) { shoot(); }
	if ((currentMask & POWERUP_RAPIDFIRE) == POWERUP_RAPIDFIRE && timer(BULLET::RAPIDFIRE_LENGTH)) {
		currentMask = currentMask & ~POWERUP_RAPIDFIRE;
	}

	if (InputSystem::usingController) {
		if ((InputSystem::GetButton(SDL_CONTROLLER_BUTTON_A) && !spacePressed)) {
			shoot();
		}
		spacePressed = InputSystem::GetButton(SDL_CONTROLLER_BUTTON_A);
	}
	if (!InputSystem::usingController) {
		if ((InputSystem::keys[SDL_SCANCODE_SPACE] && !spacePressed)) {
			shoot();
		}
		spacePressed = InputSystem::keys[SDL_SCANCODE_SPACE];
	}
}

void BulletSystem::shoot() {
	auto& currentID = EntityManager::currentVessel;
	auto& currentMask = EntityManager::entities[currentID].mask;

	if ((currentMask & POWERUP_GRAPESHOT) == POWERUP_GRAPESHOT) {
		allocateBullet(-15);
		allocateBullet(15);
	}

	allocateBullet(0.0);
	recoil();
	nameID++;
}
void BulletSystem::allocateBullet(double angleOffset = 0.0) {
	EntityID& currentVessel = EntityManager::currentVessel;
	std::stringstream tmp; tmp << "Bullet " << nameID;
	EntityMask mask = COMPONENT_BULLET;
	if ((EntityManager::entities[EntityManager::currentVessel].mask & POWERUP_INFINITYBULLET) == POWERUP_INFINITYBULLET) {
		mask |= COMPONENT_WALLLOOP;
		mask &= ~COMPONENT_WALLDEATH;
	}
	auto currentAngle = MovementSystem::positions[currentVessel].angle;
	auto& currentVelocity = MovementSystem::velocities[currentVessel];
	auto& currentRect = CollisionSystem::rects[currentVessel];
	auto& currentDest = RenderingSystem::textures[currentVessel];
	auto& currentID = EntityManager::allocateEntity(tmp.str().c_str(),
		(currentRect.center[0] - 3) + (cos((currentAngle + angleOffset) * 0.0174533f) * (currentDest.dest.w / 2.2f)),
		(currentRect.center[1] - 3) + (sin((currentAngle + angleOffset) * 0.0174533f) * (currentDest.dest.h / 2.2f)),
		7, 7, 25, 25, 2, 2, mask).id;
	MovementSystem::positions[currentID].angle = currentAngle;

	MovementSystem::formatIDVelocity(currentID,
		static_cast<float>((float)cos((currentAngle + angleOffset) * 0.0174533f)) * BULLET::MOVEMENT_SPEED, 
		static_cast<float>((float)sin((currentAngle + angleOffset) * 0.0174533f)) * BULLET::MOVEMENT_SPEED, false);
	HealthDamageSystem::damages[currentID].hardness = 2;
	HealthDamageSystem::damages[currentID].multiplier = 1.0f;
	CollisionSystem::rects[currentID].hitboxScaling = 0.5f;
}

bool BulletSystem::timer(int timer) {
	if (now % timer == 0) {
		return true;
	}
	return false;
}


void BulletSystem::recoil() {
	EntityID& currentVessel = EntityManager::currentVessel;
	auto& currentVelocity = MovementSystem::velocities[currentVessel];
	auto& currentPosition = MovementSystem::positions[currentVessel];

	currentVelocity.dx -= static_cast<float>(cos(currentPosition.angle * 0.0174533f)) * SPACESHIP::RECOIL;
	currentVelocity.dy -= static_cast<float>(sin(currentPosition.angle * 0.0174533f)) * SPACESHIP::RECOIL;
}