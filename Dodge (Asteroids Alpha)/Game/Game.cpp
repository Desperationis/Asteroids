#include "stdafx.h"
#include "Game.h"
#include "TM.h"
#include "Meteor.h"
#include "Player.h"

Input Game::input;
SDL_Renderer* Game::renderer;
SDL_Window* Game::window;
std::vector<std::vector<Meteor>> meteors;
Uint16 Game::WINDOWWIDTH;
Uint16 Game::WINDOWHEIGHT;
Player* mouse = nullptr;
Uint32 Game::ticks;
void SpawnMeteor()
{
	int x = rand() % -50, y = rand() % -50;
	while (abs(mouse->mousePos[0] - x) < SPAWN_RANGE && abs(mouse->mousePos[1] - y) < SPAWN_RANGE)
	{
		x = rand() % Game::WINDOWWIDTH, y = rand() % Game::WINDOWHEIGHT;
	}
	meteors[0].push_back(Meteor(x, y));
}
Game::Game(const char* title, int w, int h, Uint32 flags, int x, int y)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == NULL)
	{
		printf("-SDL \n");

		if (TTF_Init() == NULL) { printf("-True Type \n"); }
		else { printf("FAILURE - True Type \n"); }

		window = SDL_CreateWindow(title, x, y, w, h, flags);
		if (window) { printf("-Window \n"); }
		else { printf("FAILURE - Window \n"); }
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) { printf("-Renderer \n"); }
		else { printf("FAILURE - Renderer \n"); }

		running = true;
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	}
	else { printf("FAILURE - SDL \n"); running = false; }
	WINDOWWIDTH = w;
	WINDOWHEIGHT = h;
	for (int i = 0; i < 16; i++)
	{
		meteors.push_back(std::vector<Meteor>());
	}
	
	meteors[0].push_back(Meteor());
	mouse = new Player();
}
Uint32 frame = 0;
void Game::update()
{
	ticks = SDL_GetTicks();
	frame += 1;
	if (frame % METEOR_RATE == 0) SpawnMeteor();
	for (int i = 0; i < meteors.size(); i++)
	{
		for (int j = 0; j < meteors[i].size(); j++)
		{
			meteors[i][j].update();

			if (meteors[i][j].dest.x <= (Game::WINDOWWIDTH/2) && meteors[i][j].dest.y <= (Game::WINDOWHEIGHT / 2) && meteors[i][j].current_node != 0)
			{
				meteors[0].push_back(Meteor(meteors[i][j]));
				meteors[i].erase(meteors[i].begin() + j);
				meteors[0][meteors[0].size() - 1].current_node = 0;
			}
			else if (meteors[i][j].dest.x >= (Game::WINDOWWIDTH / 2) && meteors[i][j].dest.y <= (Game::WINDOWHEIGHT / 2) && meteors[i][j].current_node != 1)
			{
				meteors[1].push_back(Meteor(meteors[i][j]));
				meteors[i].erase(meteors[i].begin() + j);
				meteors[1][meteors[1].size() - 1].current_node = 1;
			}
			else if (meteors[i][j].dest.x <= (Game::WINDOWWIDTH / 2) && meteors[i][j].dest.y >=(Game::WINDOWHEIGHT / 2) && meteors[i][j].current_node != 2)
			{
				meteors[2].push_back(Meteor(meteors[i][j]));
				meteors[i].erase(meteors[i].begin() + j);
				meteors[2][meteors[2].size() - 1].current_node = 2;
			}
			else if (meteors[i][j].dest.x >= (Game::WINDOWWIDTH / 2) && meteors[i][j].dest.y >= (Game::WINDOWHEIGHT / 2) && meteors[i][j].current_node != 3)
			{
				meteors[3].push_back(Meteor(meteors[i][j]));
				meteors[i].erase(meteors[i].begin() + j);
				meteors[3][meteors[3].size() - 1].current_node = 3;
			}
		}
	}
	mouse->update(meteors);
}
void Game::render()
{
	SDL_RenderClear(renderer);
	mouse->render();
	for (int i = 0; i < meteors.size(); i++)
	{
		for (int j = 0; j < meteors[i].size(); j++)
		{
			meteors[i][j].render();
			if (input.keys[SDL_SCANCODE_LSHIFT])
			{
				meteors[i][j].renderNode();
			}
		}
	}
	for (int i = 0; i < mouse->bullets.size(); i++)
	{
		mouse->bullets[i].render();
		if (input.keys[SDL_SCANCODE_LSHIFT])
		{
			mouse->bullets[i].renderNode();
		}
	}
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

	input.PumpKeys();
	if (input.keys[SDL_SCANCODE_ESCAPE])
	{
		running = false;
		return;
	}
	if (input.mouse[input.RIGHT])
	{
		SpawnMeteor();
	}
}

void Game::clean()
{
	TTF_Quit();
	SDL_Quit();
}