#pragma once
#include "../stdafx.h"
#include <cmath>
#include <vector>
#include <string>
#include <ctime>
#include "Setup.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "../../Tools/TM.h"
#include "../../Tools/Input.h"

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
	static Input input;
	static SDL_Window * window;
	static SDL_Renderer* renderer;
private:
	EntityManager* EM;
	SDL_Event event;
	bool running;
};
