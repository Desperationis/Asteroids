#include "SceneManager.h"
#include "../SceneNamespace.h"
#include "../../Systems/InputSystem/InputSystem.h"

SceneManager::Scenes SceneManager::currentScene = MENU;
Uint32 SceneManager::nextID = 0;
ComponentMap<Button> SceneManager::buttons;

using namespace ScenesNamespace;

SceneManager::SceneManager() {
	initScenes();
}

bool pressed = false;
void SceneManager::update() {
	switch (currentScene) {
	case GAME:
		Game::EM->update();
		break;
	case MENU:
			if (InputSystem::mouse[InputSystem::LEFT] && !pressed) {
				for (auto it = buttons.begin(); it != buttons.end(); it++) {
					if (InputSystem::mouse[InputSystem::X] < it.value().dest.x + it.value().dest.w &&
						InputSystem::mouse[InputSystem::X] > it.value().dest.x &&
						InputSystem::mouse[InputSystem::Y] < it.value().dest.y + it.value().dest.h &&
						InputSystem::mouse[InputSystem::Y] > it.value().dest.y) {
						if (static_cast<Scenes>(it.value().scene) != NONE) currentScene = static_cast<Scenes>(it.value().scene);
						std::cout << "HIT" << std::endl;
					}
				}
			}
			pressed = InputSystem::mouse[InputSystem::LEFT];
		break;
	}
}

void SceneManager::render() {

	switch (currentScene) {
	case GAME:
		Game::EM->render();
		break;
	case MENU:
		for (auto it = buttons.begin(); it != buttons.end(); it++) {
			it.value().render();
		}
		break;
	}
}

EntityID SceneManager::allocateButton(int x, int y, int w, int h, Scenes scene, const char* text, SDL_Color& color, SDL_Color& bg_color, const char* file, int ptsize) {
	nextID++;
	buttons[nextID] = Button{ };
	auto& currentButton = buttons[nextID];
	currentButton.dest.x = x;
	currentButton.dest.y = y;
	currentButton.dest.w = w;
	currentButton.dest.h = h;
	currentButton.scene = scene;
	currentButton.bg_color = bg_color;

	FontSystem::setUp(currentButton.font, file, ptsize);
	FontSystem::setText(currentButton.font, text, color);

	currentButton.font.dest.x = (currentButton.dest.x + (currentButton.dest.w / 2)) - (currentButton.font.dest.w / 2);
	currentButton.font.dest.y = (currentButton.dest.y + (currentButton.dest.h / 2)) - (currentButton.font.dest.h / 2);

	return nextID;
}

EntityID SceneManager::allocateButton(int x, int y, int w, int h, const char* texture) {
	nextID++;
	buttons[nextID] = Button{ };
	auto& currentButton = buttons[nextID];
	currentButton.dest.x = x;
	currentButton.dest.y = y;
	currentButton.dest.w = w;
	currentButton.dest.h = h;

	currentButton.texture = TM::LoadTexture(texture);
	currentButton.textureLoaded = true;

	return nextID;
}

void SceneManager::freeID(const EntityID& id) {
	buttons.erase(id);
} 