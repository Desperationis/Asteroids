#include "Menu.h"
#include "../SceneManager/SceneManager.h"

using Scenes = SceneManager::Scenes;

Menu::Menu() {
	SDL_Color color{ 0,0,0,255 }, bg_color{ 255,255,255,255 };
	SceneManager::allocateButton((CONSOLE::WINDOW_WIDTH / 2) - (500/2), (CONSOLE::WINDOW_HEIGHT / 2) - (150 / 2) + 100, 500, 150, Scenes::GAME, "Start (?)", 
		color, bg_color, "Fonts\\8bitoperator_jve.ttf", 64);
	color = bg_color;
	bg_color.r = bg_color.g = bg_color.b = 0;
	SceneManager::allocateButton((CONSOLE::WINDOW_WIDTH / 2) - (500/2), (CONSOLE::WINDOW_HEIGHT / 2) - (50 / 2) - 70, 500,50, Scenes::NONE, "Asteroids",
		color, bg_color, "Fonts\\8bitoperator_jve.ttf", 128);
}