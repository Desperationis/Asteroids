#include "Game.h"
#include "../Entities/EntityManager.h"


SDL_Renderer* Game::renderer;
SDL_Window* Game::window;
Uint8 Game::countedFrames = 0;

Game::Game(const char* title, int w, int h, Uint32 flags, int x, int y)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == NULL)
	{
		if (TTF_Init() == NULL) { printf("-True Type \n"); }
		else { printf("FAILURE - True Type \n"); }

		window = SDL_CreateWindow(title, x, y, w, h, flags);
		renderer = SDL_CreateRenderer(window, -1, CONSOLE::RENDERER_FLAGS);

		running = true;
		SDL_SetRenderDrawColor(renderer, CONSOLE::RENDERER_DRAWCOLOR[0], 
			CONSOLE::RENDERER_DRAWCOLOR[1], CONSOLE::RENDERER_DRAWCOLOR[2], 255);
		SDL_SetRenderDrawBlendMode(Game::renderer, SDL_BLENDMODE_BLEND);
	}
	else {  running = false; }

	EM = new EntityManager();
}
Uint64 now = 0;
void Game::update()
{
	now = SDL_GetTicks();
	float avgFPS = countedFrames / (now / 1000.0f);
	if (avgFPS > 2000000) avgFPS = 0; 
	if (countedFrames % 30 == 0) std::cout << avgFPS << std::endl;
	EM->update();
	++countedFrames;
}
void Game::render()
{
	SDL_RenderClear(renderer);

	EM->render();

	SDL_SetRenderDrawColor(renderer, CONSOLE::RENDERER_DRAWCOLOR[0], 
		CONSOLE::RENDERER_DRAWCOLOR[1], CONSOLE::RENDERER_DRAWCOLOR[2], 255);

	SDL_RenderPresent(renderer);
}

void Game::events()
{
	SDL_PollEvent(&event);

	if (event.type == SDL_QUIT)
	{
		running = false;
		return;
	}

	running = EM->events(running);
}

void Game::clean()
{
	TTF_Quit();
	SDL_Quit();
}