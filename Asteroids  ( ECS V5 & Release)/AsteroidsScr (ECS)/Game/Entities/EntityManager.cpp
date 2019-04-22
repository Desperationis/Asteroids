#include "EntityManager.h"
#include "../SystemManagerNamespace.h"

using namespace SystemsNamespace;
SDL_Texture* EntityManager::spritesheet;
ComponentMap<Name> EntityManager::names;
int EntityManager::nextID = 0;
ComponentMap<Entity> EntityManager::entities;
EntityID EntityManager::currentVessel;
std::vector<MeteorData> EntityManager::queue;

EntityManager::EntityManager()
{
	spritesheet = TM::LoadTexture("Assests\\MeteorsAssests.png");

	initSystems();
	allocateMemory();
	reset();

}

bool tmp = false;
void EntityManager::update()
{
	MeteorSystem::meteorsOnScreen = MeteorSystem::meteorID.size();
	if (MeteorSystem::meteorsOnScreen == 0 && queue.size() == 0) {
		LevelSystem::currentLevel++;
		LevelSystem::loadLevel(LevelSystem::currentLevel);
	}
	for (auto it = queue.begin(); it != queue.end(); it++) {
		MovementSystem::positions[meteorSystem->allocateMeteor(it->x, it->y, it->dx, it->dy, COMPONENT_METEOR, it->size)].angle = it->angle;
	}
	for (auto it = entities.begin(); it != entities.end(); it++) {
		movementSystem->updatePhysics(it.key(), entities[it.key()].mask);
	}
	if ((InputSystem::keys[SDL_SCANCODE_TAB] || InputSystem::GetButton(SDL_CONTROLLER_BUTTON_B)) && !tmp) {
		float angle = 0.0f;
		for (unsigned int i = 0; i < 5; i++) {
			angle = rand() % 3600 / 10.0f;
			meteorSystem->allocateMeteor(CONSOLE::WINDOW_WIDTH / 2 - 25, CONSOLE::WINDOW_HEIGHT / 2 - 25, cos(angle * 0.0174533f) * METEOR_::SPEED, sin(angle *0.0174533f) * METEOR_::SPEED, COMPONENT_METEOR, MeteorSystem::LARGE);
		}
	}
	queue.clear();
	tmp = (InputSystem::keys[SDL_SCANCODE_TAB] || InputSystem::GetButton(SDL_CONTROLLER_BUTTON_B));

	bulletSystem->update();
	scoreSystem->update();
	deathSystem->update();
	aiSystem->update();
	collisionSystem->update();
	collisionSystem->checkCollisions();
}

void EntityManager::render()
{
	SDL_Rect tmp{ ENTITY::BORDER_DISTANCE - 100,0,100,1080 };
	bool playerOutline = InputSystem::keys[SDL_SCANCODE_LSHIFT];

	for (auto it = entities.begin(); it != entities.end(); it++) {
		renderingSystem->renderEntity(it.key());
		if (InputSystem::keys[SDL_SCANCODE_LCTRL]) { collisionSystem->renderRect(it.key()); entities[currentVessel].mask |= POWERUP_GRAPESHOT | POWERUP_RAPIDFIRE | POWERUP_INFINITYBULLET;
		}
	}
	if (playerOutline) {
		TM::SetColorMod(spritesheet, 0, 200, 200);
	}
	renderingSystem->renderEntity(currentVessel);
	TM::SetColorMod(spritesheet, 255, 255, 255);

	SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
	tmp.x = ENTITY::BORDER_DISTANCE - 100;
	SDL_RenderFillRect(Game::renderer, &tmp);
	tmp.x = CONSOLE::WINDOW_WIDTH - ENTITY::BORDER_DISTANCE;
	SDL_RenderFillRect(Game::renderer, &tmp);
	scoreSystem->render();
	levelSystem->render();
	deathSystem->render();
}

void EntityManager::allocateID(Entity& entity, const char* name)
{
	auto& id = entity.id;
	auto& mask = entity.mask;
	id = nextID; nextID++;
	names[id] = Name{ name };

	if ((mask & COMPONENT_COLLISION) == COMPONENT_COLLISION) {
		collisionSystem->allocateID(id);
	}
	if ((mask & COMPONENT_TEXTURE) == COMPONENT_TEXTURE) {
		renderingSystem->allocateID(id);
	}
	if ((mask & COMPONENT_MOVEMENT) == COMPONENT_MOVEMENT) {
		movementSystem->allocateID(id);
	}
	if ((mask & COMPONENT_SCORE) == COMPONENT_SCORE) {
		scoreSystem->allocateID(id);
	}
	if ((mask & COMPONENT_DAMAGE) == COMPONENT_DAMAGE) {
		healthDamageSystem->allocateDamageID(id);
	}
	if ((mask & COMPONENT_HEALTH) == COMPONENT_HEALTH) {
		healthDamageSystem->allocateHealthID(id);
	}
	if ((mask & COMPONENT_SPLIT) == COMPONENT_SPLIT) {
		meteorSystem->allocateID(id);
	}
	if ((mask & COMPONENT_AI) == COMPONENT_AI) {
		aiSystem->allocateID(id);
	}
}

void EntityManager::freeID(const EntityID& id) {
	collisionSystem->freeID(id);
	meteorSystem->freeID(id);
	movementSystem->freeID(id);
	renderingSystem->freeID(id);
	scoreSystem->freeID(id);
	aiSystem->freeID(id);
	names.erase(id);
	entities.erase(id); //erase the actual entity at the end to prevent false-calling
}

Entity& EntityManager::allocateEntity(const char* name, int x = 0, int y = 0, int w = 0, int h = 0, int x2 = 0, int y2 = 0, int w2 = 16, int h2 = 16, EntityMask flags = COMPONENT_NONE) {
	entities[nextID] = Entity();
	auto& entity = entities[nextID];
	entity.mask = flags;
	allocateID(entity, name);

	if ((entity.mask & COMPONENT_MOVEMENT) == COMPONENT_MOVEMENT) {
		movementSystem->formatIDPosition(entity.id, x, y, 0.0);
	}
	if ((entity.mask & COMPONENT_TEXTURE) == COMPONENT_TEXTURE) {
		renderingSystem->formatID(entity.id, x, y, w, h, x2, y2, w2, h2);
	}

	return entity;
}

void EntityManager::allocateMemory() {
	entities.reserve(ENTITY::RESERVE_ENTITIES);
	allocateSystemMemory();
}

void EntityManager::reset() {
	std::vector<EntityID> tmp;
	for (auto it = entities.begin(); it != entities.end(); it++) {
		tmp.push_back(it.value().id);
	}
	for (int i = 0; i < tmp.size(); i++) {
		freeID(tmp[i]);
	}
	tmp.clear();

	currentVessel = allocateEntity("Vessel", CONSOLE::WINDOW_WIDTH / 2 - 25, CONSOLE::WINDOW_HEIGHT / 2 - 25, 40, 40, 0, 0, 50, 50, COMPONENT_VESSEL).id;
	CollisionSystem::updateSingle(currentVessel);
	CollisionSystem::rects[currentVessel].hitboxScaling = 3.0f;
	TM::SetAlphaBlending(spritesheet);
	MeteorSystem::meteorsOnScreen = 0;
	LevelSystem::currentLevel = 0;
	ScoreSystem::scores[currentVessel].score = 0;
	ScoreSystem::scores[currentVessel].preScore = -1;
	DeathSystem::lives = 3;
	DeathSystem::dead = false;
	LevelSystem::loadLevel(0);
}