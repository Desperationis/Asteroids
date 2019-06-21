#pragma once
#include "Button.h"
#include "../Components/ButtonComponents.h"
#include "SceneManager/SceneManager.h"

using namespace BUTTONMASK;

struct ButtonInfo {
	const ButtonMask mask;
	SDL_Rect dest;
	SceneManager::Scenes scene;
	const char* text;
	SDL_Color color;
	SDL_Color bg_color;
	const char* file;
	const char* fontFile;
	int ptsize;
	//used to set up a button; Doesn't actually contain the data
};

struct ButtonSystem {
	static void update();
	static void render();
	static void allocateID(const EntityID& id, const ButtonInfo& info);
	static void free();

	static ComponentMap<Font> texts;
	static ComponentMap<SDL_Texture*> textures;
	static ComponentMap<SceneManager::Scenes> scenes;
	static ComponentMap<Switch> switches;
	static ComponentMap<Button> buttons;
};
