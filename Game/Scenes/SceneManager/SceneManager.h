#pragma once
#include "../../../Tools/TM.h"
#include "../../Entities/EntityManager.h"
#include "../Button.h"
#include "../../Systems/FontSystem/FontSystem.h"

struct ButtonSystem;
struct ButtonInfo;
class SceneManager {
public:
	enum Scenes { NONE, MENU, GAME };
	static Scenes currentScene;

	SceneManager();

	static void update();
	static void render();
	static EntityID allocateButton(ButtonInfo& info);
	static void freeID(const EntityID& id);

	static Uint32 nextID;
};
