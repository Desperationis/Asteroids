#pragma once
#include "TM.h"
#include "Meteor.h"
#include <vector>
struct Bullet
{
	Bullet(int x, int y, int change_x = 0, int change_y = 0)
	{
		dest.x = x;
		dest.y = y;
		this->change_x = change_x;
		this->change_y = change_y;
	}
	void update() { dest.x += change_x; dest.y += change_y; }
	void render() {
		SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);

		SDL_RenderFillRect(Game::renderer, &dest);

		SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
	}
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

	SDL_Rect dest{ 0,0,5,2 };
	int change_x = 0, change_y = 0;
	int current_node;
};
struct Player
{
	SDL_Texture* texture;
	Uint32 then = 0;
	std::vector<Bullet> bullets;
	SDL_Rect dest{ Game::input.mouse[Game::input.X] - (dimensions[0] / 2),Game::input.mouse[Game::input.Y] - (dimensions[1] / 2), 16,16 };
	int dimensions[2];
	int mousePos[2]{ 0,0 }; //used for slight delay
	double angle = 0.0;
	int delta_y = 0, delta_x = 0;
	Player()
	{
		texture = TM::LoadTexture("Assests\\Player.png");
		SDL_QueryTexture(texture, NULL, NULL, &dimensions[0], &dimensions[1]); //w  ||  h
	}
	inline bool delay(Uint32 milliseconds)
	{
		if (Game::ticks - then > milliseconds)
		{
			then = Game::ticks;
			return true;
		}

		return false;
	}
	void updateMouse()
	{
		delta_y = Game::input.mouse[Game::input.Y] - mousePos[1];
		delta_x = Game::input.mouse[Game::input.X] - mousePos[0];
		if (delta_y != 0 && delta_x != 0)  angle = atan2(delta_y, delta_x) * 180 / M_PI;
		mousePos[0] = Game::input.mouse[Game::input.X];
		mousePos[1] = Game::input.mouse[Game::input.Y];
	}
	void update(std::vector<std::vector<Meteor>>& list)
	{
		if (Game::input.keys[SDL_SCANCODE_SPACE] & delay(BULLETDELAY))
		{
			int mouse_changex = Game::input.mouse[Game::input.X] - mousePos[0];
			int mouse_changey = Game::input.mouse[Game::input.Y] - mousePos[1];
			double dexterity_x = 1;
			double dexterity_y = 1;
			if (mouse_changex != 0)
			{
				dexterity_x = abs(mouse_changex / 5);
			}
			if (mouse_changey != 0)
			{
				dexterity_y = abs(mouse_changey / 5);
			}
			bullets.push_back(Bullet(dest.x, dest.y, mouse_changex / dexterity_x, mouse_changey / dexterity_y));
		}
		updateMouse();
		for (int i = 0; i < list.size(); i++)
		{
			for (int j = 0; j < list[i].size(); j++)
			{
				if (mousePos[0] < list[i][j].dest.x + list[i][j].dest.w &&
					mousePos[0]+ dimensions[0] > list[i][j].dest.x &&
					mousePos[1]< list[i][j].dest.y + list[i][j].dest.h &&
					mousePos[1]+ dimensions[0]> list[i][j].dest.y)
				{
					list[i].clear();
				}
			}
		}
		int end = bullets.size();
		int x = 0;
		for (; x < end;)
		{
			Bullet& bullet = bullets[x];
			bullet.update();
			bullet.current_node = 0;
			if (bullet.dest.x >= (Game::WINDOWWIDTH / 2) && bullet.dest.y <= (Game::WINDOWHEIGHT / 2)) bullet.current_node = 1;
			if (bullet.dest.x <= (Game::WINDOWWIDTH / 2) && bullet.dest.y >= (Game::WINDOWHEIGHT / 2)) bullet.current_node = 2;
			if (bullet.dest.x >= (Game::WINDOWWIDTH / 2) && bullet.dest.y >= (Game::WINDOWHEIGHT / 2)) bullet.current_node = 3;

			if (bullet.dest.x < 0 || bullet.dest.y < 0 || bullet.dest.x > Game::WINDOWWIDTH || bullet.dest.y > Game::WINDOWHEIGHT)
			{
				bullets.erase(bullets.begin() + x);
				x -= 1;
				end -= 1;
			}
			else {
				for (int j = 0; j < list[bullet.current_node].size(); j++)
				{
					if (bullet.dest.x > list[bullet.current_node][j].dest.x && bullet.dest.x < list[bullet.current_node][j].dest.x + list[bullet.current_node][j].dest.w
						&& bullet.dest.y > list[bullet.current_node][j].dest.y && bullet.dest.y < list[bullet.current_node][j].dest.y + list[bullet.current_node][j].dest.h)
					{
						list[bullet.current_node][j].die(list, bullet.current_node);
						list[bullet.current_node].erase(list[bullet.current_node].begin() + j );
						bullets.erase(bullets.begin() + x);
						x -= 1;
						end -= 1;
					}
				}
				//Current Situation: bullets now crash the program if it spawn in a meteor
			}
			x++;

		}
	}

	void render()
	{
		dest.x = Game::input.mouse[Game::input.X] - (dest.w / 2);
		dest.y = Game::input.mouse[Game::input.Y] - (dest.h / 2);
		TM::DrawTextureEx(texture, dest, SDL_FLIP_NONE, angle);
	};
};