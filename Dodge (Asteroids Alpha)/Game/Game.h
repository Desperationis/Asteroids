#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Input.h"

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
	static Uint16 WINDOWWIDTH;
	static Uint16 WINDOWHEIGHT;
	static Uint32 ticks;
private:
	SDL_Event event;
	bool running;
};
