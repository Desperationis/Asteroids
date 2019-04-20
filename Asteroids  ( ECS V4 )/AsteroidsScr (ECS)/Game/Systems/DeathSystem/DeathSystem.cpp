#include "DeathSystem.h"
#include "../ScoreSystem/ScoreSystem.h"
#include "../RenderingSystem/RenderingSystem.h"
#include "../MovementSystem/MovementSystem.h"
#include "../../Scenes/SceneManager/SceneManager.h"

bool DeathSystem::dead = false;
std::vector<EntityID> DeathSystem::tmp;
Uint8 DeathSystem::lives = 3;
Uint64 DeathSystem::now = 1;

void DeathSystem::die() {
	auto& currentMask = EntityManager::entities[EntityManager::currentVessel].mask;

	if (lives == 0) {
		SceneManager::currentScene = SceneManager::Scenes::MENU;
	}
	if (lives != 0 && !((EntityManager::entities[EntityManager::currentVessel].mask & COMPONENT_INVINCIBLE) == COMPONENT_INVINCIBLE)) {
		lives--;
		MovementSystem::formatIDPosition(EntityManager::currentVessel, CONSOLE::WINDOW_WIDTH / 2 - 25, CONSOLE::WINDOW_HEIGHT / 2 - 25, MovementSystem::positions[EntityManager::currentVessel].angle);
		currentMask |= COMPONENT_INVINCIBLE;
		dead = true;
	}
}

void DeathSystem::update() {
	auto& currentMask = EntityManager::entities[EntityManager::currentVessel].mask;
	if ((currentMask & COMPONENT_INVINCIBLE) == COMPONENT_INVINCIBLE && timer(SPACESHIP::INVINCIBILITY_FRAMES)) {
		currentMask &= ~COMPONENT_INVINCIBLE;
		TM::SetColorMod(EntityManager::spritesheet, 255, 255, 255);
		dead = false;
		now = 1;
	}
	if (dead) {
		now++;
		TM::SetColorMod(EntityManager::spritesheet, 255, (now * 255) / SPACESHIP::INVINCIBILITY_FRAMES, (now * 255) / SPACESHIP::INVINCIBILITY_FRAMES);
	}
}

SDL_Rect scr = { 0,0,50,50 }, dest;
void DeathSystem::render() {
	dest.w = dest.h = ScoreSystem::font.fontDest.h;
	for (int i = 0; i < lives; i++) {
		dest.x = ScoreSystem::font.fontDest.x + ScoreSystem::font.fontDest.w + (40 * (i + 1));
		dest.y = ScoreSystem::font.fontDest.y;
		TM::DrawTexture(EntityManager::spritesheet, dest, scr);
	}
}

bool DeathSystem::timer(int delay) {
	if (now % delay == 0) {
		return true;
	}
	return false;
}