#include "RenderingSystem.h"
#include "../MovementSystem/MovementSystem.h"
#include "../HealthDamageSystem/HealthDamageSystem.h"

ComponentMap<Texture> RenderingSystem::textures;

void RenderingSystem::renderEntity(const EntityID& id) {
	auto& texture = textures[id];
	if (EntityManager::names[id].name.find("Meteor") != std::string::npos) {
		TM::SetAlpha(EntityManager::spritesheet, HealthDamageSystem::healths[id].health * 2.55f);
	}
	TM::DrawTextureEx(EntityManager::spritesheet, texture.dest, texture.scr,SDL_FLIP_NONE,MovementSystem::positions[id].angle + 90);
	TM::SetAlpha(EntityManager::spritesheet, 255);
}

void RenderingSystem::allocateID(const EntityID& id) {
	textures[id] = Texture{ { }, { 0,0,0,0} };
}
void RenderingSystem::freeID(const EntityID& id) {
	textures.erase(id);
}
void RenderingSystem::renderAll() {

}
void RenderingSystem::renderRect(const EntityID& id) {
	SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(Game::renderer, &textures[id].dest);
}

void RenderingSystem::formatID(EntityID& id, int x, int y, int w, int h, int x2, int y2, int w2, int h2) {
	auto& dest = RenderingSystem::textures[id].dest;
	auto& scr = RenderingSystem::textures[id].scr;

	dest.x = x;
	dest.y = y;
	dest.w = w;
	dest.h = h;

	scr.x = x2;
	scr.y = y2;
	scr.w = w2;
	scr.h = h2;
}