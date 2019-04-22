#include "SceneManager.h"
#include "../SceneNamespace.h"
#include "../../Systems/InputSystem/InputSystem.h"
#include "../ButtonSystem.h"

SceneManager::Scenes SceneManager::currentScene = MENU;
Uint32 SceneManager::nextID = 0;
using namespace ScenesNamespace;

SceneManager::SceneManager() {
}

void SceneManager::update() {
	switch (currentScene) {
	case GAME:
		if (sWITCH == nullptr) {
			sWITCH = new GameControllerSwitch();
			delete menu;
			menu = nullptr;
		}
		else {
			sWITCH->update();
		}
		Game::EM->update();
		ButtonSystem::update();
		break;
	case MENU:
		if (menu == nullptr) {
			menu = new Menu();
			delete sWITCH;
			sWITCH = nullptr;
			EntityManager::reset();
		}
		ButtonSystem::update();
		break;
	}
}


void SceneManager::render() {

	switch (currentScene) {
	case GAME:
		Game::EM->render();
		ButtonSystem::render();
		break;
	case MENU:
		for (auto it = ButtonSystem::buttons.begin(); it != ButtonSystem::buttons.end(); it++) {
			ButtonSystem::render();
		}
		break;
	}
}

EntityID SceneManager::allocateButton(ButtonInfo& info) {
	nextID++;
	ButtonSystem::allocateID(nextID, info);
	return nextID;
}

void SceneManager::freeID(const EntityID& id) {
	ButtonSystem::buttons.erase(id);
}