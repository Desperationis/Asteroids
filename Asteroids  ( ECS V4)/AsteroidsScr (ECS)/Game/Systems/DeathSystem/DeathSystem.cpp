#include "DeathSystem.h"
#include "../ScoreSystem/ScoreSystem.h"
#include "../RenderingSystem/RenderingSystem.h"
#include "../MovementSystem/MovementSystem.h"

bool DeathSystem::dead = false;
std::vector<EntityID> DeathSystem::tmp;
Uint8 DeathSystem::lives = 3;

void DeathSystem::die() {
	auto& currentMask = EntityManager::entities[EntityManager::currentVessel].mask;

	if (lives != 0) {
		lives--;
		MovementSystem::formatIDPosition(EntityManager::currentVessel, CONSOLE::WINDOW_WIDTH / 2 - 25, CONSOLE::WINDOW_HEIGHT / 2 - 25, 0.0);
		MovementSystem::formatIDVelocity(EntityManager::currentVessel, 0.0f, 0.0f, false);
	}

	tmp.clear();
	dead = true;
}

void DeathSystem::update() {
	if (dead) {
		dead = false;
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
