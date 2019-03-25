#include "../BulletSystem/BulletSystem.h"
#include "../InputSystem/InputSystem.h"
#include "../MovementSystem/MovementSystem.h"
#include "../CollisionSystem/CollisionSystem.h"
#include "../RenderingSystem/RenderingSystem.h"

EntityID nameID = 0;
bool spacePressed = false;
void BulletSystem::update() {
	auto& currentID = EntityManager::currentVessel;
	auto& currentMask = EntityManager::entities[currentID].mask;

	if ((currentMask & POWERUP_RAPIDFIRE) == POWERUP_RAPIDFIRE && timer(BULLET::RAPIDFIRE_TICKS)) shoot();

	if (!InputSystem::controllerConnected) {
		if ((InputSystem::keys[SDL_SCANCODE_SPACE] && !spacePressed)) {
			shoot();
		}
		spacePressed = InputSystem::keys[SDL_SCANCODE_SPACE];
	}
	if (InputSystem::controllerConnected) {
		if ((InputSystem::GetButton(SDL_CONTROLLER_BUTTON_A) && !spacePressed)) {
			shoot();
		}
		spacePressed = InputSystem::GetButton(SDL_CONTROLLER_BUTTON_A);
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
	auto currentAngle = MovementSystem::positions[currentVessel].angle;
	auto& currentVelocity = MovementSystem::velocities[currentVessel];
	auto& currentRect = CollisionSystem::rects[currentVessel];
	auto& currentDest = RenderingSystem::textures[currentVessel];

	auto& currentID = EntityManager::allocateEntity(tmp.str().c_str(),
		currentRect.center[0] + (cos((currentAngle + angleOffset) * 0.0174533f) * (currentDest.dest.w / 2.0f)),
		currentRect.center[1] + (sin((currentAngle + angleOffset) * 0.0174533f) * (currentDest.dest.h / 2.0f)),
		5, 5, 25, 25, 2, 2, COMPONENT_BULLET).id;

	MovementSystem::formatIDVelocity(currentID,
		static_cast<float>((float)cos((currentAngle + angleOffset) * 0.0174533f)) * BULLET::MOVEMENT_SPEED, 
		static_cast<float>((float)sin((currentAngle + angleOffset) * 0.0174533f)) * BULLET::MOVEMENT_SPEED, false);
}

bool BulletSystem::timer(int timer) {
	now++;
	if (now % timer == 0) {
		then = now;
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