#pragma once
#include "../Game/Game/Game.h"

struct Rect
{
	SDL_Rect dest;
	int right = 0, bottom = 0, left = 0, top = 0, width = 0, height = 0, center[2]{ 0,0 };
	//The Following code cointains data as described:
	//left = x
	//right = x + width
	//top = y
	//bottom = y + height

	Rect() {};
	template<typename T> Rect(const T x , const T y, const T w, const T h)
	{
		GetRect(x, y,w,h);
	}
	template<class T> static bool CollideRect(const T& target1, const T& target2)
	{
		if (target1.left < target2.right &&
			target1.right > target2.left &&
			target1.bottom > target2.top &&
			target1.top< target2.bottom)
		{
			return true;
		}
		return false;
	}
	static void DrawRect(const SDL_Rect& dest , const Uint8 R = 255,const Uint8 G = 0, const Uint8 B = 0)
	{
		SDL_SetRenderDrawColor(Game::renderer, R, G, B, 255);
		SDL_RenderDrawRect(Game::renderer, &dest);
	}
	static void FillRect(const SDL_Rect& dest, const Uint8 R = 255, const Uint8 G = 0, const Uint8 B = 0, const Uint8 A = 255)
	{
		SDL_SetRenderDrawColor(Game::renderer, R, G, B, A);
		SDL_RenderFillRect(Game::renderer, &dest);
	}
	template<typename T>
	void GetRect(const T x, const T y) { //Only call once for non moving objects
		dest.x = left = x;
		dest.y = top = y;
		right = x + width;
		bottom = y + height;
	}
	template<typename T>
	void GetRect(const T x, const T y , const T w, const T h) { //Only call once for non moving objects
		dest.x = left = x;
		dest.y = top = y;
		dest.w = width = w;
		dest.h = height = h;
		right = left + width;
		bottom = top + height;
		center[0] = left + (width / 2);
		center[1] = top + (height / 2);
	}
	void UpdateRect()
	{
		 left = dest.x;
		 top = dest.y;
		 right = left + width;
		 bottom = top + height;
		 center[0] = left + (width / 2);
		 center[1] = top + (height / 2);
	}

	//dest variable for rendering only,
	//pointer that points to dest.x, y, ect.
};
