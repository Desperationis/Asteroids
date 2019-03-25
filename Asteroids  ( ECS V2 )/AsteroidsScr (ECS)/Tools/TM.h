#pragma once
#include "../Game/Game/Game.h"

struct TM
{
	//basic rendering
	static void DrawTexture(SDL_Texture*& texture, SDL_Rect & dest, SDL_Rect& scr);
	static void DrawTexture(SDL_Texture*& texture, SDL_Rect & dest);
	static void DrawTexture(SDL_Texture*& texture);

	//complex rendering
	static void DrawTextureEx(SDL_Texture*& texture, SDL_Rect& dest, SDL_Rect& scr, SDL_RendererFlip SDL_Flip,SDL_Point& p, double angle);
	static void DrawTextureEx(SDL_Texture*& texture, SDL_Rect& dest, SDL_Rect& scr, SDL_RendererFlip SDL_Flip, double angle);
	static void DrawTextureEx(SDL_Texture*& texture, SDL_Rect& dest, SDL_RendererFlip SDL_Flip, double angle);

	//basic loading
	static SDL_Texture* LoadTexture(const char* texture);
	static SDL_Texture* LoadBWTexture(const char* texture);

	//complex blending
	static void SetAlphaBlending(SDL_Texture*& texture);
	static void RemoveAlphaBlending(SDL_Texture*& texture);
	static void SetAlpha(SDL_Texture*& texture, Uint8 alpha);

	//complex altering
	static void SetColorMod(SDL_Texture*& texture, Uint8 R, Uint8 G, Uint8 B);
};