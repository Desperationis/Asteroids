#include "MeteorSystem.h"
#include "../MovementSystem/MovementSystem.h"
#include "../CollisionSystem/CollisionSystem.h"

EntityID MeteorSystem::nameID = 0;
ComponentMap<Split> MeteorSystem::sizes;
int MeteorSystem::meteorsOnScreen = 0;
ComponentMap<EntityID> MeteorSystem::meteorID;

EntityID MeteorSystem::allocateMeteor(float x, float y, float dx, float dy, EntityMask mask, METEOR size) {
	std::stringstream tmp; tmp << "Meteor " << nameID;

	int radius = 0;
	switch (size) {
	case SMALL:
		radius = 30;
		break;
	case MEDIUM:
		radius = 50;
		break;
	case LARGE:
		radius = 80;
		break;
	case XLARGE:
		radius = 130;
		break;
	case GIGALARGE:
		radius = 200;
		break;
	case DEUS:
		radius = 400;
		break;
	}


	EntityID& currentID = EntityManager::allocateEntity(tmp.str().c_str(), x, y, radius, radius,
		50 + ((rand() % 3) * 50), 0, 50, 50, mask).id;

	MovementSystem::formatIDVelocity(currentID, dx, dy, false);
	MovementSystem::velocities[currentID].rotation = sqrt((dx * dx) + (dy * dy)) / 2;
	CollisionSystem::rects[currentID].hitboxScaling = 2.0f;
	sizes[currentID].size = size;
	return currentID;
}

void MeteorSystem::allocateID(const EntityID& id) {
	sizes[id] = Split{ };
	meteorID[id] = id;
}

void MeteorSystem::freeID(const EntityID& id) {
	sizes.erase(id);
	meteorID.erase(id);
}

void MeteorSystem::splitMeteor(const EntityID& id) {
	auto& currentRect = CollisionSystem::rects[id];
	auto& currentSize = sizes[id].size;
	auto angle = CollisionSystem::rects[id].angleOfImpact;
	int newSize = currentSize - 1;

	int radius = 0;
	switch (currentSize) {
	case MEDIUM:
		radius = 30;
		break;
	case LARGE:
		radius = 50;
		break;
	case XLARGE:
		radius = 80;
		break;
	case GIGALARGE:
		radius = 130;
		break;
	case DEUS:
		radius = 250;
		break;
	}

	if (newSize != -1) {
		MeteorData data;
		float speedIncrease = 1.0f;
		data.x = currentRect.center[0] - (radius / 2);
		data.y = currentRect.center[1] - (radius / 2);
		switch (currentSize) {
		case LARGE:
			speedIncrease = 1.5f;
			break;
		case MEDIUM:
			speedIncrease = 3.0f;
			break;
		}
		data.dx = cos((angle - 7) * 0.0174533f) * METEOR_::SPEED * speedIncrease;
		data.dy = sin((angle - 7) * 0.0174533f) * METEOR_::SPEED * speedIncrease;
		data.size = static_cast<METEOR>(newSize);
		data.angle = angle - 5;
		EntityManager::queue.push_back(data);

		data.dx = cos((angle + 7) * 0.0174533f) * METEOR_::SPEED * speedIncrease;
		data.dy = sin((angle + 7) * 0.0174533f) * METEOR_::SPEED * speedIncrease;
		data.angle = angle + 5;
		EntityManager::queue.push_back(data);
	}
}

int MeteorSystem::scoreMeteor(METEOR size) {
	int score = 0;
	switch (size) {
	case MeteorSystem::METEOR::SMALL:
		score = 500;
		break;
	case MeteorSystem::METEOR::MEDIUM:
		score = 1000;
		break;
	case MeteorSystem::METEOR::LARGE:
		score = 2000;
		break;
	case MeteorSystem::METEOR::XLARGE:
		score = 5000;
		break;
	case MeteorSystem::METEOR::GIGALARGE:
		score = 10000;
		break;
	case MeteorSystem::METEOR::DEUS:
		score= 100000;
		break;
	};

	return score;
}