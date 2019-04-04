#pragma once
#include "../stdafx.h"
#include "../Game/Setup.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "../../Tools/TM.h"

class EntityManager;
struct Game
{
public:
	Game(const char* title, int w, int h, Uint32 flags = NULL , int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED);
	inline bool Running() { return running; }
	void update();
	void render();
	void events();
	void clean();
	static SDL_Window * window;
	static SDL_Renderer* renderer;
	static Uint8 countedFrames;
private:
	EntityManager* EM;
	SDL_Event event;
	bool running;
};
