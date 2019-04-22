#include "../CollisionSystem/CollisionSystem.h"
#include "../RenderingSystem/RenderingSystem.h"
#include "../MovementSystem/MovementSystem.h"
#include "../ScoreSystem/ScoreSystem.h"
#include "../DeathSystem/DeathSystem.h"
#include "../HealthDamageSystem/HealthDamageSystem.h"
#include "../MeteorSystem/MeteorSystem.h"
#include "../UFOSystem/UFOSystem.h"

ComponentMap<Rect> CollisionSystem::rects;
ComponentMap<ComponentMap<EntityID>> CollisionSystem::nodes;
std::vector<EntityID> meteorHitlist, hitlist;

void CollisionSystem::checkCollision(const EntityID& id, const char* name) {
	auto& names = EntityManager::names;
	auto& positions = MovementSystem::positions;
	auto& currentMask = EntityManager::entities[id].mask;
	bool player = EntityManager::currentVessel == id;
	bool bulletDead = false, meteorDead = false;
	


	for (auto it = nodes[positions[id].node].begin(); it != nodes[positions[id].node].end(); it++) {
		if (names[it.key()].name.find(name) != std::string::npos) {
			if (CollideRect(rects[it.key()], rects[id]) && it.key() != id) {


				if (name == "PowerUp") {
					currentMask |= UFOSystem::powerUps[it.key()];
					hitlist.push_back(it.key());
					UFOSystem::powerUps.erase(it.key());
				}
				else if (player) {
					DeathSystem::die();
				}
				else if (name == "EnemyBullet" && player) {
					DeathSystem::die();
				}
				else if(name == "Meteor") {
					while (!meteorDead && !bulletDead) {
						HealthDamageSystem::attack(it.key(), id);

						if (HealthDamageSystem::healths[it.key()].health <= 0.0f) {
							meteorHitlist.push_back(it.key());
							rects[it.key()].angleOfImpact = MovementSystem::positions[id].angle;
							ScoreSystem::scores[EntityManager::currentVessel].score += MeteorSystem::scoreMeteor(static_cast<MeteorSystem::METEOR>(MeteorSystem::sizes[id].size));
							MeteorSystem::meteorsOnScreen--;
							meteorDead = true;
						}
						if (HealthDamageSystem::damages[id].hardness <= 0) {
							hitlist.push_back(id);
							bulletDead = true;
						}
					}
				}
				else if (name == "UFO" && !((currentMask & COMPONENT_ENEMYBULLET) == COMPONENT_ENEMYBULLET)) {
					UFOSystem::allocatePowerUp(it.key(), static_cast<UFOSystem::POWERUP>(rand() % 3));
					if (player) {
						hitlist.push_back(id);
					}
					else if ((currentMask & COMPONENT_ENEMYBULLET) != COMPONENT_ENEMYBULLET) {
						hitlist.push_back(it.key());
						if (!player) {
							hitlist.push_back(id);
						}
					}
				}
				break;
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
				checkCollision(it.key(), "UFO");
			}
		}
	}
	for (int i = 0; i < meteorHitlist.size(); i++) {
		MeteorSystem::splitMeteor(meteorHitlist[i]);
	}
	for (int i = 0; i < meteorHitlist.size(); i++) {
		EntityManager::freeID(meteorHitlist[i]);
	}
	for (int i = 0; i < hitlist.size(); i++) {
		EntityManager::freeID(hitlist[i]);
	}
	hitlist.clear();
	meteorHitlist.clear();

	checkCollision(EntityManager::currentVessel, "Meteor");
	checkCollision(EntityManager::currentVessel, "UFO");
	checkCollision(EntityManager::currentVessel, "PowerUp");
	checkCollision(EntityManager::currentVessel, "EnemyBullet");
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
	auto& currentBetterPos = MovementSystem::positions[id];

	currentRect.left = static_cast<float>(currentPos.x);
	currentRect.right = static_cast<float>(currentPos.x + currentPos.w);
	currentRect.top = static_cast<float>(currentPos.y);
	currentRect.bottom = static_cast<float>(currentPos.y + currentPos.h);
	currentRect.center[0] = static_cast<float>(currentBetterPos.x + (currentPos.w / 2.0f));
	currentRect.center[1] = static_cast<float>(currentBetterPos.y + (currentPos.h / 2.0f));

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



