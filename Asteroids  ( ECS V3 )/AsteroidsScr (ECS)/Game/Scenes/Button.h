#pragma once
#include "../../Tools/TM.h"
#include "../Entities/Entity.h"
#include "../Systems/FontSystem/FontSystem.h"

struct Button : public Entity {
	Button() {};
	void render();
	SDL_Rect dest, textDest;
	int scene = 0;
	
	Font font;
	SDL_Color bg_color{ 255,255,255,255  };
	SDL_Texture* texture = nullptr;
	bool textureLoaded = false;
};
