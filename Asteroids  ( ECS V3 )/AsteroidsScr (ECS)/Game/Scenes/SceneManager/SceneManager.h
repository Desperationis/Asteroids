#pragma once
#include "../../../Tools/TM.h"
#include "../../Entities/EntityManager.h"
#include "../Button.h"
#include "../../Systems/FontSystem/FontSystem.h"

class SceneManager {
public:
	enum Scenes { NONE, MENU, GAME };
	static Scenes currentScene;

	SceneManager();

	static void update();
	static void render();
	static EntityID allocateButton(int x, int y, int w, int h, Scenes scene, const char* text, SDL_Color& color, SDL_Color& bg_color, const char* file, int ptsize);
	static EntityID allocateButton(int x, int y, int w, int h, const char* texture);
	static void freeID(const EntityID& id);

	static ComponentMap<Button> buttons;
	static Uint32 nextID;
};
