#pragma once
#include "TM.h"
#include "Game.h"
class Meteor
{
public:
	double change_x, change_y, angle;
	int delta_x, delta_y;
	int current_node = 0;

	static SDL_Texture* texture;
	SDL_Rect dest{ 350,350,50,50 };
	enum SIZES{SMALL = 30, NORMAL = 40, LARGE = 50};
	Meteor() {
		texture = TM::LoadTexture("Assests\\Meteor.png");
		srand(static_cast<unsigned int>(time(0)));

		do
		{
			change_x = ((rand() % 1000) - 500) / 100;
		} while (change_x == 0);
		do
		{
			change_y = ((rand() % 1000) - 500) / 100;
		} while (change_y == 0);

		delta_y = change_y - 0;
		delta_x = change_x - 0;
		angle = atan2(delta_y, delta_x) * 180 / M_PI;
	}
	Meteor(int x, int y) {
		do
		{
			change_x = ((rand() % 1000) - 500) / 100;
		} while (change_x == 0);
		do
		{
			change_y = ((rand() % 1000) - 500) / 100;
		} while (change_y == 0);
		delta_y = change_y - 0;
		delta_x = change_x - 0;
		angle = atan2(delta_y, delta_x) * 180 / M_PI;
		dest.x = x; dest.y = y;
	}
	Meteor(int x, int y, int change_x, int change_y) {
		this->change_x = change_x;
		this->change_y = change_y;
		delta_y = change_y - 0;
		delta_x = change_x - 0;
		angle = atan2(delta_y, delta_x) * 180 / M_PI;
		this->dest.x = x; this->dest.y = y;
	}
	Meteor(SDL_Rect& rect, int change_x, int change_y) {
		this->change_x = change_x;
		this->change_y = change_y;
		delta_y = change_y - 0;
		delta_x = change_x - 0;
		angle = atan2(delta_y, delta_x) * 180 / M_PI;
		this->dest.x = rect.x; this->dest.y = rect.y;
		this->dest.w = rect.w; this->dest.h = rect.h;
	}
	void render() { TM::DrawTextureEx(texture, dest, SDL_FLIP_NONE, angle); }
	inline void GetAngle() {
		delta_y = change_y - 0;
		delta_x = change_x - 0;
		angle = atan2(delta_y, delta_x) * 180 / M_PI;
	};
	void renderNode() {
		switch (current_node)
		{
		case 0:
			SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
			SDL_RenderFillRect(Game::renderer, &dest);
			break;
		case 1:
			SDL_SetRenderDrawColor(Game::renderer, 0, 255, 0, 255);
			SDL_RenderFillRect(Game::renderer, &dest);
			break;
		case 2:
			SDL_SetRenderDrawColor(Game::renderer, 0, 0, 255, 255);
			SDL_RenderFillRect(Game::renderer, &dest);
			break;
		case 3:
			SDL_SetRenderDrawColor(Game::renderer, 0, 255, 255, 255);
			SDL_RenderFillRect(Game::renderer, &dest);
			break;
		}
		SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
	}
	void update() { 
		dest.x += change_x;
		dest.y += change_y;
		
		if (dest.x < -dest.w) dest.x = Game::WINDOWWIDTH;
		if (dest.x > Game::WINDOWWIDTH) dest.x = -dest.w;
		if (dest.y < -dest.h) dest.y = Game::WINDOWHEIGHT;
		if (dest.y > Game::WINDOWHEIGHT) dest.y = -dest.h;
	};
	void die(std::vector<std::vector<Meteor>>& list , int node)
	{
		if (dest.w != 30)
		{
			if (dest.w == 50)
			{
				dest.w = 40;
				dest.h = 40;
			}
			else if (dest.w = 40)
			{
				dest.w = 30;
				dest.h = 30;
			}
			list[node].push_back(Meteor(dest,change_x,change_y));
		}
		
		//Problem 10/1: pushing back a new Meteor returns a pointer, which is why 2 meteros don't appear.
		//Update: I was wrong, the meteors were being edited wrongly when SMALL meteors appear
	}
};

SDL_Texture* Meteor::texture;
