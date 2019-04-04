#include "MeteorSystem.h"
#include "../MovementSystem/MovementSystem.h"
#include "../CollisionSystem/CollisionSystem.h"

void MeteorSystem::allocateMeteor(float x, float y, float dx, float dy, EntityMask mask) {
	std::stringstream tmp; tmp << "Meteor " << nameID;
	EntityID& currentID = EntityManager::allocateEntity(tmp.str().c_str(), x, y, 30 + ((rand() % 5) * 5), 30 + ((rand() % 5) * 5),
		50 + ((rand() % 2) * 50), 0, 50, 50, mask).id;

	MovementSystem::formatIDVelocity(currentID, dx, dy, false);
	MovementSystem::velocities[currentID].rotation = sqrt((dx * dx) + (dy * dy)) / 2;
	CollisionSystem::rects[currentID].hitboxScaling = 2.5f;
}