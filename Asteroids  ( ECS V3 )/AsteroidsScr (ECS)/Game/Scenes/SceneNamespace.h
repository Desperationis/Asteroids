#pragma once
#include "../Scenes/Menu/Menu.h"



namespace ScenesNamespace {
	Menu* menu = nullptr;

	void initScenes() {
		menu = new Menu();
	}
}