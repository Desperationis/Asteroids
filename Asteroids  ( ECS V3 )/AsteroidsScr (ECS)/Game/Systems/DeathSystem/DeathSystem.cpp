#include "DeathSystem.h"
#include "../ScoreSystem/ScoreSystem.h"
#include "../RenderingSystem/RenderingSystem.h"

bool DeathSystem::dead = false;
std::vector<EntityID> DeathSystem::tmp;

void DeathSystem::die() {
	auto& currentMask = EntityManager::entities[EntityManager::currentVessel].mask;

	for (auto it = EntityManager::names.begin(); it != EntityManager::names.end(); it++) {
		if (it->second.name.find("Meteor") != std::string::npos) {
			tmp.push_back(it->first);
		}
	}
	for (int i = 0; i < tmp.size(); i++) {
		EntityManager::freeID(tmp[i]);
	}
	tmp.clear();
	dead = true;
}

void DeathSystem::update() {
	if (dead) {
		dead = false;
	}
}
