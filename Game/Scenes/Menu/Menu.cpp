#include "Menu.h"
#include "../SceneManager/SceneManager.h"
#include "../ButtonSystem.h"

using Scenes = SceneManager::Scenes;

Menu::Menu() {
	ButtonInfo* info = nullptr;
	info = new ButtonInfo {
		COMPONENT_TEXTURED,
		{0,0,0,0},
		SceneManager::Scenes::NONE,
		"Yeah?",
		{ 0,0,0,255 },
		{ 255,255,255,255 },
		"../Assests/TitleScreen.png",
		"../Fonts/8bitoperator_jve.ttf",
		16
	};

	SceneManager::allocateButton(*info);
	ButtonSystem::buttons[SceneManager::nextID].dest.x = (CONSOLE::WINDOW_WIDTH / 2) - (ButtonSystem::buttons[SceneManager::nextID].dest.w / 2);
	ButtonSystem::buttons[SceneManager::nextID].dest.y = (CONSOLE::WINDOW_HEIGHT / 2) - (ButtonSystem::buttons[SceneManager::nextID].dest.h / 2) - ButtonSystem::buttons[SceneManager::nextID].dest.h;


	delete info; info = nullptr;
	info = new ButtonInfo {
		COMPONENT_DRAWN | COMPONENT_SCENE,
		{(CONSOLE::WINDOW_WIDTH / 2) - (500 / 2), (CONSOLE::WINDOW_HEIGHT / 2) - (150 / 2) + 100, 500,150},
		SceneManager::Scenes::GAME,
		"Start (?)",
		{ 0,0,0,255 },
		{ 255,255,255,255 },
		"../Assests/TitleScreen.png",
		"../Fonts/8bitoperator_jve.ttf",
		64
	};

	SceneManager::allocateButton(*info);
	delete info; info = nullptr;
}
