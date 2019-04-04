#include "../CollisionSystem/CollisionSystem.h"
#include "../RenderingSystem/RenderingSystem.h"
#include "../MovementSystem/MovementSystem.h"
#include "../ScoreSystem/ScoreSystem.h"
#include "../DeathSystem/DeathSystem.h"


ComponentMap<Rect> CollisionSystem::rects;
std::vector<ComponentMap<EntityID>> CollisionSystem::nodes;


void CollisionSystem::checkCollision(const EntityID& id, const char* name) {
	auto& names = EntityManager::names;
	auto& positions = MovementSystem::positions;
	bool player = EntityManager::currentVessel == id;
	

	for (auto it = nodes[positions[id].node].begin(); it != nodes[positions[id].node].end(); it++) {
		if (names[it.key()].name.find(name) != std::string::npos) {
			if (CollideRect(rects[it.key()], rects[id]) && it.key() != id) {
				if (player) {
					DeathSystem::die();
				}
				else {
					EntityManager::freeID(it.key());
					ScoreSystem::scores[EntityManager::currentVessel].score++;
				}
			}
		}
	}
}

void CollisionSystem::checkCollisions() {
	auto& entities = EntityManager::entities;
	auto& names = EntityManager::names;
	auto& positions = MovementSystem::positions;
	for (auto it = entities.begin(); it != entities.end(); it++) {
		if (names[it.key()].name.find("Bullet") != std::string::npos) {
			if (positions.find(it.key()) != positions.end()) {
				checkCollision(it.key(), "Meteor");
			}
		}
	}
	checkCollision(EntityManager::currentVessel, "Meteor");
}

void CollisionSystem::update() {
	for (auto it = rects.begin(); it != rects.end(); it++) {
		auto& currentRect = it.value();
		updateSingle(it.key());
	}
}

void CollisionSystem::updateSingle(const EntityID& id){
	auto& currentRect = rects[id];
	auto& currentPos = RenderingSystem::textures[id].dest;

	currentRect.left = static_cast<float>(currentPos.x);
	currentRect.right = static_cast<float>(currentPos.x + currentPos.w);
	currentRect.top = static_cast<float>(currentPos.y);
	currentRect.bottom = static_cast<float>(currentPos.y + currentPos.h);
	currentRect.center[0] = static_cast<float>(currentPos.x + (currentPos.w / 2.0f));
	currentRect.center[1] = static_cast<float>(currentPos.y + (currentPos.h / 2.0f));

	if ((EntityManager::entities[id].mask & COMPONENT_HITBOX) == COMPONENT_HITBOX) {
		currentRect.left = currentRect.center[0] - (currentPos.w / rects[id].hitboxScaling);
		currentRect.right = currentRect.center[0] + (currentPos.w / rects[id].hitboxScaling);
		currentRect.top = currentRect.center[1] - (currentPos.h / rects[id].hitboxScaling);
		currentRect.bottom = currentRect.center[1] + (currentPos.h / rects[id].hitboxScaling);
	}
}

void CollisionSystem::allocateID(const EntityID& id) {
	rects[id] = Rect{};
}

void CollisionSystem::freeID(const EntityID& id) {
	rects.erase(id);
	nodes[MovementSystem::positions[id].node].erase(id);
}

void CollisionSystem::formatRect(const EntityID& id, int x, int y, int w, int h) {
	auto& currentRect = CollisionSystem::rects[id];

	currentRect.left = static_cast<float>(x);
	currentRect.top = static_cast<float>(y);
	currentRect.right = static_cast<float>(x + w);
	currentRect.bottom = static_cast<float>(y + h);
}

void CollisionSystem::renderRect(const EntityID& id) {
	SDL_SetRenderDrawColor(Game::renderer, 0, 155, 155, 255);
	SDL_Rect tmp { rects[id].left, rects[id].top, rects[id].right - rects[id].left, rects[id].bottom - rects[id].top };
	SDL_RenderDrawRect(Game::renderer, &tmp);
}



