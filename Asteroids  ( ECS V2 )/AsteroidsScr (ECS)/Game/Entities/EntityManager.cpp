#include "EntityManager.h"
#include "../SystemManagerNamespace.h"
using namespace SystemsNamespace;
SDL_Texture* EntityManager::spritesheet;
ComponentMap<Name> EntityManager::names;
int EntityManager::nextID = 0;
ComponentMap<Entity> EntityManager::entities;
EntityID EntityManager::currentVessel;

EntityManager::EntityManager()
{
	spritesheet = TM::LoadTexture("Assests\\MeteorsAssests.png");

	initSystems();
	allocateMemory();
	currentVessel = allocateEntity("Vessel", CONSOLE::WINDOW_WIDTH / 2 - 25, CONSOLE::WINDOW_HEIGHT / 2 - 25, 50, 50, 0, 0, 50, 50, COMPONENT_VESSEL).id;
	CollisionSystem::rects[currentVessel].hitboxScaling = 4.0f;

}

bool tmp = false;
void EntityManager::update()
{
	for (auto it = entities.begin(); it != entities.end(); it++) {
		movementSystem->updatePhysics(it.key(), entities[it.key()].mask);
	}
	if ((InputSystem::keys[SDL_SCANCODE_TAB] || InputSystem::GetButton(SDL_CONTROLLER_BUTTON_B)) && !tmp) {
		float angle = 0.0f;
		for (unsigned int i = 0; i < 50; i++) {
			angle = rand() % 3600 / 10.0f;
			meteorSystem->allocateMeteor(CONSOLE::WINDOW_WIDTH / 2 - 25, CONSOLE::WINDOW_HEIGHT / 2 - 25, cos(angle * 0.0174533f) * 5, sin(angle *0.0174533f) * 5, COMPONENT_METEOR);
		}
	}
	tmp = (InputSystem::keys[SDL_SCANCODE_TAB] || InputSystem::GetButton(SDL_CONTROLLER_BUTTON_B));

	collisionSystem->update();
	collisionSystem->checkCollisions();
	bulletSystem->update();
	scoreSystem->update();
	deathSystem->update();
}


void EntityManager::render()
{
	bool renderNode = InputSystem::keys[SDL_SCANCODE_LSHIFT];

	for (auto it = entities.begin(); it != entities.end(); it++) {
		renderingSystem->renderEntity(it.key());
		collisionSystem->renderRect(it.key());

		if (renderNode) {
			SDL_SetRenderDrawColor(Game::renderer, (MovementSystem::positions[it.key()].node + 1) * 2,
				(MovementSystem::positions[it.key()].node + 1) * 2,
				(MovementSystem::positions[it.key()].node + 1) * 2, 255);
			SDL_RenderFillRect(Game::renderer, &RenderingSystem::textures[it.key()].dest);
		}
	}

	scoreSystem->render();
}

void EntityManager::allocateID(Entity& entity, const char* name)
{
	auto& id = entity.id;
	auto& mask = entity.mask;
	id = nextID; nextID++;

	if ((mask & COMPONENT_TEXTURE) == COMPONENT_TEXTURE) {
		renderingSystem->allocateID(id);
	}
	if ((mask & COMPONENT_MOVEMENT) == COMPONENT_MOVEMENT) {
		movementSystem->allocateID(id);
	}
	if ((mask & COMPONENT_COLLISION) == COMPONENT_COLLISION) {
		collisionSystem->allocateID(id);
	}
	if ((mask & COMPONENT_SCORE) == COMPONENT_SCORE) {
		scoreSystem->allocateID(id);
	}
	names[id] = Name{ name }; //doesn't actually save memory - velocity would be applied to a static object
}

void EntityManager::freeID(const EntityID& id) {
	collisionSystem->freeID(id);
	movementSystem->freeID(id);
	renderingSystem->freeID(id);
	scoreSystem->freeID(id);
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