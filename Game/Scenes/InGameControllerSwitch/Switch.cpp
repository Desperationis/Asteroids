#include "Switch.h"
#include "../SceneManager/SceneManager.h"
#include "../ButtonSystem.h"
#include "../../Systems/InputSystem/InputSystem.h"
EntityID switchID;
GameControllerSwitch::GameControllerSwitch() {
	ButtonInfo* info = new ButtonInfo{
		COMPONENT_DRAWN | COMPONENT_SWITCH,
		{30,CONSOLE::WINDOW_HEIGHT - 30 - 37,125,37},
		SceneManager::Scenes::GAME,
		"Controller",
		{ 0,0,0,255 },
		{ 255,255,255,155 },
		"../Assests/TitleScreen.png",
		"../Fonts/emulogic.ttf",
		12
	};

	switchID = SceneManager::allocateButton(*info);
	delete info;

	info = new ButtonInfo{
		COMPONENT_DRAWN | COMPONENT_SCENE,
		{165,CONSOLE::WINDOW_HEIGHT - 30 - 37,125,37},
		SceneManager::Scenes::MENU,
		"Back",
		{ 0,0,0,255 },
		{ 255,255,255,155 },
		"../Assests/TitleScreen.png",
		"../Fonts/emulogic.ttf",
		12
	};

	SceneManager::allocateButton(*info);
	delete info;
}

void GameControllerSwitch::update() {
	if (ButtonSystem::switches[switchID]._switch_) {
		SDL_Color tmp{ 100,100,100,255 };
		ButtonSystem::buttons[switchID].bg_color = tmp;
		InputSystem::usingController = true;
	}
	else {
		SDL_Color tmp{ 255,255,255,255 };
		ButtonSystem::buttons[switchID].bg_color = tmp;
		InputSystem::usingController = false;
	}
}
